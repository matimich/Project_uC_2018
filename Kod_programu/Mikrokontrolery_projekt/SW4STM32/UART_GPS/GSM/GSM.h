/*
 * GSM.h
 *
 *  Created on: 12.01.2019
 *      Author: Mateusz
 */

#ifndef GSM_GSM_H_
#define GSM_GSM_H_

#include "stm32f4xx_hal.h"
#include "main.h"

#define NUMER "+48666666666"
#define sprawdz_numer 1

extern uint8_t GSM_Rx;
extern uint8_t GSM_Tx;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;
extern char GSM_Buff[254];

uint8_t numer_sprawdzenie(uint8_t messp[]);		//zabezpieczenie przed nieporzadanym numerem
void GSM_send(char message[],char number[]);   //wysylanie wiadomosci
void GSM_rec_set(void);						  //ustawienie modulu GSM
int GSM_rec_check(void);					 //sprawdzenie otrzymania wiadomosci
void save_mess(char mess[]);				//zapis wiadomosci to buffora



#endif /* GSM_GSM_H_ */
