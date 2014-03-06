#include <ApplicationServices/ApplicationServices.h>
#include <node.h>
#include "nan.h"

using namespace v8;

NAN_METHOD(Press) {
  NanScope();

  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    NanReturnUndefined();
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
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
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    NanReturnUndefined();
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    NanReturnUndefined();
  }

  CGEventRef move = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(args[0]->NumberValue(), args[1]->NumberValue()), kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);

  if(move == NULL) {
    ThrowException(Exception::TypeError(String::New("Error creating the event")));
    NanReturnUndefined();
  }

  NanReturnUndefined();
}

NAN_METHOD(GetPos) {
  NanScope();

  CGEventRef event = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);

  Local<Object> pos = Object::New();

  pos->Set(String::NewSymbol("x"), Number::New(cursor.x));
  pos->Set(String::NewSymbol("y"), Number::New(cursor.y));

  NanReturnValue(pos);
}

void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("press"),
      FunctionTemplate::New(Press)->GetFunction());
  exports->Set(String::NewSymbol("move"),
      FunctionTemplate::New(Move)->GetFunction());
  exports->Set(String::NewSymbol("getPos"),
      FunctionTemplate::New(GetPos)->GetFunction());
}

NODE_MODULE(addon, Init)
