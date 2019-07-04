/*
 * File:          crazybot.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>

#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <stdio.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define pi 3.1416

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP); 
  
  double lin_vel;
  //double dis_sen;
  double vel = 0;
  double rpm;
  double rpm2; 
  /////This is the radio of each wheel//////
  double radio=0.075; 
  
  double anterior= 0; 
  double anterior2= 0;
  
  

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   
   
   WbDeviceTag ps_left = wb_robot_get_device("sensor_left");
   WbDeviceTag ps_right = wb_robot_get_device("sensor_right");
   
   WbDeviceTag ds = wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(ds,TIME_STEP);  
   
   /////Enable the position sensor///////////////////////////
   
   wb_position_sensor_enable(ps_left, TIME_STEP);
   wb_position_sensor_enable(ps_right, TIME_STEP);  
   
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   
   wb_motor_set_position(wheel_right, INFINITY);   
   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_velocity(wheel_left, vel);
   wb_motor_set_velocity(wheel_right, vel);
   
   
  while (wb_robot_step(TIME_STEP) != -1) {
  

     int key = wb_keyboard_get_key(); 
     
     
      double initial,diference; 
      double initial2,diference2;
     
     initial=wb_position_sensor_get_value(ps_left); 
     diference= (initial-anterior)/0.064; 
     anterior=initial;
     
     initial2=wb_position_sensor_get_value(ps_right); 
     diference2= (initial2-anterior2)/0.064; 
     anterior2=initial2;
     
     
    if (key==WB_KEYBOARD_UP){
     
     vel = 40; 
    
     wb_motor_set_position(wheel_left, INFINITY);
     wb_motor_set_velocity(wheel_left, -vel);
     wb_motor_set_position(wheel_right, INFINITY);
     wb_motor_set_velocity(wheel_right, -vel);
  
     }
     
     if (key==WB_KEYBOARD_DOWN){
     
     vel = 1.3333333333333335; 
           
     wb_motor_set_position(wheel_left, INFINITY);
     wb_motor_set_velocity(wheel_left, vel);
     wb_motor_set_position(wheel_right, INFINITY);
     wb_motor_set_velocity(wheel_right, vel);
   
     }
     
     if (key==WB_KEYBOARD_LEFT){
     
     vel= 15; 
     
     wb_motor_set_position(wheel_left, INFINITY);
     wb_motor_set_velocity(wheel_left, -vel);
     wb_motor_set_position(wheel_right, INFINITY);
     wb_motor_set_velocity(wheel_right, 0);
    
     }
     if (key==WB_KEYBOARD_RIGHT){
     
     vel= 15; 
     
     wb_motor_set_position(wheel_left, INFINITY);
     wb_motor_set_velocity(wheel_left, 0);
     wb_motor_set_position(wheel_right, INFINITY);
     wb_motor_set_velocity(wheel_right, -vel);
    
     }
          
     if (key==WB_KEYBOARD_END){
      
     
     wb_motor_set_position(wheel_left, INFINITY);
     wb_motor_set_velocity(wheel_left, 0);
     wb_motor_set_position(wheel_right, INFINITY);
     wb_motor_set_velocity(wheel_right, 0);
    
     }      
     rpm= (diference*60)/(2*pi)*-1;
     rpm2= (diference2*60)/(2*pi)*-1;
     
     lin_vel=diference*radio*-1; 
     
     //lin_vel= (((2*pi)*radio)/60)*rpm;
     
     printf("Linear velocity: %lf\n", lin_vel);
     printf("RPM left: %lf\n", rpm);
     printf("RPM right: %lf\n", rpm2);
     //printf("Angular velocity left: %lf\n", diference);
     //printf("Angular velocity right: %lf\n", diference2);
    
     
     
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
