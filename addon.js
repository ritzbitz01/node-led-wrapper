var addon = require('./build/Release/led-wrapper');
//var pixeladdon = require('.build/Release/pixelobject');

var obj = new addon.LedWrapper();
var pixel = new addon.PixelObject(16,16,250,250,250);
console.log(typeof obj, pixel, obj.proto);
obj.setPixels(pixel);
//obj.SetPixels(pixel);
//console.log( obj.plusOne() ); // 11
//console.log( obj.plusOne() ); // 12
//console.log( obj.plusOne() ); // 13