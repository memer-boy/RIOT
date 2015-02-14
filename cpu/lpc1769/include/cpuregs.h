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
#define PINSEL_BASE        0x4002C000u
#define PINSEL01_ADR        0x4002C004u
#define PINSEL02_ADR        0x4002C008u
#define PINSEL03_ADR        0x4002C00Cu
#define PINSEL04_ADR        0x4002C010u
#define PINSEL07_ADR        0x4002C01Cu
#define PINSEL08_ADR        0x4002C020u
#define PINSEL09_ADR        0x4002C024u
#define PINSEL10_ADR        0x4002C028u

#define PINMODE_BASE       0x4002C040u
#define PINMODE01_ADR       0x4002C044u
#define PINMODE02_ADR       0x4002C048u
#define PINMODE03_ADR       0x4002C04Cu
#define PINMODE04_ADR       0x4002C050u
#define PINMODE05_ADR       0x4002C054u
#define PINMODE06_ADR       0x4002C058u
#define PINMODE07_ADR       0x4002C05Cu
#define PINMODE09_ADR       0x4002C064u

#define PINMODEOD_BASE      0x4002C068u
#define PINMODEOD1_ADR      0x4002C06Cu
#define PINMODEOD2_ADR      0x4002C070u
#define PINMODEOD3_ADR      0x4002C074u
#define PINMODEOD4_ADR      0x4002C078u

#define I2CPADCFG_ADR       0x4002C07Cu

/* GPIO registers*/
#define FIO0DIR_ADR         0x2009C000u
#define FIO1DIR_ADR         0x2009C020u
#define FIO2DIR_ADR         0x2009C040u
#define FIO3DIR_ADR         0x2009C060u
#define FIO4DIR_ADR         0x2009C080u

#define FIO0MASK_ADR        0x2009C010u
#define FIO1MASK_ADR        0x2009C030u
#define FIO2MASK_ADR        0x2009C050u
#define FIO3MASK_ADR        0x2009C070u
#define FIO4MASK_ADR        0x2009C090u

#define FIO0PIN_ADR         0x2009C014u
#define FIO1PIN_ADR         0x2009C034u
#define FIO2PIN_ADR         0x2009C054u
#define FIO3PIN_ADR         0x2009C074u
#define FIO4PIN_ADR         0x2009C094u

#define FIO0SET_ADR         0x2009C018u
#define FIO1SET_ADR         0x2009C038u
#define FIO2SET_ADR         0x2009C058u
#define FIO3SET_ADR         0x2009C078u
#define FIO4SET_ADR         0x2009C098u

#define FIO0CLR_ADR         0x2009C01Cu
#define FIO1CLR_ADR         0x2009C03Cu
#define FIO2CLR_ADR         0x2009C05Cu
#define FIO3CLR_ADR         0x2009C07Cu
#define FIO4CLR_ADR         0x2009C09Cu

#ifdef	__cplusplus
}
#endif

#endif	/* CPUREGS_H */

