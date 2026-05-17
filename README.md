# MeshHat

> A standard Raspberry Pi HAT with everything needed to run [MeshCore](https://meshcore.io) or [Meshtastic](https://meshtastic.org) — right out of the box.

---

## Overview

MeshHat is a Raspberry Pi HAT (Hardware Attached on Top) that integrates all the components required to join or extend a LoRa mesh network. Whether you're building an internet gateway, running automations, or deploying a remote node, MeshHat gives you a single-board solution with no additional wiring.

---

## Features

| Component | Details |
|---|---|
| **LoRa Module** | E22P — 1W output power |
| **Radio Driver MCU** | RP2040 |
| **Programming Interface** | SWD connector (for RP2040 firmware updates) |
| **Host Interface** | UART0 (Raspberry Pi ↔ RP2040) |
| **Remote Flashing** | SWD lines routed to Raspberry Pi GPIO |

---

## How It Works

Communication between the RP2040 (which handles radio duties) and the Raspberry Pi host runs over **UART0**. The RP2040 can also be **reflashed remotely** via the SWD lines connected to the Pi — no physical access to the board required for firmware updates.

---

## Example Applications

- **Internet Gateway** — Bridge a LoRa mesh network to the internet
- **Mesh Automations** — Trigger actions based on mesh messages or node events
- **Remote Sensor Node** — Deploy a standalone, Pi-powered mesh node

---

## Compatible Firmware

- [MeshCore](https://meshcore.io)
- [Meshtastic](https://meshtastic.org)

---

## Getting Started

> ⚠️ *Documentation in progress. Pinout diagrams, setup guides, and firmware flashing instructions coming soon.*

---

## Contributing

Pull requests and issue reports are welcome. If you've built something with MeshHat, we'd love to hear about it.

---

## License

*To be specified.*
