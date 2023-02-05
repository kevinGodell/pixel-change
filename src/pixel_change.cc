#include "object.h"
#include "engine.h"
#include <napi.h>
#include <string>

#if defined NAPI_DEBUG && NAPI_DEBUG == 1
#include <iostream>
using std::cout;
using std::endl;
#endif

Napi::Value CreateObject(const Napi::CallbackInfo &info) {
    const Napi::Env env = info.Env();
    if (info.Length() < 1 || info[0].IsEmpty() || !info[0].IsObject()) {
        throw Napi::Error::New(env, "A configuration object was expected { width, height, depth }");
    }
    const Napi::Object configObj = info[0].As<Napi::Object>();
    if (!configObj.HasOwnProperty("width") || !configObj.Get("width").IsNumber() || configObj.Get("width").As<Napi::Number>().Int32Value() < 1) {
        throw Napi::Error::New(configObj.Env(), "Width must be an integer greater than 0");
    }
    if (!configObj.HasOwnProperty("height") || !configObj.Get("height").IsNumber() || configObj.Get("height").As<Napi::Number>().Int32Value() < 1) {
        throw Napi::Error::New(configObj.Env(), "Height must be an integer greater than 0");
    }
    if (!configObj.HasOwnProperty("depth") || !configObj.Get("depth").IsNumber() || (configObj.Get("depth").As<Napi::Number>().Int32Value() != 1 && configObj.Get("depth").As<Napi::Number>().Int32Value() != 3 && configObj.Get("depth").As<Napi::Number>().Int32Value() != 4)) {
        throw Napi::Error::New(configObj.Env(), "Depth must be an integer set to 1, 3, or 4");
    }
    if (configObj.HasOwnProperty("draw") && !configObj.Get("draw").IsBoolean()) {
        throw Napi::Error::New(configObj.Env(), "Draw must be a boolean");
    }
    if (configObj.HasOwnProperty("response") && !configObj.Get("response").IsString()) {
        throw Napi::Error::New(configObj.Env(), "Response must be a string set to percent, bounds, or blobs");
    }

#if defined NAPI_DEBUG && NAPI_DEBUG == 1
    cout << "c++ version : " << __cplusplus << endl;
    // show system size values for types being used
    cout << "size of bool : " << sizeof(bool) << endl;
    cout << "size of std::string : " << sizeof(std::string) << endl;
    cout << "size of int32_t : " << sizeof(int32_t) << endl;
    cout << "size of uint32_t : " << sizeof(uint32_t) << endl;
    cout << "size of float : " << sizeof(float) << endl;
    cout << "size of std::vector<bool> : " << sizeof(std::vector<bool>) << endl;
    cout << "size of std::vector<uint8_t> : " << sizeof(std::vector<uint8_t>) << endl;
    cout << "size of std::vector<Result> : " << sizeof(std::vector<Result>) << endl;
    cout << "size of Config struct : " << sizeof(Config) << endl;
    cout << "size of All struct : " << sizeof(All) << endl;
    cout << "size of Bounds struct : " << sizeof(Bounds) << endl;
    cout << "size of Region struct : " << sizeof(Region) << endl;
    cout << "size of Blob struct : " << sizeof(Blob) << endl;
    cout << "size of Result struct : " << sizeof(Result) << endl;
    cout << "size of Pixels struct : " << sizeof(Pixels) << endl;
    cout << "size of CallbackData struct : " << sizeof(CallbackData) << endl;

    if (configObj.HasOwnProperty("depth")) cout << "depth : " << configObj.Get("depth").As<Napi::Number>().Uint32Value() << endl;
    if (configObj.HasOwnProperty("width")) cout << "width : " << configObj.Get("width").As<Napi::Number>().Uint32Value() << std::endl;
    if (configObj.HasOwnProperty("height")) std::cout << "height : " << configObj.Get("height").As<Napi::Number>().Uint32Value() << std::endl;
    if (configObj.HasOwnProperty("response")) std::cout << "response : " << configObj.Get("response").As<Napi::String>().Utf8Value() << std::endl;
    if (configObj.HasOwnProperty("draw")) std::cout << "draw : " << configObj.Get("draw").As<Napi::Boolean>().Value() << std::endl;
    if (configObj.HasOwnProperty("difference")) std::cout << "difference : " << configObj.Get("difference").As<Napi::Number>().Uint32Value() << std::endl;
    if (configObj.HasOwnProperty("percent")) std::cout << "percent : " << configObj.Get("percent").As<Napi::Number>().FloatValue() << std::endl;
    if (configObj.HasOwnProperty("regions")) {
        const Napi::Array regionsJs = configObj.Get("regions").As<Napi::Array>();
        //uint32_t regionsLength = regionsJs.Length();
        cout << "regions length : " << regionsJs.Length() << endl;
        for (uint32_t r = 0; r < regionsJs.Length(); ++r) {
            Napi::Object obj = regionsJs.Get(r).As<Napi::Object>();
            const std::string name = obj.HasOwnProperty("name") ? obj.Get("name").As<Napi::String>() : std::string();
            const uint32_t difference = obj.HasOwnProperty("difference") ? obj.Get("difference").As<Napi::Number>().Uint32Value() : 0;
            const float percent = obj.HasOwnProperty("percent") ? obj.Get("percent").As<Napi::Number>().FloatValue() : 0;
            const uint32_t bitsetCount = obj.HasOwnProperty("bitsetCount") ? obj.Get("bitsetCount").As<Napi::Number>().Uint32Value() : 0;
            const uint32_t bitsetLength = obj.HasOwnProperty("bitset") ? static_cast<uint32_t>(obj.Get("bitset").As<Napi::Buffer<bool>>().Length()) : 0;
            const uint32_t minX = obj.HasOwnProperty("minX") ? obj.Get("minX").As<Napi::Number>().Uint32Value() : 0;
            const uint32_t maxX = obj.HasOwnProperty("maxX") ? obj.Get("maxX").As<Napi::Number>().Uint32Value() : 0;
            const uint32_t minY = obj.HasOwnProperty("minY") ? obj.Get("minY").As<Napi::Number>().Uint32Value() : 0;
            const uint32_t maxY = obj.HasOwnProperty("maxY") ? obj.Get("maxY").As<Napi::Number>().Uint32Value() : 0;
            cout << name << " - " << difference << " - " << minX << " - " << maxX << " - " << minY << " - " << maxY << " - " << percent << " - " << bitsetCount << " - " << bitsetLength << endl;
        }
    }
#endif
    return PixelChange::NewInstance(env, configObj);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports = Napi::Function::New(env, CreateObject, "CreateObject");
    exports.Set("CreateObject", Napi::Function::New(env, CreateObject));

    Napi::Object package = Napi::Object::New(env);
    package.Set("name", PACKAGE_NAME);
    package.Set("version", PACKAGE_VERSION);
    exports.Set("package", package);

    Napi::Object current = Napi::Object::New(env);
    current.Set("napi", Napi::VersionManagement::GetNapiVersion(env));
    auto node = Napi::VersionManagement::GetNodeVersion(env);
    current.Set("node", std::to_string(node->major) + "." + std::to_string(node->minor) + "." + std::to_string(node->patch));
    exports.Set("current", current);

    Napi::Object build = Napi::Object::New(env);
    //build.Set(NAME, VERSION);
    build.Set("cplusplus", __cplusplus);
    build.Set("napi", NAPI_VERSION);
    build.Set("node", NODE_VERSION);
    build.Set("date", __DATE__);
    build.Set("time", __TIME__);
    exports.Set("build", build);

    PixelChange::Init(env);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)