#include "Controller.h"

static int   _abs(int x)   { return x>=0? x:-x; }
static float _abs(float x) { return x>=0? x:-x; }

/*static*/ float Controller::stickValuesX[NUM_STICKS] = {0};
/*static*/ float Controller::stickValuesY[NUM_STICKS] = {0};
/*static*/ bool Controller::isTouchedValues[NUM_STICKS] = {0};

bool Controller::isTouched( int stickIndex )
{
	if (!isValidStick(stickIndex)) return false;

	return isTouchedValues[stickIndex-1];
}

void Controller::feed( int stickIndex, int state, float dx, float dy )
{
	if (!isValidStick(stickIndex)) return;

	isTouchedValues[stickIndex-1] = (state != STATE_RELEASE);

	stickValuesX[stickIndex-1] = dx;
	stickValuesY[stickIndex-1] = dy;
}

float Controller::getX( int stickIndex )
{
	if (!isValidStick(stickIndex)) return 0;
	return stickValuesX[stickIndex-1];
}

float Controller::getY( int stickIndex )
{
	if (!isValidStick(stickIndex)) return 0;
	return stickValuesY[stickIndex-1];
}

float Controller::getTransformedX( int stickIndex, float deadZone, float scale/*=1.0f*/, bool limit1/*=false*/ )
{
	if (!isValidStick(stickIndex)) return 0;
	return linearTransform(stickValuesX[stickIndex-1], deadZone, scale, limit1);
}

float Controller::getTransformedY( int stickIndex, float deadZone, float scale/*=1.0f*/, bool limit1/*=false*/ )
{
	if (!isValidStick(stickIndex)) return 0;
	return linearTransform(stickValuesY[stickIndex-1], deadZone, scale, limit1);
}

float Controller::linearTransform( float value, float deadZone, float scale/*=1.0f*/, bool limit1/*=false*/ )
{
	float deadSigned = value >= 0? deadZone : -deadZone;
	if (_abs(deadSigned) >= _abs(value)) return 0;
	float ret = (value - deadSigned) * scale;
	if (limit1 && _abs(ret) > 1) ret = ret>0.0f? 1.0f : -1.0f;
	return ret;
}

/*static*/
bool Controller::isValidStick(int stick) {
	return stick > 0 && stick <= NUM_STICKS;
}
