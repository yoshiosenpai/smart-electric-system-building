
---

### `docs/faq.md`

```markdown
# FAQ — Smart Electric System (FYP Prototype)

## General
**Q: Is this safe for permanent home use?**  
A: No. This is a **demo prototype** on a wooden board. It is not certified for household installation.

**Q: Why do we use Blynk “Virtual Pins” instead of Digital Pins?**  
A: Virtual Pins decouple app UI from hardware pins, making sync and logic handling easier (e.g., buttons + app + debouncing).

---

## Connectivity
**Q: ESP32 won’t connect to Wi-Fi.**  
- Use **2.4 GHz** SSID (no 5 GHz).  
- Check SSID/PASS spelling; avoid special characters.  
- Try a phone hotspot for demo stability.

**Q: Blynk stays offline.**  
- Verify `BLYNK_AUTH_TOKEN`.  
- Log into the **same Blynk region** on Console and App.  
- Ensure the device is created from the **same template** with V0–V3.

---

## Relays & Buttons
**Q: Relays click ON when I expect OFF.**  
- Your module might be active-HIGH. Set `RELAY_ACTIVE_LOW = false;`

**Q: Buttons don’t toggle reliably.**  
- Confirm wiring: **GPIO ↔ Button ↔ GND**; use `INPUT_PULLUP`.  
- Increase debounce: `DEBOUNCE_MS` to 150–200 ms.

**Q: Why momentary (NO) buttons, not latching switches?**  
- With Option A, ESP32 is the “logic switch”. Momentary inputs produce clean events; firmware maintains the true state and syncs to Blynk.

---

## Power & Safety
**Q: What fuse rating should I use?**  
- Inline fuse on **Live**; typical **2–3 A slow-blow** for 4 × 5–10 W LED bulbs (low current). Adjust for your local mains and load.

**Q: The relay board gets warm. Is that normal?**  
- Mild warmth is okay. Run a **15–30 min soak test**; keep relay coil area <~60 °C. Improve spacing/ventilation on the board.

---

## Features & Extensions
**Q: Can I add schedules/automation?**  
- Yes, use Blynk Automation or add firmware timers (e.g., `BlynkTimer`).

**Q: Can I see the *actual* lamp state if someone changes mains?**  
- That’s **Option B** (AC sensing). For FYP safety, we stick to Option A. You can demo Option B on one channel with an isolated AC sensor if required.

**Q: Can I add OTA updates?**  
- Yes (ArduinoOTA or AsyncElegantOTA). Not required for this FYP, but nice bonus.

---

## Presentation Tips
- Show both **App control** and **Button control**.  
- Keep AC and DC lanes separated; use big **CAUTION: 230V/120V AC** label.  
- Bring a short **demo script** and a **multimeter** for current checks.

