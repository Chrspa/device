#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

#define EPD_DIN    10
#define EPD_CLK    9
#define EPD_CS     8
#define EPD_DC     7
#define EPD_RST    6
#define EPD_BUSY   5

GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(
    GxEPD2_290(/*CS=*/ EPD_CS, /*DC=*/ EPD_DC, /*RST=*/ EPD_RST, /*BUSY=*/ EPD_BUSY));

void setup() {
    Serial.begin(115200);
    display.init();
    display.setRotation(1);
    display.setTextSize(1);
    display.setCursor(10, 10);
    display.println("Hallo, ePaper!");
    display.display();
}

void loop() {
}
