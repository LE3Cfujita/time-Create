#include "RecoveryEnemy.h"

RecoveryEnemy::RecoveryEnemy()
{
}

RecoveryEnemy::~RecoveryEnemy()
{
}

void RecoveryEnemy::Initialize(XMFLOAT2 pos)
{
	objectMember = GameObject::RECOVERYENEMY;
	HP = 10;
	r = 64;
	recovery = LoadGraph("Resource/healEnemy.png");
	heal = LoadGraph("Resource/healEffect.png");
	position = pos;
	actionFlag = false;
}

void RecoveryEnemy::Update()
{
	if (actionFlag == false)
	{
		Spwan();
	}
	else
	{
		Move();
		BeamAttack();
	}
	if (HP <= 0)
	{
		objState = DEATH;
	}
}

void RecoveryEnemy::Draw()
{
	if (actionFlag == true)
	{
		DrawRectGraph(position.x - r, position.y - r, animeCount * 128, 0, 128, 128, recovery, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph(position.x, position.y, size, angle, recovery, TRUE, FALSE);
	}
	if (moveFlag == false)
	{
		DrawGraph(position.x - r, position.y - r, heal, true);
	}
}

void RecoveryEnemy::Resource(int bul)
{
	this->bul = bul;
}

void RecoveryEnemy::HitAction(GameObject* gameObject)
{
	if (actionFlag != true)return;
	if (gameObject->GetObjectMember() == OBJECTMEMBER::PLAYERBULLET)
	{
		//PlaySoundMem(damageSE, DX_PLAYTYPE_BACK, TRUE);
		HP--;
		gameObject->SetDeathFlag(true);
	}
}

void RecoveryEnemy::Move()
{
	moveTime++;

	if (moveFlag == false)
	{
		if (moveTime >= 240)
		{
			moveFlag = true;
			moveTime = 0;
			RecoveryItem* item = new RecoveryItem;
			item->BaseInitialize(referenceGameObjects);
			item->Initialize({ position });
			addGameObjects.push_back(item);
			beamFlag = true;
		}
		Attack();
		if (position.y <= 16)topFlag = true;//trueだったら下移動
		if (position.y >= 704)topFlag = false;//falseだったら上移動
		if (topFlag == true)position.y += 3;
		else position.y -= 3;
	}
	else
	{
		Recovery();
		if (moveTime >= 240)
		{
			moveFlag = false;
			moveTime = 0;
		}
	}
}

void RecoveryEnemy::Recovery()
{
	time++;
	if (time >= 15)
	{
		if (HP < 99)
		{
			HP += 2;
		}
		time = 0;
	}
}

void RecoveryEnemy::Attack()
{
	if (attackFlag == false)
	{
		RecoveryBullet* bullet = new RecoveryBullet();
		bullet->BaseInitialize(referenceGameObjects);
		bullet->Initialize(position);
		bullet->Resource(bul);
		addGameObjects.push_back(bullet);
		attackFlag = true;
	}
	else
	{
		attackTime++;
		if (attackTime > 5)
		{
			attackFlag = false;
			attackTime = 0;
		}
	}
}

void RecoveryEnemy::BeamAttack()
{
	if (beamFlag == true)
	{
		int a = rand() % 2;

		RecoveryBeam* bullet = new RecoveryBeam();
		bullet->BaseInitialize(referenceGameObjects);
		if (a == 1)
		{
			bullet->Initialize({ 180,-720 });
		}
		else
		{
			bullet->Initialize({ 480,-720 });
		}
		addGameObjects.push_back(bullet);
		beamFlag = false;
	}
}

void RecoveryEnemy::Spwan()
{
	if (size < 1)
	{
		angle += 0.5;
		size += 0.02;
	}
	else
	{
		actionFlag = true;
	}
}
