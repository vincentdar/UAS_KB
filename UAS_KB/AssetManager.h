#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

namespace UAS_KB
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
		std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	public:
		~AssetManager();

		void LoadTexture(std::string name, std::string fileName);
		sf::Texture& GetTexture(std::string name);
		void RemoveTexture(std::string name);

		void LoadFonts(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);
		void RemoveFont(std::string name);

		void LoadSoundBuffer(std::string name, std::string fileName);
		sf::SoundBuffer& GetSoundBuffer(std::string name);
		void RemoveSoundBuffer(std::string name);

	};
}

