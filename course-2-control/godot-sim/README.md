# 🎮 Godot Kinematics & PID Simulator

This directory contains the Godot-based simulation engine for visualizing physical kinematics and closed-loop control algorithms before running them on hardware.

## 🎯 Objectives
1. **Kinematics Engine:**
   - 2D/3D forward and inverse kinematics visualization.
   - Dynamic joint rotation constraints.
2. **PID Visualization:**
   - Graphical plot of target setpoint, current output, and error margins.
   - Interactive slider controls to tune $K_p$, $K_i$, and $K_d$ variables in real-time.
   - External data binding to stream simulation variables over Serial/UDP.

## 🚀 Future Setup
- Create a Godot 4.x project in this directory.
- Implement GDScript files for the PID mathematical model:
  $$u(t) = K_p e(t) + K_i \int_0^t e(\tau) d\tau + K_d \frac{de(t)}{dt}$$
