# RTYPE Developer Documentation

This project contains several scripts to help you build and run the project.

## How does it work?

The project is divided into several modules:

- `engine`: The engine part of the project
- `rtype-client`: The client part of the project
- `rtype-server`: The server part of the project

The `engine` module is a library that contains all the logic of the game. It is used by both the client and the server.

The `rtype-client` module is a graphical client that uses the engine to display the game.

The `rtype-server` module is a server that uses the engine to run the game.

## Getting Started

### Installation

#### Python

[Python](https://www.python.org/downloads/) is required because we use [Conan](https://docs.conan.io/en/latest/) to manage our dependencies which needs it.

1. Windows

    - Download the latest version of Python from [here](https://www.python.org/downloads/windows/).

2. Linux

    - Ubuntu

    ```shell
    sudo apt install python3
    ```

    - Arch Linux

    ```shell
    sudo pacman -S python
    ```

    - Fedora

    ```shell
    sudo dnf install python3
    ```

    - OpenSUSE

    ```shell
    sudo zypper install python3
    ```

3. MacOS

    - Download the latest version of Python from [here](https://www.python.org/downloads/mac-osx/).
    - Brew

    ```shell
    brew install python3
    ```

#### Conan

We use [Conan](https://docs.conan.io/en/latest/) to manage our dependencies.

To install it, simply run the following command :

```shell
pip install --user conan
```

Then, you need to run the following commands to configure Conan :

```shell
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

If any error occurs, check the [official documentation](https://docs.conan.io/en/latest/).

#### CMake

[CMake](https://cmake.org/download/) is required to build the project.

1. Windows

    - Download the latest version of CMake from [here](https://cmake.org/download/).

2. Linux

    - Ubuntu

    ```shell
    sudo apt install cmake
    ```

    - Arch Linux

    ```shell
    sudo pacman -S cmake
    ```

    - Fedora

    ```shell
    sudo dnf install cmake
    ```

    - OpenSUSE

    ```shell
    sudo zypper install cmake
    ```

3. MacOS

    - Download the latest version of CMake from [here](https://cmake.org/download/).
    - Brew

    ```shell
    brew install cmake
    ```

### Scripts

There is both scripts for Windows and Linux.

> ⚠️ Make sure to run the scripts from the root of the project ⚠️

- build-engine.sh

    This script builds the engine.

    ```shell
    ./scripts/linux/build-engine.sh
    ```

    No arguments available.

- build-client.sh

    This script builds the client.

    ```shell
    ./scripts/linux/build-client.sh
    ```

    The following arguments are available:

    - `-engine`: Builds the engine before building the client.
    - `-cicd`: Builds the client in CICD mode.
    - `-run`: Runs the client after building it.

- build-server.sh

    This script builds the server.

    ```shell
    ./scripts/linux/build-server.sh
    ```

    The following arguments are available:

    - `-cicd`: Builds the server in CICD mode.
    - `-run`: Runs the server after building it.

### Documentation

You can find the documentation [here](./doc/documenation.pdf).

To update it, simply run the following command :
```shell
./generateDoc
```

⚠️ Don't forget to update the [Doxyfile](./Doxyfile) if you've added a documented file ⚠️
> Search for `INPUT =`