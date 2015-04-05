/*
 * File     syscalls.c
 * Author   Guillermo Reyes <guillermo.reyes@braincrums.solutions>
 *
 * Date     February 22, 2015, 4:59 PM
 * 
 * Copyright (C) braincrumbs Solutions
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

#include "board.h"
#include "thread.h"
#include "kernel.h"
#include "mutex.h"
#include "ringbuffer.h"
#include "irq.h"
#include "periph/uart.h"

extern char _sheap; /* start of the heap */
extern char _eheap; /* end of the heap */
caddr_t heap_top = (caddr_t) & _sheap + 4;

static mutex_t uart_rx_mutex;
static char rx_buf_mem[STDIO_RX_BUFSIZE];
static ringbuffer_t rx_buf;

int _wait_r(struct _reent *reent, int *status) {
    (void) status;

    reent->_errno = ENOTSUP;

    return -1;
}

int _fork_r(struct _reent *reent) {
    reent->_errno = ENOTSUP;

    return -1;
}

int _execve_r(struct _reent *reent, char *name, char **argv, char **env) {
    (void) name;
    (void) argv;
    (void) env;

    reent->_errno = ENOTSUP;

    return -1;
}

int _kill_r(struct _reent *r, int pid, int sig) {
    (void) pid;
    (void) sig;
    r->_errno = ESRCH; /* not implemented yet */
    return -1;
}

void rx_cb(void *arg, char data) {
    (void) arg;

    ringbuffer_add_one(&rx_buf, data);
    mutex_unlock(&uart_rx_mutex);
}

void _init(void) {
    mutex_init(&uart_rx_mutex);
    ringbuffer_init(&rx_buf, rx_buf_mem, STDIO_RX_BUFSIZE);
    uart_init(STDIO, STDIO_BAUDRATE, rx_cb, 0, 0);
}

void _fini(void) {
    /* nothing to do here */
}

void _exit(int n) {
    printf("#! exit %i: resetting\n", n);
    NVIC_SystemReset();
    while (1);
}

caddr_t _sbrk_r(struct _reent *reent, ptrdiff_t incr) {
    unsigned int state = disableIRQ();
    caddr_t res = heap_top;

    if (((incr > 0) && ((heap_top + incr > &_eheap) || (heap_top + incr < res))) ||
        ((incr < 0) && ((heap_top + incr < &_sheap) || (heap_top + incr > res)))) {
        reent->_errno = ENOMEM;
        res = (void *) - 1;
    }
    else {
        heap_top += incr;
    }

    restoreIRQ(state);
    return res;
}

int _getpid(void) {
    return sched_active_pid;
}

int _open_r(struct _reent *reent, const char *name, int mode) {
    (void) name;
    (void) mode;

    reent->_errno = ENODEV; /* not implemented yet */
    return -1;
}

int _read_r(struct _reent *reent, int fd, void *buffer, unsigned int count) {
    (void) fd;
    (void) count;

    while (rx_buf.avail == 0) {
        mutex_lock(&uart_rx_mutex);
    }

    reent->_errno = 0;

    return ringbuffer_get(&rx_buf, (char*) buffer, rx_buf.avail);
}

int _write_r(struct _reent *reent, int fd, const void *data, unsigned int count) {
    int i = 0;

    (void) fd;


    while (i < count) {
        uart_write_blocking(STDIO, ((char*) data)[i++]);
    }

    reent->_errno = 0;

    return i;
}

int _close_r(struct _reent *reent, int fd) {
    (void) fd;

    reent->_errno = ENODEV; /* not implemented yet */
    return -1;
}

_off_t _lseek_r(struct _reent *reent, int fd, _off_t pos, int dir) {
    (void) fd;
    (void) pos;
    (void) dir;

    reent->_errno = ENODEV; /* not implemented yet */
    return -1;
}

int _fstat_r(struct _reent *reent, int fd, struct stat * st) {
    (void) fd;
    (void) st;

    reent->_errno = ENODEV; /* not implemented yet */
    return -1;
}

int _stat_r(struct _reent *reent, char *name, struct stat *st) {
    (void) name;
    (void) st;

    reent->_errno = ENODEV; /* not implemented yet */
    return -1;
}

int _isatty_r(struct _reent *reent, int fd) {
    (void) fd;

    reent->_errno = 0;
    return 1;
}

int _unlink_r(struct _reent *r, char* path) {
    (void) path;

    r->_errno = ENODEV; /* not implemented yet */
    return -1;
}

__attribute__((weak))
int _kill(int pid, int sig) {
    (void) pid;
    (void) sig;

    errno = ESRCH; /* not implemented yet */
    return -1;
}
