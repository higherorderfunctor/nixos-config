let
  jsonText = builtins.readFile ./.nvfetcher/generated.json;
  jsonData = builtins.fromJSON jsonText;
in
  jsonData
# TODO:
# ERROR][2024-03-14 01:30:12] .../vim/lsp/rpc.lua:789  "rpc" "/etc/profiles/per-user/caubut/bin/nixd"  "stderr"  "/etc/profiles/per-user/caubut/bin/nixd: error while loading shared libraries: libbc.so: cannot open shared object file: No such file or directory\n"
# [ERROR][2024-03-14 01:39:34] .../vim/lsp/rpc.lua:789  "rpc" "/etc/profiles/per-user/caubut/bin/nixd"  "stderr"  "/etc/profiles/per-user/caubut/bin/nixd: error while loading shared libraries: libbc.so: cannot open shared object file: No such file or directory\n"
# [ERROR][2024-03-14 01:40:06] .../vim/lsp/rpc.lua:789  "rpc" "/etc/profiles/per-user/caubut/bin/nixd"  "stderr"  "/etc/profiles/per-user/caubut/bin/nixd: error while loading shared libraries: libbc.so: cannot open shared object file: No such file or directory\n"
# [START][2024-03-14 01:40:13] LSP logging initiated
# [ERROR][2024-03-14 01:40:13] .../vim/lsp/rpc.lua:789  "rpc" "/etc/profiles/per-user/caubut/bin/nixd"  "stderr"  "/etc/profiles/per-user/caubut/bin/nixd: error while loading shared libraries: libbc.so: cannot open shared object file: No such file or directory\n"
# [WARN][2024-03-14 01:40:14] ...lsp/handlers.lua:135 "The language server copilot triggers a registerCapability handler for workspace/didChangeWorkspaceFolders despite dynamicRegistration set to false. Report upstream, this warning is harmless"
# [START][2024-03-14 01:40:30] LSP logging initiated
# [ERROR][2024-03-14 01:40:30] .../vim/lsp/rpc.lua:789  "rpc" "/etc/profiles/per-user/caubut/bin/nixd"  "stderr"  "/etc/profiles/per-user/caubut/bin/nixd: error while loading shared libraries: libbc.so: cannot open shared object file: No such file or directory\n"
# [WARN][2024-03-14 01:40:30] ...lsp/handlers.lua:135 "The language server copilot triggers a registerCapability handler for workspace/didChangeWorkspaceFolders despite dynamicRegistration set to false. Report upstream, this warning is harmless"
# ~
# ~
