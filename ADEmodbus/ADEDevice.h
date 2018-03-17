#pragma once
#include<stdbool.h>
#include<stdint.h>
#include"DeviceManager.h"
#include"FxModbus.h"

class DIO;
class ADC;

class ADEDevice
{
public:
	ADEDevice(DeviceManager* manager);
	~ADEDevice();

private:
	uint8_t deviceID;
	DIO* dio;
	ADC* adc;
	DeviceManager* manager;
public:
	uint8_t getDeviceID() const;
	bool setDeviceID(uint8_t const deviceID);
	bool readAllADCChannels(uint16_t* values) const;
	bool readOneADCChannel(uint16_t* values, uint8_t channel) const;
	bool writeOutputPins(uint8_t pins) const;
	bool readInputPins(uint8_t *pins) const;
	uint8_t getADCSampleRange() const;
	bool setADCSampleRange(uint8_t range) const;
	bool enableADC() const;
	bool disableADC() const;
};

