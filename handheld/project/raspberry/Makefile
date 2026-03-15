MODULE := minecraftpi

SOURCES := \
../../src/main.cpp \
../../src/platform/input/Controller.cpp \
../../src/platform/input/Keyboard.cpp \
../../src/platform/input/Mouse.cpp \
../../src/platform/input/Multitouch.cpp \
../../src/platform/time.cpp \
../../src/platform/CThread.cpp \
../../src/NinecraftApp.cpp \
../../src/Performance.cpp \
../../src/SharedConstants.cpp \
../../src/client/IConfigListener.cpp \
../../src/client/Minecraft.cpp \
../../src/client/Options.cpp \
../../src/client/OptionStrings.cpp \
../../src/client/OptionsFile.cpp \
../../src/client/MouseHandler.cpp \
../../src/client/gamemode/CreatorMode.cpp \
../../src/client/gamemode/GameMode.cpp \
../../src/client/gamemode/CreativeMode.cpp \
../../src/client/gamemode/SurvivalMode.cpp \
../../src/client/gui/components/Button.cpp \
../../src/client/gui/components/ImageButton.cpp \
../../src/client/gui/components/GuiElement.cpp \
../../src/client/gui/components/GuiElementContainer.cpp \
../../src/client/gui/components/ItemPane.cpp \
../../src/client/gui/components/InventoryPane.cpp \
../../src/client/gui/components/LargeImageButton.cpp \
../../src/client/gui/components/NinePatch.cpp \
../../src/client/gui/components/RolledSelectionListH.cpp \
../../src/client/gui/components/RolledSelectionListV.cpp \
../../src/client/gui/components/ScrolledSelectionList.cpp \
../../src/client/gui/components/ScrollingPane.cpp \
../../src/client/gui/components/SmallButton.cpp \
../../src/client/gui/components/Slider.cpp \
../../src/client/gui/components/OptionsItem.cpp \
../../src/client/gui/components/OptionsGroup.cpp \
../../src/client/gui/components/OptionsPane.cpp \
../../src/client/gui/Font.cpp \
../../src/client/gui/Gui.cpp \
../../src/client/gui/GuiComponent.cpp \
../../src/client/gui/Screen.cpp \
../../src/client/gui/screens/ScreenChooser.cpp \
../../src/client/gui/screens/ArmorScreen.cpp \
../../src/client/gui/screens/ChatScreen.cpp \
../../src/client/gui/screens/ConfirmScreen.cpp \
../../src/client/gui/screens/ChestScreen.cpp \
../../src/client/gui/screens/crafting/PaneCraftingScreen.cpp \
../../src/client/gui/screens/crafting/StonecutterScreen.cpp \
../../src/client/gui/screens/crafting/WorkbenchScreen.cpp \
../../src/client/gui/screens/crafting/CraftingFilters.cpp \
../../src/client/gui/screens/DeathScreen.cpp \
../../src/client/gui/screens/ChooseLevelScreen.cpp \
../../src/client/gui/screens/SimpleChooseLevelScreen.cpp \
../../src/client/gui/screens/FurnaceScreen.cpp \
../../src/client/gui/screens/InBedScreen.cpp \
../../src/client/gui/screens/IngameBlockSelectionScreen.cpp \
../../src/client/gui/screens/JoinGameScreen.cpp \
../../src/client/gui/screens/OptionsScreen.cpp \
../../src/client/gui/screens/PauseScreen.cpp \
../../src/client/gui/screens/ProgressScreen.cpp \
../../src/client/gui/screens/RenameMPLevelScreen.cpp \
../../src/client/gui/screens/SelectWorldScreen.cpp \
../../src/client/gui/screens/StartMenuScreen.cpp \
../../src/client/gui/screens/TextEditScreen.cpp \
../../src/client/gui/screens/UploadPhotoScreen.cpp \
../../src/client/model/ChickenModel.cpp \
../../src/client/model/CowModel.cpp \
../../src/client/model/HumanoidModel.cpp \
../../src/client/model/PigModel.cpp \
../../src/client/model/QuadrupedModel.cpp \
../../src/client/model/SheepModel.cpp \
../../src/client/model/SheepFurModel.cpp \
../../src/client/model/geom/Cube.cpp \
../../src/client/model/geom/ModelPart.cpp \
../../src/client/model/geom/Polygon.cpp \
../../src/client/particle/Particle.cpp \
../../src/client/particle/ParticleEngine.cpp \
../../src/client/player/LocalPlayer.cpp \
../../src/client/player/RemotePlayer.cpp \
../../src/client/player/input/KeyboardInput.cpp \
../../src/client/renderer/Chunk.cpp \
../../src/client/renderer/EntityTileRenderer.cpp \
../../src/client/renderer/GameRenderer.cpp \
../../src/client/renderer/ItemInHandRenderer.cpp \
../../src/client/renderer/LevelRenderer.cpp \
../../src/client/renderer/RenderChunk.cpp \
../../src/client/renderer/RenderList.cpp \
../../src/client/renderer/Tesselator.cpp \
../../src/client/renderer/Textures.cpp \
../../src/client/renderer/TileRenderer.cpp \
../../src/client/renderer/culling/Frustum.cpp \
../../src/client/renderer/entity/ArrowRenderer.cpp \
../../src/client/renderer/entity/ChickenRenderer.cpp \
../../src/client/renderer/entity/EntityRenderDispatcher.cpp \
../../src/client/renderer/entity/EntityRenderer.cpp \
../../src/client/renderer/entity/FallingTileRenderer.cpp \
../../src/client/renderer/entity/HumanoidMobRenderer.cpp \
../../src/client/renderer/entity/ItemRenderer.cpp \
../../src/client/renderer/entity/ItemSpriteRenderer.cpp \
../../src/client/renderer/entity/MobRenderer.cpp \
../../src/client/renderer/entity/PaintingRenderer.cpp \
../../src/client/renderer/entity/PlayerRenderer.cpp \
../../src/client/renderer/entity/SheepRenderer.cpp \
../../src/client/renderer/entity/TntRenderer.cpp \
../../src/client/renderer/entity/TripodCameraRenderer.cpp \
../../src/client/renderer/ptexture/DynamicTexture.cpp \
../../src/client/renderer/tileentity/ChestRenderer.cpp \
../../src/client/renderer/tileentity/SignRenderer.cpp \
../../src/client/renderer/tileentity/TileEntityRenderDispatcher.cpp \
../../src/client/renderer/tileentity/TileEntityRenderer.cpp \
../../src/client/sound/Sound.cpp \
../../src/client/sound/SoundEngine.cpp \
../../src/locale/I18n.cpp \
../../src/nbt/Tag.cpp \
../../src/network/command/CommandServer.cpp \
../../src/network/ClientSideNetworkHandler.cpp \
../../src/network/NetEventCallback.cpp \
../../src/network/Packet.cpp \
../../src/network/RakNetInstance.cpp \
../../src/network/ServerSideNetworkHandler.cpp \
../../src/server/CreatorLevel.cpp \
../../src/server/ServerLevel.cpp \
../../src/server/ServerPlayer.cpp \
../../src/util/DataIO.cpp \
../../src/util/Mth.cpp \
../../src/util/StringUtils.cpp \
../../src/util/PerfTimer.cpp \
../../src/util/PerfRenderer.cpp \
../../src/world/Direction.cpp \
../../src/world/entity/Entity.cpp \
../../src/world/entity/Mob.cpp \
../../src/world/entity/player/Inventory.cpp \
../../src/world/entity/player/Player.cpp \
../../src/world/item/Item.cpp \
../../src/world/item/ItemInstance.cpp \
../../src/world/level/Explosion.cpp \
../../src/world/level/Level.cpp \
../../src/world/level/Region.cpp \
../../src/world/level/chunk/LevelChunk.cpp \
../../src/world/level/material/Material.cpp \
../../src/world/phys/HitResult.cpp

CC := g++
SHELL := /bin/bash

CFLAGS := -DPOSIX -DGFX_SMALLER_CHUNKS -DNO_EGL -DUSE_VBO -O2 -g
LDFLAGS := -lGL -lGLEW -lSDL -lpng ../../src/raknet/libRakNet_static_O1.a

OBJECTS := $(SOURCES:%.cpp=%.o)

all: $(MODULE)

$(MODULE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(MODULE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(MODULE)