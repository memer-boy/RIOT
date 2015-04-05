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

static pinblock_t connect[] = {
    CONNECT(PIN(0, 22), DEFAULT, ONCHIP_PULLDOWN, NORMAL), // LED2
    CONNECT(PIN(0, 0), ALTERN2, ONCHIP_PULLUP, NORMAL), // TXD3
    CONNECT(PIN(0, 1), ALTERN2, ONCHIP_PULLUP, NORMAL), // RXD3
    CONNECT(PIN(0, 15), ALTERN2, ONCHIP_PULLDOWN, NORMAL), // SCK0
    CONNECT(PIN(0, 16), ALTERN2, ONCHIP_PULLUP, NORMAL), // SSEL0
    CONNECT(PIN(0, 17), ALTERN2, ONCHIP_PULLDOWN, NORMAL), // MISO0
    CONNECT(PIN(0, 18), ALTERN2, ONCHIP_PULLDOWN, NORMAL) // MOSI0
};

void board_init(void) {
    irq_arch_disable();

    if (LPC_SYS_CTL.PLL0STAT.PLLC0_STAT || LPC_SYS_CTL.PLL0STAT.PLLE0_STAT) {

        LPC_SYS_CTL.PLL0CON.PLLC0 = 0;

        LPC_SYS_CTL.PLL0FEED = 0xAA;
        LPC_SYS_CTL.PLL0FEED = 0x55;

        LPC_SYS_CTL.PLL0CON.PLLE0 = 0;

        LPC_SYS_CTL.PLL0FEED = 0xAA;
        LPC_SYS_CTL.PLL0FEED = 0x55;
    }

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
    
    while(LPC_SYS_CTL.PLL0STAT.PLOCK0 != 1);

    LPC_SYS_CTL.PLL0CON.PLLC0 = 1;

    LPC_SYS_CTL.PLL0FEED = 0xAA;
    LPC_SYS_CTL.PLL0FEED = 0x55;

    if (pinblock_init(connect, sizeof(connect))) {
        // Error connecting pin block, TODO: Tell user about the error!
    }
}