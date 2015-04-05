/*
 * File     uart.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 14, 2015, 2:42 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "cpu-conf.h"
#include "core_cm3.h"
#include "cpuvars.h"
#include "periph_conf.h"
#include "periph/uart.h"
#include <stdbool.h>

#ifdef UART_1_EN
#error UART1 is not implemented yet!
#endif

#if F_CPU < (120000000UL)
#error UART only supported at 120 MHz!
#endif

#ifdef UART_0_EN
#if UART_0_CCLK == 8
#define UART_0_CCLKSEL     (0b11)
#elif UART_0_CCLK == 4
#define UART_0_CCLKSEL     (0b00)
#elif UART_0_CCLK == 2
#define UART_0_CCLKSEL     (0b10)
#elif UART_0_CCLK == 1
#define UART_0_CCLKSEL     (0b01)
#else
#error UART_0_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif
#endif

#ifdef UART_2_EN
#if UART_2_CCLK == 8
#define UART_2_CCLKSEL     (0b11)
#elif UART_2_CCLK == 4
#define UART_2_CCLKSEL     (0b00)
#elif UART_2_CCLK == 2
#define UART_2_CCLKSEL     (0b10)
#elif UART_2_CCLK == 1
#define UART_2_CCLKSEL     (0b01)
#else
#error UART_2_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif
#endif

#ifdef UART_3_EN
#if UART_3_CCLK == 8
#define UART_3_CCLKSEL     (0b11)
#elif UART_3_CCLK == 4
#define UART_3_CCLKSEL     (0b00)
#elif UART_3_CCLK == 2
#define UART_3_CCLKSEL     (0b10)
#elif UART_3_CCLK == 1
#define UART_3_CCLKSEL     (0b01)
#else
#error UART_3_CCLK devider has an invalid value or is not defined in periph_conf.h
#endif
#endif

/*
 * BaudRate = PCLK / (16 * (256 * UnDLM + UnDLL) * DivMulC)
 * 
 * BaudRate = PCLK / (16 * UnDL * DivMulC)
 * 
 * (UnDL * DivMulC) = PCLK / (16 * BaudRate)
 * 
 * DivMulC is always a ratio equal or grater than one,
 * and not larger than 1.933
 * 
 * We can iterate over the defined constants of the DivMulC
 * to find the closest integer match possible.
 * 
 */
#define RLS_ID 0b011
#define RDA_ID 0b010
#define CTI_ID 0b110
#define THR_ID 0b001

#define ISR_DECL(X)                             \
void isr_uart ## X (void) {                  \
    int id = uarts[X].base->IIR.IntId;          \
    do {                                        \
        if (id == RDA_ID) {                     \
            uarts[X].rx_cb(uarts[X].arg, uarts[X].base->RBR);\
        }                                       \
        if (id == THR_ID) {                     \
            uarts[X].tx_cb(uarts[X].arg);       \
        }                                       \
    } while (!uarts[X].base->IIR.IntStatus);    \
    NVIC_ClearPendingIRQ(UART ## X ## _IRQn);   \
}

struct uart_st {
    uartx_t *base;
    uint32_t baudrate;
    uart_rx_cb_t rx_cb;
    uart_tx_cb_t tx_cb;
    void *arg;
    bool isBlocking;
};

struct uart_st1 {
    void *base;
    uint32_t baudrate;
    uart_rx_cb_t rx_cb;
    uart_tx_cb_t tx_cb;
    void *arg;
    bool isBlocking;
};

struct uart_st uarts[4] = {
    {&LPC_UART0},
    {0},
    {&LPC_UART2},
    {&LPC_UART3},
};

static void setBaudRate(uart_t uart, uint32_t baudrate) {

    (void) baudrate;

    // 115200 @ 120MHz only
    uarts[uart].base->LCR.DLAB = 1;
    uarts[uart].base->FDR.DIVADDVAL = 1;
    uarts[uart].base->FDR.MULVAL = 6;
    uarts[uart].base->DLL = 7;
    uarts[uart].base->DLM = 0;

    uarts[uart].base->LCR.DLAB = 0;
}

int uart_init(
    uart_t uart,
    uint32_t baudrate,
    uart_rx_cb_t rx_cb,
    uart_tx_cb_t tx_cb,
    void *arg) {

    switch (uart) {
#ifdef UART_0_EN
    case UART_0:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_0_CCLKSEL;
        break;
#endif
#ifdef UART_2_EN
    case UART_2:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_2_CCLKSEL;
        break;
#endif
#ifdef UART_3_EN
    case UART_3:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_3_CCLKSEL;
        break;
#endif
    default: return -2;
    }

    uarts[uart].isBlocking = false;
    uarts[uart].baudrate = baudrate;
    uarts[uart].rx_cb = rx_cb;
    uarts[uart].tx_cb = tx_cb;
    uarts[uart].arg = arg;

    setBaudRate(uart, baudrate);

    uarts[uart].base->LCR.WORD_LEN = 0b11;
    uarts[uart].base->LCR.STOP_BIT = 0;
    uarts[uart].base->LCR.PARITY_EN = 0;

    uarts[uart].base->FCR.FIFO_EN = 1;

    uarts[uart].base->IER.RBR_IE = 1;

    return 0;
}

int uart_init_blocking(uart_t uart, uint32_t baudrate) {
    switch (uart) {
#ifdef UART_0_EN
    case UART_0:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_0_CCLKSEL;
        break;
#endif
#ifdef UART_2_EN
    case UART_2:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_2_CCLKSEL;
        break;
#endif
#ifdef UART_3_EN
    case UART_3:
        LPC_SYS_CTL.PCLKSEL1.PCLK_UART3 = UART_3_CCLKSEL;
        break;
#endif
    default: return -2;
    }

    uarts[uart].isBlocking = true;
    uarts[uart].baudrate = baudrate;

    setBaudRate(uart, baudrate);

    uarts[uart].base->LCR.WORD_LEN = 0b11;
    uarts[uart].base->LCR.STOP_BIT = 0;
    uarts[uart].base->LCR.PARITY_EN = 0;

    uarts[uart].base->FCR.FIFO_EN = 1;

    return 0;
}

void uart_tx_begin(uart_t uart) {
    if (!uarts[uart].isBlocking) {
        uarts[uart].base->IER.THRE_IE = 1;
    }
}

int uart_write(uart_t uart, char data) {
    if (uarts[uart].isBlocking) {
        return uart_write_blocking(uart, data);
    }

    uarts[uart].base->THR = data;

    return 1;
}

int uart_read_blocking(uart_t uart, char *data) {
    while (!uarts[uart].base->LSR.RDR);

    *data = uarts[uart].base->RBR;

    return 1;
}

int uart_write_blocking(uart_t uart, char data) {
    while (!uarts[uart].base->LSR.THRE);

    uarts[uart].base->THR = data;

    return 1;
}

void uart_poweron(uart_t uart) {
    switch (uart) {
#ifdef UART_0_EN
    case UART_0:
        LPC_SYS_CTL.PCONP.PCUART0 = 1;
        break;
#endif
#ifdef UART_1_EN
    case UART_1:
        LPC_SYS_CTL.PCONP.PCUART1 = 1;
        break;
#endif
#ifdef UART_2_EN
    case UART_2:
        LPC_SYS_CTL.PCONP.PCUART2 = 1;
        break;
#endif
#ifdef UART_3_EN
    case UART_3:
        LPC_SYS_CTL.PCONP.PCUART3 = 1;
        break;
#endif
    }
}

void uart_poweroff(uart_t uart) {
    switch (uart) {
#ifdef UART_0_EN
    case UART_0:
        LPC_SYS_CTL.PCONP.PCUART0 = 0;
        break;
#endif
#ifdef UART_1_EN
    case UART_1:
        LPC_SYS_CTL.PCONP.PCUART1 = 0;
        break;
#endif
#ifdef UART_2_EN
    case UART_2:
        LPC_SYS_CTL.PCONP.PCUART2 = 0;
        break;
#endif
#ifdef UART_3_EN
    case UART_3:
        LPC_SYS_CTL.PCONP.PCUART3 = 0;
        break;
#endif
    }
}

#ifdef UART_0_EN
ISR_DECL(0)
#endif
#ifdef UART_1_EN
ISR_DECL(1)
#endif
#ifdef UART_2_EN
ISR_DECL(2)
#endif
#ifdef UART_3_EN
ISR_DECL(3)
#endif