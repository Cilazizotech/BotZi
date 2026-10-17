
# BotZi - 3D printed robotic arm with Arduino Nano
<img width="1253" height="832" alt="Gemini_Generated_Image__BOTZI_PCBWAY_GITHUB1" src="https://github.com/user-attachments/assets/2e0bab7a-50c7-4a6f-9d70-6ceeac30ec54" />

[![Sponsored by PCBWay](https://img.shields.io/badge/PCB-PCBWay-green?style=for-the-badge&logo=pcbway)](https://www.pcbway.com)

# Meet BotZI: The Compact, DIY Robot Arm for Makers & Innovators!

I created BotZI out of a passion for accessible robotics and prototyping. Whether you are an educator, a hobbyist, or an engineer looking for a versatile tool on your workbench, BotZI was designed to bridge the gap between complex industrial automation and affordable desktop experimentation. From precise pick-and-place tasks to learning kinematics and custom micro-controller integration, BotZI provides a hands-on platform to bring your hardware projects to life.

Building a reliable robot arm requires clean electronics and stable power distribution—and that’s where PCBWay came in to make this project possible!

# PCBWay Services for BotZi Robotic Arm
Special thanks to [PCBWay](https://www.pcbway.com) for sponsoring the custom PCBs for the BotZi project!

## 1. Introduction to PCBWay

[PCBWay](https://www.pcbway.com) is a leading one-stop manufacturing platform specializing in quick-turn PCB prototype fabrication, PCB assembly (PCBA), and custom hardware prototyping services—including **3D Printing (SLA, SLS, SLM Metal)**, **CNC Machining**, **Sheet Metal Fabrication**, and **Injection Molding**.

<p align="center">
<img width="50%" alt="PCBWay logo_2" src="https://github.com/user-attachments/assets/46381ec6-34f2-4753-81d1-89a16966b9d2" />
</p>
Whether you need low-cost prototype circuit boards, custom shield assemblies, or 3D-printed structural mechanical parts, PCBWay delivers fast lead times, instant online quotes, and thorough Design for Manufacturability (DFM) reviews.

## 2. Project Background

**BotZi** is an open-source, compact 3D-printed robotic arm kit designed for makers, educators, and hobbyists. Powered by an Arduino Nano and controlled via dual analog joysticks, BotZi is built for versatile desktop experimentation, pick-and-place tasks, and learning kinematics.
<img width="60%" alt="AI_COVER_PCBWAY_blue" src="https://github.com/user-attachments/assets/8ba081c3-3620-4da5-81ea-0ba87d4acbc9" />

To handle current spikes and power distribution across multiple MG90S micro servos without erratic voltage drops, BotZi requires a dedicated custom mainboard / controller shield.

<img width="50%" alt="pcb2" src="https://github.com/user-attachments/assets/ca4a733e-9f88-484f-b0a7-d93cb9a14070" />

* **Target Application:** Desktop Educational & Prototyping Robotic Arm
* **Core Controller:** Arduino Nano + Custom Servo Driver Shield
* **Sponsorship Goal:** Fabricate high-reliability custom PCBs via PCBWay to ensure clean power routing and effortless hand-soldering assembly.

## 3. Order & Fabrication Process

Ordering the custom controller board via PCBWay’s online interface was fast and straight-forward:

1. **File Upload & Quote:**
   * Exported standard Gerber files and drill maps from the PCB design software:
<img width="50%" alt="pcb1" src="https://github.com/user-attachments/assets/b2b2d337-8a14-4810-86db-2a724b678458" />

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
* 
If you are working on your own robotics, IoT, or custom circuit projects, I highly recommend PCBWay for fast, high-quality, and budget-friendly PCB fabrication and assembly services.

## Check out BotZI on Tindie & Cults3D to build your own today!

## Github:
https://github.com/Cilazizotech/BotZi

## Buy only 3D model:
https://cults3d.com/:2845980

## Buy kit on tindie.com:
https://www.tindie.com/products/43268/

## Buy kit without 3D printed parts on tindie.com:
https://www.tindie.com/products/43401/

## Please use one of the .ino file according to your language preferences:
1. BotZi_controller_sw_20260712_v1.2.ino - Hungarian
2. BotZi_controller_sw_20260712_v1.2_en.ino - English
3. BotZi_controller_sw_20260712_v1.2_de.ino - Deutsch
4. BotZi_controller_sw_20260712_v1.2_es.ino - Español
5. BotZi_controller_sw_20260712_v1.2_fa.ino - Français
6. BotZi_controller_sw_20260712_v1.2_it.ino - Italiano

## Youtube videos :
https://www.youtube.com/@CilazizoTech

## Contact / Kapcsolat:
cilazizotech@gmail.com
+36-30-4141-858

<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145243 (Közepes)" src="https://github.com/user-attachments/assets/2accf344-273c-484f-8514-8a411dada6a0" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145225 (Közepes)" src="https://github.com/user-attachments/assets/5a114ed5-d78f-45e6-a43b-5fefda757b16" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145126 (Közepes)" src="https://github.com/user-attachments/assets/af9fc734-a402-4aba-8531-44d056aed9fa" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145123 (Közepes)" src="https://github.com/user-attachments/assets/1ac47508-2469-4c85-b296-0cea5aa23d38" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145119 (Közepes)" src="https://github.com/user-attachments/assets/635d0867-7f84-4458-89cd-45b2e16e0f6a" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145059 (Közepes)" src="https://github.com/user-attachments/assets/da34cc08-b810-4e80-b501-cccef2887466" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_145041 (Közepes)" src="https://github.com/user-attachments/assets/5a24ddde-4337-4700-933d-66c67b65d167" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_144927 (Közepes)" src="https://github.com/user-attachments/assets/484bd2bc-be94-454b-aaa8-9efa4e81dbf7" />
<img width="3114" height="1752" alt="2026-07-17T15_14_21 848Z-20260607_144918 (Közepes)" src="https://github.com/user-attachments/assets/a9f798b9-7e17-46f3-ad39-6a9dc3408db1" />
<img width="3111" height="1752" alt="2026-07-17T14_58_29 963Z-20260613_181242" src="https://github.com/user-attachments/assets/ffcb1ad6-57bc-4064-b1d7-03f719d2e59a" />
<img width="2336" height="4148" alt="2026-07-17T14_58_29 963Z-20260613_181218" src="https://github.com/user-attachments/assets/c0c49d64-e497-4d26-9c69-c4e2119b0dc7" />
<img width="3111" height="1752" alt="2026-07-17T14_58_29 963Z-20260613_181212" src="https://github.com/user-attachments/assets/da7127ae-a763-4dac-a92b-050597b55e5a" />
<img width="3111" height="1752" alt="2026-07-17T14_58_29 963Z-20260613_181209" src="https://github.com/user-attachments/assets/6155fc9b-5327-48d8-9b63-b8059b241a74" />
<img width="675" height="1073" alt="gb4" src="https://github.com/user-attachments/assets/d70c9f2a-d739-4d27-8715-50d8fc0e37ee" />
<img width="655" height="777" alt="gb3" src="https://github.com/user-attachments/assets/7261c5c4-126a-4007-b9a3-3a6a8e40e864" />
<img width="604" height="891" alt="gb2" src="https://github.com/user-attachments/assets/082d8b2e-17c4-46c7-98ac-0bc449a4f7e4" />
<img width="829" height="675" alt="gb1" src="https://github.com/user-attachments/assets/74ce98c4-4cea-412d-9974-adef328effaf" />
<img width="120" height="35" alt="PCBWay logo（2）" src="https://github.com/user-attachments/assets/b4c04eca-05e5-41e4-8d3b-d7f305997810" />

