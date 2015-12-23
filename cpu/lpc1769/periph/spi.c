/*
 * File     spi.c
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

#include <stdint.h>
#include "periph/spi.h"
#include "periph_conf.h"
#include "pinblock.h"
#include "cpuvars.h"
#include "mutex.h"

typedef struct spi_dev {
    uint8_t configured;
    uint8_t master;
    lpc_spi_t spi_reg;
    mutex_t lock;
    char (*cb) (char);
} spi_dev;

/* add guard for the case that no SPI device is defined */
#if SPI_NUMOF

static pinblock_t spi_pins[] = {
    CONNECT(PIN(0, 15), ALTERN2, NO_PULLS, NORMAL),
    CONNECT(PIN(0, 17), ALTERN2, NO_PULLS, NORMAL),
    CONNECT(PIN(0, 18), ALTERN2, NO_PULLS, NORMAL),
#ifdef SPI_0_EN
    CONNECT(PIN(0, 21), PRIMARY, ONCHIP_PULLUP, NORMAL),
#endif
#ifdef SPI_1_EN
    CONNECT(PIN(0, 22), PRIMARY, ONCHIP_PULLUP, NORMAL),
#endif
#ifdef SPI_2_EN
    CONNECT(PIN(0, 27), PRIMARY, ONCHIP_PULLUP, NORMAL),
#endif
#ifdef SPI_3_EN
    CONNECT(PIN(0, 28), PRIMARY, ONCHIP_PULLUP, NORMAL),
#endif
};

static spi_dev devices[] = {
    { .configured = 0, .master = 0, .lock = MUTEX_INIT, .spi_reg = {{}} , .cb = 0},
    { .configured = 0, .master = 0, .lock = MUTEX_INIT, .spi_reg = {{}} , .cb = 0},
    { .configured = 0, .master = 0, .lock = MUTEX_INIT, .spi_reg = {{}} , .cb = 0},
    { .configured = 0, .master = 0, .lock = MUTEX_INIT, .spi_reg = {{}} , .cb = 0},
};

int spi_init(spi_t dev, spi_conf_t conf, spi_speed_t speed, uint8_t master, char (*cb)(char data)) {
    devices[dev].configured = 1;

    // spi_conf_t
    switch (conf) {
    case SPI_CONF_FIRST_RISING:
        devices[dev].spi_reg.S0SPCR.CPOL = 1;
        devices[dev].spi_reg.S0SPCR.CPHA = 0;
        break;
    case SPI_CONF_SECOND_RISING:
        devices[dev].spi_reg.S0SPCR.CPOL = 1;
        devices[dev].spi_reg.S0SPCR.CPHA = 1;
        break;
    case SPI_CONF_FIRST_FALLING:
        devices[dev].spi_reg.S0SPCR.CPOL = 0;
        devices[dev].spi_reg.S0SPCR.CPHA = 0;
        break;
    case SPI_CONF_SECOND_FALLING:
        devices[dev].spi_reg.S0SPCR.CPOL = 0;
        devices[dev].spi_reg.S0SPCR.CPHA = 1;
        break;
    default:
        return -2;
    }

    if (master != 0) {
        devices[dev].master = 1;
        devices[dev].spi_reg.S0SPCR.MSTR = 1;
    }
    else {
        devices[dev].cb = cb;
    }

    devices[dev].spi_reg.S0SPCR.BitEnable = 1;

    // spi_speed_t, assume 120 MHz for now
    LPC_SYS_CTL.PCLKSEL0.PCLK_SPI = 0b01;

    switch (speed) {
    case SPI_SPEED_10MHZ:
      LPC_SPI0.S0SPCCR.Counter = 12;
        break;
    case SPI_SPEED_5MHZ:
      LPC_SPI0.S0SPCCR.Counter = 24;
        break;
    case SPI_SPEED_1MHZ:
      LPC_SPI0.S0SPCCR.Counter = 120;
        break;
    case SPI_SPEED_400KHZ:
      LPC_SYS_CTL.PCLKSEL0.PCLK_SPI = 0b00;
      LPC_SPI0.S0SPCCR.Counter= 75;
        break;
    case SPI_SPEED_100KHZ:
      LPC_SYS_CTL.PCLKSEL0.PCLK_SPI = 0b11;
      LPC_SPI0.S0SPCCR.Counter = 150;
        break;
    default:
        return -1;
    }
    
    return 0;
}

/**
 * @brief Initialize the given SPI device to work in master mode
 *
 * In master mode the SPI device is configured to control the SPI bus. This means the device
 * will start and end all communication on the bus and control the CLK line. For transferring
 * data on the bus the below defined transfer functions should be used.
 *
 * @param[in] dev       SPI device to initialize
 * @param[in] conf      Mode of clock phase and clock polarity
 * @param[in] speed     desired clock speed for driving the SPI bus
 *
 * @return              0 on success
 * @return              -1 on unavailable speed value
 * @return              -2 on other errors
 */
int spi_init_master(spi_t dev, spi_conf_t conf, spi_speed_t speed) {
#ifdef SPI_NUMOF
#ifdef SPI_0_EN
    if (dev == SPI_0) {
        return spi_init(dev, conf, speed, 1, 0);
    }
    
    return -2;
#else
#error No SPI configured, only SPI_0 is supported
#endif
#endif
}

/**
 * @brief Initialize the given SPI device to work in slave mode
 *
 * In slave mode the SPI device is purely reacting to the bus. Transaction will be started and
 * ended by a connected SPI master. When a byte is received, the callback is called in interrupt
 * context with this byte as argument. The return byte of the callback is transferred to the
 * master in the next transmission cycle. This interface enables easy implementation of a register
 * based access paradigm for the SPI slave.
 *
 * @param[in] dev       The SPI device to initialize as SPI slave
 * @param[in] conf      Mode of clock phase and polarity
 * @param[in] cb        callback called every time a byte was received
 *
 * @return              0 on success
 * @return              -1 on error
 */
int spi_init_slave(spi_t dev, spi_conf_t conf, char (*cb)(char)) {
#ifdef SPI_NUMOF
#ifdef SPI_0_EN
    if (dev == SPI_0) {
        return spi_init(dev, conf, 0, 0, cb);
    }
    
    return -2;
#else
#error No SPI configured, only SPI_0 is supported
#endif
#endif
}

/**
 * @brief Configure SCK, MISO and MOSI pins for the given SPI device
 *
 * @param[in] dev       SPI device to use
 *
 * @return              0 on success
 * @return              -1 on error
 */
int spi_conf_pins(spi_t dev) {
#ifdef SPI_0_EN
    // configure pins
    if(pinblock_connect(spi_pins, sizeof(spi_pins)/sizeof(pinblock_t))) {
        return -1;
    }
    
    return 0;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Get mutually exclusive access to the given SPI bus
 *
 * In case the SPI device is busy, this function will block until the bus is free again.
 *
 * @param[in] dev       SPI device to access
 *
 * @return              0 on success
 * @return              -1 on error
 */
int spi_acquire(spi_t dev) {
#ifdef SPI_0_EN
    mutex_lock(&(devices[dev].lock));
    return 0;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Release the given SPI device to be used by others
 *
 * @param[in] dev       SPI device to release
 *
 * @return              0 on success
 * @return              -1 on error
 */
int spi_release(spi_t dev) {
#ifdef SPI_0_EN
    mutex_unlock(&devices[dev].lock);
    return 0;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Transfer one byte on the given SPI bus
 *
 * @param[in] dev       SPI device to use
 * @param[in] out       Byte to send out, set NULL if only receiving
 * @param[out] in       Byte to read, set NULL if only sending
 *
 * @return              Number of bytes that were transfered
 * @return              -1 on error
 */
int spi_transfer_byte(spi_t dev, char out, char *in) {
#ifdef SPI_0_EN
    LPC_SPI0.S0SPCCR.Counter = devices[dev].spi_reg.S0SPCCR.Counter;
    //LPC_SPI0.S0SPCR = devices[dev].spi_reg.S0SPCR;
    LPC_SPI0.S0SPCR.BITS = 0b1000;
    
    LPC_SPI0.S0SPDR.DataLow = 0xffff & out;
    
    if(in != 0) {
    }
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Transfer a number bytes on the given SPI bus
 *
 * @param[in] dev       SPI device to use
 * @param[in] out       Array of bytes to send, set NULL if only receiving
 * @param[out] in       Buffer to receive bytes to, set NULL if only sending
 * @param[in] length    Number of bytes to transfer
 *
 * @return              Number of bytes that were transfered
 * @return              -1 on error
 */
int spi_transfer_bytes(spi_t dev, char *out, char *in, unsigned int length) {
#ifdef SPI_0_EN
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Transfer one byte to/from a given register address
 *
 * This function is a shortcut function for easier handling of register based SPI devices. As
 * many SPI devices use a register based addressing scheme, this function is a convenient short-
 * cut for interfacing with such devices.
 *
 * @param[in] dev       SPI device to use
 * @param[in] reg       Register address to transfer data to/from
 * @param[in] out       Byte to send, set NULL if only receiving data
 * @param[out] in       Byte to read, set NULL if only sending
 *
 * @return              Number of bytes that were transfered
 * @return              -1 on error
 */
int spi_transfer_reg(spi_t dev, uint8_t reg, char out, char *in) {
#ifdef SPI_0_EN
    return -1;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Transfer a number of bytes from/to a given register address
 *
 * This function is a shortcut function for easier handling of register based SPI devices. As
 * many SPI devices use a register based addressing scheme, this function is a convenient short-
 * cut for interfacing with such devices.
 *
 * @param[in] dev       SPI device to use
 * @param[in] reg       Register address to transfer data to/from
 * @param[in] out       Byte array to send data from, set NULL if only receiving
 * @param[out] in       Byte buffer to read into, set NULL if only sending
 * @param[in] length    Number of bytes to transfer
 *
 * @return              Number of bytes that were transfered
 * @return              -1 on error
 */
int spi_transfer_regs(spi_t dev, uint8_t reg, char *out, char *in, unsigned int length) {
#ifdef SPI_0_EN
    return -1;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Tell the SPI driver that a new transaction was started. Call only when SPI in slave mode!
 *
 * @param[in] dev       SPI device that is active
 * @param[in] reset_val The byte that is send to the master as first byte
 */
void spi_transmission_begin(spi_t dev, char reset_val) {
#ifdef SPI_0_EN
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Power on the given SPI device
 *
 * @param[in] dev       SPI device to power on
 */
inline void spi_poweron(spi_t dev) {
#ifdef SPI_0_EN
    LPC_SYS_CTL.PCONP.PCSPI = 1;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

/**
 * @brief Power off the given SPI device
 *
 * @param[in] dev       SPI device to power off
 */
inline void spi_poweroff(spi_t dev) {
#ifdef SPI_0_EN
    LPC_SYS_CTL.PCONP.PCSPI = 0;
#else
#error No SPI configured, only SPI_0 is supported
#endif
}

#endif /* SPI_NUMOF */

/** @} */
