/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

/* This is still a work in progress.
 *
 *  Missing:
 *      - Asynchronous Counter focused
 *      - Asynchronous Gauge focused
 *
 *  Unsure:
 *      - Contexts & how that will work
 */

#ifndef __METRICS_H__
#define __METRICS_H__

#include "common.h"

typedef struct ot_meter_provider ot_meter_provider_t;
typedef struct ot_meter ot_meter_t;
typedef struct ot_counter ot_counter_t;
typedef struct ot_histogram ot_histogram_t;
typedef struct ot_udcounter ot_udcounter_t;

struct instrument_opts {
    struct ot_string unit;
    struct ot_string desc;
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
ot_meter_t *ot_meter_create(const ot_meter_provider_t *tp); /**< the provider to get meters from */


/*-- Counter APIs ------------------------------------------------------------*/

/**
 *  Create a counter instrument from the provided meter and options.  Once a
 *  counter is created it exists for the duration of the program.
 */
ot_counter_t *ot_create_counter(const ot_meter_t *m,                 /**< the meter that does the creation */
                                const struct ot_string *name,        /**< the name of the counter */
                                const struct instrument_opts *opts); /**< additional options */


/**
 *  Finds the counter that matches the name and provided attributes for later
 *  use.  If a new dimension of the meter is needed, this call will perform
 *  that operation as well.
 */
ot_counter_t *ot_counter_find(const ot_meter_t *m,          /**< the meter to reference */
                              const struct ot_string *name, /**< the name of the counter to look for */
                              struct ot_attributes *kv);    /**< any additional attributes */


/**
 *  Finds a counter based on an existing counter and it's options/configuration.
 *  Like ot_counter_find() this function can create new counters that express
 *  the specified dimensions.
 */
ot_counter_t *ot_counter_find_with(const ot_counter_t *c,     /**< find a more specific counter */
                                   struct ot_attributes *kv); /**< any additional attributes */


/**
 *  Increments the specified counter the specified amount.
 */
void ot_counter_add(ot_counter_t *c, /**< the counter to increment */
                    double amount);  /**< the amount to increment */

/**
 *  Increments the specified counter by 1.
 */
void ot_counter_inc(ot_counter_t *c); /**< the counter to increment */


/*-- Up/Down Counter APIs ----------------------------------------------------*/


/**
 *  Create an up/down counter instrument from the provided meter and options.
 *  Once a counter is created it exists for the duration of the program.
 */
ot_udcounter_t *ot_create_udcounter(const ot_meter_t *m,                 /**< the meter that does the creation */
                                    const struct ot_string *name,        /**< the name of the counter */
                                    const struct instrument_opts *opts); /**< additional options */


/**
 *  Finds the up/down counter that matches the name and provided attributes for
 *  later use.  If a new dimension of the meter is needed, this call will
 *  perform that operation as well.
 */
ot_udcounter_t *ot_udcounter_find(const ot_meter_t *m,          /**< the meter to reference */
                                  const struct ot_string *name, /**< the name of the counter to look for */
                                  struct ot_attributes *kv);    /**< any additional attributes */


/**
 *  Finds an up/down counter based on an existing counter and it's options or
 *  configuration.  Like ot_udcounter_find() this function can create new
 *  counters that express the specified dimensions.
 */
ot_udcounter_t *ot_udcounter_find_with(const ot_udcounter_t *c,   /**< find a more specific counter */
                                       struct ot_attributes *kv); /**< any additional attributes */


/**
 *  Increments the specified counter the specified amount.
 */
void ot_udcounter_add(ot_udcounter_t *c, /**< the counter to increment */
                      double amount);    /**< the amount to increment */


/*-- Histogram APIs ----------------------------------------------------------*/


/**
 *  Create an histogram instrument from the provided meter and options.
 *  Once a histogram is created it exists for the duration of the program.
 */
ot_histogram_t *ot_create_histogram(const ot_meter_t *m,                 /**< the meter that does the creation */
                                    const struct ot_string *name,        /**< the name of the histogram */
                                    const struct instrument_opts *opts); /**< additional options */


/**
 *  Finds the histogram that matches the name and provided attributes for
 *  later use.  If a new dimension of the meter is needed, this call will
 *  perform that operation as well.
 */
ot_histogram_t *ot_histogram_find(const ot_meter_t *m,          /**< the meter to reference */
                                  const struct ot_string *name, /**< the name of the histogram to look for */
                                  struct ot_attributes *kv);    /**< any additional attributes */


/**
 *  Finds an histogram based on an existing histogram and it's options or
 *  configuration.  Like ot_histogram_find() this function can create new
 *  histogram that express the specified dimensions.
 */
ot_histogram_t *ot_histogram_find_with(const ot_histogram_t *h,   /**< find a more specific histogram */
                                       struct ot_attributes *kv); /**< any additional attributes */


/**
 *  Records a measurement with the specified histogram.
 */
void ot_histogram_record(ot_histogram_t *h,   /**< the histogram to record with */
                         double measurement); /**< the amount to increment */

#endif
