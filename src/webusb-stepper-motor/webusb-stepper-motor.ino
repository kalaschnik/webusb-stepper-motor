
// Adjusted Example 5 from: https://forum.arduino.cc/index.php?topic=396450.0
// ... to test and debug different stepper motor steps, directions, style using Serial Monitor input
// ... AND MODIFIED TO USE WEBUSB

#include <Adafruit_MotorShield.h>
#include <WebUSB.h>
WebUSB WebUSBSerial(1, "ccp-odc.eva.mpg.de/webusb/");

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #1 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];  // temporary array for use when parsing

// variables to hold the parsed data
uint16_t motorSpeed = 10;         // Set the delay for the Stepper Motor speed in RPM.
uint16_t motorSteps = 200;        // The number of steps we want to move
uint8_t motorDir = FORWARD;       // FORWARD (1), BACKWARD (2)
uint8_t motorStyle = INTERLEAVE;  // How to perform each step, can be SINGLE (1), DOUBLE (2), INTERLEAVE (3) or MICROSTEP (4)

boolean newData = false;

//============

void setup() {
    WebUSBSerial.begin(115200);
    // needs empty while blocks in setup(), otherwise print() does not work
    while (!WebUSBSerial) {
    }
    WebUSBSerial.println("Stepper Motor ready");
    WebUSBSerial.flush();

    AFMS.begin();  // create with the default frequency 1.6KHz
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (WebUSBSerial && WebUSBSerial.available() && newData == false) {
        rc = WebUSBSerial.read();
        WebUSBSerial.write(rc);

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            } else {
                receivedChars[ndx] = '\0';  // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {  // split the data into its parts

    char *strtokIndx;  // this is used by strtok() as an index

    strtokIndx = strtok(tempChars, ",");  // get the first part - the string
    motorSpeed = atoi(strtokIndx);        // copy it to messageFromPC

    strtokIndx = strtok(NULL, ",");  // this continues where the previous call left off
    motorSteps = atoi(strtokIndx);   // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    motorDir = atoi(strtokIndx);  // convert this part to a float

    strtokIndx = strtok(NULL, ",");
    motorStyle = atoi(strtokIndx);  // convert this part to a float

    // EXECUTE PARSED DATA
    myMotor->setSpeed(motorSpeed);
    myMotor->step(motorSteps, motorDir, motorStyle);

    // EXECUTE SHAKING (FORWARD/BACKWORD)
}

//============

void showParsedData() {
    WebUSBSerial.print("Speed (RPM): ");
    WebUSBSerial.println(motorSpeed);
    WebUSBSerial.print("Steps: ");
    WebUSBSerial.println(motorSteps);
    WebUSBSerial.print("Direction: ");
    WebUSBSerial.println(motorDir);
    WebUSBSerial.print("Style: ");
    WebUSBSerial.println(motorStyle);
    WebUSBSerial.flush();
}
