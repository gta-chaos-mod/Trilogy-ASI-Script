# GTA Chaos Mod
Welcome to the official GTA Chaos Mod repository!

This repository, together with this README, is still very much WIP.

## What does this mod do?
Similar to the old [Vice City Chaos% mod](https://github.com/Lighnat0r-pers/gta-vc-chaos) by [Lightnat0r](https://github.com/Lighnat0r), it activates effects in the corresponding game every X seconds / minutes (cooldown can be defined in the GUI tool).

## Which GTA games does it support?
Right now it only supports **San Andreas**, though due to utilizing the [plugin-sdk](https://github.com/DK22Pac/plugin-sdk) it *should* be possible to also support **Vice City** and **III** in the future.

## Which versions of the games does it support?
**GTA San Andreas**: v1.0 US (EU *might* work, but I don't have an EU copy to test it with...)

## How do I downgrade my game to the required version?
**GTA San Andreas**: https://dl1.rockstarnexus.com/gta/sa/GTASA_12-9-14_Steam_to_V1_DG.exe

## What ASI Loader is recommended to play the mod with?
I **highly** recommend using the [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) by [ThirteenAG](https://github.com/ThirteenAG) purely due to the fact that it supports saving CrashDumps.

You can find the latest release here: https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/latest  

Download the `Ultimate-ASI-Loader.zip` file (not the `_x64.zip` one)  
It will contain a file called `dinput8.dll` - move the file to your GTA directory.  
Now rename it to `vorbisFile.dll` and replace the original.  
(Good for people that use the `dinput8.dll` mouse fix. Also the only way I personally got the ASI Loader to work)

Silent's ASI Loader works as well, but if you want to open an issue with some crashes I'll be closing any that do not have crash dumps.

Depending on which ASI Loader you picked, the files differ in size a bit:
- `vorbisFile.dll` (Ultimate ASI Loader): 2,102KB / 2,152,448 bytes
- `vorbisFile.dll` (Silent's ASI Loader): 53KB / 53,760 bytes

The reason why the Ultimate ASI Loader is **WAY BIGGER** in size is because it supports more than just the original `vorbisFile.dll`, comes with an additional windowed mode feature, a ["d3d8 to d3d9" pseudo-driver](https://github.com/crosire/d3d8to9) and a crash handler.

If you don't need any of that, Silent's ASI Loader will be all you need.

## How do I download the mod then?
Head on over to the the `Releases` tab or [click here](https://github.com/gta-chaos-mod/asi-script/releases/latest).

Installation is as simple as installing an ASI Loader (see previous section) and dropping the `.asi` file into either the `scripts` folder or into the game directory.

The `.exe` can be anywhere you want, as long as it has write permissions since it automatically saves the settings in a file called `config.cfg` in the same directory.

## ... and how do I use it?
Simple:
1. Start the game
2. Launch the corresponding `Chaos Mod.exe`
3. Now you have 2 options:
	1. Either press `Auto-Start` in the GUI, which will make it wait for you starting a new game and skipping the first cutscene (just like the autosplitter when doing a speedrun)
	2. Or you just press `Start` right away
4. Suffer

## Is there a list of all effects?
Of course! Here's a [spreadsheet](http://bit.ly/gta-sa-chaos-mod) that has all of them!

## I can't load any of my saves ingame!
Since this mod was built with speedrunners in mind, the `Load Save` option was disabled from both the main menu and the pause menu.

The only way to load the last autosave right now is to restart the game.

You can prevent it from trying to load the autosave by holding `Left CTRL` when booting up the game.

This will be addressed in a config file further down the line.

## Where are the autosaves being saved to?
Inside a sub-directory called `chaos_mod` in your corresponding GTA User Files folder.

## My game's crashing!
Great! Create an issue with the `.log` and `.dmp` files from the `CrashDumps` folder. (Best to archive them into a `.zip` file or similar)

## I have a suggestion for an effect!
Also great! Feel free to create an issue with that as well, best to explain what it should do in detail.

It could be that it is pretty much impossible to implement, or that I just won't consider working on it because there are already effects that are similar to it though, so keep that in mind.

## Why is there no license?!
There is a license. It's "All Rights Reserved" for now.

## I hate you!
Right back at you 😉

## **ATTENTION, ALL STREAMERS!**
You don't have to, but it'd be amazing if you could tag your streams with `#chaos` or something similar, maybe even tweet it out with the `#GTA_Chaos_Mod` hashtag.

I wouldn't mind potentially dropping by and seeing you guys suffer with the mod 😁

# Credits
## [DK22Pac](https://github.com/DK22Pac) and everyone involved in the [plugin-sdk](https://github.com/DK22Pac/plugin-sdk)

## [Parik](https://github.com/Zarig)
who has been helping me with a lot of function hooks and other things in the mod 💖

## Early beta testers
- [Jugachi](https://twitch.tv/jugachi)
- [Heinki](https://twitch.tv/heinki)
- [Naro](https://twitch.tv/naro)
- [Joshimuz](https://twitch.tv/joshimuz)
- [English\_Ben](https://twitch.tv/english_ben)
- [Tezur0](https://twitch.tv/tezur0)
- [GTA_Madman](https://twitch.tv/gta_madman)

## Everyone in the release race that was held on the 30th of August, 2019
- [123robot](https://twitch.tv/123robot)
- [DomoTheRussian](https://twitch.tv/domotherussian)
- [English\_Ben](https://twitch.tv/english_ben)
- [Gaël](https://twitch.tv/gaeldemarseille)
- [Jessey](https://twitch.tv/jesseysnipenl)
- [Nate](https://twitch.tv/natehotshot)
- [PizzaFourLife](https://twitch.tv/pizzafourlife)
- [RoK](https://twitch.tv/rok_24)
- [SpuG3](https://twitch.tv/spug3)
- [Terrtail](https://twitch.tv/terrtail)
- [zoton2](https://twitch.tv/zoton2)