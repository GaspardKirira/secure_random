# secure_random

Minimal secure random utilities for modern C++.

`secure_random` provides cryptographically secure random byte generation
with helpers for hex and base64url tokens.

Header-only. No heavy dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/secure_random

## Why secure_random?

Unlike `std::rand` or `std::mt19937`, this library:

-   Uses OS-provided secure randomness
-   Generates cryptographically strong bytes
-   Provides hex token generation
-   Provides base64url token generation
-   Is fully header-only
-   Has zero external dependencies

Perfect for:

-   API keys
-   Session tokens
-   Password reset tokens
-   JWT secret generation
-   Nonces
-   CSRF tokens
-   CLI tools

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/secure_random
vix deps
```

### Manual

Clone the repository:

``` bash
git clone https://github.com/GaspardKirira/secure_random.git
```

Add the `include/` directory to your project.

## Quick Examples

### Generate Raw Bytes

``` cpp
#include <secure_random/secure_random.hpp>
#include <iostream>

int main()
{
  auto bytes = secure_random::bytes(32);
  std::cout << "generated: " << bytes.size() << " bytes\n";
}
```

### Generate Hex Token

``` cpp
#include <secure_random/secure_random.hpp>
#include <iostream>

int main()
{
  std::string token = secure_random::hex(32);
  std::cout << token << "\n";
}
```

32 random bytes → 64 hex characters.

### Generate Base64url Token

``` cpp
#include <secure_random/secure_random.hpp>
#include <iostream>

int main()
{
  std::string token = secure_random::base64url(24);
  std::cout << token << "\n";
}
```

No padding. URL-safe.

## API Overview

``` cpp
secure_random::bytes(size);

secure_random::hex(size);

secure_random::base64url(size);
```

Where:

`size` = number of random bytes to generate.

## Platform Support

-   Linux / macOS: uses `/dev/urandom`
-   Windows: uses `BCryptGenRandom`

Relies on the operating system's secure RNG.

## Security Notes

-   Do not use `std::rand` for cryptographic purposes
-   This library pulls randomness directly from the OS
-   Suitable for token and key generation
-   Not a full cryptographic framework

## Tests

Run:

``` bash
vix build
vix tests
```

## Design Philosophy

`secure_random` focuses on:

-   Minimal API surface
-   Deterministic behavior
-   Zero configuration
-   OS-backed security
-   Small integration footprint

Built for modern C++ systems where simplicity matters.

## License

MIT License
Copyright (c) Gaspard Kirira

