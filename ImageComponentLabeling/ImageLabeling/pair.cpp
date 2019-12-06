#include <iostream>
#include "pair.h"
using namespace std;
 //testing pair.h making sure it works
int main(){
  Pair one;
  Pair two;

  one.updateLabel(3);
  two.updateLabel(2);
  two.updatePosition(1);

  cout<<one.label()<<" and "<<one.position()<<endl; //3 and 0
  cout<<two.label()<<" and "<<two.position()<<endl; //2 and 1
}
