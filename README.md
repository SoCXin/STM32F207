# [STM32F207](https://github.com/SoCXin/STM32F207)

[![sites](http://182.61.61.133/link/resources/SoC.png)](http://www.SoC.Xin)

[![Build Status](https://github.com/SoCXin/STM32F207/workflows/src/badge.svg)](https://github.com/SoCXin/STM32F207/actions/workflows/src.yml)

* [ST](https://www.st.com/zh/): [Cortex-M3](https://github.com/SoCXin/Cortex)
* [L4R5](https://github.com/SoCXin/Level): 120 MHz (150DMIPS/398CoreMark)

## [简介](https://github.com/SoCXin/STM32F207/wiki)

[STM32F207](https://github.com/SoCXin/STM32F207) 系列采用意法90nm NVM制程制造而成，具有创新型自适应实时存储加速器（ART Accelerator™）和多层总线矩阵，实现了前所未有的高性价比。

[![sites](docs/STM32F207.png)](https://www.st.com/zh/microcontrollers-microprocessors/stm32f2x7.html)

### 关键特性

* 以太网 MAC10/100
* 2 x USB OTG (其中一个支持HS)
* 15个通信接口(6个7.5 Mb/s的USART、3个30 Mb/s的SPI、3个I²C、2个CAN、SDIO)
* 2x12bit DAC, 24ch 3x12bit ADC 2MSPS(交错模式6MSPS)
* STM32F215/STM32F217整合加密/HASH处理器，为AES 128、192、256、Triple DES和HASH(MD5、SHA-1)提供硬件加速。

### [资源收录](https://github.com/SoCXin)

* [参考资源](src/)
* [参考文档](docs/)
* [参考工程](project/)

### [选型建议](https://github.com/SoCXin)

[STM32F207](https://www.st.com/zh/microcontrollers-microprocessors/stm32f2x7.html)是STM32高性能MCU的入门级产品，已经比较悠久，相较低配版本[STM32F205](https://www.st.com/zh/microcontrollers-microprocessors/stm32f2x5.html) 增加了符合IEEE 1588 v2标准要求的以太网MAC10/100和能够连接CMOS照相机传感器的8-14位并行摄像头接口，并且只有100-176引脚封装。STM32F21X相对同型号STM32F20X增加了硬件加密单元。

选择STM32F2系列是为兼容性和成熟的STM32开发生态（可靠性、资源和工程师），选择STM32F207则是在此基础上获得以太网MAC用于扩展网络应用，其次获得比F1系列进阶的片上资源，而STM32F103具备的MCU史上里程碑的开源资源可以借用过来，STM32F2系列的另一个亮点在于多出的USB OTG HS接口。

不选择[STM32F207](https://github.com/SoCXin/STM32F207)的理由则是因为有[STM32F407](https://github.com/SoCXin/STM32F407)等存在提供了更多技术/参数吸引力，特别是在开源项目上，后者拥有更高的优先级和更多的使用者。

#### 封装规格

* STM32F205R: WLCSP66(4×4mm)、LQFP64(10×10mm)
* STM32F207V: LQFP100 (14×14mm)
* STM32F207Z: LQFP144 (20×20mm)
* STM32F207I: BGA/LQFP176

[STM32F2系列](https://www.st.com/zh/microcontrollers-microprocessors/stm32f2-series.html)与[STM32F1系列](https://www.st.com/zh/microcontrollers-microprocessors/stm32f1-series.html)外设兼容性：

[![sites](docs/F1VSF2.jpg)](http://www.elecfans.com/d/1153505.html)

### 相关开发板 (NUCLEO-F207ZG)

[![sites](docs/B.jpg)](https://detail.tmall.com/item.htm?spm=a230r.1.14.18.f8d755adypkmDs&id=613173541804&ns=1&abbucket=19)

#### 高完成度开源项目

* [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)
* [STM32CubeF2](https://github.com/STMicroelectronics/STM32CubeF2)


### [探索芯世界 www.SoC.xin](http://www.SoC.Xin)
