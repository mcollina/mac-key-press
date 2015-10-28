#include <ApplicationServices/ApplicationServices.h>
#include <node.h>
#include "nan.h"

using namespace v8;

NAN_METHOD(Press) {

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  CGEventRef down = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) info[0]->NumberValue(), true);
  CGEventPost(kCGHIDEventTap, down);
  CFRelease(down);

  CGEventRef up = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) info[0]->NumberValue(), false);
  CGEventPost(kCGHIDEventTap, up);
  CFRelease(up);

  return;
}

NAN_METHOD(Move) {

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }


  size_t xMax = CGDisplayPixelsWide(kCGDirectMainDisplay);
  size_t yMax = CGDisplayPixelsHigh(kCGDirectMainDisplay);

  if (info[0]->NumberValue() > xMax || info[0]->NumberValue() < 0 || info[1]->NumberValue() > yMax || info[1]->NumberValue() < 0){
    Nan::ThrowTypeError("Invalid cursor position");
    return;
  }

  CGEventRef move = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(info[0]->NumberValue(), info[1]->NumberValue()), kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);

  if(move == NULL) {
    Nan::ThrowTypeError("Error creating the event");
    return;
  }

  return;
}

NAN_METHOD(GetPos) {

  CGEventRef event = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);

  Local<Object> pos = Nan::New<Object>();

  Nan::Set(pos, Nan::New<String>("x").ToLocalChecked(), Nan::New<Number>(cursor.x));
  Nan::Set(pos, Nan::New<String>("y").ToLocalChecked(), Nan::New<Number>(cursor.y));

  info.GetReturnValue().Set(pos);
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New<String>("press").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(Press)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("move").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(Move)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("getPos").ToLocalChecked(),Nan::GetFunction(Nan::New<FunctionTemplate>(GetPos)).ToLocalChecked());
}

NODE_MODULE(addon, Init)
