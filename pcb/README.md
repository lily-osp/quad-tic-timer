# Quad-Tic-Timer: ATtiny85 Synchronized Robotic Pulse Generator PCB

A 30x30mm 2-layer KiCad 9 development board for the **Quad-Tic-Timer** firmware. Driven by an **Atmel ATtiny85-20SU**, it provides four synchronized phase-accurate pulse outputs scaled exponentially by a single precision 10-turn control pot.

Designed and verified using the **pcb** skill with full **KiCad 9** headless tooling and production-ready **JLCPCB** fabrication deliverables.

---

## 📌 3D Render Previews

| Top Side (Components & Telemetry) | Bottom Side (Ground Plane & Labeling) |
| :---: | :---: |
| ![Top 3D Render](jlcpcb_production/quad-tic-timer_render_top.png) | ![Bottom 3D Render](jlcpcb_production/quad-tic-timer_render_bottom.png) |

---

## ⚡ Hardware Architecture & Features

- **Microcontroller**: Microchip / Atmel **ATtiny85-20SU** (SOIC-8, 8 MHz internal calibrated RC oscillator).
- **Quad Synchronized Pulse Outputs**:
  - `O1` (PB0 / Pin 5): 1.00 s/tic nominal (0.20 s – 5.00 s range)
  - `O2` (PB1 / Pin 6): 0.75 s/tic nominal (0.15 s – 3.75 s range)
  - `O3` (PB2 / Pin 7): 0.50 s/tic nominal (0.10 s – 2.50 s range)
  - `O4` (PB4 / Pin 3): 0.25 s/tic nominal (0.05 s – 1.25 s range)
- **Dual Potentiometer Sourcing**:
  - **Onboard Trimmer**: Bourns 3296W vertical 10k 25-turn potentiometer (`RV1`).
  - **External Pot Header**: 1x03 2.54mm pin header (`JEXT`) for panel-mount 10-turn pots (Bourns 3590S).
  - **Source Select Jumper**: 1x03 2.54mm header (`JP1`). Jumper pins 1-2 for onboard trimmer, 2-3 for external pot.
- **Power & Conditioning**:
  - `C1` (100nF 0805): Dedicated VCC decoupling placed within 2 mm of U1 pin 8.
  - `C2` (10nF 0805): Low-pass noise filter on ADC3 wiper input (U1 pin 2).
  - `R5` (10k 0805): Pull-up on RESET (pin 1) keeping reset line high while leaving it ISP-programmable.
  - `JPWR` (1x02): 5V DC input.
- **Visual Status Telemetry**:
  - Four independent 0805 LEDs (`D1`–`D4`) driven through 1kΩ ballast resistors (`R1`–`R4`) indicating pulse ticks on each channel.
- **Output Interface**:
  - `JOUT` (1x06 2.54mm header): Exposes `O1`, `O2`, `O3`, `O4`, `VCC`, and `GND`.
- **Board Specifications**:
  - Form factor: **30.0 mm x 30.0 mm** with 2.0 mm corner chamfers.
  - Layer stack: 2-layer (1.6 mm FR4, 1 oz Cu, HASL lead-free).
  - Bottom layer: Continuous low-impedance ground plane (`B.Cu`).
  - Free prototype rule compliant (well within JLCPCB 100x100mm bounds).

---

## 🗂️ Project Deliverables (Zero Bloat)

```text
quad-tic-timer/pcb/
├── README.md                      # Comprehensive technical hardware documentation
├── fp-info-cache                  # KiCad footprint library cache
├── quad-tic-timer.kicad_pro       # KiCad 9 project file
├── quad-tic-timer.kicad_prl       # KiCad 9 local settings file
├── quad-tic-timer.kicad_sch       # KiCad 9 complete schematic with embedded symbols
├── quad-tic-timer.kicad_pcb       # KiCad 9 fully routed board (0 DRC, 0 unconnected)
├── quad-tic-timer-drc.rpt         # Official KiCad DRC report (0 errors, 0 warnings)
├── quad-tic-timer-erc.rpt         # Official KiCad ERC report (0 errors, 0 warnings)
└── jlcpcb_production/             # Turn-key manufacturing archive
    ├── quad-tic-timer_gerber_jlcpcb.zip  # RS-274X Gerbers + Excellon NC drills
    ├── quad-tic-timer_bom_jlcpcb.csv     # Bill of Materials formatted for JLCPCB
    ├── quad-tic-timer_cpl_jlcpcb.csv     # Pick-and-place centroid coordinate file
    ├── quad-tic-timer_render_top.png     # Photorealistic 3D top render
    └── quad-tic-timer_render_bottom.png  # Photorealistic 3D bottom render
```

---

## ⚡ Bill of Materials (BOM)

| Designator | Description | Footprint | LCSC Part # | Qty |
| :--- | :--- | :--- | :--- | :--- |
| **U1** | ATtiny85-20SU 8-bit AVR Microcontroller | SOIC-8_3.9x4.9mm_P1.27mm | C44533 | 1 |
| **RV1** | 10k Precision Multi-turn Trimpot | Bourns_3296W_Vertical | C180126 | 1 |
| **C1** | 100nF 50V Ceramic Capacitor | C_0805_2012Metric | C49678 | 1 |
| **C2** | 10nF 50V Ceramic Capacitor | C_0805_2012Metric | C1710 | 1 |
| **R5** | 10kΩ 1% 1/8W Pullup Resistor | R_0805_2012Metric | C17414 | 1 |
| **R1–R4** | 1kΩ 1% 1/8W LED Current-Limiters | R_0805_2012Metric | C17513 | 4 |
| **D1–D4** | Green LED Indicators | LED_0805_2012Metric | C2297 | 4 |
| **JPWR** | 1x02 2.54mm Pin Header (Power In) | PinHeader_1x02_P2.54mm_Vertical | C2241 | 1 |
| **JP1** | 1x03 2.54mm Pin Header (Pot Select) | PinHeader_1x03_P2.54mm_Vertical | C2242 | 1 |
| **JEXT** | 1x03 2.54mm Pin Header (Ext Pot) | PinHeader_1x03_P2.54mm_Vertical | C2242 | 1 |
| **JOUT** | 1x06 2.54mm Pin Header (Signal Out) | PinHeader_1x06_P2.54mm_Vertical | C2245 | 1 |

---

## 🔍 Verification & Quality Assurance

1. **Pre-flight Placement Validation**:
   - Courtyard overlaps: **0 collisions**
   - Minimum edge clearance: **> 0.5 mm** across all footprints
2. **Electrical Rules Check (ERC)**:
   - `quad-tic-timer-erc.rpt`: **0 errors, 0 warnings**
   - All 47 electrical nodes matched 1:1 with PCB netlist
3. **Design Rules Check (DRC)**:
   - `quad-tic-timer-drc.rpt`: **0 errors, 0 warnings, 0 unconnected items**
   - Minimum track width: 0.25 mm (well above 0.15 mm JLCPCB limit)
   - Minimum track clearance: 0.20 mm
   - Minimum via drill/diameter: 0.30 mm / 0.60 mm
4. **Manufacturing Package Integrity**:
   - Drill Census: 27 drilled holes (2 files, PTH + NPTH)
   - Board outline verified on `Edge_Cuts` (`.gm1`)
   - Gerbers tested and packaged into `quad-tic-timer_gerber_jlcpcb.zip` ready for one-click upload.
