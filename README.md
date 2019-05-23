# [STM8L15x](https://github.com/sochub/STM8L15) 

[![sites](SoC/SoC.png)](http://www.qitas.cn) 

#### 厂商：[ST](https://github.com/sochub/ST)

#### 架构：[STM8](https://github.com/sochub/STM8)

### [描述](https://github.com/sochub/STM8L15/wiki) 

主要针对8051市场替换，产品特点是提供低功耗设计

STM8L151xx(without LCD)：

    STM8L151C4, STM8L151C6, STM8L151K4,STM8L151K6, STM8L151G4, STM8L151G6
STM8L152xx(with LCD)：

    STM8L152C4, STM8L152C6, STM8L152K4, STM8L152K6

STM8L151/152 offer more performance and features compared to STM8L101.

Based on 16 MHz proprietary STM8 core, up to 64 Kbytes of Flash program memory, 4 Kbytes of SRAM and up to 2 Kbytes of data EEPROM

packages from 20 to 80 pins， 12-bit ADC and DAC

[![sites](SoC/STM8L15.png)](https://www.st.com/en/microcontrollers-microprocessors/STM8L15-series.html) 


### [内部收录](https://github.com/sochub/STM8L15)

* [资源](src/)
* [文档](docs/)
* [工程](project/)

### [外部收录](https://github.com/sochub/STM8)

* [Arduino for STM8](https://github.com/stm32duino/Arduino_Core_STM8)

### [选型建议](https://github.com/sochub/STM8L15)

同系列的STM8L151/152主要区别在于是否有LCD控制器，段式液晶驱动器可以驱动4x28=112个液晶段

向下替换方案[STM8L05x](https://github.com/sochub/STM8L0) 和[STM8L10x](https://github.com/sochub/STM8L10) 

向上替换方案[STM32L0](https://github.com/sochub/STM32L0) 和[STM32L1](https://github.com/sochub/STM32L1) 

极低功耗方案可以考虑TI的[MSP430](https://github.com/sochub/MSP430) 和[MSP432](https://github.com/sochub/MSP432) 

##  [SoC资源平台](http://www.qitas.cn)  
