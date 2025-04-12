// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: WaterTank

#include "../ui.h"

void ui_MQTTSettings_screen_init(void)
{
    ui_MQTTSettings = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_MQTTSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TopInfoBar = lv_obj_create(ui_MQTTSettings);
    lv_obj_remove_style_all(ui_TopInfoBar);
    lv_obj_set_width(ui_TopInfoBar, 318);
    lv_obj_set_height(ui_TopInfoBar, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_TopInfoBar, 1);
    lv_obj_set_y(ui_TopInfoBar, 1);
    lv_obj_remove_flag(ui_TopInfoBar, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_TopInfoBar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TopInfoBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TopInfoBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Spinner1 = lv_spinner_create(ui_TopInfoBar);
    //lv_spinner_set_anim_params(ui_Spinner1, 1000, 90);
    lv_obj_set_width(ui_Spinner1, 20);
    lv_obj_set_height(ui_Spinner1, 20);
    lv_obj_set_align(ui_Spinner1, LV_ALIGN_RIGHT_MID);
    lv_obj_remove_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_Spinner1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_Spinner1, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_imWifiConnected1 = lv_image_create(ui_TopInfoBar);
    lv_image_set_src(ui_imWifiConnected1, &ui_img_1628538605);
    lv_obj_set_width(ui_imWifiConnected1, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_height(ui_imWifiConnected1, LV_SIZE_CONTENT);    /// 20
    lv_obj_set_align(ui_imWifiConnected1, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_imWifiConnected1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_imWifiConnected1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imWifiDisconnected1 = lv_image_create(ui_TopInfoBar);
    lv_image_set_src(ui_imWifiDisconnected1, &ui_img_1718934963);
    lv_obj_set_width(ui_imWifiDisconnected1, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_height(ui_imWifiDisconnected1, LV_SIZE_CONTENT);    /// 20
    lv_obj_set_align(ui_imWifiDisconnected1, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_imWifiDisconnected1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_imWifiDisconnected1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imInternetOK1 = lv_image_create(ui_TopInfoBar);
    lv_image_set_src(ui_imInternetOK1, &ui_img_communicator_png);
    lv_obj_set_width(ui_imInternetOK1, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_height(ui_imInternetOK1, LV_SIZE_CONTENT);    /// 20
    lv_obj_set_x(ui_imInternetOK1, 20);
    lv_obj_set_y(ui_imInternetOK1, 0);
    lv_obj_set_align(ui_imInternetOK1, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_imInternetOK1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_imInternetOK1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imInternetNOK1 = lv_image_create(ui_TopInfoBar);
    lv_image_set_src(ui_imInternetNOK1, &ui_img_478874422);
    lv_obj_set_width(ui_imInternetNOK1, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_height(ui_imInternetNOK1, LV_SIZE_CONTENT);    /// 20
    lv_obj_set_x(ui_imInternetNOK1, 20);
    lv_obj_set_y(ui_imInternetNOK1, 0);
    lv_obj_set_align(ui_imInternetNOK1, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_imInternetNOK1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_imInternetNOK1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ContMQTTServer = lv_obj_create(ui_MQTTSettings);
    lv_obj_remove_style_all(ui_ContMQTTServer);
    lv_obj_set_width(ui_ContMQTTServer, 318);
    lv_obj_set_height(ui_ContMQTTServer, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_ContMQTTServer, 1);
    lv_obj_set_y(ui_ContMQTTServer, 22);
    lv_obj_remove_flag(ui_ContMQTTServer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContMQTTServer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContMQTTServer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContMQTTServer, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMQTTlbl = lv_label_create(ui_ContMQTTServer);
    lv_obj_set_width(ui_lblMQTTlbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblMQTTlbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblMQTTlbl, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_lblMQTTlbl, "MQTT Server");

    ui_TextAreaMQTTServer = lv_textarea_create(ui_ContMQTTServer);
    lv_obj_set_width(ui_TextAreaMQTTServer, 150);
    lv_obj_set_height(ui_TextAreaMQTTServer, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_TextAreaMQTTServer, -15);
    lv_obj_set_y(ui_TextAreaMQTTServer, 0);
    lv_obj_set_align(ui_TextAreaMQTTServer, LV_ALIGN_RIGHT_MID);
    if("0123456789.:" == "") lv_textarea_set_accepted_chars(ui_TextAreaMQTTServer, NULL);
    else lv_textarea_set_accepted_chars(ui_TextAreaMQTTServer, "0123456789.:");
    lv_textarea_set_placeholder_text(ui_TextAreaMQTTServer, "192.168.0.100");
    lv_textarea_set_one_line(ui_TextAreaMQTTServer, true);
    lv_obj_remove_flag(ui_TextAreaMQTTServer,
                       LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                       LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_TextAreaMQTTServer, LV_SCROLLBAR_MODE_OFF);



    ui_ContMQTTUser = lv_obj_create(ui_MQTTSettings);
    lv_obj_remove_style_all(ui_ContMQTTUser);
    lv_obj_set_width(ui_ContMQTTUser, 318);
    lv_obj_set_height(ui_ContMQTTUser, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_ContMQTTUser, 1);
    lv_obj_set_y(ui_ContMQTTUser, 59);
    lv_obj_remove_flag(ui_ContMQTTUser, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContMQTTUser, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContMQTTUser, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContMQTTUser, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMQTTuser = lv_label_create(ui_ContMQTTUser);
    lv_obj_set_width(ui_lblMQTTuser, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblMQTTuser, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblMQTTuser, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_lblMQTTuser, "MQTT User");

    ui_TextAreaMQTTuser = lv_textarea_create(ui_ContMQTTUser);
    lv_obj_set_width(ui_TextAreaMQTTuser, 150);
    lv_obj_set_height(ui_TextAreaMQTTuser, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_TextAreaMQTTuser, -15);
    lv_obj_set_y(ui_TextAreaMQTTuser, 0);
    lv_obj_set_align(ui_TextAreaMQTTuser, LV_ALIGN_RIGHT_MID);
    lv_textarea_set_placeholder_text(ui_TextAreaMQTTuser, "User");
    lv_textarea_set_one_line(ui_TextAreaMQTTuser, true);
    lv_obj_remove_flag(ui_TextAreaMQTTuser,
                       LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                       LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_TextAreaMQTTuser, LV_SCROLLBAR_MODE_OFF);



    ui_ContMQTTPassword = lv_obj_create(ui_MQTTSettings);
    lv_obj_remove_style_all(ui_ContMQTTPassword);
    lv_obj_set_width(ui_ContMQTTPassword, 318);
    lv_obj_set_height(ui_ContMQTTPassword, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_ContMQTTPassword, 1);
    lv_obj_set_y(ui_ContMQTTPassword, 96);
    lv_obj_remove_flag(ui_ContMQTTPassword, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContMQTTPassword, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContMQTTPassword, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContMQTTPassword, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMQTTPassword = lv_label_create(ui_ContMQTTPassword);
    lv_obj_set_width(ui_lblMQTTPassword, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblMQTTPassword, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblMQTTPassword, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_lblMQTTPassword, "MQTT Password");

    ui_TextAreaMQTTPassword = lv_textarea_create(ui_ContMQTTPassword);
    lv_obj_set_width(ui_TextAreaMQTTPassword, 150);
    lv_obj_set_height(ui_TextAreaMQTTPassword, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_TextAreaMQTTPassword, -15);
    lv_obj_set_y(ui_TextAreaMQTTPassword, 0);
    lv_obj_set_align(ui_TextAreaMQTTPassword, LV_ALIGN_RIGHT_MID);
    lv_textarea_set_placeholder_text(ui_TextAreaMQTTPassword, "Password");
    lv_textarea_set_one_line(ui_TextAreaMQTTPassword, true);
    lv_obj_remove_flag(ui_TextAreaMQTTPassword,
                       LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                       LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_TextAreaMQTTPassword, LV_SCROLLBAR_MODE_OFF);



    ui_Back = lv_button_create(ui_MQTTSettings);
    lv_obj_set_width(ui_Back, 100);
    lv_obj_set_height(ui_Back, 30);
    lv_obj_set_x(ui_Back, 100);
    lv_obj_set_y(ui_Back, 88);
    lv_obj_set_align(ui_Back, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Back, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Back, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblBack = lv_label_create(ui_Back);
    lv_obj_set_width(ui_lblBack, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblBack, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblBack, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBack, "Back");

    ui_Save = lv_button_create(ui_MQTTSettings);
    lv_obj_set_width(ui_Save, 100);
    lv_obj_set_height(ui_Save, 30);
    lv_obj_set_x(ui_Save, -92);
    lv_obj_set_y(ui_Save, 45);
    lv_obj_set_align(ui_Save, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Save, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Save, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblBack1 = lv_label_create(ui_Save);
    lv_obj_set_width(ui_lblBack1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblBack1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblBack1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBack1, "Save");

    ui_Forget = lv_button_create(ui_MQTTSettings);
    lv_obj_set_width(ui_Forget, 100);
    lv_obj_set_height(ui_Forget, 30);
    lv_obj_set_x(ui_Forget, 99);
    lv_obj_set_y(ui_Forget, 42);
    lv_obj_set_align(ui_Forget, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Forget, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Forget, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblBack2 = lv_label_create(ui_Forget);
    lv_obj_set_width(ui_lblBack2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblBack2, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_align(ui_lblBack2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBack2, "Forget");

    ui_Connect = lv_button_create(ui_MQTTSettings);
    lv_obj_set_width(ui_Connect, 100);
    lv_obj_set_height(ui_Connect, 30);
    lv_obj_set_x(ui_Connect, -90);
    lv_obj_set_y(ui_Connect, 90);
    lv_obj_set_align(ui_Connect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Connect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_Connect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblBack3 = lv_label_create(ui_Connect);
    lv_obj_set_width(ui_lblBack3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblBack3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblBack3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBack3, "Connect");

    ui_KeyboardMQTT = lv_keyboard_create(ui_MQTTSettings);
    lv_obj_set_width(ui_KeyboardMQTT, 320);
    lv_obj_set_height(ui_KeyboardMQTT, 103);
    lv_obj_set_align(ui_KeyboardMQTT, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_KeyboardMQTT, LV_OBJ_FLAG_HIDDEN);     /// Flags

    lv_obj_add_event_cb(ui_TextAreaMQTTServer, ui_event_TextAreaMQTTServer, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaMQTTuser, ui_event_TextAreaMQTTuser, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaMQTTPassword, ui_event_TextAreaMQTTPassword, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Back, ui_event_Back, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Save, ui_event_Save, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Forget, ui_event_Forget, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_KeyboardMQTT, ui_event_KeyboardMQTT, LV_EVENT_ALL, NULL);

}
