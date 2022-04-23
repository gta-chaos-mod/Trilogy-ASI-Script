# GTA Trilogy Chaos Mod: Reborn
Welcome to the official **GTA Trilogy Chaos Mod: Reborn** repository!

This repository, together with this README, is still very much **WIP**.

# Why "Reborn"?
The mod had some issues and was my first C++ project, thus I did not have a lot of experience on how to best do a lot of things right.

The **"Reborn"** project aims to fix this by pretty much **rewriting the majority of the mod from scratch.** (except code for drawing effects and a few other things)

It will also be easier for interested developers to contribute to the project be it with their own effects or with help on the general codebase.

## Basic Style-Guide
- Effects are headerless, meaning all you need is a `.cpp` file in the correct subfolder
- Includes should be done with angled brackets (`<>`) except for the corresponding file header (ex. `GameUtil.cpp` and `GameUtil.h`)
- Includes are to be grouped and sorted by their category (They should get sorted by clang-format)
    - If a header is required for a new utility class it should be sorted at the top with quotation marks (`""`)
    - Includes from the Chaos Mod (`util/` and such) should be sorted at the top or, if present, right after the file header
    - Includes from system headers should be sorted after the Chaos Mod includes
    - Includes from plugin-sdk should be sorted after the system includes
    - Uses of namespaces should be done after the plugin-sdk includes