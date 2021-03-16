#include "usbhid_map.h"

#include <stdio.h>
#include <string.h>

#ifndef ITEM_GROUP_MAX_USAGES
#define ITEM_GROUP_MAX_USAGES   16
#endif

#ifndef ITEM_GROUP_MAX_STACK
#define ITEM_GROUP_MAX_STACK    5
#endif

#ifndef ITEM_GROUP_MAX_FINAL
#define ITEM_GROUP_MAX_FINAL    16
#endif

struct item_group_st {
    uint8_t usages[ITEM_GROUP_MAX_USAGES];
    uint8_t usages_i;
    uint8_t report_count;

    struct usbhid_map_item_st item;
};



void usbhid_map_free(usbhid_map_ref_t map_ref )
{
    assert(map_ref != NULL);

    free(map_ref);
}

int usbhid_map_parse_desc(usbhid_map_ref_t * map_ref, const uint8_t * desc, const size_t len)
{
    assert(map_ref != NULL);
    assert(desc != NULL);
    assert(len > 4);

    // always begin with USAGE_PAGE USAGE
    if (desc[0] != Usage_Page(1) || desc[2] != Usage(1)){
        return EXIT_FAILURE;
    }

    uint8_t usage_page = desc[1];
    uint8_t usage = desc[3];

    uint8_t fgi = 0;
    struct item_group_st final_groups[ITEM_GROUP_MAX_FINAL];

    size_t final_report_count = 0;
    size_t final_item_count = 0;

    uint8_t igs = 0;
    struct item_group_st item_group_stack[ITEM_GROUP_MAX_STACK];
    memset(&item_group_stack, 0, sizeof(struct item_group_st));

#define item_group          item_group_stack[igs]
    // on push items the global items should be pushed on stack
    // but we push everything
#define push_item_group()   { \
                                if(igs >= ITEM_GROUP_MAX_STACK) return EXIT_FAILURE; \
                                memset(&item_group_stack[++igs], 0, sizeof(struct item_group_st)); \
                            }
#define pop_item_group()    { \
                                if (igs == 0) return EXIT_FAILURE; \
                                igs--;           \
                            }

    // usage_page is a global field, so pass it on
    item_group.item.usage_page = usage_page;

    // start beyond initial usage + usage_page
    uint16_t index = 4;

    while(index < len) {

        uint8_t itemTag = desc[index] & TAG_MASK;
        uint8_t itemSize = ri_ItemSize(desc[index] & SIZE_MASK);
        int32_t itemData = 0;

        if(index + itemSize >= len){
            fprintf(stderr,"description corrupted, would go beyond buffer.\r\n");
            return EXIT_FAILURE;
        }

        if(itemSize == 1)
            itemData = desc[index + 1];
        else if(itemSize == 2)
            itemData = *((int16_t *)&desc[index + 1]);
        else if(itemSize == 4)
            itemData = *((int32_t *)&desc[index + 1]);
        else
            itemData = 0;

        switch(itemTag & TYPE_MASK)
        {
            case MAIN_ITEM:

                item_group.item.type = itemTag;
                item_group.item.opts = itemData;

                switch(itemTag)
                {
                    case Input(0):
                        if (fgi >= ITEM_GROUP_MAX_FINAL){
                            fprintf(stderr, "too small ITEM_GROUP_MAX_FINAL\n");
                            return EXIT_FAILURE;
                        }
                        if (item_group.report_count == 0){
                            item_group.report_count = 1;
                        }
                        else if (item_group.report_count > 1 && item_group.usages_i == 0){
                            for(int i = 0; i < item_group.report_count; i++){
                                item_group.usages_i = 0;
                            }
                        }
                        else if (item_group.usages_i < item_group.report_count){
                            if (item_group.usages_i == 1){
                                for(int i = 1; i < item_group.report_count; i++){
                                    item_group.usages[i] = item_group.usages[0];
                                }
                            } else {
                                fprintf(stderr, "not enough input items listed in group %d vs %d\n", item_group.usages_i, item_group.report_count);
                                return EXIT_FAILURE;
                            }
                        }
                        final_item_count += item_group.report_count;
                        memcpy(&final_groups[fgi++], &item_group, sizeof(struct item_group_st));
//                        index += ri_StringGet(str + index, "  Input (%s)", ri_dataType(Input(0), itemData));
                        break;
                    case Output(0):
                        if (fgi >= ITEM_GROUP_MAX_FINAL){
                            fprintf(stderr, "too small ITEM_GROUP_MAX_FINAL\n");
                            return EXIT_FAILURE;
                        }
                        if (item_group.report_count == 0){
                            item_group.report_count = 1;
                        }
                        else if (item_group.report_count > 1 && item_group.usages_i == 0){
                            for(int i = 0; i < item_group.report_count; i++){
                                item_group.usages_i = 0;
                            }
                        }
                        else if (item_group.usages_i < item_group.report_count){
                            if (item_group.usages_i == 1){
                                for(int i = 1; i < item_group.report_count; i++){
                                    item_group.usages[i] = item_group.usages[0];
                                }
                            } else {
                                fprintf(stderr, "not enough output items listed in group %d vs %d\n", item_group.usages_i, item_group.report_count);
                                return EXIT_FAILURE;
                            }
                        }
                        final_item_count += item_group.report_count;
                        memcpy(&final_groups[fgi++], &item_group, sizeof(struct item_group_st));
//                        index += ri_StringGet(str + index, "  Output (%s)", ri_dataType(Output(0), itemData));
                        break;
                    case Feature(0):
                        if (fgi >= ITEM_GROUP_MAX_FINAL){
                            fprintf(stderr, "too small ITEM_GROUP_MAX_FINAL\n");
                            return EXIT_FAILURE;
                        }
                        if (item_group.report_count == 0){
                            item_group.report_count = 1;
                        }
                        else if (item_group.report_count > 1 && item_group.usages_i == 0){
                            for(int i = 0; i < item_group.report_count; i++){
                                item_group.usages_i = 0;
                            }
                        }
                        else if (item_group.usages_i < item_group.report_count){
                            if (item_group.usages_i == 1){
                                for(int i = 1; i < item_group.report_count; i++){
                                    item_group.usages[i] = item_group.usages[0];
                                }
                            } else {
                                fprintf(stderr, "not enough feature items listed in group %d vs %d\n", item_group.usages_i, item_group.report_count);
                                return EXIT_FAILURE;
                            }
                        }
                        final_item_count += item_group.report_count;
                        memcpy(&final_groups[fgi++], &item_group, sizeof(struct item_group_st));
//                        index += ri_StringGet(str + index, "  Feature (%s)", ri_dataType(Feature(0), itemData));
                        break;
                    case Collection(0):
//                        index += ri_StringGet(str + index, "Collection (%s)", ri_ColletionType((uint8_t)itemData));
//                        if(itemData & 0xFFFFFF00U)
//                            index += ri_StringGet(str + index, " ???");
                        break;
                    case End_Colletion(0):
//                        index += ri_StringGet(str + index, "End Collection");
                        break;
                    default:
                        fprintf(stderr, "Unkonwn item: %02x\n", itemTag);
//                        return EXIT_FAILURE;
//                        index += ri_StringGet(str + index, "Unknown Item: %02X", itemTag);
                        break;
                }

                // reset internal counters
                item_group.usages_i = 0;
                item_group.report_count = 0;

                // reset local items
                item_group.item.usage = 0;
                item_group.item.usage_min = 0;
                item_group.item.usage_max = 0;
                item_group.item.designator_index = 0;
                item_group.item.designator_min = 0;
                item_group.item.designator_max = 0;
                item_group.item.string_index = 0;
                item_group.item.string_min = 0;
                item_group.item.string_max = 0;
                item_group.item.delimiter = 0;
                break;

            case GLOBAL_ITEM:

                switch(itemTag)
                {
                    case Usage_Page(0):
//                        assert((itemData & ~0xff) == 0); // require uint8_t
                        item_group.item.usage_page = itemData;
//                        printf("Usage Page (%02x)\n", itemData);
//                        *pUsagePage = itemData;
//                        index += ri_StringGet(str + index, "Usage Page (%s)", ri_UsagePage(itemData));
                        break;
                    case Logical_Minimum(0):
                        item_group.item.logical_min = itemData;
//                        index += ri_StringGet(str + index, "Logical Min (%d)", itemData);
                        break;
                    case Logical_Maximum(0):
                        item_group.item.logical_max = itemData;
//                        index += ri_StringGet(str + index, "Logical Max (%d)", itemData);
                        break;
                    case Physical_Minimum(0):
                        item_group.item.physical_min = itemData;
//                        index += ri_StringGet(str + index, "Physical Min (%d)", itemData);
                        break;
                    case Physical_Maximum(0):
                        item_group.item.physical_max = itemData;
//                        index += ri_StringGet(str + index, "Physical Max (%d)", itemData);
                        break;
                    case Unit_Exponent(0):
                        item_group.item.unit_exponent = itemData;

//                        assert( <= itemData && itemData <= 0x7);
//
//                        if( 0x04 < itemData && itemData < 0x10){
//                            input.unit_exponent = (int8_t[]){5,6,7,-8,-7,-6,-5,-4,-3,-2,-1}[itemData - 5];
//                        } else {
//                            input.unit_exponent = itemData;
//                        }

//                        index += ri_StringGet(str + index, "Unit Exponent (%s)", ri_Exponent(itemData));
                        break;
                    case Unit(0):
                        item_group.item.unit = itemData;
//                        index += ri_StringGet(str + index, "Unit (%s)", ri_Unit((uint32_t)itemData));
                        break;
                    case Report_Size(0):
                        assert((itemData & ~0xff) == 0); // require uint8_t
                        item_group.item.report_size = itemData;
//                        index += ri_StringGet(str + index, "Report Size (%d)", itemData);
                        break;
                    case Report_ID(0):
                        assert((itemData & ~0xff) == 0); // require uint8_t
                        item_group.item.report_id = itemData;
                        final_report_count++;
//                        index += ri_StringGet(str + index, "Report ID (%d)", itemData);
                        break;
                    case Report_Count(0):
                        assert((itemData & ~0xff) == 0); // require uint8_t
                        item_group.report_count = itemData;
//                        index += ri_StringGet(str + index, "Report Count (%d)", itemData);
                        break;
                    case Push(0):
                    push_item_group();
                        break;
                    case Pop(0):
                    pop_item_group();
                        break;
                    default:
                        fprintf(stderr, "unknown item %02x\n", itemTag);
//                        index += ri_StringGet(str + index, "Unknown Item: %02X", itemTag);
                        break;
                }
                break;
            case LOCAL_ITEM:

                switch(itemTag)
                {
                    case Usage(0):
                        /* TODO: 根据Usage Page查表 */
                        if (item_group.usages_i >= ITEM_GROUP_MAX_USAGES){
                            fprintf(stderr, "too many usages (too small ITEM_GROUP_MAX_USAGES)\n");
                            return EXIT_FAILURE;
                        }
                        item_group.usages[item_group.usages_i++] = itemData;
//                        printf("Usage (%02x) %d\n", itemData, item_group.usages_i);
//                        index += ri_StringGet(str + index, "Usage (%s)", ri_Usage(usagePage, itemData));
                        break;
                    case Usage_Minimum(0):
                        item_group.item.usage_min = itemData;
//                        index += ri_StringGet(str + index, "Usage Min (%d)", itemData);
                        break;
                    case Usage_Maximum(0):
                        item_group.item.usage_max = itemData;
//                        index += ri_StringGet(str + index, "Usage Max (%d)", itemData);
                        break;
                    case Designator_Index(0):
                        item_group.item.designator_index = itemData;
//                        index += ri_StringGet(str + index, "Designator Index (%d)", itemData);
                        break;
                    case Designator_Minimum(0):
                        item_group.item.designator_min = itemData;
//                        index += ri_StringGet(str + index, "Designator Min (%d)", itemData);
                        break;
                    case Designator_Maximum(0):
                        item_group.item.designator_max = itemData;
//                        index += ri_StringGet(str + index, "Designator Max (%d)", itemData);
                        break;
                    case String_Index(0):
                        item_group.item.string_index = itemData;
                        break;
                    case String_Minimum(0):
                        item_group.item.string_min = itemData;
                        break;
                    case String_Maximum(0):
                        item_group.item.string_max = itemData;
                        break;
                    case Delimiter(0):
                        item_group.item.delimiter = itemData;
                        /* defines the deginning or end of a set of local items.
                        ** 1 = open set, 0 = close set.
                        */
//                        index += ri_StringGet(str + index, "Delimiter (%s)", ri_DelimiterItem(itemData));
                    default:
                        fprintf(stderr, "unknown local item: %02x\n", itemTag);
                        break;
                }
                break;
            default:
                LOG("Unknown Type: %02X, index: %d\r\n", itemTag, index);
                break;
        }
        index += (itemSize + 1);
    }

    // sanity check
    if (index < len){
        return EXIT_FAILURE;
    }

    usbhid_map_ref_t mr = *map_ref = calloc(1, sizeof(usbhid_map_t) + final_item_count * sizeof(struct usbhid_map_item_st));

    mr->usage_page = usage_page;
    mr->usage = usage;
    mr->item_count = final_item_count;
    mr->report_count = final_report_count ? final_report_count : 1;

    int32_t current_type = -1;
    int32_t current_report = -1;
    uint32_t report_bit_offset = 0;

    for(int g = 0, i = 0; g < fgi; g++){
        for(int j = 0; j < final_groups[g].report_count; j++, i++){

            memcpy(&mr->items[i], &final_groups[g].item, sizeof(struct usbhid_map_item_st));

            mr->items[i].usage = final_groups[g].usages[j];

            if (current_type != mr->items[i].type){
                current_type = mr->items[i].type;
                current_report = mr->items[i].report_id;
                report_bit_offset = 0;
            }
            else if (current_report != mr->items[i].report_id){
                current_report = mr->items[i].report_id;
                report_bit_offset = 0;
            }

            mr->items[i].report_offset = report_bit_offset;

            report_bit_offset += mr->items[i].report_size;

//            printf("%d %02x %d %d\n", mr->items[i].report_id, mr->items[i].usage, mr->items[i].report_size, mr->items[i].report_bit_offset);
        }
    }

    return EXIT_SUCCESS;
}


size_t usbhid_map_get_report_ids(usbhid_map_ref_t map_ref, uint8_t type, uint8_t *list)
{
    assert(map_ref != NULL);
    assert(list != NULL);

    int last_report_id = -1;

    struct usbhid_map_item_st * item = map_ref->items;
    size_t icount = map_ref->item_count;

    size_t rcount = 0;

    for(int i = 0; i < icount; i++, item++){
        if (type == item->type && last_report_id != item->report_id){
            list[rcount++] = last_report_id = item->report_id;
        }
    }

    assert(rcount == map_ref->report_count);

    return rcount;
}

struct usbhid_map_item_st * usbhid_map_get_item(
        usbhid_map_ref_t map_ref,
        uint8_t type,
        uint8_t report_id,
        uint8_t usage_page,
        uint8_t usage,
        struct usbhid_map_item_st *after
)
{
    assert(map_ref != NULL);
    assert(after == NULL || map_ref->items <= after);

    struct usbhid_map_item_st * item = after ? after : map_ref->items;
    size_t count = map_ref->item_count - ((after - map_ref->items) / sizeof(struct usbhid_map_item_st));
    for(;count--; item++){
        if (item->type == type && item->report_id == report_id && item->usage_page == usage_page && item->usage == usage){
            return item;
        }
    }

    return NULL;
}

int usbhid_map_extract_values(int32_t *values, struct usbhid_map_item_st *items[], size_t icount, const uint8_t *report,
                              const size_t rsize)
{
    assert(values != NULL);
    assert(items != NULL);
    assert(icount > 0);
    assert(report != NULL);
    assert(rsize > 0);

    // for all items
    for(int i = 0; i < icount; i++){
        uint8_t byte = items[i]->report_offset / 8;
        uint8_t byte_end = byte + items[i]->report_size / 8;

        assert(byte_end < rsize);

        uint8_t bit = items[i]->report_offset % 8;
        uint8_t nbits = items[i]->report_size;

//        printf("bit %d nbits %d\n", bit, nbits);

        int32_t v = ntohl(*(int32_t*)&report[byte]);
        v = ((v >> (32 - bit - nbits)) & ~(~0 << nbits));

        values[i] = v;

//        printf("byte %d bit %d nbits %d val %d\n", byte, bit, nbits, v);



    }

    return EXIT_SUCCESS;
}
 