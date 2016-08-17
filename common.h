//
// Created by lahmer on 8/16/16.
//

#ifndef CLIOTEST_COMMON_H
#define CLIOTEST_COMMON_H

#include <iostream>
#include <plog/Log.h>
#include <libconfig.h++>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include<thread>
#include <mutex>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslSocket;


#include "RequestServer/Semaphore.h"
#include "Compute.h"
#include "RequestServer/ResquestServer.h"
#include "RequestServer/ConnectionManager.h"
#include "RequestServer/RequestThread.h"
#include "RequestServer/RequestThreadPoolManager.h"



const int REQUEST_SERVER_DEFAULT_PORT = 16000;
#endif //CLIOTEST_COMMON_H
