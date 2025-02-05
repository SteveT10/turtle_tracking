# Senior Capstone: Turtle Tracking Project

## Introduction

The Turtle Tracking Project is a collaboration with the Washington Department of Fish and Wildlife (WDFW) and Texas Instruments (TI). Approximately 30 to 40 Endangered Northwestern Pond Turtles are monitored within an approximate 60 meter by 60 meter habitat. The WDFW needs to locate eggs laid by female turtles and transfer them to zoos for raising. The process of tracking the turtle eggs is laborious and time-consuming, requiring personnel to triangulate the position of Passive Integrated Transponders (PIT) tags on each turtle and then collect the eggs. This project seeks to offer a less labor-intensive method of tracking turtles and alerts WDFW when turtles have potentially laid eggs.

## Proposed Solution

The proposed project solution is a Ultra-wideband (UWB) network spanning over the Turtle habitat. The network will consist of 4 or more anchor points surrounding the habitat and each Turtle will be equipped with a lightweight, low-profile UWB tag. The system will be driven by a Raspberry Pi computer, which communicates with one UWB anchor through Bluetooth and pings for the locations of each UWB tag. Once the Raspberry pi has the location of a tag and detects an area where turtles require attention from WDFW biologists, it sends an SMS to the biologists about their whereabouts.

## System Overview

![System Overview](./assets/system-overview.png)

### Figure 1: Represents the high-level system overview


For the high-level system design of the Turtle Tracking Project, we can break down the system into 3 subsystems, which are the UWB Transceiver tags, the monitoring system, and finally the SMS system.

![Hardware Architecture](./assets/hardware-arch.png)

### Figure 2: Represents the Monitoring System

### Power Supply
The UWB tags will be powered by a 3.3 voltage coin cell which will power the MCU and UWB chip on the Tag printed circuit board. The UWB anchors and Raspberry Pi Computer will be powered using on-site outlets and no maintenance should be required for the power supply of these stationary parts. The coin cell of the UWB tags should be changed out with charged cells at
least once per year or whenever convenient.

### Ultra Wide Band (UWB) Transceiver
An Ultra Wide Band Transceiver system is attached to each turtle in the habitat. These systems contain an antenna that can both send and receive data via ultra-wideband, sending the position data of a turtle to the base station at a set interval. Each tag is driven by an MSP430fr2476 microcontroller.

![diagram1](./assets/diagram.png)

### Figure 3: Initial Circuit Diagram of System


![diagram2](./assets/diagram2.png)

### Figure 4: Initial Gateway Circuit Diagram of System

### MSP430fr2476 MCU

The main goal of our microcontroller is to interface with the UWB transceiver to process the data and handle communication protocols. It will handle pings from the Raspberry Pi for location data and gather the distance between itself and the anchors. An MSP430 microcontroller was chosen due to its advertised low-power modes.

### UWB Anchor

UWB anchors are afforded a higher profile and weight capacity due to being stationary and not attached to turtles. DWM1001 development boards are utilized here due to having readily available housing and equipment to run the boards. The UWB anchors will wait for distance queries from UWB tags and send their distance between themselves the tag.

### Monitoring System

The monitoring system consists of the RPI5/ SPI communication and UWB Receiver. This module will be designed to detect and read information from the UWB modules. It will read the position data of each turtle and perform calculations to determine their locations. Once a turtle has left the defined pond area, the system will then use the SMS system to notify the
biologists.

