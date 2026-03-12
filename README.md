# Minecraft PE
insert mcpe image :D
# About
TBA lol

# Compiling
to build it, make sure you have the latest VitaSDK from vitasdk.org
PSVITA
```
cmake -DPUBLISH=on -B build -S handheld/project/vita
cd build
make -j$(nproc)
```
Win32 version TBA
Android version TBA

# Credits
   - Olebeck (graphics, sound, networking)
   - Li (controls, refining options, menuing) <-- original project!
   - Koutsie (original options menu)
   - PVR_PSP2 developers (GrapheneCt) 
# Platform
- linux 0%
- Psvita 80%
- win32 Unknown
- Android Unknown
- RaspberryPI Unknown
- IOS Unknown
- Ps3 0%

# Other information:
 - VPK is just install-and-play, no additional setup should be required.
 - due to the vita having very slow IO speeds, world generation can take awhile on the first time
 - savedata (worlds, options , etc) are stored in ux0:/data/minecraftpe/
 - To add servers Its located in ux0:data/minecraftpe/games/com.mojang/minecraftpe/server.json for psvita
 For android its /sdcard/games/com.mojang/minecraftpe/server.json
