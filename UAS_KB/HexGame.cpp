#include "HexGame.h"
#include <float.h>

namespace UAS_KB
{
	HexGame::HexGame(GameDataRef data): m_data(data)
	{
		
	}
	HexGame::~HexGame()
	{
		//Safely delete manually allocated memory
		DestroyBoard();
	}
	void HexGame::VInit()
	{		
		std::cout << "Abed beb" << std::endl;
		m_data->assets.LoadTexture("HexTile", HEX_TILESET);
		m_data->assets.LoadTexture("StartButton", UI_BUTTON_START);
		m_data->assets.LoadTexture("RestartButton", UI_BUTTON_RESTART);
		m_data->assets.LoadTexture("BackButton", UI_BUTTON_BACK);

		//Start to create board
		CreateBoard();

		startButton.VInit(m_data, sf::Vector2f(10, 600), 0.4f, "StartButton");
		restartButton.VInit(m_data, sf::Vector2f(120, 650), 0.2f, "RestartButton");
		exitButton.VInit(m_data, sf::Vector2f(175, 650), 0.2f, "BackButton");
	}
	void HexGame::VDraw(float dt)
	{
		m_data->window.clear(backgroundColor);
		// Draw Disini
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				m_data->window.draw(board[i][j].VGetSprite());
			}
		}
		//Draw UI
		m_data->window.draw(startButton.VGetSprite());
		m_data->window.draw(restartButton.VGetSprite());
		m_data->window.draw(exitButton.VGetSprite());
		m_data->window.display();
	}
	void HexGame::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			//Input khusus State HexGame disini
			
				if (sf::Event::Closed == event.type)
				{
					this->VExit();
					this->m_data->window.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					this->VExit();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
				{
					displayBoard = true;
				}
			if (!isUpdate && !isOver)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					bool isClicked = false;
					sf::Vector2i localPosition = sf::Mouse::getPosition(m_data->window);
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							isClicked = board[i][j].ClickBlue(localPosition.x, localPosition.y);
							if (isClicked)
							{
								status = 1;
							}
						}
					}
					if (condition())	//just true and false
					{
						std::cout << "Permainan Berakhir";
					};
					//Check if it presses UI button
					startButtonClicked = startButton.OnClicked(true, localPosition.x, localPosition.y);
					restartButtonClicked = restartButton.OnClicked(true, localPosition.x, localPosition.y);
					exitButtonClicked = exitButton.OnClicked(true, localPosition.x, localPosition.y);
				}
			}
			
			//if (event.mouseButton.button == sf::Mouse::Right)
			//{
			//	sf::Vector2i localPosition = sf::Mouse::getPosition(m_data->window);
			//	//std::cout << "x: " << localPosition.x << " y: " << localPosition.y << std::endl;
			//	for (int i = 0; i < size; i++)
			//	{
			//		for (int j = 0; j < size; j++)
			//		{
			//			board[i][j].ClickRed(localPosition.x, localPosition.y);
			//		}
			//	}
			//	if (condition())//just true and false
			//	{
			//		std::cout << "Permainan Berakhir";
			//	};
			//}
			
		}
	}
	void HexGame::VUpdate(float dt)
	{
		isUpdate = true;
		if (exit)
		{
			VExit();
			return;
		}
		//Update Board
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				board[i][j].VUpdate(dt);
			}
		}
		if (displayBoard)
		{
			DisplayBoardStatus();
			displayBoard = false;
		}
		if (status == 1)
		{
			if (!IsBoardFull())
			{
				std::cout << "Computer Turns" << std::endl;
				int moveValue = INT_MAX;
				int bestValue = INT_MIN;
				int bestValue_row = -1;
				int bestValue_col = -1;
				//Parent of Alpha Beta Minimax, AI Starts here
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						if (board[i][j].GetStatus() == 0)
						{
							//Minimax Starts here
							board[i][j].SetStatus(2);
							moveValue = Minimax(1, false, INT_MIN, INT_MAX);
							board[i][j].SetStatus(0);
							std::cout << "Row: " << i << " Col: " << j << " Value: " << moveValue << std::endl;
							//Find the best value
							if (moveValue > bestValue)
							{
								bestValue = moveValue;
								bestValue_row = i;
								bestValue_col = j;
							}
						}
					}
				}
				//std::cout << "Row: " << bestValue_row << " Col: " << bestValue_col << std::endl;
				board[bestValue_row][bestValue_col].SetStatus(2);
				status = 0;
				std::cout << "Global Count: " << globalCount << std::endl;
				globalCount = 0;
			}
			
		}
		//UPDATE START BUTTON
		if (startButtonClicked)
		{
			UIStart();
			startButtonClicked = false;
		}
		//UPDATE RESTART BUTTON
		if (restartButtonClicked)
		{
			UIRestart();
			restartButtonClicked = false;
		}
		//UPDATE EXIT BUTTON
		if (exitButtonClicked)
		{
			UIExit();
			exitButtonClicked = false;
		}
		isUpdate = false;

	}
	void HexGame::VResume()
	{
	}
	void HexGame::VPause()
	{
	}
	void HexGame::VExit()
	{
		m_data->machine.RemoveState();
	}
	void HexGame::CreateBoard()
	{
		//Create Object
		board = new HexTile* [size];
		for (int i = 0; i < size; i++)
		{
			board[i] = new HexTile[size];
		}

		//VInit
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				board[i][j].VInit(m_data);
			}
		}
		//Position to make a grid
		float x = SCREEN_WIDTH / 32;
		float y = SCREEN_HEIGHT / 6;
		int offset = 0;
		
		for (int i = 0; i < size; i++)
		{
			x = SCREEN_WIDTH / 32 + offset;
			for (int j = 0; j < size; j++)
			{
				board[i][j].SetPosition(x, y);
				x += 60;
			}
			y += 39;
			offset += 30;
		}
	}
	void HexGame::DestroyBoard()
	{
		//Clean up
		for (int i = 0; i < size; i++)
		{
			delete[] board[i];
		}
		delete[] board;
	}
	void HexGame::DisplayBoardStatus()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				std::cout << board[i][j].GetStatus() << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		/*CheckBoardCondition();*/
		std::cout << std::endl;
	}
	int  HexGame::CheckBoardCondition()
	{
		//Check if board is touching the top and bottom boundaries
		//top boundaries
		for (int i = 0; i < size; i++)
		{
			if (board[0][i].GetStatus() == 1)
			{
				Node* first = new Node();
				first->i = 0;
				first->j = i;
				first->parent;
				board[first->i][first->j].SetVisited(true);
				int res = RecurseCheck(first, 1);
				board[first->i][first->j].SetVisited(false);
				if (res == 1)
				{
					//std::cout << "Connected" << std::endl;
					delete first;
					return 1;
				}
				else
				{
					//std::cout << "Disconnected For Blue" << std::endl;
				}
				delete first;
			}
		}
		//Check if board is touching the top and bottom boundaries
		//left boundaries
		for (int i = 0; i < size; i++)
		{
			if (board[i][0].GetStatus() == 2)
			{
				Node* first = new Node();
				first->i = i;
				first->j = 0;
				first->parent;
				board[first->i][first->j].SetVisited(true);
				int res = RecurseCheck(first, 2);
				board[first->i][first->j].SetVisited(false);
				if (res == 1)
				{
					//std::cout << "Connected" << std::endl;
					delete first;
					return 2;
				}
				else
				{
					//std::cout << "Disconnected For Red" << std::endl;
					
				}
				delete first;
			}
		}
		return 3;
	}
	bool HexGame::condition()
	{
		int i = CheckBoardCondition();
		if (i == 1)
		{
			std::cout << "Biru Menang\n";
			std::string pharse = "Blue Win";
			std::string command = "espeak \"" + pharse + "\"";
			const char* charCommand = command.c_str();
			system(charCommand);
			isOver = true;

			return true;
		}
		if (i == 2)
		{
			std::string pharse = "Yellow Win";
			std::string command = "espeak \"" + pharse + "\"";
			const char* charCommand = command.c_str();
			system(charCommand);
			std::cout << "Kuning Menang\n";
			isOver = true;

			return true;
		}
		if (i == 3)
		{
			std::cout << "Waiting....\n";
			return false;
		}
		return false;
	}
	bool HexGame::IsValidIndex(int x, int y, int dir_x, int dir_y)
	{
		if ((x + dir_x >= 0 && x + dir_x < size) && (y + dir_y >= 0 && y + dir_y < size))
		{
			return true;
		}
		return false;
	}
	bool HexGame::IsBoardFull() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j].GetStatus() == 0) {
					return false;
				}
			}
		}
		return true;
	}
	std::vector<Node> HexGame::GetPossibleMoves()
	{
		std::vector<Node> possibleMoves;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j].GetStatus() == 0) {
					Node lul;
					lul.i = i;
					lul.j = j;
					possibleMoves.push_back(lul);
				}
			}
		}
		return possibleMoves;
	}

	int HexGame::Max(int a, int b)
	{
		if (a > b)
		{
			return a;
		}
		return b;
	}

	int HexGame::Min(int a, int b)
	{
		if (a < b)
		{
			return a;
		}
		return b;
	}
	
	/*int HexGame::getHeuristicScore(int score,int count)
	{
		int retreivedScore = transposTable
	}*/
	int HexGame::Minimax(int depth, bool isComputerTurn, int alpha, int beta)	//1 node sendiri
	{
		globalCount++;
		//Evaluate Board
		if (depth == 7) {
			return EvaluateBoard();
		}
		
		int score = EvaluateBoard();

		
		//Transposition 
		
		

		
		//Computer Wins
		if (score == 10)
		{
			//std::cout << "SCORE 10 depth: " << depth << std::endl;
			return score - depth;	
		}

		//Human Wins
		if (score == -10)
		{
			//std::cout << "SCORE -10 depth: " << depth << std::endl;
			return score + depth;
		}

		//Check Available Moves
		if (IsBoardFull())
		{
			//Tie
			return 0;
		}
		
		int bestValue = 0;

		if (isComputerTurn) 
		{
			bestValue = INT_MIN;
			bool cut = false;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (board[i][j].GetStatus() == 0)
					{
						int eval = 0;
						board[i][j].SetStatus(2);
						eval = Minimax(depth + 1, false, alpha, beta);
						board[i][j].SetStatus(0);
						bestValue = Max(bestValue, eval);
						alpha = Max(alpha, eval);
						if (beta <= alpha)
						{
							cut = true;
						}
					}
					if (cut)
					{
						break;
					}
				}
				if (cut)
				{
					break;
				}
			}
		}
		else 
		{
			bestValue = INT_MAX;
			bool cut = false;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (board[i][j].GetStatus() == 0)
					{
						int eval = 0;
						board[i][j].SetStatus(1);
						eval = Minimax(depth + 1, true, alpha, beta);
						board[i][j].SetStatus(0);
						bestValue = Min(bestValue, eval);
						beta = Min(beta, eval);
						if (beta <= alpha)
						{
							cut = true;
						}
					}
					if (cut)
					{
						break;
					}
				}
				if (cut)
				{
					break;
				}
			}
		}
		return bestValue;
	}

	int HexGame::EvaluateBoard()
	{
		int eval = CheckBoardCondition();
		if (eval == 1)
		{
			return -10;
		}
		else if (eval == 2)
		{
			return 10;
		}
		return 0;
	}

	int HexGame::RecurseCheck(Node* parent, int status)
	{
		//std::cout << parent->i << " " << parent->j << std::endl;
		if (status == 1)
		{
			if (parent->i == size - 1)
			{
				return 1;
			}
		}
		else if (status == 2)
		{
			if (parent->j == size - 1)
			{
				return 1;
			}
		}
		
		
		
		for (int i = 0; i < 6; i++)
		{
			if (IsValidIndex(parent->i, parent->j, direction[i][0], direction[i][1]))
			{
				if (board[parent->i + direction[i][0]][parent->j + direction[i][1]].GetStatus() == status)
				{
					if (board[parent->i + direction[i][0]][parent->j + direction[i][1]].IsVisited() == false)
					{
						Node* node = new Node();
						node->i = parent->i + direction[i][0];
						node->j = parent->j + direction[i][1];
						node->parent = parent;
						board[node->i][node->j].SetVisited(true);
						int res = RecurseCheck(node, status);
						board[node->i][node->j].SetVisited(false);
						if (res == 1)
						{
							return 1;
						}
						delete node;
					}
				}
				
			}
		}
		return 0;
	}
	void HexGame::UIStart()
	{
		std::cout << "FUNCTION UI START" << std::endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{

			}
		}
	}
	void HexGame::UIRestart()
	{
		std::cout << "FUNCTION UI RESTART" << std::endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				board[i][j].SetStatus(0);
			}
		}
	}
	void HexGame::UIExit()
	{
		std::cout << "FUNCTION UI EXIT" << std::endl;
		exit = true;
	}

}