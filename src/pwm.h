/*
 * pwm.h
 *
 *  Created on: 4 de out de 2019
 *      Author: rayan
 */

#ifndef LIB_PWM_H_
#define LIB_PWM_H_

/**
  * @brief  Inicia a configuração do pwm.
  * @param	Nenhum
  *
  * @retval Nenhum.
  */
void pwmInit();

/**
  * @brief  Move o carro para frente.
  * @param	imSpeed: Define o duty cycle do pwm.
  *
  * @retval Nenhum.
  */
void goAhead(uint8_t imSpeed);

/**
  * @brief  Move o carro para trás.
  * @param	imSpeed: Define o duty cycle do pwm.
  *
  * @retval Nenhum.
  */
void goBack(uint8_t imSpeed);

/**
  * @brief  Move o carro para esquerda.
  * @param	imSpeed: Define o duty cycle do pwm.
  *
  * @retval Nenhum.
  */
void toLeft(uint8_t imSpeed);

/**
  * @brief  Move o motor para direita.
  * @param	imSpeed: Define o duty cycle do pwm.
  *
  * @retval Nenhum.
  */
void toRight(uint8_t imSpeed);

void itsTimeToStop();

/**
  * @brief  Define o movimento do carro.
  * @param	imSpeed: Define o duty cycle do pwm.
  *
  * @retval Nenhum.
  */
void move(uint8_t imSpeed, uint8_t data);

#endif /* LIB_PWM_H_ */
