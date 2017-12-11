//
// Created by victor on 12/9/17.
//

#ifndef ASIO_PLAYGROUND_SERVER_H
#define ASIO_PLAYGROUND_SERVER_H
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "session.h"

using boost::asio::ip::tcp;
namespace http = boost::beast::http;

class server {
 public:

  server(boost::asio::io_service &io_service, short port);
 private:

  void do_accept();
  tcp::acceptor _acceptor;
  tcp::socket _socket;
};

#endif //ASIO_PLAYGROUND_SERVER_H
