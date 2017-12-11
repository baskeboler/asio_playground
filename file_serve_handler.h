//
// Created by victor on 12/9/17.
//

#ifndef ASIO_PLAYGROUND_FILE_SERVE_HANDLER_H
#define ASIO_PLAYGROUND_FILE_SERVE_HANDLER_H
#include "request_handler.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
class file_serve_handler : public request_handler {
  fs::path server_root;
  std::string mount_path;
 public:
  file_serve_handler(const boost::filesystem::path &server_root, const std::string &mount_path);
 public:
  void handle_request(request &request1, response &response1) override;
};

#endif //ASIO_PLAYGROUND_FILE_SERVE_HANDLER_H
