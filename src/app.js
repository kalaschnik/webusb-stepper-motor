import { serial } from './serial.js';

console.log('Starting app');

console.log('Imported serial.js', serial);

const link = document.getElementById('connection');

link.addEventListener('click', () => {
	// navigator.usb
	// 	.requestDevice({ filters: [{ vendorId: 9025 }] })
	// 	.then((device) => {
	// 		console.log(device);
	// 	});

	serial.requestPort().then((device) => {
		if (device) {
			link.textContent = 'Connected';
			device.connect();
		}
	});
});
