# RTYPE PROJECT

## Topic

Welcome to R-TYPE, a classic side-scrolling shooter game where you pilot a spaceship and battle against waves of enemy forces. In this game, you must navigate through various levels, defeat challenging bosses, and ultimately save the world from an alien invasion.

> You can find the subject [here](./subject.pdf) :rocket:

## How does it work?

### Gameplay

R-TYPE is a fast-paced action game that requires quick reflexes and strategic thinking. As the pilot of a powerful spacecraft, you'll need to avoid obstacles and enemy fire while shooting down enemy ships and ground defenses. To help you succeed, you can collect power-ups and special weapons that increase your firepower and give more health !

Each level in R-TYPE features unique challenges and enemies, culminating in a fierce boss battle that tests your skills and mastery of the game.

You can navigate your ship using the directional arrows :

- ⬆ : up
- ⬅ : left
- ➡ : right
- ⬇ : down
- Space : shoot

### Network

R-TYPE can be played both offline and online. In online mode, players can join together to take on the game's challenges in co-op mode.

The online mode uses a client-server architecture, with the game server responsible for managing the game state and enforcing game rules. Players connect to the game server using a network protocol such as UDP.

By the way if you want to create your own client, you must follow the protocol attached.

### Game engine

It is possible to develop different games using the same game engine, which speeds up the development process and makes it possible to create games faster. In the case of RType, Flappy Bird and Factorio, these games were developed using the same game engine that was developed earlier. Although these games are very different from each other, their shared game engine allows them to have similarities in performance and usability. This is an advantage for developers because it allows us to reuse existing code and resources to create new games, while improving the quality and experience for players.

## Getting Started

### Installation

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

#### Documentation

The developers documentation is generated with [Doxygen](https://www.doxygen.nl/manual/install.html).

Make sure that you have the following additionnal dependencies :

- `texlive-latex-base`
- `texlive-fonts-recommended`
- `texlive-fonts-extra`
- `texlive-latex-extra`

### Quickstart

#### Documentation

You can find the documentation [here](./doc/documenation.pdf).

To update it, simply run the following command :

```shell
./generateDoc
```

:warning: Don't forget to update the [Doxyfile](./Doxyfile) if you've added a documented file :warning:

> Search for `INPUT =`

### More games :

With the project we have made 2 more games !

### Factorio

The goal of Factorio is to build and manage an automated factory in a hostile environment. The player starts on an alien planet with few resources and must mine raw materials such as iron, copper and coal to build factories that produce increasingly advanced items.

### Flappy Bird

The goal of Flappy Bird is to make a bird fly through a series of obstacles made of green pipes, without touching the pipes or the ground. The player controls the bird by pressing on the screen to flap its wings and make it fly. Each time the player successfully passes a pipe, he scores a point. The ultimate goal of the game is to get the highest score possible by passing as many pipes as possible.

To make the bird fly in the Flappy Bird game, you need to press the "space" key. Each press of the "space" key will make the bird flap its wings and fly a little higher. It is important to synchronize the flapping of the wings with the movements of the bird to avoid the obstacles and achieve the best possible score. Keep in mind that timing is crucial in this game, so try to find the right rhythm to make the bird fly successfully.

## Our team :heart:

| [<img src="https://github.com/William-Karkegi.png?size=85" width=85><br><sub>William</sub>](https://github.com/William-Karkegi) | [<img src="https://github.com/Nokimalos.png?size=85" width=85><br><sub>Kaan</sub>](https://github.com/Nokimalos) | [<img src="https://github.com/QuentinCn.png?size=85" width=85><br><sub>Quentin</sub>](https://github.com/QuentinCn) | [<img src="https://github.com/shemtovsamuel.png?size=85" width=85><br><sub>Samuel</sub>](https://github.com/shemtovsamuel) | [<img src="https://github.com/Enzo-ALAIMO.png?size=85" width=85><br><sub>Enzo</sub>](https://github.com/Enzo-ALAIMO) |
| :-----------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------: |
