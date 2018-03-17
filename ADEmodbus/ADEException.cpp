#include "ADEException.h"

ADEException::ADEException(const char* errMessage)
{
	this->errMessage = errMessage;
}

ADEException::~ADEException()
{
}
