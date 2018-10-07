/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/*Begining of Auto generated code by Atmel studio */
//#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include<Wire.h>
#include "Timer1.h"
//Beginning of Auto generated function prototypes by Atmel Studio
void requestEvent();
//End of Auto generated function prototypes by Atmel Studio

Timer1 tc1;

//Beginning of Auto generated function prototypes by Atmel Studio
void receiveEvent(int howMany);
void wihteGold();
void blackGold();
//End of Auto generated function prototypes by Atmel Studio

int x, p, q;
int Wled = 4, Bled = 5;
int Step = 3, dir = 2;
int Read1 = A0;                             //判断是否有球来
int Read2 = A1;                             //判断球的颜色
int Q =0;
int b = 0, w = 0;
int g = 0;
int MS1 = 8;
int MS2 = 7;
int MS3 = 6;

boolean flag = false;

int step_count = 0;

//定时器中断
void step_motor()
{
	for(int i = 0;i<=100;i++)
	{
			digitalWrite(Step,HIGH);
			delayMicroseconds(500);
			digitalWrite(Step,LOW);
			delayMicroseconds(500);
	}

}

void setup()
{
	Wire.begin(5);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	pinMode(Step, OUTPUT); // Step
	pinMode(dir, OUTPUT); // Dir
	digitalWrite(dir,HIGH);
	digitalWrite(Step,LOW);
	
	//pinMode(MS1,INPUT_PULLUP);
	//pinMode(MS2,INPUT_PULLUP);
	//pinMode(MS3,INPUT_PULLUP);
	
	Serial.begin(115200);
	delay(1000);
	
	//#定时器初始化
	//tc1.setMode("CTC",2000);
	//tc1.attachInterrupt(step_motor);
}

void loop()
{
	int p = analogRead(Read1);
	int q = analogRead(Read2);

step_motor();
delay(44000);
//step_count = 100;
		
	//#如果是收白球
	if (Q == 0)
	{
		digitalWrite(Wled, HIGH);
		digitalWrite(Bled, LOW);
		
		//步进电机运动
		wihteGold();
	}
	
	//#如果是收黑球
	if (Q == 1)
	{
		digitalWrite(Bled, HIGH);
		digitalWrite(Wled, LOW);
		
		//步进电机运动
		blackGold();
	}
	
	//串口调试
// 	Serial.print("q:");
	Serial.print(q);
	Serial.print("p:");
	Serial.print(p);
	Serial.print("Q:");
	Serial.print(Q);
	Serial.print("g:");
	Serial.println(g);
}
void receiveEvent(int howMany)
{
	while (0 < Wire.available())
	{
		Q = Wire.read();
	}
}

void requestEvent()
{
	Wire.write(g);
}

void wihteGold()
{
	//刚开始没球就一直转
	if (p > 500)
	flag = true;
	
	if (flag == false)
	{
		step_count = 2;
	}
	else
	{
		if (p > 500)
		{
			delay(200);
			//收到白球
			if (q > 450)
			{
				digitalWrite(dir, LOW);
				step_count = 122;
				w++;
			}
			//收到黑球
			if (q < 450)
			{
				digitalWrite(dir, HIGH);
				step_count = 122;
			}
		}
	}
	
	//赋值得分球数量
	g = w;
}
void blackGold()
{
	//刚上电没球就一直转
	if (p > 500)
	flag = true;

	if (flag == false)
	{
		step_count = 2;
	}
	else
	{
		if (p > 500)
		{
			if (q < 450)
			{
				digitalWrite(dir, LOW);
				step_count = 122;
				b++;
			}
			if (q > 450)
			{
				digitalWrite(dir, HIGH);
				step_count = 122;
			}
		}
	}
	g = b;
}

