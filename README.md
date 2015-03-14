Mac-Key-Press
=============

Press a key or move the mouse on a Mac.

```javascript
var press = require('mac-key-press').press;
var move = require('mac-key-press').move;
var getPos = require('mac-key-press').getPos;

press(12);

setInterval(function() {
  move(Math.floor((Math.random()*1000)), Math.floor((Math.random()*1000)))
  console.log(getPos());
}, 500);
```

Keyboard
--------

![Alt text](mackeyboard1.gif)

(Image fetched here:
http://web.archive.org/web/20100501161453/http://www.classicteck.com/rbarticles/mackeyboard.php)

Install
-------

```
$ npm install mac-press-key
```

License
-------

Copyright (c) 2014-2015 Matteo Collina (http://matteocollina.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
