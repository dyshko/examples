#include "serversession.h"
#include <iostream>

using boost::asio::ip::tcp;

ServerSession::ServerSession(tcp::socket socket):
    Session(std::move(socket))
{
}

void ServerSession::onWriteFailed()
{
    std::cout << "Error sending message" << std::endl;
}

void ServerSession::onReadFailed()
{
    std::cout << "Error recieving message" << std::endl;
}

void ServerSession::onRead()
{
    std::string message(m_readMessage.body(), m_readMessage.bodyLength());
    std::cout << "Received: " << message << std::endl;
    std::string reply = (message == "Hello world" ? "Status: OK": "Status: NOT OK");
    Message msg;
    msg.setBody(reply);
    deliver(msg);
}
