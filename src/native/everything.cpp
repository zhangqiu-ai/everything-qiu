#include <napi.h>
#include "Everything.h"

Napi::Value Search(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // 检查 Everything 服务是否运行
    if (!Everything_IsDBLoaded()) {
        Napi::Error::New(env, "Everything database is not loaded").ThrowAsJavaScriptException();
        return env.Null();
    }
    
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
    
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong argument type")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
    
    std::u16string searchStr = info[0].As<Napi::String>().Utf16Value();
    
    // 初始化 Everything
    Everything_SetSearchW(reinterpret_cast<LPCWSTR>(searchStr.c_str()));
    
    // 执行搜索并检查结果
    if (!Everything_Query(TRUE)) {
        DWORD error = Everything_GetLastError();
        std::string errorMsg = "Everything search failed with error: " + std::to_string(error);
        Napi::Error::New(env, errorMsg).ThrowAsJavaScriptException();
        return env.Null();
    }
    
    // 获取结果
    DWORD resultCount = Everything_GetNumResults();
    
    // 打印调试信息
    printf("Search query: %ls\n", reinterpret_cast<LPCWSTR>(searchStr.c_str()));
    printf("Result count: %lu\n", resultCount);
    
    Napi::Array results = Napi::Array::New(env, resultCount);
    
    for (DWORD i = 0; i < resultCount; i++) {
        Napi::Object result = Napi::Object::New(env);
        
        LPCWSTR fileName = Everything_GetResultFileNameW(i);
        LPCWSTR filePath = Everything_GetResultPathW(i);
        
        // 打印调试信息
        printf("File %lu: %ls\\%ls\n", i, filePath, fileName);
        
        result.Set("filename", 
            Napi::String::New(env, 
                reinterpret_cast<const char16_t*>(fileName), 
                wcslen(fileName)));
                
        result.Set("path", 
            Napi::String::New(env, 
                reinterpret_cast<const char16_t*>(filePath), 
                wcslen(filePath)));
                
        results[i] = result;
    }
    
    return results;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // 初始化 Everything
    Everything_SetMax(1000); // 设置最大结果数
    
    exports.Set(Napi::String::New(env, "search"),
                Napi::Function::New(env, Search));
    return exports;
}

NODE_API_MODULE(everything, Init)