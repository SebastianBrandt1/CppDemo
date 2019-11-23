#pragma once
#include "Global.h"

class DemoCase
{
public:
	DemoCase() = default;
	virtual ~DemoCase() = default;
	virtual int Run() {
		return 0;
	}
};

