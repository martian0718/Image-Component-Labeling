#ifndef POSITION_H
#define POSITION_H

struct position
{
   int row,  // row number of position
       col;  // column number of position

   operator int() const {return row;}
};

#endif
