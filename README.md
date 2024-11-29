# WiFi Simulator (WiFi 4, WiFi 5, WiFi 6)

## Overview
This project provides simulations for **WiFi 4 (802.11n)**, **WiFi 5 (802.11ac)**, and **WiFi 6 (802.11ax)**. Each protocol is modeled with a focus on their respective communication features:

- **WiFi 4**: Simulates the **CSMA/CA** (Carrier Sense Multiple Access with Collision Avoidance) protocol for managing packet transmission in the network.
- **WiFi 5**: Simulates **MU-MIMO** (Multi-User, Multiple Input, Multiple Output), enabling simultaneous data transmission to multiple users.
- **WiFi 6**: Simulates **OFDMA** (Orthogonal Frequency Division Multiple Access), allowing the division of the channel into smaller sub-channels for parallel communication.

Each simulation computes key network performance metrics, such as **throughput**, **average latency**, and **maximum latency**, under varying user loads.

## Project Files

### 1. **WiFi4Simulator.cpp** (WiFi 4 - CSMA/CA)

- **Protocol**: CSMA/CA (Carrier Sense Multiple Access with Collision Avoidance)
- **Features**:
  - Random backoff for users.
  - Single user access at a time.
  - **Throughput and Latency Calculation**: Calculates throughput (Mbps) and latency (ms).
  - **Packet Transmission**: Simulates transmission of 1 KB packets.

### 2. **WiFi5Simulator.cpp** (WiFi 5 - MU-MIMO)

**WiFi 5** uses **MU-MIMO (Multi-User, Multiple Input, Multiple Output)** technology, which enables simultaneous data transmission to multiple users by utilizing multiple antennas at both the access point (AP) and user devices.

- **Protocol**: MU-MIMO (Multi-User MIMO)
- **Features**:
  - **Simultaneous Transmission**: The AP can serve multiple users concurrently.
  - **CSI (Channel State Information)**: Each user sends their CSI to the AP, which adjusts transmission strategies based on the data.
  - **Round-Robin Scheduling**: Users are scheduled in a round-robin manner to avoid collisions.
  - **15 ms Parallel Communication Slot**: Once CSI is collected, users communicate in parallel for 15 ms.
  - **Throughput and Latency**: Calculates throughput and latency under different loads (e.g., 1 user, 10 users, 100 users).

### 3. **WiFi6Simulator.cpp** (WiFi 6 - OFDMA)

**WiFi 6** uses **OFDMA (Orthogonal Frequency Division Multiple Access)**, which splits the channel into smaller sub-channels. This allows multiple users to communicate simultaneously on different sub-channels, increasing network efficiency and reducing contention.

- **Protocol**: OFDMA (Orthogonal Frequency Division Multiple Access)
- **Features**:
  - **Sub-Channel Allocation**: The 20 MHz WiFi channel is divided into smaller sub-channels (e.g., 2 MHz, 4 MHz, or 10 MHz).
  - **Parallel Communication**: Each user communicates on a dedicated sub-channel for 5 ms, maximizing parallelism and reducing contention.
  - **Round-Robin Scheduling**: Users are scheduled in a round-robin manner, and the AP allocates sub-channels based on current load.
  - **Throughput and Latency**: Calculates throughput and latency for multiple users under various sub-channel allocations.

---

## Features

### WiFi 4 (CSMA/CA)
- **Random backoff times** for each user to avoid collision.
- **Single-user access**: Only one user can transmit at any given time.
- **Throughput and latency calculations** based on total transmitted data and time taken.
- **Transmission of 1 KB packets**.

### WiFi 5 (MU-MIMO)
- **Multiple users transmit simultaneously** using **multi-user MIMO**.
- **CSI (Channel State Information)** is collected for each user and used by the AP to optimize transmission.
- **Round-robin scheduling** ensures fair transmission.
- **15 ms parallel communication slot** allows multiple users to transmit data simultaneously.

### WiFi 6 (OFDMA)
- **OFDMA (Orthogonal Frequency Division Multiple Access)** splits the 20 MHz channel into smaller sub-channels (2 MHz, 4 MHz, or 10 MHz).
- **Parallel communication for up to multiple users** across different sub-channels.
- **Round-robin scheduling** for users, optimizing the usage of available resources.
- **5 ms sub-channel communication slot**.
make file run command
---
Build the Project:
The default target builds the project by compiling source files into object files and linking them into the executa
 make
Running the Simulation:
Once the project is compiled, you can run the simulation by executing the respective binary for WiFi 4, WiFi 5, or WiFi 6.
 ./WiFiSimulator
Clean build files: To clean the build directory (removes compiled object files and executables):
 make clean
Optimized build: To build the project with optimization enabled:
 make optimized