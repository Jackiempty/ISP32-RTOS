# ISP32-RTOS manual
## Pre-flashing tasks
* Go to menu-config to set timer stack to maxium (else runtime stack overflow happens)

## Task categories
In order to seperate the rick of making one funtional module's code messing with others, I decided to try a way that to develop each module parallelly in branches and merge them back to main once a module is finished and fully functional.  

Tasks including:  
* main: Main branch that contains stable and funtional version 
* sensors: Contains any newest development on sensors modules -> **done, for now at least**
* storage: Contains storage modules such as data logger & SD card -> **done**
* commu/recv: Contains the developments of communication modules like LoRa -> **done**
* slave: Contains stm and it's slaves development such as ADC, buzzer, servo motors...
* fsm: Finite state machine -> **done**

## Current situation
10/08/24: It can read sensors' signal now, including GPS, imu, and bmp280, and print it in serial monitor in the frequency of 2 Hz.  
10/15/24: Storage function finished, can log datas read from sensors to sd card in the frequency of 2 Hz.  
10/30/24: LoRa module migration completed, can send and read data by LoRa