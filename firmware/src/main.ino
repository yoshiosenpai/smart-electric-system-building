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