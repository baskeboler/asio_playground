//
// Created by victor on 12/9/17.
//

#ifndef ASIO_PLAYGROUND_SESSION_H
#define ASIO_PLAYGROUND_SESSION_H
#include <memory>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <list>
#include "request_handler.h"
using boost::asio::ip::tcp;
namespace http = boost::beast::http;




class request_chain {
  std::list<request_handler_factory*> factories;
  request_handler* get(request& req, std::list<request_handler_factory*> list) {
    if (list.empty())
      return nullptr;
    auto f = list.front();
    list.pop_front();
    return f->get(req, get(req, list));
  }
 public:
  void add(request_handler_factory* f) {
    factories.push_back(f);
  }
  request_handler* get(request& req) {
    return get(req, factories);
  }
};




class session : public std::enable_shared_from_this<session> {
  tcp::socket _socket;
  boost::beast::flat_buffer _buffer{8096};
  request _request;
  response _response;
  boost::asio::basic_waitable_timer<std::chrono::steady_clock> _deadline{
      _socket.get_io_service(), std::chrono::seconds(60)
  };
  request_chain chain;
  void check_deadline();

 public:
  explicit session(tcp::socket socket);
  virtual ~session();
  virtual void handle(request& , response&);
  void start();
 private:

  void do_read();
  void create_response();

  void write_response();
  void process_request();
};

#endif //ASIO_PLAYGROUND_SESSION_H
