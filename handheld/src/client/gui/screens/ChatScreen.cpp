#include "ChatScreen.h"
#include "DialogDefinitions.h"
#include "../Gui.h"
#include "../../Minecraft.h"
#include "../../../AppPlatform.h"
#include "../../../platform/log.h"

void ChatScreen::init() {
    minecraft->platform()->createUserInput(DialogDefinitions::DIALOG_NEW_CHAT_MESSAGE);
}
void ChatScreen::render(int xm, int ym, float a) {
    int status = minecraft->platform()->getUserInputStatus();
    if (status > -1) {  // this might be firing immediately as 0
        // handle user input here if needed
        minecraft->setScreen(NULL);  // closes right away before OSK appears
    }
}