// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#include <unistd/host.h>
#include <unistd/err.h>
#include <array>
#include <cerrno>
#include <climits>
#include <unistd.h>

namespace unistd {

std::string gethostname() {
  std::array<char, _POSIX_HOST_NAME_MAX> buf{};
  if (::gethostname(buf.data(), buf.max_size()) == 0)
    return {buf.data()};
  else
    sys_err(errno, __func__);
}

void sethostname(const std::string &name) {
  if (::sethostname(name.c_str(), name.length()) == -1)
    sys_err(errno, __func__);
}

}
