#include "results.h"
#include "engine.h"
#include "napi.h"
#include <cstdint>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// create js object and push to js array
Napi::Array
PercentCallback(const Napi::Env &env, CallbackData &callbackData) {
    //const Napi::HandleScope scope(env);
    Napi::Array resultsJs = Napi::Array::New(env);
    const std::vector<Result> &results = callbackData.results;
    if (!results.empty()) {
        uint32_t j = 0;
        for (const auto &result : results) {
            if (!result.flagged) continue;
            SetPercentResult(env, result, resultsJs, j++);
        }
        /* todo implement pixels draw
        Pixels &pixels = callbackData.pixels;
        if (pixels.ptr) {
            uint8_t *ptr = pixels.ptr.release();
            const Napi::Buffer<uint8_t> pixelsJs = Napi::Buffer<uint8_t>::New(env, ptr, pixels.size, DeleteExternalData);
            cb.Call({env.Null(), resultsJs, pixelsJs});
            return;
        }*/
    }
    return resultsJs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// create js object and push to js array
Napi::Array
BoundsCallback(const Napi::Env &env, CallbackData &callbackData) {
    //const Napi::HandleScope scope(env);
    Napi::Array resultsJs = Napi::Array::New(env);
    const std::vector<Result> &results = callbackData.results;
    if (!results.empty()) {
        uint32_t j = 0;
        for (const auto &result : results) {
            if (!result.flagged) continue;
            SetBoundsResult(env, result, resultsJs, j++);
        }
        Pixels &pixels = callbackData.pixels;
        if (pixels.ptr) {
            uint8_t *ptr = pixels.ptr.release();
            const Napi::Buffer<uint8_t> pixelsJs = Napi::Buffer<uint8_t>::New(env, ptr, pixels.size, DeleteExternalData);
            resultsJs.Set("pixels", pixelsJs);
        }
    }
    return resultsJs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// create js object and push to js array
Napi::Array
BlobsCallback(const Napi::Env &env, CallbackData &callbackData) {
    //const Napi::HandleScope scope(env);
    Napi::Array resultsJs = Napi::Array::New(env);
    const std::vector<Result> &results = callbackData.results;
    if (!results.empty()) {
        uint32_t j = 0;
        for (const auto &result : results) {
            if (!result.flagged) continue;
            SetBlobsResult(env, result, resultsJs, j++);
        }
        Pixels &pixels = callbackData.pixels;
        if (pixels.ptr) {
            uint8_t *ptr = pixels.ptr.release();
            const Napi::Buffer<uint8_t> pixelsJs = Napi::Buffer<uint8_t>::New(env, ptr, pixels.size, DeleteExternalData);
            resultsJs.Set("pixels", pixelsJs);
        }
    }
    return resultsJs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// free memory from heap allocated array used as Buffer data
void
DeleteExternalData(Napi::Env /*&env*/, const uint8_t *finalizeData) {
    delete[] finalizeData;
}