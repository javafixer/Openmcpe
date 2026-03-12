#ifndef NET_MINECRAFT_CLIENT_GUI_SCREENS__JoinGameScreen_H__
#define NET_MINECRAFT_CLIENT_GUI_SCREENS__JoinGameScreen_H__

#include "../Screen.h"
#include "../components/Button.h"
#include "../components/ScrolledSelectionList.h"
#include "../../Minecraft.h"
#include "../../../network/RakNetInstance.h"

class JoinGameScreen;

// --------------------- Server List ---------------------
class AvailableGamesList : public ScrolledSelectionList
{
    int selectedItem;
    ServerList copiedServerList;

    friend class JoinGameScreen;

public:
    AvailableGamesList(Minecraft* _minecraft, int _width, int _height)
        : ScrolledSelectionList(_minecraft, _width, _height, 24, _height - 30, 28)
    {
        selectedItem = -1;
    }

protected:
    virtual int getNumberOfItems() override { return (int)copiedServerList.size(); }
    virtual void selectItem(int item, bool doubleClick) override { selectedItem = item; }
    virtual bool isSelectedItem(int item) override { return item == selectedItem; }
    virtual void renderBackground() override {}
    virtual void renderItem(int i, int x, int y, int h, Tesselator& t) override
    {
        const PingedCompatibleServer& s = copiedServerList[i];
        unsigned int color = s.isSpecial ? 0xff00b0 : 0xffffa0;
        drawString(minecraft->font, s.name.C_String(), x, y + 2, color);
        drawString(minecraft->font, s.address.ToString(false), x, y + 16, 0xffffa0);
    }
};

// --------------------- JoinGameScreen ---------------------
class JoinGameScreen : public Screen
{
public:
    JoinGameScreen();
    virtual ~JoinGameScreen();

    // Screen overrides
    void init() override;
    void setupPositions() override;
    void tick() override;
    void render(int xm, int ym, float a) override;
    bool handleBackEvent(bool isDown) override;
    bool isInGameScreen() override;

    // Buttons
    void buttonClicked(Button* button);
    bool isIndexValid(int index);

private:
    // Internal helpers
    void loadServersFromJson(const std::string& filepath);

    // Force vtable generation
    void forceVtable();

    // UI
    Button bJoin;
    Button bBack;
    AvailableGamesList* gamesList;

    // Servers
    ServerList manualServers;
};

#endif // NET_MINECRAFT_CLIENT_GUI_SCREENS__JoinGameScreen_H__