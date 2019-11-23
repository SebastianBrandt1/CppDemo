#pragma once
#include "DemoCase.h"
class TypeDeduction :
	public DemoCase
{
public:
	TypeDeduction() = default;
	~TypeDeduction() = default;
	int Run() override;
};

