//
// Created by lahmer on 8/18/16.
//

#ifndef CLIOTEST_TASKQUEUEMANAGER_H
#define CLIOTEST_TASKQUEUEMANAGER_H

#include"../common.h"
class TaskThread;

///This class is responsible for managing the task queue and assigning to each
///thread a task
///This class will calculate the number of cores of the system
///then spawn a thread for each core and assign each thread for a core
///by modifying the affinity of the thread this is an os specific operation
class TaskQueueManager {
    friend class Compute;
private:
    static void InitialiseTaskQueueManager();
    //TODO::add the system that pushes messages using this method
    static void PushMessage(const Message& msg);
private:
    static std::vector<std::unique_ptr<TaskThread>> m_ThreadPool;
    static int m_index;
    static std::mutex m_IndexMutex;
};


#endif //CLIOTEST_TASKQUEUEMANAGER_H
