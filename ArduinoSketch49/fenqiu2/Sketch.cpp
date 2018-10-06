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

boolean flag = false;

int step_count = 0;

//定时器中断
void step_motor()
{
	if(step_count!=0){
		if(step_count%2==0)
		digitalWrite(Step,HIGH);
		else
		digitalWrite(Step,LOW);
		step_count--;
	}
}

void setup()
{
	Wire.begin(5);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	pinMode(Step, OUTPUT); // Step
	pinMode(dir, OUTPUT); // Dir
	Serial.begin(9600);
	delay(1000);
	
	//定时器初始化
	tc1.setMode("CTC",1);
	tc1.attachInterrupt(step_motor);
}

void loop()
{
	int p = analogRead(Read1);
	int q = analogRead(Read2);
	
	//如果是收白球
	if (Q == 0)
	{
		digitalWrite(Wled, HIGH);
		digitalWrite(Bled, LOW);
		if (p > 500)
		flag = true;
		if (flag == false)
		{
			digitalWrite(dir, LOW);
			digitalWrite(Step, HIGH); // Output high
			delayMicroseconds(8000); // Wait 1/2 a ms
			digitalWrite(Step, LOW); // Output low
			delayMicroseconds(8000); // Wait 1/2 a ms
		}
		else
		{
			if (p > 500)
			{
				delay(200);
				if (q > 450)
				{
					digitalWrite(dir, LOW);
					step_count = 122;
// 					for (x = 0; x < 67; x++)
// 					{
// 						digitalWrite(Step, HIGH); // Output high
// 						delayMicroseconds(5000); // Wait 1/2 a ms
// 						digitalWrite(Step, LOW); // Output low
// 						delayMicroseconds(5000); // Wait 1/2 a ms
// 					}
					w++;
				}
				if (q < 450)
				{
					digitalWrite(dir, HIGH);
					step_count = 122;
// 					for (x = 0; x < 67; x++)
// 					{
// 						digitalWrite(Step, HIGH); // Output high
// 						delayMicroseconds(5000); // Wait 1/2 a ms
// 						digitalWrite(Step, LOW); // Output low
// 						delayMicroseconds(5000); // Wait 1/2 a ms
// 					}
				}
			}
		}
		g = w;
	}
	//如果是收黑球
	if (Q == 1)
	{
		digitalWrite(Bled, HIGH);
		digitalWrite(Wled, LOW);
		if (p > 500)
		flag = true;
		if (flag == false)
		{
			digitalWrite(dir, LOW);
			digitalWrite(Step, HIGH); // Output high
			delayMicroseconds(8000); // Wait 1/2 a ms
			digitalWrite(Step, LOW); // Output low
			delayMicroseconds(8000); // Wait 1/2 a ms
		}
		else
		{
			if (p > 500)
			{
				if (q < 450)
				{
					digitalWrite(dir, LOW);
					for (x = 0; x < 67; x++)
					{
						digitalWrite(Step, HIGH); // Output high
						delayMicroseconds(5000); // Wait 1/2 a ms
						digitalWrite(Step, LOW); // Output low
						delayMicroseconds(5000); // Wait 1/2 a ms
					}
					b++;
				}
				if (q > 450)
				{
					digitalWrite(dir, HIGH);
					for (x = 0; x < 67; x++)
					{
						digitalWrite(Step, HIGH); // Output high
						delayMicroseconds(5000); // Wait 1/2 a ms
						digitalWrite(Step, LOW); // Output low
						delayMicroseconds(5000); // Wait 1/2 a ms
					}
				}
			}
		}
		g = b;
	}
	Serial.print("q:");
	Serial.print(q);
	Serial.print("p:");
	Serial.print(p);
	Serial.print("Q:");
	Serial.print(Q);
	Serial.print("g:");
	Serial.println(g);
	/*Serial.write(Q);
	Serial.write("B:");
	Serial.write(b);
	Serial.write("W:");
	Serial.write(w);
	Serial.write('\n');
	delay(500);*/
}
void receiveEvent(int howMany)
{
	while (0 < Wire.available())
	{
		Q = Wire.read();
	}
	/*Serial.print("Q:");
	Serial.println(Q);*/
}
void requestEvent() {
	Wire.write(g); // respond with message of 6 bytes
	// as expected by master
}
void wihteGold()
{
	if (p > 500)
	flag = true;
	if (flag == false)
	{
		digitalWrite(dir, LOW);
		digitalWrite(Step, HIGH); // Output high
		delayMicroseconds(8000); // Wait 1/2 a ms
		digitalWrite(Step, LOW); // Output low
		delayMicroseconds(8000); // Wait 1/2 a ms
	}
	else
	{
		if (p > 500)
		{
			if (q > 450)
			{
				digitalWrite(dir, LOW);
				for (x = 0; x < 67; x++)
				{
					digitalWrite(Step, HIGH); // Output high
					delayMicroseconds(5000); // Wait 1/2 a ms
					digitalWrite(Step, LOW); // Output low
					delayMicroseconds(5000); // Wait 1/2 a ms
				}
				w++;
			}
			if (q < 450)
			{
				digitalWrite(dir, HIGH);
				for (x = 0; x < 67; x++)
				{
					digitalWrite(Step, HIGH); // Output high
					delayMicroseconds(5000); // Wait 1/2 a ms
					digitalWrite(Step, LOW); // Output low
					delayMicroseconds(5000); // Wait 1/2 a ms
				}
				w++;
			}
			//delay(100);
		}
	}
}
void blackGold()
{
	if (p > 500)
	flag = true;
	if (flag == false)
	{
		digitalWrite(dir, LOW);
		digitalWrite(Step, HIGH); // Output high
		delayMicroseconds(8000); // Wait 1/2 a ms
		digitalWrite(Step, LOW); // Output low
		delayMicroseconds(8000); // Wait 1/2 a ms
	}
	else
	{
		if (p > 500)
		{
			if (q < 450)
			{
				digitalWrite(dir, LOW);
				for (x = 0; x < 67; x++)
				{
					digitalWrite(Step, HIGH); // Output high
					delayMicroseconds(5000); // Wait 1/2 a ms
					digitalWrite(Step, LOW); // Output low
					delayMicroseconds(5000); // Wait 1/2 a ms
				}
				b++;
			}
			if (q > 450)
			{
				digitalWrite(dir, HIGH);
				for (x = 0; x < 67; x++)
				{
					digitalWrite(Step, HIGH); // Output high
					delayMicroseconds(5000); // Wait 1/2 a ms
					digitalWrite(Step, LOW); // Output low
					delayMicroseconds(5000); // Wait 1/2 a ms
				}
				b++;
			}
		}
	}
}

