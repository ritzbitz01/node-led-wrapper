#ifndef LEDWRAPPER_H
#define LEDWRAPPER_H

#include <node.h>
#include "pixelobject.h"
#include "led-matrix.h"

class LedWrapper : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  explicit LedWrapper();
  ~LedWrapper();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetPixels(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;

  //RGBMatrix* m;
};

#endif