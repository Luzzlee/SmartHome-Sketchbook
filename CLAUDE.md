# SmartHome-Sketchbook

Arduino/ESP32 (WiFiNINA-based board) sketches for SmartHome devices — connect to WiFi, then to the MQTT broker from `SmartHome-Infrastructure` to publish/receive device state.

See also: [top-level `D:\Git\CLAUDE.md`](../CLAUDE.md) for how this fits with the other SmartHome repos.

## Tech stack

Arduino, `WiFiNINA` + `PubSubClient` libraries (install via Arduino Library Manager).

## Structure

- `libraries/util/wiFiHelper/` — `WiFiHelper(ssid, password)`: `begin()`, `reconnect()`, `isConnected()`.
- `libraries/util/mqttHelper/` — `MqttHelper(server, port, user, password)`: `begin()`, `reconnect()`, `loop()`, `publish(topic, payload)`, `setCallback(cb)`.
- `sketches/setLightWithMqtt/` — **the working, complete example.** Uses both helper libraries correctly.
- `sketches/connectWlanMqtt/` — an earlier/abandoned experiment, currently broken (see below).
- `sketches/tests/{Potentiometer_01,RGB_01}/` — standalone RGB LED test sketches, no WiFi/MQTT.

## Secrets

Real WiFi/MQTT credentials go in a gitignored `arduino_secrets.h` **per sketch folder** (each sketch's own directory is on the Arduino include path), based on the committed `arduino_secrets.h.example` template:

```cpp
#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."
#define MQTT_USERNAME "..."
#define MQTT_PASSWORD "..."
```

Copy the template and fill in real values before compiling/flashing:
```bash
cp sketches/setLightWithMqtt/arduino_secrets.h.example sketches/setLightWithMqtt/arduino_secrets.h
```

## Known issues / not yet done

- `sketches/connectWlanMqtt/connectWlanMqtt.ino` `#include`s a `WiFiConnection.ino` file that does not exist in this repo — **this sketch cannot currently compile.** Looks like an earlier experiment that was abandoned in favor of `setLightWithMqtt.ino`'s helper-library approach. Not fixed (would require guessing unknown design intent) — use `setLightWithMqtt.ino` as the reference implementation instead.
