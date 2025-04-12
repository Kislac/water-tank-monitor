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







✅ Ajánlott kiosztás például:
Érpár	Szín	Jel
1	Zöld + Zöld/fehér	SDA + GND
2	Narancs + Narancs/fehér	SCL + GND
3	Kék + Kék/fehér	+5V + üres
4	Barna + Barna/fehér	opcionális: LED vagy más GPIO

Használj alacsonyabb I2C sebességet (pl. 100kHz)
Húzz fel erősebb pull-up ellenállásokat (pl. 2.2kΩ helyett 1.5kΩ)

Az I2C specifikáció szerint pull-up ellenállás kell SDA és SCL vonalra.

Hossz	Jelszint	Javasolt pull-up
< 1 m	3.3V	4.7kΩ – 10kΩ
5–6 m	3.3V	2.2kΩ – 3.3kΩ



📊 Példakapcsolás
lua
Copy
Edit
ESP32
  ├── SDA ---[2.2kΩ]---+--- SDA wire ---> VL53L1X & AHT10
  │                   |
  │                  3.3V
  └── SCL ---[2.2kΩ]---+--- SCL wire ---> VL53L1X & AHT10

VL53L1X & AHT10
  └── 3.3V ---||--- GND (100nF + 10µF párhuzamosan)


T568B kiosztás:
1. Narancs/Fehér    --> GND
2. Narancs          --> SCL
3. Zöld/Fehér       --> GND
4. Kék              --> +5
5. Kék/Fehér        --> Üres
6. Zöld             --> SCA
7. Barna/Fehér      --> Üres
8. Barna            --> Üres
