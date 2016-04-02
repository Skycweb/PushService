#pragma once
#include "../include/lzz_Factory.h"

class lzz_Heartbeat:public lzz_Factory
{
public:

	~lzz_Heartbeat() override;
	void onLoad() override;
};
