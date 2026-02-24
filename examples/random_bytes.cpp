#include <secure_random/secure_random.hpp>

#include <iostream>

int main()
{
  const auto b = secure_random::bytes(16);

  std::cout << "random bytes (16): " << b.size() << "\n";
  return 0;
}
