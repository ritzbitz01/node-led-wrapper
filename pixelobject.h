#ifndef PIXELOBJECT_H
#define PIXELOBJECT_H

#include <node.h>

class PixelObject : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  uint8_t x_;
  uint8_t y_;
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;
 private:
  explicit PixelObject(uint8_t x_ = 0, uint8_t y_ = 0, uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0);
  ~PixelObject();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;
 
};

#endif