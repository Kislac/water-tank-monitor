SET(SOURCES screens/ui_Main_Screen.c
    screens/ui_Wifi_Settings.c
    screens/ui_WifiScanResult.c
    screens/ui_ConnectToWifi.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_1628538605.c
    images/ui_img_1718934963.c
    images/ui_img_communicator_png.c
    images/ui_img_478874422.c)

add_library(ui ${SOURCES})
