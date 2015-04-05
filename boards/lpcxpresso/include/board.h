/*
 * File     board.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 21, 2015, 5:19 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef BOARD_H
#define	BOARD_H

#include <stdint.h>
#include "cpu.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define F_CPU   (120000000UL)
#define F_OSC   (12000000UL)
#define CLK_SRC (0b01)          // Main oscillator as source

#define PLL0_M_VAL  (19U)
#define PLL0_N_VAL  (0U)
#define CCLKSEL_VAL (3U)
#define USBSEL_VAL  (9U)

#define STDIO               (BOARD_UART0)
#define STDIO_BAUDRATE      (115200U)
#define STDIO_RX_BUFSIZE    (64U)

#ifdef	__cplusplus
}
#endif

#endif	/* BOARD_H */

