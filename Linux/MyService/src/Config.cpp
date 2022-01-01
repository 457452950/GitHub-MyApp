#include "Config.h"
#include <fstream>
#include <utils/include/AsyncLogger.h>

namespace wlb
{
    using namespace Log;
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
		LOG(L_INFO) << "file name :" << s_strFileName;
		s_Config = new Config();
		s_Config->load();
	}

	void Config::load()
	{
		if (!m_reader.HasMember("endPoint") || !m_reader["endPoint"].IsString())
		{
			LOG(L_ERROR) << "endPoint illegal";
			return;
		}

		LOG(L_INFO) << "endPoint : " << m_reader["endPoint"].GetString();
		_EndPointIP = m_reader["endPoint"].GetString();


		if (!m_reader.HasMember("endPort") || !m_reader["endPort"].IsInt())
		{
			LOG(L_ERROR) << "endPort illegal";
			return;
		}

		LOG(L_INFO) << "endPort : " << m_reader["endPort"].GetInt();
		_EndPointPort = m_reader["endPort"].GetInt();


		if (!m_reader.HasMember("frontPoint") || !m_reader["frontPoint"].IsString())
		{
			LOG(L_ERROR) << "frontPoint illegal";
			return;
		}

		LOG(L_INFO) << "frontPoint : " << m_reader["frontPoint"].GetString();
		_FrontPointIP = m_reader["frontPoint"].GetString();


		if (!m_reader.HasMember("frontPort") || !m_reader["frontPort"].IsInt())
		{
			LOG(L_ERROR) << "frontPort illegal";
			return;
		}

		LOG(L_INFO) << "frontPort : " << m_reader["frontPort"].GetInt();
		_FrontPointPort = m_reader["frontPort"].GetInt();


		if (!m_reader.HasMember("redisServerPoint") || !m_reader["redisServerPoint"].IsString())
		{
			LOG(L_ERROR) << "redisServerPoint illegal";
			return;
		}

		LOG(L_INFO) << "redisServerPoint : " << m_reader["redisServerPoint"].GetString();
		_RedisIP = m_reader["redisServerPoint"].GetString();

		if (!m_reader.HasMember("redisPort") || !m_reader["redisPort"].IsInt())
		{
			LOG(L_ERROR) << "redisPort illegal";
			return;
		}

		LOG(L_INFO) << "redisPort : " << m_reader["redisPort"].GetInt();
		_RedisPort = m_reader["redisPort"].GetInt();


		if (!m_reader.HasMember("maxBufSize") || !m_reader["maxBufSize"].IsInt())
		{
			LOG(L_ERROR) << "maxBufSize illegal";
			_MaxBuffSize = 16;
			return;
		}

		LOG(L_INFO) << "maxBufSize : " << m_reader["maxBufSize"].GetInt();
		_MaxBuffSize = m_reader["maxBufSize"].GetInt();
	}

}
