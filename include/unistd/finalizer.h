// -*- Mode: C++; -*-
// Copyright © 2025 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_FINALIZER_H
#define UNISTD_FINALIZER_H

namespace unistd {

// This is a common implementation and should likely be considered
// public domain.
template <class F> class ScopeFinalizer {
  F f;
public:
  ScopeFinalizer(const ScopeFinalizer&) = delete;
  ScopeFinalizer& operator=(const ScopeFinalizer&) = delete;
  ScopeFinalizer(F f) : f {f} {}
  ~ScopeFinalizer() {
    f();
  }
};

} // namespace unistd

#endif
