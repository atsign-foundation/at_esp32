<img width=250px src="https://atsign.dev/assets/img/atPlatform_logo_gray.svg?sanitize=true">

<a href="https://registry.platformio.org/libraries/jeremytubongbanua/at_client"><img src="https://badges.registry.platformio.org/packages/jeremytubongbanua/library/at_client.svg" alt="PlatformIO Registry" /></a>

# at_esp32

ESP32 C++ (Arduino framework) implementation of the atPlatform.

## Installation

Learn how to add `at_client` as a dependency in your PlatformIO project. The atPlatform only supports the Arduino framework for the [ESP32](https://www.espressif.com/en/products/modules/esp32).

You can either go to PlatformIO Home and go to Libraries and search up [`at_client`](https://registry.platformio.org/libraries/jeremytubongbanua/at_client) then click on "Add to Project", or simply:

Setup your `platform.ini` similar to:

```
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    jeremytubongbanua/at_client@^0.0.1
monitor_speed = 115200
```

## Getting Started

(WIP)

## Resources

Core assets used in this project:

- [ESP32-WROOM](https://www.espressif.com/en/products/modules/esp32)
- [PlatformIO](https://platformio.org/)
- [Mbed-TLS](https://github.com/Mbed-TLS/mbedtls)

## Contribute

Any and all pull requests are appreciated and welcome. Please read our [contributing guidelines](CONTRIBUTING.md) containing detailed instructions on how to contribute correctly and create a proper pull request. If you have any questions, please feel free to reach out to us on our [Discord server](https://discord.atsign.com).

## License

BSD 3-Clause License

Copyright (c) 2022, The Atsign Foundation

All rights reserved.

## Maintainers

- [JeremyTubongbanua](https://github.com/JeremyTubongbanua)
- [TylerTrott](https://github.com/TylerTrott)
- [cpswan](https://github.com/cpswan)
- [cconstab](https://github.com/cconstab)
