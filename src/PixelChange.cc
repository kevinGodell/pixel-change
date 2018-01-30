#include <napi.h>
#include <cmath>

uint8_t Abs(uint8_t x) {
    return x < 0 ? -x : x;
}

uint8_t Diff(uint8_t p1, uint8_t p2, uint8_t diff) {
    return Abs(p1 - p2) >= diff;
}

uint8_t Diff(uint8_t r1, uint8_t r2, uint8_t g1, uint8_t g2, uint8_t b1, uint8_t b2, uint8_t diff) {
    return Abs((r1 - r2 + g1 - g2 + b1 - b2)/3) >= diff;
}

Napi::Number CompareGrayPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, difference, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint32_t difference = info[2].As<Napi::Number>().Uint32Value();
    if (difference > 255 || difference < 1) {
        Napi::TypeError::New(env, "Difference value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = difference;
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh) {
        Napi::TypeError::New(env, "Pixel buffers must be the same length and equal to width * height").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    uint32_t diffs = 0;
    for (uint32_t y = 0, i = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, i++) {
            if (Diff(buf0[i], buf1[i], diff)) diffs++;
        }
    }
    Napi::Number num = Napi::Number::New(env, 100 * diffs / wxh);
    return num;
}

Napi::Value CompareRgbPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, difference, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint32_t difference = info[2].As<Napi::Number>().Uint32Value();
    if (difference > 255 || difference < 1) {
        Napi::TypeError::New(env, "Difference value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = difference;
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh * 3) {
        Napi::TypeError::New(env, "Pixel buffers must be the same length and equal to width * height * 3").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    uint32_t diffs = 0;
    for (uint32_t y = 0, i = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, i+=3) {
            if (Diff(buf0[i], buf1[i], buf0[i+1], buf1[i+1], buf0[i+2], buf1[i+2], diff)) diffs++;
        }
    }
    Napi::Number num = Napi::Number::New(env, 100 * diffs / wxh);
    return num;
}

Napi::Number CompareRgbaPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, diff, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint32_t difference = info[2].As<Napi::Number>().Uint32Value();
    if (difference > 255 || difference < 1) {
        Napi::TypeError::New(env, "Difference value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = difference;
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh * 4) {
        Napi::TypeError::New(env, "Pixels buffers must be the same length and equal to width * height * 4").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    uint32_t diffs = 0;
    for (uint32_t y = 0, i = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, i+=4) {
            if (Diff(buf0[i], buf1[i], buf0[i+1], buf1[i+1], buf0[i+2], buf1[i+2], diff)) diffs++;
        }
    }
    Napi::Number num = Napi::Number::New(env, 100 * diffs / wxh);
    return num;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "compareGrayPixels"), Napi::Function::New(env, CompareGrayPixels));
    exports.Set(Napi::String::New(env, "compareRgbPixels"), Napi::Function::New(env, CompareRgbPixels));
    exports.Set(Napi::String::New(env, "compareRgbaPixels"), Napi::Function::New(env, CompareRgbaPixels));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)