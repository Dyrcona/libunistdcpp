// -*- Mode: C++; -*-
// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_SYSNAME_H
#define UNISTD_SYSNAME_H
#include <sys/utsname.h>
#include <memory>
#include <string>
#include <ostream>

namespace unistd {

class SysName {
public:
  SysName();
  SysName(const SysName &) = delete;
  SysName(SysName &&) = delete;
  ~SysName() = default;
  SysName& operator=(const SysName &) = delete;
  SysName& operator=(SysName &&) = delete;
  std::string sysname() const;
  std::string nodename() const;
  std::string release() const;
  std::string version() const;
  std::string machine() const;

private:
  std::unique_ptr<struct utsname> info;
};

std::ostream& operator<<(std::ostream &os, const SysName &info);

}

#endif
