#include <ApplicationServices/ApplicationServices.h>
#include <node.h>
#include "nan.h"

using namespace v8;

NAN_METHOD(Press) {
  NanScope();

  if (args.Length() < 1) {
    NanThrowTypeError("Wrong number of arguments");
    NanReturnUndefined();
  }

  if (!args[0]->IsNumber()) {
    NanThrowTypeError("Wrong arguments");
    NanReturnUndefined();
  }

  CGEventRef down = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) args[0]->NumberValue(), true);
  CGEventPost(kCGHIDEventTap, down);
  CFRelease(down);

  CGEventRef up = CGEventCreateKeyboardEvent(NULL, (CGKeyCode) args[0]->NumberValue(), false);
  CGEventPost(kCGHIDEventTap, up);
  CFRelease(up);

  NanReturnUndefined();
}

NAN_METHOD(Move) {
  NanScope();

  if (args.Length() < 2) {
    NanThrowTypeError("Wrong number of arguments");
    NanReturnUndefined();
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    NanThrowTypeError("Wrong arguments");
    NanReturnUndefined();
  }


  size_t xMax = CGDisplayPixelsWide(kCGDirectMainDisplay);
  size_t yMax = CGDisplayPixelsHigh(kCGDirectMainDisplay);

  if (args[0]->NumberValue() > xMax || args[0]->NumberValue() < 0 || args[1]->NumberValue() > yMax || args[1]->NumberValue() < 0){
    NanThrowTypeError("Invalid cursor position");
    NanReturnUndefined();
  }

  CGEventRef move = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(args[0]->NumberValue(), args[1]->NumberValue()), kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);

  if(move == NULL) {
    NanThrowTypeError("Error creating the event");
    NanReturnUndefined();
  }

  NanReturnUndefined();
}

NAN_METHOD(GetPos) {
  NanScope();

  CGEventRef event = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);

  Local<Object> pos = NanNew<Object>();

  pos->Set(NanNew<String>("x"), NanNew<Number>(cursor.x));
  pos->Set(NanNew<String>("y"), NanNew<Number>(cursor.y));

  NanReturnValue(pos);
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew<String>("press"),
      NanNew<FunctionTemplate>(Press)->GetFunction());
  exports->Set(NanNew<String>("move"),
      NanNew<FunctionTemplate>(Move)->GetFunction());
  exports->Set(NanNew<String>("getPos"),
     NanNew<FunctionTemplate>(GetPos)->GetFunction());
}

NODE_MODULE(addon, Init)
