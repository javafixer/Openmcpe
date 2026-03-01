#ifndef NET_MINECRAFT_CLIENT_PLAYER__VitaInput_H__
#define NET_MINECRAFT_CLIENT_PLAYER__VitaInput_H__

//package net.minecraft.client.player;

#include "KeyboardInput.h"
#include "../../../platform/input/Controller.h"

// @note: This is just copy-pasted from KeyboardInput right now.
class VitaInput : public KeyboardInput
{
	typedef KeyboardInput super;
public:
	VitaInput(Options* options)
	:	super(options)
	{}

	void tick(Player* player) {
		const int moveStick = 1;
		if (Controller::isTouched(moveStick)) {
			xa = -Controller::getTransformedX(moveStick, 0.1f, 1.25f, true);
			ya = +Controller::getTransformedY(moveStick, 0.1f, 1.25f, true);
		}
		super::tick(player);
	}
};

#endif /*NET_MINECRAFT_CLIENT_PLAYER__VitaInput_H__*/
