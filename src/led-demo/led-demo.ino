#include <WebUSB.h>
WebUSB WebUSBSerial(1, "https://ccp-odc.eva.mpg.de/webusb/");

const int ledPin = 13;

// if you want to use the serial monitor && the browser, uncomment the following line
// if you only want to use this sketch in the browser set it to true
const bool onlyWebUSBEnabled = true;

void setup() {
    WebUSBSerial.begin(9600);
    if (!onlyWebUSBEnabled) {
        SerialUSB.begin(9600);
    }
    // needs empty while blocks in setup(), otherwise print() does not work
    while (!WebUSBSerial) {
    }
    if (!onlyWebUSBEnabled) {
        while (!SerialUSB) {
        }
    }

    // WebUSB output (console)
    // flush is needed, otherwise there is no ouput in the browser’s console
    WebUSBSerial.println("WebUSB Serial ready!");
    WebUSBSerial.flush();

    // Serial Monitor output
    if (!onlyWebUSBEnabled) {
        SerialUSB.println("Starting from SerialUSB");
    }

    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (WebUSBSerial && WebUSBSerial.available()) {
        // read input from the browser
        int byte = WebUSBSerial.read();
        WebUSBSerial.write(byte);

        if (byte == 'H') {
            digitalWrite(ledPin, HIGH);
            if (!onlyWebUSBEnabled) {
                SerialUSB.println("received H");
            }
            WebUSBSerial.println("Turning on the LED");
        } else if (byte == 'L') {
            digitalWrite(ledPin, LOW);
            if (!onlyWebUSBEnabled) {
                SerialUSB.println("received L");
            }
            WebUSBSerial.println("Turning off the LED");
        }

        WebUSBSerial.flush();
    }
}