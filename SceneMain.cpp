#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
}
SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	m_hPlayerGraphic = LoadGraph("data/player.bmp");
	m_hShotGraphic = LoadGraph("data/shot.bmp");

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);

	for (auto& pShot : m_pShot)
	{
		pShot = nullptr;
	}
}

// �I������
void SceneMain::end()
{
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);

	for (auto& pShot : m_pShot)
	{
		if (!pShot) continue;
		delete pShot;
		pShot = nullptr;
	}
}

// ���t���[���̏���
void SceneMain::update()
{
	m_player.update();
	for (auto& pShot : m_pShot)
	{
		if (!pShot) continue;
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;
		}
	}
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_player.draw();

	for (auto& pShot : m_pShot)
	{
		if (!pShot) continue;
		pShot->draw();
	}
	
	// ���ݑ��݂��Ă���ʂ̐���\��
	int shotNum = 0;
	for (auto& pShot : m_pShot)
	{
		if (!pShot) continue;
		if (pShot->isExist()) shotNum++;
	}
	DrawFormatString(0, 0, GetColor(225, 225, 225), "�e�̐��F%d", shotNum);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	for (auto& pShot : m_pShot)
	{
		if (pShot) continue;

		pShot = new ShotNormal;
		pShot->setHandle(m_hShotGraphic);
		pShot->start(pos);
		return true;
	}
	return false;
}

bool SceneMain::createShotSin(Vec2 pos)
{
	for (auto& pShot : m_pShot)
	{
		if (pShot) continue;

		pShot = new ShotSin;
		pShot->setHandle(m_hShotGraphic);
		pShot->start(pos);
		return true;
	}
	return false;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	for (auto& pShot : m_pShot)
	{
		if (pShot) continue;

		pShot = new ShotBound;
		pShot->setHandle(m_hShotGraphic);
		pShot->start(pos);
		return true;
	}
	return false;
}