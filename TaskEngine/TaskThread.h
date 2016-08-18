//
// Created by lahmer on 8/18/16.
//

#ifndef CLIOTEST_TASKTHREAD_H
#define CLIOTEST_TASKTHREAD_H

#include "../common.h"
class Message;
class TaskThread {
public:
    TaskThread(const unsigned short& core);
    void Stop();
    void AssignTask(const Message& msg);
public:
    semaphore *m_QueueSemaphore;
    std::mutex m_QueueMutex;
private:
    std::unique_ptr<std::thread> m_TaskThread;
    unsigned short m_CoreIndex;
    std::vector<Message> m_MessageQueue;

};


#endif //CLIOTEST_TASKTHREAD_H
