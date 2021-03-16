#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "usbhid_map.h"


const uint8_t desc[] = {
        0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
        0x09, 0x04,        // Usage (Joystick)
        0xA1, 0x01,        // Collection (Application)
        0xA1, 0x02,        //   Collection (Logical)
        0x95, 0x02,        //     Report Count (2)
        0x75, 0x0A,        //     Report Size (10)
        0x15, 0x00,        //     Logical Minimum (0)
        0x26, 0xFF, 0x03,  //     Logical Maximum (1023)
        0x35, 0x00,        //     Physical Minimum (0)
        0x46, 0xFF, 0x03,  //     Physical Maximum (1023)
        0x09, 0x30,        //     Usage (X)
        0x09, 0x31,        //     Usage (Y)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x75, 0x04,        //     Report Size (4)
        0x95, 0x01,        //     Report Count (1)
        0x25, 0x07,        //     Logical Maximum (7)
        0x46, 0x3B, 0x01,  //     Physical Maximum (315)
        0x66, 0x14, 0x00,  //     Unit (System: English Rotation, Length: Centimeter)
        0x09, 0x39,        //     Usage (Hat switch)
        0x81, 0x42,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
        0x65, 0x00,        //     Unit (None)
        0x75, 0x08,        //     Report Size (8)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x09, 0x35,        //     Usage (Rz)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xA4,              //     Push
        0x95, 0x08,        //       Report Count (8)
        0x75, 0x01,        //       Report Size (1)
        0x25, 0x01,        //       Logical Maximum (1)
        0x45, 0x01,        //       Physical Maximum (1)
        0x05, 0x09,        //       Usage Page (Button)
        0x19, 0x01,        //       Usage Minimum (0x01)
        0x29, 0x08,        //       Usage Maximum (0x08)
        0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xB4,              //     Pop
        0x09, 0x36,        //     Usage (Slider)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x95, 0x04,        //     Report Count (4)
        0x75, 0x01,        //     Report Size (1)
        0x25, 0x01,        //     Logical Maximum (1)
        0x45, 0x01,        //     Physical Maximum (1)
        0x05, 0x09,        //     Usage Page (Button)
        0x19, 0x09,        //     Usage Minimum (0x09)
        0x29, 0x0C,        //     Usage Maximum (0x0C)
        0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x95, 0x04,        //     Report Count (4)
        0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0xC0,              //   End Collection
        0xA1, 0x02,        //   Collection (Logical)
        0x95, 0x04,        //     Report Count (4)
        0x75, 0x08,        //     Report Size (8)
        0x26, 0xFF, 0x00,  //     Logical Maximum (255)
        0x46, 0xFF, 0x00,  //     Physical Maximum (255)
        0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        //     Usage (0x01)
        0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0,              //   End Collection
        0xC0,              // End Collection

// 122 bytes
};

const size_t len = sizeof(desc);

#define REPORT_SIZE 7

const uint8_t reports[] = {
        0, 0, 0, 0, 0, 0, 0,
        0xff, 0b11000000, 0, 0, 0, 0, 0,
        0, 0b111111, 0b11110000, 0, 0, 0, 0,
        0xff, 0xff, 0b11110000, 0, 0, 0, 0,

        //// REAL DATA

        0, 0, 0, 0, 0, 0, 0,

        // center
        0x00, 0x02, 0x88, 0x80, 0x00, 0xff, 0x00,

        0, 0, 0, 0, 0, 0, 0,

        // front
        0xd4, 0x01, 0x80, 0x91, 0x00, 0xff, 0x00,

        // rear
        0x98, 0xfe, 0x8f, 0x75, 0x00, 0xff, 0x00,

        // left
        0x00, 0x70, 0x87, 0x80, 0x00, 0xff, 0x00,

        // right
        0xff, 0xf3, 0x87, 0x7b, 0x00, 0xff, 0x00,


        0, 0, 0, 0, 0, 0, 0,


        // front left
        0x00, 0x00, 0x80, 0xa6, 0x00, 0xff, 0x00,

        // front right
        0xff, 0x03, 0x80, 0x8a, 0x00, 0xff, 0x00,

        // rear left
        0x00, 0xfc, 0x8f, 0x76, 0x00, 0xff, 0x00,

        // rear right
        0xff, 0xff, 0x8f, 0x8d, 0x00, 0xff, 0x00,


        0, 0, 0, 0, 0, 0, 0,

        // center (rx left)
        0x02, 0xf2, 0x87, 0x00, 0x00, 0xff, 0x00,

        // center
        0x00, 0x02, 0x88, 0x80, 0x00, 0xff, 0x00,

        // center (rx right)
        0x00, 0xf2, 0x87, 0xff, 0x00, 0xff, 0x00,


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

    struct usbhid_map_item_st * x = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_X, NULL);
    struct usbhid_map_item_st * y = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Y, NULL);

    uint8_t report_id_list[8];

    assert(sizeof(report_id_list) >= map_ref->report_count);

    size_t r = usbhid_map_get_report_ids(map_ref, Input(0), report_id_list);

    if (r == 0){
        fprintf(stderr,"No input reports!\n");
        usbhid_map_free(map_ref);
        return EXIT_FAILURE;
    }

    if (map_ref->usage_page == UP_Generic_Desktop && map_ref->usage == GD_Joystick){
        printf("is Joystick! :)\n");

        printf("has x ? %s", x ? "yes, " : "no\n");
        if (x){
            printf("report %d bitoffset %d size %d\n", x->report_id, x->report_offset, x->report_size);
        }

        printf("has y ? %s", y ? "yes, " : "no\n");
        if (y){
            printf("report %d bitoffset %d size %d\n", y->report_id, y->report_offset, y->report_size);
        }

        if (x && y){

            int32_t values[2];
            struct usbhid_map_item_st * items[2] = {x,y};

            for (int i = 0; i < report_count; i++){


                usbhid_map_extract_values(values, items, 2, &reports[i*REPORT_SIZE], REPORT_SIZE);

                for (int j = 0; j < REPORT_SIZE; j++){
                    printf("%02x ", reports[i*REPORT_SIZE + j]);
                }
                printf("\t x / y \t %d\t %d\n", values[0], values[1]);
            }
        }
    }


    usbhid_map_free(map_ref);

    return 0;
}
