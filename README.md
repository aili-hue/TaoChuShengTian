# TaoChuShengTian（逃出生天）

> 一个基于 **UE5.4** 的第三人称逃生游戏练习项目 | C++ + Blueprint 混合开发实战

[![](https://img.shields.io/badge/Engine-Unreal%205.4-313131?style=flat-square&logo=unrealengine)](https://www.unrealengine.com/)
[![](https://img.shields.io/badge/Language-C%2B%2B%20%26%20Blueprint-00a8e8?style=flat-square)](https://github.com/aili-hue/TaoChuShengTian)
[![](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

## 📖 项目简介

这是一个**单机逃生游戏 Demo**，完全从零自学 UE5 5 个月后的第一个完整项目。玩家需要在动态场景中：
- 🔍 寻找并装配武器
- 🎒 管理背包物品
- 🚪 与环境交互（开门、躲避等）
- ⚔️ 对抗敌人
- 🏃 找到逃生出口

**设计初心**：不是为了做一个"完整商业游戏"，而是在真实项目中**实践所有学到的知识**。所有核心逻辑用 C++ 实现，部分 UI 和动画通过 Blueprint 实现。

---

## ✨ 核心功能一览

| 功能模块 | 描述 |
|---------|------|
| **角色控制** | 基于增强输入系统，支持移动、跳跃、加速、蹲下 |
| **视角系统** | 一/三人称平滑切换，武器状态自动调整视角 |
| **背包系统** | 组件 + 数据资产驱动，支持拾取、存储、切换 |
| **武器系统** | 动态生成、装配、碰撞判定、动画蒙太奇驱动 |
| **交互系统** | Overlap 检测 + 委托通知，进门时限制操作并调整状态 |
| **血量系统** | 组件化管理，伤害计算与 UI 联动 |
| **反馈系统** | 血条、伤害数字、动画反馈 |

---

## 🛠 技术栈

```
引擎          Unreal Engine 5.4
语言          C++ (核心逻辑 90%) + Blueprint (UI/动画)
架构          组件化、数据驱动
关键特性      • 增强输入系统 (Enhanced Input)
              • 委托与接口通信
              • 弱指针与垃圾回收管理
              • 定时器与动画蒙太奇同步
              • 物理碰撞与 Sweep 检测
```

---

## 📁 项目结构

```
Source/TaoChuShengTian/
├── JueSe/                    # 角色类
│   └── My_Character.h/.cpp   # 玩家角色主类
├── Actor_WuPin/              # 物品基类
├── BeiBao/                   # 背包组件
├── HP/                       # 血量组件
├── door/                     # 门与交互系统
├── MyPrimaryDataAsset/       # 物品数据资产
└── ...
```

> ℹ️ 文件和变量命名目前在从中文拼音向英文过渡。

---

## 🎮 主要学习收获

通过这个项目，我深入实践了：

- ✅ **C++ 与 Blueprint 协同开发** - 性能关键路径用 C++，UI/动画用 Blueprint
- ✅ **组件化架构设计** - 背包、血量等独立组件的高内聚低耦合实现
- ✅ **委托与接口通信** - 组件间的事件驱动解耦
- ✅ **内存管理与 GC** - 弱指针、智能指针的正确使用
- ✅ **定时器与动画同步** - 攻击、移动动画的精确时序控制
- ✅ **状态冲突调试** - 排查快速操作导致的卡死、穿模问题

---

## ⚠️ 已知问题与改进计划

| 问题 | 优先级 | 计划方案 |
|------|--------|--------|
| 攻击判定缺少 Sweep，快速挥击可能穿模 | 🔴 高 | 使用 SweepSingleByChannel 重构 |
| 部分逻辑（速度管理）耦合度高 | 🟡 中 | 完全组件化解耦 |
| 变量命名中英混合 | 🟡 中 | 全量重构为英文命名 |
| 缺少音效与完整 UI 反馈 | 🟢 低 | 后续迭代计划 |
| 无演示视频 | 🟢 低 | 计划录制 1-2 分钟 Demo |

---

## 📦 如何使用

```bash
# 1. 克隆项目
git clone https://github.com/aili-hue/TaoChuShengTian.git

# 2. 用 UE5.4 打开 .uproject 文件
# 3. 编译 C++ 项目（需要安装 Visual Studio）
# 4. 点击 Play 开始游戏
```

**环境要求**：
- Unreal Engine 5.4+
- Visual Studio 2022（C++ 编译）
- Windows 10/11 或 macOS

---

## 💬 经验分享

如果你也在学习 UE5，这个项目可能能帮你：
- 看到**实战中的组件化设计**是什么样的
- 理解 **C++ 与 Blueprint 如何配合**才能又快又稳
- 学习**常见的游戏逻辑如何从零实现**

欢迎提 Issue、讨论、或者 Fork 后自己改进！

---

## 📞 联系方式

- **GitHub**: [@aili-hue](https://github.com/aili-hue)
- **B站/知乎**: 待补充
- **Email**: 欢迎在 Issue 中交流

---

## 🙏 致谢

感谢所有开源教程和 UE 社区的无私分享。

这个项目还有许多不成熟之处，但正是**在不断修补和重构的过程中**，我学到了最多的东西。希望它也能对你的学习有所帮助。

---

**Last Updated**: 2026-06-13
