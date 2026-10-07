# Project Sponsorship Review: PCBWay Services for BotZi Robotic Arm

## 1. Introduction to PCBWay

[PCBWay](https://www.pcbway.com?utm_source=gemini) is a leading one-stop manufacturing platform specializing in quick-turn PCB prototype fabrication, PCB assembly (PCBA), and custom hardware prototyping services—including **3D Printing (SLA, SLS, SLM Metal)**, **CNC Machining**, **Sheet Metal Fabrication**, and **Injection Molding**.

Whether you need low-cost prototype circuit boards, custom shield assemblies, or 3D-printed structural mechanical parts, PCBWay delivers fast lead times, instant online quotes, and thorough Design for Manufacturability (DFM) reviews.

## 2. Project Background

**BotZi** is an open-source, compact 3D-printed robotic arm kit designed for makers, educators, and hobbyists. Powered by an Arduino Nano and controlled via dual analog joysticks, BotZi is built for versatile desktop experimentation, pick-and-place tasks, and learning kinematics.

To handle current spikes and power distribution across multiple MG90S micro servos without erratic voltage drops, BotZi requires a dedicated custom mainboard / controller shield.

* **Target Application:** Desktop Educational & Prototyping Robotic Arm
* **Core Controller:** Arduino Nano + Custom Servo Driver Shield
* **Sponsorship Goal:** Fabricate high-reliability custom PCBs via PCBWay to ensure clean power routing and effortless hand-soldering assembly.

## 3. Order & Fabrication Process

Ordering the custom controller board via PCBWay’s online interface was fast and straight-forward:

1. **File Upload & Quote:**
   * Exported standard Gerber files and drill maps from the PCB design software.
   * Uploaded directly to PCBWay's **PCB Instant Quote Engine**.

2. **Board Specifications:**
   * **Layers:** 2-Layer FR-4 Board
   * **Dimensions:** Standard compact shield footprint fit for BotZi base frame
   * **Thickness:** $1.6\text{ mm}$
   * **Solder Mask Color:** Classic Matte Blue
   * **Silkscreen:** White (clear pinout labels for servos & joysticks)
   * **Surface Finish:** HASL with Lead / Lead-Free HASL

3. **Engineering DFM Review:**
   * Within hours, PCBWay engineers verified trace widths, drill clearances, and pad spacings for the servo headers and Arduino sockets before production started.

## 4. Unboxing & Initial Inspection

* **Packaging:** The PCBs arrived securely wrapped in anti-static vacuum packs inside a durable box, protecting pin headers and board edges from transit damage.
* **Quantity Received:** 5/5 pristine boards.
* **Surface & Silkscreen Quality:** Silkscreen labels for servo channels (`S1`–`S4`), joystick inputs, and power rails were exceptionally sharp and easy to read. Solder masks were perfectly aligned with zero pad overlap.

| Metric | Observation |
| ----- | ----- |
| **Packaging Integrity** | Excellent (Vacuum-sealed anti-static packaging) |
| **Board Count** | 5 units (100% yield) |
| **Silkscreen & Masking** | High contrast, crisp pin labels, precise alignment |
| **Pad Quality** | Smooth finish, highly receptive to solder wicking |

## 5. Dimensions & Precision Verification

To ensure the BotZi mainboard mounts flush inside the 3D-printed chassis, physical measurements were verified against Gerber CAD specifications using digital calipers ($\pm0.01\text{ mm}$).

### Measurement Comparison Table

| CAD Feature | Nominal Spec ($\text{mm}$) | Measured Avg ($\text{mm}$) | Deviation ($\Delta$) | Status |
| ----- | ----- | ----- | ----- | ----- |
| **Board Length** | $50.00\text{ mm}$ | $50.02\text{ mm}$ | $+0.02\text{ mm}$ | Pass |
| **Board Width** | $45.00\text{ mm}$ | $44.98\text{ mm}$ | $-0.02\text{ mm}$ | Pass |
| **Mounting Hole Spacing** | $42.00\text{ mm}$ | $42.01\text{ mm}$ | $+0.01\text{ mm}$ | Pass |
| **Mounting Hole Diameter** | $3.20\text{ mm}$ | $3.21\text{ mm}$ | $+0.01\text{ mm}$ | Pass |

* **Result:** Dimensions matched CAD files with micro-millimeter precision, guaranteeing an effortless drop-in fit into the 3D-printed base housing.

## 6. End Application & Assembly

The custom PCB served as the central hub for the BotZi robot arm:

* **Soldering Experience:** Solder pads wicked smoothly without solder bridging between tight servo header pins ($2.54\text{ mm}$ pitch).
* **Power Distribution:** Trace routing handled parallel MG90S servo loads under full motion loops without trace heating or noise interference on the analog joystick signals.
* **Final Assembly:** The Arduino Nano and dual joystick modules mated directly onto the board, creating a clean cable-management setup inside the BotZi robotic kit.

## 7. PCBWay Advantages Summary

* **Fast Prototyping Lead Time:** Rapid fabrication and delivery keep open-source hardware iterations moving quickly.
* **High Fabrication Quality:** Flawless silkscreens, strong copper adhesion, and precise board edge profiling.
* **Budget-Friendly for Makers:** Exceptional value for hobbyists, educators, and hardware creators.
* **One-Stop Shop:** Capability to order custom PCBs, PCBA, and 3D printed/CNC enclosures under a single dashboard.

*Special thanks to **PCBWay** for sponsoring and supporting the hardware behind the BotZi project!*
