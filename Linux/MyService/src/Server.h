//
// Created by wlb on 2021/9/19.
//

#ifndef MYSERVICE_SERVER_H
#define MYSERVICE_SERVER_H

#include "BaseConnection.h"
#include "BaseServer.h"

using namespace wlb;

class Server : public BaseServer
{
public:
    Server(int port);
    Server(std::string addr, int port);

protected:
    void onConnected(Connection_ptr conn) override;
    void onMessage(Connection_ptr conn, std::string Doc) override;
    void onDisconnected(Connection_ptr conn) override;
    void onTime() override;

};


#endif //MYSERVICE_SERVER_H
