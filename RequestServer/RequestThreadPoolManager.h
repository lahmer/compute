//
// Created by lahmer on 8/17/16.
//

#ifndef CLIOTEST_REQUESTTHREADPOOLMANAGER_H
#define CLIOTEST_REQUESTTHREADPOOLMANAGER_H
#include"../common.h"
#include "ConnectionManager.h"
class RequestThread;
class RequestThreadPoolManager {
    friend class ConnectionManager;
private:
    ///This function is responsible for calling the thread pool manager which
    ///will spawn the threads responsibles for the initial handeling of the requests
    static void InitialiseThreadPoolManager();

private:
    static std::vector<RequestThread> m_ThreadPool;
};


#endif //CLIOTEST_REQUESTTHREADPOOLMANAGER_H
