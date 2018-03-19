#pragma once
#include<stdint.h>
#include<stdbool.h>
#include"ADEException.h"

#define MAX_DEVICE_NUM 256

class ADEDevice;
class FxModbus;

class DeviceManager
{
public:
	DeviceManager();
	~DeviceManager();

private:
	ADEDevice * * deviceList;
	uint8_t deviceCounter;
	int16_t deviceSecleted;  //The index of the device selected in deviceList equal to deviceID-1.
public:
	FxModbus * modbus;
public:
	bool initManager();
	bool updateDeciceList();
	uint8_t getDeviceCounter() const;
	bool selectDevice(uint8_t deviceID);
	bool enableADC() const;
	bool disableADC() const;
	bool readAllADCChannels(uint16_t* value) const;
	bool readOneADCChannel(uint16_t* value, uint8_t channel) const;
	bool readInputPins(uint8_t* pinsValue) const;
	bool writeOutputPins(uint8_t pinsValue) const;
	bool setModbusMode(uint8_t modbusMode);
	bool setRTUParameters();
	bool setTCPParameters();
		
};

