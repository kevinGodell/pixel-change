#ifndef SRC_CALLBACK_H_
#define SRC_CALLBACK_H_

#include "engine.h"
#include <napi.h>
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AsyncWorkerCallback : public Napi::AsyncWorker {
public:
    AsyncWorkerCallback(const Napi::Function &cb, const ExecuteFunc &execute, const ConvertFunc &convert, const Napi::Buffer<uint8_t> &napiBuf0, const Napi::Buffer<uint8_t> &napiBuf1);

    void Execute() override;

    void OnOK() override;

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
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif