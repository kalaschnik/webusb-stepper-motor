import { serial } from './serial.js';

console.log('Starting app');

console.log('Imported serial.js', serial);

const link = document.getElementById('connection')! as HTMLAnchorElement;

link.addEventListener('click', () => {
	console.log('clicked');

	navigator.usb
		.requestDevice({ filters: [{ vendorId: 9025 }] })
		.then((device) => {
			console.log(device);
		});
});
