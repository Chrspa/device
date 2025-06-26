#ifndef BLEPERIPHERAL_H
#define BLEPERIPHERAL_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BLEPeripheral {
public:
    BLEPeripheral(const std::string& deviceName,
                  const std::string& serviceUUID,
                  const std::string& charUUID);

    void begin();
    void sendData(const std::string& data);

private:
    std::string deviceName;
    std::string serviceUUID;
    std::string charUUID;

    BLEServer* pServer;
    BLEService* pService;
    BLECharacteristic* pCharacteristic;
    bool deviceConnected;

    class ServerCallbacks : public BLEServerCallbacks {
    public:
        ServerCallbacks(BLEPeripheral* parent) : parent(parent) {}
        void onConnect(BLEServer* pServer);
        void onDisconnect(BLEServer* pServer);
    private:
        BLEPeripheral* parent;
    };

    class CharacteristicCallbacks : public BLECharacteristicCallbacks {
    public:
        void onWrite(BLECharacteristic* pCharacteristic) override;
    };
};

#endif
