//
// Created by victor on 12/9/17.
//

#ifndef ASIO_PLAYGROUND_DIRECT_RESPONSE_HANDLER_H
#define ASIO_PLAYGROUND_DIRECT_RESPONSE_HANDLER_H

#include "request_handler.h"

class direct_response_handler: public request_handler {
  std::string message;
  http::status status;
 public:
  direct_response_handler(const std::string &message, http::status status);
 public:
  void handle_request(request &request1, response &respnse1) override;
  virtual ~direct_response_handler();
};

class direct_response_handler_factory: public request_handler_factory {
  std::string message;
  http::status status;
 public:
  direct_response_handler_factory(const std::string &message, http::status status);
 public:
  request_handler *get(request &req, request_handler *next) override;
};

#endif //ASIO_PLAYGROUND_DIRECT_RESPONSE_HANDLER_H
