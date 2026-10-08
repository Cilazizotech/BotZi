# Project Sponsorship Review: PCBWay Services for BotZi Robotic Arm

## 1. Introduction to PCBWay

[PCBWay](https://www.pcbway.com) is a leading one-stop manufacturing platform specializing in quick-turn PCB prototype fabrication, PCB assembly (PCBA), and custom hardware prototyping services—including **3D Printing (SLA, SLS, SLM Metal)**, **CNC Machining**, **Sheet Metal Fabrication**, and **Injection Molding**.

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
   * Exported standard Gerber files and drill maps from the PCB design software:
<img width="50%" alt="pcb1" src="https://github.com/user-attachments/assets/b2b2d337-8a14-4810-86db-2a724b678458" />
<img width="50%" alt="pcb2" src="https://github.com/user-attachments/assets/ca4a733e-9f88-484f-b0a7-d93cb9a14070" />

* Generate gerber files in KiCAD:
<img width="60%" alt="pcb3" src="https://github.com/user-attachments/assets/90db6faf-479a-491a-8bda-e31836b0a2db" />

* Do NOT forget to select the minimum required layers!:
<img width="80%" alt="pcb4" src="https://github.com/user-attachments/assets/bfa429d3-1225-4793-ab2d-2e421e0ba6cc" />

* Then generate drill files:
<img width="80%" alt="pcb5" src="https://github.com/user-attachments/assets/7bd46612-0294-4593-8b2d-78b80e73b3bb" />
<img width="60%" alt="pcb6" src="https://github.com/user-attachments/assets/96eaf3dd-c17a-4be2-a875-b89e98dcc3cb" />

* After that pack all exported data into one .zip file.

* Uploaded directly to PCBWay's **Quick order**:
<img width="75%" alt="pcb8" src="https://github.com/user-attachments/assets/a38a5fd1-14d7-4326-ac86-6c93a56744dc" />
<img width="75%" alt="pcb9" src="https://github.com/user-attachments/assets/0cce2f76-6362-435a-b373-74a6face772f" />

* Add the .zip file into the upload:
<img width="60%" alt="pcb10" src="https://github.com/user-attachments/assets/a0541eb5-866a-4eb4-8947-78980d7ff353" />
<img width="50%" alt="pcb11" src="https://github.com/user-attachments/assets/78259b72-6a8d-4a0d-b312-643c0fe53b67" />

* After successful upload the dimensions can be seen:
<img width="85%" alt="pcb12" src="https://github.com/user-attachments/assets/39874e42-5993-4353-ad7a-be01c16bd9eb" />

* Properties of PCB can be reviewed and changed to the desired settings:
<img width="80%" alt="pcb13" src="https://github.com/user-attachments/assets/ac34fe16-2bee-4bb8-8ce1-87b8a573b7d7" />
<img width="80%" alt="pcb14" src="https://github.com/user-attachments/assets/b7f5a7db-aa61-456b-af00-620a87a38498" />

* Select shipping method:
<img width="50%" alt="pcb16" src="https://github.com/user-attachments/assets/1fae1418-4fab-4ee9-943d-57bd74b9e56a" />
<img width="45%" alt="pcb18" src="https://github.com/user-attachments/assets/c936c4b9-daa6-462f-a885-b39762baaff2" />

* Order is ready for checkout:
<img width="80%" alt="pcb19" src="https://github.com/user-attachments/assets/62b3ecaa-6f6f-4399-aac8-df4c92a30ba0" />


2. **Board Specifications:**
   * **Layers:** 2-Layer FR-4 Board
   * **Dimensions:** Standard compact shield footprint fit for BotZi base frame
   * **Thickness:** $1.6\text{ mm}$
   * **Solder Mask Color:** Classic Matte Blue
   * **Silkscreen:** White (clear pinout labels for servos & joysticks)
   * **Surface Finish:** HASL with Lead

3. **Engineering DFM Review:**
   * Within hours, PCBWay engineers verified trace widths, drill clearances, and pad spacings for the servo headers and Arduino sockets before production started.

## 4. Unboxing & Initial Inspection

* **Packaging:** The PCBs arrived securely wrapped in anti-static vacuum packs inside a durable box, protecting pin headers and board edges from transit damage.
<img width="80%" alt="unbox_box" src="https://github.com/user-attachments/assets/2d3d6f4d-63bd-4c2d-b785-b13a8aa85f95" />


* **Quantity Received:** 5/5 pristine boards.
* **Surface & Silkscreen Quality:** Silkscreen labels for servo channels (`S1`–`S4`), joystick inputs, and power rails were exceptionally sharp and easy to read. Solder masks were perfectly aligned with zero pad overlap.
<img width="916" height="521" alt="unboxpcb1" src="https://github.com/user-attachments/assets/e42cd600-2e9d-40d5-ba39-80480682d928" />


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
| **Board Length** | $141.00\text{ mm}$ | $140.97\text{ mm}$ | $-0.03\text{ mm}$ | Pass |
| **Board Width** | $68.2.00\text{ mm}$ | $68.7\text{ mm}$ | $+0.05\text{ mm}$ | Pass |

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
