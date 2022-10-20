// log all devices
document.getElementById('all-devices').addEventListener('click', () => {
	navigator.usb.requestDevice({ filters: [{}] }).then((device) => {
		console.log(device);
	});
});

const link = document.getElementById('connection');
const high = document.getElementById('high');
const low = document.getElementById('low');

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

high.addEventListener('click', () => {
	if (port) {
		port.send(textEncoder.encode('H')).catch((error) => {
			console.log('Send error: ' + error);
		});
		console.log('Sent H, turning LED on');
	}
});

low.addEventListener('click', () => {
	if (port) {
		port.send(textEncoder.encode('L')).catch((error) => {
			console.log('Send error: ' + error);
		});
		console.log('Sent L, turning LED off');
	}
});
