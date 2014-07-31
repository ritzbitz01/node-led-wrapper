#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <v8.h>
#include "led-wrapper.h"
#include "led-matrix.h"
//#include "pixelobject.h"

using namespace v8;

Persistent<Function> LedWrapper::constructor;

LedWrapper::LedWrapper() {

}

LedWrapper::~LedWrapper() {

}

void LedWrapper::Init(Handle<Object> exports) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("LedWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  fprintf(stderr, "CALLING PROTOTYPE");
  //NODE_SET_PROTOTYPE_METHOD(tpl, "setPixels", SetPixels);
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPixels"),
       FunctionTemplate::New(SetPixels)->GetFunction());
  constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("LedWrapper"), constructor);
}

Handle<Value> LedWrapper::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
  	fprintf(stderr, "CALLING CONSTRUCTOR");
    // Invoked as constructor: `new MyObject(...)`
    //double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    LedWrapper* obj = new LedWrapper();
    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    fprintf(stderr, "NOT CALLING CONSTRUCTOR");
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

Handle<Value> LedWrapper::SetPixels(const Arguments& args) {
	fprintf(stderr, "CALLING SET PIXELS\n");
	// Arguments can either be a single Pixel, or a Pixel array.
	HandleScope scope;

	//Local<Array> pixelArray = Local<Array>::Cast(args[0]);

	//int arrayLength = pixelArray->Length();

	PixelObject* obj = ObjectWrap::Unwrap<PixelObject>(args[0]->ToObject());
	fprintf(stderr, "obj unwrapped\n");
	// Create a RgbMatrix and set the pixels
	GPIO io;
	fprintf(stderr, "GPIO created");
  	if (!io.Init())
    	fprintf(stderr, "ERROR SETTING UP GPIO");

    fprintf(stderr, "GPIO SET UP\n");
  	// The matrix, our 'frame buffer'.
  	RGBMatrix m(&io);

  	//for(int i = 0; i < arrayLength; i++) {
  	//	Handle<PixelObject> obj = Handle<PixelObject>::Cast(pixelArray->Get(Integer::New(i)));
  		//pixelArray->Get(Integer::New(i))->ToObject();
  	m.SetPixel(obj->x_, obj->y_, obj->r_, obj->g_, obj->b_);
  	//}

	return scope.Close(Undefined());
}

// void init(Handle<Object> exports) {
// 	exports->Set(String::NewSymbol("hello"),
// 	FunctionTemplate::New(Method)->GetFunction());
// }

//NODE_MODULE(led_wrapper, LedWrapper::Init)