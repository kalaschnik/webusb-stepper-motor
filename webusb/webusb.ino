#include <WebUSB.h>

WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/");

void setup()
{
	WebUSBSerial.begin(9600);
	while (!WebUSBSerial)
	{
		;
	}
}

void loop()
{
	WebUSBSerial.println("Hello from Arduino to Browser");
	WebUSBSerial.flush();
	delay(1000);
}