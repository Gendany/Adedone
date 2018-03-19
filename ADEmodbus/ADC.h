#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string>

#include"ADEDevice.h"
#include"FxModbus.h"
#include"ADEException.h"
#define CHANNEL_NUM 8

enum SAMPLE_RANGE
{
	RANGE5,			//ADC sample range [-5, 5]
	RANGE10,		//ADC sample range [-10, 10] 
	INVALID_RANGE
};
class ADC
{
public:
	ADC(ADEDevice * owner);
	~ADC();

private:
	uint16_t channels[CHANNEL_NUM];
	ADEDevice* owner;
	uint8_t sampleRange;
	bool isEnabled;
public:
	bool enableADC(FxModbus* modbus);
	bool disableADC(FxModbus* modbus);
	bool readAllChannels(FxModbus* modbus, uint16_t* channelsValue);
	bool readOneChannel(FxModbus* modbus, uint16_t* channelValue, uint8_t channelNum);
	bool setSampleRange(FxModbus* modbus,SAMPLE_RANGE range);
	SAMPLE_RANGE getSampleRange(FxModbus* modbus);
};

