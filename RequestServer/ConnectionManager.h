//
// Created by lahmer on 8/17/16.
//

#ifndef CLIOTEST_CONNECTIONMANAGER_H
#define CLIOTEST_CONNECTIONMANAGER_H

#include "../common.h"
///This class represents the request server connection manager it will spawn a thread
///that will keep on listening on the server port and when a connection arrives he
///will push it into the connections vector
class semaphore;
class ConnectionManager {
    friend class ResquestServer;
    friend class RequestThread;
private:
    ///This method will create the thread that will keep on listening connections
    ///and then push the connection to the connection list
    static void InitialiseConnectionManager();

    ///This method will stop the thread responsible for accepting new connections
    static void StopConnectionManager();

    static void SpawnThread();

    static void KillThread();

private:
    static std::unique_ptr<std::vector<std::shared_ptr<sslSocket>> > m_ConnectionsList;
    static std::mutex m_ConnectionListMutex;
    static std::unique_ptr<std::thread> m_ConnectionMonitorThread;
    static std::atomic<bool> m_StopFlag ;
    static semaphore m_semaphore;
};


#endif //CLIOTEST_CONNECTIONMANAGER_H
