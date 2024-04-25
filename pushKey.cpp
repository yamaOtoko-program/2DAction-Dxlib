#include "pushKey.hpp"
#include "Dxlib.h"
pushKey::pushKey(int a) {
	this->a = a;
	canpush = false;
}
bool pushKey::push() {
	if (a == MOUSE_INPUT_LEFT || a == MOUSE_INPUT_RIGHT || a == MOUSE_INPUT_MIDDLE) {
		if (!(GetMouseInput() & a)) { canpush = false; return false; }
	}
	else {
		if (!CheckHitKey(a)) { canpush = false; return false; }
	}
	if (!canpush) {
		canpush = true;
		return true;
	}
	return false;
}