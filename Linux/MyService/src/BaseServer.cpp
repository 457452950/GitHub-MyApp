//
// Created by wang on 2021/9/12.
//

#include "BaseServer.h"
#include <iostream>

namespace wlb
{

BaseServer::BaseServer(int port)
{
    m_pIOService = std::make_shared<ioService_type>();
    m_pAccept = std::make_shared<acceptor_type>
            (*m_pIOService, BoostTCP::endpoint(BoostTCP::v4(), port));
 
    
    accept();
}

BaseServer::BaseServer(std::string addr, int port)
{
    m_pIOService = std::make_shared<ioService_type>();
    m_pAccept = std::make_shared<acceptor_type>
            (*m_pIOService);
    m_pAccept->open(BoostTCP::v4());
    
    boost::system::error_code ec;
    m_pAccept->set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec){
        std::cout << ec.message() << std::endl;
        return;
    }
    
    auto endPoint = BoostTCP::endpoint(boost::asio::ip::make_address_v4(addr), port);
    m_pAccept->bind(endPoint);
    m_pAccept->listen();
    
    accept();
}


void BaseServer::accept()
{
    Connection_ptr conn = std::make_shared<Connection_type>(m_pIOService);
    m_pAccept->async_accept(*conn->sock, boost::bind(
            &BaseServer::AcceptHandle,
            this,
            boost::asio::placeholders::error,
            conn));
}

void BaseServer::AcceptHandle(boost::system::error_code ec, Connection_ptr conn)
{
    if (ec)
    {
        std::cout << "[BaseServer::AcceptHandle] : " << ec.message() << std::endl;
    }
    
    accept();
    onConnected(conn);

    conn->sock->async_receive(boost::asio::buffer(conn->pBuff), boost::bind(
            &BaseServer::RecvHandle,
            this,
            boost::asio::placeholders::error,
            conn));
    
    m_vecConns.push_back(conn);
}

void BaseServer::RecvHandle(boost::system::error_code ec, Connection_ptr conn)
{
    if (ec)
    {
        if(ErrorHandle(ec, conn)){
            onDisconnected(conn);
            return;
        }
    }
    
    std::string strBuf;
    strBuf.assign(conn->pBuff.begin(), conn->pBuff.end());
    onMessage(conn, strBuf);
    
    send(conn, strBuf);
    
    if (conn->isKeepAlive())
    {
        conn->sock->async_read_some(boost::asio::buffer(conn->pBuff), boost::bind(
                &BaseServer::RecvHandle,
                this,
                boost::asio::placeholders::error,
                conn));
    }
    else
    {
        auto iter = std::find(m_vecConns.begin(), m_vecConns.end(), conn);
        m_vecConns.erase(iter);
    }
}

void BaseServer::SendHandle(boost::system::error_code ec, BaseServer::Connection_ptr conn)
{
    if (ec)
    {
        if(ErrorHandle(ec, conn)){
            onDisconnected(conn);
            return;
        }
    }
}


void BaseServer::run()
{
    m_pIOService->run();
}

void BaseServer::onConnected(Connection_ptr conn)
{
    std::cout << "onConnected : " << m_vecConns.size() << std::endl;
}

void BaseServer::onDisconnected(Connection_ptr conn)
{
    std::cout << "onDisconnected" << "" << std::endl;
    auto iter = std::find(m_vecConns.begin(), m_vecConns.end(), conn);
    m_vecConns.erase(iter);
}

void BaseServer::onMessage(Connection_ptr conn, std::string Doc)
{
    std::cout << "recv : " << Doc << std::endl;
}

bool BaseServer::ErrorHandle(boost::system::error_code ec, Connection_ptr conn)
{
    std::cout << "[BaseServer::RecvHandle] : " << ec.value() << " = "
              << ec.message() << std::endl;
    
    return true;
}

void BaseServer::send(Connection_ptr conn, std::string Doc)
{
    conn->sock->async_send(boost::asio::buffer(Doc), boost::bind(
            &BaseServer::SendHandle,
            this,
            boost::asio::placeholders::error,
            conn
            ));
}


}