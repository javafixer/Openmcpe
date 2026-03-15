#include "PauseScreen.h"
#include "StartMenuScreen.h"
#include "ChatScreen.h"
#include "OptionsScreen.h"
#include "../components/ImageButton.h"
#include "../../Minecraft.h"
#include "../../../util/Mth.h"

PauseScreen::PauseScreen(bool wasBackPaused)
:	saveStep(0),
	visibleTime(0),
	bContinue(0),
	bQuit(0),
	bChat(0),
	bSettings(0),
	wasBackPaused(wasBackPaused),
	bSound(&Options::Option::SOUND, 1, 0),
	bThirdPerson(&Options::Option::THIRD_PERSON),
	bHideGui(&Options::Option::HIDE_GUI)
{
	ImageDef def;
	def.setSrc(IntRectangle(160, 144, 39, 31));
	def.name = "gui/touchgui.png";
	IntRectangle& defSrc = *def.getSrc();

	def.width = defSrc.w * 0.666667f;
	def.height = defSrc.h * 0.666667f;

	bSound.setImageDef(def, true);
	defSrc.y += defSrc.h;
	bThirdPerson.setImageDef(def, true);
	bHideGui.setImageDef(def, true);
}

PauseScreen::~PauseScreen() {
	delete bContinue;
	delete bQuit;
	delete bChat;
	delete bSettings;
}

void PauseScreen::init() {
	if (minecraft->useTouchscreen()) {
		bContinue = new Touch::TButton(1, "Back to game");
		bQuit     = new Touch::TButton(2, "Quit to title");
		bChat     = new Touch::TButton(5, "Chat");
		bSettings = new Touch::TButton(6, "Settings");
	} else {
		bContinue = new Button(1, "Back to game");
		bQuit     = new Button(2, "Quit to title");
		bChat     = new Button(5, "Chat");
		bSettings = new Button(6, "Settings");
	}

	buttons.push_back(bContinue);
	buttons.push_back(bQuit);
	buttons.push_back(bChat);
	buttons.push_back(bSettings);

	bSound.updateImage(&minecraft->options);
	bThirdPerson.updateImage(&minecraft->options);
	bHideGui.updateImage(&minecraft->options);
	buttons.push_back(&bSound);
	buttons.push_back(&bThirdPerson);

	for (unsigned int i = 0; i < buttons.size(); ++i) {
		if (buttons[i] == &bSound) continue;
		if (buttons[i] == &bThirdPerson) continue;
		if (buttons[i] == &bHideGui) continue;
		tabButtons.push_back(buttons[i]);
	}
}

void PauseScreen::setupPositions() {
	saveStep = 0;
	int yBase = 16;

	bContinue->width = bQuit->width = bChat->width = bSettings->width = 160;

	bContinue->x = (width - bContinue->width) / 2;
	bContinue->y = yBase + 32 * 1;

	bQuit->x = (width - bQuit->width) / 2;
	bQuit->y = yBase + 32 * 2;

	bChat->x = (width - bChat->width) / 2;
	bChat->y = yBase + 32 * 3;

	bSettings->x = (width - bSettings->width) / 2;
	bSettings->y = yBase + 32 * 4;

	bSound.y = bThirdPerson.y = 8;
	bSound.x = 4;
	bThirdPerson.x = bSound.x + 4 + bSound.width;
	bHideGui.x = bThirdPerson.x + 4 + bThirdPerson.width;
}

void PauseScreen::tick() {
	super::tick();
	visibleTime++;
}

void PauseScreen::render(int xm, int ym, float a) {
	renderBackground();
	drawCenteredString(font, "Game menu", width / 2, 24, 0xffffff);
	super::render(xm, ym, a);
}

void PauseScreen::buttonClicked(Button* button) {
	if (button->id == bContinue->id) {
		minecraft->setScreen(NULL);
	}
	if (button->id == bQuit->id) {
		minecraft->leaveGame();
	}
	if (button->id == bChat->id) {
		minecraft->setScreen(new ChatScreen());
	}
	if (button->id == bSettings->id) {
		minecraft->setScreen(new OptionsScreen());
	}
	if (button->id == OptionButton::ButtonId) {
		((OptionButton*)button)->toggle(&minecraft->options);
	}
}

void PauseScreen::updateServerVisibilityText() {}