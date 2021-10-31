#include "promise.h"
#include "engine.h"
#include "results.h"
#include "napi.h"
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AsyncWorkerPromise::AsyncWorkerPromise(const Napi::Env &env, const ExecuteFunc &execute, const ConvertFunc &convert, const Napi::Buffer<uint8_t> &napiBuf0, const Napi::Buffer<uint8_t> &napiBuf1)
        : Napi::AsyncWorker(env),
          execute_(execute),
          convert_(convert),
          buf0_(napiBuf0.Data()),
          buf1_(napiBuf1.Data()),
          buf0ref_(Napi::Reference<Napi::Buffer<uint8_t>>::New(napiBuf0, 1)),
          buf1ref_(Napi::Reference<Napi::Buffer<uint8_t>>::New(napiBuf1, 1)),
          deferred_(Napi::Promise::Deferred::New(env)) {
}

Napi::Promise AsyncWorkerPromise::getPromise() const {
    return deferred_.Promise();
}

void AsyncWorkerPromise::Execute() {
    this->execute_(this->buf0_, this->buf1_, this->callbackData_);
}

void AsyncWorkerPromise::OnOK() {
    deferred_.Resolve(this->convert_(Env(), this->callbackData_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////