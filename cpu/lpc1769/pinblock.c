/*
 * File     pinblock.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     January 11, 2015, 8:14 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "pinblock.h"
#include "cpuvars.h"
#include <errno.h>

#define _BLOCK(PIN_DEF) ((PIN_DEF).pin>>4)
#define _PIN(PIN_DEF)   (0xff & (PIN_DEF).pin)


void _pinblock_set_func(pinblock_t);
void _pinblock_set_mode(pinblock_t);
void _pinblock_set_mode_od(pinblock_t);

uint16_t pinblock_init(pinblock_t *config, uint16_t len) {
    for (; len > 0; len--) {
        uint8_t block = _BLOCK(*config);
        uint8_t pin = _PIN(*config);

        switch (block) {
        case 0:
            if ((pin > 30) || (pin > 11 && pin < 15)) {
                return ENXIO;
            }
            break;
        case 1:
            if ((pin > 31) ||
                (pin > 1 && pin < 4) ||
                (pin > 4 && pin < 8) ||
                (pin > 10 && pin < 14)) {
                return ENXIO;
            }
            break;
        case 2:
            if (pin > 13) {
                return ENXIO;
            }
            break;
        case 3:
            if (pin != 25 || pin != 26) {
                return ENXIO;
            }
            break;
        case 4:
            if (pin != 28 || pin != 29) {
                return ENXIO;
            }

            break;
        case 5:
            if (pin != 3) {
                return ENXIO;
            }

            _pinblock_set_func(*config);

            config++;

            continue;
        }

        _pinblock_set_func(*config);
        _pinblock_set_mode(*config);
        _pinblock_set_mode_od(*config);

        config++;
    }

    return 0;
}

void _pinblock_set_func(pinblock_t config) {
    uint8_t block = _BLOCK(config);
    uint8_t pin = _PIN(config);
    uint32_t func = config.function;
    uint32_t mask = 0b11;
    uint32_t reg = &LPC_PINSEL.SEL0;

    switch (block) {
    case 0:
        if (pin > 15) {
            reg = &LPC_PINSEL.SEL1;
            pin = pin % 16;
        }
        break;
    case 1:
        if (pin > 15) {
            reg = &LPC_PINSEL.SEL3;
            pin = pin % 16;
        }
        else {
            reg = &LPC_PINSEL.SEL2;
        }
        break;
    case 2:
        reg = &LPC_PINSEL.SEL4;
        break;
    case 3:
        reg = &LPC_PINSEL.SEL7;
        break;
    case 4:
        reg = &LPC_PINSEL.SEL9;
        break;
    case 5:
        reg = &LPC_PINSEL.SEL10;
        break;
    }

    func = func << (pin * 2);
    mask = mask << (pin * 2);

    reg &= ~mask;
    reg = func;
}

void _pinblock_set_mode(pinblock_t config) {
    uint8_t block = _BLOCK(config);
    uint8_t pin = _PIN(config);
    uint32_t mode = config.mode;
    uint32_t mask = 0b11;
    uint32_t reg = &LPC_PINMODE.MODE0;

    switch (block) {
    case 0:
        if (pin > 15) {
            reg = &LPC_PINMODE.MODE1;
            pin = pin % 16;
        }
        break;
    case 1:
        if (pin > 15) {
            reg = &LPC_PINMODE.MODE3;
            pin = pin % 16;
        }
        else {
            reg = &LPC_PINMODE.MODE2;
        }
        break;
    case 2:
        reg = &LPC_PINMODE.MODE4;
        break;
    case 3:
        reg = &LPC_PINMODE.MODE7;
        break;
    case 4:
        reg = &LPC_PINMODE.MODE9;
        break;
    }

    mode = mode << (pin * 2);
    mask = mask << (pin * 2);

    reg &= ~mask;
    reg = mode;
}

void _pinblock_set_mode_od(pinblock_t config) {
    uint8_t block = _BLOCK(config);
    uint8_t pin = _PIN(config);
    uint32_t od = config.opendrain;
    uint32_t mask = 0b1;
    uint32_t reg = &LPC_PINMODEOD.OD[block];

    od = od << pin;
    mask = mask << pin;

    reg &= ~mask;
    reg = od;
}
