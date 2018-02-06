#include <napi.h>
#include <cmath>
#include <algorithm>

Napi::Number CompareGrayPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, diff, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    if (info[2].As<Napi::Number>().Uint32Value() > 255 || info[2].As<Napi::Number>().Uint32Value() < 1) {
        Napi::TypeError::New(env, "Diff value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = info[2].As<Napi::Number>().Uint32Value();
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
            if (std::abs(buf0[i] - buf1[i]) >= diff) diffs++;
        }
    }
    return Napi::Number::New(env, 100 * diffs / wxh);
}

Napi::Number CompareRgbPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, diff, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    if (info[2].As<Napi::Number>().Uint32Value() > 255 || info[2].As<Napi::Number>().Uint32Value() < 1) {
        Napi::TypeError::New(env, "Diff value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = info[2].As<Napi::Number>().Uint32Value();
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
            if(std::abs(buf0[i] + buf0[i+1] + buf0[i+2] - buf1[i] - buf1[i+1] - buf1[i+2])/3 >= diff) diffs++;
        }
    }
    return Napi::Number::New(env, 100 * diffs / wxh);
}

Napi::Number CompareRgbaPixels(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, diff, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    if (info[2].As<Napi::Number>().Uint32Value() > 255 || info[2].As<Napi::Number>().Uint32Value() < 1) {
        Napi::TypeError::New(env, "Diff value must range from 1 to 255").ThrowAsJavaScriptException();
        return Napi::Number::New(env, NAN);
    }
    const uint8_t diff = info[2].As<Napi::Number>().Uint32Value();
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
            if(std::abs(buf0[i] + buf0[i+1] + buf0[i+2] - buf1[i] - buf1[i+1] - buf1[i+2])/3 >= diff) diffs++;
        }
    }
    return Napi::Number::New(env, 100 * diffs / wxh);
}

////////////////////////////////////////////////////////////////////////

Napi::Array CompareGrayRegions(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsArray() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, regions, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    const Napi::Array regionsArr = info[2].As<Napi::Array>();
    const Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    const Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh) {
        Napi::TypeError::New(env, "Pixels buffers must be the same length and equal to width * height").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    uint8_t minDiff = 255;
    const uint32_t regionsLen = regionsArr.Length();
    std::vector<std::tuple<std::string, uint8_t, uint32_t, Napi::Buffer<uint8_t>, uint32_t>> regionsVec(regionsLen);
    for (uint32_t i = 0; i < regionsLen; i++) {
        if (
            !regionsArr.Get(i).IsObject() ||
            regionsArr.Get(i).As<Napi::Object>().GetPropertyNames().Length() != 4 ||
            !regionsArr.Get(i).As<Napi::Object>().Has("name") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("diff") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("count") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("bitset") ||
            !regionsArr.Get(i).As<Napi::Object>().Get("name").IsString() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("diff").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("count").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("bitset").IsBuffer()
        )
        {
            Napi::TypeError::New(env, "Regions must contain 4 properties: name, diff, count, and bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const std::string name = regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>();
        if (regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() < 1 || regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() > 255) {
            Napi::TypeError::New(env, "Diff value must range from 1 to 255.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const uint8_t diff = regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value();
        minDiff = std::min(minDiff, diff);
        const uint32_t count = regionsArr.Get(i).As<Napi::Object>().Get("count").As<Napi::Number>().Uint32Value();
        if (!(count < wxh && count > 0)) {
            Napi::TypeError::New(env, "Count should indicate the number of 1's in bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const Napi::Buffer<uint8_t> bitset = regionsArr.Get(i).As<Napi::Object>().Get("bitset").As<Napi::Buffer<uint8_t>>();
        if (bitset.Length() != wxh) {
            Napi::TypeError::New(env, "Pixel bitset must be the same length as width * height.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        regionsVec[i] = std::make_tuple(regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>(), diff, count, bitset, 0);
    }
    for (uint32_t y = 0, p = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, p++) {
            const uint8_t diff = std::abs(buf0[p] - buf1[p]);
            if (minDiff > diff) continue;
            for (uint32_t i = 0; i < regionsLen; i++) {
                if (!std::get<3>(regionsVec[i])[p] || diff < std::get<1>(regionsVec[i])) continue;
                std::get<4>(regionsVec[i])++;
            }
        }
    }
    Napi::Array results = Napi::Array::New(env, regionsLen);
    for(uint32_t i = 0; i < regionsLen; i++) {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("name", std::get<0>(regionsVec[i]));
        obj.Set("percent", 100 * std::get<4>(regionsVec[i]) / std::get<2>(regionsVec[i]));
        results[i] = obj;
    }
    return results;
}

Napi::Array CompareRgbRegions(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsArray() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, regions, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    const Napi::Array regionsArr = info[2].As<Napi::Array>();
    const Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    const Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh * 3) {
        Napi::TypeError::New(env, "Pixels buffers must be the same length and equal to width * height * 3").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    uint8_t minDiff = 255;
    const uint32_t regionsLen = regionsArr.Length();
    std::vector<std::tuple<std::string, uint8_t, uint32_t, Napi::Buffer<uint8_t>, uint32_t>> regionsVec(regionsLen);
    for (uint32_t i = 0; i < regionsLen; i++) {
        if (
            !regionsArr.Get(i).IsObject() ||
            regionsArr.Get(i).As<Napi::Object>().GetPropertyNames().Length() != 4 ||
            !regionsArr.Get(i).As<Napi::Object>().Has("name") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("diff") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("count") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("bitset") ||
            !regionsArr.Get(i).As<Napi::Object>().Get("name").IsString() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("diff").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("count").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("bitset").IsBuffer()
        )
        {
            Napi::TypeError::New(env, "Regions must contain 4 properties: name, diff, count, and bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const std::string name = regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>();
        if (regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() < 1 || regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() > 255) {
            Napi::TypeError::New(env, "Diff value must range from 1 to 255.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const uint8_t diff = regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value();
        minDiff = std::min(minDiff, diff);
        const uint32_t count = regionsArr.Get(i).As<Napi::Object>().Get("count").As<Napi::Number>().Uint32Value();
        if (!(count < wxh && count > 0)) {
            Napi::TypeError::New(env, "Count should indicate the number of 1's in bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const Napi::Buffer<uint8_t> bitset = regionsArr.Get(i).As<Napi::Object>().Get("bitset").As<Napi::Buffer<uint8_t>>();
        if (bitset.Length() != wxh) {
            Napi::TypeError::New(env, "Pixel bitset must be the same length as width * height.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        regionsVec[i] = std::make_tuple(regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>(), diff, count, bitset, 0);
    }
    for (uint32_t y = 0, p = 0, i = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, p++, i+=3) {
            const uint8_t diff = std::abs(buf0[i] + buf0[i+1] + buf0[i+2] - buf1[i] - buf1[i+1] - buf1[i+2])/3;
            if (minDiff > diff) continue;
            for (uint32_t i = 0; i < regionsLen; i++) {
                if (!std::get<3>(regionsVec[i])[p] || diff < std::get<1>(regionsVec[i])) continue;
                std::get<4>(regionsVec[i])++;
            }
        }
    }
    Napi::Array results = Napi::Array::New(env, regionsLen);
    for(uint32_t i = 0; i < regionsLen; i++) {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("name", std::get<0>(regionsVec[i]));
        obj.Set("percent", 100 * std::get<4>(regionsVec[i]) / std::get<2>(regionsVec[i]));
        results[i] = obj;
    }
    return results;
}

Napi::Array CompareRgbaRegions(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 5 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsArray() || !info[3].IsBuffer() || !info[4].IsBuffer() ) {
        Napi::TypeError::New(env, "Must be 5 args passed as width, height, regions, buffer0, buffer1").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    const uint32_t width = info[0].As<Napi::Number>().Uint32Value();
    const uint32_t height = info[1].As<Napi::Number>().Uint32Value();
    const Napi::Array regionsArr = info[2].As<Napi::Array>();
    const Napi::Buffer<uint8_t> buf0 = info[3].As<Napi::Buffer<uint8_t>>();
    const Napi::Buffer<uint8_t> buf1 = info[4].As<Napi::Buffer<uint8_t>>();
    const uint32_t len0 = buf0.Length();
    const uint32_t len1 = buf1.Length();
    const uint32_t wxh = width * height;
    if (len0 != len1 || len0 != wxh * 4) {
        Napi::TypeError::New(env, "Pixels buffers must be the same length and equal to width * height * 4").ThrowAsJavaScriptException();
        return Napi::Array::New(env);
    }
    uint8_t minDiff = 255;
    const uint32_t regionsLen = regionsArr.Length();
    std::vector<std::tuple<std::string, uint8_t, uint32_t, Napi::Buffer<uint8_t>, uint32_t>> regionsVec(regionsLen);
    for (uint32_t i = 0; i < regionsLen; i++) {
        if (
            !regionsArr.Get(i).IsObject() ||
            regionsArr.Get(i).As<Napi::Object>().GetPropertyNames().Length() != 4 ||
            !regionsArr.Get(i).As<Napi::Object>().Has("name") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("diff") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("count") ||
            !regionsArr.Get(i).As<Napi::Object>().Has("bitset") ||
            !regionsArr.Get(i).As<Napi::Object>().Get("name").IsString() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("diff").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("count").IsNumber() ||
            !regionsArr.Get(i).As<Napi::Object>().Get("bitset").IsBuffer()
        )
        {
            Napi::TypeError::New(env, "Regions must contain 4 properties: name, diff, count, and bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const std::string name = regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>();
        if (regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() < 1 || regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value() > 255) {
            Napi::TypeError::New(env, "Diff value must range from 1 to 255.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const uint8_t diff = regionsArr.Get(i).As<Napi::Object>().Get("diff").As<Napi::Number>().Uint32Value();
        minDiff = std::min(minDiff, diff);
        const uint32_t count = regionsArr.Get(i).As<Napi::Object>().Get("count").As<Napi::Number>().Uint32Value();
        if (!(count < wxh && count > 0)) {
            Napi::TypeError::New(env, "Count should indicate the number of 1's in bitset.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        const Napi::Buffer<uint8_t> bitset = regionsArr.Get(i).As<Napi::Object>().Get("bitset").As<Napi::Buffer<uint8_t>>();
        if (bitset.Length() != wxh) {
            Napi::TypeError::New(env, "Pixel bitset must be the same length as width * height.").ThrowAsJavaScriptException();
            return Napi::Array::New(env);
        }
        regionsVec[i] = std::make_tuple(regionsArr.Get(i).As<Napi::Object>().Get("name").As<Napi::String>(), diff, count, bitset, 0);
    }
    for (uint32_t y = 0, p = 0, i = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++, p++, i+=4) {
            const uint8_t diff = std::abs(buf0[i] + buf0[i+1] + buf0[i+2] - buf1[i] - buf1[i+1] - buf1[i+2])/3;
            if (minDiff > diff) continue;
            for (uint32_t i = 0; i < regionsLen; i++) {
                if (!std::get<3>(regionsVec[i])[p] || diff < std::get<1>(regionsVec[i])) continue;
                std::get<4>(regionsVec[i])++;
            }
        }
    }
    Napi::Array results = Napi::Array::New(env, regionsLen);
    for(uint32_t i = 0; i < regionsLen; i++) {
        Napi::Object obj = Napi::Object::New(env);
        obj.Set("name", std::get<0>(regionsVec[i]));
        obj.Set("percent", 100 * std::get<4>(regionsVec[i]) / std::get<2>(regionsVec[i]));
        results[i] = obj;
    }
    return results;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "compareGrayPixels"), Napi::Function::New(env, CompareGrayPixels));
    exports.Set(Napi::String::New(env, "compareRgbPixels"), Napi::Function::New(env, CompareRgbPixels));
    exports.Set(Napi::String::New(env, "compareRgbaPixels"), Napi::Function::New(env, CompareRgbaPixels));
    exports.Set(Napi::String::New(env, "compareGrayRegions"), Napi::Function::New(env, CompareGrayRegions));
    exports.Set(Napi::String::New(env, "compareRgbRegions"), Napi::Function::New(env, CompareRgbRegions));
    exports.Set(Napi::String::New(env, "compareRgbaRegions"), Napi::Function::New(env, CompareRgbaRegions));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)