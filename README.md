# QueSera

```
Que será, será
Whatever will be, will be
The future's not ours to see
Que será, será
What will be, will be
```
--- The song "Que Sera, Sera" by Doris Day, 1956

## Intro

The e-ink smart calendar that I've been too busy and nearly forgot to continue working on.

The original project is here: [https://github.com/huming2207/Hindle](https://github.com/huming2207/Hindle).

Now I have just finished my major assignments in this semester. 
So I finally got some time in the SWOT VAC week to deal with the stuff I have planned to do earlier this year.

Compared to the previous project, this new project aims to use more ESP-IDF APIs directly, instead of using Arduino. Bacause:

- PlatformIO may leads to some strange issues with indexing and it may causes false alarms on missing headers.
- ESP-IDF has official built-in CMake support, so I can code with CLion now.
- Writing the "real" C++ code instead of Arduino-style C++ code is more challenging. But it helps me practise more C++ anyway.
- May receive potential performance improvements without Arduino.

## Credit

U8g2 ESP-IDF HAL by Neil Kolban: [https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2](https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2)