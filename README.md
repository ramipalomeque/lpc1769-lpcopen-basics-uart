# LPC1769 LPCOpen Basics: UART Example

[![MCU](https://shields.io)](https://nxp.com)
[![SDK](https://shields.io)](https://nxp.com)
[![IDE](https://shields.io)](https://nxp.com)
[![Language](https://shields.io)](https://wikipedia.org)

A clean, production-ready example demonstrating how to configure, transmit, and receive data using the Universal Asynchronous Receiver-Transmitter (**UART**) peripheral on the **NXP LPC1769** microcontroller with **LPCOpen v2.xx** firmware libraries inside **MCUXpresso IDE**.

This repository serves as a starter guide for firmware engineers learning asynchronous serial communication and low-level peripheral driver integration on the Cortex-M3 architecture.

---

## 🚀 Key Features

* **UART Peripheral Initialization:** Step-by-step baud rate calculation and configuration (e.g., 115200 bps, 8N1).
* **Transmission & Reception:** Basic polling or interrupt-driven data handling loop for serial communication.
* **Pin Muxing Integration:** Proper setup of target GPIO pins for TX and RX alternate functions.
* **Modular Codebase:** Clean separation of concerns between header (`inc/`) and source (`src/`) files.

---

## 🛠️ Hardware & Software Requirements

### Hardware
* **Microcontroller:** NXP LPC1769 (Cortex-M3)
* **Development Board:** LPCXpresso LPC1769 board (or custom hardware layout)
* **Debugger:** Integrated LinkServer probe, CMSIS-DAP, or J-Link
* **Extras:** USB-to-UART converter (FTDI) or terminal monitor to view serial output.

### Software
* **IDE:** MCUXpresso IDE (v11.x or newer recommended)
* **Software Library:** LPCOpen Platform v2.xx for LPC17xx family
* **Serial Terminal:** Putty, Tera Term, or the built-in MCUXpresso IDE Terminal.

---

## 📁 Repository Structure

```text
├── inc/               # C Header files (.h) with register mappings and function prototypes
├── src/               # C Source files (.c) containing main loop and UART peripheral setup
├── .cproject          # MCUXpresso IDE compiler and toolchain configurations
├── .project           # MCUXpresso project structure markers
└── .gitignore         # Tailored ignore paths for Eclipse/MCUXpresso build artifacts
```

---

## 💻 How to Import and Run

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/ramipalomeque/lpc1769-lpcopen-basics-uart.git
   ```
2. **Import into MCUXpresso:**
   * Open MCUXpresso IDE.
   * Go to **File > Import > General > Existing Projects into Workspace**.
   * Select the cloned repository root folder as the root directory.
   * Ensure `lpc1769_lpcOpen_basicsUART` (or your project name) is checked, then click **Finish**.
3. **Link LPCOpen Library:**
   * Make sure your workspace contains the `lpc_chip_175x_6x` base library from NXP.
   * Right-click the project -> **Properties > C/C++ Build > Settings > MCU Linker > Libraries** to verify paths if necessary.
4. **Build & Debug:**
   * Click the **Build** (Hammer) icon to compile.
   * Click the **Debug** (Blue Bug) icon to flash the `.axf` bin onto your LPC1769 board.

---

## 🔍 Code Walkthrough (Brief Overview)

The firmware performs the following operational loop:
1. **System Initialization:** `SystemInit()` configures internal core clocks.
2. **Peripheral Setup:** `Chip_UART_Init()` boots up the target UART block and sets the baud rate.
3. **Pin Configuration:** Maps the pins (like P0.2 and P0.3) to operate as `TXD` and `RXD`.
4. **Data Stream:** Uses functions like `Chip_UART_SendBlocking()` to transmit character buffers, or checks status flags to parse incoming serial commands.

---

## 🏷️ Meta Keywords & SEO Tags
`lpc1769-uart-example` | `lpcopen-uart-sample` | `mcuxpresso-uart-project` | `cortex-m3-serial-communication` | `nxp-lpc1769-uart-tutorial` | `embedded-c-uart`
