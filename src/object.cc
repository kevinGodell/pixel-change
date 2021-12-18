#include "object.h"
#include "callback.h"
#include "promise.h"
#include "engine.h"
#include "results.h"
#include <napi.h>
#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PixelChange::PixelChange(const Napi::CallbackInfo &info)
        : Napi::ObjectWrap<PixelChange>(info) {
    const Napi::Env env = info.Env();
    const Napi::HandleScope scope(env);
    const Napi::Object configObj = info[0].As<Napi::Object>();
    Configure(configObj, this->execute_, this->convert_, this->bufLength_);
}

Napi::FunctionReference PixelChange::constructor;

void PixelChange::Init(const Napi::Env &env) {
    const Napi::HandleScope scope(env);
    const Napi::Function func = DefineClass(env, "PixelChange", {
            InstanceMethod("compare", &PixelChange::Compare),
            InstanceMethod("compareSync", &PixelChange::CompareSync)
    });
    PixelChange::constructor = Napi::Persistent(func);
    PixelChange::constructor.SuppressDestruct();
}

Napi::Object PixelChange::NewInstance(const Napi::Env &env, const Napi::Object &config) {
    Napi::EscapableHandleScope scope(env);
    const Napi::Object object = PixelChange::constructor.New({config});
    return scope.Escape(napi_value(object)).ToObject();
}

Napi::Value PixelChange::Compare(const Napi::CallbackInfo &info) {
    const Napi::Env &env = info.Env();
    const Napi::Buffer<uint8_t> &napiBuf0 = info[0].As<Napi::Buffer<uint8_t>>();
    const Napi::Buffer<uint8_t> &napiBuf1 = info[1].As<Napi::Buffer<uint8_t>>();

    if (info[2].IsFunction()) {
        const Napi::Function &cb = info[2].As<Napi::Function>();

        if (napiBuf0.Length() != this->bufLength_ || napiBuf1.Length() != this->bufLength_) {
            return cb.Call({Napi::Error::New(env, "Both buffers must have a length of " + std::to_string(this->bufLength_)).Value()});
        }

        auto *asyncWorkerCallback = new AsyncWorkerCallback(cb, this->execute_, this->convert_, napiBuf0, napiBuf1);
        asyncWorkerCallback->Queue();
        return env.Undefined();
    } else {

        if (napiBuf0.Length() != this->bufLength_ || napiBuf1.Length() != this->bufLength_) {
            Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);
            deferred.Reject(Napi::Error::New(env, "Both buffers must have a length of " + std::to_string(this->bufLength_)).Value());
            return deferred.Promise();
        }

        auto *asyncWorkerPromise = new AsyncWorkerPromise(env, this->execute_, this->convert_, napiBuf0, napiBuf1);
        asyncWorkerPromise->Queue();
        return asyncWorkerPromise->getPromise();
    }
}

Napi::Value PixelChange::CompareSync(const Napi::CallbackInfo &info) {
    const Napi::Env &env = info.Env();
    const Napi::Buffer<uint8_t> &napiBuf0 = info[0].As<Napi::Buffer<uint8_t>>();
    const Napi::Buffer<uint8_t> &napiBuf1 = info[1].As<Napi::Buffer<uint8_t>>();

    if (napiBuf0.Length() != this->bufLength_ || napiBuf1.Length() != this->bufLength_) {
        throw Napi::Error::New(env, "Both buffers must have a length of " + std::to_string(this->bufLength_));
    }

    const uint8_t *buf0 = napiBuf0.Data();
    const uint8_t *buf1 = napiBuf1.Data();
    CallbackData callbackData;
    this->execute_(buf0, buf1, callbackData);
    return this->convert_(env, callbackData);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////