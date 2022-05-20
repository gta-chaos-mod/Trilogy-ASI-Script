# GTA Trilogy Chaos Mod: Reborn
Welcome to the official **GTA Trilogy Chaos Mod: Reborn** repository!

This repository, together with this README, is still very much **WIP**.

# Why "Reborn"?
The mod had some issues and was my first C++ project, thus I did not have a lot of experience on how to best do a lot of things right.

The **"Reborn"** project aims to fix this by pretty much **rewriting the majority of the mod from scratch.** (except code for drawing effects and a few other things)

It will also be easier for interested developers to contribute to the project be it with their own effects or with help on the general codebase.

# How can I help?
Check out the [CONTRIBUTING](CONTRIBUTING.md) file for more information.

# What does this mod do?
Similar to the old [Vice City Chaos% mod](https://github.com/Lighnat0r-pers/gta-vc-chaos) by [Lightnat0r](https://github.com/Lighnat0r), it activates effects in the corresponding game every X seconds / minutes (cooldown can be defined in the GUI tool).

# Which GTA games does it support?
It started off as a mod for **San Andreas**, which is the one that is mainly supported right now.  
However, there is already basic support for **Vice City** and **III** implemented. It will take longer to bring all (if possible) custom effects over, and also implement their corresponding ingame cheats though.

# Which versions of the games does it support?
**GTA San Andreas**: v1.0 US  
~~**GTA Vice City**: v1.0 US~~  
~~**GTA III**: v1.0 US~~

So far only San Andreas is officially supported.  
Vice City and III have some sort of basic support in already, but the GUI Tool doesn't support them yet.

# How do I downgrade my game to the required version?
There's a handy thread over on the GTA Forums that has downgraders vor GTA III, Vice City and even San Andreas.  
https://gtaforums.com/topic/936600-iii-iv-various-gta-downgraders/

# What ASI Loader is recommended to play the mod with?
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

# How do I download the mod then?
Head on over to the the `Releases` tab or [click here](https://github.com/gta-chaos-mod/asi-script/releases/latest).

Installation is as simple as installing an ASI Loader (see previous section) and copying all the files into your game directory. (So the `chaos_mod` folder, the `scripts` folder and the `.exe`)

The `.exe` can be anywhere you want, as long as it has write permissions since it automatically saves the settings in a file called `config.cfg` in the same directory.

**You also need to have [.NET Framework 4.7.2](https://dotnet.microsoft.com/download/dotnet-framework/net472) installed.**

# ... and how do I use it?
Simple:
1. Start the game
2. Launch the corresponding `Trilogy Chaos Mod.exe`
3. Now you have 2 options:
	1. Either press `Auto-Start` in the GUI, which will make it wait for you starting a new game and skipping the first cutscene (just like the autosplitter when doing a speedrun)
	2. Or you just press `Start` right away
4. Suffer

# Is there a list of all effects?
Of course! Here's a [spreadsheet](http://bit.ly/gta-sa-chaos-mod) that has all of them!

# How do I load the last autosave when ingame?
Hold down `Left CTRL` when hovering over the `Load Game` option in the menu.

# Where are the autosaves being saved to?
Inside a sub-directory called `chaos_mod` in your corresponding GTA User Files folder.

# How do I setup the Twitch voting?
In the Twitch tab you have to fill out the `Access Token` and `Client ID` fields.

To generate an Access Token and get a Client ID, please head to [this website](https://chaos.lord.moe/) and follow the instructions.

For Twitch you now have the option to have voting happen through chat messages (1, 2, 3) or their integrated Polls system.

![https://i.imgur.com/6Ebrgfy.png](https://i.imgur.com/6Ebrgfy.png)

# How do I setup the YouTube voting? (Experimental)
Enable the `Experimental` tab by pressing `File` and then `Experimental`.
Tick the checkbox that says `YouTube Connection`.

Put your livestream ID into the `Access Token` field in the `Stream` tab and put something random into `Client ID` (this field doesn't matter in this mode as it's not read).

Do note that in YouTube mode there will be no chat messages posted about voting happening.

# My game's crashing!
Great! Create an issue with the `.log` and `.dmp` files from the `CrashDumps` folder. (Best to archive them into a `.zip` file or similar)

# I have a suggestion for an effect!
Also great! Feel free to create an issue with that as well, best to explain what it should do in detail.

It could be that it is pretty much impossible to implement, or that I just won't consider working on it because there are already effects that are similar to it though, so keep that in mind.

# Credits
## [DK22Pac](https://github.com/DK22Pac) and everyone involved in the [plugin-sdk](https://github.com/DK22Pac/plugin-sdk)

## [Parik](https://github.com/Parik27)
who has been helping me with a lot of function hooks and other things in the mod 💖

## Early beta testers
- [English\_Ben](https://twitch.tv/english_ben)
- [GTA_Madman](https://twitch.tv/gta_madman)
- [Heinki](https://twitch.tv/heinki)
- [Joshimuz](https://twitch.tv/joshimuz)
- [Jugachi](https://twitch.tv/jugachi)
- [Naro](https://twitch.tv/naro)
- [Tezur0](https://twitch.tv/tezur0)

## Everyone in the v3.0 release race that was held on the [DATE HERE]
- You?

## Everyone in the v1.0 release race that was held on the 30th of August, 2019
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
- [wariscoach](https://twitch.tv/wariscoach)