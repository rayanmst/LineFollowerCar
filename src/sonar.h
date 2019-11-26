/*
 * sonar.h
 *
 *  Created on: 12 de nov de 2019
 *      Author: rayan
 */

#ifndef LIB_SONAR_H_
#define LIB_SONAR_H_

#define SONAR_PORT GPIO_B
#define SONAR_ENABLE_PIN  PB5

void sonar_init();
uint64_t get_dist();


#endif /* LIB_SONAR_H_ */
