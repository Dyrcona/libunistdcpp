// -*- Mode: C++; -*-
// Copyright © 2022 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_HOST_H
#define UNISTD_HOST_H
#include <string>

namespace unistd {

std::string gethostname();

void sethostname(const std::string &name);

}

#endif
