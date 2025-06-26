#include "BLEPeripheral.h"
#include <Arduino.h>

BLEPeripheral::BLEPeripheral(const std::string& deviceName,
                             const std::string& serviceUUID,
                             const std::string& charUUID)
    : deviceName(deviceName),
      serviceUUID(serviceUUID),
      charUUID(charUUID),
      pServer(nullptr),
      pService(nullptr),
      pCharacteristic(nullptr),
      deviceConnected(false) {}

void BLEPeripheral::begin() {
    BLEDevice::init(deviceName);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks(this));

    pService = pServer->createService(serviceUUID);
    pCharacteristic = pService->createCharacteristic(
        charUUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    pCharacteristic->addDescriptor(new BLE2902());
    pCharacteristic->setCallbacks(new CharacteristicCallbacks());

    pCharacteristic->setValue("Hello BLE");
    pService->start();
    pServer->getAdvertising()->start();

    Serial.println("BLE Peripheral started, waiting for client...");
}

void BLEPeripheral::sendData(const std::string& data) {
    if (deviceConnected) {
        pCharacteristic->setValue(data);
        pCharacteristic->notify();
    }
}

void BLEPeripheral::ServerCallbacks::onConnect(BLEServer* pServer) {
    parent->deviceConnected = true;
    Serial.println("Device connected");
}

void BLEPeripheral::ServerCallbacks::onDisconnect(BLEServer* pServer) {
    parent->deviceConnected = false;
    Serial.println("Device disconnected");
}

void BLEPeripheral::CharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    Serial.print("Received: ");
    Serial.println(value.c_str());
}
