# 🧠 Autonomous Systems Development Workspace

Welcome to your master tracking board for the **Autonomous Systems Curriculum**. This workspace bridges low-level hardware architecture, real-time operating systems (RTOS), control theory, and kinematic simulations.

---

## 🛠️ Hardware Ecosystem
- **Low-Level Sandbox:** **STM32 NUCLEO-F401RE** (ARM Cortex-M4) + **X-NUCLEO-IQS4A1A** Shield.
- **Production RTOS Platform:** **nRF7002 DK** (Wi-Fi 6 Companion Board).
- **Host System:** Fedora Laptop via ST-Link/V2-1 interface.

---

## 🗺️ Curriculum Progress Board

### 📘 Course 1: Autonomous Systems Architecture
*Focuses on hardware abstraction, register-level bare-metal programming, sensor interfaces, and middleware integration.*

| Module / Milestone | Description | Target Hardware | Status | Links |
| :--- | :--- | :---: | :---: | :---: |
| **1. Bare-Metal UART Driver** | Register-level USART2 driver for serial feedback. | STM32 Nucleo | 🟢 Completed | [stm32-baremetal](./course-1-architecture/stm32-baremetal/) |
| **2. Bare-Metal Interrupts** | NVIC setup, external interrupt routines, timer baselines. | STM32 Nucleo | 🟡 In Progress | [stm32-baremetal](./course-1-architecture/stm32-baremetal/) |
| **3. Zephyr RTOS Setup** | CMake/Kconfig workspace, multithreaded blinking LED. | nRF7002 DK | ⚪ Not Started | [nrf7002dk-zephyr](./course-1-architecture/nrf7002dk-zephyr/) |
| **4. RTOS IPC & Threads** | Thread synchronization, queues, and mutexes for sensor reading. | nRF7002 DK | ⚪ Not Started | [nrf7002dk-zephyr](./course-1-architecture/nrf7002dk-zephyr/) |
| **5. Wi-Fi & Middleware** | Connecting nRF7002 to local AP and transmitting telemetry. | nRF7002 DK | ⚪ Not Started | [nrf7002dk-zephyr](./course-1-architecture/nrf7002dk-zephyr/) |

---

### 📙 Course 2: Spatial Intelligence & Control
*Focuses on kinematics, mathematical control loops, closed-loop PID systems, and simulations.*

| Module / Milestone | Description | Environment | Status | Links |
| :--- | :--- | :---: | :---: | :---: |
| **1. Kinematics Simulation** | Godot-based forward and inverse kinematics visualization. | Godot Engine | ⚪ Not Started | [godot-sim](./course-2-control/godot-sim/) |
| **2. PID Simulator** | Dynamic visual control loops adjusting PID parameters on-screen. | Godot Engine | ⚪ Not Started | [godot-sim](./course-2-control/godot-sim/) |
| **3. Hardware-in-the-Loop** | Running target-level PID loops matching simulation telemetry. | STM32 / nRF | ⚪ Not Started | [target-pid](./course-2-control/target-pid/) |

---

## ⚡ Quick-Start Reference

### Bare-Metal STM32 Compilation & Flashing
```bash
cd course-1-architecture/stm32-baremetal
make        # Compile and generate firmware.bin
make flash  # Write to Nucleo-F401RE board
```

### Serial Communication
Connect to the Virtual COM port at `115200` baud:
```bash
screen /dev/ttyACM0 115200
```

> [!NOTE]
> Make sure your udev rules are properly configured to allow non-root access to `/dev/ttyACM0` and the ST-Link device.

> [!IMPORTANT]
> The STM32 serves as our low-level register-level sandbox, while the nRF7002 DK acts as our multi-threaded RTOS network node. Telemetry from the STM32 controls will interface with the Godot simulation via serial/Wi-Fi connection.
