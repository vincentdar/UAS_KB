#pragma once
#include "IState.h"
#include "Game.h"
#include "HexTile.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

namespace UAS_KB
{
	class Node
	{
	public:
		//Index in BOARD
		int i;
		int j;

		//Pointer to other Nodes
		Node* parent;
		std::vector<Node*> nodes;

		bool AddNodes(Node* node)
		{
			if (node == parent)
			{
				return false;
			}
			nodes.push_back(node);
		}
	};

	class HexGame: public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;
		
		//Game Components
		HexTile** board;
		int direction[6][2] = { {0, -1}, {1 , -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1} };
		int size = 11;
		bool exit = false;
		bool displayBoard = false;

		//UI Components
		sf::Color backgroundColor = sf::Color(123, 129, 135);
		Button startButton;
		bool startButtonClicked = false;
		Button restartButton;
		bool restartButtonClicked = false;
		Button exitButton;
		bool exitButtonClicked = false;

	public:
		HexGame(GameDataRef data);
		~HexGame();
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
		void CreateBoard();
		void DestroyBoard();
		void DisplayBoardStatus();
		void CheckBoardCondition();
		bool IsValidIndex(int x, int y, int dir_x, int dir_y);
		int RecurseCheck(Node* parent, int status);

		//UI Function
		void UIStart();
		void UIRestart();
		void UIExit();
	};

}

