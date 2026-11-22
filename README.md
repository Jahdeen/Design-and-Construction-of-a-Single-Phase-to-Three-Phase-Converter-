# Design and Construction of a Single-Phase to Three-Phase Converter

A microcontroller-driven, solid-state single-phase to three-phase AC converter designed to generate a balanced **220V, 50Hz three-phase AC supply** from a standard single-phase utility grid. 

Developed as a B.Eng. Final Year Project at the Department of Electrical and Electronics Engineering, **Abubakar Tafawa Balewa University (ATBU), Bauchi**.

---

## 📖 Overview
In many rural, agricultural, and small-scale industrial regions, utility distribution is limited to single-phase power due to the high cost of three-phase infrastructure. Traditional rotary phase converters are bulky, noisy, and require frequent mechanical maintenance, while passive capacitor-based converters suffer from severe phase imbalance under varying loads.

This project provides a compact, silent, and cost-effective **solid-state static phase converter** capable of driving low-to-medium power three-phase loads (up to **100W**) with precise **120° phase displacement** and **>83% conversion efficiency**.

---

## ⚙️ System Architecture

The hardware is organized into five modular stages:

1. **Step-Down & Rectification Stage:** Steps down 220V AC (50Hz) mains to an isolated 12V AC supply, rectified via a **KBPC3510** full-wave bridge rectifier and smoothed with a 2200µF electrolytic capacitor (~15V DC bus).
2. **Dual Linear Voltage Regulation:** 
   - **LM7812** provides a regulated **12V DC** rail for the gate driver supply (`VCC`) and cooling fans.
   - Cascaded **LM7805** steps 12V down to a clean **5V DC** logic rail for the microcontroller and gate driver logic (`VDD`).
3. **Microcontroller Control Stage:** An **ATmega328P** (clocked at 16 MHz) generates six custom Sinusoidal Pulse Width Modulation (SPWM) control signals shifted by 120° (6.67 ms at 50Hz), incorporating dead-time delays to prevent shoot-through.
4. **Gate Driver & H-Bridge Inverter Stage:** Six **IR2110** high/low-side gate drivers (with `FR107` bootstrap diodes and `0.22µF` bootstrap capacitors) drive three independent full-bridge (H-bridge) inverters built with **IRFZ44N** N-channel power MOSFETs.
5. **Step-Up Magnetic Stage:** Three independent 12V-to-220V step-up transformers filter the high-frequency PWM waveforms via primary winding inductance and elevate the voltage to a balanced three-phase output (Star/Wye or Delta configurable).

---

## 📊 Technical Specifications

| Parameter | Specification |
| :--- | :--- |
| **Input Voltage** | 220 V AC, 50 Hz (Single-Phase) |
| **Output Voltage** | 220 V AC Phase-to-Neutral / 380–415 V Line-to-Line |
| **Output Frequency** | 50 Hz |
| **Phase Displacement** | 120° Electrical Degrees (6.67 ms delay) |
| **Rated Output Power** | 100 W Max (33.33 W per phase) |
| **Conversion Efficiency** | > 83% |
| **Microcontroller** | ATmega328P @ 16 MHz |
| **Gate Drivers** | 6 × IR2110 (High/Low Side) |
| **Switching Devices** | 12 × IRFZ44N Power MOSFETs (4 per H-bridge) |

---

## 🔌 ATmega328P Pinout Configuration

| Phase | Phase Angle | Time Delay | High-Side Pin | Low-Side Pin |
| :--- | :--- | :--- | :--- | :--- |
| **Phase A** | 0° | 0.00 ms | Digital Pin **D5** | Digital Pin **D6** |
| **Phase B** | 120° | 6.67 ms | Digital Pin **D7** | Digital Pin **D8** |
| **Phase C** | 240° | 13.33 ms | Digital Pin **D9** | Digital Pin **D10** |

---

## 🛠️ Bill of Materials (Key Components)

* **Microcontroller:** 1 × ATmega328P + 16 MHz Crystal Oscillator + 2 × 22pF ceramic capacitors
* **Gate Drivers:** 6 × IR2110 ICs
* **MOSFETs:** 12 × IRFZ44N N-Channel HEXFETs (with aluminum heatsinks)
* **Voltage Regulators:** 1 × LM7812, 1 × LM7805
* **Rectifier:** 1 × KBPC3510 (35A, 1000V Bridge Rectifier)
* **Transformers:** 1 × 220V/12V (10A, 120VA) Step-Down; 3 × 12V/220V Step-Up
* **Passives & Diodes:** 
  * 12 × 10 Ω Gate Resistors, 12 × 10 kΩ Pull-down Resistors
  * 6 × FR107 Fast-Recovery Bootstrap Diodes
  * 6 × 0.22 µF MLCC Bootstrap Capacitors
  * 1 × 2200 µF Bulk Filter Capacitor, 22 µF & 0.1 µF Decoupling Capacitors

---

## 👥 Authors & Supervision

Authors:** Abdullahi Mujahideen Momoh,Elijah Emmanuel Edoh, Abdullahi Mujahideen Momoh, Israel Victor Onyedickachi, Joshua Bitrus Mabur, Yahaya Abdulrazak, Umar Adamu Gargawa, Umar Musa, and Yazid Idris Saleh
* **Supervisor:** Mal. Sani Sabo
* **Institution:** Department of Electrical and Electronics Engineering, Abubakar Tafawa Balewa University (ATBU), Bauchi, Nigeria (November 2026)

---

## ⚠️ Safety Warning
This circuit steps up low-voltage DC to **220V / 415V AC**. Ensure proper galvanic isolation, adequate heatsinking on MOSFETs/regulators, and insulated enclosures before energizing the step-up transformer stage.

