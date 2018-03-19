#include "FxModbus.h"

FxModbus::FxModbus()
{
	this->mode = FXMODBUS_RTU;
	this->ctx = nullptr;
	this->tcpParameters = nullptr;
	this->rtuParameters = nullptr;
	this->slaveId = 0;//broadcast mode
}

FxModbus::~FxModbus()
{
}

MODBUS_MODE FxModbus::getModbusMode() const
{
	return this->mode;
}

bool FxModbus::setModbusMode(const MODBUS_MODE mode)
{
	if (mode == FXMODBUS_RTU || mode == FXMODBUS_TCP)
	{
		this->mode = mode;
		return true;
	}
	return false;;
}

bool FxModbus::setTCPParameters(TCPParameters* tcpParameters)
{
	if (nullptr == tcpParameters)
		return false;;
	this->tcpParameters = tcpParameters;
	return true;
}

bool FxModbus::setRTUParameters(RTUParameters* rtuParameters)
{
	if (nullptr == rtuParameters)
		return false;;
	this->rtuParameters = rtuParameters;
	return true;
}

bool FxModbus::createSession()
{
	if(this->ctx!=nullptr)
	{
		
	}

	if (this->mode == FXMODBUS_RTU && this->rtuParameters != nullptr)
	{
		this->ctx = modbus_new_rtu(
			this->rtuParameters->device,
			this->rtuParameters->baud,
			this->rtuParameters->parity,
			this->rtuParameters->data_bit,
			this->rtuParameters->stop_bit
		);
		if (ctx == nullptr)
		{
			return false;
		}
	}
	else if (this->mode == FXMODBUS_TCP && this->tcpParameters != nullptr)
	{
		this->ctx = modbus_new_tcp(
			this->tcpParameters->ip,
			this->tcpParameters->port
		);
		if (ctx == nullptr)
		{
			return false;
		}
	}
	else { return false; }
	return true;
}

bool FxModbus::scanSlave(uint8_t slaveId)
{
	//todo:comunicate with the slave, juge it exist or not 
	return false;
}

int FxModbus::readBits(int addr, int nb, uint8_t* dest) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_read_bits(this->ctx, addr, nb, dest);
}

int FxModbus::readInputBits(int addr, int nb, uint8_t* dest) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_read_input_bits(this->ctx, addr, nb, dest);
}

int FxModbus::readRegisters(int addr, int nb, uint16_t* dest) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_read_registers(this->ctx, addr, nb, dest);
}

int FxModbus::readInputRegisters(int addr, int nb, uint16_t* dest) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_read_input_registers(this->ctx, addr, nb, dest);
}

int FxModbus::writeBit(int coil_addr, int status) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_write_bit(this->ctx, coil_addr, status);
}

int FxModbus::writeRegister(int reg_addr, int value) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_write_register(this->ctx, reg_addr, value);
}

int FxModbus::writeBits(int addr, int nb, const uint8_t* data) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_write_bits(this->ctx, addr, nb, data);
}

int FxModbus::writeRegisters(int addr, int nb, const uint16_t* data) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_write_registers(this->ctx, addr, nb, data);
}

int FxModbus::maskWriteRegister(const int addr, const uint16_t and_mask, const uint16_t or_mask) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_mask_write_register(this->ctx, addr, and_mask, or_mask);
}

int FxModbus::writeAndReadRegisters(
	const int write_addr,
	const int write_nb,
	const uint16_t* src,
	const int read_addr,
	const int read_nb,
	uint16_t* dest) const
{
	if (this->ctx == nullptr)
		return -1;
	return modbus_write_and_read_registers(
		this->ctx,
		write_addr,
		write_nb,
		src,
		read_addr,
		read_nb,
		dest
	);
}
