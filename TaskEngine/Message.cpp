//
// Created by lahmer on 8/18/16.
//

#include "Message.h"

Message::Message(std::string msg, std::shared_ptr<sslSocket> socket) {
    m_Command = msg;
    m_socket = socket;
}