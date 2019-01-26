/*
 * zone.c
 *
 *  Created on: 22.12.2018
 *      Author: Mateusz
 */

#include "zone.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
//50°00.50438'N,020°59.11361'E




void send_google(char data[],char data_2[])
{
	strcpy (data_2,"\r\nFind me on google maps:\n\r");
    strcat (data_2,"http://maps.google.com/maps?q=");
	char array[100] = {
	data[19],data[20],'°',data[21],data[22],'.',data[24],data[25],
	data[26],data[27],data[28],'\'',data[30],',',data[32],data[33],data[34],
	'°',data[35],data[36],'.',data[38],data[39],data[40],data[41],
	data[42],'\'',data[44]};
	strcat (data_2,array);
}


int StrefaSzerokosc(char data[],int Szer_Gorna_Granica,int Szer_Dolna_Granica)
{
	int szerokosc_gps[9];
	int szer_liczba = 0;
	int k = 19;

	for(int i = 0 ; i < 9 ; i++)
	{
		if(k == 23)
		{
			k++;
			i--;
		}
		else
		{
			szerokosc_gps[i] = (int)data[k] - 48;
			int potega = 1;

			for(int j = 0 ; j < (8 - i) ; j++)
			{
				potega = potega * 10;
			}
			if(szerokosc_gps[i]!= 0)
				szer_liczba = szer_liczba +  szerokosc_gps[i]*potega ;
			k++;
		}
	}
	if( data[30] == 'S')	//sprawdzenie znaku
	{
		szer_liczba = -szer_liczba;
	}
	if (szer_liczba < Szer_Gorna_Granica  &&  szer_liczba > Szer_Dolna_Granica)	//sprawdzenie strefy
	return 1; // jest ok
	else // strefa opuszczona
	return 0;
}

int DlugoscSzerokosc(char data[],int Dl_prawo_Granica,int Dl_lewo_Granica)
{
	int dl_gps[10];
	int dl_liczba = 0;
	int k = 32;

	for(int i = 0 ; i < 10 ; i++)
	{
		if(k == 37)
		{
			k++;
			i--;

		}
		else
		{
			dl_gps[i] = (int)data[k] - 48;
			int potega = 1;

			for(int j = 0 ; j < (9 - i) ; j++)
			{
				potega = potega * 10;
			}
			if(dl_gps[i]!= 0)
				dl_liczba = dl_liczba +  dl_gps[i]*potega ;
			k++;
		}
	}

	if( data[44] == 'W')	//sprawdzenie znaku
		dl_liczba = -dl_liczba;

	if (dl_liczba < Dl_prawo_Granica  &&  dl_liczba > Dl_lewo_Granica)	//sprawdzenie strefy
	return 1; // jest ok
	else // strefa opuszczona
	return 0;
}


/*
void zapisz_do_eeprom(int punkt)
{
	if(punkt == 1)
	{

	}
	else if (punkt == 1)
	{

	}
}


void ustaw_punkt_GS(int* Szer_Gorna_Granica)
{
	uint8_t Check = 0;
	uint8_t k = 0;
	uint8_t szerokosc[9] ;

	do
	{
		HAL_UART_Receive(&huart6,&Check,1,10);
		Check =  Check - 48;

		if(Check <= 9 && Check >=0)	//funkcja pobiera znaki dopuki zawieraja sie w przedziale od 0-9
		{
			szerokosc[k] = Check;
			k++;
		}
		else
			break;
	}while(1);

	*Szer_Gorna_Granica = 0; //wyzerowanie poprzedniej wielkosci

	for(int i = 0 ; i < k ; i++)
	{
				int potega = 1;

				for(int j = 0 ; j < (8 - i) ; j++)
				{
					potega = potega * 10;
				}
				if(szerokosc[i]!= 0)
					*Szer_Gorna_Granica = *Szer_Gorna_Granica +  szerokosc[i]*potega ;
	}
	//HAL_UART_Transmit(&huart6, &Check,1,10);
	//HAL_UART_Transmit(&huart6, (uint8_t*) Szer_Gorna_Granica,1,10);
	zapisz_do_eeprom(1);
}
*/



