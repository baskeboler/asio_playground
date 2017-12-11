//
// Created by victor on 12/9/17.
//
#include <boost/iostreams/copy.hpp>
#include "file_serve_handler.h"
#include <boost/algorithm/string.hpp>
void file_serve_handler::handle_request(request &req, response &res) {

  std::string path = req.target().to_string();
  boost::algorithm::erase_all(path, mount_path);

  fs::path fetch = server_root / path;
  if (fs::exists(fetch)) {
    if (fs::is_directory(fetch)) {

    } else if (fs::is_regular_file(fetch)) {
      fs::ifstream is(fetch);
      char buf[1024];
//      while (is.get(buf, 1024) != 0) {
//
//      }
//      boost::iostreams::copy(is, boost::beast::ostream(res.body()));

    }
  }
}
file_serve_handler::file_serve_handler(const boost::filesystem::path &server_root, const std::string &mount_path)
    : server_root(server_root), mount_path(mount_path) {}
