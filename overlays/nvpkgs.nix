let
  jsonText = builtins.readFile ./.nvfetcher/generated.json;
  jsonData = builtins.fromJSON jsonText;
in
  jsonData
