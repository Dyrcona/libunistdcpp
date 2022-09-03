// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#include <unistd/env.h>
#include <cstdlib>

namespace unistd {

std::optional<std::string> maybe_getenv(const std::string &name) {
  if (const char *x = std::getenv(name.c_str())) return std::string(x);
  return std::nullopt;
}

}
