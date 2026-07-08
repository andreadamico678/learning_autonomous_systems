# Target PID Hardware-in-the-loop (HIL)

This directory is dedicated to the target-side PID firmware and HIL test scripts. It bridges simulation configurations with physical actuator execution.

## Objectives
1. **Low-level PID Controller:**
   - C implementation of a discrete-time PID controller.
   - Fixed-point/floating-point mathematical optimization for Cortex-M4.
   - Integral windup protection (anti-windup clamping) and derivative noise filtering.
2. **HIL Interface:**
   - Receive motor telemetry and update setpoints from the Godot simulation via UART or Wi-Fi.
   - Profile performance metrics (execution time, jitter) of the feedback loop on target.

## PID Implementation Structure
The core PID logic will follow this algorithm structure:
- Calculate Error: $e_k = r_k - y_k$
- Proportional: $P = K_p \times e_k$
- Integral: $I = I_{prev} + K_i \times e_k \times dt$ (with anti-windup clamping)
- Derivative: $D = K_d \times \frac{e_k - e_{prev}}{dt}$
- Output: $u_k = P + I + D$
