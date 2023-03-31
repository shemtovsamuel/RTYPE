#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace rtype
{
	/**
	 * @brief AssetManager class which allows you to load the assets only once
	 * 
	 */
	class AssetManager
	{
	public:
		/**
		 * @brief Get the Instance object
		 * 
		 * @return AssetManager& 
		 */
		static AssetManager &getInstance()
		{
			static AssetManager instance;
			return instance;
		}

		/**
		 * @brief Get the Texture object
		 * 
		 * @param textureName 
		 * @return sf::Texture& 
		 */
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

		/**
		 * @brief Get the Sound Buffer object
		 * 
		 * @param soundName 
		 * @return sf::SoundBuffer& 
		 */
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

		/**
		 * @brief Get the Sound object
		 * 
		 * @param soundName 
		 * @return sf::Sound& 
		 */
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

		/**
		 * @brief Play the sound
		 * 
		 * @param soundName 
		 */
		void playSound(const std::string &soundName)
		{
			getSound(soundName).play();
		}

	private:
		/**
		 * @brief Construct a new Asset Manager object with all the textures and sounds
		 * 
		 */
		AssetManager()
		{
			addTexture("r-typesheet43", "./assets/sprites/r-typesheet43.png");
			addTexture("r-typesheet42", "./assets/sprites/r-typesheet42.png");
			addTexture("r-typesheet30", "./assets/sprites/r-typesheet30.png");
			addTexture("r-typesheet32", "./assets/sprites/r-typesheet32.png");
			addTexture("r-typesheet39", "./assets/sprites/r-typesheet39.png");
			addTexture("r-typesheet31", "./assets/sprites/r-typesheet31.png");
			addTexture("r-typesheet22", "./assets/sprites/r-typesheet22.png");
			addTexture("r-typesheet23", "./assets/sprites/r-typesheet23.png");
			addTexture("r-typesheet13", "./assets/sprites/r-typesheet13.png");
			addTexture("r-typesheet37", "./assets/sprites/r-typesheet37.png");
			addTexture("r-typesheet1", "./assets/sprites/r-typesheet1.png");
			addTexture("background", "./assets/sprites/parallax/background.png");
			addTexture("stars", "./assets/sprites/parallax/stars.png");
			addTexture("stones", "./assets/sprites/parallax/stones.png");
			addTexture("planet1", "./assets/sprites/parallax/planet1.png");
			addTexture("planet2", "./assets/sprites/parallax/planet2.png");

			addSound("shoot", "./assets/sounds/shoot.wav");
			addSound("special-shoot", "./assets/sounds/special-shoot.wav");
		}
		AssetManager(const AssetManager &) = delete;
		AssetManager &operator=(const AssetManager &) = delete;

		/**
		 * @brief Add a texture
		 * 
		 * @param textureName 
		 * @param texturePath 
		 */
		void addTexture(std::string textureName, std::string texturePath)
		{
			sf::Texture texture;
			texture.loadFromFile(texturePath);
			_textures[textureName] = texture;
		}

		/**
		 * @brief Add a sound
		 * 
		 * @param soundName 
		 * @param soundPath 
		 */
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