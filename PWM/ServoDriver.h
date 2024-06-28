#ifndef __SERVODRIVER
#define __SERVODRIVER

void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void Servo_Init(void);
void Servo_SetAngle(float Angle);

#endif