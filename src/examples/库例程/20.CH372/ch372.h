#ifndef _ch372_h_
#define _ch372_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/

#define CH372_CS_PORT (GPIOB)
#define CH372_CS_PIN  (GPIO_Pin_0)

#define CH372_AO_PORT (GPIOB)
#define CH372_AO_PIN  (GPIO_Pin_1)

#define CH372_WR_PORT (GPIOB)
#define CH372_WR_PIN  (GPIO_Pin_2)

#define CH372_RD_PORT (GPIOB)
#define CH372_RD_PIN  (GPIO_Pin_3)

#define CH372_INT_PORT (GPIOB)
#define CH372_INT_PIN  (GPIO_Pin_4)

#define CH372_DATA_PORT (GPIOD)

extern void CH372_Init(void);
extern void CH372_WR_CMD(s8 Cmd);
extern void CH372_WR_CMD(s8 Cmd);
extern s8 CH372_RD_DAT(void);
extern void Delay(unsigned int nCount);
extern void CH372_WR_DAT(s8 Dat);
#endif