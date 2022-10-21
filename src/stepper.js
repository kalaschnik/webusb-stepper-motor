const lutDirection = {
	forward: 1,
	backward: 2,
};

const lutStyle = {
	single: 1,
	double: 2,
	interleave: 3,
	microstep: 4,
};

// get all form elements
document.querySelector('form').addEventListener('submit', (e) => {
	e.preventDefault();
	const { speed, steps, direction, style } = Object.fromEntries(
		new FormData(e.target).entries()
	);

	// data needs to be in <speed: number, steps: number, direction: number, style: number>
	const targetString = `<${speed}, ${steps}, ${lutDirection[direction]}, ${lutStyle[style]}>`;
	console.log('Target String:', targetString);

	if (port) {
		port.send(textEncoder.encode(targetString)).catch((error) => {
			console.log('Send error: ' + error);
		});
	}
});
