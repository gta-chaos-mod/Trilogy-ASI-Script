# Basic Style-Guide
- Effects are headerless, meaning all you need is a `.cpp` file in the correct subfolder
- Includes are grouped and sorted according to their categories, which means these rules need to be followed:
    - Includes from the Chaos Mod (`util/` and such) are to be written with quotation marks (`""`) but still use their full path, even if the corresponding file is in the same folder
    - Includes from system headers are to be written with angled brackets (`<>`)
    - Includes from plugin-sdk are to be written with angled brackets (`<>`)
    - Uses of namespaces should be done after the plugin-sdk includes