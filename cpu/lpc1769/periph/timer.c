/*
 * File     timer.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 9, 2015, 11:19 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "periph/timer.h"
#include "core_cm3.h"
#include "cpuvars.h"
#include "periph_conf.h"
#include "board.h"

#ifdef TIMER_0_EN
#if TIMER_0_CCLK == 8
#define TIMER_0_CCLKSEL     (0b11)
#elif TIMER_0_CCLK == 4
#define TIMER_0_CCLKSEL     (0b00)
#elif TIMER_0_CCLK == 2
#define TIMER_0_CCLKSEL     (0b10)
#elif TIMER_0_CCLK == 1
#define TIMER_0_CCLKSEL     (0b01)
#else
#error TIMER_0_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif

#define TIMER_0_US_CONSTANT ((F_CPU/TIMER_0_CCLK)/1000000UL)

#endif

#ifdef TIMER_1_EN
#if TIMER_1_CCLK == 8
#define TIMER_1_CCLKSEL     (0b11)
#elif TIMER_1_CCLK == 4
#define TIMER_1_CCLKSEL     (0b00)
#elif TIMER_1_CCLK == 2
#define TIMER_1_CCLKSEL     (0b10)
#elif TIMER_1_CCLK == 1
#define TIMER_1_CCLKSEL     (0b01)
#else
#error TIMER_1_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif

#define TIMER_1_US_CONSTANT ((F_CPU/TIMER_1_CCLK)/1000000UL)

#endif

#ifdef TIMER_2_EN
#if TIMER_2_CCLK == 8
#define TIMER_2_CCLKSEL     (0b11)
#elif TIMER_2_CCLK == 4
#define TIMER_2_CCLKSEL     (0b00)
#elif TIMER_2_CCLK == 2
#define TIMER_2_CCLKSEL     (0b10)
#elif TIMER_2_CCLK == 1
#define TIMER_2_CCLKSEL     (0b01)
#else
#error TIMER_2_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif

#define TIMER_2_US_CONSTANT ((F_CPU/TIMER_2_CCLK)/1000000UL)

#endif

#ifdef TIMER_3_EN

#if TIMER_3_CCLK == 8
#define TIMER_3_CCLKSEL     (0b11)
#elif TIMER_3_CCLK == 4
#define TIMER_3_CCLKSEL     (0b00)
#elif TIMER_3_CCLK == 2
#define TIMER_3_CCLKSEL     (0b10)
#elif TIMER_3_CCLK == 1
#define TIMER_3_CCLKSEL     (0b01)
#else
#error TIMER_3_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif

#define TIMER_3_US_CONSTANT ((F_CPU/TIMER_3_CCLK)/1000000UL)

#endif

#define PTIMER_ISR_DECL(X)                      \
void isr_timer ## X(void) {                 \
    int chan = 0;                                   \
    if (timers[X].base->IR.MR0) {               \
        timers[X].base->IR.MR0 = 1;             \
        timers[X].base->MCR.MR0I = 0;           \
        chan = 0;                               \
    }                                           \
    else if (timers[X].base->IR.MR1) {          \
        timers[X].base->IR.MR1 = 1;             \
        timers[X].base->MCR.MR1I = 0;           \
        chan = 1;                               \
    }                                           \
    else if (timers[X].base->IR.MR2) {          \
        timers[X].base->IR.MR2 = 1;             \
        timers[X].base->MCR.MR2I = 0;           \
        chan = 2;                               \
    }                                           \
    else if (timers[X].base->IR.MR3) {          \
        timers[X].base->IR.MR3 = 1;             \
        timers[X].base->MCR.MR3I = 0;           \
        chan = 3;                               \
    }                                           \
    NVIC_ClearPendingIRQ(TIMER ## X ##_IRQn);  \
    timers[X].callback(chan);                   \
}

#if defined(TIMER_0_EN) || defined(TIMER_1_EN) || defined(TIMER_2_EN) || defined(TIMER_3_EN)

struct ptimer {
    lpc_timer_t *base;
    void (*callback)(int);
};

struct ptimer timers[4] = {
    {&LPC_TMR0},
    {&LPC_TMR1},
    {&LPC_TMR2},
    {&LPC_TMR3},
};

const uint8_t current = 0;

int timer_init(tim_t dev, unsigned int us_per_tick, void (*callback)(int)) {

    if (callback == 0 || us_per_tick == 0) {
        return -1;
    }

    switch (dev) {
#ifdef TIMER_0_EN
    case TIMER_0:
        //        timers[dev].base = &LPC_TMR0;
        LPC_SYS_CTL.PCONP.PCTIM0 = 1;

        LPC_SYS_CTL.PCLKSEL0.PCLK_TIMER0 = TIMER_0_CCLKSEL;
        LPC_TMR0.PR = TIMER_0_US_CONSTANT * us_per_tick;
        LPC_TMR0.CTCR.REGISTER = 0;
        LPC_TMR0.TCR.REGISTER = 0b10;
        LPC_TMR0.TCR.REGISTER = 0b01;

        NVIC_EnableIRQ(TIMER0_IRQn);

        break;
#endif
#ifdef TIMER_1_EN
    case TIMER_1:
        //        timers[dev].base = &LPC_TMR1;
        LPC_SYS_CTL.PCONP.PCTIM1 = 1;

        LPC_SYS_CTL.PCLKSEL0.PCLK_TIMER1 = TIMER_1_CCLKSEL;
        LPC_TMR1.PR = TIMER_1_US_CONSTANT * us_per_tick;
        LPC_TMR1.CTCR.REGISTER = 0;
        LPC_TMR1.TCR.REGISTER = 0b10;
        LPC_TMR1.TCR.REGISTER = 0b01;

        NVIC_EnableIRQ(TIMER1_IRQn);

        break;
#endif
#ifdef TIMER_2_EN
    case TIMER_2:
        //        timers[dev].base = &LPC_TMR2;
        LPC_SYS_CTL.PCONP.PCTIM2 = 1;

        LPC_SYS_CTL.PCLKSEL1.PCLK_TIMER2 = TIMER_2_CCLKSEL;
        LPC_TMR2.PR = TIMER_2_US_CONSTANT * us_per_tick;
        LPC_TMR2.CTCR.REGISTER = 0;
        LPC_TMR2.TCR.REGISTER = 0b10;
        LPC_TMR2.TCR.REGISTER = 0b01;

        NVIC_EnableIRQ(TIMER2_IRQn);

        break;
#endif
#ifdef TIMER_3_EN
    case TIMER_3:
        //        timers[dev].base = &LPC_TMR3;
        LPC_SYS_CTL.PCONP.PCTIM3 = 1;

        LPC_SYS_CTL.PCLKSEL1.PCLK_TIMER3 = TIMER_3_CCLKSEL;
        LPC_TMR3.PR = TIMER_3_US_CONSTANT * us_per_tick;
        LPC_TMR3.CTCR.REGISTER = 0;
        LPC_TMR3.TCR.REGISTER = 0b10;
        LPC_TMR3.TCR.REGISTER = 0b01;

        NVIC_EnableIRQ(TIMER3_IRQn);

        break;
#endif
    default: return -1;
    }

    timers[dev].callback = callback;

    return 1;
}

int timer_set(tim_t dev, int channel, unsigned int timeout) {
    unsigned int value = timer_read(dev) + timeout;

    switch (channel) {
    case 0:
        timers[dev].base->MR0 = value;
        timers[dev].base->MCR.MR0I = 1;
        break;
    case 1:
        timers[dev].base->MR1 = value;
        timers[dev].base->MCR.MR1I = 1;
        break;
    case 2:
        timers[dev].base->MR2 = value;
        timers[dev].base->MCR.MR2I = 1;
        break;
    case 3:
        timers[dev].base->MR3 = value;
        timers[dev].base->MCR.MR3I = 1;
        break;
    }

    return 1;
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value) {
    switch (channel) {
    case 0:
        timers[dev].base->MR0 = value;
        timers[dev].base->MCR.MR0I = 1;
        break;
    case 1:
        timers[dev].base->MR1 = value;
        timers[dev].base->MCR.MR1I = 1;
        break;
    case 2:
        timers[dev].base->MR2 = value;
        timers[dev].base->MCR.MR2I = 1;
        break;
    case 3:
        timers[dev].base->MR3 = value;
        timers[dev].base->MCR.MR3I = 1;
        break;
    }

    return 1;
}

int timer_clear(tim_t dev, int channel) {
    switch (channel) {
    case 0:
        timers[dev].base->MR0 = 0;
        timers[dev].base->MCR.MR0I = 0;
        break;
    case 1:
        timers[dev].base->MR1 = 0;
        timers[dev].base->MCR.MR1I = 0;
        break;
    case 2:
        timers[dev].base->MR2 = 0;
        timers[dev].base->MCR.MR2I = 0;
        break;
    case 3:
        timers[dev].base->MR3 = 0;
        timers[dev].base->MCR.MR3I = 0;
        break;
    }

    return 1;
}

unsigned int timer_read(tim_t dev) {
    return timers[dev].base->TC;
}

void timer_start(tim_t dev) {
    timers[dev].base->TCR.CTR_ENABLE = 1;
}

void timer_stop(tim_t dev) {
    timers[dev].base->TCR.CTR_ENABLE = 0;
}

void timer_irq_enable(tim_t dev) {
    switch (dev) {
    case TIMER_0:
        NVIC_EnableIRQ(TIMER0_IRQn);
        break;
    case TIMER_1:
        NVIC_EnableIRQ(TIMER1_IRQn);
        break;
    case TIMER_2:
        NVIC_EnableIRQ(TIMER2_IRQn);
        break;
    case TIMER_3:
        NVIC_EnableIRQ(TIMER3_IRQn);
        break;
    default: break;
    }
}

void timer_irq_disable(tim_t dev) {
    switch (dev) {
    case TIMER_0:
        NVIC_DisableIRQ(TIMER0_IRQn);
        break;
    case TIMER_1:
        NVIC_DisableIRQ(TIMER1_IRQn);
        break;
    case TIMER_2:
        NVIC_DisableIRQ(TIMER2_IRQn);
        break;
    case TIMER_3:
        NVIC_DisableIRQ(TIMER3_IRQn);
        break;
    default:break;
    }
}

void timer_reset(tim_t dev) {
    timers[dev].base->TCR.CTR_RESET = 1;
    __NOP();
    timers[dev].base->TCR.CTR_RESET = 0;
}

#else
#define timer_init(dev, us_per_tick, callback) #error No TIMER_X_EN defined in periph_conf.h
#define timer_set(dev, channel, timeout) #error No TIMER_X_EN defined in periph_conf.h
#define timer_set_absolute(dev, channel, value) #error No TIMER_X_EN defined in periph_conf.h
#define timer_clear(dev, channel) #error No TIMER_X_EN defined in periph_conf.h
#define timer_read(dev) #error No TIMER_X_EN defined in periph_conf.h
#define timer_start(dev) #error No TIMER_X_EN defined in periph_conf.h
#define timer_stop(dev) #error No TIMER_X_EN defined in periph_conf.h
#define timer_irq_enable(dev) #error No TIMER_X_EN defined in periph_conf.h
#define timer_irq_disable(dev) #error No TIMER_X_EN defined in periph_conf.h
#define timer_reset(dev) #error No TIMER_X_EN defined in periph_conf.h
#endif

#ifdef TIMER_0_EN
PTIMER_ISR_DECL(0)
#endif

#ifdef TIMER_1_EN
PTIMER_ISR_DECL(1)
#endif

#ifdef TIMER_2_EN
PTIMER_ISR_DECL(2)
#endif

#ifdef TIMER_3_EN
PTIMER_ISR_DECL(3)
#endif
