#include <ApplicationServices/ApplicationServices.h>
#include <napi.h>
#include "napi.h"

using namespace Napi;

Napi::Value Press(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  CGEventRef down = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) info[0].As<Napi::Number>().DoubleValue(), true);
  CGEventPost(kCGHIDEventTap, down);
  CFRelease(down);

  CGEventRef up = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) info[0].As<Napi::Number>().DoubleValue(), false);
  CGEventPost(kCGHIDEventTap, up);
  CFRelease(up);

  return env.Null();
}

Napi::Value Move(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t xMax = CGDisplayPixelsWide(kCGDirectMainDisplay);
  size_t yMax = CGDisplayPixelsHigh(kCGDirectMainDisplay);

  if (info[0].As<Napi::Number>().DoubleValue() > xMax || info[0].As<Napi::Number>().DoubleValue() < 0 || info[1].As<Napi::Number>().DoubleValue() > yMax || info[1].As<Napi::Number>().DoubleValue() < 0){
    Napi::TypeError::New(env, "Invalid cursor position").ThrowAsJavaScriptException();
    return env.Null();
  }

  CGEventRef move = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(info[0].As<Napi::Number>().DoubleValue(), info[1].As<Napi::Number>().DoubleValue()), kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);

  if(move == NULL) {
    Napi::TypeError::New(env, "Error creating the event").ThrowAsJavaScriptException();
    return env.Null();
  }

  return env.Null();
}

Napi::Value GetPos(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  CGEventRef event = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);

  Napi::Object pos = Napi::Object::New(env);

  (pos).Set(Napi::String::New(env, "x"), Napi::Number::New(env, cursor.x));
  (pos).Set(Napi::String::New(env, "y"), Napi::Number::New(env, cursor.y));

  return pos;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "press"), Napi::Function::New(env, Press));
  exports.Set(Napi::String::New(env, "move"), Napi::Function::New(env, Move));
  exports.Set(Napi::String::New(env, "getPos"), Napi::Function::New(env, GetPos));

  return exports;
}

NODE_API_MODULE(addon, Init)
