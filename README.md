# SmartHome-Sketchbook

Arduino/ESP32 (WiFiNINA-based board) sketches for the physical devices in the [SmartHome](https://github.com/Luzzlee/SmartHome-Backend) home-automation project. Devices connect to WiFi, then to the MQTT broker from [SmartHome-Infrastructure](https://github.com/Luzzlee/SmartHome-Infrastructure) to publish and receive device state, which [SmartHome-Backend](https://github.com/Luzzlee/SmartHome-Backend) picks up.

## Tech stack

Arduino, `WiFiNINA` + `PubSubClient` libraries (install via the Arduino Library Manager).

## Structure

- `libraries/util/wiFiHelper/`, `libraries/util/mqttHelper/` — shared connection helpers used by the sketches.
- `sketches/setLightWithMqtt/` — the working, complete reference example.
- `sketches/tests/` — standalone LED/potentiometer test sketches, no WiFi/MQTT.

## Getting started

Each sketch needs its own `arduino_secrets.h` with real WiFi/MQTT credentials, based on the committed `.example` template:

```bash
cp sketches/setLightWithMqtt/arduino_secrets.h.example sketches/setLightWithMqtt/arduino_secrets.h
```

Fill in real values, then compile and flash with the Arduino IDE (or `arduino-cli`).

For the full picture, including library API details, see [`CLAUDE.md`](./CLAUDE.md).
