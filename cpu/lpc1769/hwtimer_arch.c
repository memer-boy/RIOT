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

#include "hwtimer_cpu.h"
#include "arch/hwtimer_arch.h"
#include "periph/timer.h"

/**
 * @brief Initialize architecture dependent kernel timer support
 *
 * @param[in] handler   callback that is called when timer @p offset is reached
 * @param[in] fcpu      the core CPU-frequency for tick interval calculation
 */

void hwtimer_arch_init(void (*handler)(int), uint32_t fcpu){
    timer_init(HWTIMER, 1, handler);
}

/**
 * @brief Enable interrupts of hardware timers
 */
void hwtimer_arch_enable_interrupt(void){
    timer_irq_enable(HWTIMER);
}

/**
 * @brief Disable interrupts of hardware timers
 */
void hwtimer_arch_disable_interrupt(void){
    timer_irq_disable(HWTIMER);
}

/**
 * @brief Set a kernel timer to raise an interrupt after @p offset kernel timer
 *              ticks from now
 *
 * @param[in] offset    number of ticks until the timer fires
 * @param[in] timer     the channel to set
 */
void hwtimer_arch_set(unsigned long offset, short timer) {
    timer_set(HWTIMER, timer, offset);
}

/**
 * @brief Set a kernel timer to raise an interrupt at specified system time.
 *
 * @param[in] value     absolute timer tick value to set a timer channel to
 * @param[in] timer     the channel to set
 */
void hwtimer_arch_set_absolute(unsigned long value, short timer) {
    timer_set_absolute(HWTIMER, timer, value);
}

/**
 * @brief Unset the kernel timer with the given timer ID
 *
 * @param[in] timer     the channel to unset
 */
void hwtimer_arch_unset(short timer) {
    timer_clear(HWTIMER, timer);
}

/**
 * @brief Get the current tick count of the default hardware timer
 *
 * @return              the current value of the hwtimer
 */
unsigned long hwtimer_arch_now(void) {
    return timer_read(HWTIMER);
}
