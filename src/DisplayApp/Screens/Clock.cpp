#include <cstdio>
#include <libs/date/includes/date/date.h>
#include <Components/DateTime/DateTimeController.h>
#include <libs/lvgl/lvgl.h>
#include "Clock.h"
#include "../DisplayApp.h"
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "Symbols.h"
using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;
extern lv_style_t* LabelBigStyle;

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  Clock* screen = static_cast<Clock *>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}

//bitmap
static lv_img_dsc_t bitmap;                                           

const uint8_t bitmap_map[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x10, 0x8e, 0xff, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0xaa, 0xde, 0xa9, 0xde, 0xa9, 0xde, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08, 0x6e, 0xff, 0x00, 0x00, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0xa9, 0xde, 0xa9, 0xde, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0xff, 0x8e, 0xff, 0x8e, 0xff, 0x7b, 0xff, 0x01, 0x00, 0x20, 0x00, 0x7b, 0xff, 0x00, 0x00, 0xa9, 0xde, 0xa9, 0xde, 0xa9, 0xde, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0xff, 0xad, 0xff, 0x7a, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x96, 0xff, 0x55, 0xff, 0x35, 0xff, 0xaa, 0xde, 0xaa, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x74, 0xb5, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0xdc, 0xff, 0x74, 0xff, 0x55, 0xff, 0x55, 0xff, 0x54, 0xff, 0x8a, 0xe6, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0x41, 0x08, 0xa9, 0xde, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0xbb, 0xff, 0x55, 0xff, 0x55, 0xff, 0x75, 0xff, 0x00, 0x08, 0xa9, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x21, 0x08, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x08, 0x55, 0xff, 0x55, 0xff, 0x54, 0xff, 0xe2, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0xad, 0x7b, 0x7a, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0x35, 0xff, 0x36, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xad, 0x7b, 0xdc, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0x20, 0x00, 0x9b, 0xff, 0x35, 0xff, 0x35, 0xff, 0x35, 0xff, 0x35, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xe3, 0x18, 0x00, 0x00, 0x00, 0x00, 0x91, 0xbd, 0x55, 0xff, 0x75, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x29, 0x9b, 0xff, 0x9b, 0xff, 0x7b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0xd4, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0xfd, 0xff, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x55, 0xff, 0x55, 0xff, 0x15, 0xf7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x6a, 0x7b, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x35, 0xff, 0x55, 0xff, 0x35, 0xff, 0x43, 0x31, 0x55, 0xff, 0x35, 0xff, 0x2d, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x00, 0x00, 0x55, 0xff, 0x55, 0xff, 0x35, 0xff, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x46, 0x21, 0x55, 0xff, 0x01, 0x00, 0x21, 0x00, 0x76, 0xff, 0x55, 0xff, 0x23, 0x29, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x9a, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x01, 0x00, 0x00, 0x00, 0x55, 0xff, 0xf6, 0x4b, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x55, 0xff, 0x55, 0xff, 0x95, 0xff, 0x00, 0x00, 0x35, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xd7, 0x43, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x9b, 0xff, 0x9a, 0xff, 0x00, 0x00, 0x55, 0xff, 0x22, 0x31, 0x55, 0xff, 0xf7, 0x4b, 0xf7, 0x4b, 0x5b, 0x8d, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x00, 0x00, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x40, 0x08, 0xd8, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x5a, 0xff, 0x55, 0xff, 0x34, 0xff, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x20, 0x00, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0xff, 0x35, 0xff, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x32, 0x43, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x29, 0x6b, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x82, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0xd6, 0xff, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5a, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x20, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd6, 0x4b, 0xd1, 0x32, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd0, 0x32, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5b, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x20, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0xd6, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd7, 0x4b, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x5b, 0x8d, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x21, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x21, 0x5a, 0x85, 0x5a, 0x85, 0x5b, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x21, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xb0, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0x3a, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0x82, 0x10, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0xf1, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0xff, 0x51, 0x53, 0x5a, 0x85, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0xb6, 0x43, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xff, 0x55, 0xff, 0x35, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x01, 0x00, 0xf7, 0x4b, 0xf7, 0x4b, 0xd6, 0x43, 0x20, 0x00, 0x00, 0x00, 0x35, 0xff, 0x00, 0x00, 0xd0, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xb0, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x39, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0x20, 0x00, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xa2, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x76, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x55, 0xff, 0x93, 0xe6, 0x00, 0x00, 0x96, 0xff, 0x55, 0xff, 0x55, 0xff, 0x57, 0xff, 0x75, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5b, 0x85, 0xf7, 0x4b, 0x63, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xf7, 0x53, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x55, 0xff, 0x55, 0xff, 0x00, 0x00, 0x55, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xf2, 0x32, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x85, 0x5a, 0x85, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x94, 0x43, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x85, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x53, 0x3b, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0xd1, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd6, 0x43, 0xf7, 0x4b, 0xf7, 0x4b, 0xf7, 0x4b, 0x12, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};  

Clock::Clock(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController}, bleController{bleController} {
  displayedChar[0] = 0;
  displayedChar[1] = 0;
  displayedChar[2] = 0;
  displayedChar[3] = 0;
  displayedChar[4] = 0;
                                        
  batteryIcon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(batteryIcon, Symbols::batteryFull);
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  batteryPlug = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(bleIcon, Symbols::bluetooth);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);
                                               
  bitmap.header.always_zero = 0;
  bitmap.header.w = ????;
  bitmap.header.h = ????;
  bitmap.data_size = ???;
  bitmap.header.cf = ???;
  bitmap.data = bitmap_map;
  lv_obj_t *img_src = lv_img_create(lv_scr_act(), NULL);  /*Crate an image object*/
  lv_img_set_src(img_src, &bitmap);  /*Set the created file as image (a red fl  ower)*/
  lv_obj_set_pos(img_src, 10, 10);      /*Set the positions*/                                             
                                             
  label_date = lv_label_create(lv_scr_act(), NULL);

  lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 80);

  label_time = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  backgroundLabel = lv_label_create(lv_scr_act(), NULL);
  backgroundLabel->user_data = this;
  lv_obj_set_click(backgroundLabel, true);
  lv_obj_set_event_cb(backgroundLabel, event_handler);
  lv_label_set_long_mode(backgroundLabel, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundLabel, 240, 240);
  lv_obj_set_pos(backgroundLabel, 0, 0);
  lv_label_set_text(backgroundLabel, "");


  heartbeatIcon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(heartbeatIcon, Symbols::heartBeat);
  lv_obj_align(heartbeatIcon, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 5, -2);

  heartbeatValue = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(heartbeatValue, "0");
  lv_obj_align(heartbeatValue, heartbeatIcon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

  heartbeatBpm = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(heartbeatBpm, "BPM");
  lv_obj_align(heartbeatBpm, heartbeatValue, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

  stepValue = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(stepValue, "0");
  lv_obj_align(stepValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, -5, -2);

  stepIcon = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(stepIcon, Symbols::shoe);
  lv_obj_align(stepIcon, stepValue, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

Clock::~Clock() {
  lv_obj_clean(lv_scr_act());
}

bool Clock::Refresh() {
  batteryPercentRemaining = batteryController.PercentRemaining();
  if (batteryPercentRemaining.IsUpdated()) {
    auto batteryPercent = batteryPercentRemaining.Get();
    lv_label_set_text(batteryIcon, BatteryIcon::GetBatteryIcon(batteryPercent));
    auto isCharging = batteryController.IsCharging() || batteryController.IsPowerPresent();
    lv_label_set_text(batteryPlug, BatteryIcon::GetPlugIcon(isCharging));
  }

  bleState = bleController.IsConnected();
  if (bleState.IsUpdated()) {
    if(bleState.Get() == true) {
      lv_label_set_text(bleIcon, BleIcon::GetIcon(true));
    } else {
      lv_label_set_text(bleIcon, BleIcon::GetIcon(false));
    }
  }
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  //
 
  //
  currentDateTime = dateTimeController.CurrentDateTime();

  if(currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime-dp);
    auto yearMonthDay = date::year_month_day(dp);

    auto year = (int)yearMonthDay.year();
    auto month = static_cast<Pinetime::Controllers::DateTime::Months>((unsigned)yearMonthDay.month());
    auto day = (unsigned)yearMonthDay.day();
    auto dayOfWeek = static_cast<Pinetime::Controllers::DateTime::Days>(date::weekday(yearMonthDay).iso_encoding());

    auto hour = time.hours().count();
    auto minute = time.minutes().count();
    auto second = time.seconds().count();

    char minutesChar[3];
    sprintf(minutesChar, "%02d", minute);

    char hoursChar[3];
    sprintf(hoursChar, "%02d", hour);

    char timeStr[6];
    sprintf(timeStr, "%c%c\n%c%c", hoursChar[0],hoursChar[1],minutesChar[0], minutesChar[1]);

    if(hoursChar[0] != displayedChar[0] || hoursChar[1] != displayedChar[1] || minutesChar[0] != displayedChar[2] || minutesChar[1] != displayedChar[3]) {
      displayedChar[0] = hoursChar[0];
      displayedChar[1] = hoursChar[1];
      displayedChar[2] = minutesChar[0];
      displayedChar[3] = minutesChar[1];

      lv_label_set_text(label_time, timeStr);
    }

    if ((year != currentYear) || (month != currentMonth) || (dayOfWeek != currentDayOfWeek) || (day != currentDay)) {
      char dateStr[22];
      sprintf(dateStr, "%s %d,%s %d", DayOfWeekToString(dayOfWeek), day, MonthToString(month), year);
      lv_label_set_text(label_date, dateStr);


      currentYear = year;
      currentMonth = month;
      currentDayOfWeek = dayOfWeek;
      currentDay = day;
    }
  }

  // TODO heartbeat = heartBeatController.GetValue();
  if(heartbeat.IsUpdated()) {
    char heartbeatBuffer[4];
    sprintf(heartbeatBuffer, "%d", heartbeat.Get());
    lv_label_set_text(heartbeatValue, heartbeatBuffer);
    lv_obj_align(heartbeatIcon, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 5, -2);
    lv_obj_align(heartbeatValue, heartbeatIcon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_align(heartbeatBpm, heartbeatValue, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
  }

  // TODO stepCount = stepController.GetValue();
  if(stepCount.IsUpdated()) {
    char stepBuffer[5];
    sprintf(stepBuffer, "%lu", stepCount.Get());
    lv_label_set_text(stepValue, stepBuffer);
    lv_obj_align(stepValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, -5, -2);
    lv_obj_align(stepIcon, stepValue, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  }

  return running;
}

const char *Clock::MonthToString(Pinetime::Controllers::DateTime::Months month) {
  return Clock::MonthsString[static_cast<uint8_t>(month)];
}

const char *Clock::DayOfWeekToString(Pinetime::Controllers::DateTime::Days dayOfWeek) {
  return Clock::DaysString[static_cast<uint8_t>(dayOfWeek)];
}

char const *Clock::DaysString[] = {
        "",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat",
        "Sun"
};

char const *Clock::MonthsString[] = {
        "",
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
};

void Clock::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {
  if(obj == backgroundLabel) {
    if (event == LV_EVENT_CLICKED) {

      running = false;
    }
  }
}

bool Clock::OnButtonPushed() {
  running = false;
  return false;
}
