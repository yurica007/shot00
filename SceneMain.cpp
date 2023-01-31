#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

#include "ShotNormal.h"
#include "ShotSin.h"
#include "ShotBound.h"

namespace
{
	// ショットの発射間隔
	constexpr int kShotInterval = 16;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hTestSound = -1;
}
SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{
	// グラフィックのロード
	m_hPlayerGraphic = LoadGraph("data/player.bmp");
	m_hShotGraphic = LoadGraph("data/shot.bmp");
	// サウンドのロード
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);
}

// 終了処理
void SceneMain::end()
{
	// グラフィックアンロード
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	// サウンドアンロード
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
void SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	m_player.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			// vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_player.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	
	// 現在存在している玉の数を表示
	DrawFormatString(0, 0, GetColor(225, 225, 225), "弾の数：%d", m_pShotVt.size());
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotSin(Vec2 pos)
{
	ShotSin* pShot = new ShotSin;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;

}