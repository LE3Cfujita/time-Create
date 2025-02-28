#include "BossEnemy.h"

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Resource(int graph, int damage, int se, int weak)
{
	boss = graph;//画像読み込み
	damageSE = damage;
	attackSE = se;
	weakEnemy = weak;
}

void BossEnemy::HitAction(GameObject* gameObject)
{
	if (objState == EFFECT || objState == DEATH || actionFlag == false)return;
	if (gameObject->GetObjectMember() == OBJECTMEMBER::PLAYERBULLET)
	{
		PlaySoundMem(damageSE, DX_PLAYTYPE_BACK, TRUE);
		HP--;
		gameObject->SetDeathFlag(true);
	}
}

void BossEnemy::Spawn()
{
	dx = 1100 - position.x;
	if (dx != 0)
	{
		da = dx * dx;
		L = sqrt(da);
		position.x += (dx / L) * 10;
	}
	else
	{
		actionFlag = true;
	}
}

void BossEnemy::Move()
{
	if (position.y <= 16)moveFlag = true;//trueだったら下移動
	if (position.y >= 704)moveFlag = false;//falseだったら上移動
	if (moveFlag == true)position.y += 5;
	else position.y -= 5;
}

void BossEnemy::Attack()
{
	if (attackFlag == true)
	{
		PlaySoundMem(attackSE, DX_PLAYTYPE_BACK, TRUE);
		BossNormalBullet* bullet;
		bullet = new BossNormalBullet();
		bullet->BaseInitialize(referenceGameObjects);
		bullet->Initialize({ position });
		bullet->Resource();
		addGameObjects.push_back(bullet);
		attackFlag = false;

		int a = rand() % 5;
		if (a == 0)
		{
			if (line <= 5)
			{
				Summon();
				line++;
			}
		}
	}
	else
	{
		timer++;
		if (timer <= 120)return;
		attackFlag = true;
		timer = 0;
	}
}

void BossEnemy::Summon()
{
	for (int i = 0; i < 5; i++)
	{
		WeakEnemy* enemy;
		enemy = new WeakEnemy();
		enemy->BaseInitialize(referenceGameObjects);
		enemy->Initialize({ (float)750 + 100 * line,(float)-100 - 100 * i }, i);
		enemy->Resource(weakEnemy, damageSE, attackSE);
		addGameObjects.push_back(enemy);
	}
}

void BossEnemy::Initialize(XMFLOAT2 pos)
{
	objectMember = GameObject::BOSSENEMY;
	objectStage = GameObject::SECONDSTAGE;
	position = pos;
	r = 64;
	HP = 50;
	timer = 0;
	actionFlag = false;
}

void BossEnemy::Update()
{
	if (actionFlag == false)
	{
		Spawn();
	}
	else
	{
		if (HP <= 0)
		{
			objState = DEATH;
			deathCount = 1;
		}
		Move();
		Attack();
	}
}

void BossEnemy::Draw()
{
	if (objState == EFFECT || objState == DEATH)return;
	switch (objectStage)
	{
	case SECONDSTAGE:
		DrawRectGraph(position.x - r, position.y - r, animeCount * 128, 0, 128, 128, boss, TRUE, FALSE);
		break;
	}
}

