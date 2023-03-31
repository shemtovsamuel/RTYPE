#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace factorio
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
			addTexture("grass", "assets/grass-1.png");
			addTexture("sand", "assets/sand-1.png");
			addTexture("water", "assets/water-u.png");
			addTexture("copper", "assets/copper-ore.png");
			addTexture("iron", "assets/iron-ore.png");
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