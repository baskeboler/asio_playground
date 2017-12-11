//
// Created by victor on 12/9/17.
//

#include "direct_response_handler.h"


void direct_response_handler::handle_request(request &request1, response &response1) {
  response1.result(status);
  boost::beast::ostream(response1.body()) << message;

}
direct_response_handler::direct_response_handler(const std::string &message, http::status status)
    : message(message), status(status) {}
direct_response_handler::~direct_response_handler() {

}
request_handler *direct_response_handler_factory::get(request &req, request_handler *next) {
  return new direct_response_handler(message, status);
}
direct_response_handler_factory::direct_response_handler_factory(const std::string &message, http::status status)
    : message(message), status(status) {}
