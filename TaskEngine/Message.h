//
// Created by lahmer on 8/18/16.
//

#ifndef CLIOTEST_MESSAGE_H
#define CLIOTEST_MESSAGE_H

#include "../common.h"
class Message {
public:
    Message(std::string msg , std::shared_ptr<sslSocket> socket);
private:
    std::string m_Command;
    std::shared_ptr<sslSocket> m_socket;
};


#endif //CLIOTEST_MESSAGE_H
