SET(SOURCES screens/ui_Main_Screen.c
    screens/ui_Wifi_Settings.c
    screens/ui_WifiScanResult.c
    screens/ui_ConnectToWifi.c
    screens/ui_MQTTSettings.c
    ui_theme_manager.cpp
    ui_themes.cpp
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_wifiinternetok_png.c
    images/ui_img_wifidisconnected_png.c
    images/ui_img_wificonnectednointernet_png.c
    fonts/ui_font_DejaVuSansMono14.c
    fonts/ui_font_MontserratRegular14ExtASCI.c
    fonts/ui_font_MontserratRegular14ExtASCIBold.c
    fonts/ui_font_MontserratRegular14ExtASCIMedium.c)

add_library(ui ${SOURCES})
