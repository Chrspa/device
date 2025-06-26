#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "BLEperipheral.h"

#define EPD_DIN    10
#define EPD_CLK    9
#define EPD_CS     8
#define EPD_DC     7
#define EPD_RST    6
#define EPD_BUSY   /*-1*/5

GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(
    GxEPD2_213_B72(SS, EPD_DC, EPD_RST, EPD_BUSY)
);

#if DEVICE_XIAO_S3
#define BOARD_NAME "XIAO S3"
#elif DEVICE_XIAO_S3
#define BOARD_NAME "XIAO C3"
#else
#define BOARD_NAME "Unbekanntes Board"
#endif


BLEPeripheral ble(BOARD_NAME,
                  "4fafc201-1fb5-459e-8fcc-c5c9c331914b",
                  "beb5483e-36e1-4688-b7f5-ea07361b26a8");


const char TEXT[] = "Hello world!";

void setup() {
    Serial.begin(115200);
    delay(1000);
    // Serial.println("Init bluetooth server...");
    // ble.begin();

    Serial.println("Init display...");

    /*display.init();
    display.setRotation(1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds(TEXT, 0, 0, &tbx, &tby, &tbw, &tbh);
    // center the bounding box by transposition of the origin:
    uint16_t x = ((display.width() - tbw) / 2) - tbx;
    uint16_t y = ((display.height() - tbh) / 2) - tby;
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y);
        display.print(TEXT);
    }
    while (display.nextPage());*/

    Serial.println("Done");
}

void loop() {
    // ble.sendData("Ping from XIAO");
    Serial.println("Hello world!");
    delay(1000);
}
