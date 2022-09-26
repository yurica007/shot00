#include "DxLib.h"
#include "shot.h"


Shot::Shot()
{
	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 8.0f;
	m_vec.y = 0.0f;
}

Shot::~Shot()
{

}

void Shot::update()
{
	m_pos += m_vec;
}
// •\Ž¦
void Shot::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}
