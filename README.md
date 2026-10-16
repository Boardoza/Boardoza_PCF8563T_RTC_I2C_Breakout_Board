# Boardoza PCF8563T RTC Breakout Board

The **Boardoza PCF8563T RTC Breakout Board** is a compact and reliable real-time clock solution built around the **PCF8563T** low-power CMOS clock/calendar IC from NXP. It provides accurate timekeeping with full calendar functionality including year, month, day, weekday, hours, minutes, and seconds. Designed for embedded systems that require dependable time management.

With its simple I²C interface and clearly labeled header pins, this breakout board is fully compatible with Arduino, Raspberry Pi, STM32, ESP32, and other microcontrollers that **support I²C communication**. It is ideal for applications such as **data logging, alarm scheduling, time-stamping systems, industrial controllers, IoT devices, and battery-powered embedded projects.**

> [!WARNING]
> This product does not come with a CR1220 coin cell battery. The battery must be purchased separately.

## [Click here to purchase!](https://www.ozdisan.com/ureticiler/boardoza)

| Front Side | Back Side |
|:---:|:---:|
| ![PCF8563T Front](./assets/PCF8563T%20Front.png) | ![PCF8563T Back](./assets/PCF8563T%20Back.png) |

---

## Key Features

- **Accurate Real-Time Clock:** Maintains precise time and full calendar tracking.
- **I²C Interface:** Simple and widely supported communication with microcontrollers.
- **Interrupt & Clock Output:** Provides **nINT** for alerts and **CLK_O** for clock signal output.
- **Battery Backup Support:** Continues timekeeping during power loss with a coin cell battery.
- **Wide Compatibility:** Works with Arduino, ESP32, STM32, Raspberry Pi, and more.

---

## Technical Specifications

**Model:** PCF8563T  
**Manufacturer:** Boardoza    
**Manufacturer IC:** NXP Semiconductors  
**Input Voltage:** 2.5V – 5.5V DC  
**Functions:** Real-Time Clock & Calendar  
**Communication:** I²C (7-bit address 0x51, Write: A2h, Read: A3h)  
**Oscillator Frequency:** 32.768 kHz  
**Operating Temperature:** -40°C to +85°C  
**Board Dimensions:** 20mm x 20mm  

---

## Board Pinout

### ( J1 ) Main Connector

| Pin Number | Pin Name | Description |
|:---:|:---:|---|
| 1 | VCC | Supply Voltage |
| 2 | nINT | Interrupt Output (Active Low) |
| 3 | SDA | I²C Serial Data Pin |
| 4 | SCL | I²C Serial Clock Pin |
| 5 | CLK_O | Clock Output |
| 6 | GND | Ground |

---

## Board Dimensions

<img src="./assets/PFC8563T Dimensions.png" alt="PCF8563T Board Dimension" width="450"/>

---

## Step Files

[Boardoza PCF8563T.step](./assets/PCF8563T%20Step.step)

---

## Datasheet

[PCF8563T Datasheet](./assets/PCF8563T%20Datasheet.pdf)

---

## Version History

- V1.0.0 - Initial Release

---

## Support

- If you have any questions or need support, please contact support@boardoza.com

---

## **License**

This repository contains both hardware and software components:

### **Hardware Design**

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

All hardware design files are licensed under [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

### **Software/Firmware**

[![BSD-3-Clause][bsd-shield]][bsd]

All software and firmware are licensed under [BSD 3-Clause License][bsd].

[bsd]: https://opensource.org/licenses/BSD-3-Clause
[bsd-shield]: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg
