# ESP Web Flasher

A simple Over-The-Air (OTA) firmware updater and device control web interface for ESP8266, using only your browser.

## Features

- **OTA Firmware Update:**  
  Upload and flash new firmware (`.bin`) files to your ESP8266 device directly from your browser.
- **Progress Feedback:**  
  See upload progress and status messages in real time.
- **Device Control:**  
  Toggle the onboard LED from the web interface.
- **Modern UI:**  
  Responsive, user-friendly interface with drag & drop support.
    
## Hardware

- ESP8266-based board (e.g., NodeMCU, Wemos D1 Mini, etc.)

## Getting Started

### 1. Flash the Firmware

1. Clone or download this repository.
2. Open `Ota_main.ino` in the Arduino IDE or PlatformIO.
3. Set your WiFi credentials in `Ota_main.ino`:
    ```cpp
    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```
4. Upload the sketch to your ESP8266 board.

### 2. Connect to the Device

- After flashing, open the Serial Monitor at 115200 baud to see the device's IP address.
- Connect your computer/phone to the same WiFi network.

### 3. Use the Web Interface

1. Open a browser and go to `http://<device-ip>/`
2. You will see the ESP Web Flasher UI.
3. To update firmware:
    - Click the upload area or drag & drop a `.bin` file.
    - Click **Upload** and wait for the process to complete.
4. To control the onboard LED:
    - Use the toggle switch in the "Device Control" card.

## File Structure

- `Ota_main.ino` — Main Arduino sketch (ESP8266 firmware)
- `ota_html.h` — Web UI HTML/CSS/JS embedded as a C++ string
- `data/index.html` — (Optional) Standalone HTML for reference/testing
- `build/` — Compiled firmware output

## Dependencies

- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [ESP8266WebServer](https://arduino-esp8266.readthedocs.io/en/latest/esp8266webserver/readme.html)
- [ESP8266HTTPUpdateServer](https://arduino-esp8266.readthedocs.io/en/latest/esp8266httpupdateserver/readme.html)

## Credits

- Inspired by [eshwargit2/ESP_WebFlasher](https://github.com/eshwargit2/ESP_WebFlasher)
- UI design by [@eshwargit2](https://github.com/eshwargit2)

## License

MIT License