// Made by Pablopeza for the Oshwdem2018 minisumo competition

#include <Arduino.h>

// Motor driver library by SparkFun
#include <SparkFun_TB6612.h>

// Sharp sensor library https://github.com/guillaume-rico/SharpIR
// Remember to reduce the number of measures for the median filter default = 25
#include <SharpIR.h>

// Motor pins
#define AIN1 7
#define BIN1 9
#define AIN2 6
#define BIN2 10
#define PWMA 5
#define PWMB 11
#define STBY 8

// Sensor pins
#define floor_i A0
#define floor_d A0
#define distance_i A0
#define distance_r A0
#define distance_c A0

// Motor variables
const int offsetA = 1;
const int offsetB = 1;

// Motor declaration
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// Sensor declaration
SharpIR left_sensor(distance_i, 1080);
SharpIR center_sensor(distance_c, 1080);
SharpIR right_sensor(distance_r, 1080);

// Sensor variables


void setup()
{}

void loop()
{
/*
motor1.drive(VDCH);//izq
motor2.drive(VIZQ);//dch
*/

}
