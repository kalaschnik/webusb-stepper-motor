# Debug and Test Stepper Motors for WebUSB-enabled devices

> Based on https://github.com/kalaschnik/stepper-motor-debugging

This script uses the _Arduino Serial Monitor_ to receive an input to dynamically control different parameters of a stepper motor. This **parameters** are:

- Motor Speed (RPM)
- Motor Steps
- Motor Direction (either 1 (FORWARD) or 2 (BACKWARD))
- Motor Style (either 1 (SINGLE), 2 (DOUBLE), 3 (INTERLEAVE), 4 (MICROSTEP))

Example Input: `<10, 20, 1, 1>` which translates to:

- Set Motor Speed to 10 RPM
- Perform 20 Steps
- Move FORWARD
- in SINGLE steps
