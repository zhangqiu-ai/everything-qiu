{
  "targets": [
    {
      "target_name": "everything",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "src/native/everything.cpp" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "src/native/include"
      ],
      "libraries": [ "<(module_root_dir)/src/native/lib/Everything64.lib" ],
      "defines": [ 
        "NAPI_DISABLE_CPP_EXCEPTIONS",
        "UNICODE",
        "_UNICODE"
      ],
      "copies": [
        {
          "destination": "<(module_root_dir)/build/Release",
          "files": [ "<(module_root_dir)/src/native/lib/Everything64.dll" ]
        }
      ]
    }
  ]
}