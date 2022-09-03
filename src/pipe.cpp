// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#include <unistd/pipe.h>
#include <array>
#include <cerrno>

namespace unistd {

Pipe::Pipe(Flags flags) : handle_open{true,true} {
  if (::pipe2(handles.data(), flags) == -1)
    sys_err(errno, __func__);
}

Pipe::~Pipe() {
  if (handle_open.at(0))
    close(0);
  if (handle_open.at(1))
    close(1);
}

int Pipe::close(int which) {
  int rv{0};
  if (handle_open.at(which)) {
    rv = ::close(handles.at(which));
    if (rv == 0)
      handle_open.at(which) = false;
  }
  return rv;
}

int Pipe::dup(int which) const {
  return ::dup(handles.at(which));
}

int Pipe::dup(int which, int newfd) {
  return ::dup2(handles.at(which), newfd);
}

int Pipe::fcntl(int which, Flags flags) const {
  int rv{0};
  if (flags != none) {
    int fd = handles.at(which);
    if (flags & close_on_exec) {
      rv = ::fcntl(fd, F_SETFD, FD_CLOEXEC);
      if (rv == -1) return rv;
    }
    if (flags & nonblocking)
      rv = ::fcntl(fd, F_SETFL, O_NONBLOCK);
  }
  return rv;
}

bool Pipe::is_read_handle_open() const { return handle_open.at(0); }
bool Pipe::is_write_handle_open() const { return handle_open.at(1); }
int Pipe::get_read_handle() const { return handles.at(0); }
int Pipe::get_write_handle() const { return handles.at(1); }

void Pipe::close_read_handle() {
  if (close(0) == -1)
    sys_err(errno, __func__);
}

void Pipe::close_write_handle() {
  if (close(1) == -1)
    sys_err(errno, __func__);
}

void Pipe::set_read_handle_flags(Flags flags) const {
  if(fcntl(0, flags) == -1)
    sys_err(errno, __func__);
}

void Pipe::set_write_handle_flags(Flags flags) const {
  if(fcntl(1, flags) == -1)
    sys_err(errno, __func__);
}

void Pipe::set_flags(Flags flags) const {
  set_read_handle_flags(flags);
  set_write_handle_flags(flags);
}

int Pipe::dup_read_handle() const {
  int nfd = dup(0);
  if (nfd == -1)
    sys_err(errno, __func__);
  return nfd;
}

int Pipe::dup_write_handle() const {
  int nfd = dup(1);
  if (nfd == -1)
    sys_err(errno, __func__);
  return nfd;
}

int Pipe::dup_read_handle(int newfd) {
  int nfd = dup(0, newfd);
  if (nfd == -1)
    sys_err(errno, __func__);
  return nfd;
}

int Pipe::dup_write_handle(int newfd) {
  int nfd = dup(1, newfd);
  if (nfd == -1)
    sys_err(errno, __func__);
  return nfd;
}

ssize_t Pipe::read(std::string &str) const {
  std::array<std::string::value_type, Pipe::kbuffer_size> buffer{};
  ssize_t rv = read<std::string::value_type>(buffer.data(), buffer.size());
  if (rv)
    str.assign(buffer.data(), rv);
  return rv;
}

ssize_t Pipe::write(const std::string &str) const {
  return write<std::string::value_type>(str.c_str(), str.length());
}

Popen::Popen(const std::string &command, const std::string &type) {
  pf = ::popen(command.c_str(), type.c_str());
  if (!pf)
    sys_err(errno, __func__);
}

Popen::~Popen() {
  ::pclose(pf);
}

ssize_t Popen::read(std::string &str) {
  std::array<std::string::value_type, Pipe::kbuffer_size> buffer{};
  ssize_t n = read<std::string::value_type>(buffer.data(), buffer.size());
  if (n > 0) str.assign(buffer.data(), n);
  return n;
}

ssize_t Popen::write(const std::string &str) {
  return write<std::string::value_type>(str.c_str(), str.length());
}

}
