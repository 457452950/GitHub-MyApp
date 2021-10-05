//
// Created by wang on 2021/9/12.
//

#include "BaseServer.h"
#include <iostream>
#include <chrono>
#include "Logger.h"

namespace wlb
{

    const std::chrono::microseconds BaseServer::s_baseTick = std::chrono::microseconds(1000000 - 600);  // 1s

    BaseServer::BaseServer(int port)
    {
        m_pIOService = std::make_shared<ioService_type>();
        m_pAccept = std::make_shared<acceptor_type>
            (*m_pIOService, BoostTCP::endpoint(BoostTCP::v4(), port));

        m_tTimer = std::make_shared<timer_type>(*m_pIOService, s_baseTick);
        m_tTimer->async_wait(boost::bind(&BaseServer::TimerHandle, this, boost::asio::placeholders::error));


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
        if (ec) {
            LOG(ERROR) << "[set_option]" << ec.message();
            return;
        }

        auto endPoint = BoostTCP::endpoint(boost::asio::ip::make_address_v4(addr), port);
        m_pAccept->bind(endPoint);
        m_pAccept->listen();

        m_tTimer = std::make_shared<timer_type>(*m_pIOService, 0);
        m_tTimer->async_wait(boost::bind(&BaseServer::TimerHandle, this, boost::asio::placeholders::error));

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

    void BaseServer::TimerHandle(boost::system::error_code ec)
    {
        m_tTimer->expires_from_now(s_baseTick);
        m_tTimer->async_wait(boost::bind(&BaseServer::TimerHandle, this, boost::asio::placeholders::error));
        if (ec)
        {
            LOG(ERROR) << "error value : " << ec.value() << " error MSG : " << ec.message();
        }
        // ++m_iTick;
        int checkTime = 40 * s_secPerMil;       // 40s timer
        if ((++m_iTick %= checkTime) == 0)
        {
            onTime();
        }
    }

    void BaseServer::AcceptHandle(boost::system::error_code ec, Connection_ptr conn)
    {
        if (ec)
        {
            LOG(ERROR) << "error value : " << ec.value() << " error MSG : " << ec.message();
        }

        accept();
        conn->sock->async_read_some(boost::asio::buffer(conn->pBuff), boost::bind(
                &BaseServer::RecvHandle,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred,
                conn));
        
        
        m_vecConns.push_back(conn);
        conn->onConnected();
        
        onConnected(conn);
        
    }

    void BaseServer::RecvHandle(boost::system::error_code ec, int recvSize, Connection_ptr conn)
    {
        if (ec)
        {
            LOG(INFO) ;
            if (ErrorHandle(ec, conn)) {
                Disconnected(conn);
                return;
            }
        }
    
        if (conn->isKeepAlive())
        {
            conn->sock->async_read_some(boost::asio::buffer(conn->pBuff), boost::bind(
                    &BaseServer::RecvHandle,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred,
                    conn));
        }
        
        std::string strBuf;
        strBuf.assign(conn->pBuff.begin(), conn->pBuff.begin() + recvSize);
        onMessage(conn, strBuf);
    }

    void BaseServer::SendHandle(boost::system::error_code ec, BaseServer::Connection_ptr conn)
    {
        if (ec)
        {
            LOG(INFO) ;
            ErrorHandle(ec, conn);
            Disconnected(conn);
            return;
        }
        if (conn->m_bCloseAfterSend)
        {
            Disconnected(conn);
        }
    }


    void BaseServer::run()
    {
        m_pIOService->run();
    }
    
    
    void BaseServer::Disconnected(Connection_ptr conn)
    {
        auto iter = std::find(m_vecConns.begin(), m_vecConns.end(), conn);
        if (iter != m_vecConns.end())
            m_vecConns.erase(iter);
        onDisconnected(conn);
    }
    
    // return if need to close
    bool BaseServer::ErrorHandle(boost::system::error_code ec, Connection_ptr conn)
    {
        LOG(INFO) << "error value : " << ec.value() << " = "
            << ec.message();
        
        if (ec.value() == 2)
        {
            conn->sock->shutdown(boost::asio::socket_base::shutdown_both);
            conn->m_bCloseAfterSend = true;
            conn->setKeepAlive(false);
        }

        return true;
    }

    void BaseServer::send(Connection_ptr conn, std::string Doc)
    {
        LOG(INFO) << "send : " << Doc;
        conn->sock->async_send(boost::asio::buffer(Doc), boost::bind(
            &BaseServer::SendHandle,
            this,
            boost::asio::placeholders::error,
            conn
        ));
    }


}
