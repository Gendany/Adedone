#include "ADEDevice.h"
#include "ADC.h"
#include "DIO.h"

ADEDevice::ADEDevice(DeviceManager* manager)
{
	if (nullptr == manager)
		throw ADEException("ADEDevice:manager pointer is null.");

	deviceID = 0;
	this->dio = nullptr;
	this->adc = nullptr;
	this->manager = manager;
}

ADEDevice::~ADEDevice()
{

}


bool ADEDevice::initDevice()
{
	if( this->dio==nullptr&&this->adc==nullptr)
	{
		this->dio = new DIO(this);
		if (this->dio == nullptr)
			return false;

		this->adc = new ADC(this);
		if (this->adc == nullptr)
		{
			delete this->dio;
			this->dio = nullptr;
			return false;
		}
	}
	return true;
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
	if (this->adc == nullptr)
		return false;

	if(values == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->readAllChannels(modbus,values);
}

bool ADEDevice::readOneADCChannel(uint16_t * values, const uint8_t channel) const
{
	if (this->adc == nullptr)
		return false;

	if(values == nullptr||channel<1||channel>8)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->readOneChannel(modbus, values, channel);
}

bool ADEDevice::writeOutputPins(const uint8_t pinsValue) const
{
	if (this->dio == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->dio->writeOutputPins(modbus, pinsValue);
}

bool ADEDevice::readInputPins(uint8_t * pinsValue) const
{
	if (this->dio == nullptr)
		return false;

	if (pinsValue == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->dio->readInputPins(modbus, pinsValue);	
}

uint8_t ADEDevice::getADCSampleRange() const
{
	if (this->adc == nullptr)
		return INVALID_RANGE;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->getSampleRange(modbus);
}

bool ADEDevice::setADCSampleRange(uint8_t range) const
{
	if (this->adc == nullptr)
		return false;
	if (range<RANGE5 || range>RANGE10)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->setSampleRange(modbus,static_cast<SAMPLE_RANGE>(range));
}

bool ADEDevice::enableADC() const
{
	if (this->adc == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->enableADC(modbus);
}

bool ADEDevice::disableADC() const
{
	if (this->adc == nullptr)
		return false;
	FxModbus* modbus = this->manager->modbus;
	return this->adc->disableADC(modbus);
}
