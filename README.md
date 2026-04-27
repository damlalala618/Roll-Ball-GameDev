# Bridge Collect-Dodge Runner

A browser-based 3D runner game controlled by a physical joystick via ESP32-C3. Move your ball across a bridge, collect glowing items, and dodge obstacles — all with a real hardware controller.

> **Damla Gedikli & Yingxun** — Interface Technologies, HfG, SEM 4

---

## Demo

<video src="Bildschirmaufnahme 2026-04-28 um 00.23.42.mov" controls width="100%"></video>

> If the video does not play above, [download it here](Bildschirmaufnahme%202026-04-28%20um%2000.23.42.mov).

---

## How It Works

The ESP32-C3 reads a joystick (X/Y axes via ADC + button via GPIO) and sends single-character commands over USB serial at 115200 baud. The browser game listens over **Web Serial API** and maps those commands to in-game controls.

```
ESP32-C3  ──USB Serial──▶  Browser (Web Serial)  ──▶  Game Logic
```

### Controls

| Joystick Input | Serial Output | Action |
|---|---|---|
| X > +600 | `R` | Move right |
| X < −600 | `L` | Move left |
| Y < −600 | `U` | Speed up / Start game |
| Y > +600 | `D` | Slow down |
| Button press | `C` | Restart game |

---

## Game Rules

- **Collectibles** (cyan) — spawn every 1–2 s, +50 points on contact
- **Obstacles** (red) — spawn every 6–9 s, block a lane — GAME OVER on contact
- Press `U` to start, `C` to restart after game over

---

## Project Structure

```
├── esp32/
│   ├── src/main.c          # Joystick ADC + serial output
│   └── platformio.ini      # ESP32-C3 PlatformIO config
└── web/
    ├── index.html          # Main game (Web Serial)
    └── index_canvas.html   # Canvas variant
```

---

## Setup

### ESP32 Firmware

1. Open the `esp32/` folder in [PlatformIO](https://platformio.org/)
2. Connect the joystick:
   - X axis → GPIO 4 (ADC1_CH4)
   - Y axis → GPIO 3 (ADC1_CH3)
   - Button → GPIO 2 (pull-up)
3. Flash: `pio run --target upload`

### Web Game

1. Open `web/index.html` in Chrome or Edge (Web Serial required)
2. Click **Connect** and select the ESP32 serial port
3. Press the joystick up (`U`) to start
