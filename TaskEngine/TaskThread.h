//
// Created by lahmer on 8/18/16.
//

#ifndef CLIOTEST_TASKTHREAD_H
#define CLIOTEST_TASKTHREAD_H

#include "../common.h"
class TaskThread {
public:
    TaskThread(const unsigned short& core);
    void Stop();
private:
    std::unique_ptr<std::thread> m_TaskThread;
    unsigned short m_CoreIndex;
};


#endif //CLIOTEST_TASKTHREAD_H
