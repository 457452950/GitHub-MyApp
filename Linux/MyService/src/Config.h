#pragma once
#ifndef __CONFIG_H
#define __CONFIG_H


#include <iostream>
#include <string>
#include "JsonFileReader.h"

#define Conf wlb::Config::getInstance()


namespace wlb
{


class Config
{

public:
	~Config();

	static Config* getInstance();
	static void readFile(std::string fileName);

	std::string getEndPointAddr();
	int         getEndPointPort();
	std::string getFrontPointAddr();
	int         getFrontPointPort();
	std::string getRedisPointAddr();
	int         getRedisPort();
    int         getMaxBufferSize();
private:
	Config();

 

	JsonFileReader m_reader;

	static std::string s_strFileName;
	static Config* s_Config;
};


}





#endif // !__CONFIG_H


