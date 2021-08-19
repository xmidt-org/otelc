/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __TIME_H__
#define __TIME_H__

#include <stdint.h>

/* 0 is the default for lots of things.  Because of that it just makes sense
 * for the special value that indicates right now to be 0.  I'm sorry to the
 * first nanosecond of 1970, while you can't directly be represented, your
 * slot will be used a lot. */
#define OT_NOW (0)

/**
 *  A simple and consistent wrapper that gives the present number of nanoseconds
 *  since midnight Jan 1, 1970 in UTC time.
 *
 *  @note It is reasonable and possible that this clock is not set correctly.
 *
 *  @return the number of nanoseconds since midnight Jan 1, 1970
 */
int64_t time_now_ns();


/**
 *  A simple and consistent wrapper that gives the present number of seconds
 *  since midnight midnight Jan 1, 1970 in UTC time.
 *
 *  @note It is reasonable and possible that this clock is not set correctly.
 *
 *  @return the number of seconds since midnight Jan 1, 1970
 */
int64_t time_now_s();


/**
 *  A simple and consistent wrapper that gives the present number of nanoseconds
 *  since boot.
 *
 *  @return the number of nanoseconds since booting
 */
int64_t time_boot_now_ns();


/**
 *  A simple function that takes the difference between two nanosecond times
 *  and returns a double representing the value.
 *
 *  @param start the starting time
 *  @param end   the end time
 *
 *  @return the double representing the seconds between the two points
 */
double time_diff(int64_t start, int64_t end);

#endif
