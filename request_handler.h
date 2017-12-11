//
// Created by victor on 12/9/17.
//

#ifndef ASIO_PLAYGROUND_REQUEST_HANDLER_H
#define ASIO_PLAYGROUND_REQUEST_HANDLER_H
#include <boost/beast.hpp>
#include <boost/log/trivial.hpp>
namespace http = boost::beast::http;

typedef http::request<http::dynamic_body> request;
typedef http::response<http::dynamic_body> response;

class request_handler {
 public:
  void internal_handle_request(request &req, response &res) {
    handle_request(req, res);

  }
  virtual void handle_request(request &, response &)= 0;
  virtual ~request_handler() {
    std::cout << "destroying request handler" << std::endl;
  }
};

class request_handler_factory {

 public:
  virtual request_handler *get(request &req, request_handler *next)=0;
  virtual ~request_handler_factory() {}
};
#endif //ASIO_PLAYGROUND_REQUEST_HANDLER_H
