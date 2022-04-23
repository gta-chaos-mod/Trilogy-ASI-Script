# GTA Trilogy Chaos Mod: Reborn
Welcome to the official **GTA Trilogy Chaos Mod: Reborn** repository!

This repository, together with this README, is still very much **WIP**.

# Why "Reborn"?
The mod had some issues and was my first C++ project, thus I did not have a lot of experience on how to best do a lot of things right.

The **"Reborn"** project aims to fix this by pretty much **rewriting the majority of the mod from scratch.** (except code for drawing effects and a few other things)

It will also be easier for interested developers to contribute to the project be it with their own effects or with help on the general codebase.

## Basic Style-Guide
- Effects are headerless, meaning all you need is a `.cpp` file in the correct subfolder
- Includes are grouped and sorted according to their categories, which means these rules need to be followed:
    - Includes from the Chaos Mod (`util/` and such) are to be written with quotation marks (`""`) but still use their full path, even if the corresponding file is in the same folder
    - Includes from system headers are to be written with angled brackets (`<>`)
    - Includes from plugin-sdk are to be written with angled brackets (`<>`)
    - Uses of namespaces should be done after the plugin-sdk includes