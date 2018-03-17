#include "DIO.h"

DIO::DIO(ADEDevice* owner)
{
	if (NULL == owner)
		throw ADEException("DIO:The owner is empty pointer.");
	this->inputPins = 0;
	this->outputPins = 0;
}

DIO::~DIO()
{
}

bool DIO::readInputPins(FxModbus * modbus, uint8_t * pins)
{
	return false;
}

bool DIO::writeOutputPins(FxModbus * modbus, uint8_t pins)
{
	return false;
}
