#pragma once
#include "modbus.h"
enum MODBUS_MODE
{
	FXMODBUS_RTU,
	FXMODBUS_TCP
};

struct RTUParameters
{
	char *device;	//device name eg: 'COM1'
	int baud;		//baudrate
	char parity;	//'N' no ; 'E', EVEN;
	int data_bit;
	int stop_bit;	
};
struct TCPParameters
{
	char *ip;		//ip address
	int port;		//port	
};


class FxModbus
{
public:
	FxModbus();
	~FxModbus();

private:
	MODBUS_MODE mode;
	TCPParameters* tcpParameters;
	RTUParameters* rtuParameters;
	modbus_t* ctx;
	uint8_t slaveId;
public:
	uint8_t getSlaveId() const
	{
		return this->slaveId;
	}
	void setSlaveId(const uint8_t slave_id)
	{
		this->slaveId = slave_id;
	}

	MODBUS_MODE getModbusMode() const;
	bool setModbusMode(MODBUS_MODE mode);
	bool setTCPParameters(TCPParameters* tcpParameters);
	bool setRTUParameters(RTUParameters* rtuParameters);
	bool createSession();

	bool scanSlave(uint8_t slaveId);   
	int readBits(int addr, int nb, uint8_t* dest) const;
	int readInputBits(int addr, int nb, uint8_t* dest) const;
	int readRegisters(int addr, int nb, uint16_t* dest) const;
	int readInputRegisters(int addr, int nb, uint16_t* dest) const;
	int writeBit(int coil_addr, int status) const;
	int writeRegister(int reg_addr, int value) const;
	int writeBits(int addr, int nb, const uint8_t *data) const;
	int writeRegisters(int addr, int nb, const uint16_t *data) const;
	int maskWriteRegister(int addr, uint16_t and_mask, uint16_t or_mask) const;
	int writeAndReadRegisters(int write_addr, int write_nb,
		const uint16_t *src, int read_addr, int read_nb,
		uint16_t *dest) const;


};

