/**
 * AES67 Framework
 * Copyright (C) 2021  Philip Tschiemer, https://github.com/tschiemer/aes67
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USBHID_MAP_H
#define USBHID_MAP_H

#include "report_item.h"
#include "report_usage.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


#ifdef __cplusplus
extern "C" {
#endif

struct usbhid_map_item_st {

    // main item
    uint8_t type;
    uint8_t opts;

    // global items
    uint8_t report_id;
    uint8_t report_size;
    uint32_t usage_page;
    int32_t logical_min;
    int32_t logical_max;
    int32_t physical_min;
    int32_t physical_max;
    int32_t unit_exponent;
    int32_t unit;

    // local items
    uint8_t usage;
    int32_t usage_min;
    int32_t usage_max;
    int32_t designator_index;
    int32_t designator_min;
    int32_t designator_max;
    int32_t string_index;
    int32_t string_min;
    int32_t string_max;
    int32_t delimiter;

    uint8_t report_offset; // internal helper
};


typedef struct {
    uint8_t usage_page;
    uint8_t usage;
    uint8_t report_count;
    uint8_t item_count;
    struct usbhid_map_item_st items[];
} usbhid_map_t;


typedef usbhid_map_t *usbhid_map_ref_t;

int usbhid_map_parse_desc(usbhid_map_ref_t *map_ref, const uint8_t *desc, const size_t len);

void usbhid_map_free(usbhid_map_ref_t map_ref);

size_t usbhid_map_get_report_ids(usbhid_map_ref_t map_ref, const uint8_t type, uint8_t *list);
size_t usbhid_map_get_report_item_count(usbhid_map_ref_t map_ref, const uint8_t type, uint8_t report_id);

struct usbhid_map_item_st *usbhid_map_get_item(
        usbhid_map_ref_t map_ref,
        uint8_t type,
        uint8_t report_id,
        uint8_t usage_page,
        uint8_t usage,
        struct usbhid_map_item_st *after
);

int usbhid_map_extract_values(int32_t *values, struct usbhid_map_item_st *items[], size_t icount, const uint8_t *report,
                              const size_t rsize);

#ifdef __cplusplus
}
#endif

#endif //USBHID_MAP_H
