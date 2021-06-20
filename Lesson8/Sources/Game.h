#pragma once

extern size_t FIELD_SIZE;

enum class GameState : int
{
	IN_PROGRESS,
	HUMAN_WON,
	AI_WON,
	DRAW
};

enum class GameCharsNum : int
{
	EMPTY,
	CROSS,
	ZERO,
	MAX
};

const char GameChars[]{ ' ','X','O' };

enum class Players : int
{
	HUMAN,
	AI
};

struct Coord
{
	size_t X{};
	size_t Y{};
};

struct Cell
{
	GameCharsNum gameChar;
};

class Player
{
public:
	Player() = default;

	Player(const std::string& name, GameCharsNum ch) : 
		gameChar(ch),
		Name(name)
	{}

	bool CheckBusy(Coord coord, Cell* field[]);
	virtual Coord GetCoord(Cell* field[], GameCharsNum human) = 0;

public:
	std::string Name{};
	GameCharsNum gameChar{ GameCharsNum::MAX };
	bool IsAI{};
};

class PlayerHuman : public Player
{
public:
	PlayerHuman(const std::string& name, GameCharsNum ch) : Player(name, ch) { IsAI = false; }

public:
	Coord GetCoord(Cell* field[], GameCharsNum human) override;
};

class PlayerAI : public Player
{
public:
	PlayerAI(const std::string& name, GameCharsNum ch) : Player(name, ch) { IsAI = true; }

public:
	Coord GetCoord(Cell* field[], GameCharsNum human) override;

	Coord MiniMax(Cell* field[], GameCharsNum human);
	int MaxSearch(Cell* field[], GameCharsNum human);
	int MinSearch(Cell* field[], GameCharsNum human);

};

class Game
{
public:
	~Game();

	void CreateField(size_t fieldSize);
	void DrawField();
	int Run();

private:
	char NumToChar(GameCharsNum num);
	GameCharsNum CharToNum(char ch);
	void ClearScreen() { system("cls"); }
	void Process();
	bool CheckForDraw();
	bool CheckForWon(GameCharsNum ch);

private:
	PlayerHuman Human{ "Human", GameCharsNum::CROSS};
	PlayerAI AI{ "Computer", GameCharsNum::ZERO};
	Cell** Field{};
	GameState gameState{ GameState::IN_PROGRESS };
	Players Turn{};
};

