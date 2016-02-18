#include <Wire.h>
#include <FabricaDigital_MCP23008.h>
#include <Keypad_MCP23008.h>

const byte I2C_ADDRESS = 0x20;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

Keypad_MCP23008 keypad = Keypad_MCP23008(rowPins, colPins, ROWS, COLS);

unsigned long loopCount = 0;
unsigned long timer_t = 0;

void setup(){
  keypad.begin(I2C_ADDRESS, makeKeymap(keys));
	Serial.begin(9600);
	
	// Try playing with different debounceTime settings to see how it affects
	// the number of times per second your loop will run. The library prevents
	// setting it to anything below 1 millisecond.
	kpd.setDebounceTime(10);	// setDebounceTime(mS)
}

void loop(){
	char key = kpd.getKey();
	
	// Report the number of times through the loop in 1 second. This will give
	// you a relative idea of just how much the debounceTime has changed the
	// speed of your code. If you set a high debounceTime your loopCount will
	// look good but your keypresses will start to feel sluggish.
	if ((millis() - timer_t) > 1000) {
		Serial.print("Your loop code ran ");
		Serial.print(loopCount);
		Serial.println(" times over the last second");
		loopCount = 0;
		timer_t = millis();
	}
	loopCount++;
	if(key)
		Serial.println(key);
}
