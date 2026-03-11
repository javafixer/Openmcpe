# Minecraft PE
inset mcpe image :D
# About
TBA lol

# Compiling
to build it, make sure you have the latest VitaSDK from vitasdk.org

```
cmake -DPUBLISH=on -B build -S handheld/project/vita
cd build
make -j$(nproc)
```

If you want to build the demo; you can add the ``-DDEMO=on`` flag to the cmake line.

# Credits
   - Olebeck (graphics, sound, networking)
   - Li (controls, refining options, menuing) <-- original project!
   - Koutsie (original options menu)
   - PVR_PSP2 developers (GrapheneCt) 

# Other information:
 - VPK is just install-and-play, no additional setup should be required.
 - should be able to play local multiplayer over local wifi, and even cross-play with android/ios running official APK
 - due to the vita having very slow IO speeds, world generation can take awhile on the first time
 - savedata (worlds, options , etc) are stored in ux0:/data/minecraftpe/
 - as this is a source-port and cannot be easily adapted to any other version
