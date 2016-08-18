//
// Created by lahmer on 8/17/16.
//

#ifndef CLIOTEST_SEMAPHORE_H
#define CLIOTEST_SEMAPHORE_H

#include "../common.h"

///The c++ does'nt define a semaphore type so this class simulate the behavior of a
///semaphore
class semaphore
{
private:
    boost::mutex m_mutex;
    boost::condition_variable m_condition;
    unsigned long m_count;
public:
    semaphore();
    void notify();
    void wait();
};



#endif //CLIOTEST_SEMAPHORE_H
