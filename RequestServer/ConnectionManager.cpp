//
// Created by lahmer on 8/17/16.
//

#include "ConnectionManager.h"
std::unique_ptr<std::vector<std::shared_ptr<sslSocket>> > ConnectionManager::m_ConnectionsList;
std::unique_ptr<std::thread> ConnectionManager::m_ConnectionMonitorThread;
std::atomic<bool> ConnectionManager::m_StopFlag ;
std::mutex ConnectionManager::m_ConnectionListMutex;
semaphore ConnectionManager::m_semaphore;

void ConnectionManager::InitialiseConnectionManager() {
    m_StopFlag.store(true);
    m_ConnectionsList.reset(new std::vector<std::shared_ptr<sslSocket>> );
    m_ConnectionMonitorThread.reset(new std::thread([](){
        while(m_StopFlag.load()){
            std::shared_ptr<sslSocket> socket;
            socket.reset(new sslSocket(*ResquestServer::m_ios,*ResquestServer::m_ctx));
            ResquestServer::m_acceptor->accept(socket->lowest_layer());
            socket->handshake(boost::asio::ssl::stream_base::server);
            std::cout<<"Connection added"<<std::endl;
            m_ConnectionListMutex.lock();
            m_ConnectionsList->push_back(socket);
            m_semaphore.notify();
            m_ConnectionListMutex.unlock();
        }
    }));
    //Now we initialise the Request Thread pool manager
    RequestThreadPoolManager::InitialiseThreadPoolManager();

    //TODO::Initialise the connection monitor

}