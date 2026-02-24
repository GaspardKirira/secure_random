#include <secure_random/secure_random.hpp>

#include <cstdlib>
#include <iostream>

static void expect_true(bool v, const char *msg)
{
  if (!v)
  {
    std::cerr << "FAIL: " << msg << "\n";
    std::exit(1);
  }
}

int main()
{
  const auto bytes = secure_random::bytes(32);
  expect_true(bytes.size() == 32, "bytes size");

  const auto hex = secure_random::hex(16);
  expect_true(hex.size() == 32, "hex size");

  const auto b64 = secure_random::base64url(16);
  expect_true(!b64.empty(), "base64 not empty");

  std::cout << "ok\n";
  return 0;
}
