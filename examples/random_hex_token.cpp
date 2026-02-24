#include <secure_random/secure_random.hpp>

#include <iostream>

int main()
{
  // 32 random bytes => 64 hex chars
  const std::string token = secure_random::hex(32);

  std::cout << "hex token: " << token << "\n";
  std::cout << "length  : " << token.size() << "\n";
  return 0;
}
