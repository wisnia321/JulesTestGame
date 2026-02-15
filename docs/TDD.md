# Project Jules - Technical Design Document

## 1. Introduction
Project Jules is a high-performance, next-generation racing game engine that combines the creative freedom of voxel-based worlds (à la Minecraft) with the photorealistic visuals and simulation-grade physics of modern racing titles (à la Forza Horizon).

## 2. Technology Stack
- **Language:** C++20 (migrating to C++23 as compiler support matures).
- **Graphics API:** Vulkan 1.3 (Primary), DirectX 12 Ultimate (Secondary/Xbox).
- **Architecture:** Data-Oriented Design using Entity Component System (ECS).
- **Build System:** CMake.
- **Physics:** Custom Soft-body Physics Engine.
- **Networking:** Authoritative Server with Client-Side Prediction.

## 3. Engine Architecture
### 3.1 Core Systems
The engine is built around a Data-Oriented Design philosophy to maximize cache coherence and performance.
- **ECS (Entity Component System):** The core framework for managing game objects. We will likely use a custom implementation or a high-performance library like `EnTT` or `Flecs` if applicable, but for this project, a custom tailored ECS might be necessary for voxel integration.
- **Memory Management:** Custom allocators (Linear, Pool, Stack) to minimize fragmentation and allocation overhead.
- **Job System:** Fiber-based task scheduler for parallelizing CPU-intensive tasks (physics, voxel generation).

### 3.2 Rendering (Voxel & Ray Tracing)
The rendering pipeline is designed for massive voxel worlds.
- **Sparse Voxel Octrees (SVO):** The primary structure for representing static terrain and buildings. SVOs allow for efficient ray traversal and level-of-detail (LOD) management.
- **Dynamic Voxelization:** Moving objects (vehicles, debris) are voxelized on-the-fly or use hybrid mesh-voxel representations.
- **Ray Tracing:**
    - **Global Illumination (GI):** Real-time GI using ray tracing against the SVO structure.
    - **Reflections & Shadows:** Hardware-accelerated ray tracing where available, with software fallbacks using SVO traversal.
- **Render Graph:** A frame graph architecture to manage resource barriers and pass dependencies automatically.

### 3.3 Physics Simulation
- **Soft-body Dynamics:** Vehicles are modeled as soft bodies using a mass-spring-damper network to simulate deformation and damage.
- **Tire Model:** A discrete tire model that interacts with individual voxels. This allows for realistic traction on varied terrain (mud, asphalt, ice) and physical deformation of the terrain (ruts, tire tracks).
- **Voxel Physics:** The world itself is physically interactive. Explosions or impacts can destroy voxels, requiring dynamic updates to the SVO and physics collision proxies.

### 3.4 Networking
- **Architecture:** Client-Server model with the server being the authority.
- **Server Meshing:** To support a massive open world, the world is divided into regions managed by different server instances, with seamless handovers.
- **State Synchronization:** Delta compression and snapshot interpolation for smooth movement.
- **Prediction:** Client-side prediction for vehicle physics to ensure responsiveness, with server reconciliation for anti-cheat and consistency.

## 4. Project Structure
The project follows a standard C++ directory structure:
```
ProjectJules/
├── docs/               # Documentation
├── src/
│   ├── Core/           # Engine core (Window, Input, Memory, Logger)
│   ├── Renderer/       # Vulkan/DX12 backend, SVO implementation
│   ├── Physics/        # Soft-body dynamics, Collision detection
│   ├── Network/        # Socket handling, Replication, Server logic
│   ├── ECS/            # Entity Component System implementation
│   └── Game/           # Gameplay logic (specific to Project Jules)
├── include/            # Public headers
├── shaders/            # HLSL/GLSL shaders
├── third_party/        # External libraries (GLFW, GLM, etc.)
└── CMakeLists.txt      # Build configuration
```

## 5. Development Roadmap
1.  **Phase 1: Foundation:** Basic engine loop, windowing, and Vulkan context.
2.  **Phase 2: Voxel Renderer:** Implementing SVO construction and basic ray casting.
3.  **Phase 3: Physics Core:** Basic rigid body and soft body simulation.
4.  **Phase 4: Integration:** Driving a soft-body car on a voxel terrain.
5.  **Phase 5: Multiplayer:** Basic networking and state replication.
6.  **Phase 6: Optimization & Polish:** multithreading, LODs, and graphical fidelity.
