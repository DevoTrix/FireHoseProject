# CS/EE 120B Custom Laboratory Project Report
# Autonomous Fire Hose project
 * [demo](https://youtu.be/0UkOi1IPzAI)
# Joseph Chang
The Fire Hose Project or FHP aims to increase the safety of households. Using a flame sensor, the FHP detects the location of the source of the fire and controls a 12V pump. The goal is to put the system in front of important areas, that a fire should not occur. The status would be displayed on an LCD that could be placed elsewhere, in case it may not be in a safe area. 

## Initial Plans that was Scrapped
Having the pump move around provided too much trouble to realistically do. having the servo go 360 causes tangles in wires, and crimps in the tubing. The moving of the servo would be limited by the length of the tubing and the tanglement of tubes.

## BUGS
LOTS OF BUGS
 * Servo logic SM doesn't work as it should, despite it should be working. 
 * Servo is also too weak to move the tube.
 * transmitter and reciever not working(maybe fried) logic is there

## HardWare
  * Computing
    * 2 x Elegoo Arduino Uno R3 
  * Sensors
    * IR Sensor
    * Radio Frequency transmitter
    * Radio Frequency Reciever
  * OUTPUTS
    * LCD Screen
    * Pump
    * Relay
    * MicroServo
  * MISCELLANEOUS
    * Wires
    * Jumper Wires
    * tubing
    * 12V adapter
    * tub
## Complexities
  * Servo
  * Relay + Pump
  * RF transmitter and reciever
  
## Libraries
  * [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/)
  * SPI Library (for compiling)
## Wiring Diagram
![](https://i.imgur.com/9I0FL1u.png)
## Task Diagram
![](https://i.imgur.com/9Ja0MPY.jpg)
## SM Diagrams
![](https://i.imgur.com/8T5KJXy.jpg)
![](https://i.imgur.com/oZyrBNI.jpg)
![](https://i.imgur.com/UUHT5MZ.jpg)
![](https://i.imgur.com/OYWI17j.jpg)
