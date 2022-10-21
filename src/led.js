// get buttons
const high = document.getElementById('high');
const low = document.getElementById('low');

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
