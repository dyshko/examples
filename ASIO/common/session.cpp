#include "session.h"

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket)
  : m_socket(std::move(socket))
{
}

void Session::read()
{
    readHeader();
}

void Session::close()
{
    m_socket.close();
}

void Session::deliver(const Message& message)
{
    bool write_in_progress = !m_writeMessages.empty();
    m_writeMessages.push_back(message);
    if (!write_in_progress)
    {
        write();
    }
}

void Session::readHeader()
{
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_readMessage.data(), Message::HEADER_LENGTH),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                m_readMessage.decodeHeader();
                readBody();
            }
            else
            {
                onReadFailed();
            }
        });
}

void Session::readBody()
{
    boost::asio::async_read(m_socket,
        boost::asio::buffer(m_readMessage.body(), m_readMessage.bodyLength()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                onRead();
                readHeader();
            }
            else
            {
                onReadFailed();
            }
        });
}

void Session::write()
{
    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_writeMessages.front().data(),
          m_writeMessages.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                m_writeMessages.pop_front();
                if (!m_writeMessages.empty())
                {
                    write();
                }
            }
            else
            {
                onWriteFailed();
            }
        });
}
