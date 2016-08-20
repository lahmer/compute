//
// Created by lahmer on 8/18/16.
//

#include "TaskThread.h"

TaskThread::TaskThread(const unsigned short &core) {
    if(core < 0 || core >= std::thread::hardware_concurrency()){
        LOGE<<"recieving wrong number of core "<<core;
        std::terminate();
    }
    m_QueueSemaphore = new semaphore();
    m_CoreIndex = core;
    m_TaskThread.reset(new std::thread([this](){
        //we set the affinity to the specific core number
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(m_CoreIndex,&mask);
        int code = sched_setaffinity(0,sizeof(mask),&mask);
        if(code == -1){
            LOGE<<"Error while setting the cpu affinity "<<m_CoreIndex;
            std::terminate();
        }
        //TODO::add the task thread function here
        while(true){
            m_QueueSemaphore->wait();
            m_QueueMutex.lock();
            Message cmd = m_MessageQueue.back();
            m_MessageQueue.pop_back();
            m_QueueMutex.unlock();
            while(true);
        };


    }));
}

void TaskThread::Stop() {
    m_TaskThread->join();
}

void TaskThread::AssignTask(const Message &msg) {
    m_QueueMutex.lock();
    m_MessageQueue.push_back(msg);
    m_QueueMutex.unlock();
    m_QueueSemaphore->notify();
}