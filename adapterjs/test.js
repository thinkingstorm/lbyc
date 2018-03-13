const addon = require('./build/Release/addon');

//console.log(addon.hello());
//console.log(addon.add(3,5));

//addon((msg) => {
//  console.log(msg);
// Prints: 'hello world'
//})

const fn = addon();
console.log(fn());



