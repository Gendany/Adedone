#pragma once
#include<exception>
class ADEException :public std::exception
{
public:
	ADEException(const char* errMessage);
	~ADEException();
private:
	const char* errMessage;
public:
	char const *what()const {
		return errMessage;
	}
};

