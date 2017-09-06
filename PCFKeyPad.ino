
/*
   PCFKeyPad.pde - Example sketch for use with 4x4 membrane flexible matrix and pcf8574 module
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

  USAGE
  -----
    Connect pcf8574 module to Arduino
    Check I2C address of pcf8574 module with 'Arduino I2C_Scanner'
    Update PCF_ADDRESS below
    Plug 4x4 flexible matrix into pcf8574 module (match P0 to Row 1)
    Upload sketch and open serial monitor
    press keys on monitor and values should be displayed in serial monitor

*/

#include <Wire.h>
#include <ardMatrixKeypad.h>

#define PCF_ADDRESS       0x20

MatrixKeypad Keypad = MatrixKeypad(PCF_ADDRESS) ;

void setup() {
  Serial.begin(9600) ;
  Wire.begin();
  //
  delay(250) ;
  Serial.println("4x4 membrane keypad via PCF8574 expander") ;
}

void loop() {
  char keyValue = Keypad.getKeyValue() ;

  if (keyValue != '~') {
    Serial.println(keyValue) ;
    delay(400) ;
  }
}

