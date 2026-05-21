# 1.6" 480×480 AMOLED QSPI module (CH13613) — documentation & samples

**简体中文：** [`README.md`](README.md)

---

> This repository provides **sample projects** for this module, together with datasheets, specifications, and interface / bring-up documentation for selection reference and integration.

## Product overview

| Item | Description |
|:--|:--|
| Module | 1.6-inch **AMOLED** panel, **480×480** resolution |
| Interface | **QSPI** |
| Driver IC | **CH13613** |
| Spec ID | **`1.6-amoled-480x480-qspi-ch13613`** is the common product designation in documentation |

---

## Repository layout

### Top-level

| Path | Contents |
|:--|:--|
| `docs/` | Datasheets, specifications, initialization notes, touch IC documentation |
| `examples/` | **Sample projects** by category |

### `examples/` layout

| Location | Description (internal package folder) |
|:--|:--|
| `examples/` root | **ESP-IDF代码** (esp-lvgl-adapter + LVGL8 / LVGL9) |
| `with-te/` | **屏幕防撕裂代码** |

### Sample project paths

#### Baseline (`examples/` root)

| Description | Path |
|:--|:--|
| esp-lvgl-adapter + LVGL8 | `examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/` |
| esp-lvgl-adapter + LVGL9 | `examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/` |

#### Tear avoidance (`with-te/`)

| Description | Path |
|:--|:--|
| esp-lvgl-adapter + LVGL8 + AMOLED, with TE | `examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/` |
| esp-lvgl-adapter + LVGL9 + AMOLED, with TE | `examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/` |
