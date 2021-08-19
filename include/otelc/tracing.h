/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __TRACING_H__
#define __TRACING_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "common.h"

typedef struct ot_tracer_provider ot_tracer_provider_t;
typedef struct ot_tracer ot_tracer_t;
typedef struct ot_span ot_span_t;

/* See: https://pkg.go.dev/go.opentelemetry.io/otel/trace#SpanKind */
enum ot_span_kind {
    OT_SPAN_KIND__UNSPECIFIED = 0, /* 0 */
    OT_SPAN_KIND__INTERNAL,        /* 1 */
    OT_SPAN_KIND__SERVER,          /* 2 */
    OT_SPAN_KIND__CLIENT,          /* 3 */
    OT_SPAN_KIND__PRODUCER,        /* 4 */
    OT_SPAN_KIND__CONSUMER,        /* 5 */
};

/* See: https://pkg.go.dev/go.opentelemetry.io/otel/trace#SpanKind */
enum ot_span_code {
    OT_SPAN_CODE__UNSED = 0, /* 0 */
    OT_SPAN_CODE__ERROR,     /* 1 */
    OT_SPAN_CODE__OK,        /* 2 */
};

enum ot_tracer_ctx_type {
    OT_CONTEXT__B3 = 0, /* 0 */
    OT_CONTEXT__W3C,    /* 1 */
};

struct ot_tracer_opts {
    struct ot_string name;
    struct ot_string version;
    struct ot_string schema_url;
};

struct ot_span_links {
    size_t count;
    ot_span_t *spans;
};

struct ot_span_opts {
    struct ot_attributes kv;
    struct ot_span_links links;
    enum ot_span_kind span_kind;
    int64_t time_ns; /**< 0 == now */
};

struct ot_event_opts {
    struct ot_attributes kv;
    int64_t time_ns; /**< 0 == now */
};

struct ot_tracer_w3c {
    struct ot_string traceparent;
    struct ot_string tracestate;
};

struct ot_tracer_context {
    enum ot_tracer_ctx_type type;
    union {
        struct ot_string b3;
        struct ot_tracer_w3c w3c;
    } u;
};


/**
 *  Tracer provider creates an implementation of the tracer.  Unless the opts
 *  specified match an implementation present, the default tracer provider will
 *  be used.
 */
ot_tracer_provider_t *ot_create_tracer_provider(const struct ot_provider_opts *opts);


/*-- Tracer object functions -------------------------------------------------*/


/**
 *  Creates a tracer from the specified tracer provider.
 */
ot_tracer_t *ot_tracer_create(const ot_tracer_provider_t *tp,
                              const struct ot_tracer_context *ctx);


/**
 *  Provides the 32 character hex string at the preallocated dst.  No trailing
 *  '\0' is provided.
 */
void ot_tracer_get_id_hex(const ot_tracer_t *tracer, /**< [in] tracer to examine */
                          char *dst);                /**< [out] trace_id destination */


/**
 *  Provides the 16 byte array at the preallocated dst.
 */
void ot_tracer_get_id_bin(const ot_tracer_t *tracer, /**< [in] tracer to examine */
                          uint8_t *dst);             /**< [out] trace_id destination */


/**
 *  Create a new span with the specified parent, name and links.  This uses the
 *  present time as the start time.
 *
 *  @return The opaque span object or NULL if there is an error.
 */
ot_span_t *ot_span_start(const ot_tracer_t *tracer,        /**< [in] tracer */
                         const ot_span_t *parent,          /**< [in] parent span */
                         const char *name,                 /**< [in] the name of the span */
                         const struct ot_span_opts *opts); /**< [in] the options to use */


/*-- Span object functions ---------------------------------------------------*/


/**
 *  Provides the 16 character hex string at the preallocated dst.  No trailing
 *  '\0' is provided.
 */
void ot_span_get_id_hex(const ot_span_t *span, /**< [in] span to examine */
                        char *dst);            /**< [out] span_id destination */


/**
 *  Provides the 8 byte array at the preallocated dst.
 */
void ot_span_get_id_bin(const ot_span_t *span, /**< [in] span to examine */
                        uint8_t *dst);         /**< [out] span_id destination */


/**
 *  Returns if the span is still recording.
 *
 *  @return True if the span is still recording, false otherwise.
 */
bool ot_span_is_recording(const ot_span_t *span); /**< [in] span to inspect */


/**
 *  Sets the status of the span in the form of a code and an optional message.
 *  The previous value of the status is overwritten by this call.
 */
void ot_span_set_status(ot_span_t *span,        /**< [in] span to alter */
                        enum ot_span_code code, /**< [in] code to set */
                        const char *msg);       /**< [in] msg to optionally set */


/**
 *  Sets the span name.
 *  The previous name of the span is overwritten by this call.
 */
void ot_span_set_name(ot_span_t *span,   /**< [in] span to alter */
                      const char *name); /**< [in] name to set */


/**
 *  Sets the attributes of the span.  The set of attributes for a span are a
 *  union of all attributes with the most recent key/value pair being used in
 *  the event of duplicate entries for a key.
 */
void ot_span_set_attributes(ot_span_t *span,                 /**< [in] span to alter */
                            const struct ot_attributes *kv); /**< [in] the key/values to set */


/**
 *  Returns the tracer that created the span.
 */
ot_tracer_t *ot_span_get_tracer(const ot_span_t *span); /**< [in] span to inspect */


/**
 *  Adds an event to the span with the provided name and options.  The current
 *  time is used for the event.
 */
void ot_span_add_event(ot_span_t *span,                   /**< [in] span to attach the event */
                       const char *name,                  /**< [in] name of the event */
                       const struct ot_event_opts *opts); /**< [in] the options to use */


/**
 *  End the span.  The span becomes immutable after this call, but will not be
 *  garbage collected until og_span_release() is called to release interest in
 *  the span.
 *
 *  By decoupling the end and release the span may stay present in the system
 *  and be referenced by other spans.
 */
void ot_span_end(ot_span_t *span); /**< [in] span to end */


/**
 *  Release interest in the specified span.  Once called, the specified span is
 *  never to be used or referenced again.  This indicates to the library that
 *  beyond any reporting it may do, the span may be disposed of at any time.
 *
 *  If another span references this span and ot_span_release() is called, the
 *  reference shall continue to work, but can no longer be linked by other spans.
 */
void ot_span_release(ot_span_t *span); /**< [in] span to release */

#endif
