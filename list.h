#ifndef LIST_H
#define LIST_H
class Node{

  struct cmd current;
  Node* next;
 public:
  
  
  Node(char* name ,functor cmd){
    
    current.com = name;
    current.cmd = cmd;
    next = NULL;
  }
  

  Node(struct cmd mu){
    
    current = mu;
    next = NULL;
  }
  
  cmd*  getData(){
    return &current;
  }
  
  void setNext(Node* mu){
    
    next = mu;
  }
  
  Node* getNext(){
    return next;
  }
  

};


#endif