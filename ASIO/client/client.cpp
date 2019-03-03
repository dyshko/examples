#include "client.h"
#include <iostream>

Client::Client(boost::asio::io_context& ioContext,
    const tcp::resolver::results_type& endpoints):
    m_ioContext(ioContext),
    m_socket(m_ioContext)
{
    connect(endpoints);
}

void Client::connect(const tcp::resolver::results_type& endpoints)
{
  boost::asio::async_connect(m_socket, endpoints,
      [this](boost::system::error_code ec, tcp::endpoint)
      {
          if (!ec)
          {
              m_session = std::unique_ptr<ClientSession>(new ClientSession(std::move(m_socket)));
              m_session->read();
          }
          else
          {
              std::cout << "Cannot establish connection (close and try again)" << std::endl;
          }
      });
}


void Client::write(const std::string& message)
{
    boost::asio::post(m_ioContext,
      [this, message]()
      {
          Message msg;
          msg.setBody(message);

          m_session->deliver(msg);
      });
}

void Client::close()
{
    boost::asio::post(m_ioContext, [this]() { m_session->close(); });
}
