# Debug and Test Stepper Motors for WebUSB-enabled devices

> Based on https://github.com/kalaschnik/stepper-motor-debugging
>
> 💡 As of fall 2022, WebUSB is still Chromium-only thing: https://caniuse.com/webusb
>
> 💡 To make Arduino IDE WebUSB-ready, follow the instructions here: https://github.com/webusb/arduino

# Demos

## Stepper Motor Demo

1. Upload [webusb-stepper-motor.ino](/src/webusb-stepper-motor/webusb-stepper-motor.ino) to your [WebUSB-enabled device](#resources)
2. Go to https://ccp-odc.eva.mpg.de/webusb/
3. Click Connect and select your device
4. Follow the UI

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

## LED Demo

1. Upload [led-demo.ino](/src/led-demo/led-demo.ino) to your [WebUSB-enabled device](#resources)
2. Go to https://ccp-odc.eva.mpg.de/webusb/
3. Click Connect and select your device
4. Follow the UI

# Development

https://developer.mozilla.org/en-US/docs/Web/API/USB

## Getting Device IDs

Use either `lsusb` (Linux) `system_profiler SPUSBDataType` (macOS). Or System Information App on macOS:
![](docs/system-information.png)

💡 Note that this also includes non-WebUSB devices! For compatibilty check [Resources](#resources) section.

### `getDevices()` — WebUSB API

```js
navigator.usb.getDevices().then((devices) => {
	console.log(`Total devices: ${devices.length}`);
	devices.forEach((device) => {
		console.log(
			`Product name: ${device.productName}, serial number ${device.serialNumber}`
		);
	});
	console.log(devices);
});
```

- `getDevices()` method of the USB interface returns a Promise that resolves with an array of USBDevice objects for paired attached devices. **Device ids are provided as integers**
- System Information App shows **device ids as hex codes**

## Request a device via ID

The `requestDevice(filters)` method of the USB interface returns a Promise that resolves with an instance of USBDevice if the specified device is found. Calling this function triggers the user agent's pairing flow.

You need to provide a filter array of objects [{}]. You can query the following properties: `vendorId, productId, classCode, subclassCode, protocolCode, serialNumber`

### `requestDevice()` — WebUSB API

Request a device with a specific vendorID

```js
navigator.usb
	.requestDevice({ filters: [{ vendorId: 9025 }] })
	.then((device) => {
		console.log(device);
	});
```

Get a list of all connected Devices (empty array of objects)

```js
navigator.usb.requestDevice({ filters: [{}] }).then((device) => {
	console.log(device);
});
```

### Notes

- Device IDs can be provided in hex (0x2341) or as integer (i.e., 9025)

# Resources

- Spec: https://wicg.github.io/webusb/
- Arduino w/ compatible Hardware (Processors are ATmega32U4 or SAMD21): https://github.com/webusb/arduino
