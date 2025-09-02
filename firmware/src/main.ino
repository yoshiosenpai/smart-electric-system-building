/*
  Smart Electric System in Building (Option A: Logic Switch)
  Arduino IDE version
  - ESP32 + Blynk control for 4 relays (AC bulbs)
  - 4 local momentary buttons (NO) for manual toggle
  - Debounce + edge trigger
  - Keeps Blynk UI in sync with real state

  Low-voltage wiring:
    RELAY CH1..CH4: ESP32 GPIO16,17,18,19 -> Relay IN1..IN4
    BUTTON 1..4:   One leg -> ESP32 GPIO21,22,23,25 ; Other leg -> GND (INPUT_PULLUP)

  Mains:
    AC Live -> Fuse -> Relay COM1..COM4 (bridged)
    Relay NO1..NO4 -> Bulb1..Bulb4 Live
    Neutral -> common neutral bus

  Code by Solehin Rizal
*/

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ====== Blynk credentials (fill these) ======
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Electric System"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

const char* WIFI_SSID = "YourSSID";
const char* WIFI_PASS = "YourPass";

// ====== Pin mapping ======
const int RELAY[4]  = {16, 17, 18, 19};   // Relay IN1..IN4
const int BUTTON[4] = {21, 22, 23, 25};   // Momentary NO to GND

// Most 4-ch opto relay boards are active-LOW (LOW=ON). Flip if yours is active-HIGH.
const bool RELAY_ACTIVE_LOW = true;

// Debounce time for buttons (ms)
const unsigned long DEBOUNCE_MS = 120;

// ====== State ======
bool state[4] = {false, false, false, false};        // logical lamp states
bool lastStableBtn[4]  = {true, true, true, true};    // INPUT_PULLUP idle = HIGH
bool lastReadBtn[4]    = {true, true, true, true};
unsigned long lastChangeMs[4] = {0,0,0,0};

// ====== Helpers ======
void driveRelayHW(int ch, bool on) {
  int pin = RELAY[ch];
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(pin, on ? LOW : HIGH);
  } else {
    digitalWrite(pin, on ? HIGH : LOW);
  }
}

void reflectToApp(int ch) {
  Blynk.virtualWrite(V0 + ch, state[ch] ? 1 : 0);
}

void applyChannel(int ch, bool on, bool reflect=true) {
  state[ch] = on;
  driveRelayHW(ch, on);
  if (reflect) reflectToApp(ch);
  Serial.printf("[CH%d] -> %s\n", ch+1, on ? "ON" : "OFF");
}

void toggleChannel(int ch, bool reflect=true) {
  applyChannel(ch, !state[ch], reflect);
}

// ====== Blynk handlers ======
BLYNK_WRITE(V0) { applyChannel(0, param.asInt()); }
BLYNK_WRITE(V1) { applyChannel(1, param.asInt()); }
BLYNK_WRITE(V2) { applyChannel(2, param.asInt()); }
BLYNK_WRITE(V3) { applyChannel(3, param.asInt()); }

BLYNK_CONNECTED() {
  Serial.println("[Blynk] Connected, syncing V0..V3");
  Blynk.syncVirtual(V0, V1, V2, V3);
}

// ====== Setup/Loop ======
void setup() {
  Serial.begin(115200);
  delay(200);

  // Relay outputs: ensure OFF at boot
  for (int i = 0; i < 4; i++) {
    pinMode(RELAY[i], OUTPUT);
    if (RELAY_ACTIVE_LOW) digitalWrite(RELAY[i], HIGH);
    else                  digitalWrite(RELAY[i], LOW);
  }

  // Buttons with internal pull-up; pressed = LOW
  for (int i = 0; i < 4; i++) {
    pinMode(BUTTON[i], INPUT_PULLUP);
    lastReadBtn[i]   = digitalRead(BUTTON[i]);
    lastStableBtn[i] = lastReadBtn[i];
  }

  // Blynk will handle WiFi connect; this prints feedback
  Serial.printf("Connecting WiFi SSID: %s\n", WIFI_SSID);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  Serial.println("If stuck, check SSID/PASS or router 2.4 GHz mode.");
}

void handleButtons() {
  unsigned long now = millis();
  for (int ch = 0; ch < 4; ch++) {
    bool reading = digitalRead(BUTTON[ch]); // HIGH idle, LOW pressed

    if (reading != lastReadBtn[ch]) {
      lastReadBtn[ch] = reading;
      lastChangeMs[ch] = now; // start debounce window
    }

    if ((now - lastChangeMs[ch]) > DEBOUNCE_MS) {
      if (reading != lastStableBtn[ch]) {
        lastStableBtn[ch] = reading;

        // Falling edge (HIGH->LOW) = physical press: toggle
        if (reading == LOW) {
          toggleChannel(ch, /*reflect=*/true);
        }
      }
    }
  }
}

void loop() {
  Blynk.run();
  handleButtons();
}
