# Battleship

This is an implementation of the board game [Battleship](https://en.wikipedia.org/wiki/Battleship_(game)). It is written in C++, using [wxWidgets](https://www.wxwidgets.org/) for the GUI, [sockpp](https://github.com/fpagliughi/sockpp) for the network interface, [JSON for C++ (nlohmann)](https://github.com/nlohmann/json) for serialization, and [googletest](https://github.com/google/googletest) for the unit tests. The project was created as part of the course "Software Engineering" at ETH Zurich. 

<p align="center">
  <img src="assets/battleship_logo.png" alt="Battleship Logo"/>
</p>

## Ship Happens
The team members are:
* Tejas Gupta
* Marina Mancoridis
* Nico Müller
* Armin Riess
* Mike Schmid
* Robin Sieber

## Build

The program is built using cmake.
To build the program a C++ compiler that supports the C++20 standard is needed. (g++ version greater than 10)

```bash
mkdir build
cd build
cmake ..
make
```

## How to play
### Connecting to the server

To play the game you have to start a client (`./Battleship_Client`) for each of the two players and one server (`./Battleship_Server`). The server can only handle one game instance at once. 

In the connection panel, enter the server address, the port, and choose your username. Then click on "connect" to connect to the server. 

![connection_panel](./assets/screenshots/connection_panel.png?raw=true)

### Setting up the Board

Once you are connected to the server, the setup panel will be displayed. Here, you can arrange your ships. 

![setup_panel1](./assets/screenshots/setup_panel1.png?raw=true)

Click on one of the ships on the right to select it. Then, hover over the placement grid. Press R on your keyboard to rotate the ship and left mouse click to place it. The ships can't overlap but they can touch each other. Once a ship is placed you can't move it again. 

After all five ships have been placed, click on the ready button. This tells the server that you are ready to play. Before the game starts you may have to wait for your opponent to finish setting up their ships. 

![setup_panel2](./assets/screenshots/setup_panel2.png?raw=true)

### Playing the Game

When both players are ready, the game starts. The main game panel has two grids. The one on the left shows your ships and where your opponent has placed their shots, the one on the right is where you'll place your shots. 

![maingame_panel1](./assets/screenshots/maingame_panel1.png?raw=true)

The turn indicator at the top of the window shows whose turn it is. If it is your turn, click on a tile on the right grid to place your shot there. A red dot marks a hit, and a white dot marks a miss. If you score a hit on one of your opponent's ships you may go again, otherwise it's your opponents turn next. Once a ship has been sunk, the corresponding ship below the grid will be colored red. 

![maingame_panel2](./assets/screenshots/maingame_panel2.png?raw=true)

### Sending Emotes

During the game, you can send your opponent emotes. To do this, click on one of the emotes on the right. The emotes are displayed in the middle of the screen, some of them will also play a sound. To hide the displayed emotes simply click on them. In order to prevent spamming you can only send an emote every five seconds. 

![emote](./assets/screenshots/emote.png?raw=true)

### End of the Game

Once a player has sunk all of their opponent's ships, the game ends. A popup shows who has won and then both players are disconnected from the server. If the players want to play another game, they have to reconnect. 

![maingame_panel3](./assets/screenshots/maingame_panel3.png?raw=true)

If one of the players disconnects mid-game, for example because they have closed their client, the game ends as well and both players will have to reconnect.

## Tests and Documentation
* To run the unit tests, run `./Battleship_Test` from the build directory.
* The documentation can be found in the `documentation` folder. 

## Known Issues

* On some machines, wxWidgets is not able to play sounds when it's compiled from the git repository. A fix for this is to install wxWidgets yourself and compile the program using the `-DUSE_LOCAL_WXWIDGETS=ON` flag:
    ```bash
    mkdir build
    cd build
    cmake -DUSE_LOCAL_WXWIDGETS=ON ..
    make
    ```

* UI text is not visible on dark mode. Change your system settings to light mode to fix this.
