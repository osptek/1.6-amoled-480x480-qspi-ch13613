<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 1.6″ AMOLED 480×480（CH13613 · QSPI）</h1>

<p align="center"><b>圆形 AMOLED 模组 · QSPI · CH13613</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文</p>

<p align="center">
  <img alt="Size: 1.6 inch" src="https://img.shields.io/badge/Size-1.6%22-3498DB?style=flat-square" />
  <img alt="Resolution: 480x480" src="https://img.shields.io/badge/Resolution-480%C3%97480-8E44AD?style=flat-square" />
  <img alt="Interface: QSPI" src="https://img.shields.io/badge/Interface-QSPI-27AE60?style=flat-square" />
  <img alt="Driver: CH13613" src="https://img.shields.io/badge/Driver-CH13613-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 1.6 寸 480×480 AMOLED QSPI 模组（CH13613）宣传图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **1.6 寸 480×480 AMOLED** 是一款 **QSPI** 接口彩色显示模组，显示驱动为 **CH13613**，触摸驱动为 **CHSC6417**。方形分辨率适合圆形穿戴表盘与紧凑 HMI 等场景。

规格标识（仓库名）：`1.6-amoled-480x480-qspi-ch13613`

当前模组版本：**AM160Q480480LK**。电气与外形细节以 [`docs/AM_160_Q480480_LK_cb40223812.pdf`](./docs/AM_160_Q480480_LK_cb40223812.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 1.6 英寸 |
| 类型 | AMOLED（彩色） |
| 分辨率 | 480×480 |
| 接口 | QSPI |
| 驱动 IC | CH13613 |
| 触摸驱动 | CHSC6417 |

> 完整外形尺寸、FPC 定义、供电与时序以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-S3 · CH13613 QSPI + esp-lvgl-adapter / LVGL8 | [`examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/`](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/) |
| ESP32-S3 · CH13613 QSPI + esp-lvgl-adapter / LVGL9 | [`examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/`](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/) |
| ESP32-S3 · LVGL8 + TE 防撕裂 | [`examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/`](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/) |
| ESP32-S3 · LVGL9 + TE 防撕裂 | [`examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/`](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/) |

## 仓库结构

```text
1.6-amoled-480x480-qspi-ch13613/
├── README.md
├── README_EN.md
├── MODULE_VERSION.md
├── LICENSE
├── images/          # README 用图
├── docs/            # 规格书、驱动手册、初始化等
└── examples/        # 示例工程
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 产品规格书（AM160Q480480LK） | [`docs/AM_160_Q480480_LK_cb40223812.pdf`](./docs/AM_160_Q480480_LK_cb40223812.pdf) |
| 驱动 IC 数据手册（CH13613） | [`docs/CH_13613_SPEC_V1_0_for_customer_211101_205d382d5a.pdf`](./docs/CH_13613_SPEC_V1_0_for_customer_211101_205d382d5a.pdf) |
| 触摸 IC 数据手册（CHSC6417） | [`docs/DS_CHSC_6417_EU_24_v1_3_1_f66256c159.pdf`](./docs/DS_CHSC_6417_EU_24_v1_3_1_f66256c159.pdf) |
| 板对板连接器规格（OK-14F024-04） | [`docs/OK-14F024-04.pdf`](./docs/OK-14F024-04.pdf) |
| 初始化序列（文本） | [`docs/Truly160_480x480_CH13613_QSPI_init.txt`](./docs/Truly160_480x480_CH13613_QSPI_init.txt) |

### 示例工程

- [ESP32-S3 CH13613 QSPI + LVGL8](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8/)
- [ESP32-S3 CH13613 QSPI + LVGL9](./examples/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9/)
- [ESP32-S3 LVGL8 + TE](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl8_amoled-with-te/)
- [ESP32-S3 LVGL9 + TE](./examples/with-te/esp32s3-idf5_ch13613-qspi_esp-lvgl-adapter_lvgl9_amoled-with-te/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-FF6A00?style=for-the-badge" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
