#include "DifficultyList.h"

DifficultyList::DifficultyList()
{
	head = nullptr;
	reached = nullptr;
	totalDifficulty = 0;
}

DifficultyList::~DifficultyList()
{
	Difficulty* deleteNext = nullptr;
	Difficulty* deleteCurrent = head;
	for (int i = 0; i < totalDifficulty; i++) {
		if (i == 0)
		{
			deleteNext = deleteCurrent->next;

			delete deleteCurrent;
		}
		else {
			deleteCurrent = deleteNext;
			deleteNext = deleteCurrent->next;

			delete deleteCurrent;
		}
	}
}

void DifficultyList::insertDifficulty(int hp, int dmg, float move, int maxE, double chanceEnemy, int timerSpawn, int maxP, double chancePower, int timerPower)
{
	Difficulty* new_Difficulty = new Difficulty;
	new_Difficulty->enemyHP = hp;
	new_Difficulty->enemyDamage = dmg;
	new_Difficulty->enemyMovementSpeed = move;
	new_Difficulty->maxEnemies = maxE;
	new_Difficulty->spawnChance = chanceEnemy;
	new_Difficulty->spawnTimerMax = timerSpawn;
	new_Difficulty->maxPower = maxP;
	new_Difficulty->powerUpChance = chancePower;
	new_Difficulty->powerUpTimerMax = timerPower;
	new_Difficulty->next = nullptr;
	totalDifficulty++;

	if (head == nullptr)
	{
		head = new_Difficulty;
		reached = head;
	}
	else {
		new_Difficulty->next = head;
		head = new_Difficulty;
		reached = head;
	}
}

void DifficultyList::nextLevel()
{
	reached = reached->next;
}

Difficulty* DifficultyList::getHead()
{
	return head;
}

Difficulty* DifficultyList::getReached()
{
	return reached;
}
