#include <iostream>
#include "Logger.h"
#include "Config.h"
#include "Server.h"

using namespace std;
using namespace wlb;


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Unknow command! \nUsage:xxx.exe [config.json]\n";
		exit(0);
	}

	wlb::Config::readFile(argv[1]);
 

	BaseServer* s = new Server(Conf->getFrontPointPort());

	s->run();


	return 0;
}

