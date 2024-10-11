# ISP32-RTOS manual
## Pre-flashing tasks
* Go to menu-config to set timer stack to maxium (else runtime stack overflow happens)

## Git branch category
In order to seperate the rick of making one funtional module's code messing with others, I decided to try a way that to develop each module parallelly in branches and merge them back to main once a module is finished and fully functional.  

Branches including:  
* main: Main branch that contains stable and funtional version
* sensors: Contains any newest development on sensors modules
* storage: Contains storage modules such as data logger & SD card
* commu: Contains the developments of communication modules like LoRa
* stm: Contains stm and it's slaves development such as ADC, buzzer, servo motors...
* fsm: Finite state machine

## Current situation
It can read sensors' signal now, including GPS, imu, and bmp280, and print it in serial monitor in the frequency of 2 Hz.