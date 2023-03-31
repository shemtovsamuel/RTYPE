#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace rtype
{
	class AssetManager
	{
	public:
		static AssetManager &getInstance()
		{
			static AssetManager instance;
			return instance;
		}

		sf::Texture &getTexture(const std::string &textureName)
		{
			auto it = _textures.find(textureName);
			if (it == _textures.end())
			{
				throw std::runtime_error("Texture not found: " + textureName);
			}
			else
			{
				return it->second;
			}
		}

		sf::SoundBuffer &getSoundBuffer(const std::string &soundName)
		{
			auto it = _soundsBuffer.find(soundName);
			if (it == _soundsBuffer.end())
			{
				throw std::runtime_error("Sound not found: " + soundName);
			}
			else
			{
				return it->second;
			}
		}

		sf::Sound &getSound(const std::string &soundName)
		{
			auto it = _sounds.find(soundName);
			if (it == _sounds.end())
			{
				throw std::runtime_error("Sound not found: " + soundName);
			}
			else
			{
				return it->second;
			}
		}

		void playSound(const std::string &soundName)
		{
			getSound(soundName).play();
		}

	private:
		AssetManager()
		{
			addTexture("r-typesheet43", "./assets/sprites/r-typesheet43.png");
			addTexture("r-typesheet42", "./assets/sprites/r-typesheet42.png");
			addTexture("r-typesheet30", "./assets/sprites/r-typesheet30.png");
			addTexture("r-typesheet13", "./assets/sprites/r-typesheet13.png");
			addTexture("bird", "./assets/sprites/bird.png");
			addTexture("backgroundFlappy", "./assets/sprites/parallax/backgroundFlappy.png");
			addTexture("building", "./assets/sprites/parallax/building.png");
			addTexture("bush", "./assets/sprites/parallax/bush.png");
			addTexture("cloud", "./assets/sprites/parallax/cloud.png");
			addTexture("ground", "./assets/sprites/parallax/ground.png");
			addTexture("obstacle1Top", "./assets/sprites/obstacle/obstacle1Top.png");
			addTexture("obstacle1Bottom", "./assets/sprites/obstacle/obstacle1Bottom.png");
			addTexture("obstacle2Top", "./assets/sprites/obstacle/obstacle2Top.png");
			addTexture("obstacle2Bottom", "./assets/sprites/obstacle/obstacle2Bottom.png");
			addTexture("obstacle3Top", "./assets/sprites/obstacle/obstacle3Top.png");
			addTexture("obstacle3Bottom", "./assets/sprites/obstacle/obstacle3Bottom.png");
			addTexture("gameOver", "./assets/sprites/gameOver.png");

			addSound("shoot", "./assets/sounds/shoot.wav");
		}
		AssetManager(const AssetManager &) = delete;
		AssetManager &operator=(const AssetManager &) = delete;

		void addTexture(std::string textureName, std::string texturePath)
		{
			sf::Texture texture;
			texture.loadFromFile(texturePath);
			_textures[textureName] = texture;
		}

		void addSound(std::string soundName, std::string soundPath)
		{
			sf::SoundBuffer soundBuffer;
			soundBuffer.loadFromFile(soundPath);
			_soundsBuffer[soundName] = soundBuffer;

			sf::Sound sound;
			sound.setBuffer(getSoundBuffer(soundName));
			_sounds[soundName] = sound;
		}

		std::unordered_map<std::string, sf::Texture> _textures;
		std::unordered_map<std::string, sf::SoundBuffer> _soundsBuffer;
		std::unordered_map<std::string, sf::Sound> _sounds;
	};
}