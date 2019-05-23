# [STM8L15x](https://github.com/sochub/STM8L15) 

[![sites](SoC/SoC.png)](http://www.qitas.cn) 

#### 父级：[STM8L](https://github.com/sochub/STM8L)

#### 架构：[STM8](https://github.com/sochub/STM8)

### [描述](https://github.com/sochub/STM8L15/wiki) 

主要针对8051市场替换，产品特点是提供低功耗设计，拥有各种不同规格的产品线。

STM8L151xx(without LCD)：

    STM8L151C4, STM8L151C6, STM8L151K4,STM8L151K6, STM8L151G4, STM8L151G6
STM8L152xx(with LCD)：

    STM8L152C4, STM8L152C6, STM8L152K4, STM8L152K6

STM8L151/152 是STM8L系列中较高端的存在，提供优于STM8L101的性能，推荐(常用)型号STM8L151K4

[![sites](SoC/STM8L15.png)](https://www.st.com/en/microcontrollers-microprocessors/STM8L15-series.html) 

关键参数：
* 16 MHz STM8 core
* 4 Kbytes of SRAM 
* 2 Kbytes of EEPROM
* 64 Kbytes of Flash
* 12-bit ADC and DAC

芯片封装：

    TSSOP20、QFN20、QFN32、QFN48
    LQFP32、LQFP48、LQFP64、LQFP80

### [内部收录](https://github.com/sochub/STM8L15)

* [文档](docs/)
* [资源](src/)
    * [Bootloader](src/Bootloader)
    * [IAR](src/IAR)
    * [STVD](src/STVD)
    * [SDCC](src/SDCC)
* [contiki系统工程](contiki/)

### [外部收录](https://github.com/sochub/STM8)

* [Arduino for STM8](https://github.com/stm32duino/Arduino_Core_STM8)

### [选型建议](https://github.com/sochub/STM8L15)

同系列的STM8L151/152主要区别在于是否有LCD控制器，段式液晶驱动器可以驱动4x28=112个液晶段。

向下替换方案[STM8L0x](https://github.com/sochub/STM8L0) 和[STM8L10x](https://github.com/sochub/STM8L10) 

向上替换方案[STM32L0](https://github.com/sochub/STM32L0) 和[STM32L1](https://github.com/sochub/STM32L1) 

极低功耗方案可以考虑TI的[MSP430](https://github.com/sochub/MSP430) 和[MSP432](https://github.com/sochub/MSP432) 

##  [SoC资源平台](http://www.qitas.cn)  
