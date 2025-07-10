#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEService.h>
#include <BLEAdvertisedDevice.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define EPD_DIN    10
#define EPD_CLK    9
#define EPD_CS     8
#define EPD_DC     7
#define EPD_RST    6
#define EPD_BUSY   /*-1*/5

GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(
    GxEPD2_213_B72(SS, EPD_DC, EPD_RST, EPD_BUSY)
);

#define DEVICE_NAME "IDAC"


const char TEXT[] = "Hello world!";


class Callbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();
    Serial.print("Empfangen: ");
    Serial.println(value);
  }
};


void initBLEServer() {
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("12345678-1234-5678-1234-56789abcdef0");

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    "abcdefab-1234-5678-1234-56789abcdef0",
    BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new Callbacks());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE server started, waiting for clients.");
}

void setup() {
  Serial.begin(115200);
    delay(1000);
    Serial.println("Init BLE server...");
    initBLEServer();

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

    Serial.println("Setup done");
}

void loop() {
    Serial.println("Hello world!");
    delay(5000);
}
