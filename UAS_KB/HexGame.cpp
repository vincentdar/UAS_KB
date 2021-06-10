#include "HexGame.h"

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

		//Start to create board
		CreateBoard();
	}
	void HexGame::VDraw(float dt)
	{
		m_data->window.clear(sf::Color::Red);
		// Draw Disini
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				m_data->window.draw(board[i][j].VGetSprite());
			}
		}
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
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(m_data->window);
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						board[i][j].ClickBlue(localPosition.x, localPosition.y);
					}
				}
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(m_data->window);
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						board[i][j].ClickRed(localPosition.x, localPosition.y);
					}
				}
			}
		}
		//Polling input khusus Member Variable berupa Objek misal. m_hero.HandleInput()
	}
	void HexGame::VUpdate(float dt)
	{
		if (exit)
		{
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

		//TEMP
		/*for (int i = 0; i < 6; i++)
		{
			int x = 7;
			int y = size - 1;
			if (IsValidIndex(direction[i][0], direction[i][1], x, y))
			{
				board[direction[i][0] + x][direction[i][1] + y].SetStatus(1);
			}
		}*/
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
		CheckBoardCondition();
		std::cout << std::endl;
	}
	void HexGame::CheckBoardCondition()
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
				int res = RecurseCheck(first);
				board[first->i][first->j].SetVisited(false);
				if (res == 1)
				{
					std::cout << "Connected" << std::endl;
				}
				else
				{
					std::cout << "Disconnected" << std::endl;
				}
			}
		}
	}

	bool HexGame::IsValidIndex(int x, int y, int dir_x, int dir_y)
	{
		if ((x + dir_x >= 0 && x + dir_x < size) && (y + dir_y >= 0 && y + dir_y < size))
		{
			return true;
		}
		return false;
	}

	int HexGame::RecurseCheck(Node* parent)
	{
		if (parent->i == size - 1 || parent->j == size - 1)
		{
			return 1;
		}
		for (int i = 0; i < 6; i++)
		{
			if (IsValidIndex(parent->i, parent->j, direction[i][0], direction[i][1]))
			{
				if (board[parent->i + direction[i][0]][parent->j + direction[i][1]].GetStatus() == 1)
				{
					if (board[parent->i + direction[i][0]][parent->j + direction[i][1]].IsVisited() == false)
					{
						Node* node = new Node();
						node->i = parent->i + direction[i][0];
						node->j = parent->j + direction[i][1];
						node->parent = parent;
						board[node->i][node->j].SetVisited(true);
						int res = RecurseCheck(node);
						board[node->i][node->j].SetVisited(false);
						if (res == 1)
						{
							return 1;
						}
					}
				}
				
			}
		}
		return 0;
	}

}