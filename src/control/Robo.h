/*
 * Robo.h
 *
 *  Created on: Jul 9, 2016
 *      Author: lenovoi7
 */
#ifndef ROBO_H_
#define ROBO_H_

#include <cstring>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "GPIO.h"
#include "Pwm.h"
#include "Encoder.h"
#include "TimerTime2.h"
#include "Motor.h"



class Robo {
public:
	Robo(Motor *roboMotor0, Motor *roboMotor1, Motor *roboMotor2, Motor *roboMotor3);

	float speed[4]; //velocidade desejada para cada roda
	float real_wheel_speed[4]; //armazenará as velocidades medidas (m/s) das RODAS
   	int16_t dutycycles[4];

    Motor *motor[4];

    void init();

    //controle do robo como um todo
    void control_robo_speed(float v_r, float v_t, float w);
    void control_robo_speed(float Mx_speed[]);
    void set_robo_speed(float Mx_speed[]);
    void get_robo_speed();

    //controle de rodas separadas
    void control_motor_speed(int Mx, float Mx_speed);
    void set_motor_speed(int Mx, float Mx_speed);
    void get_wheel_speed();

    void set_pid(float p, float i, float d);
    void get_pid();

    void interrupt_control();

    float kp, ki, kd;
private:
   	float y_speed, x_speed, w;
};
extern Robo robo;
#endif /* ROBO_H_ */
