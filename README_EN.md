<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 1.6″ AMOLED 480×480 (CH13613 · QSPI)</h1>

<p align="center"><b>Round AMOLED module · QSPI · CH13613</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English</p>

<p align="center">
  <img alt="Size: 1.6 inch" src="https://img.shields.io/badge/Size-1.6%22-3498DB?style=flat-square" />
  <img alt="Resolution: 480x480" src="https://img.shields.io/badge/Resolution-480%C3%97480-8E44AD?style=flat-square" />
  <img alt="Interface: QSPI" src="https://img.shields.io/badge/Interface-QSPI-27AE60?style=flat-square" />
  <img alt="Driver: CH13613" src="https://img.shields.io/badge/Driver-CH13613-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 1.6″ 480×480 AMOLED QSPI module (CH13613) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **1.6″ 480×480 AMOLED** is a **QSPI** color display module driven by **CH13613**, with touch controller **CHSC6417**. The square resolution suits round wearables and compact HMI.

Spec ID (repository name): `1.6-amoled-480x480-qspi-ch13613`

Current module version: **AM160Q480480LK**. Electrical and mechanical details follow [`docs/AM_160_Q480480_LK_cb40223812.pdf`](./docs/AM_160_Q480480_LK_cb40223812.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 1.6 inch |
| Type | AMOLED (color) |
| Resolution | 480×480 |
| Interface | QSPI |
| Driver IC | CH13613 |
| Touch IC | CHSC6417 |

> Full outline, FPC definition, power, and timing follow the product datasheet / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-S3 · CH13613 QSPI + esp-lvgl-adapter / LVGL8 | [`examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/`](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/) |
| ESP32-S3 · CH13613 QSPI + esp-lvgl-adapter / LVGL9 | [`examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/`](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/) |
| ESP32-S3 · LVGL8 + TE | [`examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/`](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/) |
| ESP32-S3 · LVGL9 + TE | [`examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/`](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/) |

## Repository layout

```text
1.6-amoled-480x480-qspi-ch13613/
├── README.md
├── README_EN.md
├── MODULE_VERSION.md
├── LICENSE
├── images/          # README assets
├── docs/            # datasheets, init files
└── examples/        # sample projects
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Product datasheet (AM160Q480480LK) | [`docs/AM_160_Q480480_LK_cb40223812.pdf`](./docs/AM_160_Q480480_LK_cb40223812.pdf) |
| Driver IC datasheet (CH13613) | [`docs/CH_13613_SPEC_V1_0_for_customer_211101_205d382d5a.pdf`](./docs/CH_13613_SPEC_V1_0_for_customer_211101_205d382d5a.pdf) |
| Touch IC datasheet (CHSC6417) | [`docs/DS_CHSC_6417_EU_24_v1_3_1_f66256c159.pdf`](./docs/DS_CHSC_6417_EU_24_v1_3_1_f66256c159.pdf) |
| Board-to-board connector datasheet (OK-14F024-04) | [`docs/OK-14F024-04.pdf`](./docs/OK-14F024-04.pdf) |
| Init sequence (text) | [`docs/Truly160_480x480_CH13613_QSPI_init.txt`](./docs/Truly160_480x480_CH13613_QSPI_init.txt) |

### Samples

- [ESP32-S3 CH13613 QSPI + LVGL8](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/)
- [ESP32-S3 CH13613 QSPI + LVGL9](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/)
- [ESP32-S3 LVGL8 + TE](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/)
- [ESP32-S3 LVGL9 + TE](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group (China): **985881096**
- Website: <https://osptek.com/>

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
