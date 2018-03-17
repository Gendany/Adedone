#pragma once
#include<stdint.h>
#include"ADEDevice.h"
#include"ADEException.h"
#include"FxModbus.h"

class DIO
{
public:
	DIO(ADEDevice* owner);
	~DIO();

private:
	ADEDevice * owner;
	uint8_t outputPins;
	uint8_t inputPins;
public:
	bool readInputPins(FxModbus* modbus, uint8_t* pins);
	bool writeOutputPins(FxModbus* modbus, uint8_t pins);
};



