//
// Created by victor on 12/9/17.
//
#include "session.h"
#include "direct_response_handler.h"
void session::check_deadline() {
  auto self(shared_from_this());
  _deadline.async_wait(
      [self](boost::beast::error_code ec) {
        if (!ec) {
          self->_socket.close();
        }
      }
  );
}
session::session(tcp::socket socket)
    : _socket(std::move(socket)) {
  std::cout  << "creating session " << _socket.remote_endpoint() << std::endl;
  chain.add(new direct_response_handler_factory("yo que se", http::status::not_found));
}
session::~session() {
  std::cout  << "destroying session" << std::endl;
}
void session::start() {
  do_read();
  check_deadline();
}
void session::do_read() {
  auto self(shared_from_this());

  http::async_read(
      _socket,
      _buffer,
      _request,
      [self](boost::beast::error_code ec, std::size_t bytes_transfered) {
        boost::ignore_unused(bytes_transfered);
        if (!ec) {
          self->process_request();
        }
      });
}
void session::create_response() {

  _response.set(http::field::content_type, "text/html");
  boost::beast::ostream(_response.body())
      << "<html>\n"
      << "<head><title>Welcome!</title></head>"
      << "<body>"
      << "<h1> Hello world! </h1>"
      << "<p> done with beast! </p>"
      << "</body></html>";

}
void session::write_response() {
  auto self(shared_from_this());
  _response.set(http::field::content_length, _response.body().size());
  http::async_write(
      _socket,
      _response,
      [self](boost::beast::error_code ec, std::size_t) {
        self->_socket.shutdown(tcp::socket::shutdown_send, ec);
        self->_deadline.cancel();
      });
}
void session::process_request() {
  std::cout  << "got request: " << _request << std::endl ;
  _response.version(_request.version());
  handle(_request, _response);

  write_response();
}
void session::handle(request &req, response &res) {
  res.set(http::field::server, "Beast");
  res.keep_alive(false);

  std::shared_ptr<request_handler> h{chain.get(req)};
  h->internal_handle_request(req, res);

}