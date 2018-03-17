#include "ADC.h"

ADC::ADC(ADEDevice* owner)
{
	if (NULL == owner)
		throw ADEException("Owner is empty pointer.");
	this->owner = owner;
	memset(&channels, 0, sizeof(channels));
	sampleRange = RANGE5;
}

ADC::~ADC()
{

}

bool ADC::enableADC(FxModbus * modbus)
{
	return false;
}

bool ADC::disableADC(FxModbus * modbus)
{
	return false;
}

bool ADC::readAllChannels(FxModbus* modbus, uint16_t* channelsValue)
{
}

bool ADC::readOneChannel(FxModbus* modbus, uint16_t* channelValue, uint8_t channelNum)
{
}

bool ADC::setSampleRange(FxModbus * modbus, SAMPLE_RANGE range)
{
	return false;
}

SAMPLE_RANGE ADC::getSampleRange(FxModbus * modbus)
{
	return SAMPLE_RANGE();
}
