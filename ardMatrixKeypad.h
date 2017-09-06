/*
 * ardMatrixKeypad.h
 *
 */

#ifndef ardMatrixKeypad_h
#define ardMatrixKeypad_h

class MatrixKeypad {
 public:
   MatrixKeypad(int) ;
   char getKeyValue() ;

 private:
   int  pcf8574_write(int, int) ;
   int  pcf8574_read(int) ;
};


#endif /* ardMatrixKeypad_h */