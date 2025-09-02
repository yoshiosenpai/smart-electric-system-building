# Safety Checklist — Smart Electric System (FYP Prototype on Wooden Board)

> ⚠️ **DANGER: MAINS VOLTAGE (230 VAC / 120 VAC).** This prototype is for demonstration only and is **not** a certified household installation. Work under supervision, use proper tools/PPE, and never touch the board while energized.

## 0) Scope & Assumptions
- Use case: ESP32 controls 4 relays to switch LED bulbs (5–10 W each).
- Mounting: Exposed components on a **wooden board** with clear AC vs DC lanes.
- Architecture: **Option A (logic switch)** — momentary buttons to ESP32 GPIO; no mains switching by the buttons.

---

## 1) Personal Protective Equipment (PPE)
- [ ] Safety glasses
- [ ] Insulated screwdrivers
- [ ] Closed shoes, no metal jewelry/watches
- [ ] One-hand rule when probing live (keep other hand away)

---

## 2) Standards & Good Practice (Educational Context)
- [ ] **RCD/GFCI** (residual current device) protected outlet used for demos
- [ ] **Labeling**: “⚠️ MAINS VOLTAGE — DEMO ONLY” clearly visible
- [ ] **Supervision**: A qualified person reviews the wiring before first power-up

---

## 3) Parts Ratings & Selection
- [ ] Relay module rated **≥10 A @ 250 VAC**, opto-isolated inputs
- [ ] LED bulbs **≤10 W** each, non-smart (low inrush)
- [ ] Inline **fuse** on Live input: **2–3 A slow-blow** (for 4× LED bulbs)
- [ ] **Mains wire**: min **0.75 mm²** (≈ AWG 18) copper, heat-resistant insulation
- [ ] Low-voltage wires: properly sized, flexible, not frayed
- [ ] Power adapter: **5 V / 2 A** minimum, reputable brand

---

## 4) Layout & Segregation (Board Build)
- [ ] **Separate lanes**: AC on one side, DC/logic on the other (clear visual gap)
- [ ] Keep **≥10 mm** clearance between AC and DC runs (no crossovers)
- [ ] Relay board mounted so **AC terminals face AC lane**, **logic pins face DC lane**
- [ ] Cable management: clips/zip ties; no loose loops near hot parts
- [ ] Heat sources (bulbs, resistors) away from plastic or wood edges

---

## 5) Wiring Rules (Color, Termination, Strain Relief)
- [ ] **Color code**: Brown=Live, Blue=Neutral, Green/Yellow=Earth (or local standard)
- [ ] **Live path**: Wall → **Fuse** → Bridge to **COM1–COM4** → **NO1–NO4** → Bulb Lives
- [ ] **Neutral**: Direct neutral bus to all bulbs (never through relay)
- [ ] **Earth**: Pass through to any earthed metal parts/sockets (if used)
- [ ] All AC joints via **barrier terminal blocks** (no twisted/bare joins)
- [ ] Heatshrink or insulated ferrules on exposed conductors
- [ ] **Strain relief** on mains inlet (gland or clamp)

---

## 6) Low-Voltage (ESP32, Buttons, Relay Inputs)
- [ ] Common **GND** between ESP32, relay board, and 5 V adapter
- [ ] ESP32 → Relay IN1..IN4: short, tidy, not bundled with AC
- [ ] Buttons: **momentary NO**; one leg to GPIO (21/22/23/25), other to **GND**
- [ ] Firmware uses `INPUT_PULLUP`; press = **LOW**
- [ ] No low-voltage wire runs under AC terminals

---

## 7) Pre-Power Electrical Checks (Multimeter)
- **Continuity (power OFF, unplugged):**
  - [ ] **Live** does **not** short to **Neutral** or **Earth**
  - [ ] **ESP32 GND** has no continuity to AC Live/Neutral/Earth
- **Polarity:**
  - [ ] Fuse is on **Live** only (not on Neutral)
  - [ ] COMs are bridged **after** the fuse (not before)
- **Relay logic:**
  - [ ] With ESP32 unpowered, **NO** contacts are open (bulbs cannot energize)

---

## 8) First Power-On (Low Voltage Only)
- [ ] Power **5 V adapter** only; ESP32 boots
- [ ] Blynk connects; toggling V0–V3 moves **only** relay LEDs/clicks
- [ ] Buttons toggle channels once (no chatter); serial logs OK
- [ ] No unexpected heating or smell at relay board

---

## 9) Mains Bring-Up (Stepwise)
- [ ] Connect **one** bulb to CH1; verify wiring again
- [ ] Power mains via **RCD/GFCI** extension
- [ ] Toggle CH1: bulb ON/OFF cleanly; no flicker
- [ ] Measure current (optional) — consistent with bulb rating
- [ ] Repeat for CH2–CH4 one at a time, then all together
- [ ] 15–30 min **soak test** with all ON: relay area <~**60 °C** (touch-safe guideline)

---

## 10) Functional Safety Behaviors
- [ ] **Default OFF** at boot (all relays inactive)
- [ ] **Loss of Wi-Fi**: buttons still work; no random toggles
- [ ] **Recovery**: Blynk sync updates UI to current states
- [ ] **Emergency stop**: mains plug accessible, RCD test button known

---

## 11) What **Not** To Do
- [ ] Do **not** leave prototype powered **unattended**
- [ ] Do **not** expose **bare AC** terminals (always use barrier blocks/heatshrink)
- [ ] Do **not** route AC over/under the ESP32 or logic area
- [ ] Do **not** let wires rest on hot bulbs/lamps

---

## 12) Documentation Photos (for FYP Report)
- [ ] Full board photo with AC vs DC lanes labeled
- [ ] Close-ups: fuse placement, terminal blocks, relay outputs
- [ ] Wiring diagram/table included in README
- [ ] Short demo: button press → bulb ON/OFF; app sync

---

## 13) Sign-off (Before Public Demo)
| Item                              | Pass/Fail | Initials | Date |
|-----------------------------------|-----------|----------|------|
| PPE & RCD in place                |           |          |      |
| AC/DC segregation & labeling      |           |          |      |
| Fuse on Live; polarity correct    |           |          |      |
| No exposed live parts             |           |          |      |
| Low-voltage tests passed          |           |          |      |
| Single-channel AC test passed     |           |          |      |
| Four-channel AC test passed       |           |          |      |
| 30-min soak test passed           |           |          |      |

---

## 14) Risk Snapshot (Top Hazards & Mitigations)
- **Electric shock (contact with live parts)** → Barrier terminals, heatshrink, RCD, clear labels, supervision  
- **Short circuit / overheating** → Inline fuse on Live, correct wire gauge, tidy routing, soak test  
- **Logic/AC cross-talk** → 10+ mm clearance, no shared bundles, opto-isolated relays  
- **Operational misuse** → Default-OFF at boot, emergency unplug accessible, demo script rehearsed

---

**Reminder:** This checklist supports educational safety. It does **not** replace national electrical codes or compliance standards.
