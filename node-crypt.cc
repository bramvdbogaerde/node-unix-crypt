// hello.cc
#include <unistd.h>
#include <fcntl.h>
#include <node.h>
#include <crypt.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Crypt(const FunctionCallbackInfo<Value>& args) {
  char *phrase;
  char *settings;
  char* crypt_answer;
  Isolate* isolate = args.GetIsolate();
  // check function arity 
  if (args.Length() != 2) {
     isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
     return;
  } 
  if (!args[0]->IsString() || !args[1]->IsString()) {
      // the arguments should be two strings, the first one is the passphrase while the second is is the setting
      isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
      return;
  }

  // Convert to compatible C types 
  v8::String::Utf8Value v8_phrase(isolate, args[0]);
  v8::String::Utf8Value v8_settings(isolate, args[1]);
  phrase = *v8_phrase;;
  settings = *v8_settings;

  // Now run the operation
  crypt_answer = crypt(phrase, settings);
  
  // Assign the answer to the return value.
  args.GetReturnValue().Set(String::NewFromUtf8(
      isolate, crypt_answer).ToLocalChecked());
}

void CryptGenSalt(const FunctionCallbackInfo<Value>& args) {
   char *prefix;
   unsigned long count; 
   char* setting;

   Isolate* isolate = args.GetIsolate();

   if (args.Length() != 2) {
      isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
      return;
   }
   if (!args[0]->IsString() && !args[0]->IsNumber()) {
      isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
      return;
   }

   v8::String::Utf8Value v8_prefix(isolate, args[0]);
   prefix = *v8_prefix;
   count = args[1].As<v8::Number>()->Value();
   setting = crypt_gensalt(prefix, count, NULL, 0);
   
   args.GetReturnValue().Set(String::NewFromUtf8(
      isolate, setting).ToLocalChecked());
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "crypt", Crypt);
  NODE_SET_METHOD(exports, "gensalt", CryptGenSalt);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo
