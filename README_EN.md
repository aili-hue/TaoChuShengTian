# TaoChuShengTian (Escape from Heaven)

**[中文](README.md) | [English](README_EN.md)**

> A third-person escape game practice project based on **UE5.4** | C++ + Blueprint hybrid development

[![](https://img.shields.io/badge/Engine-Unreal%205.4-313131?style=flat-square&logo=unrealengine)](https://www.unrealengine.com/)
[![](https://img.shields.io/badge/Language-C%2B%2B%20%26%20Blueprint-00a8e8?style=flat-square)](https://github.com/aili-hue/TaoChuShengTian)
[![](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

## 📖 Project Overview

This is a **complete standalone escape game Demo**, the first complete project after self-learning UE5 for 5 months from scratch.

**Core Gameplay**: Players are trapped in a dynamic scene and need to escape through the following steps:
- 🔍 **Search & Assemble Weapons** - Find scattered weapon components in the environment and assemble them into usable weapons
- 🎒 **Backpack Management** - Implement item pickup, storage, and quick-switch mechanics
- 🚪 **Environmental Interaction** - Interact with doors and obstacles to create escape opportunities
- ⚔️ **Combat & Evasion** - Use weapons to fight enemies or choose to avoid them
- 🏃 **Find Escape Exit** - Locate and reach a safe place within limited time

**Design Philosophy**:
- Not about creating a "complete commercial game", but **practicing all learned knowledge in real projects**
- All core logic implemented in **C++** (approximately 90%), with some UI and animation supplemented by **Blueprint**
- Emphasis on **component architecture** and **code reusability** rather than asset stacking

---

## ✨ Core Features Overview

| Module | Description | Technical Highlights |
|--------|-------------|----------------------|
| **Character Control** | Support movement, jumping, sprinting, crouching and other basic operations | Enhanced Input System event-driven |
| **Camera System** | Smooth first/third-person switching, automatic camera adjustment based on weapon state | Camera interpolation + state machine |
| **Backpack System** | Component + data asset driven, support pickup, storage, quick switch | Configuration-based item definition, easy to extend |
| **Weapon System** | Dynamic generation, assembly, collision detection, animation montage driven | Montage callback synchronized with damage calculation |
| **Interaction System** | Overlap detection + delegate notification, operation restriction when entering doors | Non-blocking event communication |
| **Enemy AI** | Four-stage state machine: patrol, discover, chase, attack | Distance sensing + collision detection integration |
| **Health System** | Component-based management, damage calculation with real-time UI sync | Delegate pattern decouples game logic |
| **Feedback System** | Health bar, damage numbers, animation feedback, screen shake | Multi-channel comprehensive feedback improves experience |

---

## 🛠 Technology Stack

```
Engine         Unreal Engine 5.4
Language       C++ (Core Logic 90%) + Blueprint (UI/Animation)
Architecture   Component-based, Data-driven
Key Features   • Enhanced Input System
               • Delegates & Interfaces Communication
               • Weak Pointers & Garbage Collection Management
               • Timers & Animation Montage Synchronization
               • Physics Collision & Sweep Detection
               • State Machine Design Pattern
```

---

## 📁 Project Structure

```
Source/TaoChuShengTian/
├── JueSe/                    # Character Classes
│   └── My_Character.h/.cpp   # Player Character Main Class
├── Actor_WuPin/              # Item Base Class
├── BeiBao/                   # Backpack Component
├── HP/                       # Health Component
├── door/                     # Door & Interaction System
├── MyPrimaryDataAsset/       # Item Data Assets
└── ...
```

> ℹ️ File and variable naming are currently transitioning from Chinese Pinyin to English.

---

## 🎮 Key Learning Outcomes

Through this project, I have gained deep hands-on experience with:

- ✅ **C++ & Blueprint Collaborative Development** - C++ for performance-critical paths, Blueprint for UI/animation
- ✅ **Component Architecture Design** - High-cohesion, low-coupling implementation of independent components like backpack and health
- ✅ **Delegate & Interface Communication** - Event-driven decoupling between components
- ✅ **Memory Management & GC** - Correct usage of weak pointers and smart pointers
- ✅ **Timer & Animation Synchronization** - Precise timing control for attack and movement animations
- ✅ **State Conflict Debugging** - Troubleshooting freezing and clipping issues caused by rapid operations
- ✅ **Data-Driven Design** - Separating game data from logic through configuration assets

---

## 📦 How to Use

```bash
# 1. Clone the project
git clone https://github.com/aili-hue/TaoChuShengTian.git

# 2. Open .uproject file with UE5.4
# 3. Compile C++ project (requires Visual Studio installation)
# 4. Click Play to start the game
```

**Requirements**:
- Unreal Engine 5.4+
- Visual Studio 2022 (for C++ compilation)
- Windows 10/11 or macOS

---

## 💬 Experience Sharing

If you're also learning UE5, this project might help you:
- See what **component architecture design looks like in real projects**
- Understand **how C++ and Blueprint work together** for speed and stability
- Learn **how to implement common game logic from scratch**
- Master **core design patterns like state machines, delegates, and data-driven design**

Welcome to submit Issues, discussions, or Fork and make your own improvements!

---

## 📞 Contact

- **GitHub**: [@aili-hue](https://github.com/aili-hue)
- **Bilibili/Zhihu**: Coming soon
- **Email**: Feel free to communicate in Issues

---

## 🙏 Acknowledgments

Thanks to all open-source tutorials and the UE community for their generous sharing.

This project still has many immature aspects, but it is precisely **in the process of continuous fixing and refactoring** that I learned the most. Hope it also helps with your learning journey.

---

**Last Updated**: 2026-06-21
