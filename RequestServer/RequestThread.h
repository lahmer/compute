//
// Created by lahmer on 8/17/16.
//

#ifndef CLIOTEST_REQUESTTHREAD_H
#define CLIOTEST_REQUESTTHREAD_H

#include "../common.h"

class RequestThread {
public:
    RequestThread();
    void Stop();

private:
    std::unique_ptr<std::thread> m_th;

};


#endif //CLIOTEST_REQUESTTHREAD_H
