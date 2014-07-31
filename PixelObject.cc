#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <v8.h>
#include "pixelobject.h"

using namespace v8;

Persistent<Function> PixelObject::constructor;

PixelObject::PixelObject(uint8_t pixelX, uint8_t pixelY, uint8_t pixelR, uint8_t pixelG, uint8_t pixelB) 
: x_(pixelX), y_(pixelY), r_(pixelR), g_(pixelG), b_(pixelB) {

}

PixelObject::~PixelObject() {

}

// uint8_t pixelX;
// uint8_t pixelY;
// uint8_t pixelR;
// uint8_t pixelG;
// uint8_t pixelB;

void PixelObject::Init(Handle<Object> exports) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("PixelObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  // tpl->PrototypeTemplate()->Set(String::NewSymbol("setX"),
  //     FunctionTemplate::New(SetX)->GetFunction());
  constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("PixelObject"), constructor);
}

Handle<Value> PixelObject::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    uint8_t x = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    uint8_t y = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
    uint8_t r = args[2]->IsUndefined() ? 0 : args[2]->NumberValue();
    uint8_t g = args[3]->IsUndefined() ? 0 : args[3]->NumberValue();
    uint8_t b = args[4]->IsUndefined() ? 0 : args[4]->NumberValue();
    PixelObject* obj = new PixelObject(x, y, r, g, b);
    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

// Handle<Value> PixelObject::SetX(const Arguments& args) {
// 	HandleScope scope;
// 	x_ = args[0]->NumberValue();
// 	return scope.Close(Number::new(x_));
// }

// Handle<Value> PixelObject::SetY(const Arguments& args) {
// 	HandleScope scope;
// 	return scope.Close(String::New("world"));
// }

// Handle<Value> PixelObject::SetR(const Arguments& args) {
// 	HandleScope scope;
// 	return scope.Close(String::New("world"));
// }

// Handle<Value> PixelObject::SetG(const Arguments& args) {
// 	HandleScope scope;
// 	return scope.Close(String::New("world"));
// }

// Handle<Value> PixelObject::SetB(const Arguments& args) {
// 	HandleScope scope;
// 	return scope.Close(String::New("world"));
// }

// void init(Handle<Object> exports) {
// 	exports->Set(String::NewSymbol("hello"),
// 	FunctionTemplate::New(Method)->GetFunction());
// }

//NODE_MODULE(pixelobject, PixelObject::Init)