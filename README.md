# 2D Racing Game & Custom C++ Engine

**A local two-player racing game built on a custom 2D game engine architected from scratch in C++.**

![Gameplay GIF of your racing game](https://github.com/zebenbrown/GameArchitectureFinal/blob/main/demo/GameArchDemo.gif%2017-08-01-807.gif)

## About The Project

*This project was a solo project until it was time for the final project. It was built using the Allegro library at first by myself, and then I merged projects with another student.

This project consists of two primary components:
1.  **The Engine:** A foundational 2D game engine built entirely by me. It features managers for graphics, audio, input, events, and a component-based architecture.
2.  **The Game:** A local two-player racing game built on top of the engine. The gameplay portion was developed in collaboration with a partner.

The core goal was to engineer a reusable engine and then demonstrate its capabilities by building a fun, playable game.

---

## Tech Stack

* **Language:** C++
* **Libraries:** SFML 3.0.0, JSON for Modern C++
* **Tools:** Visual Studio 2022, Git

---

## Key Features & Contributions

My key contributions were focused on the engine's architecture and core systems:

* **Engine Backend Migration:** Refactored the entire engine, migrating it from the Allegro library to SFML 3.0.0 for more modern and robust graphics, audio, and input handling.
* **Performance Optimization:** Implemented an object pooling system for the game's dynamic obstacles to minimize runtime memory allocation and prevent frame drops.
* **Data-Driven Architecture:** Built a JSON-based file system to manage game saves, user settings, and persistent high scores.

---

## Getting Started

To get a local copy up and running, follow these steps.

### Prerequisites

* Windows 10/11
* Visual Studio 2022 with the "Desktop development with C++" workload installed.

### Build Instructions

1.  Clone the repo.
2.  Open the `Final.sln` solution file in Visual Studio.
3.  **Important:** In the Solution Explorer, right-click on the **`Final`** project and select **"Set as Startup Project"**.
4.  Ensure the build configuration is set to `Debug` and `Win32`.
