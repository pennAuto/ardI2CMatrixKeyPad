/*

   ardMatrixKeypad.cpp - 4x4 flexible keypad membrane + pcf8574 module
   Copyright (C) 2017  W Mead <ironapp-pennAuto@yahoo.com>

  LICENCE
  -------
    This program is free software: you can redistribute it and/or modify
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

#include "ardMatrixKeypad.h"
#include <Wire.h>                //I2C
#include <Arduino.h>             //Need for 'byte' type

//Keypad matrix
const char kbdMatrix[4][4] = {
	"123A",
	"456B",
	"789C",
	"*0#D"
} ;

//Pin mask P0-P3
//Inverted pin numbers e.g.
// Pin P0 =
//   P3  P2  P1  P0
//    0   0   0   1
// Pin mask =
//    1   1   1   0  = 0x0E
const int maskPin[4] = {
	0x0E,
	0x0D,
	0x0B,
	0x07
} ;

int PCF_ADDRESS ;

//Constructor
MatrixKeypad::MatrixKeypad(int Slave_ADDRESS){
  PCF_ADDRESS = Slave_ADDRESS ;
}

/*
 * Public Methods
 */

char MatrixKeypad::getKeyValue(){

  char          kValue ;        //pressed key
  int           noOfBytes ;     //for debugging
  byte          maskRow ;
  byte          maskCurrent ;

  kValue = '~' ;                //Default value
  //Assign row (posR)
  for(int posR = 0; posR<4; posR++){
    maskRow     = maskPin[posR] ;
	maskRow     = 0xF0 | maskRow ;
	//Write
	noOfBytes   = pcf8574_write(PCF_ADDRESS, maskRow) ;
    //Read
    maskCurrent = ~pcf8574_read(PCF_ADDRESS) ;
	maskCurrent >>= 4 ;
	//Find column (posC)
    if(maskCurrent){
	  int posC = 0;
      while ((maskCurrent >> (posC++)) != 0 ) ;
      posC -= 2 ;
      kValue = kbdMatrix[posR][posC] ;
    }
  }
  return kValue ;
}

/*
 * Private Methods
 */

int MatrixKeypad::pcf8574_write(int Slave_Address, int data){

  int noOfBytes ;                    //for debugging

  Wire.beginTransmission(Slave_Address) ;
  Wire.write(0xFF) ;                 //Reset
  noOfBytes = Wire.write(data) ;     //relevant row
  Wire.endTransmission() ;

  return noOfBytes ;
}

int MatrixKeypad::pcf8574_read(int Slave_Address){

  Wire.requestFrom(Slave_Address, 1) ;
  return Wire.read() ;
}
