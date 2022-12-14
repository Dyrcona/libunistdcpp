// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#include <unistd/err.h>
#include <system_error>

namespace unistd {

[[noreturn]]
void throw_system_error(int error, const std::string &context) {
  throw std::system_error{error, std::system_category(), context};
}

[[noreturn]]
void throw_generic_error(int error, const std::string &context) {
  throw std::system_error{error, std::generic_category(), context};
}

}
