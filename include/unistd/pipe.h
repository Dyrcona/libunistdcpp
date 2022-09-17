// -*- Mode: C++; -*-
// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_PIPE_H
#define UNISTD_PIPE_H
#include <array>
#include <string>
#include <climits>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <unistd/err.h>

namespace unistd {

class Pipe {
public:
  static const std::size_t kbuffer_size = PIPE_BUF;
  enum Flags {none = 0, nonblocking = O_NONBLOCK, close_on_exec = O_CLOEXEC};

  Pipe(Flags flags = Flags::none);
  ~Pipe();

  Pipe(const Pipe&) = default;
  Pipe(Pipe&&) = default;
  Pipe& operator=(const Pipe&) = default;
  Pipe& operator=(Pipe&&) = default;

  bool is_read_handle_open() const;
  bool is_write_handle_open() const;
  int get_read_handle() const;
  int get_write_handle() const;
  void close_read_handle();
  void close_write_handle();
  void set_flags(Flags flags) const;
  void set_read_handle_flags(Flags flags) const;
  void set_write_handle_flags(Flags flags) const;
  int dup_read_handle() const;
  int dup_write_handle() const;
  int dup_read_handle(int newfd);
  int dup_write_handle(int newfd);

  template<typename T>
  ssize_t read(T *buffer, std::size_t count) const {
    ssize_t rv = ::read(handles.at(0), buffer, sizeof(T) * count);
    if (rv == -1) throw_system_error(errno, __func__);
    return rv;
  }

  template<typename T>
  ssize_t write(const T *buffer, std::size_t count) const {
    ssize_t rv = ::write(handles.at(1), buffer, sizeof(T) * count);
    if (rv == -1) throw_system_error(errno, __func__);
    return rv;
  }

  template<typename T, std::size_t N>
  ssize_t read(std::array<T, N> &array) const {
    return read<T>(array.data(), N);
  }

  template<typename T, std::size_t N>
  ssize_t write(const std::array<T, N> &array) const {
    return write<T>(array.data(), N);
  }

  ssize_t read(std::string &str) const;
  ssize_t write(const std::string &str) const;

private:
  std::array<int, 2> handles{};
  std::array<bool, 2> handle_open{false, false};

  int close(int which);
  int dup(int which) const;
  int dup(int which, int newfd);
  int fcntl(int which, Flags flags) const;
};

class Popen {
public:
  Popen(const std::string &command, const std::string &type);
  ~Popen();

  Popen(const Popen&) = delete;
  Popen(Popen&&) = default;
  Popen& operator=(const Popen&) = delete;
  Popen& operator=(Popen&&) = default;

  template<typename T>
  ssize_t read(T *buffer, std::size_t count) {
    errno = 0;
    ssize_t rv = std::fread(buffer, sizeof(T), count, pf);
    if (rv < count && std::ferror(pf))
      throw_generic_error((errno) ? errno : EIO, __func__);
    return rv;
  }

  template<typename T>
  ssize_t write(const T *buffer, std::size_t count) {
    errno = 0;
    ssize_t rv = std::fwrite(buffer, sizeof(T), count, pf);
    if (rv < count && std::ferror(pf))
      throw_generic_error((errno) ? errno : EIO, __func__);
    return rv;
  }

  template<typename T, std::size_t N>
  ssize_t read(std::array<T, N> &array) {
    return read<T>(array.data(), N);
  }

  template<typename T, std::size_t N>
  ssize_t write(const std::array<T, N> &array) {
    return write<T>(array.data(), N);
  }

  ssize_t read(std::string &str);
  ssize_t write(const std::string &str);

private:
  FILE *pf{};
};

}

#endif
