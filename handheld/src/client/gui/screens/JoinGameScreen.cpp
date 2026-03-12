#include "JoinGameScreen.h"
#include "StartMenuScreen.h"
#include "ProgressScreen.h"
#include "../Font.h"
#include "../../../network/RakNetInstance.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// aa
#ifdef __APPLE__
#define SERVER_FILE_PATH "./Documents/server.json"
#elif defined(ANDROID)
#define SERVER_FILE_PATH "/sdcard/games/com.mojang/minecraftpe/server.json"
#elif defined(__VITA__)
#define SERVER_FILE_PATH "ux0:data/minecraftpe/games/com.mojang/minecraftpe/server.json"
#else
#define SERVER_FILE_PATH "server.json"
#endif

// --------------------- JoinGameScreen ---------------------
JoinGameScreen::JoinGameScreen()
    : bJoin(2, "Join Game"), bBack(3, "Back"), gamesList(nullptr)
{
    bJoin.active = false;

    // Load servers from JSON
    loadServersFromJson(SERVER_FILE_PATH);

    // Fallback local server
    if (manualServers.empty()) {
        PingedCompatibleServer server;
        server.name = "My Server";
        server.address = RakNet::SystemAddress("127.0.0.1", 19132);
        manualServers.push_back(server);
    }
}

JoinGameScreen::~JoinGameScreen()
{
    delete gamesList;
    gamesList = nullptr;
}

// --------------------- Minimal JSON Parsing ---------------------
void JoinGameScreen::loadServersFromJson(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) return;

    std::string content, line;
    while (std::getline(file, line)) content += line;

    size_t pos = 0;
    while ((pos = content.find("{", pos)) != std::string::npos) {
        size_t end = content.find("}", pos);
        if (end == std::string::npos) break;

        std::string block = content.substr(pos, end - pos + 1);

        size_t n1 = block.find("\"name\"");
        size_t a1 = block.find("\"address\"");
        if (n1 != std::string::npos && a1 != std::string::npos) {
            size_t nStart = block.find("\"", n1 + 6) + 1;
            size_t nEnd = block.find("\"", nStart);
            size_t aStart = block.find("\"", a1 + 9) + 1;
            size_t aEnd = block.find("\"", aStart);

            std::string name = block.substr(nStart, nEnd - nStart);
            std::string addr = block.substr(aStart, aEnd - aStart);

            PingedCompatibleServer server;
            server.name = name.c_str();

            std::string host = addr;
            unsigned short port = 19132;
            size_t colon = addr.find(':');
            if (colon != std::string::npos) {
                host = addr.substr(0, colon);
                port = static_cast<unsigned short>(std::stoi(addr.substr(colon + 1)));
            }

            server.address = RakNet::SystemAddress(host.c_str(), port);
            manualServers.push_back(server);
        }

        pos = end + 1;
    }
}

// --------------------- Buttons ---------------------
void JoinGameScreen::buttonClicked(Button* button)
{
    if (button->id == bJoin.id && isIndexValid(gamesList->selectedItem)) {
        PingedCompatibleServer selectedServer =
            gamesList->copiedServerList[gamesList->selectedItem];
        minecraft->joinMultiplayer(selectedServer);
        bJoin.active = false;
        bBack.active = false;
        minecraft->setScreen(new ProgressScreen());
    }

    if (button->id == bBack.id) {
        minecraft->cancelLocateMultiplayer();
        minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
    }
}

bool JoinGameScreen::handleBackEvent(bool isDown)
{
    if (!isDown) {
        minecraft->cancelLocateMultiplayer();
        minecraft->screenChooser.setScreen(SCREEN_STARTMENU);
    }
    return true;
}

// --------------------- Server List ---------------------
bool JoinGameScreen::isIndexValid(int index)
{
    return gamesList && index >= 0 && index < gamesList->getNumberOfItems();
}

void JoinGameScreen::tick()
{
    if (!gamesList) return;

    const ServerList& orgServerList = minecraft->raknetInstance->getServerList();
    ServerList serverList;

    for (auto& s : manualServers) serverList.push_back(s);
    for (auto& s : orgServerList)
        if (s.name.GetLength() > 0) serverList.push_back(s);

    if (serverList.size() != gamesList->copiedServerList.size()) {
        gamesList->copiedServerList = serverList;
        gamesList->selectItem(-1, false);
    }

    bJoin.active = isIndexValid(gamesList->selectedItem);
}

// --------------------- Init / Layout ---------------------
void JoinGameScreen::init()
{
    buttons.push_back(&bJoin);
    buttons.push_back(&bBack);

    if (minecraft->raknetInstance)
        minecraft->raknetInstance->clearServerList();

    gamesList = new AvailableGamesList(minecraft, width, height);
}

void JoinGameScreen::setupPositions()
{
    int yBase = height - 26;
    bJoin.y = bBack.y = yBase;
    bJoin.width = bBack.width = 120;
    bJoin.x = width / 2 - 124;
    bBack.x = width / 2 + 4;
}

// --------------------- Rendering ---------------------
void JoinGameScreen::render(int xm, int ym, float a)
{
    bool hasNetwork = minecraft->platform()->isNetworkEnabled(true);

    renderBackground();
    if (hasNetwork && gamesList) gamesList->render(xm, ym, a);
    Screen::render(xm, ym, a);

    std::string msg = hasNetwork ? "Scanning for WiFi Games..." : "WiFi is disabled";
    drawCenteredString(minecraft->font, msg, width / 2, hasNetwork ? 8 : height / 2 - 8, 0xffffffff);
}

bool JoinGameScreen::isInGameScreen()
{
    return false;
}

// --------------------- Force vtable ---------------------
void JoinGameScreen::forceVtable() {}

// --------------------- Force vtable link ---------------------
// Ensures the vtable is emitted during linking on Vita
JoinGameScreen* _joinGameScreenVtableForce = nullptr;