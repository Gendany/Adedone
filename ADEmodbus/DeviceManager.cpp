#include<string>
#include "DeviceManager.h"
#include "ADEDevice.h"
#include "FxModbus.h"


DeviceManager::DeviceManager()
{
	this->deviceCounter = 0;
	this->deviceList = static_cast<ADEDevice**>(malloc(sizeof(this) * MAX_DEVICE_NUM));
	memset(this->deviceList, NULL, sizeof(this)*MAX_DEVICE_NUM);
	this->deviceSecleted = -1; //None device seleted.
	this->modbus = new FxModbus();

}

DeviceManager::~DeviceManager()
{
	for (int i = 0; i < MAX_DEVICE_NUM; i++) {
		if (this->deviceList[i] != nullptr)
			delete this->deviceList[i];
	}
	free(this->deviceList);
}

bool DeviceManager::updateDeciceList()
{
	//todo:scan all slave via Fxmodbus.
	return false;
}


/**
 * \brief get the divices number.
 * \return the number of devices.
 */
uint8_t DeviceManager::getDeviceCounter() const
{
	return this->deviceCounter;
}

/**
 * \brief 
 * \param deviceID ID of the device want connect to.
 * \return true set succeed;false set failed.
 */
bool DeviceManager::selectDevice(const uint8_t deviceID)
{
	if (deviceID <= 0 || deviceID > this->deviceCounter) 
		return false;
	this->deviceSecleted = deviceID - 1;
	return true;
}

bool DeviceManager::enableADC() const
{
	if (deviceSecleted < 0)
		return false;
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->enableADC();
}

bool DeviceManager::disableADC() const
{
	if (deviceSecleted < 0)
		return false;	
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->disableADC();
}

bool DeviceManager::readAllADCChannels(uint16_t * value) const
{
	if (deviceSecleted < 0 || value == nullptr)
		return false;
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->readAllADCChannels(value);
}

bool DeviceManager::readOneADCChannel(uint16_t * value, const uint8_t channel) const
{
	if (deviceSecleted < 0 || value == nullptr || channel < 1 || channel >8 )
		return false;
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->readOneADCChannel(value, channel);
}

bool DeviceManager::readInputPins(uint8_t * pinsValue) const
{
	if (deviceSecleted < 0 || pinsValue == nullptr)
		return false;
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->readInputPins(pinsValue);
}

/**
 * \brief Set the deviceSelected's pins as pinsValue 
 * \param pinsValue: the status of output pins. Each bit of pinsValue map to a pin.
 * \return true: set succeed. false:failed.
 */
bool DeviceManager::writeOutputPins(const uint8_t pinsValue) const
{
	if (deviceSecleted < 0 )
		return false;
	ADEDevice* device = this->deviceList[this->deviceSecleted];
	return device->writeOutputPins(pinsValue);
}

bool DeviceManager::setModbusMode(uint8_t modbusMode)
{
	//todo: set the modbus work mode RTU or TCP.
	return false;
}


bool DeviceManager::setRTUParameters()
{
	return false;
}

bool DeviceManager::setTCPParameters()
{
	return false;
}
