#include "Config.h"
#include <fstream>
#include <Logger.h>

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
		LOG(INFO) << "file name :" << s_strFileName;
		s_Config = new Config();
	}

	std::string Config::getEndPointAddr()
	{
		if (!m_reader.HasMember("endPoint") || !m_reader["endPoint"].IsString())
		{
			LOG(ERROR) << "endPoint illegal";
			return "";
		}

		LOG(INFO) << "endPoint : " << m_reader["endPoint"].GetString();
		return m_reader["endPoint"].GetString();
	}

	int Config::getEndPointPort()
	{
		if (!m_reader.HasMember("endPort") || !m_reader["endPort"].IsInt())
		{
			LOG(ERROR) << "endPort illegal";
			return 0;
		}

		LOG(INFO) << "endPort : " << m_reader["endPort"].GetInt();
		return m_reader["endPort"].GetInt();
	}

	std::string Config::getFrontPointAddr()
	{
		if (!m_reader.HasMember("frontPoint") || !m_reader["frontPoint"].IsString())
		{
			LOG(ERROR) << "frontPoint illegal";
			return "";
		}

		LOG(INFO) << "frontPoint : " << m_reader["frontPoint"].GetString();
		return m_reader["frontPoint"].GetString();
	}

	int Config::getFrontPointPort()
	{
		if (!m_reader.HasMember("frontPort") || !m_reader["frontPort"].IsInt())
		{
			LOG(ERROR) << "frontPort illegal";
			return 0;
		}

		LOG(INFO) << "frontPort : " << m_reader["frontPort"].GetInt();
		return m_reader["frontPort"].GetInt();
	}

	std::string Config::getRedisPointAddr()
	{
		if (!m_reader.HasMember("redisServerPoint") || !m_reader["redisServerPoint"].IsString())
		{
			LOG(ERROR) << "redisServerPoint illegal";
			return "";
		}

		LOG(INFO) << "redisServerPoint : " << m_reader["redisServerPoint"].GetString();
		return m_reader["redisServerPoint"].GetString();
	}

	int Config::getRedisPort()
	{
		if (!m_reader.HasMember("redisPort") || !m_reader["redisPort"].IsInt())
		{
			LOG(ERROR) << "redisPort illegal";
			return 0;
		}

		LOG(INFO) << "redisPort : " << m_reader["redisPort"].GetInt();
		return m_reader["redisPort"].GetInt();
	}

	int Config::getMaxBufferSize()
	{
		if (!m_reader.HasMember("maxBufSize") || !m_reader["maxBufSize"].IsInt())
		{
			LOG(ERROR) << "maxBufSize illegal";
			return 16;
		}

		LOG(INFO) << "maxBufSize : " << m_reader["maxBufSize"].GetInt();
		return m_reader["maxBufSize"].GetInt();
	}


}
