# SmartHome-Sketchbook

Arduino/ESP32 (WiFiNINA-based board) sketches for SmartHome devices — connect to WiFi, then to the MQTT broker from `SmartHome-Infrastructure` to publish/receive device state.

See also: [top-level `D:\Git\CLAUDE.md`](../CLAUDE.md) for how this fits with the other SmartHome repos.

## Tech stack

Arduino, `WiFiNINA` + `PubSubClient` libraries (install via Arduino Library Manager).

## Structure

- `libraries/util/wiFiHelper/` — `WiFiHelper(ssid, password)`: `begin()`, `reconnect()`, `isConnected()`.
- `libraries/util/mqttHelper/` — `MqttHelper(server, port, user, password, deviceCommandTopic)`: `begin()`, `reconnect()`, `loop()`, `publish(topic, payload)`, `subscribe(topic)`, `setCallback(cb)`. `reconnect()` re-publishes an "online" message and re-subscribes to `deviceCommandTopic` on every (re)connect.
- `sketches/setLightWithMqtt/` — **the working, complete example.** Uses both helper libraries correctly; subscribes to its `smarthome/light/<DEVICE_NAME>/<DEVICE_ID>` command topic (matching `SmartHome-Backend`'s `DevicesService.SwitchLight` topic schema) and drives an output pin on "ON"/"OFF" payloads.
- `sketches/tests/{Potentiometer_01,RGB_01}/` — standalone RGB LED test sketches, no WiFi/MQTT.

## CI

`.github/workflows/arduino-compile.yml` runs on every push and PR: installs the `arduino:mbed_nano` core plus the `WiFiNINA`/`PubSubClient` libraries via `arduino-cli`, generates a dummy `arduino_secrets.h` per sketch from its committed `.example` file, and compiles every sketch under `sketches/**` (FQBN `arduino:mbed_nano:nanorp2040connect`, with `libraries/util` on the library search path). Compile-only — no flashing/hardware test.

## Secrets

Real WiFi/MQTT credentials go in a gitignored `arduino_secrets.h` **per sketch folder** (each sketch's own directory is on the Arduino include path), based on the committed `arduino_secrets.h.example` template:

```cpp
#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."
#define MQTT_USERNAME "..."
#define MQTT_PASSWORD "..."
#define DEVICE_NAME "..."
#define DEVICE_ID "..."
```

`DEVICE_NAME`/`DEVICE_ID` must match the device as registered in the `SmartHome-Backend` database — they're used to build the MQTT command topic `smarthome/light/<DEVICE_NAME>/<DEVICE_ID>` that the sketch subscribes to. The sketch lowercases `DEVICE_NAME` itself when building this topic (matching the backend's lowercased topic), so it can be entered in any case here; `DEVICE_ID` is used as-is and must match exactly, including case.

Copy the template and fill in real values before compiling/flashing:
```bash
cp sketches/setLightWithMqtt/arduino_secrets.h.example sketches/setLightWithMqtt/arduino_secrets.h
```

## Known issues / not yet done

None currently.
