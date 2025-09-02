# Blynk Setup (ESP32 + 4 Channels)

This guide links your ESP32 to the Blynk app, with 4 virtual switches (V0–V3) that control 4 relays. It matches the Arduino sketch in this repo.

---

## 1) Create Template & Device (Blynk Console)
1. Sign in to **Blynk Console** (web).
2. **Create Template**
   - Template Name: `Smart Electric System`
   - Hardware: `ESP32`
   - Connection: `WiFi`
3. **Create Datastreams (4x)**
   - For each `V0`, `V1`, `V2`, `V3`:
     - **Type:** Virtual Pin  
     - **Data Type:** Integer  
     - **Min/Max:** 0 / 1  
     - **Default:** 0  
     - **Permissions:** Read & Write  
4. **Save** the template.
5. **Create Device** from this template (assign it to your account).

> Grab these from **Device Info**:  
> - `BLYNK_TEMPLATE_ID`  
> - `BLYNK_TEMPLATE_NAME` (optional for display)  
> - `BLYNK_AUTH_TOKEN`  
> Put them in your Arduino sketch.

---

## 2) Build the Mobile Dashboard (Blynk App)
1. Open the **Blynk mobile app** → log in with the same account.
2. Your device should appear; open it.
3. Add **4 × Switch** widgets:
   - Switch #1 → Datastream `V0`
   - Switch #2 → Datastream `V1`
   - Switch #3 → Datastream `V2`
   - Switch #4 → Datastream `V3`
4. (Optional) Add **Labels** like “Bulb 1…4”.

---

## 3) Matching the Arduino Sketch
The provided sketch expects:
- **Relays:** GPIO `16/17/18/19` → Relay `IN1..IN4`
- **Buttons (momentary NO):** GPIO `21/22/23/25` → GND (use `INPUT_PULLUP`)
- **Virtual pins:** `V0..V3`
- **Active-LOW relays:** `RELAY_ACTIVE_LOW = true` (flip if your board is active-HIGH)

On connection, the code does:
```cpp
Blynk.syncVirtual(V0, V1, V2, V3);
