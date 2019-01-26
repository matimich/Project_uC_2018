/*
 * GSM.c
 *
 *  Created on: 12.01.2019
 *      Author: Mateusz
 */


#include "GSM.h"
#include "string.h"

uint8_t GSM_Rx;
uint8_t GSM_Tx;
char GSM_Buff[254];

void GSM_send(char message[],char number[])
{
	{
		char* information = "AT\r";
		int length = sprintf(information,"AT\r");
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(2000);
	{
		char* information = "AT+CMGF=1\r";
		int length = sprintf(information,"AT+CMGF=1\r");
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(1000);
	{
	  	char* information = "AT+CMGS=";
	  	int length = sprintf(information,"AT+CMGS=");
	  	HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(500);
	{
		int length = printf("%s",number);
	  	HAL_UART_Transmit(&huart2, (uint8_t*) number,(uint16_t) length,10);
	}
	HAL_Delay(1000);
	{
		int length = printf("%s",message);
	  	HAL_UART_Transmit(&huart2, (uint8_t*) message,(uint16_t) length,10);
	  	GSM_Tx = 0x1A;
	  	HAL_UART_Transmit(&huart2, &GSM_Tx,1,10);
	  	GSM_Tx = 0x0D;
	  	HAL_UART_Transmit(&huart2, &GSM_Tx,1,10);
	  	GSM_Tx = 0x0A;
	}
}



void GSM_rec_set(void)
{
	{
		char* information = "AT\r";
		int length = sprintf(information,"AT\r");
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(2000);
	{
		char* information = "AT+CMGF=1\r";
		int length = sprintf(information,"AT+CMGF=1\r");
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(1000);
	{
		char* information = "AT+CNMI=2,2,0,0\r";
		int length = sprintf(information,"AT+CNMI=2,2,0,0\r");	//wylaczenie zapisywania do pamieci karty
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(1000);
	{
		char* information = "AT+CMGL=\"REC UNREAD\"\r";
		int length = sprintf(information,"AT+CMGL=\"REC UNREAD\"\r");
		HAL_UART_Transmit(&huart2, (uint8_t*) information,(uint16_t) length,10);
	}
	HAL_Delay(1000);
}

int GSM_rec_check(void)
{
	HAL_UART_Receive(&huart2, &GSM_Rx,1,10);
	if(GSM_Rx == 'C')
	{
		HAL_UART_Receive(&huart2, &GSM_Rx,1,10);
		if(GSM_Rx == 'M')
		{
			HAL_UART_Receive(&huart2, &GSM_Rx,1,10);
			if(GSM_Rx == 'T')
			{
				//uint8_t chr[44];
				uint8_t chr[59];
				//HAL_UART_Receive(&huart2, chr,44,10);
				HAL_UART_Receive(&huart2, chr,59,10);
			#if	sprawdz_numer ==1

				if(numer_sprawdzenie(chr) == 1)
				return 1;
				else
				{
					GSM_send(NUMER,"Proba wlamania na telefon\n\r");
					return 0;
				}
			#else
				return 1;
			#endif
			}
			else
			HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);
			}
		else
		HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);
	}
	else
	HAL_UART_Receive_IT(&huart2, &GSM_Rx, 1);
	return 0;
}

void save_mess(char mess[])
{
	int i = 0;
	do
	{
		HAL_UART_Receive(&huart2, &GSM_Rx,1,10);
		GSM_Tx =GSM_Rx;
		mess[i] = GSM_Tx;
		i++;
	}while(GSM_Tx !='x' && GSM_Tx !='X');

	for(uint8_t j=i;j<254;j++)
	{
		mess[i] ='\0';
	}
	HAL_UART_Receive_IT(&huart2,&GSM_Rx,1);
}


uint8_t numer_sprawdzenie(uint8_t messp[])
{
	char numer_2[12] = {messp[3],messp[4],messp[5],messp[6],messp[7],messp[8],messp[9]
	,messp[10],messp[11],messp[12],messp[13]};	//pobranie numeru przychodzacego

	if(strcmp(NUMER,numer_2)!=0)
		return 1;
	else
		return 0;
}

