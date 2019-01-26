/*
 * zone.h
 *
 *  Created on: 22.12.2018
 *      Author: Mateusz
 */

#ifndef ZONE_ZONE_H_
#define ZONE_ZONE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//utworzenie ramki danych z linkiem do google_maps
void send_google(char data[],char* source);


//sprawdzenie punktow strefy - szer geog
int StrefaSzerokosc(char data[],int Szer_Gorna_Granica,int Szer_Dolna_Granica);

//sprawdzenie punktow strefy - dlug geog
int DlugoscSzerokosc(char data[],int Dl_prawo_Granica,int Dl_lewo_Granica);


/*ustawienie punktow strefy przez uzytkownika - do przyszlego rozwiniecia  */
//void ustaw_punkt_A(int* Szer_Gorna_Granica,int* Szer_Dolna_Granica,int* Dl_prawo_Granica,int* Dl_lewo_Granica);
//void ustaw_punkt_GS(int* Szer_Gorna_Granica); //#6 ustaw gorna szerokosc geograficzna za ktora rejestrator nie moze wyjsc
//void zapisz_do_eeprom(int punkt);




#endif /* ZONE_ZONE_H_ */
