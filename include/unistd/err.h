// -*- Mode: C++; -*-
// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_ERR_H
#define UNISTD_ERR_H
#include <string>

namespace unistd {

[[noreturn]]
void throw_system_error(int error, const std::string &context);

[[noreturn]]
void throw_generic_error(int error, const std::string &context);

}

#endif
