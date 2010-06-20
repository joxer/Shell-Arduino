
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
#include "list.h"


ArduinoShell::ArduinoShell(int _bauds): bauds(_bauds){
  
  Serial.begin(bauds);
  Serial.flush();
  delay(50);
  Serial.println("Arduino-Shell by Diego Candido < diego.luca.candido@gmail.com >\r\nWrite help for commands");
  delay(20);
  Serial.flush();
  Serial.end();
  
  first = NULL;
  
}

void ArduinoShell::addFunction(char* name, functor cmd){
  
  
  if(first == NULL){

    first = (Node*)malloc(sizeof(Node));
    first->getData()->cmd = cmd;
    first->getData()->com = name;
    first->setNext(NULL);
  }
  else{
    Node *nn = NULL;

    for(nn = first; nn->getNext() != NULL;nn = nn->getNext());
    
    Node *kk = (Node*)malloc(sizeof(Node));
    kk->getData()->cmd = cmd;
    kk->getData()->com = name;
    kk->setNext(NULL);
    nn->setNext(kk);

  }
  
}

int ArduinoShell::getChoice(){
  Serial.begin(bauds);
  Serial.flush();
  delay(50);
  char phrase[25];
  memset(phrase, '\0', 25);
  int i = 0;
  Serial.print("Arduino~: ");
  delay(50);
  while(1){
    if(i < 25 && Serial.available() > 0){
      
      phrase[i] = Serial.read();
      Serial.print(phrase[i]);
      if(phrase[i] == ';' || phrase[i] == 13){
	phrase[i] = ' ';
	break;
      }
      
      if(phrase[i] == 127 && i > 0){
	i--;
	Serial.print(byte(8));
	Serial.print(' ');
	Serial.print(byte(8));
      }
      else if(phrase[i] == 127 && i == 0)
	;
       else if(i > -1){

	 i++;
       }
     }
     else if(i == 25){
       Serial.println("");
       Serial.print("ERROR -- TOO MUCH CHARACTER FOR COMMAND");
       break;
     }
   }
  
   Serial.println("");
   delay(10);
   Serial.flush();
   if(i != 0 && i < 25){

     int n = dispatch(phrase);
     if(n == -1)
       Serial.println("error string");
    else if(n == 0)
      Serial.println("--- Ok!");
    else if(n == 1)
      Serial.println("command not found");
  }
  Serial.flush();
  delay(10);
  Serial.end();
}
int ArduinoShell::dispatch(char choice[12]){
  
  char *first_t, *second_t, *third_t, *fourth_t;
  first_t = strtok(choice, " ");
  second_t = strtok(NULL, " ");
  third_t = strtok(NULL, " ");
  fourth_t = strtok(NULL, " ");
  // it's a better choice to implement the control inside function 'cause it's possible that there aren't other token
  Node* tmp;
  for(tmp = first; tmp != NULL ; tmp = tmp->getNext()){
    
    if(strcmp(first_t,tmp->getData()->com) == 0){
      
      tmp->getData()->cmd(atoi(second_t), atoi(third_t), atoi(fourth_t));
      return 0;
    }
  }
  return 1;
  
  
}

