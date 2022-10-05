#pragma once

#include "ShotBase.h"

class ShotSin : public ShotBase
{
public:
	ShotSin() {}
	virtual ~ShotSin() {}

	// ショット開始
	virtual void start(Vec2 pos);

	// 更新
	virtual void update();

};