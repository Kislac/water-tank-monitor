// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank

#include "../ui.h"

void ui_WifiScanResult_screen_init(void)
{
    ui_WifiScanResult = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_WifiScanResult, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_row(ui_WifiScanResult, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_WifiScanResult, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container1 = lv_obj_create(ui_WifiScanResult);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 318);
    lv_obj_set_height(ui_Container1, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Container1, 1);
    lv_obj_set_y(ui_Container1, 22);
    lv_obj_remove_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Container1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Container1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Container1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Container1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Label1, "Wifi Scan list");
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_funcWifiScan = lv_button_create(ui_Container1);
    lv_obj_set_width(ui_funcWifiScan, 100);
    lv_obj_set_height(ui_funcWifiScan, 34);
    lv_obj_set_align(ui_funcWifiScan, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_funcWifiScan, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_funcWifiScan, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_funcWifiScan);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Scan Wifi");

    ui_btnback = lv_button_create(ui_Container1);
    lv_obj_set_width(ui_btnback, 100);
    lv_obj_set_height(ui_btnback, 34);
    lv_obj_set_align(ui_btnback, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_btnback, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnback, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label19 = lv_label_create(ui_btnback);
    lv_obj_set_width(ui_Label19, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label19, "Back");

    ui_PanelWifiList = lv_obj_create(ui_WifiScanResult);
    lv_obj_set_width(ui_PanelWifiList, 318);
    lv_obj_set_height(ui_PanelWifiList, 176);
    lv_obj_set_x(ui_PanelWifiList, 0);
    lv_obj_set_y(ui_PanelWifiList, 63);
    lv_obj_set_align(ui_PanelWifiList, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_PanelWifiList, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_PanelWifiList, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_radius(ui_PanelWifiList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelWifiList, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelWifiList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelWifiList, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_PanelWifiList, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelWifiList, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelWifiList, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelWifiList, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelWifiList, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_PanelWifiList, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_PanelWifiList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_PanelWifiList);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label3, "Press the \"Scan Wifi\" Button to Scan\nConnect only 2,4gHz WiFi!");

    ui_panelScanningWifi = lv_obj_create(ui_WifiScanResult);
    lv_obj_set_width(ui_panelScanningWifi, 282);
    lv_obj_set_height(ui_panelScanningWifi, 92);
    lv_obj_set_align(ui_panelScanningWifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_panelScanningWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_panelScanningWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label26 = lv_label_create(ui_panelScanningWifi);
    lv_obj_set_width(ui_Label26, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label26, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label26, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label26, "Scanning nearby Wifi's.\nPlease wait...");
    lv_obj_set_style_text_align(ui_Label26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_funcWifiScan, ui_event_funcWifiScan, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btnback, ui_event_btnback, LV_EVENT_ALL, NULL);

}
