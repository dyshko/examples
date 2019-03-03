#include "client.h"

#include <iostream>

ClientSession::ClientSession(boost::asio::ip::tcp::socket socket):
    Session(std::move(socket))
{
}

void ClientSession::onWriteFailed()
{
    std::cout << "Error sending message" << std::endl;
    close();
}

void ClientSession::onReadFailed()
{
    std::cout << "Error receiving message" << std::endl;
    close();
}

void ClientSession::onRead()
{
    std::cout.write(m_readMessage.body(), m_readMessage.bodyLength());
    std::cout << std::endl;
}

