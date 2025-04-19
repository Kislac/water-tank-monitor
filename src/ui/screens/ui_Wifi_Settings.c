// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank

#include "../ui.h"

void ui_Wifi_Settings_screen_init(void)
{
    ui_Wifi_Settings = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Wifi_Settings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Wifi_Settings, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_BackGround);
    ui_object_set_themeable_style_property(ui_Wifi_Settings, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_BackGround);

    ui_TopInfoBar2 = lv_obj_create(ui_Wifi_Settings);
    lv_obj_remove_style_all(ui_TopInfoBar2);
    lv_obj_set_width(ui_TopInfoBar2, 318);
    lv_obj_set_height(ui_TopInfoBar2, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_TopInfoBar2, 1);
    lv_obj_set_y(ui_TopInfoBar2, 1);
    lv_obj_remove_flag(ui_TopInfoBar2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_TopInfoBar2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_BackGround);
    ui_object_set_themeable_style_property(ui_TopInfoBar2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_BackGround);
    ui_object_set_themeable_style_property(ui_TopInfoBar2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                           _ui_theme_color_Border);
    ui_object_set_themeable_style_property(ui_TopInfoBar2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                           _ui_theme_alpha_Border);
    lv_obj_set_style_border_width(ui_TopInfoBar2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Spinner4 = lv_spinner_create(ui_TopInfoBar2);
    //lv_spinner_set_anim_params(ui_Spinner4, 1000, 90);
    lv_obj_set_width(ui_Spinner4, 20);
    lv_obj_set_height(ui_Spinner4, 20);
    lv_obj_set_align(ui_Spinner4, LV_ALIGN_RIGHT_MID);
    lv_obj_remove_flag(ui_Spinner4, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_Spinner4, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_Spinner4, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Container3 = lv_obj_create(ui_Wifi_Settings);
    lv_obj_remove_style_all(ui_Container3);
    lv_obj_set_width(ui_Container3, 318);
    lv_obj_set_height(ui_Container3, 146);
    lv_obj_set_x(ui_Container3, 1);
    lv_obj_set_y(ui_Container3, 49);
    lv_obj_set_flex_flow(ui_Container3, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Container3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(ui_Container3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_BackGround);
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_BackGround);
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                           _ui_theme_color_Border);
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                           _ui_theme_alpha_Border);
    lv_obj_set_style_border_width(ui_Container3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Container3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container9 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container9);
    lv_obj_set_width(ui_Container9, lv_pct(100));
    lv_obj_set_height(ui_Container9, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Container9, 0);
    lv_obj_set_y(ui_Container9, -1);
    lv_obj_set_align(ui_Container9, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container9, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container9, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container9, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container9, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container9, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4 = lv_label_create(ui_Container9);
    lv_obj_set_width(ui_Label4, lv_pct(30));
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label4, "Wifi Status: ");
    ui_object_set_themeable_style_property(ui_Label4, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label4, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiStatus = lv_label_create(ui_Container9);
    lv_obj_set_width(ui_lblWifiStatus, lv_pct(70));
    lv_obj_set_height(ui_lblWifiStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiStatus, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiStatus, "-");
    ui_object_set_themeable_style_property(ui_lblWifiStatus, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiStatus, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiStatus, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container10 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container10);
    lv_obj_set_width(ui_Container10, lv_pct(100));
    lv_obj_set_height(ui_Container10, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container10, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container10, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label15 = lv_label_create(ui_Container10);
    lv_obj_set_width(ui_Label15, lv_pct(30));
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label15, "Wifi SSID: ");
    ui_object_set_themeable_style_property(ui_Label15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiSSID = lv_label_create(ui_Container10);
    lv_obj_set_width(ui_lblWifiSSID, lv_pct(70));
    lv_obj_set_height(ui_lblWifiSSID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiSSID, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiSSID, "-");
    ui_object_set_themeable_style_property(ui_lblWifiSSID, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiSSID, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiSSID, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container11 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container11);
    lv_obj_set_width(ui_Container11, lv_pct(100));
    lv_obj_set_height(ui_Container11, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container11, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label17 = lv_label_create(ui_Container11);
    lv_obj_set_width(ui_Label17, lv_pct(30));
    lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label17, "IP Address: ");
    ui_object_set_themeable_style_property(ui_Label17, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label17, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiIP = lv_label_create(ui_Container11);
    lv_obj_set_width(ui_lblWifiIP, lv_pct(70));
    lv_obj_set_height(ui_lblWifiIP, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiIP, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiIP, "-");
    ui_object_set_themeable_style_property(ui_lblWifiIP, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiIP, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiIP, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container12 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container12);
    lv_obj_set_width(ui_Container12, lv_pct(100));
    lv_obj_set_height(ui_Container12, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container12, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container12, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container12, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container12, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container12, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container12, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label20 = lv_label_create(ui_Container12);
    lv_obj_set_width(ui_Label20, lv_pct(30));
    lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label20, "RSSI: ");
    ui_object_set_themeable_style_property(ui_Label20, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label20, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiRSSI = lv_label_create(ui_Container12);
    lv_obj_set_width(ui_lblWifiRSSI, lv_pct(70));
    lv_obj_set_height(ui_lblWifiRSSI, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiRSSI, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiRSSI, "-");
    ui_object_set_themeable_style_property(ui_lblWifiRSSI, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiRSSI, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiRSSI, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container13 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container13);
    lv_obj_set_width(ui_Container13, lv_pct(100));
    lv_obj_set_height(ui_Container13, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container13, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container13, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container13, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container13, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container13, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container13, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label22 = lv_label_create(ui_Container13);
    lv_obj_set_width(ui_Label22, lv_pct(30));
    lv_obj_set_height(ui_Label22, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label22, "Channel:");
    ui_object_set_themeable_style_property(ui_Label22, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label22, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiChannel = lv_label_create(ui_Container13);
    lv_obj_set_width(ui_lblWifiChannel, lv_pct(70));
    lv_obj_set_height(ui_lblWifiChannel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiChannel, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiChannel, "-");
    ui_object_set_themeable_style_property(ui_lblWifiChannel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiChannel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiChannel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container14 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container14);
    lv_obj_set_width(ui_Container14, lv_pct(100));
    lv_obj_set_height(ui_Container14, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container14, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container14, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label24 = lv_label_create(ui_Container14);
    lv_obj_set_width(ui_Label24, lv_pct(30));
    lv_obj_set_height(ui_Label24, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label24, "Security:");
    ui_object_set_themeable_style_property(ui_Label24, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label24, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblWifiSecurity = lv_label_create(ui_Container14);
    lv_obj_set_width(ui_lblWifiSecurity, lv_pct(70));
    lv_obj_set_height(ui_lblWifiSecurity, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblWifiSecurity, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblWifiSecurity, "-");
    ui_object_set_themeable_style_property(ui_lblWifiSecurity, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblWifiSecurity, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblWifiSecurity, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container16 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container16);
    lv_obj_set_width(ui_Container16, lv_pct(100));
    lv_obj_set_height(ui_Container16, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Container16, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Container16, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Container16, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container16, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container16, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container16, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label27 = lv_label_create(ui_Container16);
    lv_obj_set_width(ui_Label27, lv_pct(30));
    lv_obj_set_height(ui_Label27, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label27, "Time:");
    ui_object_set_themeable_style_property(ui_Label27, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label27, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_lblTime = lv_label_create(ui_Container16);
    lv_obj_set_width(ui_lblTime, lv_pct(50));
    lv_obj_set_height(ui_lblTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_y(ui_lblTime, 0);
    lv_obj_set_x(ui_lblTime, lv_pct(30));
    lv_label_set_text(ui_lblTime, "-");
    ui_object_set_themeable_style_property(ui_lblTime, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblTime, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblTime, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblTimeZone = lv_label_create(ui_Container16);
    lv_obj_set_width(ui_lblTimeZone, lv_pct(20));
    lv_obj_set_height(ui_lblTimeZone, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblTimeZone, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_lblTimeZone, "-");
    ui_object_set_themeable_style_property(ui_lblTimeZone, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_lblTimeZone, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);
    lv_obj_set_style_text_align(ui_lblTimeZone, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnScanWifi = lv_button_create(ui_Wifi_Settings);
    lv_obj_set_width(ui_btnScanWifi, 100);
    lv_obj_set_height(ui_btnScanWifi, 34);
    lv_obj_set_x(ui_btnScanWifi, 0);
    lv_obj_set_y(ui_btnScanWifi, 96);
    lv_obj_set_align(ui_btnScanWifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnScanWifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnScanWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label11 = lv_label_create(ui_btnScanWifi);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label11, "Scan WiFi");

    ui_Container15 = lv_obj_create(ui_Wifi_Settings);
    lv_obj_remove_style_all(ui_Container15);
    lv_obj_set_width(ui_Container15, 318);
    lv_obj_set_height(ui_Container15, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Container15, 1);
    lv_obj_set_y(ui_Container15, 22);
    lv_obj_remove_flag(ui_Container15, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Container15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_BackGround);
    ui_object_set_themeable_style_property(ui_Container15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_BackGround);
    ui_object_set_themeable_style_property(ui_Container15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                           _ui_theme_color_Border);
    ui_object_set_themeable_style_property(ui_Container15, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                           _ui_theme_alpha_Border);
    lv_obj_set_style_border_width(ui_Container15, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Container15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Container15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Container15, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Container15, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label14 = lv_label_create(ui_Container15);
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label14, "Wifi Details");
    ui_object_set_themeable_style_property(ui_Label14, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_FontColor);
    ui_object_set_themeable_style_property(ui_Label14, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_FontColor);

    ui_btnForgetWifi = lv_button_create(ui_Wifi_Settings);
    lv_obj_set_width(ui_btnForgetWifi, 100);
    lv_obj_set_height(ui_btnForgetWifi, 34);
    lv_obj_set_x(ui_btnForgetWifi, 5);
    lv_obj_set_y(ui_btnForgetWifi, 96);
    lv_obj_set_align(ui_btnForgetWifi, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_btnForgetWifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnForgetWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label25 = lv_label_create(ui_btnForgetWifi);
    lv_obj_set_width(ui_Label25, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label25, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label25, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label25, "Forget WiFi");

    ui_btnBack = lv_button_create(ui_Wifi_Settings);
    lv_obj_set_width(ui_btnBack, 100);
    lv_obj_set_height(ui_btnBack, 34);
    lv_obj_set_x(ui_btnBack, -5);
    lv_obj_set_y(ui_btnBack, 96);
    lv_obj_set_align(ui_btnBack, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_btnBack, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnBack, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label28 = lv_label_create(ui_btnBack);
    lv_obj_set_width(ui_Label28, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label28, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label28, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label28, "Back");

    lv_obj_add_event_cb(ui_btnScanWifi, ui_event_btnScanWifi, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btnForgetWifi, ui_event_btnForgetWifi, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btnBack, ui_event_btnBack, LV_EVENT_ALL, NULL);

}
