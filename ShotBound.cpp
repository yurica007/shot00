#include "game.h"
#include "ShotBound.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
	
	// ���˕Ԃ��
	constexpr int kBoundMax = 3;

	// �O���t�B�b�N�f�[�^�̃T�C�Y
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

void ShotBound::start(Vec2 pos)
{
	ShotBase::start(pos);

	float randAngel = static_cast<float>(GetRand(359));
	float rad = randAngel * DX_PI_F / 180.0;	// ���W�A���ɕϊ�

	m_vec.x = cosf(rad);
	m_vec.y = sinf(rad);
	m_vec *= kShotSpeed;

	m_boundCount = 0;
}

void ShotBound::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;

	if (m_boundCount < kBoundMax)
	{
		if (m_pos.x < 0.0f)
		{
			m_pos.x = 0.0f;
			m_vec.x *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.y < 0.0f)
		{
			m_pos.y = 0.0f;
			m_vec.y *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.x > Game::kScreenWidth - kSizeX)
		{
			m_pos.x = Game::kScreenWidth - kSizeX;
			m_vec.x *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.y > Game::kScreenHeight - kSizeY)
		{
			m_pos.y = Game::kScreenHeight - kSizeY;
			m_vec.y *= -1.0f;
			m_boundCount++;
		}
	}
	else
	{
		if (m_pos.x < (0 - kSizeX))
		{
			m_isExist = false;
		}
		if (m_pos.y < (0 - kSizeY))
		{
			m_isExist = false;
		}
		if (m_pos.x > Game::kScreenWidth)
		{
			m_isExist = false;
		}
		if (m_pos.y > Game::kScreenHeight)
		{
			m_isExist = false;
		}
	}
}