# HEKT Console Engine
![Static Badge](https://img.shields.io/badge/EnTT-v3.16.0-ECS?style=flat-square&logo=developmentcontainers&logoColor=white&labelColor=black&color=white)
![Static Badge](https://img.shields.io/badge/C%2B%2B-v20-Standard?style=flat-square&logo=c%2B%2B&logoColor=white&labelColor=purple&color=white)
![Static Badge](https://img.shields.io/badge/Terminal-Windows-CMD?style=flat-square&logo=iterm2&logoColor=white&labelColor=black&color=white)

    ===================================================
     _    _ ______ _  _ _______  _____             _ 
    | |  | |  ____| |/ /__   __|/ ____|           | |
    | |__| | |__  | ' /   | |  | |     ___  _ __  | |
    |  __  |  __| |  <    | |  | |    / _ \| '_ \ | |
    | |  | | |____| . \   | |  | |___| (_) | | | ||_|
    |_|  |_|______|_|\_\  |_|   \_____\___/|_| |_|(_)
                                                     
                     CONSOLE ENGINE v1.0
    ===================================================

**HEKT Console Engine** is a fast, lightweight 2D game engine built in C++20 designed specifically for text-based and ASCII games using the Windows Console. 

Built with modern C++ and an Entity Component System (ECS) architecture, it abstracts away the complex and verbose Windows Console API into an easy-to-use framework for rapid game development.

### Key Features
* **Modern ECS Architecture:** Powered by the open-source `EnTT` library for highly performant and modular entity-component management (Transform, Sprite, Velocity, etc.).
* **Advanced Console Rendering:** Uses custom double-buffered screen handles and `WriteConsoleOutput` for flicker-free, high-performance rendering.
* **Robust Viewport Management:** Seamlessly handles console window resizing, viewport anchoring, and prevents scrollbar ghosting/artifacts.
* **Input Management:** Intuitive keybinding and input polling system with application event loops (`OnStart`, `OnUpdate`).
* **Clear Debugging:** Built-in debug modes and straightforward toggles (e.g., `DebugOn()`) to quickly isolate and troubleshoot engine or game logic issues.

Perfect for rendering terminal games, UI-heavy console applications, or as a learning tool for C++ engine architecture.

### How to Use This Engine
1. Clone the repository and open `HEKTConsoleEngine.sln` in Visual Studio.
2. Build the solution so both `Engine` and `Sandbox` are available.
3. Start working in `Sandbox/src/main.cpp`. This is the game entry point and the best place to wire your own gameplay logic.
4. Use `Application` to register callbacks:
   - `OnStart` for initialization
   - `OnUpdate` for per-frame gameplay logic
5. Create entities through `App.entityManager`, then attach components such as `TransformComponent`, `SpriteComponent`, `VelocityComponent`, `TagComponent`, and `ColliderComponent`.
6. Load ASCII sprite files from `Sandbox/assets/sprites/` with `App.spriteParser.ParseSpriteComponent(...)`.
7. Set the keys you want to read with `App.inputSystem.SetUsingKeys(...)`, then poll them inside `OnUpdate`.
8. Enable debug or quit behavior with `App.DebugOn(...)` and `App.QuitOn(...)`.

Minimal sandbox setup:

```cpp
HEKTConsoleEngine::Application App;

void Start() {
    // Create entities and attach components here.
}

void Update(float deltaTime) {
    // Handle input, movement, collision, and game logic here.
}

int main() {
    App.OnStart = Start;
    App.OnUpdate = Update;
    App.Run();
    return 0;
}
```

If you are extending the engine itself, keep gameplay code in `Sandbox/src` and engine-level changes in `Engine/src` and `Engine/include`.
