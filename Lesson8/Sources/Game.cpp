#include "Lesson8PCH.h"

const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 Generator(static_cast<unsigned int>(seed));

size_t FIELD_SIZE = 3;

int GenerateRandomInt(int a, int b)
{
	return Generator() % (b - a + 1) + a;
}

bool Player::CheckBusy(Coord coord, Cell* field[])
{
	if (coord.X >= FIELD_SIZE || coord.Y >= FIELD_SIZE) {
		std::cout << "Error! Move out of range!" << std::endl;
		return false;
	}

	if (field[coord.X-1][coord.Y-1].gameChar != GameCharsNum::EMPTY) {
		std::cout << "Sorry! You can not move here! Cell is busy!" << std::endl;
		return false;
	}

	return true;
}


Game::~Game()
{
	for (auto i = 0; i < FIELD_SIZE; i++)
		delete[] Field[i];
	delete[] Field;
}

void Game::CreateField(size_t fieldSize)
{
	FIELD_SIZE = fieldSize;

	Field = new Cell * [FIELD_SIZE];
	for (auto i = 0; i < FIELD_SIZE; i++)
		Field[i] = new Cell[FIELD_SIZE];

	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE; x++) {
			Field[y][x].gameChar = GameCharsNum::EMPTY;
		}
	}

	if (GenerateRandomInt(0, 1000) > 500) {
		Human.gameChar = GameCharsNum::CROSS;
		AI.gameChar = GameCharsNum::ZERO;
	}
	else {
		Human.gameChar = GameCharsNum::ZERO;
		AI.gameChar = GameCharsNum::CROSS;
	}

	Turn = static_cast<Players>(GenerateRandomInt(0, 1));
}

void Game::DrawField()
{
	std::cout << std::endl << "     ";
	for (size_t x = 0; x < FIELD_SIZE; x++)
	{
		std::cout << x + 1 << "   ";
	}
	std::cout << std::endl;

	for (auto y = 0; y < FIELD_SIZE; y++) {
		std::cout << " " << y + 1 << " | ";
		for (auto x = 0; x < FIELD_SIZE; x++) {
			std::cout << NumToChar(Field[y][x].gameChar) << " | ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "   Human: " << NumToChar(Human.gameChar) << std::endl;
	std::cout << "Computer: " << NumToChar(AI.gameChar) << std::endl << std::endl;
}

char Game::NumToChar(GameCharsNum num)
{
	return GameChars[(int)num];
}

GameCharsNum Game::CharToNum(char ch)
{
	switch (ch) {
	case 'X': return GameCharsNum::CROSS;
	case ' ': return GameCharsNum::EMPTY;
	case 'O': return GameCharsNum::ZERO;
	}

	return GameCharsNum::MAX;
}

int Game::Run()
{
	bool done = false;
	do {
		switch (gameState)
		{
			case GameState::IN_PROGRESS:
				Process();
				ClearScreen();
				DrawField();
			break;
			case GameState::HUMAN_WON:
				std::cout << "Human won! 8=)" << std::endl;
				done = true;
			break;
			case GameState::AI_WON:
				std::cout << "Computer won! 8=)" << std::endl;
				done = true;
			break;
			case GameState::DRAW:
				std::cout << "Draw 8=/" << std::endl;
				done = true;
			break;
		}
	} while (done == false);

	return 0;
}

void Game::Process()
{
	if (Turn == Players::AI) {
		Coord c = AI.GetCoord(Field, Human.gameChar);
		Field[c.Y][c.X].gameChar = AI.gameChar;
		Turn = Players::HUMAN;
		if(CheckForWon(AI.gameChar))
			gameState = GameState::AI_WON;
		if(CheckForDraw())
			gameState = GameState::DRAW;
	}
	else {
		Coord c = Human.GetCoord(Field, Human.gameChar);
		Field[c.Y][c.X].gameChar = Human.gameChar;
		Turn = Players::AI;
		if (CheckForWon(Human.gameChar))
			gameState = GameState::HUMAN_WON;
		if (CheckForDraw())
			gameState = GameState::DRAW;
	}
}

bool Game::CheckForDraw()
{
	bool ret = true;

	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE - 1; x++) {
			if (Field[y][x].gameChar == GameCharsNum::EMPTY) {
				ret = false;
			}
		}
	}

	return ret;
}

bool Game::CheckForWon(GameCharsNum ch)
{
	int num = 0;
	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE - 1; x++) {
			if (Field[y][x].gameChar == Field[y][x + 1].gameChar && (Field[y][x].gameChar==ch && Field[y][x + 1].gameChar == ch))
				num++;
		}
		if (num == FIELD_SIZE - 1) {
			return true;
		}
		else
			num = 0;
	}
	num = 0;
	for (auto x = 0; x < FIELD_SIZE; x++) {
		for (auto y = 0; y < FIELD_SIZE - 1; y++) {
			if (Field[y][x].gameChar == Field[y + 1][x].gameChar && (Field[y][x].gameChar == ch && Field[y + 1][x].gameChar == ch))
				num++;
		}
		if (num == FIELD_SIZE - 1) {
			return true;
		}
		else
			num = 0;
	}

	num = 0;
	for (size_t x = 0, y = 0; x < FIELD_SIZE, y < FIELD_SIZE; x++, y++) {
		if (Field[y][x].gameChar == ch)
			num++;
	}
	if (num >= FIELD_SIZE)
		return true;

	num = 0;
	for (size_t x = FIELD_SIZE - 1, y = 0; x > 0, y < FIELD_SIZE; x--, y++) {
		if (Field[y][x].gameChar == ch)
			num++;
	}
	if (num >= FIELD_SIZE)
		return true;

	return false;
}

Coord PlayerHuman::GetCoord(Cell* field[], GameCharsNum human)
{
	Coord ret;

	do
	{
		std::cout << "Enter x: ";
		std::cin >> ret.X;
		std::cout << "Enter y: ";
		std::cin >> ret.Y;
		CheckBusy(ret, field);
	} while (ret.X == 0 || ret.Y == 0 || ret.X > FIELD_SIZE || ret.Y > FIELD_SIZE || field[ret.Y - 1][ret.X - 1].gameChar != GameCharsNum::EMPTY);

	ret.X--;
	ret.Y--;

	return ret;
}

Coord PlayerAI::GetCoord(Cell* field[], GameCharsNum human)
{
	if (FIELD_SIZE == 3) {
		return MiniMax(field, human);
	}

	size_t midX = static_cast<int>(FIELD_SIZE / 2);
	size_t midY = midX;

	std::unique_ptr<Coord[]> arr = std::make_unique<Coord[]>(FIELD_SIZE * FIELD_SIZE + 1);
	size_t num = 0;
	
	for (size_t y = 0; y < FIELD_SIZE; y++) {
		for (size_t x = 0; x < FIELD_SIZE; x++) {
			if (field[y][x].gameChar == GameCharsNum::EMPTY)
			{
				arr[num++] = { x, y };
			}
		}
	}
	if (num > 0)
	{
		const size_t index = GenerateRandomInt(0, 1000) % num;
		return arr[index];
	}

	return { midX, midY };
}

Coord PlayerAI::MiniMax(Cell* field[], GameCharsNum human)
{
	int bestMoveScore = 100; 
	Coord bestMove;

	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE; x++) {
			if (field[y][x].gameChar == GameCharsNum::EMPTY) {
				field[y][x].gameChar = gameChar;
				int tempMoveScore = MaxSearch(field, human);
				if (tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.X = x;
					bestMove.Y = y;
				}
				field[y][x].gameChar = GameCharsNum::EMPTY;
			}
		}
	}

	return bestMove;
}

int PlayerAI::MaxSearch(Cell* field[], GameCharsNum human)
{
	Coord bestMove;

	int bestMoveScore = -1000;
	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE; x++) {
			if (field[y][x].gameChar == GameCharsNum::EMPTY) {
				field[y][x].gameChar = human;
				int tempMoveScore = MinSearch(field, human);
				if (tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.X = x;
					bestMove.Y = y;
				}
				field[y][x].gameChar = GameCharsNum::EMPTY;
			}
		}
	}

	return bestMoveScore;
}

int PlayerAI::MinSearch(Cell* field[], GameCharsNum human)
{
	Coord bestMove;

	int bestMoveScore = 1000;
	for (auto y = 0; y < FIELD_SIZE; y++) {
		for (auto x = 0; x < FIELD_SIZE; x++) {
			if (field[y][x].gameChar == GameCharsNum::EMPTY) {
				field[y][x].gameChar = gameChar;
				int tempMove = MaxSearch(field, human);
				if (tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.X = x;
					bestMove.Y = y;
				}
				field[y][x].gameChar = GameCharsNum::EMPTY;
			}
		}
	}

	return bestMoveScore;
}
