#ifndef SRC_PROMISE_H_
#define SRC_PROMISE_H_

#include "engine.h"
#include "napi.h"
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AsyncWorkerPromise : public Napi::AsyncWorker {
public:
    AsyncWorkerPromise(const Napi::Env &env, const ExecuteFunc &execute, const ConvertFunc &convert, const Napi::Buffer<uint8_t> &napiBuf0, const Napi::Buffer<uint8_t> &napiBuf1);

    void Execute() override;

    void OnOK() override;

    Napi::Promise getPromise() const;

private:
    // in
    const ExecuteFunc execute_;
    const ConvertFunc convert_;
    const uint8_t *buf0_;
    const uint8_t *buf1_;
    const Napi::Reference<Napi::Buffer<uint8_t>> buf0ref_;
    const Napi::Reference<Napi::Buffer<uint8_t>> buf1ref_;

    // out
    CallbackData callbackData_;
    const Napi::Promise::Deferred deferred_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif