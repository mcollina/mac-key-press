
var press = require('./').press;
var move = require('./').move;

press(12);

setInterval(function() {
  move(Math.floor((Math.random()*1000)), Math.floor((Math.random()*1000)))
}, 500);

