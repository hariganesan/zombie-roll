// Hari Ganesan 7/24/13
// zombie-roll: handling logic

#include "Window.hpp"

void MyWindow::performLogic() {
	// FIELD

	if (g->display == D_FIELD) {
		moved = false;
		if (keys.left) {
			if (g->mc->moveLeft()) {
				moved = true;
			}
		} else if (keys.down) {
			if (g->mc->moveDown()) {
				moved = true;
			}
		} else if (keys.right) {
			if (g->mc->moveRight()) {
				moved = true;
			}
		} else if (keys.up) {
			if (g->mc->moveUp()) {
				moved = true;
			}
		}

		// battle!
		// if (moved && rand() % 100 < g->currentArea->battlePercent*100) {
			// g->createBattle();
			// g->display = DT_FIELD_BATTLE;
		// }

	// FIELD-BATTLE TRANSITION

	} else if (g->display == DT_FIELD_BATTLE) {
		if (g->timer > TT_FIELD_BATTLE) {
			g->timer = 0;
			g->display = D_BATTLE;
		}

	// BATTLE

	} else if (g->display == D_BATTLE) {
		;
	}
}
