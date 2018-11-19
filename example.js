
var press = require('./').press;
var move = require('./').move;
var getPos = require('./').getPos;

press(12);

setInterval(function() {
  move(Math.floor((Math.random()*100 + 1)), Math.floor((Math.random()*100 + 1)))
  console.log(getPos());
}, 500);

