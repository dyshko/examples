#pragma once

#include <boost/asio.hpp>

#include "clientsession.h"

/**
 * @brief The Client class represents the client:
 * creates the connection and manages session
 */
class Client
{
public:
    using tcp = boost::asio::ip::tcp;

    Client(boost::asio::io_context& ioContext,
        const tcp::resolver::results_type& endpoint);

    /**
     * @brief write sends the message
     * @param message
     */
    void write(const std::string& message);

    /**
     * @brief close closes the session
     */
    void close();

private:

    /**
     * @brief connect establishes the connection and start session
     * @param endpoints
     */
    void connect(const tcp::resolver::results_type& endpoints);

    /**
     * @brief m_ioContext boost asio context
     */
    boost::asio::io_context& m_ioContext;

    /**
     * @brief m_session a session of the Client
     */
    std::unique_ptr<ClientSession> m_session;

    /**
     * @brief m_socket socket object
     */
    tcp::socket m_socket;
};
