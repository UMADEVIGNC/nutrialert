# 🥗 NutriAlert BLE

<p align="center">
  <img src="banner.svg" alt="NutriAlert BLE Banner" width="100%">
</p>

<p align="center">
  <a href="https://www.iarc.who.int/wp-content/uploads/2021/09/IARC_Evidence_Summary_Brief_2.pdf">
    <img src="https://img.shields.io/badge/Science-WHO%20IARC%20Brief%20%232-blueviolet?style=for-the-badge" alt="WHO IARC Paper">
  </a>
  <img src="https://img.shields.io/badge/Connectivity-Bluetooth%20LE%20(v5.x)-blue?style=for-the-badge&logo=bluetooth" alt="BLE">
  <img src="https://img.shields.io/badge/Hardware-RGB%20LED%20Alert%20Device-orange?style=for-the-badge" alt="Hardware Stack">
  <img src="https://img.shields.io/badge/Nutri--Score-A%20%7C%20B%20%7C%20C%20%7C%20D%20%7C%20E-success?style=for-the-badge" alt="Nutri-Score Range">
</p>

---

## 📖 Overview

**NutriAlert BLE** bridges the gap between digital nutritional data and instant, real-world behavioral feedback. By scanning a consumer food product's EAN barcode with a smartphone app, the system processes its numerical nutritional profiling index and transmits a light data payload via **Bluetooth Low Energy (BLE)** to a dedicated hardware module.

The physical device instantly illuminates an onboard **RGB LED array** matching the standard 5-color Nutri-Score classification—giving consumers an undeniable, ambient visual warning *before* they make a dietary choice.

---

## 🚀 Key Features

* **Instant EAN Scanning:** High-performance, low-latency barcode parsing through the mobile companion application.
* **Low-Overhead BLE Communication:** Optimized Bluetooth Low Energy GATT architecture ensures rapid transmission between mobile peripherals and the hardware node.
* **Chroma-Status Alerts:** The physical IoT module cycles through the verified five-tier Nutri-Score spectrum:
  * 🟩 **A** (Dark Green) & **B** (Light Green) – Optimal choices.
  * 🟨 **C** (Yellow) – Moderate profile.
  * 🟧 **D** (Orange) & 🟥 **E** (Red) – High-risk alert.
* **Robust Local Cache:** Speeds up response times for frequently scanned items, limiting unnecessary API latency and keeping the hardware responsive.

---

## 🔄 System Architecture & Data Flow
