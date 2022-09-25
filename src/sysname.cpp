// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#include <unistd/sysname.h>
#include <unistd/err.h>

namespace unistd {

SysName::SysName() {
  info = std::make_unique<struct utsname>();
  if (uname(info.get()) != 0)
    throw_system_error(errno, __func__);
}

std::string SysName::sysname() const {
  return {info->sysname};
}

std::string SysName::nodename() const {
  return {info->nodename};
}

std::string SysName::release() const {
  return {info->release};
}

std::string SysName::version() const {
  return {info->version};
}

std::string SysName::machine() const {
  return {info->machine};
}

std::ostream& operator<<(std::ostream& os, const SysName& sysname) {
  return os << sysname.sysname() << " " << sysname.nodename() << " " << sysname.release()
            << " " << sysname.version() << " " << sysname.machine();
}

}
