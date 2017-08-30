{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "./pbcwrapper",
        "./pbc-0.5.14"
      ],
      "target_name": "addon",
      "sources": [
        "main.cc",
        "./pbcwrapper/Zr.cc",
        "./pbcwrapper/G.cc",
        "./pbcwrapper/G1.cc",
        "./pbcwrapper/G2.cc",
        "./pbcwrapper/GT.cc",
        "./pbcwrapper/Pairing.cc",
        "./pbcwrapper/PPPairing.cc"
      ],
      "libraries": [ "-Wl,-rpath,./pbcwrapper/libPBC.a", "-lpbc", "-lgmp" ],
      "cflags": [ "-fexceptions" ],
      "cflags_cc": [ "-fexceptions" ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "cflags_cc+": [
          "-std=c++0x"
        ],
      "conditions": [
        ["OS==\"mac\"", {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ]
    }
  ]
}
