# BrawToFall

## Description
Alcohol Skill Game is a text-based game where players can improve their drinking skills, manage their stability, and level up. Players select drinks from a shop that affect their stability and can upgrade their skills with accumulated points.

## Features
- Choose drinks with varying stability loss.
- Increase drinking skill and maximum stability.
- Leveling system that rewards players with points.
- Stability recovery over time.
- Save and load game progress.

## Planned Features
1. Fix the stability gain in the settings menu.
2. Ensure that skill points are correctly tracked.
3. Adjust starting stability from 100 to 0.
4. Investigate and resolve any additional issues.
5. Introduce a boss fight. The first boss, "Qnkata," will drink "Pirinsko" and will have a stability of 16, unlike the player who starts with 100 stability.
6. Implement an in-game currency system. Players will earn currency by defeating bosses, allowing them to purchase new alcoholic drinks.

## Requirements
- C++ compiler (e.g., g++)
- Standard C++ library

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/trifon1402/Source-code-of-c-drinking-game.git
   cd Source-code-of-c-drinking-game

2.Compile the code:

```

g++ main.cpp -o alcohol_game -pthread
```
Run the game:

bash

    ./main

## Usage

In Main menu is 6 functions

1.Start - you start to drink with every press of Enter and there is Statistic. You need to Buy Alcohol to start drionking

2.Settings - ther is nothing there will be all game controle settings and stabitity regenerator. BUG - There is 2 func nad they don't work will be fixed. 

3.Shop - This is the place we buy alkohol but for now everything is free just select it.

4.View skill status - In this place you can see all Statistic you have.

5.Upgrade skill - There is palce to upgrade your stability barr and drinking skill.wit every point you add 25 to stability max in default stabiliti max is 25. when you upgrade drinking you upgrade level point you have  with every skill point put it in drinking you gain |levelpoint you win * 2|.

6.Exit - This is the way you can save your progress. Never skipt it. Or it can't be saved.

## License

This game is licensed under the MIT License. See the LICENSE file for more details.
Contact

If you have any questions or suggestions, feel free to reach out to me at trifon1404@abv.bg.

vbnet


### Changes Made:
- Added a "Planned Features" section that outlines the improvements and new features you intend to implement.

Feel free to customize further or let me know if you need more adjustments!
