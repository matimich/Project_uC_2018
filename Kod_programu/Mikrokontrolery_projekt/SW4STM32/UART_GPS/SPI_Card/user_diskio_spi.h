/**
 ******************************************************************************
  * @file    user_diskio_spi.h
  * @brief   This file contains the common defines and functions prototypes for  
  *          the user_diskio_spi driver implementation
  ******************************************************************************
  * Portions copyright (C) 2014, ChaN, all rights reserved.
  * Portions copyright (C) 2017, kiwih, all rights reserved.
  *
  * This software is a free software and there is NO WARRANTY.
  * No restriction on use. You can use, modify and redistribute it for
  * personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
  * Redistributions of source code must retain the above copyright notice.
  *
  ******************************************************************************
  */

#ifndef _USER_DISKIO_SPI_H
#define _USER_DISKIO_SPI_H

#include "integer.h" //from FatFs middleware library
#include "diskio.h" //from FatFs middleware library
#include "ff_gen_drv.h" //from FatFs middleware library
#include "main.h"

//we define them as extern because they are defined in a separate .c file to user_diskio.c (which #includes this .h file)

#define FCLK_SLOW() { hspi1.Instance->I2SPR = 256; }	/* Set SCLK = slow */
#define FCLK_FAST() { hspi1.Instance->I2SPR = 16; }	/* Set SCLK = fast */

#define CS_HIGH()	{HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);}
#define CS_LOW()	{HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);}


extern  DSTATUS USER_SPI_initialize (BYTE pdrv);
extern  DSTATUS USER_SPI_status (BYTE pdrv);
extern  DRESULT USER_SPI_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  extern  DRESULT USER_SPI_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  extern  DRESULT USER_SPI_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

#endif
