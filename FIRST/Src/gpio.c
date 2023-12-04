/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Pinout Configuration
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 2 */
/*�������ò�*/

/**
  * ��    ����SPIдSS���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SS�ĵ�ƽ����Χ0~1
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SSΪ�͵�ƽ����BitValueΪ1ʱ����Ҫ��SSΪ�ߵ�ƽ
  */
void MySPI_W_SS(uint8_t BitValue)
{
	
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (GPIO_PinState)BitValue);
		
}

/**
  * ��    ����SPIдSCK���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SCK�ĵ�ƽ����Χ0~1
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SCKΪ�͵�ƽ����BitValueΪ1ʱ����Ҫ��SCKΪ�ߵ�ƽ
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	// ��� GPIO_WriteBit
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (GPIO_PinState)BitValue);
		//����BitValue������SCK���ŵĵ�ƽ
}

/**
  * ��    ����SPIдMOSI���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��MOSI�ĵ�ƽ����Χ0~0xFF
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��MOSIΪ�͵�ƽ����BitValue��0ʱ����Ҫ��MOSIΪ�ߵ�ƽ
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	// ��� GPIO_WriteBit
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (GPIO_PinState)BitValue);
		//����BitValue������MOSI���ŵĵ�ƽ��BitValueҪʵ�ַ�0��1������
}

/**
  * ��    ����I2C��MISO���ŵ�ƽ
  * ��    ������
  * �� �� ֵ��Э�����Ҫ�õ��ĵ�ǰMISO�ĵ�ƽ����Χ0~1
  * ע������˺�����Ҫ�û�ʵ�����ݣ���ǰMISOΪ�͵�ƽʱ������0����ǰMISOΪ�ߵ�ƽʱ������1
  */
uint8_t MySPI_R_MISO(void)
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);		//��ȡMISO��ƽ������
}

/**
  * ��    ����SPI��ʼ��
  * ��    ������
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ�ʵ��SS��SCK��MOSI��MISO���ŵĳ�ʼ��
  */

 
/*Э���*/

/**
  * ��    ����SPI��ʼ
  * ��    ������
  * �� �� ֵ����
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//����SS����ʼʱ��
}

/**
  * ��    ����SPI��ֹ
  * ��    ������
  * �� �� ֵ����
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//����SS����ֹʱ��
}

/**
  * ��    ����SPI��������һ���ֽڣ�ʹ��SPIģʽ0
  * ��    ����ByteSend Ҫ���͵�һ���ֽ�
  * �� �� ֵ�����յ�һ���ֽ�
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;					//������յ����ݣ�������ֵ0x00���˴����븳��ֵ0x00��������õ�
	
	for (i = 0; i < 8; i ++)						//ѭ��8�Σ����ν���ÿһλ����
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));		//ʹ������ķ�ʽȡ��ByteSend��ָ��һλ���ݲ�д�뵽MOSI��
		MySPI_W_SCK(1);								//����SCK���������Ƴ�����
		if (MySPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}	//��ȡMISO���ݣ����洢��Byte����
																//��MISOΪ1ʱ���ñ���ָ��λΪ1����MISOΪ0ʱ����������ָ��λΪĬ�ϵĳ�ֵ0
		MySPI_W_SCK(0);								//����SCK���½�����������
	}
	
	return ByteReceive;								//���ؽ��յ���һ���ֽ�����
}
/* USER CODE END 2 */
