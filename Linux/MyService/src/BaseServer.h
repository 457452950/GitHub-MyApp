//
// Created by wang on 2021/9/12.
//

#ifndef MYSERVICE_BASESERVER_H
#define MYSERVICE_BASESERVER_H

#include <string>
#include <memory>
#include <functional>
#include "boost/bind.hpp"
#include "boost/asio.hpp"
#include "BaseConnection.h"

namespace wlb
{

class BaseServer
{
    using BoostTCP = boost::asio::ip::tcp;
    
    using acceptor_type = BoostTCP::acceptor;
    using acceptor_ptr = std::shared_ptr<acceptor_type>;
    
    using ioService_type = boost::asio::io_service;
    using ioService_ptr = std::shared_ptr<ioService_type>;
    
    using socket_type = BoostTCP::socket;
    using socket_ptr  = std::shared_ptr<socket_type>;
    
    using Connection_type = BaseConnection;
    using Connection_ptr = std::shared_ptr<Connection_type>;
    using vecConnection = std::vector<Connection_ptr>;
    using buffer_type = std::string;
public:
    BaseServer(int port);
    BaseServer(std::string addr, int port);
    ~BaseServer() = default;
    
    void run();

protected:
    void accept();
    void send(Connection_ptr conn, std::string Doc);
    
    void AcceptHandle(boost::system::error_code ec, Connection_ptr conn);
    void RecvHandle(boost::system::error_code ec, Connection_ptr conn);
    void SendHandle(boost::system::error_code ec, Connection_ptr conn);
    
    bool ErrorHandle(boost::system::error_code ec, Connection_ptr conn);
protected:
    virtual void onMessage(Connection_ptr conn, std::string Doc);
    virtual void onConnected(Connection_ptr conn);
    virtual void onDisconnected(Connection_ptr conn);
    
    
protected:
    acceptor_ptr m_pAccept;
    ioService_ptr m_pIOService;
    vecConnection m_vecConns;
    
    
private:


};

}
#endif //MYSERVICE_BASESERVER_H