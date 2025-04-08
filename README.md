# lidar-water-tank-monitor
esp32 based (CYB (esp32-2432S032C) lidar-water-tank-monitor sending to HA via MQTT



follow this steps: https://github.com/rzeldent/esp32-smartdisplay


SquareLine_Studio_Windows_v1_4_2


clone this: https://github.com/rzeldent/platformio-espressif32-sunton
copy the boards definition to the <home>/.platformio\platforms\espressif32\boards
create new projects with  esp32-2432S032C board







SquarlineStudio Settings
New project:
- Major LVGL version: 9.1
- Visual Studio for development on windows PC (v2.0.1)
- Res: 320x240
- ColorDepth 16Bit
- LVGL version 9.1.0
Project Export Root: D:\GIT\water-tank-monitor
UI Files Export Path: D:\GIT\water-tank-monitor\src\ui
LVGL Include Path: lvgl.h
Call functions export file: don't export




pf.ini file:
[env:esp32-2432S032C]
platform = espressif32
board = esp32-2432S032C
framework = arduino
monitor_speed = 115200
build_flags = 
    -Ofast
    -Wall
    -DCORE_DEBUG_LEVEL=ARDUHAL_LOG_LEVEL_INFO
    -D LV_CONF_PATH="D:\GIT\water-tank-monitor\include\lv_conf.h"
lib_deps = 
    https://github.com/rzeldent/esp32-smartdisplay



copy this file
D:\GIT\water-tank-monitor\.pio\libdeps\esp32-2432S032C\lvgl\lv_conf_template.h
to D:\GIT\water-tank-monitor\include and rename to 
provide lvgl.h config path to pf.ini --> -D LV_CONF_PATH="D:\GIT\water-tank-monitor\include\lv_conf.h"

add lvgl/lvgl@^9.2.2 library to the project