#include "JsonFileReader.h"

namespace wlb
{

	JsonFileReader::JsonFileReader(std::string fileName)
	{
		std::ifstream ifile(fileName);
		if (!ifile.is_open())
		{
			std::cout << "[JsonFileReader::JsonFileReader]!ifile.is_open():" << std::endl;
			exit(-1);
		}
		rapidjson::IStreamWrapper iSW(ifile);

		m_docData.ParseStream(iSW);
		if (m_docData.HasParseError())
		{
			std::cout << "[JsonFileReader::JsonFileReader]HasParseError:" << m_docData.GetParseError() << std::endl;
		}
		
		if (!m_docData.IsObject())
		{
			std::cout << "[JsonFileReader::JsonFileReader]IsObject:flase\n" ;
		}

	}

	JsonFileReader::~JsonFileReader()
	{
	}



 


}