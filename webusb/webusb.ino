#include <WebUSB.h>
WebUSB WebUSBSerial(1, "127.0.0.1:5500/src/");

const int ledPin = 13;

void setup()
{
	WebUSBSerial.begin(9600);
	// needs empty while blocks in setup(), otherwise print() does not work
	while (!WebUSBSerial)
		;
	while (!SerialUSB)
		;

	// WebUSB output (console)
	// flush is needed, otherwise there is no ouput in the browser’s console
	WebUSBSerial.println("WebUSB Serial ready!");
	WebUSBSerial.flush();

	// Serial Monitor output
	SerialUSB.println("Starting from SerialUSB");

	pinMode(ledPin, OUTPUT);
}

void loop()
{
	if (WebUSBSerial && WebUSBSerial.available())
	{
		// read input from the browser
		int byte = WebUSBSerial.read();
		WebUSBSerial.write(byte);

		if (byte == 'H')
		{
			digitalWrite(ledPin, HIGH);
			SerialUSB.println("received H");
			WebUSBSerial.println("Tuning on the LED");
		}
		else if (byte == 'L')
		{
			digitalWrite(ledPin, LOW);
			SerialUSB.println("received L");
			WebUSBSerial.println("Tuning off the LED");
		}

		WebUSBSerial.flush();
	}
}