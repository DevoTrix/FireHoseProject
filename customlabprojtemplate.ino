//define global inputs here

//define global outputs here


typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 8;
task tasks[tasksNum];

enum insertStateName{ /* insert states here*/};
int stateName_Tick(int state{
    switch(state){
        case /*state1*/:
            break;

    }
    switch(state){
        case /*state1*/:
            break;
    }
    return state;
}


void setup(){
    
    //initialize inputs here

    // initialize outputs here


    unsigned char i = 0;
  
    tasks[i].state = ;
    tasks[i].period = 10;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &;
    i++;
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
