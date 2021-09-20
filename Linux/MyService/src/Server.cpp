//
// Created by wlb on 2021/9/19.
//

#include "Server.h"
#include "Logger.h"

Server::Server(int port) : BaseServer(port)
{

}

Server::Server(std::string addr, int port) : BaseServer(addr, port)
{

}

void Server::onConnected(Connection_ptr conn)
{
    LOG(INFO) << "onConnected, connect number : " << m_vecConns.size();
}

void Server::onMessage(Connection_ptr conn, std::string Doc)
{
    LOG(INFO) << conn->GetRemoteEndPoint().address().to_string() << " : " << htons(conn->GetRemoteEndPoint().port())
    << " recv size : " << Doc.size() << " \nrecv : " << Doc;
    // this->send(conn, Doc);
    // conn->sock->shutdown(boost::asio::socket_base::shutdown_both);
}

void Server::onDisconnected(Connection_ptr conn)
{
    LOG(INFO) << "onDisconnected, connect number : " << m_vecConns.size();
}

void Server::onTime()
{
    LOG(INFO) << "time out";
}

