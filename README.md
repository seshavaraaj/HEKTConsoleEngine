# HEKT Console Engine
![Static Badge](https://img.shields.io/badge/EnTT-v3.16.0-ECS?style=flat-square&logo=developmentcontainers&logoColor=white&labelColor=black&color=white)
![Static Badge](https://img.shields.io/badge/C%2B%2B-v20-Standard?style=flat-square&logo=c%2B%2B&logoColor=white&labelColor=purple&color=white)
![Static Badge](https://img.shields.io/badge/Terminal-Windows-CMD?style=flat-square&logo=iterm2&logoColor=white&labelColor=black&color=white)

**HEKT Console Engine** is a fast, lightweight 2D game engine built in C++20 designed specifically for text-based and ASCII games using the Windows Console. 

Built with modern C++ and an Entity Component System (ECS) architecture, it abstracts away the complex and verbose Windows Console API into an easy-to-use framework for rapid game development.

### Key Features
* **Modern ECS Architecture:** Powered by the open-source `EnTT` library for highly performant and modular entity-component management (Transform, Sprite, Velocity, etc.).
* **Advanced Console Rendering:** Uses custom double-buffered screen handles and `WriteConsoleOutput` for flicker-free, high-performance rendering.
* **Robust Viewport Management:** Seamlessly handles console window resizing, viewport anchoring, and prevents scrollbar ghosting/artifacts.
* **Input Management:** Intuitive keybinding and input polling system with application event loops (`OnStart`, `OnUpdate`).
* **Clear Debugging:** Built-in debug modes and straightforward toggles (e.g., `DebugOn()`) to quickly isolate and troubleshoot engine or game logic issues.

Perfect for rendering terminal games, UI-heavy console applications, or as a learning tool for C++ engine architecture.
