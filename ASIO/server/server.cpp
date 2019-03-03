#include "server.h"

using boost::asio::ip::tcp;
#include <iostream>

Server::Server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint):
    m_acceptor(io_context, endpoint)
{
    accept();
}

void Server::accept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
              if (!ec)
              {
                  std::cout << "Accepted new connection: " << socket.remote_endpoint().address().to_string()
                            << " " << socket.remote_endpoint().port() << std::endl;
                  auto session =
                          std::unique_ptr<ServerSession>(new ServerSession(std::move(socket)));
                  session->read();
                  m_sessions.push_back(move(session));
              }

              accept();
        });
}
