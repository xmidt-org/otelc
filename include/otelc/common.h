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

struct ot_attribute {
    struct ot_string key;
    struct ot_string val;
};

struct ot_attributes {
    size_t count;
    struct ot_attribute *attributes;
};

struct ot_provider_opts {
    struct ot_string name;
    struct ot_string version;
    struct ot_string schema_url;
};


#endif
