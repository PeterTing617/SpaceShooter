#pragma once

// Difficulty Struct
struct Difficulty
{
	// Enemies
	int enemyHP;
	int enemyDamage;
	float enemyMovementSpeed;
	int maxEnemies;
	double spawnChance;
	int spawnTimerMax;

	// PowerUps
	int maxPower;
	double powerUpChance;
	int powerUpTimerMax;

	Difficulty* next;

};

// Singly-linked List - Difficulty
class DifficultyList
{
private:
	int totalDifficulty;
	Difficulty* head;
	Difficulty* reached;

public:
	// Constructor and Destructor
	DifficultyList();
	virtual ~DifficultyList();

	// Functions
	// Insert a difficulty struct at the back of head
	void insertDifficulty(int hp, int dmg, float move, int maxE, double chanceEnemy, int timerSpawn, int maxP, double chancePower, int timerPower);

	// Proceed to next level
	void nextLevel();

	// Get the head difficultys
	Difficulty* getHead();

	// Get the reached difficultys
	Difficulty* getReached();
};

