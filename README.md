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
- [mtausig's tiny-asn1](https://gitlab.com/mtausig/tiny-asn1)

## Contribute

1. Open VSCode and install the PlatformIO VScode extension. You will use this extension to interact with the ESP32. Go to the PlatformIO Home (if you lost it just open the command palette and search and run the `PlatformIO: Home` command) and install the `Espressif32` platform by clicking on the `Platforms` tab and searching for `Espressif32` and clicking on the `Install` button.

2. Make a fork of this repository and git clone it to your local machine.

```
git clone <YOUR_FORK_URL> <path
```

3. Open the PlatformIO CLI by doing `Ctrl (or Cmd) + Shift + P` and run the `PlatformIO: Open PlatformIO Core CLI` command to open the CLI terminal. Then run the following command in the Platform CLI to initialize the `.pio` file.

```
pio project init
```

4. Create a `main.cpp` file in the `src` folder and add the following code:

This will allow you to compile the code. 

```cpp
void setup() {};
void loop() {};
```

5. Open the command palette with `Ctrl (or Cmd) + Shift + P` and run the `PlatformIO: Build` command to build the project. You should get no errors and the terminal should output a build successful. If you get an error, ensure you are executing the commands in the root of the project (the same folder as the `platformio.ini` file).

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
