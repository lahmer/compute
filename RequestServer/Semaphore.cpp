//
// Created by lahmer on 8/17/16.
//

#include "Semaphore.h"

semaphore::semaphore() {
    m_count = 0;
}
void semaphore::notify(){
    boost::mutex::scoped_lock lock(m_mutex);
    ++m_count;
    m_condition.notify_one();
}
void semaphore::wait(){
    boost::mutex::scoped_lock lock(m_mutex);
    while(!m_count)
        m_condition.wait(lock);
    --m_count;
}