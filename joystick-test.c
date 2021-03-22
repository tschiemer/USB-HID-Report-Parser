#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "usbhid_map.h"

// ID 046d:c215 Logitech Inc. Logitech Extreme 3D
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

        0x08, 0xf2, 0x17, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x27, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x37, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x47, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x57, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x67, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x77, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x07, 0x80, 0x00, 0x00, 0x00,
        // x, y

//        0, 0, 0, 0, 0, 0, 0,
//        1, 0, 0, 0, 0, 0, 0,
//        2, 0, 0, 0, 0, 0, 0,
//        0x10, 0, 0, 0, 0, 0, 0,
//        0x11, 0, 0, 0, 0, 0, 0,
//        0x20, 0, 0, 0, 0, 0, 0,
//        0xf0, 0, 0, 0, 0, 0, 0,
//        0xff, 0, 0, 0, 0, 0, 0,
//        0, 1, 0,0,0,0,0,
//        1, 1, 0,0,0,0,0,
//        0x11, 1, 0,0,0,0,0,
//        0xff, 1, 0,0,0,0,0,
//        0xff, 2, 0,0,0,0,0,
//        0xff, 4, 0,0,0,0,0,
//        0xff, 7, 0,0,0,0,0,
//        0xff, 0xf, 0,0,0,0,0,
//
//
//        0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x0c, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x30, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x50, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0xb0, 0x71, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x60, 0x77, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x80, 0x77, 0x00, 0x00, 0x00, 0x00,

// WARNING wrong assumption about report layout, the constructed values are WRONG

//        0, 0xfc, 0x0f, 0,0,0,0,
//        0xff, 0b11000000, 0, 0, 0, 0, 0,
//        0, 0b111111, 0b11110000, 0, 0, 0, 0,
//        0xff, 0xff, 0b11110000, 0, 0, 0, 0,

        // hat switch
//
//        0, 0, 0x1, 0,0,0,0,
//        0, 0, 0x2, 0,0,0,0,
//        0, 0, 0x4, 0,0,0,0,
//        0, 0, 0x4, 0,0,0,0,
//        0, 0, 0x8, 0,0,0,0,
//        0, 0, 0xf, 0,0,0,0,
//
//        // rz
//
//        0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 1, 0, 0, 0,
//        0, 0, 0, 0xf, 0, 0, 0,
//        0, 0, 0, 0x7f, 0, 0, 0,
//        0, 0, 0, 0x80, 0, 0, 0,
//        0, 0, 0, 0xff, 0, 0, 0,
//
//        // slider
//
//        0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 1, 0,
//        0, 0, 0, 0, 0, 4, 0,
//        0, 0, 0, 0, 0, 8, 0,
//        0, 0, 0, 0, 0, 0x10, 0,
//        0, 0, 0, 0, 0, 0x80, 0,
//        0, 0, 0, 0, 0, 0xff, 0,
//
//        // buttons
//
//        0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0b10000000, 0, 0,
//        0, 0, 0, 0, 0b01000000, 0, 0,
//        0, 0, 0, 0, 0b00100000, 0, 0,
//        0, 0, 0, 0, 0b00010000, 0, 0,
//        0, 0, 0, 0, 0b00001000, 0, 0,
//        0, 0, 0, 0, 0b00000100, 0, 0,
//        0, 0, 0, 0, 0b00000010, 0, 0,
//        0, 0, 0, 0, 0b00000001, 0, 0,
//        0, 0, 0, 0, 0b01010101, 0, 0,
//        0, 0, 0, 0, 0b10101010, 0, 0,
//        0, 0, 0, 0, 0, 0, 0b10000000,
//        0, 0, 0, 0, 0, 0, 0b01000000,
//        0, 0, 0, 0, 0, 0, 0b00100000,
//        0, 0, 0, 0, 0, 0, 0b00010000,
//        0, 0, 0, 0, 0, 0, 0b00001000,
//        0, 0, 0, 0, 0, 0, 0b00000100,
//        0, 0, 0, 0, 0, 0, 0b00000010,
//        0, 0, 0, 0, 0, 0, 0b00000001,
//        0, 0, 0, 0, 0, 0, 0b00010001,
//        0, 0, 0, 0, 0, 0, 0b00100010,
//        0, 0, 0, 0, 0, 0, 0b01000100,
//        0, 0, 0, 0, 0, 0, 0b10001000,


        //// REAL DATA

        0, 0, 0, 0, 0, 0, 0,

        // center
        0x08, 0x02, 0x88, 0x80, 0x00, 0x00, 0x00,

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

        0, 0, 0, 0, 0, 0, 0,

        // slider
        0x00, 0x22, 0x88, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x00, 0xb4, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x00, 0xff, 0x00,

        0, 0, 0, 0, 0, 0, 0,

        // buttons
        0x00, 0x22, 0x88, 0x80, 0x00, 0x00, 0x01,
        0x00, 0x22, 0x88, 0x80, 0x00, 0x00, 0x02,
        0x00, 0x22, 0x88, 0x80, 0x00, 0x00, 0x04,
        0x00, 0x22, 0x88, 0x80, 0x00, 0x00, 0x08,
        0x00, 0x22, 0x88, 0x80, 0x01, 0x00, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x10, 0x00, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x04, 0x00, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x08, 0x00, 0x00,
        0x00, 0x22, 0x88, 0x80, 0x20, 0x00, 0x00,

        0, 0, 0, 0, 0, 0, 0,

        // hat

        0x08, 0xf2, 0x17, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x27, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x37, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x47, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x57, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x67, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x77, 0x80, 0x00, 0x00, 0x00,
        0x08, 0xf2, 0x07, 0x80, 0x00, 0x00, 0x00,

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
                    printf(" page %d usage %d offset %d size %d \n", item->usage_page, item->usage, item->report_offset, item->report_size);
                }

                last = item;
//            } while(item);



        }
    }

//    return 0;

    struct usbhid_map_item_st * x = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_X, NULL);
    struct usbhid_map_item_st * y = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Y, NULL);
    struct usbhid_map_item_st * hat_switch = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Hat_Switch, NULL);
    struct usbhid_map_item_st * rz = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Rz, NULL);
    struct usbhid_map_item_st * slider = usbhid_map_get_item(map_ref, Input(0), 0, UP_Generic_Desktop, GD_Slider, NULL);

    #define NBUTTONS 17 // well there are only 16, but let's see wether the logic below works
    struct usbhid_map_item_st * buttons[NBUTTONS];

    memset(buttons, 0, sizeof(buttons));

    for (int i = 0; i < NBUTTONS && (i == 0 || buttons[i-1]); i++ ){
        buttons[i] = usbhid_map_get_item(map_ref, Input(0), 0, UP_Button, 0, i == 0 ? NULL : buttons[i-1]);
    }



    if (map_ref->usage_page == UP_Generic_Desktop && map_ref->usage == GD_Joystick){
        printf("is Joystick! :)\n");



        int32_t values[21];
        char * str[21];
        struct usbhid_map_item_st * items[21];

        size_t icount = 0;

        if (x){
            printf("x:  bitoffset %d size %d\n", x->report_offset, x->report_size);
            str[icount] = "x = %d  ";
            items[icount++] = x;
        }
        if (y){
            printf("y: bitoffset %d size %d\n", y->report_offset, y->report_size);
            str[icount] = "y = %d  ";
            items[icount++] = y;
        }
        if (hat_switch){
            printf("hat switch: bitoffset %d size %d\n", hat_switch->report_offset, hat_switch->report_size);
            str[icount] = "Hat Switch = %d  ";
            items[icount++] = hat_switch;
        }
        if (rz){
            printf("rz: bitoffset %d size %d\n", rz->report_offset, rz->report_size);
            str[icount] = "Rz = %d  ";
            items[icount++] = rz;
        }
        if (slider){
            printf("slider: bitoffset %d size %d\n", slider->report_offset, slider->report_size);
            str[icount] = "Slider = %d  ";
            items[icount++] = slider;
        }
        for (int i = 0; i < 16; i++){
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
