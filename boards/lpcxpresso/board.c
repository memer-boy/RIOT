/*
 * File     board_init.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     January 11, 2015, 10:04 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "board.h"
#include "arch/irq_arch.h"
#include "cpuvars.h"
#include "pinblock.h"
#include "bitarithm.h"
#include "cpu.h"

#define PCUART3     (BIT25)
#define PCGPIO      (BIT15)

static pinblock_t connect[] = {
//    CONNECT(PIN(0, 22), DEFAULT, ONCHIP_PULLDOWN, NORMAL), // LED2
    CONNECT(PIN(0, 0), ALTERN2, ONCHIP_PULLUP, NORMAL), // TXD3
    CONNECT(PIN(0, 1), ALTERN2, ONCHIP_PULLUP, NORMAL), // RXD3
    CONNECT(PIN(0, 15), ALTERN2, ONCHIP_PULLDOWN, NORMAL), // SCK0
    CONNECT(PIN(0, 16), ALTERN2, ONCHIP_PULLUP, NORMAL), // SSEL0
    CONNECT(PIN(0, 17), ALTERN2, ONCHIP_PULLDOWN, NORMAL), // MISO0
    CONNECT(PIN(0, 18), ALTERN2, ONCHIP_PULLDOWN, NORMAL) // MOSI0
};

void board_init(void) {
    LPC_SYS_CTL.PLL1CON.PLLC1 = 0;

    LPC_SYS_CTL.PLL1FEED = 0xAA;
    LPC_SYS_CTL.PLL1FEED = 0x55;

    LPC_SYS_CTL.PLL1CON.PLLE1 = 0;

    LPC_SYS_CTL.PLL1FEED = 0xAA;
    LPC_SYS_CTL.PLL1FEED = 0x55;

    LPC_SYS_CTL.PLL0CON.PLLC0 = 0;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    LPC_SYS_CTL.PLL0CON.PLLE0 = 0;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    /* Temporal settings to setup PLL */
    
    LPC_SYS_CTL.CCLKCFG.CCLKSEL = 0;
    LPC_SYS_CTL.SCS.OSCRANGE = 1;
    LPC_SYS_CTL.SCS.OSCEN = 1;
    
    while(LPC_SYS_CTL.SCS.OSCSTAT != 1);
    
    LPC_SYS_CTL.CLKSRCSEL.CLKSRC = CLK_SRC;
    LPC_SYS_CTL.PLL0CFG.MSEL0 = PLL0_M_VAL;
    LPC_SYS_CTL.PLL0CFG.NSEL0 = PLL0_N_VAL;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    LPC_SYS_CTL.PLL0CON.PLLE0 = 1;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    LPC_SYS_CTL.CCLKCFG.CCLKSEL = CCLKSEL_VAL;
    LPC_SYS_CTL.USBCLKCFG.USBSEL = USBSEL_VAL;

    while (LPC_SYS_CTL.PLL0STAT.PLOCK0 != 1);
    
    LPC_SYS_CTL.PLL0CON.PLLC0 = 1;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    LPC_SYS_CTL.PCONP.REGISTER = 0;

    LPC_SYS_CTL.PCLKSEL1.REGISTER = (0x000C0000 | 0x00000C00);

    LPC_SYS_CTL.FLASHCFG.FLASHTIM = 0x4;

    LPC_SYS_CTL.PCONP.REGISTER |= PCGPIO;

    LPC_PINSEL.SEL0 = (0b1010 | 0x80000000);
    LPC_PINSEL.SEL1 = 0b101010;
    LPC_PINMODE.MODE1 = 0x3000;

    LPC_GPIO[0].FIODIR = 0x400000;
    LPC_GPIO[0].FIOSET = 0x400000;

    NVIC_SetPriority(PendSV_IRQn, 0xff);
    //    if (pinblock_init(connect, sizeof(connect))) {
//        // Error connecting pin block, TODO: Tell user about the error!
//    }
}
