#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "usbhid_map.h"

//
const uint8_t desc[] = {
        0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
        0x09, 0x02,        // Usage (Mouse)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x01,        //   Usage (Pointer)
        0xA1, 0x00,        //   Collection (Physical)
        0x05, 0x09,        //     Usage Page (Button)
        0x15, 0x00,        //     Logical Minimum (0)
        0x25, 0x01,        //     Logical Maximum (1)
        0x19, 0x01,        //     Usage Minimum (0x01)
        0x29, 0x07,        //     Usage Maximum (0x07)
        0x95, 0x07,        //     Report Count (7)
        0x75, 0x01,        //     Report Size (1)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x95, 0x01,        //     Report Count (1)
        0x75, 0x01,        //     Report Size (1)
        0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
        0x09, 0x30,        //     Usage (X)
        0x09, 0x31,        //     Usage (Y)
        0x09, 0x38,        //     Usage (Wheel)
        0x15, 0x81,        //     Logical Minimum (-127)
        0x25, 0x7F,        //     Logical Maximum (127)
        0x75, 0x08,        //     Report Size (8)
        0x95, 0x03,        //     Report Count (3)
        0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,              //   End Collection
        0xC0,              // End Collection

// 52 bytes

};

const size_t len = sizeof(desc);

#define REPORT_SIZE 4

const uint8_t reports[] = {

        0, 0, 0, 0,
        1, 0, 0, 0,
        2, 0, 0, 0,
        4, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,

};

const size_t report_count = sizeof(reports) / REPORT_SIZE;

int main(int argc, char * argv[])
{


    usbhid_map_ref_t map_ref;

    if (usbhid_map_parse_desc(&map_ref, desc, len)){
        return EXIT_FAILURE;
    }

    printf("Usage page: %d\n", map_ref->usage_page);
    printf("Usage: %d\n", map_ref->usage);
    printf("Report count: %d\n", map_ref->report_count);

    uint8_t report_id_list[8];

    memset(report_id_list, 0, sizeof(report_id_list));

    assert(sizeof(report_id_list) >= map_ref->report_count);

    size_t rid_count = usbhid_map_get_report_ids(map_ref, Input(0), report_id_list, sizeof(report_id_list));

    if (rid_count == 0){
        fprintf(stderr,"No input reports!\n");
        usbhid_map_free(map_ref);
        return EXIT_FAILURE;
    }
    printf("Input reports: %zu [", rid_count);
    for(int i = 0; i < rid_count; i++){
        printf("%d%s", report_id_list[i], i+1 < rid_count ? ", " : "");
    }
    printf("]\n");

    for(int r = 0; r < rid_count; r++){
        size_t ic = usbhid_map_get_report_item_count(map_ref, Input(0), report_id_list[r]);
        printf("Report %d item count: %zu\n", r, ic);

        struct usbhid_map_item_st * last = NULL;
        for(int i = 0; i < ic; i++){
//            printf("i %d ic %d  \n", i, ic);
            struct usbhid_map_item_st * item = NULL;
            uint8_t usage_page = 0;
            uint8_t usage = 0;
//            do {
                item = usbhid_map_get_item(map_ref, Input(0), report_id_list[r], usage_page, usage, last);

                if (item){
                    usage_page = item->usage_page;
                    usage = item->usage;
                    printf(" report_id %d usage_page 0x%02x usage 0x%02x size %d\n", report_id_list[r], item->usage_page, item->usage, item->report_size);
                }

                last = item;
//            } while(item);



        }
    }

    struct usbhid_map_item_st * x = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_X, NULL);
    struct usbhid_map_item_st * y = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Y, NULL);
    struct usbhid_map_item_st * wheel = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Wheel, NULL);

    #define NBUTTONS 10
    struct usbhid_map_item_st * buttons[NBUTTONS];

    memset(buttons, 0, sizeof(buttons));

    for (int i = 0; i < NBUTTONS && (i == 0 || buttons[i-1]); i++ ){
        buttons[i] = usbhid_map_get_item(map_ref, Input(0), 0, UP_Button, 0, i == 0 ? NULL : buttons[i-1]);
    }



    if (map_ref->usage_page == UP_Generic_Desktop && map_ref->usage == GD_Mouse){
        printf("is mouse! :)\n");



        int32_t values[21];
        char * str[21];
        struct usbhid_map_item_st * items[21];

        size_t icount = 0;

        if (x){
            printf("x: bitoffset %d size %d\n", x->report_offset, x->report_size);
            str[icount] = "x = %d  ";
            items[icount++] = x;
        }
        if (y){
            printf("y: bitoffset %d size %d\n", y->report_offset, y->report_size);
            str[icount] = "y = %d  ";
            items[icount++] = y;
        }
        if (wheel){
            printf("wheel: bitoffset %d size %d\n", wheel->report_offset, wheel->report_size);
            str[icount] = "Wheel = %d  ";
            items[icount++] = wheel;
        }
        for (int i = 0; i < NBUTTONS; i++){
            if (buttons[i]){
                printf("button[%d]: bitoffset %d size %d\n", i, buttons[i]->report_offset, buttons[i]->report_size);
                str[icount] = "%d";
                items[icount++] = buttons[i];
            }
        }

        for (int i = 0; i < report_count; i++){


            usbhid_map_extract_values(values, items, icount, &reports[i*REPORT_SIZE], REPORT_SIZE);

            for (int j = 0; j < REPORT_SIZE; j++){
                printf("%02x ", reports[i*REPORT_SIZE + j]);
            }
            printf("   ");

            for(int v = 0; v < icount; v++){
                printf(str[v], values[v]);
            }

            printf("\n");
        }

    }


    usbhid_map_free(map_ref);

    return 0;
}
