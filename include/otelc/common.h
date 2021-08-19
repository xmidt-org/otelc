/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct ot_string {
    size_t len;
    const char *s;
};

struct ot_string_attribute {
    struct ot_string key;
    struct ot_string value;
};

struct ot_bool_attribute {
    struct ot_string key;
    bool value;
};

struct ot_double_attribute {
    struct ot_string key;
    double value;
};

struct ot_int64_attribute {
    struct ot_string key;
    int64_t value;
};

struct ot_attributes {
    size_t count;
    union {
        struct ot_string_attribute *strings;
        struct ot_bool_attribute *bools;
        struct ot_double_attribute *doubles;
        struct ot_int64_attribute *int64s;
    } u;
};

struct ot_provider_opts {
    struct ot_string name;
    struct ot_string version;
    struct ot_string schema_url;
};


#endif
