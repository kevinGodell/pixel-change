#include "callback.h"
#include "engine.h"
#include "results.h"
#include "napi.h"
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AsyncWorkerCallback::AsyncWorkerCallback(const Napi::Function &cb, const ExecuteFunc &execute, const ConvertFunc &convert, const Napi::Buffer<uint8_t> &napiBuf0, const Napi::Buffer<uint8_t> &napiBuf1)
        : Napi::AsyncWorker(cb),
          execute_(execute),
          convert_(convert),
          buf0_(napiBuf0.Data()),
          buf1_(napiBuf1.Data()),
          buf0ref_(Napi::Reference<Napi::Buffer<uint8_t>>::New(napiBuf0, 1)),
          buf1ref_(Napi::Reference<Napi::Buffer<uint8_t>>::New(napiBuf1, 1)) {
}

void AsyncWorkerCallback::Execute() {
    this->execute_(this->buf0_, this->buf1_, this->callbackData_);
}

void AsyncWorkerCallback::OnOK() {
    Callback().Call({Env().Null(), this->convert_(Env(), this->callbackData_)});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////