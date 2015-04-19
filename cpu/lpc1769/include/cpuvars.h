/*
 * File     cpuvars.h
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     January 11, 2015, 7:54 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef CPUVARS_H
#define	CPUVARS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "cpuregs.h"

#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          5         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
#define   __I     volatile             /*!< defines 'read only' permissions                 */
#else
#define   __I     volatile const       /*!< defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< defines 'write only' permissions                */
#define     __IO    volatile             /*!< defines 'read / write' permissions              */

typedef enum IRQn {
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn = -14, /*!< 2 Non Maskable Interrupt                         */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M3 Memory Management Interrupt          */
    BusFault_IRQn = -11, /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
    UsageFault_IRQn = -10, /*!< 6 Cortex-M3 Usage Fault Interrupt                */
    SVCall_IRQn = -5, /*!< 11 Cortex-M3 SV Call Interrupt                   */
    DebugMonitor_IRQn = -4, /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
    PendSV_IRQn = -2, /*!< 14 Cortex-M3 Pend SV Interrupt                   */
    SysTick_IRQn = -1, /*!< 15 Cortex-M3 System Tick Interrupt               */

    /******  LPC17xx Specific Interrupt Numbers *******************************************************/
    WDT_IRQn = 0, /*!< Watchdog Timer Interrupt                         */
    TIMER0_IRQn = 1, /*!< Timer0 Interrupt                                 */
    TIMER1_IRQn = 2, /*!< Timer1 Interrupt                                 */
    TIMER2_IRQn = 3, /*!< Timer2 Interrupt                                 */
    TIMER3_IRQn = 4, /*!< Timer3 Interrupt                                 */
    UART0_IRQn = 5, /*!< UART0 Interrupt                                  */
    UART1_IRQn = 6, /*!< UART1 Interrupt                                  */
    UART2_IRQn = 7, /*!< UART2 Interrupt                                  */
    UART3_IRQn = 8, /*!< UART3 Interrupt                                  */
    PWM1_IRQn = 9, /*!< PWM1 Interrupt                                   */
    I2C0_IRQn = 10, /*!< I2C0 Interrupt                                   */
    I2C1_IRQn = 11, /*!< I2C1 Interrupt                                   */
    I2C2_IRQn = 12, /*!< I2C2 Interrupt                                   */
    SPI_IRQn = 13, /*!< SPI Interrupt                                    */
    SSP0_IRQn = 14, /*!< SSP0 Interrupt                                   */
    SSP1_IRQn = 15, /*!< SSP1 Interrupt                                   */
    PLL0_IRQn = 16, /*!< PLL0 Lock (Main PLL) Interrupt                   */
    RTC_IRQn = 17, /*!< Real Time Clock Interrupt                        */
    EINT0_IRQn = 18, /*!< External Interrupt 0 Interrupt                   */
    EINT1_IRQn = 19, /*!< External Interrupt 1 Interrupt                   */
    EINT2_IRQn = 20, /*!< External Interrupt 2 Interrupt                   */
    EINT3_IRQn = 21, /*!< External Interrupt 3 Interrupt                   */
    ADC_IRQn = 22, /*!< A/D Converter Interrupt                          */
    BOD_IRQn = 23, /*!< Brown-Out Detect Interrupt                       */
    USB_IRQn = 24, /*!< USB Interrupt                                    */
    CAN_IRQn = 25, /*!< CAN Interrupt                                    */
    DMA_IRQn = 26, /*!< General Purpose DMA Interrupt                    */
    I2S_IRQn = 27, /*!< I2S Interrupt                                    */
    ENET_IRQn = 28, /*!< Ethernet Interrupt                               */
    RIT_IRQn = 29, /*!< Repetitive Interrupt Timer Interrupt             */
    MCPWM_IRQn = 30, /*!< Motor Control PWM Interrupt                      */
    QEI_IRQn = 31, /*!< Quadrature Encoder Interface Interrupt           */
    PLL1_IRQn = 32, /*!< PLL1 Lock (USB PLL) Interrupt                    */
    USBActivity_IRQn = 33, /* USB Activity interrupt                             */
    CANActivity_IRQn = 34, /* CAN Activity interrupt                             */
} IRQn_Type;

#include "core_cm3.h"

/* System control */
typedef struct sys_ctl {
    // 0x400FC000u

    union {

        struct {
            __I uint32_t : 12;
            __IO uint32_t FLASHTIM : 4;
        };
        __IO uint32_t REGISTER;
    } FLASHCFG;

    // 0x400FC004u
    __I uint32_t RESERVED0[31];

    // 0x400FC080

    union {

        struct {
            __IO uint32_t PLLE0 : 1;
            __IO uint32_t PLLC0 : 1;
            __I uint32_t : 30;
        };
        __IO uint32_t REGISTER;
    } PLL0CON;

    // 0x400FC084

    union {

        struct {
            __IO uint32_t MSEL0 : 15;
            __I uint32_t : 1;
            __IO uint32_t NSEL0 : 8;
            __I uint32_t : 8;
        };
        __IO uint32_t REGISTER;
    } PLL0CFG;

    // 0x400FC088

    union {

        struct {
            __I uint32_t MSEL0 : 15;
            __I uint32_t : 1;
            __I uint32_t NSEL0 : 8;
            __I uint32_t PLLE0_STAT : 1;
            __I uint32_t PLLC0_STAT : 1;
            __I uint32_t PLOCK0 : 1;
            __I uint32_t : 5;
        };
        __I uint32_t REGISTER;
    } PLL0STAT;

    // 0x400FC08C
    __O uint32_t PLL0FEED;

    // 0x400FC090
    __I uint32_t RESERVED1[4];

    // 0x400FC0A0

    union {

        struct {
            __IO uint32_t PLLE1 : 1;
            __IO uint32_t PLLC1 : 1;
            __I uint32_t : 30;
        };
        __IO uint32_t REGISTER;
    } PLL1CON;

    // 0x400FC0A4

    union {

        struct {
            __IO uint32_t MSEL1 : 5;
            __IO uint32_t PSEL1 : 2;
            __I uint32_t : 25;
        };
        __IO uint32_t REGISTER;
    } PLL1CFG;

    // 0x400FC0A8

    union {

        struct {
            __I uint32_t MSEL1 : 5;
            __I uint32_t PSEL1 : 2;
            __I uint32_t : 1;
            __I uint32_t PLLE1_STAT : 1;
            __I uint32_t PLLC1_STAT : 1;
            __I uint32_t PLOCK0 : 1;
            __I uint32_t : 21;
        };
        __I uint32_t REGISTER;
    } PLL1STAT;

    // 0x400FC0AC
    __O uint32_t PLL1FEED;

    // 0x400FC0B0
    __I uint32_t RESERVED2[4];

    // 0x400FC0C0

    union {

        struct {
            __IO uint32_t PM0 : 1;
            __IO uint32_t PM1 : 1;
            __IO uint32_t BODRPM : 1;
            __IO uint32_t BOGD : 1;
            __IO uint32_t BORD : 1;
            __I uint32_t : 2;
            __IO uint32_t SMFLAG : 1;
            __IO uint32_t DSFLAG : 1;
            __IO uint32_t PDFLAG : 1;
            __IO uint32_t DPDFLAG : 1;
            __I uint32_t : 20;
        };
        __IO uint32_t REGISTER;
    } PCON;

    // 0x400FC0C4

    union {

        struct {
            __I uint32_t : 1;
            __IO uint32_t PCTIM0 : 1;
            __IO uint32_t PCTIM1 : 1;
            __IO uint32_t PCUART0 : 1;
            __IO uint32_t PCUART1 : 1;
            __I uint32_t : 1;
            __IO uint32_t PCPWM1 : 1;
            __IO uint32_t PCI2C0 : 1;
            __IO uint32_t PCSPI : 1;
            __IO uint32_t PCRTC : 1;
            __IO uint32_t PCSSP1 : 1;
            __I uint32_t : 1;
            __IO uint32_t PCADC : 1;
            __IO uint32_t PCCAN1 : 1;
            __IO uint32_t PCCAN2 : 1;
            __IO uint32_t PCGPIO : 1;
            __IO uint32_t PCRIT : 1;
            __IO uint32_t PCMCPWM : 1;
            __IO uint32_t PCQEI : 1;
            __IO uint32_t PCI2C1 : 1;
            __I uint32_t : 1;
            __IO uint32_t PCSSP0 : 1;
            __IO uint32_t PCTIM2 : 1;
            __IO uint32_t PCTIM3 : 1;
            __IO uint32_t PCUART2 : 1;
            __IO uint32_t PCUART3 : 1;
            __IO uint32_t PCI2C2 : 1;
            __IO uint32_t PCI2S : 1;
            __I uint32_t : 1;
            __IO uint32_t PCGPDMA : 1;
            __IO uint32_t PCENET : 1;
            __IO uint32_t PCUSB : 1;
        };
        __IO uint32_t REGISTER;
    } PCONP;

    // 0x400FC0C8
    __I uint32_t RESERVED3[15];

    // 0x400FC104

    union {

        struct {
            __IO uint32_t CCLKSEL : 8;
            __I uint32_t : 24;
        };
        __IO uint32_t REGISTER;
    } CCLKCFG;

    // 0x400FC108

    union {

        struct {
            __IO uint32_t USBSEL : 4;
            __I uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } USBCLKCFG;

    // 0x400FC10C

    union {

        struct {
            __IO uint32_t CLKSRC : 2;
            __I uint32_t : 30;
        };
        __IO uint32_t REGISTER;
    } CLKSRCSEL;

    // 0x400FC110

    union {

        struct {
            __I uint32_t : 1;
            __IO uint32_t CAN1SLEEP : 1;
            __IO uint32_t CAN2SLEEP : 1;
            __I uint32_t : 29;
        };
        __IO uint32_t REGISTER;
    } CANSLEEPCLR;

    // 0x400FC114

    union {

        struct {
            __I uint32_t : 1;
            __IO uint32_t CAN1WAKE : 1;
            __IO uint32_t CAN2WAKE : 1;
            __I uint32_t : 29;
        };
        __IO uint32_t REGISTER;
    } CANWAKEFLAGS;

    // 0x400FC118
    __I uint32_t RESERVED4[10];

    // 0x400FC140

    union {

        struct {
            __I uint32_t EINT0 : 1;
            __I uint32_t EINT1 : 1;
            __I uint32_t EINT2 : 1;
            __I uint32_t EINT3 : 1;
            __I uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } EXTINT; /* External Interrupts                */

    // 0x400FC144
    __I uint32_t RESERVED5;

    // 0x400FC148

    union {

        struct {
            __IO uint32_t EXTMODE0 : 1;
            __IO uint32_t EXTMODE1 : 1;
            __IO uint32_t EXTMODE2 : 1;
            __IO uint32_t EXTMODE3 : 1;
            __IO uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } EXTMODE;

    // 0x400FC14C

    union {

        struct {
            __IO uint32_t EXTPOLAR0 : 1;
            __IO uint32_t EXTPOLAR1 : 1;
            __IO uint32_t EXTPOLAR2 : 1;
            __IO uint32_t EXTPOLAR3 : 1;
            __IO uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } EXTPOLAR;

    // 0x400FC150
    __I uint32_t RESERVED6[12];

    // 0x400FC180

    union {

        struct {
            __I uint32_t POR : 1;
            __I uint32_t EXTR : 1;
            __I uint32_t WDTR : 1;
            __I uint32_t BODR : 1;
            __I uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } RSID; /* Reset                              */

    // 0x400FC184
    __I uint32_t RESERVED7[7];

    // 0x400FC1A0

    union {

        struct {
            __I uint32_t : 4;
            __IO uint32_t OSCRANGE : 1;
            __IO uint32_t OSCEN : 1;
            __I uint32_t OSCSTAT : 1;
            __I uint32_t : 25;
        };
        __IO uint32_t REGISTER;
    } SCS; /* Syscon Miscellaneous Registers     */

    // 0x400FC1A4
    __I uint32_t RESERVED8;

    // 0x400FC1A8

    union {

        struct {
            __IO uint32_t PCLK_WDT : 2;
            __IO uint32_t PCLK_TIMER0 : 2;
            __IO uint32_t PCLK_TIMER1 : 2;
            __IO uint32_t PCLK_UART0 : 2;
            __IO uint32_t PCLK_UART1 : 2;
            __IO uint32_t : 2;
            __IO uint32_t PCLK_PWM1 : 2;
            __IO uint32_t PCLK_I2C0 : 2;
            __IO uint32_t PCLK_SPI : 2;
            __IO uint32_t : 2;
            __IO uint32_t PCLK_SSP1 : 2;
            __IO uint32_t PCLK_DAC : 2;
            __IO uint32_t PCLK_ADC : 2;
            __IO uint32_t PCLK_CAN1 : 2;
            __IO uint32_t PCLK_CAN2 : 2;
            __IO uint32_t PCLK_ACF : 2;
        };
        __IO uint32_t REGISTER;
    } PCLKSEL0;

    // 0x400FC1AC

    union {

        struct {
            __IO uint32_t PCLK_QEI : 2;
            __IO uint32_t PCLK_GPIOINT : 2;
            __IO uint32_t PCLK_PCB : 2;
            __IO uint32_t PCLK_I2C1 : 2;
            __IO uint32_t : 2;
            __IO uint32_t PCLK_SSP0 : 2;
            __IO uint32_t PCLK_TIMER2 : 2;
            __IO uint32_t PCLK_TIMER3 : 2;
            __IO uint32_t PCLK_UART2 : 2;
            __IO uint32_t PCLK_UART3 : 2;
            __IO uint32_t PCLK_I2C2 : 2;
            __IO uint32_t PCLK_I2S : 2;
            __IO uint32_t : 2;
            __IO uint32_t PCLK_RIT : 2;
            __IO uint32_t PCLK_SYSCON : 2;
            __IO uint32_t PCLK_MC : 2;
        };
        __IO uint32_t REGISTER;
    } PCLKSEL1;

    // 0x400FC1B0
    __I uint32_t RESERVED9[4];

    // 0x400FC1C0

    union {

        struct {
            __I uint32_t USB_INT_REQ_LP : 1;
            __I uint32_t USB_INT_REQ_HP : 1;
            __I uint32_t USB_INT_REQ_DMA : 1;
            __I uint32_t USB_HOST_INT : 1;
            __I uint32_t USB_ATX_INT : 1;
            __I uint32_t USB_OTG_INT : 1;
            __I uint32_t USB_I2C_INT : 1;
            __I uint32_t : 1;
            __I uint32_t USB_NEED_CLK : 1;
            __I uint32_t : 22;
            __I uint32_t EN_USB_INTS : 1;
        };
        __IO uint32_t REGISTER;
    } USBIntSt; /* USB Device/OTG Interrupt Register  */

    // 0x400FC1C4

    union {

        struct {
            __I uint32_t DMASEL08 : 1;
            __I uint32_t DMASEL09 : 1;
            __I uint32_t DMASEL10 : 1;
            __I uint32_t DMASEL11 : 1;
            __I uint32_t DMASEL12 : 1;
            __I uint32_t DMASEL13 : 1;
            __I uint32_t DMASEL14 : 1;
            __I uint32_t DMASEL15 : 1;
            __I uint32_t : 24;
        };
        __IO uint32_t REGISTER;
    } DMAREQSEL;

    // 0x400FC1C8

    union {

        struct {
            __I uint32_t CLKOUTSEL : 4;
            __I uint32_t CLKOUTDIV : 4;
            __I uint32_t CLKOUT_EN : 1;
            __I uint32_t CLKOUT_ACT : 1;
            __I uint32_t : 22;
        };
        __IO uint32_t REGISTER;
    } CLKOUTCFG; /* Clock Output Configuration         */
} sys_ctl_t;

#define LPC_SYS_CTL     (*((sys_ctl_t *) SYS_CTRL_BASE))

/* Timers */
typedef struct timer {

    union {

        struct {
            __IO uint32_t MR0 : 1;
            __IO uint32_t MR1 : 1;
            __IO uint32_t MR2 : 1;
            __IO uint32_t MR3 : 1;
            __IO uint32_t CR0 : 1;
            __IO uint32_t CR1 : 1;
            __I uint32_t : 26;
        };
        __IO uint32_t REGISTER;
    } IR;

    union {

        struct {
            __IO uint32_t CTR_ENABLE : 1;
            __IO uint32_t CTR_RESET : 1;
        };
        __IO uint32_t REGISTER;
    } TCR;

    __IO uint32_t TC;
    __IO uint32_t PR;
    __IO uint32_t PC;

    union {

        struct {
            __IO uint32_t MR0I : 1;
            __IO uint32_t MR0R : 1;
            __IO uint32_t MR0S : 1;
            __IO uint32_t MR1I : 1;
            __IO uint32_t MR1R : 1;
            __IO uint32_t MR1S : 1;
            __IO uint32_t MR2I : 1;
            __IO uint32_t MR2R : 1;
            __IO uint32_t MR2S : 1;
            __IO uint32_t MR3I : 1;
            __IO uint32_t MR3R : 1;
            __IO uint32_t MR3S : 1;
            __I uint32_t : 20;
        };
        __IO uint32_t REGISTER;
    } MCR;

    __IO uint32_t MR0;
    __IO uint32_t MR1;
    __IO uint32_t MR2;
    __IO uint32_t MR3;

    union {

        struct {
            __IO uint32_t CAP0RE : 1;
            __IO uint32_t CAP0FE : 1;
            __IO uint32_t CAP0I : 1;
            __IO uint32_t CAP1RE : 1;
            __IO uint32_t CAP1FE : 1;
            __IO uint32_t CAP1I : 1;
            __I uint32_t : 26;
        };
        __IO uint32_t REGISTER;
    } CCR;

    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __I uint32_t RESERVED0[2];

    union {

        struct {
            __IO uint32_t EM0 : 1;
            __IO uint32_t EM1 : 1;
            __IO uint32_t EM2 : 1;
            __IO uint32_t EM3 : 1;
            __IO uint32_t EMC0 : 1;
            __IO uint32_t EMC1 : 1;
            __IO uint32_t EMC2 : 1;
            __IO uint32_t EMC3 : 1;
            __I uint32_t : 24;
        };
        __IO uint32_t REGISTER;
    } EMR;

    __I uint32_t RESERVED1[12];

    union {

        struct {
            __IO uint32_t MODE : 2;
            __IO uint32_t CTR_INPUTSEL : 2;
            __I uint32_t : 28;
        };
        __IO uint32_t REGISTER;
    } CTCR;

} lpc_timer_t;

#define LPC_TMR0        (*((lpc_timer_t *) T0_BASE))
#define LPC_TMR1        (*((lpc_timer_t *) T1_BASE))
#define LPC_TMR2        (*((lpc_timer_t *) T2_BASE))
#define LPC_TMR3        (*((lpc_timer_t *) T3_BASE))

/* Pin connect block */
typedef union pinsel {

    struct {
        __IO uint32_t SEL0;
        __IO uint32_t SEL1;
        __IO uint32_t SEL2;
        __IO uint32_t SEL3;
        __IO uint32_t SEL4;
        __I uint32_t RESERVED0[2];
        __IO uint32_t SEL7;
        __I uint32_t RESERVED1[1];
        __IO uint32_t SEL9;
        __IO uint32_t SEL10;
    };
    __IO uint32_t SEL[11];
} pinsel_t;

typedef union pinmode {

    struct {
        __IO uint32_t MODE0;
        __IO uint32_t MODE1;
        __IO uint32_t MODE2;
        __IO uint32_t MODE3;
        __IO uint32_t MODE4;
        __IO uint32_t MODE5;
        __IO uint32_t MODE6;
        __IO uint32_t MODE7;
        __I uint32_t RESERVED[1];
        __IO uint32_t MODE9;
    };
    __IO uint32_t MODE[10];
} pinmode_t;

typedef union pinmodeod {

    struct {
        __IO uint32_t OD0;
        __IO uint32_t OD1;
        __IO uint32_t OD2;
        __IO uint32_t OD3;
        __IO uint32_t OD4;
    };
    __IO uint32_t OD[5];
} pinmodeod_t;

#define LPC_PINSEL      (*((pinsel_t *)(PINCONNECT_BASE + PINSEL00_OFFSET)))
#define LPC_PINMODE     (*((pinmode_t *)(PINCONNECT_BASE + PINMODE00_OFFSET)))
#define LPC_PINMODEOD   (*((pinmodeod_t *)(PINCONNECT_BASE + PINMODEOD0_OFFSET)))

/* GPIO block */
typedef struct gpio {
    __IO uint32_t FIODIR;
    __IO uint32_t RESERVED[3];
    __IO uint32_t FIOMASK;
    __IO uint32_t FIOPIN;
    __IO uint32_t FIOSET;
    __IO uint32_t FIOCLR;
} gpio_t;

/* LPC_GPIO[x] */
#define LPC_GPIO        ((gpio_t *)(GPIO_BASE))


/* UARTs */
typedef struct uart {

    union {

        struct {
            __I uint32_t RBR : 8;
            __I uint32_t : 24;
        };

        struct {
            __O uint32_t THR : 8;
            __O uint32_t : 24;
        };

        struct {
            __IO uint32_t DLL : 8;
            __IO uint32_t : 24;
        };
    };

    union {

        struct {
            __IO uint32_t RBR_IE : 1;
            __IO uint32_t THRE_IE : 1;
            __IO uint32_t RXLS_IE : 1;
            __IO uint32_t : 5;
            __IO uint32_t ABEOIntEn : 1;
            __IO uint32_t ABTOIntEn : 1;
            __IO uint32_t : 22;
        } IER;

        struct {
            __IO uint32_t DLM : 8;
            __IO uint32_t : 24;
        };
    };

    union {

        struct {
            __I uint32_t IntStatus : 1;
            __I uint32_t IntId : 3;
            __I uint32_t : 2;
            __I uint32_t FIFO_EN : 2;
            __I uint32_t ABEOInt : 1;
            __I uint32_t ABTOInt : 1;
            __I uint32_t : 22;
        } IIR;

        struct {
            __O uint32_t FIFO_EN : 1;
            __O uint32_t RX_FIFO_RS : 1;
            __O uint32_t TX_FIFO_RS : 1;
            __O uint32_t DMA_MODE : 1;
            __O uint32_t : 2;
            __O uint32_t RX_TLEVEL : 2;
            __O uint32_t : 24;
        } FCR;
    };

	struct {
		__IO uint32_t WORD_LEN : 2;
		__IO uint32_t STOP_BIT : 1;
		__IO uint32_t PARITY_EN : 1;
		__IO uint32_t PARITY_SEL : 2;
		__IO uint32_t BREAK_CTL : 1;
		__IO uint32_t DLAB : 1;
		__IO uint32_t : 24;
	} LCR;

	__I uint32_t RESERVED0;

	struct {
		__I uint32_t RDR : 1;
		__I uint32_t OE : 1;
		__I uint32_t PE : 1;
		__I uint32_t FE : 1;
		__I uint32_t BI : 1;
		__I uint32_t THRE : 1;
		__I uint32_t TEMT : 1;
		__I uint32_t RXFE : 1;
		__I uint32_t : 24;
	} LSR;

    __I uint32_t RESERVED1;

	struct {
		__IO uint32_t SCR : 8;
		__IO uint32_t : 24;
	};

	struct {
		__IO uint32_t START : 1;
		__IO uint32_t MODE : 1;
		__IO uint32_t AUTORESTART : 1;
		__IO uint32_t : 5;
		__IO uint32_t ABEOIntClr : 1;
		__IO uint32_t ABTOIntClr : 1;
		__IO uint32_t : 22;
	} ACR;

	struct {
		__IO uint32_t IrDAEn : 1;
		__IO uint32_t IrDAInv : 1;
		__IO uint32_t FixPulseEn : 1;
		__IO uint32_t PulseDiv : 3;
		__IO uint32_t : 26;
	} ICR;

	struct {
		__IO uint32_t DIVADDVAL : 4;
		__IO uint32_t MULVAL : 4;
		__IO uint32_t : 24;
	} FDR;

    __I uint32_t RESERVED2;

	struct {
		__IO uint32_t : 7;
		__IO uint32_t TXEN : 1;
		__IO uint32_t : 24;
	} TER;
} uartx_t;

#define LPC_UART0       (*((uartx_t *) UART0_BASE))
#define LPC_UART2       (*((uartx_t *) UART2_BASE))
#define LPC_UART3       (*((uartx_t *) UART3_BASE))

#ifdef	__cplusplus
}
#endif

#endif	/* CPUVARS_H */

