/**
 * @file secure_random.hpp
 * @brief Minimal secure random utilities for modern C++.
 *
 * Header-only.
 *
 * Provides:
 *  - secure random bytes
 *  - hex token generation
 *  - base64url token generation
 *
 * Uses:
 *  - /dev/urandom on Unix-like systems
 *  - BCryptGenRandom on Windows
 *
 * MIT License
 */

#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#endif

namespace secure_random
{

  namespace detail
  {

    inline void fill_random_bytes(std::uint8_t *data, std::size_t size)
    {
#if defined(_WIN32)

      if (BCryptGenRandom(nullptr,
                          reinterpret_cast<PUCHAR>(data),
                          static_cast<ULONG>(size),
                          BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0)
      {
        throw std::runtime_error("BCryptGenRandom failed");
      }

#else
      std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
      if (!urandom)
        throw std::runtime_error("failed to open /dev/urandom");

      urandom.read(reinterpret_cast<char *>(data), size);
      if (!urandom)
        throw std::runtime_error("failed to read random bytes");

#endif
    }

    inline std::string to_hex(const std::uint8_t *data, std::size_t size)
    {
      static const char *hex = "0123456789abcdef";

      std::string out;
      out.reserve(size * 2);

      for (std::size_t i = 0; i < size; ++i)
      {
        out.push_back(hex[(data[i] >> 4) & 0xF]);
        out.push_back(hex[data[i] & 0xF]);
      }

      return out;
    }

    static constexpr char b64_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789-_";

    inline std::string base64url_encode(const std::uint8_t *data, std::size_t size)
    {
      std::string out;
      out.reserve(((size + 2) / 3) * 4);

      std::size_t i = 0;
      while (i + 3 <= size)
      {
        const std::uint32_t n =
            (data[i] << 16) |
            (data[i + 1] << 8) |
            (data[i + 2]);

        out.push_back(b64_table[(n >> 18) & 63]);
        out.push_back(b64_table[(n >> 12) & 63]);
        out.push_back(b64_table[(n >> 6) & 63]);
        out.push_back(b64_table[n & 63]);

        i += 3;
      }

      const std::size_t rem = size - i;

      if (rem == 1)
      {
        const std::uint32_t n = data[i] << 16;
        out.push_back(b64_table[(n >> 18) & 63]);
        out.push_back(b64_table[(n >> 12) & 63]);
      }
      else if (rem == 2)
      {
        const std::uint32_t n =
            (data[i] << 16) |
            (data[i + 1] << 8);

        out.push_back(b64_table[(n >> 18) & 63]);
        out.push_back(b64_table[(n >> 12) & 63]);
        out.push_back(b64_table[(n >> 6) & 63]);
      }

      return out;
    }

  } // namespace detail

  inline std::vector<std::uint8_t> bytes(std::size_t size)
  {
    std::vector<std::uint8_t> out(size);
    detail::fill_random_bytes(out.data(), size);
    return out;
  }

  inline std::string hex(std::size_t size)
  {
    const auto b = bytes(size);
    return detail::to_hex(b.data(), b.size());
  }

  inline std::string base64url(std::size_t size)
  {
    const auto b = bytes(size);
    return detail::base64url_encode(b.data(), b.size());
  }

} // namespace secure_random
