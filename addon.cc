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

void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("press"),
      FunctionTemplate::New(Press)->GetFunction());
}

NODE_MODULE(addon, Init)
