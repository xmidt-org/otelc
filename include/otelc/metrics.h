/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

/* TODO: Very much a work in progress. */

#ifndef __METRICS_H__
#define __METRICS_H__

#include "common.h"

typedef struct ot_meter_provider ot_meter_provider_t;
typedef struct ot_meter ot_meter_t;
typedef struct ot_counter ot_counter_t;
typedef struct ot_fcounter ot_fcounter_t;
typedef struct ot_updown ot_updown_t;
typedef struct ot_fupdown ot_fupdown_t;

struct instrument_opts {
    struct ot_string name;
    struct ot_string unit;
    struct ot_string desc;
    struct ot_attributes kv;
};


/**
 *  Meter provider creates an implementation of the meter.  Unless the opts
 *  specified match an implementation present, the default meter provider will
 *  be used.
 */
ot_meter_provider_t *ot_create_meter_provider(const struct ot_provider_opts *opts);


/**
 *  Creates a meter from the specified meter provider.
 */
ot_meter_t *ot_meter_create(const ot_meter_provider_t *tp);


/*-- Counter APIs - Integer --------------------------------------------------*/

/**
 *  Create a counter instrument from the provided meter and options.  Once a
 *  counter is created it exists for the duration of the program.
 */
ot_counter_t ot_create_counter(const ot_meter_t *m,
                               const struct instrument_opts *opts);

ot_counter_t ot_counter_find(const ot_meter_t *m,
                             const struct instrument_opts *opts);

#if 0
void ot_mi_counter_add(ot_counter_t c,
                       uint64_t amount,
                       const struct ot_attributes *kv);

/*-- Counter APIs - Double ---------------------------------------------------*/

/* Monotonic Double version */
md_counter_t ot_create_md_counter(meter_t m, const struct instrument_opts *opts);
md_counter_t ot_md_counter_find(meter_provider_t mp, const struct instrument_opts *opts);
void ot_md_counter_add(md_counter_t c, double amount, const struct ot_attributes *kv);

/* UpDown Integer version */
udi_counter_t ot_create_udi_counter(meter_t m, const struct instrument_opts *opts);
udi_counter_t ot_udi_counter_find(meter_provider_t mp, const struct instrument_opts *opts);
void ot_udi_counter_add(udi_counter_t c, int64_t amount, const struct ot_attributes *kv);

/* UpDown Double version */
udd_counter_t ot_create_udd_counter(meter_t m, const struct instrument_opts *opts);
udd_counter_t ot_udd_counter_find(meter_provider_t mp, const struct instrument_opts *opts);
void ot_udd_counter_add(udd_counter_t c, double amount, const struct ot_attributes *kv);


/* Histogram focused */

/* Integer version */
i_histogram_t ot_create_i_histogram(meter_t m, const struct instrument_opts *opts,
                                    size_t bucket_count, int64_t *buckets);
i_histogram_t ot_i_histogram_find(meter_provider_t mp, const struct instrument_opts *opts);
void ot_i_histogram_record(i_histogram_t c, int64_t value, const struct ot_attributes *kv);

/* Double version */
d_histogram_t ot_create_d_histogram(meter_t m, const struct instrument_opts *opts,
                                    size_t bucket_count, double *buckets);
d_histogram_t ot_d_histogram_find(meter_provider_t mp, const struct instrument_opts *opts);
void ot_d_histogram_record(d_histogram_t c, double value, const struct ot_attributes *kv);

/* Asynchronous Counter focused */
/* TODO for now */

/* Asynchronous Gauge focused */
/* TODO for now */
#endif

#endif
