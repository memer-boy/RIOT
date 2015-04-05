/*
 * File     periph_conf.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 9, 2015, 11:23 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef PERIPH_CONF_H
#define	PERIPH_CONF_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "board.h"

/* Timers */
#define TIMER_NUMOF         4

#define TIMER_0_EN          1
#define TIMER_1_EN          1
#define TIMER_2_EN          1
#define TIMER_3_EN          1

#define TIMER_0_MAX_VALUE   (0xFFFFFFFFu)
#define TIMER_1_MAX_VALUE   (0xFFFFFFFFu)
#define TIMER_2_MAX_VALUE   (0xFFFFFFFFu)
#define TIMER_3_MAX_VALUE   (0xFFFFFFFFu)

#define TIMER_0_CCLK        8
#define TIMER_1_CCLK        8
#define TIMER_2_CCLK        8
#define TIMER_3_CCLK        8

#define HWTIMER             TIMER_0
#define HWTIMER_CHANN       0

/* UARTs */
#define UART_NUMOF          1

#define UART_3_EN           1
    
#define UART_3_CCLK         8

#define BOARD_UART0         UART_3

#ifdef	__cplusplus
}
#endif

#endif	/* PERIPH_CONF_H */

