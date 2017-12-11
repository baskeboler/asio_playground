//
// Created by victor on 12/9/17.
//

#include "server.h"
server::server(boost::asio::io_service &io_service, short port) :
    _acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
    _socket(io_service)
{
  do_accept();
}
void server::do_accept() {
  _acceptor.async_accept(
      _socket,
      [this](boost::system::error_code ec) {
        std::cout << "accept connection " << ec <<std::endl;
        if (!ec) {
          std::make_shared<session>(std::move(_socket))->start();
        }
        do_accept();
      });
}
