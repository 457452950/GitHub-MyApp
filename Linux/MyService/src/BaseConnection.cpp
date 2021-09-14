//
// Created by wlb on 2021/9/12.
//

#include "BaseConnection.h"

namespace wlb
{

BaseConnection::BaseConnection(std::shared_ptr<ioService_type> io)
:m_pIOService(io)
{
    sock = std::make_shared<socket_type>(*io);
    pBuff.resize(Conf->getMaxBufferSize() * 1024);
    m_bKeepAlive = true;
}

boost::asio::ip::tcp::endpoint BaseConnection::GetRemoteEndPoint(boost::system::error_code& ec)
{
    return sock->remote_endpoint(ec);
}

boost::asio::ip::tcp::endpoint BaseConnection::GetLocalEndPoint(boost::system::error_code &ec)
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


}