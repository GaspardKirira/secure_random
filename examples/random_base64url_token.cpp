#include <secure_random/secure_random.hpp>

#include <iostream>

int main()
{
  // 24 random bytes => base64url token (no padding)
  const std::string token = secure_random::base64url(24);

  std::cout << "base64url token: " << token << "\n";
  std::cout << "length        : " << token.size() << "\n";
  return 0;
}
