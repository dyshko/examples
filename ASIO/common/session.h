#pragma once

#include "message.h"
#include <deque>

#include <boost/asio.hpp>

/**
 * @brief The Session class is an abstract
 * session class. It provides the basic functionality of
 * sending and getting messages over the network (using TCP) in an
 * async way.
 * Also it stores the queue of the ongoing messages
 *
 * Some functions related to error and messages handling
 * need to be implemented in order to instantiate the
 * class object (see below)
 */
class Session
{
public:

    /**
     * @brief Session
     * @param socket object of the established connection
     */
    Session(boost::asio::ip::tcp::socket socket);

    virtual ~Session() = default;

    /**
     * @brief starts to read asynchronously the incomming channel
     */
    virtual void read();

    /**
     * @brief deliver sends the message asynchronously
     * @param message
     */
    virtual void deliver(const Message& message);

    /**
     * @brief close closes the session/socket
     */
    virtual void close();

protected:

    /**
     * @brief onRead must implement the behavior on the message recieved
     * message is accessible from @m_readMessage member
     */
    virtual void onRead() = 0;

    /**
     * @brief onWriteFailed must implement the behavior on the write fail
     */
    virtual void onWriteFailed() = 0;

    /**
     * @brief onReadFailed must implement the behavior on the read fail
     */
    virtual void onReadFailed() = 0;

    /**
     * @brief m_socket socked object
     */
    boost::asio::ip::tcp::socket m_socket;

    /**
     * @brief m_readMessage is a recieved message (if any)
     */
    Message m_readMessage;

    /**
     * @brief m_writeMessages the queue of messages to be sent
     */
    std::deque<Message> m_writeMessages;

private:
    /**
     * @brief readHeader helper function to read the header
     * and proceed to the body/handle errors
     */
    void readHeader();

    /**
     * @brief readBody helper function to read the body, handle
     * message and handle errors
     */
    void readBody();

    /**
     * @brief write helper function to write messages and manage
     * the pending queue
     */
    void write();
};
