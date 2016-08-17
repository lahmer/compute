//
// Created by lahmer on 8/17/16.
//

#include "RequestThreadPoolManager.h"
std::vector<RequestThread> RequestThreadPoolManager::m_ThreadPool;

void RequestThreadPoolManager::InitialiseThreadPoolManager() {
    //first spawn the number of threads specified by the configuration file
    for(int i = 0 ; i < Compute::g_InitialRequestServerThreadPoolSize ;i++){
        m_ThreadPool.push_back(RequestThread());
    }
}