// -*- Mode: C++; -*-
// Copyright © 2025 Jason Stephenson
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt
#ifndef UNISTD_FINALIZER_H
#define UNISTD_FINALIZER_H

namespace unistd {

// This is a common implementation and should likely be considerd
// public domain.
template <class F> class scope_finalizer {
  F f;
public:
  scope_finalizer(const scope_finalizer&) = delete;
  scope_finalizer& operator=(const scope_finalizer&) = delete;
  scope_finalizer(F f) : f {f} {}
  ~scope_finalizer() {
    f();
  }
};

} // namespace unistd

#endif
