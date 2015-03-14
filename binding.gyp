{
  "targets": [
    {
      "target_name": "addon",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "System/Library/Frameworks/ApplicationServices.framework/Headers",
       ],
       "link_settings": {
         "libraries": [
           "-framework ApplicationServices",
         ]
       },
      "sources": [ "addon.cc" ]
    }
  ]
}
