//
// Created by wlb on 2021/9/12.
//

#ifndef MYSERVICE_BASECONNECTION_H
#define MYSERVICE_BASECONNECTION_H

#include <memory>
#include <vector>
#include "boost/asio.hpp"
#include "src/Config.h"

namespace wlb{

class BaseConnection
{
    using BoostTCP = boost::asio::ip::tcp;
    
    using ioService_type = boost::asio::io_service;
    using ioService_ptr = std::weak_ptr<ioService_type>;
    
    using socket_type = BoostTCP::socket;
    using socket_ptr  = std::shared_ptr<socket_type>;
    
    using buffer_type = std::vector<char>;
public:
    BaseConnection(std::shared_ptr<ioService_type> io);
    ~BaseConnection() {
    }
    
    void onConnected();
    
    BoostTCP::endpoint GetRemoteEndPoint();
    BoostTCP::endpoint GetLocalEndPoint();
    BoostTCP::endpoint GetRemoteEndPoint(boost::system::error_code& ec);
    BoostTCP::endpoint GetLocalEndPoint(boost::system::error_code& ec);
    
    bool isKeepAlive(){
        return m_bKeepAlive;
    }
    void CloseConnect(boost::system::error_code& ec);
    void CloseConnect();
public:
    socket_ptr     sock;
    buffer_type    pBuff;
protected:
    ioService_ptr  m_pIOService;
    bool           m_bKeepAlive;
    
};

}

#endif //MYSERVICE_BASECONNECTION_H
