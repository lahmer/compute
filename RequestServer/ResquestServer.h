//
// Created by lahmer on 8/16/16.
//

#ifndef CLIOTEST_RESQUESTSERVER_H
#define CLIOTEST_RESQUESTSERVER_H

#include "../common.h"
#include "ConnectionManager.h"

class ResquestServer {
    friend class ConnectionManager;
public:
    static void InitResquestServer();
    static void Start();
    static void Stop();
private:
    static boost::asio::io_service* m_ios;
    static boost::asio::ip::tcp::acceptor* m_acceptor;
    static boost::asio::ssl::context* m_ctx;

};


#endif //CLIOTEST_RESQUESTSERVER_H
