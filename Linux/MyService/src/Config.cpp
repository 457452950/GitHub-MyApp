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
		s_Config->load();
	}

	void Config::load()
	{
		if (!m_reader.HasMember("endPoint") || !m_reader["endPoint"].IsString())
		{
			LOG(ERROR) << "endPoint illegal";
			return;
		}

		LOG(INFO) << "endPoint : " << m_reader["endPoint"].GetString();
		_EndPointIP = m_reader["endPoint"].GetString();


		if (!m_reader.HasMember("endPort") || !m_reader["endPort"].IsInt())
		{
			LOG(ERROR) << "endPort illegal";
			return;
		}

		LOG(INFO) << "endPort : " << m_reader["endPort"].GetInt();
		_EndPointPort = m_reader["endPort"].GetInt();


		if (!m_reader.HasMember("frontPoint") || !m_reader["frontPoint"].IsString())
		{
			LOG(ERROR) << "frontPoint illegal";
			return;
		}

		LOG(INFO) << "frontPoint : " << m_reader["frontPoint"].GetString();
		_FrontPointIP = m_reader["frontPoint"].GetString();


		if (!m_reader.HasMember("frontPort") || !m_reader["frontPort"].IsInt())
		{
			LOG(ERROR) << "frontPort illegal";
			return;
		}

		LOG(INFO) << "frontPort : " << m_reader["frontPort"].GetInt();
		_FrontPointPort = m_reader["frontPort"].GetInt();


		if (!m_reader.HasMember("redisServerPoint") || !m_reader["redisServerPoint"].IsString())
		{
			LOG(ERROR) << "redisServerPoint illegal";
			return;
		}

		LOG(INFO) << "redisServerPoint : " << m_reader["redisServerPoint"].GetString();
		_RedisIP = m_reader["redisServerPoint"].GetString();

		if (!m_reader.HasMember("redisPort") || !m_reader["redisPort"].IsInt())
		{
			LOG(ERROR) << "redisPort illegal";
			return;
		}

		LOG(INFO) << "redisPort : " << m_reader["redisPort"].GetInt();
		_RedisPort = m_reader["redisPort"].GetInt();


		if (!m_reader.HasMember("maxBufSize") || !m_reader["maxBufSize"].IsInt())
		{
			LOG(ERROR) << "maxBufSize illegal";
			_MaxBuffSize = 16;
			return;
		}

		LOG(INFO) << "maxBufSize : " << m_reader["maxBufSize"].GetInt();
		_MaxBuffSize = m_reader["maxBufSize"].GetInt();
	}

}
