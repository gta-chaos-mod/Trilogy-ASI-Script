const { WebSocketServer } = require('ws');

const ePickedVote = {
	UNDETERMINED: -1,
	NONE: 0,

	FIRST: 1 << 0,
	SECOND: 1 << 1,
	THIRD: 1 << 2,

	FIRST_SECOND: (1 << 0) | (1 << 1),
	FIRST_THIRD: (1 << 0) | (1 << 2),
	SECOND_THIRD: (1 << 1) | (1 << 2),

	ALL: (1 << 0) | (1 << 1) | (1 << 2),
};

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
			pickedChoice: ePickedVote.UNDETERMINED,
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
