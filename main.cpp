#include <cstdlib>
#include <iostream>
#include <memory>
//#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include "server.h"


using boost::asio::ip::tcp;
namespace http = boost::beast::http;

int main(int argc, char *argv[]) {

  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }
    boost::asio::io_service io_service;
    server s(io_service, 2323);
    io_service.run();

  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  std::cout << "Hello, World!" << std::endl;
  return 0;
}