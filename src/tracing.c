/* SPDX-FileCopyrightText: 2021-2022 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#include <string.h>

#include "otelc/tracing.h"

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
ot_tracer_provider_t *ot_create_tracer_provider(const struct ot_provider_opts *opts)
{
    (void) opts;

    return NULL;
}


ot_tracer_t *ot_tracer_create(const ot_tracer_provider_t *tp,
                              const struct ot_tracer_context *ctx)
{
    (void) tp;
    (void) ctx;

    return NULL;
}


void ot_tracer_get_id_hex(const ot_tracer_t *tracer, char *dst)
{
    (void) tracer;

    memset(dst, 0, 32);
}


void ot_tracer_get_id_bin(const ot_tracer_t *tracer, uint8_t *dst)
{
    (void) tracer;

    memset(dst, 0, 16);
}


ot_span_t *ot_span_start(const ot_tracer_t *tracer,
                         const ot_span_t *parent,
                         const char *name,
                         const struct ot_span_opts *opts)
{
    (void) tracer;
    (void) parent;
    (void) name;
    (void) opts;

    return NULL;
}


void ot_span_get_id_hex(const ot_span_t *span, char *dst)
{
    (void) span;

    memset(dst, 0, 16);
}


void ot_span_get_id_bin(const ot_span_t *span, uint8_t *dst)
{
    (void) span;

    memset(dst, 0, 8);
}


bool ot_span_is_recording(const ot_span_t *span)
{
    (void) span;

    return false;
}


void ot_span_set_status(ot_span_t *span,
                        enum ot_span_code code,
                        const char *msg)
{
    (void) span;
    (void) code;
    (void) msg;
}


void ot_span_set_name(ot_span_t *span,
                      const char *name)
{
    (void) span;
    (void) name;
}


void ot_span_set_attributes(ot_span_t *span,
                            const struct ot_attributes *kv)
{
    (void) span;
    (void) kv;
}


ot_tracer_t *ot_span_get_tracer(const ot_span_t *span)
{
    (void) span;

    return NULL;
}


void ot_span_add_event(ot_span_t *span,
                       const char *name,
                       const struct ot_event_opts *opts)
{
    (void) span;
    (void) name;
    (void) opts;
}


void ot_span_end(ot_span_t *span)
{
    (void) span;
}


void ot_span_release(ot_span_t *span)
{
    (void) span;
}
