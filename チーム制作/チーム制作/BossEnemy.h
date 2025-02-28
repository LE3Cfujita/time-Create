#pragma once
#include"GameObject.h"
#include"HitEffect.h"
#include "DownEffec.h"
#include"BossNormalBullet.h"
#include"WeakEnemy.h"
class BossEnemy : public GameObject
{

public:
	BossEnemy();
	~BossEnemy();

	//初期化
	void Initialize(XMFLOAT2 pos);

	void Update();

	void Draw();

	void Resource(int graph,int damage,int se,int weak);

	void HitAction(GameObject* gameObject);

	void Spawn();

private:

	void Move();

	void Attack();

	void Summon();



	int boss;
	int weakEnemy;
	//変数
	bool moveFlag = false;
	bool attackFlag = false;

	int line = 0;
	//音関係
	int damageSE;
	int attackSE;

};

