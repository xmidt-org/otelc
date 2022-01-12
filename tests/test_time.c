/* SPDX-FileCopyrightText: 2021-2022 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

/* Needed for clock_gettime */
#define _POSIX_C_SOURCE 199309L

#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "otelc/time.h"

struct test_clock {
    time_t s;
    long ns;
    int rv;

    int more;
};

static struct test_clock *__mono;
static int clock_mono(struct timespec *tp)
{
    int rv = __mono->rv;

    tp->tv_sec  = __mono->s;
    tp->tv_nsec = __mono->ns;

    if (__mono->more) {
        __mono++;
    }
    return rv;
}


static struct test_clock *__rt;
static int clock_real(struct timespec *tp)
{
    int rv = __rt->rv;

    tp->tv_sec  = __rt->s;
    tp->tv_nsec = __rt->ns;

    if (__rt->more) {
        __rt++;
    }
    return rv;
}


int clock_gettime(clockid_t clockid, struct timespec *tp)
{
    if (CLOCK_REALTIME == clockid) {
        return clock_real(tp);
    } else if (CLOCK_MONOTONIC == clockid) {
        return clock_mono(tp);
    }

    return -1;
}


void test_boot_time()
{
    struct test_clock clocks[3] = {
        {.s = 100,       .ns = 0,  .rv = 0, .more = 1},
        {.s = 120, .ns = 1000000,  .rv = 0, .more = 1},
        {  .s = 0,       .ns = 0, .rv = -1, .more = 0},
    };
    int64_t t1 = 0LL;
    int64_t t2 = 0LL;
    double delta;

    __mono = clocks;

    t1 = time_boot_now_ns();
    t2 = time_boot_now_ns();

    CU_ASSERT(0LL == time_boot_now_ns());

    CU_ASSERT(100000000000 == t1);
    CU_ASSERT(120001000000 == t2);

    delta = time_diff(t1, t2);
    /* 20.001 +/- .0001*/
    CU_ASSERT(20.0009 < delta);
    CU_ASSERT(delta < 20.0011);

    printf("delta: %.6f\n", delta);
}


void add_suites(CU_pSuite *suite)
{
    *suite = CU_add_suite("time.c tests", NULL, NULL);
    CU_add_test(*suite, "boot time Tests", test_boot_time);
}


/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main(void)
{
    unsigned rv     = 1;
    CU_pSuite suite = NULL;

    if (CUE_SUCCESS == CU_initialize_registry()) {
        add_suites(&suite);

        if (NULL != suite) {
            CU_basic_set_mode(CU_BRM_VERBOSE);
            CU_basic_run_tests();
            printf("\n");
            CU_basic_show_failures(CU_get_failure_list());
            printf("\n\n");
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if (0 != rv) {
        return 1;
    }

    return 0;
}
