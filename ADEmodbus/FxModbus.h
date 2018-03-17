#pragma once
#include "modbus.h"
enum MODBUS_MODE
{
	RTU,
	TCP
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
public:
	MODBUS_MODE getModbusMode();
	bool setModbusMode(MODBUS_MODE mode);
	bool setTCPParameters(TCPParameters* tcpParameters);
	bool setRTUParameters(RTUParameters* rtuParameters);
	bool scanSlave(uint8_t slaveId);

	int readBits(int addr, int nb, uint8_t* dest);
	int readInputBits(int addr, int nb, uint8_t* dest);
	int readRegisters(int addr, int nb, uint16_t* dest);
	int readInputRegisters(int addr, int nb, uint8_t* dest);
	int writeBit(int coil_addr, int status);
	int writeRegister(int reg_addr, int value);
	int writeBits(int addr, int nb, const uint8_t *data);
	int writeRegisters(int addr, int nb, const uint16_t *data);
	int maskWriteRegister(int addr, uint16_t and_mask, uint16_t or_mask);
	int writeAndReadRegisters(int write_addr, int write_nb,
		const uint16_t *src, int read_addr, int read_nb,
		uint16_t *dest);


};

