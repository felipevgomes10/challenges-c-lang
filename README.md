# C Programming Challenges

This repository contains a collection of C programming challenges, organized into four distinct projects. Each project features a "Novice," "Adventurer," and "Master" challenge, designed to test and develop skills in fundamental data structures and algorithms.

## Prerequisites

To compile and run these challenges, you need a C compiler like `gcc` and the `make` utility installed on your system.

## How to Run the Challenges

A `Makefile` is provided in the root directory to simplify the compilation and execution of each challenge. Open your terminal in the root of the repository and use the following commands:

| Command                   | Description                                             |
| ------------------------- | ------------------------------------------------------- |
| `make war-novice`           | Runs the Novice challenge for WAR Estruturado.          |
| `make war-adventurer`       | Runs the Adventurer challenge for WAR Estruturado.      |
| `make war-master`           | Runs the Master challenge for WAR Estruturado.          |
| `make survival-novice`      | Runs the Novice challenge for the Survival Game.        |
| `make survival-adventurer`  | Runs the Adventurer challenge for the Survival Game.    |
| `make survival-master`      | Runs the Master challenge for the Survival Game.        |
| `make tetris-novice`        | Runs the Novice challenge for Tetris Stack.             |
| `make tetris-adventurer`    | Runs the Adventurer challenge for Tetris Stack.         |
| `make tetris-master`        | Runs the Master challenge for Tetris Stack.             |
| `make detective-novice`     | Runs the Novice challenge for Detective Quest.          |
| `make detective-adventurer` | Runs the Adventurer challenge for Detective Quest.      |
| `make detective-master`     | Runs the Master challenge for Detective Quest.          |
| `make clean`              | Removes all compiled binary files from the project.     |

---

## Project Descriptions

### 1. Project: WAR Estruturado

#### Novice Challenge: Territory Construction
- **Objective:** Build a foundational database for game territories using a `struct` and a static array.

#### Adventurer Challenge: Interactive Attacks
- **Objective:** Implement an attack simulation between territories using dynamic memory allocation and pointers.

#### Master Challenge: Strategic Missions
- **Objective:** Implement a dynamic strategic mission system, where players are assigned a random mission and the game checks for a victory condition after each turn.

### 2. Project: Jogo de Sobrevivência (Survival Game)

#### Novice Challenge: Initial Loot Backpack
- **Objective:** Implement a player's starting inventory system using a static array of `structs`.

#### Adventurer Challenge: Vector vs. Linked List
- **Objective:** Compare the performance of a static vector (array) and a dynamic linked list for managing inventory.

#### Master Challenge: Advanced Sorting Analysis
- **Objective:** Implement and analyze the performance (comparisons and execution time) of three different sorting algorithms (Bubble, Insertion, Selection) on a collection of game components.

### 3. Project: Tetris Stack

#### Novice Challenge: The Piece Queue
- **Objective:** Simulate the queue of upcoming pieces in Tetris using a circular queue.

#### Adventurer Challenge: The Reserve Stack
- **Objective:** Integrate the piece queue with a stack to allow the player to reserve pieces.

#### Master Challenge: Advanced Piece Management
- **Objective:** Implement advanced strategic actions, allowing pieces to be swapped between the circular queue and the reserve stack.

### 4. Project: Detective Quest

#### Novice Challenge: The Mansion Map
- **Objective:** Create an interactive map of a mansion using a Binary Tree.

#### Adventurer Challenge: Collecting Clues
- **Objective:** Integrate the binary tree map with a Binary Search Tree (BST) to collect and organize clues.

#### Master Challenge: The Final Verdict
- **Objective:** Integrate three data structures: a **Binary Tree** for the map, a **BST** for ordered clue collection, and a **Hash Table** to link clues to suspects, culminating in a final accusation phase.
