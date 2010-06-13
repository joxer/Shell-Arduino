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

#ifndef FUNCTOR
#define FUNCTOR
typedef void (*functor)(int,int,int);
struct cmd{ 
  char* com;
  functor cmd;
  };

#endif


#include <string.h>
#include <WProgram.h> 
#include <list.h>

#ifndef SHELL_HPP
#define SHELL_HPP




class ArduinoShell {
  Node *first;
  int bauds;
  cmd commands[7];
 public:
  ArduinoShell(int);
  void addFunction(char*, functor);
  int getChoice();
 private:
  int dispatch(char[]);
  
};
#endif
