const { WebSocketServer } = require('ws');

const tests = {
	time: {
		type: 'time',
		data: {
			remaining: 30000,
			cooldown: 60000,
			mode: '',
		},
	},
	votes: {
		type: 'votes',
		data: {
			effects: ['Effect 1', 'Effect Two', 'Effect $$$'],
			votes: [50, 120, 300],
			pickedChoice: -1,
		},
	},
};

function getRandomInt(max, min = 0) {
	return Math.floor(Math.random() * max) + min;
}

function test() {
	const server = new WebSocketServer({ port: 42069 });

	server.on('connection', (socket) => {
		setInterval(() => {
			tests.time.data.remaining -= 10;
			if (tests.time.data.remaining <= 0) {
				tests.time.data.remaining = tests.time.data.cooldown;
			}

			for (let i = 0; i < 3; i++) {
				tests.votes.data.votes[i] = getRandomInt(500);
			}

			socket.send(JSON.stringify(tests.time));
			socket.send(JSON.stringify(tests.votes));
		}, 10);
	});

	console.log(`Websocket Server listening on port ${42069}.`);
}

test();
