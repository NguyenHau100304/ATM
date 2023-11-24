#pragma once

#include "ATM.h"


namespace server {
	ATM atm;

	void run() {
		atm.runProcess();
	}

}