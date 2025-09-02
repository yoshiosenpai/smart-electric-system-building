# Test Plan — Smart Electric System (ESP32 + Blynk + Buttons)

Scope: Verify Option-A logic (ESP32 as source of truth), safety basics, and demo readiness on a wooden board.

---

## 1) Test Environment
- Low-voltage: ESP32 + 4-ch relay board + 5V/2A adapter
- Inputs: 4 × momentary NO buttons (to GND)
- Loads: 4 × LED bulbs (5–10 W), E27 holders
- AC: Fused Live → Relay COM bridge; NO → Bulb Lives; Neutral bus
- Tools: Serial Monitor (115200), multimeter (voltage/current), timer/stopwatch
- Network: 2.4 GHz Wi-Fi or phone hotspot

---

## 2) Acceptance Criteria (summary)
- **Connectivity:** ESP32 connects to Wi-Fi & Blynk within 30 s.
- **Control:** Each channel toggles via **App** and **Button**; update reflected in both within 300 ms.
- **Default State:** On power-up, all channels **OFF** (relays inactive) until commanded.
- **Debounce:** Single press → single toggle (no chatter).
- **Safety:** Fuse inline on Live; AC and DC wiring clearly separated and insulated.
- **Soak:** 30-minute ON test: no excessive heating or intermittent behavior.

---

## 3) Functional Tests

### 3.1 Low-Voltage Bring-Up
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Power ESP32 + relays only (no AC) | Board powers; no relays latched |
| 2 | Open Serial Monitor | Wi-Fi + Blynk connect messages |
| 3 | Press Button 1 | Serial shows `[CH1] -> ON/OFF`; Relay 1 clicks |
| 4 | Toggle V0 in app | Relay 1 clicks; Serial reflects state; app mirrors |
| 5 | Repeat for CH2–CH4 | All pass |

### 3.2 App–Button Consistency
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Turn CH1 ON in app | Relay ON; app shows ON |
| 2 | Press Button 1 once | Relay toggles OFF; app flips to OFF |
| 3 | Press Button 1 twice (slow) | Two toggles; app matches each |
| 4 | Long-press Button 1 | **One** toggle only (debounce ok) |

### 3.3 Power Cycle Behavior
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Set CH1=ON, CH2=OFF, CH3=ON, CH4=OFF | States set |
| 2 | Power cycle ESP32 | All relays default **OFF** at boot |
| 3 | After Blynk connect | `syncVirtual` aligns app and device (device keeps OFF until commanded) |

> Note: This prototype defaults **OFF** for safety. Document this in your report.

---

## 4) High-Voltage (AC) Tests — With Caution
**Pre-check:** Fuse installed; terminals insulated; clear AC/DC separation; supervisor present.

### 4.1 Single-Channel AC Test
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Wire CH1 only to bulb | Wiring checked |
| 2 | Apply AC | No sparks/smell; bulb OFF |
| 3 | Toggle V0 (or Button 1) | Bulb ON/OFF cleanly; no flicker |
| 4 | Measure current | Matches bulb rating; relay coil still cool |

### 4.2 Four-Channel AC Test
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Wire all 4 bulbs | Wiring checked |
| 2 | Turn all ON | All bulbs ON; adapter/relays stable |
| 3 | Turn all OFF | All bulbs OFF |

---

## 5) Soak & Thermal
- **Test:** Keep all four bulbs ON for **30 minutes**.
- **Observe:** No random toggles; relay board temperature acceptable (coil area ideally < ~60 °C).  
- **Record:** Ambient temp, any anomalies.

---

## 6) Network Resilience
| Step | Action | Expected |
|-----:|-------|----------|
| 1 | Disconnect Wi-Fi/hotspot | App shows offline; **buttons still work** |
| 2 | Reconnect Wi-Fi | Device reconnects; app syncs to current states within a few seconds |

---

## 7) Documentation Artifacts to Capture
- Photos of board layout (AC lane vs DC lane), fuse placement, labels
- Short video: Button press → app updates; App toggle → relay click → bulb ON
- Serial logs during tests (copy snippets)
- Cost table + final BOM links

---

## 8) Test Log Template

| Date | Tester | Test Case ID | Result (P/F) | Notes / Fixes |
|------|--------|--------------|--------------|---------------|
|      |        | LV-01        |              |               |
|      |        | LV-02        |              |               |
|      |        | AC-01        |              |               |
|      |        | AC-02        |              |               |
|      |        | SOAK-01      |              |               |
|      |        | NET-01       |              |               |

---

## 9) Risks & Mitigations
- **Mains safety:** Always fuse Live; insulate joints; never touch while powered.  
- **Relay logic inverted:** Flip `RELAY_ACTIVE_LOW`.  
- **Button bounce:** Increase `DEBOUNCE_MS`.  
- **Wi-Fi drop:** Buttons still work; state sync on reconnect.

