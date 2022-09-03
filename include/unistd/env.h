// -*- Mode: C++; -*-
// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_ENV_H
#define UNISTD_ENV_H
#include <string>
#include <optional>
#include <cstdlib>

namespace unistd {

std::optional<std::string> maybe_getenv(const std::string &name);

}

#endif
