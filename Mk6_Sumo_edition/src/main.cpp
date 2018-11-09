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
#define floor_d A4
#define distance_s_i A3
#define distance_s_r A2
#define distance_s_c A1

// Motor variables
const int offsetA = 1;
const int offsetB = -1; //derecha

// Motor declaration
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// Sensor declaration
SharpIR left_sensor(distance_s_i, 1080);
SharpIR center_sensor(distance_s_c, 1080);
SharpIR right_sensor(distance_s_r, 1080);

// Sensor variables
int distance_c = 0;
int distance_l = 0;
int distance_r = 0;
int floor_left = 0;
int floor_right = 0;

int fdistance_c = 0; // filtered distance_c
int fdistance_l = 0; //
int fdistance_r = 0;

// Sensor Values
#define WHITE_LINE 500    // value of the readings above white border the higher, the whitest
#define DISTANCE_LIMIT 35 // maximum distance of detection

void read_sensors()
{
  distance_c = center_sensor.distance();
  distance_l = left_sensor.distance();
  distance_r = right_sensor.distance();
  floor_left = analogRead(floor_i);
  floor_right = analogRead(floor_d);
}

int distance_filter(int filtered_measure)
{
  if(filtered_measure > DISTANCE_LIMIT)
    {
      filtered_measure = DISTANCE_LIMIT;
    }
    return filtered_measure;
}

void filter_sensors()
{
  fdistance_c = distance_filter(distance_c) ;
  fdistance_l = distance_filter(distance_l) ;
  fdistance_r = distance_filter(distance_r) ;
}




void setup()
{

  Serial.begin(115200);


}

void sensor_serial_print()
{
  Serial.print(fdistance_l);
  Serial.print(" ");
  Serial.print(floor_left);
  Serial.print(" ");
  Serial.print(floor_right);
  Serial.print(" ");
  Serial.print(fdistance_r);
  Serial.println(" ");
}

void search_rot(int rotation_speed, bool direction)
{
  if(direction == true)
    {
      motor1.drive(rotation_speed);
      motor2.drive(-rotation_speed);
      }else
        {
        motor1.drive(-rotation_speed);
        motor2.drive(rotation_speed);
        }
}

void loop()
{
read_sensors();
filter_sensors();
sensor_serial_print();

//MIRAMOS EL SUELO

if((floor_left > WHITE_LINE)||(floor_left > WHITE_LINE))
{

int counter_2 = 0;
bool whiteclose = false;
for(counter_2 = 0; counter_2 < 300 ; counter_2++)
  {
    read_sensors();
    filter_sensors();
    if(whiteclose == false)
       {
         motor1.drive(-100);
         motor2.drive(-100);
       }
  }

for(counter_2 = 0; counter_2 < 1000 ; counter_2++)
    {
      search_rot(100, true);
      read_sensors();
      filter_sensors();
      if((fdistance_l < 30)||(fdistance_l < 30))
      {
        counter_2 = 1000;
      }
      counter_2++;
    }

}


//BUSCAMOS

if((fdistance_l < 35)||(fdistance_l < 35))
{
  if(fdistance_r > fdistance_l + 4)
  {
    motor1.drive(100);
    motor2.drive(180);
  }else{
        if(fdistance_l > fdistance_r + 4)
          {
          motor1.drive(180);
          motor2.drive(100);
        }else
          {
            motor1.drive(100);
            motor2.drive(100);
          }

      }
}else
  {
    search_rot(100, true);
  }

//sensor_serial_print();

/*
if(fdistance_l<30)
{
      motor1.drive(-100);
      motor2.drive(100);

}else
  {
    motor1.brake();
    motor2.brake();
  }
*/



}
