# Raylib Physics Engine

A real-time 2D physics sandbox built in C++ using [Raylib](https://www.raylib.com/) and [raygui](https://github.com/raysan5/raygui). Spawn rigid bodies, place effectors, connect springs, and watch it all interact — live and interactively.

---

## Features

### Rigid Bodies
- Circular bodies with configurable **mass**, **size**, **restitution (bounce)**, **damping**, and **gravity scale**
- Three body types: **Dynamic**, **Kinematic**, and **Static**
- Bodies spawn at the mouse position with a randomized initial velocity direction
- Color is randomly assigned per body

### World & Physics Simulation
- Global **gravity** vector (adjustable at runtime via GUI)
- Fixed-timestep simulation loop with **semi-implicit Euler integration** for stability
- **World bounds** collision with restitution — bodies bounce off the edges
- **Circle-circle collision detection** using squared distance vs. summed radii — only pairs where at least one body is Dynamic are tested
- **Position correction** proportional to inverse mass to separate overlapping bodies
- **Impulse resolution** using the contact normal and combined restitution, run **4 sub-steps per frame**
- Near-zero distance is handled with a small random jitter to avoid degenerate normals
- Acceleration is cleared each frame after integration

### Effectors
Place effectors by right-clicking. Each occupies a circular zone and affects bodies within it:

| Effector | Color | Behavior |
|---|---|---|
| **Point** | Pink / Lime | Repels or attracts bodies toward/from a center point |
| **Area** | Blue | Applies a directional force at a configurable angle |
| **Drag** | Purple | Applies a velocity-opposing force (damping) |
| **Gravitation** | Yellow | Simulates N-body gravitational attraction between bodies inside the zone |

Hold `Space` while placing a Point Effector to toggle between attract and repel modes.

### Springs
- Connect two bodies with a **Hooke's Law** spring
- Configurable **stiffness** and **damping**
- Rest length is automatically set to the distance between bodies at connection time
- Drag forces can also be applied interactively from the mouse cursor to a body (`Middle Click` + `Ctrl`)

### World Camera
- Custom camera with a **pixels-per-unit** scale and Y-axis flip (world Y-up, screen Y-down)
- `ScreenToWorld` / `WorldToScreen` coordinate conversion for all interactions

### GUI (raygui)
- Collapsible **Physics Controls** panel (toggle with `Tab`)
- Sliders for all body, spring, and effector parameters
- Dropdown selectors for body type and effector type
- **Simulate** toggle button and `S` key shortcut
- FPS target slider (10–120)
- Lavanda raygui style applied at startup

---

## Controls

| Input | Action |
|---|---|
| `Left Click` | Spawn a body at mouse position |
| `Space` + `Left Click (Hold)` | Spawn bodies continuously |
| `Right Click (Hold)` | Place an effector at mouse position |
| `Middle Click` | Select a body to start a spring connection |
| `Middle Click` (on second body) | Connect the two selected bodies with a spring |
| `Middle Click` + `Ctrl (Hold)` | Apply a spring force from cursor to selected body |
| `S` | Toggle simulation on/off |
| `Tab` | Toggle the Physics Controls panel |
| `Space` (while placing Point Effector) | Toggle attract/repel mode |

---

## Architecture

```
main.cpp                  — Window, input loop, GUI integration
world.cpp / world.h       — Simulation step, body/effector/spring management, collision
body.cpp / body.h         — Rigid body data and force application
integrator.h              — Euler integration methods (Explicit & Semi-Implicit)
worldCamera.cpp / .h      — Screen↔world coordinate transform with Y-flip
spring.cpp / spring.h     — Spring constraint with damping
collision.cpp / .h        — Circle-circle detection, position separation, impulse resolution
effectors/
  pointEffector.cpp       — Radial attract/repel
  areaEffector.cpp        — Directional force field
  dragEffector.cpp        — Velocity damping zone
  gravitationEffector.cpp — N-body gravitational attraction
gui_physics.h             — raygui panel layout and state struct
```

---

## Physics Details

### Integration
Uses **Semi-Implicit (Symplectic) Euler**:
```
velocity += acceleration * dt
velocity *= 1 / (1 + damping * dt)   // damping applied here
position += velocity * dt
```
This is more energy-conserving than Explicit Euler, making springs and collisions more stable.

### Force Modes
`Body::AddForce()` supports four modes (only affects Dynamic bodies):

| Mode | Effect |
|---|---|
| `Force` | Adds to acceleration scaled by inverse mass |
| `Impulse` | Directly changes velocity, scaled by inverse mass |
| `Acceleration` | Adds to acceleration (ignores mass) |
| `VelocityChange` | Directly changes velocity (ignores mass) |

### Spring Force
Uses Hooke's Law:  
`F = -k * (length - restLength)`  
with velocity-projected damping along the spring axis.

### Collision Resolution
Detection uses squared distance vs. summed radii for efficiency. Resolution is a two-pass process per sub-step:

1. **Separation** — pushes overlapping bodies apart along the contact normal, weighted by inverse mass so heavier bodies move less:
   ```
   separation = normal * (depth / totalInverseMass)
   bodyA.position += separation * bodyA.inverseMass
   bodyB.position -= separation * bodyB.inverseMass
   ```

2. **Impulse** — applies equal and opposite velocity changes, only if bodies are approaching (skipped if already separating):
   ```
   impulseMagnitude = -(1 + restitution) * relativeVelocity·normal / (1/mA + 1/mB)
   ```
   Restitution is the **sum** of both bodies' restitution values, so two bouncy bodies amplify each other.

### Gravitation Effector
Computes pairwise N-body attraction for all bodies inside the zone:  
`F = strength * (mA * mB) / d²`  
with a minimum distance clamp of 1.0 to avoid singularities.

---

## Dependencies

- [Raylib](https://www.raylib.com/) — window, rendering, input
- [raygui](https://github.com/raysan5/raygui) — immediate-mode GUI
- [raymath](https://github.com/raysan5/raylib/blob/master/src/raymath.h) — Vector2 math
- C++17 or later

---
