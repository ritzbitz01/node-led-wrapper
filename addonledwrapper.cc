#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "led-wrapper.h"
#include "pixelobject.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  LedWrapper::Init(exports);
  PixelObject::Init(exports);
}

NODE_MODULE(led_wrapper, InitAll)