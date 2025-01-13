//
// impl/config.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_CONFIG_HPP
#define BOOST_ASIO_IMPL_CONFIG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cerrno>
#include <cstdlib>
#include <limits>
#include <stdexcept>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
T config_get(const config_service& service, const char* section,
    const char* key, T default_value, false_type /*is_bool*/)
{
  if (is_unsigned<T>::value)
  {
    char buf[std::numeric_limits<unsigned long long>::max_digits10 + 1];
    if (const char* str = service.get_value(section, key, buf, sizeof(buf)))
    {
      char* end = nullptr;
      unsigned long long result = std::strtoull(str, &end, 0);
      if (errno == ERANGE || result > (std::numeric_limits<T>::max)())
        detail::throw_exception(std::out_of_range("config out of range"));
      return static_cast<T>(result);
    }
  }
  else
  {
    char buf[std::numeric_limits<long long>::max_digits10 + 1];
    if (const char* str = service.get_value(section, key, buf, sizeof(buf)))
    {
      char* end = nullptr;
      long long result = std::strtoll(str, &end, 0);
      if (errno == ERANGE || result < (std::numeric_limits<T>::min)()
          || result > (std::numeric_limits<T>::max)())
        detail::throw_exception(std::out_of_range("config out of range"));
      return static_cast<T>(result);
    }
  }
  return default_value;
}

template <typename T>
T config_get(const config_service& service, const char* section,
    const char* key, T default_value, true_type /*is_bool*/)
{
  char buf[std::numeric_limits<unsigned long long>::max_digits10 + 1];
  if (const char* str = service.get_value(section, key, buf, sizeof(buf)))
  {
    char* end = nullptr;
    unsigned long long result = std::strtoll(str, &end, 0);
    if (errno == ERANGE || (result != 0 && result != 1))
      detail::throw_exception(std::out_of_range("config out of range"));
    return static_cast<T>(result != 0);
  }
  return default_value;
}

} // namespace detail

template <typename T>
constraint_t<is_integral<T>::value, T>
config::get(const char* section, const char* key, T default_value) const
{
  return detail::config_get(service_, section,
      key, default_value, is_same<T, bool>());
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CONFIG_HPP
