// -*- Mode: C++; -*-
#ifndef UNISTD_ASPRINTF_H
#define UNISTD_ASPRINTF_H
#include <unistd/err.h>
#include <string>
#include <string_view>
#include <memory>
#include <cstdio>
#include <cerrno>

/**
 * asprintf functionality for C++ with std::string.
 *
 * Sources:
 * https://stackoverflow.com/a/26221725/11722
 * https://gist.github.com/Zitrax/a2e0040d301bf4b8ef8101c0b1e3f1d5
 *
 * No license is mentioned in Zitrax's (Daniel Bengtsson) gist, but
 * the original code from iFreilicht on Stackoverflow is posted with a
 * CC0 version 1.0 license, i.e. public domain.
 */

namespace unistd {

template<typename T>
auto asprintf_convert(T&& t) {
  if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, std::string_view>) {
    std::string s = std::move(static_cast<std::string>(t));
    return std::forward<std::string>(s).c_str();
  }
  else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, std::string>) {
    return std::forward<T>(t).c_str();
  }
  else {
    return std::forward<T>(t);
  }
}

template<typename ... Args>
auto asprintf_impl(std::string& out, const std::string& format, Args&& ... args) {
  auto length = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
  if (length < 1) return length;
  std::size_t size = length + 1;
  auto buf = std::make_unique<char[]>(size);
  length = std::snprintf(buf.get(), size, format.c_str(), std::forward<Args>(args)...);
  if (length > 0) out.assign(buf.get(), length);
  return length;
}

template<typename ... Args>
std::string asprintf(const std::string& format, Args&& ... args) {
  std::string out{};
  if (asprintf_impl(out, format, asprintf_convert(std::forward<Args>(args))...) == -1)
    throw_generic_error(errno, __func__);
  return out;
}

template<typename ... Args>
std::string asprintf(std::string_view& format, Args&& ... args) {
  return asprintf(static_cast<std::string>(format), std::forward<Args>(args)...);
}

}

#endif
