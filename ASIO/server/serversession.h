#pragma once

#include "session.h"

/**
 * @brief The ServerSession class
 * implements the session for the Server
 */
class ServerSession: public Session
{
public:
    ServerSession(boost::asio::ip::tcp::socket socket);

    virtual ~ServerSession() override = default;

    /**
     * @brief onRead displays the message and reply with the status
     */
    virtual void onRead() override;

    /**
     * @brief onWriteFailed displays error message
     */
    virtual void onWriteFailed() override;

    /**
     * @brief onReadFailed displays error message
     */
    virtual void onReadFailed() override;
};
