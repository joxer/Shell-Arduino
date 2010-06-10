
#ifndef SHELL_HPP
#define SHELL_HPP
#include <string.h>
#include <WProgram.h> 




class ArduinoShell {
  struct cmd{ 
  char* com;
    void (*cmd)(int,int,int) ;
};
  int bauds;
  cmd commands[7];
 public:
  ArduinoShell(int);
  
  int getChoice();
 private:
  int dispatch(char[]);
  
};
#endif
