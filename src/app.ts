console.log('Starting app');

const link = document.getElementById('connection')! as HTMLAnchorElement;

link.addEventListener('click', () => {
	console.log('clicked');

	navigator.usb
		.requestDevice({ filters: [{ vendorId: 9025 }] })
		.then((device) => {
			console.log(device);
		});
});
