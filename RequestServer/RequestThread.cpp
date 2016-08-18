//
// Created by lahmer on 8/17/16.
//

#include "RequestThread.h"

RequestThread::RequestThread() {
    m_th.reset(new std::thread([this](){
        while(true){
            ConnectionManager::m_semaphore.wait();
            ConnectionManager::m_ConnectionListMutex.lock();
            std::shared_ptr<sslSocket> socket = ConnectionManager::m_ConnectionsList.get()->back();
            ConnectionManager::m_ConnectionsList.get()->pop_back();
            ConnectionManager::m_ConnectionListMutex.unlock();
            //TODO::Here we add the function that this thread will execute
            //while(true);
            std::string message = "Helko there \n";
            boost::asio::write(*socket, boost::asio::buffer(message));

        }
    }));
}

void RequestThread::Stop() {
    m_th->join();
}