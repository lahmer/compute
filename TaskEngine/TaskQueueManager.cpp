//
// Created by lahmer on 8/18/16.
//

#include "TaskQueueManager.h"
std::vector<std::unique_ptr<TaskThread> > TaskQueueManager::m_ThreadPool;
int TaskQueueManager::m_index;
std::mutex TaskQueueManager::m_IndexMutex;


void TaskQueueManager::InitialiseTaskQueueManager() {
    for(int i = 0  ; i < std::thread::hardware_concurrency() ; i++){
        std::unique_ptr<TaskThread> th;
        th.reset(new TaskThread(i));
        m_ThreadPool.push_back(std::move(th));
     }
}

void TaskQueueManager::PushMessage(const Message& msg) {
    m_IndexMutex.lock();
    if(m_index == std::thread::hardware_concurrency()-1)
        m_index = 0;
    else
        m_index++;
    m_ThreadPool.at(m_index)->AssignTask(msg);
    m_IndexMutex.unlock();
}