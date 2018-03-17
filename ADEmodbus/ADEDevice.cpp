#include "ADEDevice.h"
#include "ADC.h"
#include "DIO.h"

ADEDevice::ADEDevice(DeviceManager* manager)
{
	if (nullptr == manager)
		throw ADEException("ADEDevice:manager pointer is null.");
	deviceID = 0;
	this->dio = new DIO(this);
	this->adc = new ADC(this);
}

ADEDevice::~ADEDevice()
{
	delete this->adc;
	delete this->dio;
}

uint8_t ADEDevice::getDeviceID() const
{
	return this->deviceID;
}

bool ADEDevice::setDeviceID(uint8_t const deviceID)
{
	if (deviceID < 1 || deviceID > MAX_DEVICE_NUM)
		return  false;
	this->deviceID = deviceID;
	return true;
}

bool ADEDevice::readAllADCChannels(uint16_t* values) const
{
	if(values == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->readAllChannels(modbus,values);
}

bool ADEDevice::readOneADCChannel(uint16_t * values, const uint8_t channel) const
{
	if(values == nullptr||channel<1||channel>8)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->readOneChannel(modbus, values, channel);
}

bool ADEDevice::writeOutputPins(const uint8_t pinsValue) const
{
	FxModbus* modbus = this->manager->modbus;
	return this->dio->writeOutputPins(modbus, pinsValue);
	return false;
}

bool ADEDevice::readInputPins(uint8_t * pinsValue) const
{
	if (pinsValue == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->dio->readInputPins(modbus, pinsValue);	
}

uint8_t ADEDevice::getADCSampleRange() const
{

	FxModbus* modbus = this->manager->modbus;
	return this->adc->getSampleRange(modbus);
}

bool ADEDevice::setADCSampleRange(uint8_t range) const
{
	if (range<RANGE5 || range>RANGE10)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->setSampleRange(modbus,static_cast<SAMPLE_RANGE>(range));
}

bool ADEDevice::enableADC() const
{
	FxModbus* modbus = this->manager->modbus;
	return this->adc->enableADC(modbus);
}

bool ADEDevice::disableADC() const
{
	FxModbus* modbus = this->manager->modbus;
	return this->adc->disableADC(modbus);
}
