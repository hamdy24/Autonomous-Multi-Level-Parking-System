# Automated Multi-Level Parking System
---
![Project Logo]([link-to-your-logo-or-relevant-image](https://www.google.com/url?sa=i&url=https%3A%2F%2Ftheautomatedparkingcompany.com%2Fmultilevel-car-parking-system-cost-a-sustainable-solution-for-urban-parking-challenges%2F&psig=AOvVaw3-SsQ91WVHK9mzg8uqlch-&ust=1721564720308000&source=images&cd=vfe&opi=89978449&ved=0CBEQjRxqFwoTCPiHhsjOtYcDFQAAAAAdAAAAABAE))

## Overview
The Automated Multi-Level Parking System is a cutting-edge project designed to streamline parking management using advanced technologies such as Vehicle-to-Vehicle (V2V) communication and Firmware Over-The-Air (FOTA) updates. This project leverages the STM32 microcontroller and NodeMCU to create a robust, efficient, and scalable solution for modern parking challenges.

## Features
- **Advanced V2V Communication:** Enables seamless data exchange and coordination between the car lifting robot and the elevator robot.
- **FOTA Updates:** Allows for remote firmware updates, ensuring the system remains up-to-date and secure without physical intervention.
- **ESP32 Camera Integration:** Captures plate numbers to add a layer of automation and functionality.
- **Custom Firmware and Bootloader:** Developed MCAL, HAL, and bootloader for STM32, along with NodeMCU gateway code for secure data transmission.
- **PID Control:** Ensures precise movement and positioning of robots for accurate parking operations.

## Project Components
### Hardware
- **STM32 Microcontroller:** Central control unit for real-time operations.
- **NodeMCU (ESP8266/ESP32):** Acts as a gateway for server communication and data buffering.
- **Robots:** Car lifting robot and elevator robot for vehicle movement and placement.
- **ESP32CAM:** Captures plate numbers for enhanced automation.

### Software
- **MCAL and HAL Drivers:** Custom drivers for STM32 to interface with various hardware components.
- **Bootloader:** Manages firmware updates, verifies CRC, and handles secure memory flashing.
- **NodeMCU Gateway Code:** Buffers and transmits data chunks from the server to the STM32.
- **FOTA Server:** Encodes, chunks, and transmits firmware updates to the NodeMCU.

## Repository Structure
```
├── Connection (Schematics)
│   ├── Elevator_Robot Schematic
│   ├── Lifiting_Robot Schematic
├── Elev_Robot (Code)
├── FOTA
│   ├── FOTA_Bootloader
│   └── Gateway
├── Main Gate ESP32 (Code)
├── Lifting_Robot (Code)
└── STM_TO_ESP (V2V Gateway Code)
└── Server (FOTA and V2V Gateway Code)
```

## Installation and Setup
### Prerequisites
- STM32 development environment (e.g., STM32CubeIDE)
- NodeMCU development environment (e.g., Arduino IDE)
- Server setup with Python and necessary libraries

### Steps
1. **Clone the repository:**
   ```bash
   git clone https://github.com/hamdy24/Autonomous-Parking-System
   cd Autonomous-Parking-System
   ```
2. **Setup STM32 Firmware:**
   - Open the STM32CubeIDE project.
   - Build and flash the firmware onto the STM32 microcontroller.
3. **Setup NodeMCU:**
   - Open the Arduino IDE project.
   - Upload the NodeMCU gateway code.
4. **Run the FOTA Server:**
   - Navigate to the Server directory.
   - Run the FOTA server script:
     ```bash
     python HostRunningSTMwithTCP.py
     ```
5. **Connect the Hardware:**
   - Follow the schematics to connect STM32, NodeMCU, and other components.
   - Power up the system and ensure all components are communicating properly.

## Usage
1. **Initialize the System:**
   - Power on the STM32 and NodeMCU modules.
   - Start the FOTA server and ensure it is connected to the NodeMCU.
2. **Parking Operations:**
   - Use the control interface to send parking commands.
   - Monitor the robots as they coordinate to park and retrieve vehicles.
3. **Firmware Updates:**
   - Upload new firmware via the FOTA server interface.
   - Observe the NodeMCU handling data chunks and the STM32 bootloader performing secure updates.

## Contributing
We welcome contributions to enhance the system's functionality and efficiency. Please fork the repository and create a pull request with detailed information on your changes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements
We extend our gratitude to Prof. Osama ElGhoniemy for his invaluable guidance and support throughout this project. Special thanks to team members Abdullah Emad and Mona Mohamed for their dedication and hard work.

## Contact
For more information, please contact:
- [Hamdy Abdelrahman](https://www.linkedin.com/in/hamdy-abdul-rahman/)
- [hamdy.abdelrhmaan@gmail.com]

---
