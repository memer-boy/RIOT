/*
 * File     hwtimer.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 9, 2015, 10:06 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "arch/hwtimer_arch.h"
#include "periph/timer.h"
#include "board.h"
#include "thread.h"

void irq_handler(int channel);
void (*timeout_handler)(int);

void hwtimer_arch_init(void (*handler)(int), uint32_t fcpu)
{
    timeout_handler = handler;
    timer_init(HWTIMER, 1, &irq_handler);
}

void hwtimer_arch_enable_interrupt(void)
{
    timer_irq_enable(HWTIMER);
}

void hwtimer_arch_disable_interrupt(void)
{
    timer_irq_disable(HWTIMER);
}

void hwtimer_arch_set(unsigned long offset, short timer)
{
    timer_set(HWTIMER, timer, offset);
}

void hwtimer_arch_set_absolute(unsigned long value, short timer)
{
    timer_set_absolute(HWTIMER, timer, value);
}

void hwtimer_arch_unset(short timer)
{
    timer_clear(HWTIMER, timer);
}

unsigned long hwtimer_arch_now(void)
{
    return timer_read(HWTIMER);
}

void irq_handler(int channel)
{
    timeout_handler((short)(channel));
}
