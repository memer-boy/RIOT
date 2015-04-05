/*
 * File     pinblock.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     January 11, 2015, 7:55 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef PINBLOCK_H
#define	PINBLOCK_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define PRIMARY         0b00
#define ALTERN1         0b01
#define ALTERN2         0b10
#define ALTERN3         0b11
#define DEFAULT         PRIMARY

#define ONCHIP_PULLUP   0b00
#define REPEATER        0b01
#define NO_PULLS        0b10
#define ONCHIP_PULLDOWN 0b11

#define NORMAL          0b0
#define OPEN_DRAIN      0b1

#define TPIU_ENABLED    0b10

#define TRACE_BLOCK     0x05
#define TRACE_PIN       0x01

#define PIN(BLOCK,NUMBER)   ( ( (BLOCK & 0x0f) << 4 ) | (NUMBER & 0x0f) )
#define CONNECT(PINDEF, FUNCTION, PULLS, OPENDRAIN) { .cfg = PINDEF, .function = FUNCTION, .mode = PULLS, .opendrain = OPENDRAIN }

typedef struct pinblock {
    uint8_t pin;

    union {

        struct {
            uint8_t function : 2;
            uint8_t mode : 2;
            uint8_t opendrain : 1;
            uint8_t RESERVED : 3;
        };
        uint8_t cfg;
    };
} pinblock_t;

/**
 * @brief Initialize pin connect block.
 * 
 * This function sets the pin function, pin mode and open drain options
 * of each pin defined in the array, other pins not included in the array
 * will have their default function, mode and open drain option.
 * 
 * The array should be initialized statically with a series of CONNECT macro
 * calls, e.g.
 * 
 *  static pincfg_t config[] {
 *      CONNECT(PIN(0,0), ALTERN2, NO_PULLS, OPEN_DRAIN),
 *      CONNECT(PIN(1,1), PRIMARY, ONCHIP_PULLUP, NORMAL),
 *  };
 * 
 * @param [in] config   CONNECTs array.
 * @param [in] len      CONNECTs array length, e.g. sizeof(config).
 * @return              0 if successful, any value otherwise.
 */
uint16_t pinblock_init(pinblock_t *config, uint16_t len);
#ifdef	__cplusplus
}
#endif

#endif	/* PINBLOCK_H */

