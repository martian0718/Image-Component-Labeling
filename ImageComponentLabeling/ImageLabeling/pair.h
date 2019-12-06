#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>
using namespace std;


class Pair{
private:
  int labels;
  int discoveredPosition;
public:
  Pair();
  Pair(int l, int d);
  void updateLabel(int x);
  int label();
  void updatePosition(int x);
  int position();
  friend ostream& operator <<(ostream& os, const Pair& p);
};

Pair:: Pair(){
  labels = 0;
  discoveredPosition = 0;
}
Pair:: Pair(int l, int d){
  labels = l;
  discoveredPosition = d;
}
void Pair:: updateLabel(int x){
  labels = x;
}
int Pair:: label(){
  return labels;
}
void Pair:: updatePosition(int x){
  discoveredPosition = x;
}
int Pair:: position(){
  return discoveredPosition;
}

ostream& operator <<(ostream& os, const Pair& p){
  if((p.labels/10) < 1 && (p.discoveredPosition/10) < 1)
    os <<"[  "<< p.labels<<","<<p.discoveredPosition<<"]";
  else if((p.labels/10 < 1) || (p.discoveredPosition/10) < 1)
    os <<"[ "<<p.labels<<","<<p.discoveredPosition<<"]";
  else if((p.labels/10) >= 1 && (p.discoveredPosition/10) >= 1)
    os <<"["<<p.labels<<","<<p.discoveredPosition<<"]";

}

 #endif
