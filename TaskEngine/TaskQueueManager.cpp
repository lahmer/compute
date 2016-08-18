//
// Created by lahmer on 8/18/16.
//

#include "TaskQueueManager.h"
std::vector<std::unique_ptr<TaskThread> > TaskQueueManager::m_ThreadPool;

void TaskQueueManager::InitialiseTaskQueueManager() {
    for(int i = 0  ; i < std::thread::hardware_concurrency() ; i++){
        std::unique_ptr<TaskThread> th;
        th.reset(new TaskThread(i));
        m_ThreadPool.push_back(std::move(th));
    }

}