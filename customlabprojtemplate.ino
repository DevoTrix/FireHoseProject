#include <VirtualWire.h> //only library i would be using
//define global inputs here
int IRSensor = A1;

//define global outputs here
int relayPin = A0;
//define global variables here
int fire = 0;
int globalPosition = 0;
int firstPos = 0;
int secondPos = 0;
int firePos = 0;
int doneMoving = 1;
int delay = 0;

typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 3;
task tasks[tasksNum];

enum servo_States{ Servo_INIT, Left, Right, F1, F2, Calc, S1, S2, Fire, Write};
// servo logic
int servo_Tick(int state1){
    switch(state1){
        case Servo_INIT:
            state1 = Left;
            break;
        case Left: //sweeps left;
            int sensor = analogRead(IRSensor); //analgoRead gives off a variety of numbers
            int flame = map(sensor,0, 1024, 0, 1); //maps those numbers to 0 or 1, 1 being there is a fire.
            if(delay == 0){  //make sure that the delayMicrosecond isn't being used.
                if(flame == 1){ //if flame is detected, start the calibration to detect the angle of the fire. 
                    state1 = F1;
                }
                else if(globalPosition <180){  //keeps the servo turning left till 180
                    state1 = Left;
                }
                else if(globalPosition >= 180){ //reverses direction once reached the 180 mark.
                    state1 = Right;
                }
            }
            break;
        case Right: //sweeps right
            int sensor = analogRead(IRSensor);
            int flame = map(sensor,0, 1024, 0, 1);
            if(delay==0){
                if(flame == 1){
                    state1 = F1;
                }
                else if(globalPosition > 0){
                    state1 = Right;
                }
                else if(globalPosition <= 0){
                    state1 = Left;
                }
            }
            break;
        case F1: //locates the left side before it stops detecting
            int sensor = analogRead(IRSensor);
            int flame = map(sensor,0, 1024, 0, 1);
            if(delay == 0){
                if((flame == 1) ||  (globalPosition >0 && globalPosition <= 180)){ // keeps it going left till it stops detecting or reached the end
                    state1 = F1;
                }
                else if(flame == 0){ //if fire is no longer detected, stop and mark;
                    firstPos = globalPosition;
                    state1 = F2;
                }
                else if(globalPosition <= 0){ //if it is near the edge mark the edge,
                    firstPos = 0;
                    state1 = F2;
                }
                else if(globalPosition >= 180){//if it is near the edge mark the edge,
                    firstPos = 180;
                    state1 = F2;
                }
            }
            break;
        case F2: //detects right side
            int sensor = analogRead(IRSensor);
            int flame = map(sensor,0, 1024, 0, 1);
            if(delay ==0){
                if((flame == 1) ||  (globalPosition >0 && globalPosition <= 180)){ //flipped version of F2
                    state1 = F2;
                }
                else if(flame == 0){
                    firstPos = globalPosition;
                    state1 = Calc;
                }
                else if(globalPosition <= 0){
                    firstPos = 0;
                    state1 = Calc;
                }
                else if(globalPosition >= 180){
                    firstPos = 180;
                    state1 = Calc;
                }
            }
            break;
        case Calc: //calculates the fire position using the midpoint
            if(globalPosition > firePos){
                state1 = S2;
            }
            else if(globalPosition < firePos){
                state1 = S1;
            }
            else if(globalPosition == firePos){
                state1 = Fire;
            }
            break;
        case S1: // moves hose to the left if position is too low
            if(delay == 0){ //this delay isnt the dely function doesn't pause the program like delay does, just ignores other conditions if delay is checked.  mainly to not fuck with the delayMicrosecond() used to control the servo. 
                if(globalPosition == firePos){
                    state1 = Fire;
                }
                else {
                    state1 = S1;
                }
            }
            break;
        case S2: // moves to the right if position is too high
            if(delay == 0){
                if(globalPosition == firePos){
                    state1 = Fire;
                }
                else {
                    state1 = S1;
                }
            }
            break;
        case Fire: //sends a signal to the pump state to turn on the pump
            int sensor = analogRead(IRSensor); 
            int flame = map(sensor,0, 1024, 0, 1);
            if(flame == 0){
                fire = 0;
                state1 = Write;
            }
            else{
                state1 = Fire;
            }
            break;
        case Write: //resets position of the hose back to 0. 
            if(delay == 0){
                if(globalPosition != 0){
                    state1 = Write;
                }
                else if(globalPosition == 0){
                    state1 = Left;
                }
            }
            break;
    }
    switch(state1){
        case Left: //moves the servo https://create.arduino.cc/projecthub/nannigalaxy/control-servo-motor-without-library-1d8606 basic idea from this on how to do it without the library
            globalPosition = globalPosition + 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case Right:
            globalPosition = globalPosition - 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case F1:
            globalPosition = globalPosition + 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case F2:
            globalPosition = globalPosition - 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case Calc:
            firePos = (firstPos - secondPos) / 2;
        case S1:
            globalPosition = globalPosition + 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case S2:
            globalPosition = globalPosition - 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        case Fire:
            fire = 1;
            break;
        case Write:
            globalPosition = globalPosition - 1;
            int val = (globalPosition * 10) + 500;
            digitalWrite(pin, HIGH);
            delay = 1;
            delayMicroseconds(val);
            delay = 0;
            digitalWrite(pin,LOW);
            break;
        default:
            break;
    }
    return state1;
}

//controls the pump

enum pump_State{ Pump_INIT, OFF, ON};

int pump_Tick(int state2){
    switch(state2){
        case Pump_INIT:
            state2 = OFF; 
            break;
        case OFF:
            if(fire == 1){ //if the fire is detected, set relay to HIGH
                digitalWrite(relayPin, HIGH);
                state2 = ON;
            }
            else{
                state2 = OFF;
            }
            break;
        case ON:
            if(fire == 0){ //if fire is not detected, set relay to LOW
                digitalWrite(relayPin, LOW);
                state2 = OFF;
            }
            else{
                state2 = ON;
            }
            break;

    }
    switch(state2){
        case OFF:
            break;
        case ON:
            break;
    }
    return state2;
}


//transmitter code

enum trans_State{ Trans_INIT, noFire, isFire};

int trans_Tick(int state3){
    switch(state3){
        case Trans_INIT:
            state = noFire;
            break;
        case noFire:
            if(fire == 1){
                state3 = isFire;
            }
            else{
                state3 = noFire;
            }
            break;
        case isFire:
            if(fire == 0){
                state3 = noFire;
            }
            else{
                state3 = isFire;
            }
            break;
    }
    switch(state3){
        case noFire:
            char *message = "0 ";
            message += millis();
            vw_send((uint8_t *)message, strlen(message));
            break;
        case isFire:
            char *message = "1 ";
            message += millis();
            vw_send((uint8_t *)message, strlen(message));
            break;
    }
    return state3;
}

void setup(){
    
    //initialize inputs here

    // initialize outputs here
    pinMode(relayPin, OUTPUT);
    vw_setup(2000); // Bits per sec

    unsigned char i = 0;
  
    tasks[i].state = ;
    tasks[i].period = 10;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &;
    i++;

    Serial.begin(9600);
}
void loop(){
    unsigned char i;
    for (i = 0; i < tasksNum; ++i) {
        if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsedTime = millis(); // Last time this task was ran
        }
    }
}