#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define EPD_DIN    10
#define EPD_CLK    9
#define EPD_CS     8
#define EPD_DC     7
#define EPD_RST    6
#define EPD_BUSY   /*-1*/5

GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(
    GxEPD2_290(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
);

const char TEXT[] = "Hello world!";

void setup() {
    Serial.begin(115200);
    Serial.println("Init display");

    display.init(115200, true, 2, false);
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
    while (display.nextPage());

    Serial.println("Done");
}

void loop() {

}
