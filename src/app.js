console.log('Starting app');

console.log('Imported serial.js helper object', serial);

// get connection links

// log all devices
document.getElementById('all-devices').addEventListener('click', () => {
	navigator.usb.requestDevice({ filters: [{}] }).then((device) => {
		console.log(device);
	});
});

const link = document.getElementById('connection');

let port;
let textDecoder = new TextDecoder();
let textEncoder = new TextEncoder();
link.addEventListener('click', () => {
	if (port) {
		// If port is already connected, disconnect it
		link.textContent = 'Connect';
		port.disconnect();
		port = null;
		console.log('Device is disconnected.');
	} else {
		// If there is no port, then connect to a new port
		serial
			.requestPort()
			.then((selectedPort) => {
				port = selectedPort;
				port.connect().then(
					() => {
						console.log(
							'Device is connected to Product ID: ' +
								port.device_.productId.toString(16) +
								' and Vendor ID: ' +
								port.device_.vendorId.toString(16)
						);

						link.textContent = 'Disconnect';
						port.onReceive = (data) => {
							console.log(textDecoder.decode(data));
						};
						port.onReceiveError = (error) => {
							console.log('Receive error: ' + error);
						};
					},
					(error) => {
						console.log('Connection error: ' + error);
					}
				);
			})
			.catch((error) => {
				console.log('Connection error: ' + error);
			});
	}
});
