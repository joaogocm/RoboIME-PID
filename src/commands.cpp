#include "utils/commandline.h"
#include "control/Robo.h"

extern CommandLine cmdline;

extern Robo robo;


uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];

	if(argc==1){
		robo.get_pid();
		size+=sprintf(buffer+size, "%d %d %d\r\n", (int)robo.kp, (int)robo.ki, (int)robo.kd);
		size+=sprintf(buffer+size, "%d %d %d %d\r\n", (int)robo.speed[0], (int)robo.speed[1], (int)robo.speed[2], (int)robo.speed[3]);
	}
	else if(argc==2){
		//desired_speed = atoi((char*)argv8[1]);

		size+=sprintf(buffer+size, "%d %d %d %d\r\n", (int)robo.speed[0], (int)robo.speed[1], (int)robo.speed[2], (int)robo.speed[3]);
	}
	else if (argc==3){
		int Mx=0;

		Mx = atoi((char*)argv8[1]);
		robo.speed[Mx]=atoi((char*)argv8[2]);
		size+=sprintf(buffer+size, "%d %d %d %d\r\n", (int)robo.speed[0], (int)robo.speed[1], (int)robo.speed[2], (int)robo.speed[3]);

	}
	else if (argc==4){
		robo.kp=(float)atoi((char*)argv8[1]);
		robo.ki=(float)atoi((char*)argv8[2]);
		robo.kd=(float)atoi((char*)argv8[3]);
		robo.set_pid(robo.kp, robo.ki, robo.kd);
		size+=sprintf(buffer+size, "%d %d %d %d\r\n", (int)robo.speed[0], (int)robo.speed[1], (int)robo.speed[2], (int)robo.speed[3]);
	}
	else {
		size+=sprintf(buffer+size, "Syntax: info\r\n");
	}
	return size;
}

//comando a ser enviado no prompt para escrever o valor atual de velocidade na porta serial

CommandLine cmdline({"[A"},
						 {cmd_info});
