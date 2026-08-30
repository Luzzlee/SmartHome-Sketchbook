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

`DEVICE_NAME`/`DEVICE_ID` must match the device as registered in the `SmartHome-Backend` database — they're used to build the MQTT command topic `smarthome/light/<DEVICE_NAME>/<DEVICE_ID>` that the sketch subscribes to.

Copy the template and fill in real values before compiling/flashing:
```bash
cp sketches/setLightWithMqtt/arduino_secrets.h.example sketches/setLightWithMqtt/arduino_secrets.h
```

## Known issues / not yet done

None currently.
