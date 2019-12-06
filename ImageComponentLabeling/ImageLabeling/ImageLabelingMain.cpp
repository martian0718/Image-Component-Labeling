#include <iostream> //allows us to use cin and cout
#include <cstdlib> //allows us to use rand()
#include "pair.h"
#include "stack.h"
#include "position.h"
#include "aqueue.h"
using namespace std;

void intro(int &dimension, double &density); //forward declaration of intro function
int dimensionInput(); //forward declaration of the dimensionInput function
double densityInput(); //forward declaration of the densityInput function
void initalGrid(Pair ** &gridDepth, Pair ** &gridBreadth, int dimension, double density); //foward declaration of initialGrid function
void printGrids(Pair **gridDepth,Pair ** gridBreadth, int dimension); //forward declaration of the printGrids function
void scanGrid(Pair **gridDepth, Pair **gridBreadth, int dimension); //forward declaration of the scanGrid functions
bool labelDepth(Pair **gridDepth, int row, int col, int label); //forward declaration of the labelDepth function
bool labelBreadth(Pair **gridBreadth, int row, int col, int label); //forward declaration of the labelBreadth function

int main(){
  //initializing variables
  int dimension; //dimension of the grid
  double density; //density of the grid being filled with foreground or background components
  //introduction and asks for user input
  intro(dimension,density); //spits out the intro to the program
  //making a 2D array of Pair Objects
  Pair **gridDepth;
  Pair **gridBreadth;
  //Initalizes the grid that we will be using
  initalGrid(gridDepth,gridBreadth,dimension,density);
  //prints the grids for depth first searching and breadth first searching
  printGrids(gridDepth,gridBreadth,dimension);
  //scan the grids and label them
  scanGrid(gridDepth, gridBreadth, dimension);
  //prints the new grids after
  cout<<"Grids after Depth First Searching And Breadth First Searching:"<<endl;
  cout<<"--------------------------------------------------------------"<<endl;
  printGrids(gridDepth,gridBreadth,dimension);
  //end program
  return 0;
}

void intro(int &dimension, double &density){
  char answer;
  cout<<"Welcome to the Image Labeling Component Program!!"<<endl;
  cout<<"We have a default setting for Density and Dimension of the image."<<endl;
  cout<<"\n"; //makes an extra line between default settings and introduction
  cout<<"Default Dimension: 15 x 15"<<endl;
  cout<<"Default Density: 0.33"<<endl;
  cout<<"\n";
  cout<<"Would you like to use these default settings? (y/n): ";
  cin>>answer;
  if(answer=='n'){
    cout<<"OK. That's fine. What would you like to change the settings to?"<<endl;
    dimension = dimensionInput(); //uses the function to get the user to input a dimension
    density = densityInput(); //uses the function to get the user to input a density
  } else {
    dimension = 15;
    density = 0.33;
  }
  cout<<"Dimension of Image: "<< dimension<<endl;
  cout<<"Density of Image: "<<density<<endl;
}

//gets the user to input a dimension for the grid
int dimensionInput(){
  int dimension;
  cout<<"Dimension (5-20): ";
  cin>>dimension;
  //loops through asking for dimension if is not in range
  if((dimension < 5) || (dimension > 20)){
    do {
      cout<<"Your input for Dimension of the image is not in range!"<<endl;
      cout<<"Please give a Dimension in range (5-20): ";
      cin>>dimension;
    } while((dimension < 5) || (dimension > 20));
  }
  return dimension;
}

//gets the user to input a density for the image component
double densityInput(){
  double density;
  cout<<"Now we need a Density between 0 and 1. ";
  cout<<"Density: ";
  cin>>density;
  if((density <= 0) || (density >= 1)){
    do {
      cout<<"Your input for Density of the Image Components is not in range!"<<endl;
      cout<<"Please give a Density in between the range (0-1): ";
      cin>>density;

    } while((density <= 0) || (density >= 1));
  }
  return density;
}

void initalGrid(Pair **&gridDepth, Pair **&gridBreadth, int dimension, double density){
  srand(time(NULL)); //initializes random seed
  //makes the 2D array
  gridDepth = new Pair*[dimension+2];
  for(int i = 0; i < dimension+2; i++){
    gridDepth[i] = new Pair[dimension+2];
  }
  gridBreadth = new Pair*[dimension+2];
  for(int i = 0; i < dimension+2; i++){
    gridBreadth[i] = new Pair[dimension+2];
  }
  //initalizes the wall around the grid that we don't print
  for(int col = 0; col < dimension+2; col++){
    gridDepth[0][col].updateLabel(0);
    gridBreadth[0][col].updateLabel(0);
    gridDepth[dimension+1][col].updateLabel(0);
    gridBreadth[dimension+1][col].updateLabel(0);
  }
  for(int row = 0; row < dimension+2; row++){
    gridDepth[row][0].updateLabel(0);
    gridBreadth[row][0].updateLabel(0);
    gridDepth[row][dimension+1].updateLabel(0);
    gridBreadth[row][dimension+1].updateLabel(0);

  }
  //initializes the grid with the random 1s and 0s
  for(int row = 1; row <= dimension; row++){
    for(int col = 1; col <= dimension; col++){
      int random = rand();
      double myR = (double)random/RAND_MAX;
      if(myR<density){
        gridDepth[row][col].updateLabel(1);
        gridBreadth[row][col].updateLabel(1);
      } else {
        gridDepth[row][col].updateLabel(0);
        gridDepth[row][col].updateLabel(0);
      }
    }
  }
}



void printGrids(Pair ** gridDepth, Pair **gridBreadth, int dimension){
  //prints out depth grid
  cout<<"Grid for Depth First Searching: "<<endl;
  cout<<endl;
  for(int row = 1; row <= dimension; row++){
    for(int col = 1; col <= dimension; col++){
      cout<<gridDepth[row][col]<<"  ";
    }
    cout<<"\n";
  }
  //prints out breadth grid
  cout<<"Grid for Breadth First Searching: "<<endl;
  cout<<endl;
  for(int row = 1; row <= dimension; row++){
    for(int col = 1; col <= dimension; col++){
      cout<<gridBreadth[row][col]<<"  ";
    }
    cout<<"\n";
  }
}
//scans the grid to label the image components by finding the 1s
void scanGrid(Pair **gridDepth, Pair  **gridBreadth, int dimension){
  int labelD = 2;
  int labelB = 2;
  for(int row = 1; row <= dimension; row++){
    for(int col = 1; col <= dimension; col++){
      if(gridDepth[row][col].label()==1){
        //update the image component with a new label for both depth and breadth
        labelDepth(gridDepth, row, col, labelD);
        labelD++;
      }
      if(gridBreadth[row][col].label()==1){
        labelBreadth(gridBreadth, row, col, labelB);
        labelB++;
      }
    }
  }
}
//labels the image by using depth first searching
bool labelDepth(Pair **gridDepth, int row, int col, int label){
  //creating a stack of positions
  Stack<position> check;

  // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up

   position currentLocation;
   currentLocation.row = row;
   currentLocation.col = col;
   int newR, newC;
   int option = 0;
   int lastOption = 3;
   int counter = 1;

   gridDepth[currentLocation.row][currentLocation.col].updateLabel(label);
   gridDepth[currentLocation.row][currentLocation.col].updatePosition(counter);
   check.push(currentLocation);
   do {
     while(option <= lastOption){ //goes through the options and makes sure it hasn't found the next position yet
       newR = currentLocation.row + offset[option].row;
       newC = currentLocation.col + offset[option].col;
       if(gridDepth[newR][newC].label()==1) break; //checks the new position if it needs to be labled.
       option++;
     }
     if(option <= lastOption){ //if we did find the next
       check.push(currentLocation); //then push the previous location into the stack
       currentLocation.row = newR; //make the new currentlocation to where we are now
       currentLocation.col = newC;
       counter++;
       gridDepth[newR][newC].updateLabel(label);
       gridDepth[newR][newC].updatePosition(counter);
       option = 0;
     } else { //if we couldn't find the next open position with the label

       if(check.empty()){
         return false;
       }
       currentLocation = check.top();
       check.pop();
       option = 0;
     }
   }while(!check.empty());

   return true;

}
//labels the image by using breadth first searching
bool labelBreadth(Pair **gridBreadth, int row, int col, int label){

  AQueue<position> check;

  // initialize offsets
  position offset[4];
  offset[0].row = 0; offset[0].col = 1;   // right
  offset[1].row = 1; offset[1].col = 0;   // down
  offset[2].row = 0; offset[2].col = -1;  // left
  offset[3].row = -1; offset[3].col = 0;  // up

  position currentLocation;
  currentLocation.row = row;
  currentLocation.col = col;
  position neighbor;
  int option = 0;
  int lastOption = 3;
  int counter = 1;
  bool found;

  gridBreadth[currentLocation.row][currentLocation.col].updateLabel(label);
  gridBreadth[currentLocation.row][currentLocation.col].updatePosition(counter);
  check.push(currentLocation);


  do {
    check.pop();
    found = false;
    for(int i = option; i <= lastOption; i++){
      neighbor.row = currentLocation.row + offset[i].row;
      neighbor.col = currentLocation.col + offset[i].col;
      if(gridBreadth[neighbor.row][neighbor.col].label()==1){
        counter++;
        found = true;
        gridBreadth[neighbor.row][neighbor.col].updateLabel(label);
        gridBreadth[neighbor.row][neighbor.col].updatePosition(counter);
        check.push(neighbor);
      }
    }
    if(check.empty())
      return false;
    currentLocation = check.front();
  }while( !check.empty() || found);

  return true;

}
