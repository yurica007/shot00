#pragma once

#include "ShotBase.h"

class ShotBound : public ShotBase
{
public:
	ShotBound() {}
	virtual ~ShotBound() {}

	// �V���b�g�J�n
	virtual void start(Vec2 pos);

	// �X�V
	virtual void update();

private:
	// ���˕Ԃ�����
	int m_boundCount;
};
