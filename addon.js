var addon = require('./build/Release/led-wrapper');
//var pixeladdon = require('.build/Release/pixelobject');

var obj = new addon.LedWrapper();
var pixelArray = new Uint8Array(8);

pixelArray[0] = 0;
pixelArray[1] = 250;
pixelArray[2] = 250;
pixelArray[3] = 250;
pixelArray[4] = 1;
pixelArray[5] = 120;
pixelArray[6] = 240;
pixelArray[7] = 80;//[0,250,250,250,1,120,240,80];
//var pixel = new addon.PixelObject(16,16,250,250,250);
//console.log(typeof obj, pixel, obj.proto);
//obj.setPixels(pixel);
//var pixel2 = new addon.PixelObject(16,20, 120, 240, 80);
obj.setPixels(pixelArray);
//obj.SetPixels(pixel);
//console.log( obj.plusOne() ); // 11
//console.log( obj.plusOne() ); // 12
//console.log( obj.plusOne() ); // 13