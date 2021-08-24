/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#include "otelc/metrics.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */

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
ot_meter_provider_t *ot_create_meter_provider(const struct ot_provider_opts *opts)
{
    (void)opts;
    return NULL;
}


ot_meter_t *ot_meter_create(const ot_meter_provider_t *tp)
{
    (void)tp;
    return NULL;
}


ot_counter_t *ot_create_counter(const ot_meter_t *m,
                                const struct ot_string *name,
                                const struct instrument_opts *opts)
{
    (void)m;
    (void)name;
    (void)opts;
    return NULL;
}


ot_counter_t *ot_counter_find(const ot_meter_t *m,
                              const struct ot_string *name,
                              struct ot_attributes *kv)
{
    (void)m;
    (void)name;
    (void)kv;
    return NULL;
}


ot_counter_t *ot_counter_find_with(const ot_counter_t *c,
                                   struct ot_attributes *kv)
{
    (void)c;
    (void)kv;
    return NULL;
}


void ot_counter_add(ot_counter_t *c,
                    double amount)
{
    (void)c;
    (void)amount;
}


void ot_counter_inc(ot_counter_t *c)
{
    (void)c;
}


ot_udcounter_t *ot_create_udcounter(const ot_meter_t *m,
                                    const struct ot_string *name,
                                    const struct instrument_opts *opts)
{
    (void)m;
    (void)name;
    (void)opts;
    return NULL;
}


ot_udcounter_t *ot_udcounter_find(const ot_meter_t *m,
                                  const struct ot_string *name,
                                  struct ot_attributes *kv)
{
    (void)m;
    (void)name;
    (void)kv;
    return NULL;
}


ot_udcounter_t *ot_udcounter_find_with(const ot_udcounter_t *c,
                                       struct ot_attributes *kv)
{
    (void)c;
    (void)kv;
    return NULL;
}


void ot_udcounter_add(ot_udcounter_t *c,
                      double amount)
{
    (void)c;
    (void)amount;
}


ot_histogram_t *ot_create_histogram(const ot_meter_t *m,
                                    const struct ot_string *name,
                                    const struct instrument_opts *opts)
{
    (void)m;
    (void)name;
    (void)opts;
    return NULL;
}


ot_histogram_t *ot_histogram_find(const ot_meter_t *m,
                                  const struct ot_string *name,
                                  struct ot_attributes *kv)
{
    (void)m;
    (void)name;
    (void)kv;
    return NULL;
}


ot_histogram_t *ot_histogram_find_with(const ot_histogram_t *h,
                                       struct ot_attributes *kv)
{
    (void)h;
    (void)kv;
    return NULL;
}


void ot_histogram_record(ot_histogram_t *h,
                         double measurement)
{
    (void)h;
    (void)measurement;
    return NULL;
}

