#include <LiquidCrystal.h>
#include <SPI.h>
#include <RH_ASK.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RH_ASK driver;
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;
char *message = 0;
int delay_gcd;
const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum isFire_State { IF_INIT, S0 };
int IsFire_Tick(int state) {
  switch (state) {
    case IF_INIT:
      state = S0;
      break;
    case S0:
      uint8_t buf[1];
      uint8_t buflen = sizeof(buf);
      if (driver.recv(buf, &buflen)) {
        int i;
        message = (char *)buf;
      }
      Serial.println((char *)buf);
      if (((char)buf[0]) == "1") {
        lcd.setCursor(0, 0);
        lcd.print("ALERT FIRE");
        lcd.setCursor(3, 1);
        lcd.print("Spraying Water");

      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("All Clear");
      }
      state = S0;
      break;
  }

  return state;
}
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  unsigned char i = 0;
  if(!driver.init()){
    Serial.print("fail");
  }
  tasks[i].state = IF_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &IsFire_Tick;
  i++;
  Serial.begin(9600);
  delay_gcd = 100;  // GCD
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ((millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis();  // Last time this task was ran
    }
  }
}
