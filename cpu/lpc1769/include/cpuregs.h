/*
 * File     cpuregs.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     January 11, 2015, 7:41 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef CPUREGS_H
#define	CPUREGS_H

#ifdef	__cplusplus
extern "C" {
#endif
/* System control */
#define SYS_CTRL_BASE       0x400FC000u
#define FLASHCFG_OFFSET     0x00000000u
#define PLL0CON_OFFSET      0x00000080u
#define PLL0CFG_OFFSET      0x00000084u
#define PLL0STAT_OFFSET     0x00000088u
#define PLL0FEED_OFFSET     0x0000008Cu
#define PLL1CON_OFFSET      0x000000A0u
#define PLL1CFG_OFFSET      0x000000A4u
#define PLL1STAT_OFFSET     0x000000A8u
#define PLL1FEED_OFFSET     0x000000ACu
#define PCON_OFFSET         0x000000C0u
#define PCONP_OFFSET        0x000000C4u
#define CCLKCFG_OFFSET      0x00000104u
#define USBCLKCFG_OFFSET    0x00000108u
#define CLKSRCSEL_OFFSET    0x0000010Cu
#define CANSLEEPCLR_OFFSET  0x00000110u
#define CANWAKEFLAGS_OFFSET 0x00000114u
#define EXTINT_OFFSET       0x00000140u
#define EXTMODE_OFFSET      0x00000148u
#define EXTPOLAR_OFFSET     0x0000014Cu
#define RSID_OFFSET         0x00000180u
#define CSC_OFFSET          0x000001A0u
#define PCLKSEL0_OFFSET     0x000001A8u
#define PCLKSEL1_OFFSET     0x000001ACu
#define CLKOUTCFG_OFFSET    0x000001C8u

/* Timers */
#define T0_BASE             0x40004000u
#define T1_BASE             0x40008000u
#define T2_BASE             0x40090000u
#define T3_BASE             0x40094000u

#define TXCR_OFFSET         0x00000004u
#define TXTC_OFFSET         0x00000008u
#define TXPR_OFFSET         0x0000000Cu
#define TXPC_OFFSET         0x00000010u
#define TXMCR_OFFSET        0x00000014u
#define TXMR0_OFFSET        0x00000018u
#define TXMR1_OFFSET        0x0000001Cu
#define TXMR2_OFFSET        0x00000020u
#define TXMR3_OFFSET        0x00000024u
#define TXCCR_OFFSET        0x00000028u
#define TXCR0_OFFSET        0x0000002Cu
#define TXCR1_OFFSET        0x00000030u
#define TXEMR_OFFSET        0x0000003Cu
#define TXCTCR_OFFSET       0x00000070u

/* Pin connect block */
#define PINCONNECT_BASE     0x4002C000u
#define PINSEL00_OFFSET     0x00000000u
#define PINSEL01_OFFSET     0x00000004u
#define PINSEL02_OFFSET     0x00000008u
#define PINSEL03_OFFSET     0x0000000Cu
#define PINSEL04_OFFSET     0x00000010u
#define PINSEL07_OFFSET     0x0000001Cu
#define PINSEL08_OFFSET     0x00000020u
#define PINSEL09_OFFSET     0x00000024u
#define PINSEL10_OFFSET     0x00000028u

#define PINMODE00_OFFSET    0x00000040u
#define PINMODE01_OFFSET    0x00000044u
#define PINMODE02_OFFSET    0x00000048u
#define PINMODE03_OFFSET    0x0000004Cu
#define PINMODE04_OFFSET    0x00000050u
#define PINMODE05_OFFSET    0x00000054u
#define PINMODE06_OFFSET    0x00000058u
#define PINMODE07_OFFSET    0x0000005Cu
#define PINMODE09_OFFSET    0x00000064u

#define PINMODEOD0_OFFSET   0x00000068u
#define PINMODEOD1_OFFSET   0x0000006Cu
#define PINMODEOD2_OFFSET   0x00000070u
#define PINMODEOD3_OFFSET   0x00000074u
#define PINMODEOD4_OFFSET   0x00000078u

#define I2CPADCFG_BASE      0x0000007Cu

/* GPIO registers*/
#define GPIO_BASE           0x2009C000u

#define FIO0DIR_OFFSET      0x00000000u
#define FIO1DIR_OFFSET      0x00000020u
#define FIO2DIR_OFFSET      0x00000040u
#define FIO3DIR_OFFSET      0x00000060u
#define FIO4DIR_OFFSET      0x00000080u

#define FIO0MASK_OFFSET     0x00000010u
#define FIO1MASK_OFFSET     0x00000030u
#define FIO2MASK_OFFSET     0x00000050u
#define FIO3MASK_OFFSET     0x00000070u
#define FIO4MASK_OFFSET     0x00000090u

#define FIO0PIN_OFFSET      0x00000014u
#define FIO1PIN_OFFSET      0x00000034u
#define FIO2PIN_OFFSET      0x00000054u
#define FIO3PIN_OFFSET      0x00000074u
#define FIO4PIN_OFFSET      0x00000094u

#define FIO0SET_OFFSET      0x00000018u
#define FIO1SET_OFFSET      0x00000038u
#define FIO2SET_OFFSET      0x00000058u
#define FIO3SET_OFFSET      0x00000078u
#define FIO4SET_OFFSET      0x00000098u

#define FIO0CLR_OFFSET      0x0000001Cu
#define FIO1CLR_OFFSET      0x0000003Cu
#define FIO2CLR_OFFSET      0x0000005Cu
#define FIO3CLR_OFFSET      0x0000007Cu
#define FIO4CLR_OFFSET      0x0000009Cu

/* UARTs registers */
#define UART0_BASE          0x4000C000u
#define UART1_BASE          0x40010000u
#define UART2_BASE          0x40098000u
#define UART3_BASE          0x4009C000u

#define RBR_OFFSET          0x00000000u
#define THR_OFFSET          0x00000000u
#define DLL_OFFSET          0x00000000u
#define DLM_OFFSET          0x00000004u
#define IER_OFFSET          0x00000004u
#define IIR_OFFSET          0x00000008u
#define FCR_OFFSET          0x00000008u
#define LCR_OFFSET          0x0000000Cu
#define MCR_OFFSET          0x00000010u
#define LSR_OFFSET          0x00000014u
#define MSR_OFFSET          0x00000018u
#define SCR_OFFSET          0x0000001Cu
#define ACR_OFFSET          0x00000020u
#define ICR_OFFSET          0x00000024u
#define FDR_OFFSET          0x00000028u
#define TER_OFFSET          0x00000030u
#define RS485CTRL_OFFSET    0x0000004Cu
#define ADRMATCH_OFFSET     0x00000050u
#define RS485DLY_OFFSET     0x00000054u

/* SPI registers */
#define SPI0_BASE           0x40020000u
#define S0SPCR_OFFSET       0x00000000u
#define S0SPSR_OFFSET       0x00000004u
#define S0SPDR_OFFSET       0x00000008u
#define S0SPCCR_OFFSET      0x0000000Cu
#define S0SPINT_OFFSET      0x0000001Cu
    
/* GPDMA registers */
#define GPDMAC_BASE         0x50004000u
#define GPDMACH0_BASE       0x50004100u
#define GPDMACH1_BASE       0x50004120U
#define GPDMACH2_BASE       0x50004140U
#define GPDMACH3_BASE       0x50004160U
#define GPDMACH4_BASE       0x50004180U
#define GPDMACH5_BASE       0x500041A0U
#define GPDMACH6_BASE       0x500041C0U
#define GPDMACH7_BASE       0x500041E0U
#ifdef	__cplusplus
}
#endif

#endif	/* CPUREGS_H */

