#pragma once

#include <list>
#include <boost/asio.hpp>
#include "message.h"

#include "serversession.h"

/**
 * @brief The Server class represents the server:
 * accepts the connection and manages sessions
 * Multiple sessions are possible for a single server
 */
class Server
{
public:
    Server(boost::asio::io_context& io_context,
        const boost::asio::ip::tcp::endpoint& endpoint);

private:

    /**
     * @brief accept accepts the connection and starts to
     * listen for the incoming messages
     */
    void accept();

    /**
     * @brief m_acceptor tcp acceptor
     */
    boost::asio::ip::tcp::acceptor m_acceptor;

    /**
     * @brief m_sessions list of all server sessions
     */
    std::list<std::unique_ptr<ServerSession>> m_sessions;
};


