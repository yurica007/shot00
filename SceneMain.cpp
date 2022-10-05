#include "DxLib.h"
#include "SceneMain.h"

namespace
{
	// ショットの発射間隔
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

// 初期化
void SceneMain::init()
{
	m_hPlayerGraphic = LoadGraph("data/player.bmp");
	m_hShotGraphic = LoadGraph("data/shot.bmp");

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);

	for (auto& shot : m_pShotNormal)
	{
		shot = nullptr;
	}
	for (auto& shot : m_pShotSin)
	{
		shot = nullptr;
	}
	for (auto& shot : m_pShotBound)
	{
		shot = nullptr;
	}
}

// 終了処理
void SceneMain::end()
{
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
}

// 毎フレームの処理
void SceneMain::update()
{
	m_player.update();
	for (auto& shot : m_pShotNormal)
	{
		if (!shot) continue;
		shot->update();
	}
	for (auto& shot : m_pShotSin)
	{
		if (!shot) continue;
		shot->update();
	}
	for (auto& shot : m_pShotBound)
	{
		if (!shot) continue;
		shot->update();
	}
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_player.draw();

	for (auto& shot : m_shotNormal)
	{
		shot.draw();
	}
	for (auto& shot : m_shotSin)
	{
		shot.draw();
	}
	for (auto& shot : m_shotBound)
	{
		shot.draw();
	}

	// 現在存在している玉の数を表示
	int shotNum = 0;
	for (auto& shot : m_shotNormal)
	{
		if (shot.isExist()) shotNum++;
	}
	DrawFormatString(0, 0, GetColor(225, 225, 225), "normal：%d", shotNum);
	shotNum = 0;
	for (auto& shot : m_shotSin)
	{
		if (shot.isExist()) shotNum++;
	}
	DrawFormatString(0, 30, GetColor(225, 225, 225), "sin：%d", shotNum);
	shotNum = 0;
	for (auto& shot : m_shotBound)
	{
		if (shot.isExist()) shotNum++;
	}
	DrawFormatString(0, 60, GetColor(225, 225, 225), "bound：%d", shotNum);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	for (auto& shot : m_shotNormal)
	{
		if (shot.isExist()) continue;
		
		shot.start(pos);
		return true;
	}
	return false;
}

bool SceneMain::createShotSin(Vec2 pos)
{
	for (auto& shot : m_shotSin)
	{
		if (shot.isExist()) continue;

		shot.start(pos);
		return true;
	}
	return false;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	for (auto& shot : m_shotBound)
	{
		if (shot.isExist()) continue;

		shot.start(pos);
		return true;
	}
	return false;
}