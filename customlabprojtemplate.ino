#include <VirtualWire.h>
//define global inputs here
int IRSensor = A1;

//define global outputs here
int relayPin = A0;
//define global variables here
int fire = 0;
int globalPosition = 0;
int firstPos = 0;
int secondPos = 0;
int doneMoving = 1;


typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum =4;
task tasks[tasksNum];

enum servo_States{ Servo_INIT};

int servo_Tick(int state1){
    switch(state1){
        case Servo_INIT:
            break;
    }
    switch(state1){
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
            if(fire == 1){
                digitalWrite(relayPin, HIGH);
                state2 = ON;
            }
            else{
                state2 = OFF;
            }
            break;
        case ON:
            if(fire == 0){
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