#pragma once

#include "session.h"

/**
 * @brief The ClientSession class
 * implements the session for the Client
 */
class ClientSession: public Session
{
public:
    using tcp = boost::asio::ip::tcp;

    ClientSession(tcp::socket socket);

protected:
    /**
     * @brief onRead displays the read message
     */
    virtual void onRead() override;

    /**
     * @brief onWriteFailed prints error and closes the connection
     */
    virtual void onWriteFailed() override;

    /**
     * @brief onReadFailed prints error and closes the connection
     */
    virtual void onReadFailed() override;
};
