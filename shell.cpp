/* Copyright (C) 2010 by Diego Candido < diego.luca.candido@gmail.com >

  This file is part of Shell-arduino

  Shell-Arduino is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  

 */
#include "shell.h"
#include <stdlib.h>

void pingLed(int pin, int , int){
  if(pin != 0 && pin < 14){
    pinMode(pin, OUTPUT);
    Serial.println("ping");
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
  }
  else{
    
    Serial.write("--- ERROR pin choice");

  }
  
}


void setPin(int pin, int value, int){
 
 
  if(pin > 0 && pin < 14 && value >= 0 && value <= 255){
    
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
    
  }
  else{
    
    Serial.write("--- ERROR pin choice OR value choice");

  }
}

void readDigitalPin(int pin, int times,int){
  if(pin > 1 && pin < 14){
    if(times == 0) times = 1;
    for(int i = 0; i < times;i++)
      Serial.println(digitalRead(pin), DEC);
  }
  else{
    
    Serial.write("--- ERROR pin choice");

  }
}

void readAnalogPin(int pin, int times, int){
  if(pin > -1 && pin < 6){
    if(times == 0) times = 1;
    for(int i = 0; i < times;i++)
      Serial.println(analogRead(pin),DEC);
  }
  else{
    
    Serial.write("--- ERROR pin choice");

  }
}

void createPwm(int pin , int value , int){
  if(pin > 1 && pin < 14){
    pinMode(pin, OUTPUT);
    analogWrite(pin,value);
  }
  else{
    
    Serial.write("--- ERROR pin choice");

  }
  
  
}

void showStatus(int,int,int){
  int ii;
  for(int i = 2; i < 14;i++){
    Serial.print("PORT ");
    Serial.print(i);
    Serial.print(": ");
    if(i == 3 || i == 5 || i == 6|| i ==9 || i==10 || i == 11) ii = analogRead(i);
    else ii = digitalRead(i);
    Serial.println(ii, DEC);

  }
  
  
  for(int i = 0; i < 6;i++){
    Serial.print("PORT ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(analogRead(i), DEC);
  }
}
  
void help(int,int,int){

  Serial.flush();
  Serial.println("HELP: {\n\tping number_pin\n\tsetp  number_pin value\n\trdpin number_pin {times}\n\trapin number_pin {times}\n\tpwm pin_number value\n\tstatus\n\thelp\n}");


}

void monitor(int pin,int time,int){

  if(pin > 1 && pin < 14){
    if(time == 0 || time < 10) time = 10;
    pinMode(pin, INPUT);
    int origin_value = digitalRead(pin);
    for(int i = 0; i < time;i+= time/10)
      if(digitalRead(pin) != origin_value) {
	Serial.print("changed status to:");
	Serial.println(i);
	break;
      }
    Serial.println("nothing happens");
  }
  else{
    Serial.write("--- ERROR pin choice");
  }
}

ArduinoShell::ArduinoShell(int _bauds): bauds(_bauds){
  
 
  
  commands[0].com = "status";
  commands[0].cmd = showStatus;
  commands[1].com = "ping";
  commands[1].cmd = pingLed;
  commands[2].com = "setp";
  commands[2].cmd = setPin;
  commands[3].com = "rdpin";
  commands[3].cmd = readDigitalPin;
  commands[4].com = "rapin";
  commands[4].cmd = readAnalogPin;
  commands[5].com = "pwm";
  commands[5].cmd = createPwm;
  commands[6].com = "help";
  commands[6].cmd = help;
  commands[7].com = "monitor";
  commands[7].cmd = monitor;
}

int ArduinoShell::getChoice(){
  Serial.begin(bauds);
  Serial.flush();
  delay(50);
  char phrase[12];
  memset(phrase, '\0', 12);
  int i = 0;
  
  while(1){
    if(i < 12 && Serial.available() > 0){
      
      phrase[i] = Serial.read();
      
      
      i++;
      
    }
    else if(Serial.available() == 0)
      break;
  }

  
  Serial.flush();
  if(i != 0){
    
    int n = dispatch(phrase);
    if(n == -1)
      Serial.println("error string");
    else if(n == 0)
      Serial.println("--- Ok!");
    else if(n == 1)
      Serial.println("command not found");
  }
  Serial.flush();
  Serial.end();
}
int ArduinoShell::dispatch(char choice[12]){
  
  char *first_t, *second_t, *third_t, *fourth_t;
  first_t = strtok(choice, " ");
  second_t = strtok(NULL, " ");
  third_t = strtok(NULL, " ");
  fourth_t = strtok(NULL, " ");
  // it's a better choice to implement the control inside function 'cause it's possible that there aren't other token
  
  for(int i = 0; i < 8;i++){
    
    if(strcmp(first_t,commands[i].com) == 0){
      
      commands[i].cmd(atoi(second_t), atoi(third_t), atoi(fourth_t));
      return 0;
    }
  }
  return 1;
  
  
}

