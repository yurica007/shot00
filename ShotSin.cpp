#include "game.h"
#include "ShotSin.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
	constexpr float kSinSpeed = 0.5f;
}

void ShotSin::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeed;
	m_vec.y = -kShotSpeed;

}

void ShotSin::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;

	m_vec.y += kSinSpeed;

	if ((m_pos.y > Game::kScreenHeight) || (m_pos.x > Game::kScreenWidth))
	{
		m_isExist = false;
	}
}