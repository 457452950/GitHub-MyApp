//
// Created by wlb on 2021/9/12.
//

#include "BaseConnection.h"
#include "Logger.h"

namespace wlb
{

    BaseConnection::BaseConnection(std::shared_ptr<ioService_type> io)
        :m_pIOService(io)
    {
        sock = std::make_shared<socket_type>(*io);
        pBuff.resize(Conf->getMaxBufferSize() * 1024);   // max 65536 64*1024
        m_bKeepAlive = true;
    }

    boost::asio::ip::tcp::endpoint BaseConnection::GetRemoteEndPoint()
    {
        boost::system::error_code ec;
        return sock->remote_endpoint(ec);
    }
    
    boost::asio::ip::tcp::endpoint BaseConnection::GetLocalEndPoint()
    {
        boost::system::error_code ec;
        return sock->local_endpoint(ec);
    }
    
    boost::asio::ip::tcp::endpoint BaseConnection::GetRemoteEndPoint(boost::system::error_code& ec)
    {
        return sock->remote_endpoint(ec);
    }

    boost::asio::ip::tcp::endpoint BaseConnection::GetLocalEndPoint(boost::system::error_code& ec)
    {
        return sock->local_endpoint(ec);
    }

    void BaseConnection::CloseConnect(boost::system::error_code& ec)
    {
        sock->close(ec);
    }

    void BaseConnection::CloseConnect()
    {
        boost::system::error_code ec;
        sock->close(ec);
    }

void BaseConnection::onConnected()
{
    boost::system::error_code ec;
    
    boost::asio::socket_base::keep_alive ka(1);
    sock->set_option(ka, ec);
    if (ec)
    {
        LOG(ERROR) << "error val : " << ec.value() << " : " << ec.message();
    }
    
/*    boost::asio::socket_base::receive_buffer_size rbs;
    sock->get_option(rbs, ec);
    if (ec)
    {
        LOG(ERROR) << "error val : " << ec.value() << " : " << ec.message();
    }
    LOG(INFO) << "receive_buffer_size : " << rbs.value();*/
}


}