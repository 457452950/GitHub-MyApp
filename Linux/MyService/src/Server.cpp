//
// Created by wlb on 2021/9/19.
//

#include "Server.h"
#include "utils/include/AsyncLogger.h"


using namespace Log;

Server::Server(int port) : BaseServer(port)
{

}

Server::Server(std::string addr, int port) : BaseServer(addr, port)
{

}

void Server::onConnected(Connection_ptr conn)
{
    LOG(L_INFO) << "onConnected, connect number : " << m_vecConns.size();
}

void Server::onMessage(Connection_ptr conn, std::string Doc)
{
    LOG(L_INFO) << conn->GetRemoteEndPoint().address().to_string() << " : " << htons(conn->GetRemoteEndPoint().port())
        << " recv size : " << Doc.size() << " \nrecv : " << Doc;
    this->send(conn, Doc);
}

void Server::onDisconnected(Connection_ptr conn)
{
    LOG(L_INFO) << "onDisconnected, connect number : " << m_vecConns.size();
}

void Server::onTime()
{
    LOG(L_INFO) << "time out : " << m_vecConns.size();
}

