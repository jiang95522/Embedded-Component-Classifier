/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_first_page_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_bg_color(guider_ui.screen_first_page_btn, lv_color_hex(0xff9a76), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_analysis_btn, lv_color_hex(0xfff5f1), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_add_btn, lv_color_hex(0xfff5f1), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_classify_btn, lv_color_hex(0xfff5f1), LV_PART_MAIN);
        lv_obj_add_flag(guider_ui.screen_category__tileview, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(guider_ui.screen_first_pagetileview, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void screen_classify_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_bg_color(guider_ui.screen_analysis_btn, lv_color_hex(0xfff5f1), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_add_btn, lv_color_hex(0xfff5f1), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_classify_btn, lv_color_hex(0xff9a76), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.screen_first_page_btn, lv_color_hex(0xfff4f0), LV_PART_MAIN);
        lv_obj_remove_flag(guider_ui.screen_category__tileview, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_first_pagetileview, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_first_page_btn, screen_first_page_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_classify_btn, screen_classify_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
