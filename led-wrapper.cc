#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <unistd.h>
#include "led-wrapper.h"
#include "led-matrix.h"
#include "thread.h"
#include "rgbmatrixmanipulator.h"
#include "displayupdater.h"
//#include "pixelobject.h"

using namespace v8;

// Base-class for a Thread that does something with a matrix.
// class RGBMatrixManipulator : public Thread {
// public:
//   RGBMatrixManipulator(RGBMatrix *m) : running_(true), matrix_(m) {}
//   virtual ~RGBMatrixManipulator() { running_ = false; }

//   // Run() implementation needs to check running_ regularly.

// protected:
//   volatile bool running_;  // TODO: use mutex, but this is good enough for now.
//   RGBMatrix *const matrix_;
// };

// Pump pixels to screen. Needs to be high priority real-time because jitter
// here will make the PWM uneven.

RGBMatrix* LedWrapper::m;

RGBMatrixManipulator* LedWrapper::updater;

GPIO LedWrapper::io;

Persistent<Function> LedWrapper::constructor;

LedWrapper::LedWrapper() {
	// fprintf(stderr, "LED MATRIX CONSTRUCTOR GO");
	// // // Create a RgbMatrix and set the pixels
//	 GPIO io;
	// fprintf(stderr, "GPIO created\n");
   	if (!io.Init())
     	fprintf(stderr, "ERROR SETTING UP GPIO\n");

     fprintf(stderr, "GPIO SET UP\n");
   	// The matrix, our 'frame buffer'.
  	m = new RGBMatrix(&io);

  	 // the DisplayUpdater continuously pushes the matrix
    // content to the display.
    updater = new DisplayUpdater(m);
    updater->Start(10);   // high priority

 //  	// The RGBMatrixManipulator objects are filling
 //  	// the matrix continuously.
 //  	//RGBMatrixManipulator *image_gen = NULL;

 //  	// the DisplayUpdater continuously pushes the matrix
 //  	// content to the display.
 //  	RGBMatrixManipulator *updater = new DisplayUpdater(m);
 //  	updater->Start(10);   // high priority

 //  	//image_gen->Start();
}

LedWrapper::~LedWrapper() {
  // Stopping threads and wait for them to join.
  

  // Final thing before exit: clear screen and update once, so that
  // we don't have random pixels burn
  m->ClearScreen();
  m->UpdateScreen();
  delete m;
  delete updater;
}

void LedWrapper::Init(Handle<Object> exports) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("LedWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  //NODE_SET_PROTOTYPE_METHOD(tpl, "setPixels", SetPixels);
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPixels"),
       FunctionTemplate::New(SetPixels)->GetFunction());
  constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("LedWrapper"), constructor);
}

Handle<Value> LedWrapper::New(const Arguments& args) {
  HandleScope scope;



  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    //double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    LedWrapper* obj = new LedWrapper();
    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

Handle<Value> LedWrapper::SetPixels(const Arguments& args) {
	fprintf(stderr, "CALLING SET PIXELS\n");
	// Arguments can either be a single Pixel, or a Pixel array.
	HandleScope scope;

	//TypedArrayWrapper pixelArray = ObjectWrap::Unwrap<TypedArrayWrapper>(args[0]->ToObject());


	//<uint32_t>
//	Local<Array> pixelArray = Local<Array>::Cast(args[0]);

	Local<Object> pixelArray = args[0]->ToObject();
	Handle<Object> pixelArrayBuffer = pixelArray->Get(String::New("buffer"))->ToObject();
	int arrayLength = pixelArray->Get(String::New("byteLength"))->Uint32Value();

	Local<Array> data;

	// if (obj->GetIndexedPropertiesExternalArrayDataType() != kExternalIntArray) return scope.Close(Undefined());
	// int len = obj->GetIndexedPropertiesExternalArrayDataLength();
	// int* data = static_cast<int*>(obj->GetIndexedPropertiesExternalArrayData());

	//fprintf(stderr, "Data Value is: %d", data[0]);
	//Array* pixelArray = args[0];
	//PixelObject* obj = ObjectWrap::Unwrap<PixelObject>(args[0]->ToObject());


//	int arrayLength = pixelArray->Length();
	//fprintf(stderr, "Pixel array length %d", arrayLength );
	//PixelObject* obj = ObjectWrap::Unwrap<PixelObject>(args[0]->ToObject());
	//fprintf(stderr, "obj unwrapped\n");
	// Create a RgbMatrix and set the pixels
//	GPIO io;
//	//fprintf(stderr, "GPIO created\n");
//  	if (!io.Init())
//    	fprintf(stderr, "ERROR SETTING UP GPIO\n");

    //fprintf(stderr, "GPIO SET UP\n");
  	//The matrix, our 'frame buffer'.
  	//RGBMatrix m2(&io);

	Local<v8::Integer> ignore;
  	int tempX = 127;
  	int tempY = 31;
  	uint8_t* tempB;
  	uint8_t* tempG;
  	uint8_t* tempR;
  	int i = 0;

  	while(i < arrayLength) {

  	// first value is alpha... drop it
  	i++;

  	tempB = &((uint8_t*) pixelArrayBuffer->GetIndexedPropertiesExternalArrayData())[i];

	i++;

	tempG = &((uint8_t*) pixelArrayBuffer->GetIndexedPropertiesExternalArrayData())[i];

	i++;

	tempR = &((uint8_t*) pixelArrayBuffer->GetIndexedPropertiesExternalArrayData())[i];

	i++;


//  //		while(i < len) {
//  		//Handle<Object> obj = Handle<Object>::Cast(pixelArray->Get(Integer::New(i)));
// 		tempR = pixelArray->Get(Integer::New(i))->ToInteger()->Value();
//  			//tempR = data[i];
//  		i++;
//  		tempG = pixelArray->Get(Integer::New(i))->ToInteger()->Value();
//  		//tempG = data[i];
//  		i++;
//  		tempB = pixelArray->Get(Integer::New(i))->ToInteger()->Value();
//  		//tempB = data[i];
//  		i++;
//  		//ignore = pixelArray->Get(Integer::New(i))->ToInteger();
//  		//ignore = data[i];
//  		i++;

//		fprintf(stderr, "x: %d y:%d R:%d G:%d B:%d \n", tempX, tempY, *tempR, *tempG, *tempB);
  		
  		//m2.SetPixel(tempX, tempY, tempR, tempG, tempB);
	  	m->SetPixel(tempX, tempY, *tempR, *tempG, *tempB);
	  	if(tempX == 0) {
	  		tempX = 127;
	  		tempY --;
	  	} else {
	  		tempX --;
	  	}

	}
	//fprintf(stderr, "UPDATING SCREEN");
	//m2.UpdateScreen();
//  	m->UpdateScreen();
  	//usleep(5000000);

  	// m.ClearScreen();
   //  m.UpdateScreen();
	return scope.Close(Undefined());
}

// void init(Handle<Object> exports) {
// 	exports->Set(String::NewSymbol("hello"),
// 	FunctionTemplate::New(Method)->GetFunction());
// }

//NODE_MODULE(led_wrapper, LedWrapper::Init)