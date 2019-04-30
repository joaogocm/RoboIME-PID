/*
 * Robo.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: lenovoi7
 */

#include "Robo.h"
#include "pins.h"

#define sin_phi 0.50
#define cos_phi 0.866
#define sin_theta 0.707
#define cos_theta 0.707

/*#define alfa 1
#define Massa 3
#define Raio 0.09*/

Robo::Robo(Motor *roboMotor0, Motor *roboMotor1, Motor *roboMotor2, Motor *roboMotor3)
{
	motor[0]=roboMotor0;
	motor[1]=roboMotor1;
	motor[2]=roboMotor2;
	motor[3]=roboMotor3;
	this->init();
}

void Robo::init()
{
	for (int i=0; i<4; i++){
		motor[i]->Control_Speed(0);
	}
}

/*void Robo::set_robo_speed()
{
  float v0= motor[0]->real_wheel_speed;
  float v1= motor[1]->real_wheel_speed;
  float v2= motor[2]->real_wheel_speed;
  float v3= motor[3]->real_wheel_speed;

  float proj=-0.5477*v0+0.4472*v1+0.5477*v2-0.4472*v3;

    if(proj<1 && proj>-1){
    	for(int i=0; i<4; i++){
    		motor[i]->Control_Speed(speed[i]); //manda a velocidade speed[i] pro motor[i] na unidade m/s
    	}
    }
    else {
    	//nem o valor de alfa nem a massa interferem no espaço nulo.
    	speed[0]=v0-(-0.5477*v0+0.4472*v1+0.5477*v2-0.4472*v3)*(-0.5477);
    	speed[1]=v1-(-0.5477*v0+0.4472*v1+0.5477*v2-0.4472*v3)*(0.4472);
    	speed[2]=v2-(-0.5477*v0+0.4472*v1+0.5477*v2-0.4472*v3)*(0.5477);
    	speed[3]=v3-(-0.5477*v0+0.4472*v1+0.5477*v2-0.4472*v3)*(-0.4472);
    	for(int i=0; i<4; i++){
     		motors[i]->Control_Speed(speed[i]); //manda a velocidade speed[i] pro motor[i] na unidade m/s
     	}
    }//

}*/

//armazena as velocidades lineares dos centros das RODAS em real_wheel_speed[]
void Robo::get_wheel_speed()
{
	for (int i=0; i<4; i++){
		motor[i]->Get_Speed();
		real_wheel_speed[i]=motor[i]->real_wheel_speed;
	}
}

//recebe as velocidades radial, tangente em m/s e w em rad/s
//grava em speed[] os valores em m/s da velocidade DAS RODAS
void Robo::control_robo_speed(float v_r, float v_t, float w)
{
	float R = 0.075; //Raio do robo = 9cm

	speed[0] = v_t*cos_phi - v_r*sin_phi + w*R;
	speed[2] = -v_t*cos_phi - v_r*sin_phi + w*R;
	speed[3] = -v_t*cos_theta + v_r*sin_theta + w*R;
	speed[1] = v_t*cos_theta + v_r*sin_theta + w*R;
	//speed[] = 0.176; //teste: para cada roda girar com período 1s
	//speed[] está em m/s. Cuidado para manter a mesma unidade qnd passar pros motores

	for (int i=0; i<4; i++){
		control_motor_speed(i, speed[i]);
	}
}

void Robo::control_robo_speed(float Mx_speed[])
{
	for (int i=0; i<4; i++){
		control_motor_speed(i, speed[i]);
	}
}

void Robo::set_robo_speed(float Mx_speed[]) //envia velocidades pré definidas, sem controle, para os motores
{
	for (int i=0; i<4; i++){
		set_motor_speed(i, Mx_speed[i]);
	}
}


void Robo::get_robo_speed() //calcula velocidade atual do robo com os valores medidos pelo encoder
{
	get_wheel_speed();
}

void Robo::control_motor_speed(int Mx, float Mx_speed) //envia velocidade para o motor Mx, com controle
{
	if(Mx<4){
		motor[Mx]->Control_Speed(Mx_speed);
	}
}

void Robo::set_motor_speed(int Mx, float Mx_speed) //envia velocidade para o motor Mx, sem controle
{
	if(Mx<4){
		motor[Mx]->Set_Speed(Mx_speed);
	}
}

void Robo::set_pid(float p, float i, float d)
{
	for (int i=0; i<4; i++){
		motor[i]->SetPID(p, i, d);
	}
}

void Robo::get_pid(void)
{
	float *c;
	motor[0]->GetPID(c);
	kp=c[0];
	ki=c[1];
	kd=c[2];
}

void Robo::interrupt_control()
{
	//get_wheel_speed(robo.real_wheel_speed); //update real_wheel_speed com as velocidades medidas

}


