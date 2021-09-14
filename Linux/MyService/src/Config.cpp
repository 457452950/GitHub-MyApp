#include "Config.h"
#include <fstream>

namespace wlb
{
Config* Config::s_Config = nullptr;
std::string Config::s_strFileName = "";

Config::Config()
	:m_reader(s_strFileName)
{
}

Config::~Config()
{
}

Config* Config::getInstance()
{
	return s_Config;
}

void Config::readFile(std::string fileName)
{
	s_strFileName = fileName;
	s_Config = new Config();
}

std::string Config::getEndPointAddr()
{
	if (!m_reader.HasMember("endPoint") || !m_reader["endPoint"].IsString())
	{
		std::cout << "endPoint illegal" << "\n";
        return "";
	}

	return m_reader["endPoint"].GetString();
}

int Config::getEndPointPort()
{
	if ( !m_reader.HasMember("endPort") || !m_reader["endPort"].IsInt())
	{
        std::cout << "endPort illegal" << "\n";
        return 0;
	}

	return m_reader["endPort"].GetInt();
}

std::string Config::getFrontPointAddr()
{
	if (!m_reader.HasMember("frontPoint") || !m_reader["frontPoint"].IsString())
	{
		std::cout << "frontPoint illegal" << "\n";
        return "";
	}

	return m_reader["frontPoint"].GetString();
}

int Config::getFrontPointPort()
{
	if (!m_reader.HasMember("frontPort") || !m_reader["frontPort"].IsInt())
	{
		std::cout << "frontPort illegal" << "\n";
	}

	return m_reader["frontPort"].GetInt();
}

std::string Config::getRedisPointAddr()
{
	if (!m_reader.HasMember("redisServerPoint") || !m_reader["redisServerPoint"].IsString())
	{
		std::cout << "redisServerPoint illegal" << "\n";
	}

	return m_reader["redisServerPoint"].GetString();
}

int Config::getRedisPort()
{
	if (!m_reader.HasMember("redisPort") || !m_reader["redisPort"].IsInt())
	{
		std::cout << "redisPort illegal" << "\n";
	}

	return m_reader["redisPort"].GetInt();
}

int Config::getMaxBufferSize()
{
    if (!m_reader.HasMember("maxBufSize") || !m_reader["maxBufSize"].IsInt())
    {
        std::cout << "maxBufSize illegal" << "\n";
    }
    
    return m_reader["maxBufSize"].GetInt();
}


}
