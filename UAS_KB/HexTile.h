#pragma once
#include "Game.h"
#include "Animation.h"

namespace UAS_KB
{
	class HexTile
	{
	private:
		GameDataRef m_data;

		sf::Texture m_texture;
		sf::Sprite m_sprite;

		Animation anim;
		bool visited = false;
		bool clicked = false;
		int status = 0;	//0 = Gay, 1 = Blue, 2 = Red
	public:
		HexTile();
		virtual void VInit(GameDataRef data);
		virtual void VHandleInput();
		virtual void VDraw(float dt);
		virtual void VUpdate(float dt);
		virtual sf::Sprite& VGetSprite();
		void SetPosition(float x, float y);
		bool ClickBlue(int x, int y);
		bool ClickRed(int x, int y);
		void SetStatus(int status);
		int GetStatus();
		void SetVisited(bool b);
		bool IsVisited();

	};
}


