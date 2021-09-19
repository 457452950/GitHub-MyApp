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
		inline std::string 	getEndPointAddr() { return _EndPointIP; } 
		inline int         	getEndPointPort() { return _EndPointPort; }
		inline std::string 	getFrontPointAddr(){ return _FrontPointIP; }
		inline int         	getFrontPointPort() { return _FrontPointPort; }
		inline std::string 	getRedisPointAddr() { return _RedisIP; }
		inline int         	getRedisPort() { return _RedisPort; }
		inline int         	getMaxBufferSize() { return _MaxBuffSize; }
	private:
		std::string		_EndPointIP;
		int 			_EndPointPort;
		std::string		_FrontPointIP;
		int 			_FrontPointPort;
		std::string		_RedisIP;
		int 			_RedisPort;
		int 			_MaxBuffSize;

		JsonFileReader m_reader;

		// Singleton 
	public:
		static Config* 		getInstance();
		static void 		readFile(std::string fileName);
		~Config();
	private:
		Config();
		void 				load();

		static std::string 	s_strFileName;
		static Config* 		s_Config;
	};


}





#endif // !__CONFIG_H


