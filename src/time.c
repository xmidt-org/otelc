/* SPDX-FileCopyrightText: 2021-2022 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

/* Needed for clock_gettime */
#define _POSIX_C_SOURCE 199309L

#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "time.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* Any real (wall) clock should return a time after this for now since it's been
 * 50 years since Jan 1, 1970.  This value represents Jan 1, 2020 UTC. */
#define UNIX_AT_50 1577836800

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int64_t time_now_ns(void)
{
    struct timespec tp;
    int64_t rv = 0;

    if (0 == clock_gettime(CLOCK_REALTIME, &tp)) {
        rv = tp.tv_sec;
        rv *= 1000000000;
        rv += tp.tv_nsec;
    }

    if (tp.tv_sec < UNIX_AT_50) {
        return 0;
    }

    return rv;
}


int64_t time_now_s(void)
{
    struct timespec tp;
    int64_t rv = 0;

    if (0 == clock_gettime(CLOCK_REALTIME, &tp)) {
        rv = tp.tv_sec;
    }

    if (tp.tv_sec < UNIX_AT_50) {
        return 0;
    }

    return rv;
}


int64_t time_boot_now_ns(void)
{
    struct timespec tp;
    int64_t rv = 0;

    if (0 == clock_gettime(CLOCK_MONOTONIC, &tp)) {
        rv = tp.tv_sec;
        rv *= 1000000000;
        rv += tp.tv_nsec;
    }

    return rv;
}


double time_diff(int64_t start, int64_t end)
{
    double s = (double) start;
    double e = (double) end;

    return (e - s) / 1000000000;
}
