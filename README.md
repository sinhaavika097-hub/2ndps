# AgriTech IoT Early Warning System 🌾📊

An AI-driven, real-time IoT architecture designed to proactively detect pest infestations and estimate crop yield health before visible damage occurs. Built for high-speed inference and localized edge processing.

## 🚀 The Problem We're Solving
Traditional crop monitoring is reactive—farmers only know about pest outbreaks or crop stress *after* the damage is done. This system shifts agriculture to a **proactive** model by continuously cross-referencing on-the-ground environmental sensor data with predictive health models.

## 🏗️ System Architecture
1. **IoT Edge Nodes:** Field-deployed microcontrollers (e.g., ESP32) equipped with DHT sensors (temperature/humidity) and soil moisture probes stream continuous data.
2. **C++ Inference Engine (`agbackend.cpp`):** A high-performance backend that ingests multi-modal sensor arrays, calculates real-time localized stress factors, and simulates AI models to assign a **Pest Risk Score** and **Yield Health Index**.
3. **Real-Time Dashboard (`agritech_iot_dashboard.html`):** A responsive, dark-themed frontend built with Tailwind CSS and JavaScript to visualize field node data and critical alerts for district agricultural officers.

## 🛠️ Tech Stack
* **Backend:** C++ (Designed for low-latency IoT ingestion)
* **Frontend:** HTML5, Vanilla JavaScript, Tailwind CSS
* **Simulated Hardware:** ESP32 / Arduino ecosystem

## ⚙️ Quick Start (Local Development)

### 1. Run the Frontend
Simply download the repository and open `agritech_iot_dashboard.html` in any modern web browser to view the UI.

### 2. Compile the Backend Simulation
To run the C++ inference engine simulation locally:
```bash
g++ agbackend.cpp -o agbackend
./agbackend
