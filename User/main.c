/**************************
  * @file     main.c
  * @version  V1.00
  * @brief    A project template for M031 MCU.
  *
  * SPDX-License-Identifier: Apache-2.0
  * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
***************************/
#include <stdio.h>
#include "NuMicro.h"

#define PB_MODE (*(volatile uint32_t *)(0x40004000+0x040))
/*PBMODE reg add */
#define SYS_GPB_MFPL (*(volatile uint32_t*)(0x40000000+0x38))
/*SYS_GPB_MFPL reg add */
#define UART_FUNCSEL (*(volatile uint32_t*)(0x40070000 + 0x30))
/*UARTFUNCSEL reg add */
#define UART_LINE (*(volatile uint32_t*)(0x40070000 + 0x0C))
/*UARTLINE reg add */
#define UART_BAUD (*(volatile uint32_t*)(0x40070000 + 0x24))
/*UARTBAUD reg add */
#define CLK_CLKSEL1 (*(volatile uint32_t*)(0X40000200+0x14))
/*CLKSEL1 reg add */
#define CLK_APBCLK0 (*(volatile uint32_t*)(0x40000200+0x08))
/*APBCLK0 reg add */
#define SYS_GPB_MFPH (*(volatile uint32_t*)(0x40000000+0x3C))    /* reg add */
#define UART_DAT (*(volatile uint32_t*)(0x40070000+0x00))
#define SC_INTEN (*(volatile uint32_t*)(0x40070000+0x04))
#define UART_INTEN (*(volatile uint32_t*)(0x40070000+0x04))
#define UART_INTSTS (*(volatile uint32_t*)(0x40070000+0x1C))
void SYS_Init()
{
           CLK_CLKSEL1 = (CLK_CLKSEL1 &(~(0X7<<24))) | (0X3<<24);
                CLK_APBCLK0 = (CLK_APBCLK0 & (~(1<<16))) | ((1<<16));
                PB_MODE= (PB_MODE & ~(0x03<<14));
         SYS_GPB_MFPL = ((SYS_GPB_MFPL & (~(1<<28)))|(0x1<<28));
         SYS_GPB_MFPH = ((
        		 SYS_GPB_MFPH & (~(0x6<<16)|~(0X6<<20)))|((0x6<<16)|(0X6<<20)));
}
void uart()
{
        UART_FUNCSEL = (UART_FUNCSEL & (~(0x7<<0)));
        UART_LINE = (UART_LINE & (~(0X3<<0))) | (0X3<<0);
        UART_BAUD = (UART_BAUD & (~(0X3<<28)));
        UART_BAUD = (UART_BAUD & (~(255<<0))) | (50<<0);
        UART_INTEN= (UART_INTEN &(~(0x1<<0))) |(0x1<<0);
        UART_INTSTS=(UART_INTSTS &(~(0x1<<31))) | (0x1<<31);
}

int main()
{
	SYS_Init();
	uart();

	char c,i;
	unsigned char b[]="RAFFIWOO";

	for(i=0;i<9;i++)
	    	{
	    		UART_DAT=b[i];
	    	}
    while(1)
    {
    	if(UART_INTSTS & (0x1))
    	{
    		c=UART_DAT;
    				printf("%d\n",c);
    	}
    }

}
