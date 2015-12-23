/*
 * File     cpu-conf.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 10, 2015, 12:10 AM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef CPU_CONF_H
#define	CPU_CONF_H

#ifdef	__cplusplus
extern "C" {
#endif
/**
 * @name Cortex common configuration
 * @{
 */
#define CPU_IRQ_NUMOF 32
#define CPU_DEFAULT_IRQ_PRIO 32
/** @} */
    
/**
 * @name Kernel configuration
 * @{
 */
#define KERNEL_CONF_STACKSIZE_PRINTF    (1024)

#ifndef KERNEL_CONF_STACKSIZE_DEFAULT
#define KERNEL_CONF_STACKSIZE_DEFAULT   (1024)
#endif

#define KERNEL_CONF_STACKSIZE_IDLE      (256)
/** @} */

/**
 * @name UART0 buffer size definition for compatibility reasons
 * @{
 */
#ifndef UART0_BUFSIZE
#define UART0_BUFSIZE                   (128)
#endif
/** @} */

/**
 * @brief   length of CPU ID for @ref cpuid_get() in @ref periph/cpuid.h
 */
//#ifndef CPUID_ID_LEN
//#define CPUID_ID_LEN                    32
//#endif

#ifdef	__cplusplus
}
#endif

#include "cpuvars.h"
#include "core_cm3.h"

#endif	/* CPU_CONF_H */

