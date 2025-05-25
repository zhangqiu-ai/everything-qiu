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
    
    // 处理选项
    if (info.Length() > 1 && info[1].IsObject()) {
        Napi::Object options = info[1].As<Napi::Object>();
        
        if (options.Has("matchPath")) {
            Everything_SetMatchPath(options.Get("matchPath").ToBoolean());
        }
        
        if (options.Has("matchCase")) {
            Everything_SetMatchCase(options.Get("matchCase").ToBoolean());
        }
        
        if (options.Has("matchWholeWord")) {
            Everything_SetMatchWholeWord(options.Get("matchWholeWord").ToBoolean());
        }
        
        if (options.Has("regex")) {
            Everything_SetRegex(options.Get("regex").ToBoolean());
        }
        
        if (options.Has("maxResults")) {
            Everything_SetMax(options.Get("maxResults").ToNumber().Uint32Value());
        }
        
        if (options.Has("sort")) {
            Everything_SetSort(options.Get("sort").ToNumber().Uint32Value());
        }
    }
    
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
                
        // 附加信息
        result.Set("isFolder", Everything_IsFolderResult(i));
        
        LARGE_INTEGER size;
        if (Everything_GetResultSize(i, &size)) {
            result.Set("size", Napi::Number::New(env, static_cast<double>(size.QuadPart)));
        }
        
        FILETIME created, modified;
        if (Everything_GetResultDateCreated(i, &created)) {
            // 转换 FILETIME 到 JavaScript Date
            ULARGE_INTEGER uli;
            uli.LowPart = created.dwLowDateTime;
            uli.HighPart = created.dwHighDateTime;
            double ms = static_cast<double>(uli.QuadPart) / 10000.0 - 11644473600000.0;
            result.Set("created", Napi::Date::New(env, ms));
        }
        
        if (Everything_GetResultDateModified(i, &modified)) {
            ULARGE_INTEGER uli;
            uli.LowPart = modified.dwLowDateTime;
            uli.HighPart = modified.dwHighDateTime;
            double ms = static_cast<double>(uli.QuadPart) / 10000.0 - 11644473600000.0;
            result.Set("modified", Napi::Date::New(env, ms));
        }
        
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