#pragma once

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

#include <iostream>

#include "FastNoiseLite.hpp"

namespace factorio
{
    namespace map
    {
        // Define the structure of a tile entity
        struct Tile {
            int groundType;
            int resourceType;
            int x;
            int y;
        };

        // Define the structure of a world entity
        struct World {
            std::vector<Tile> tiles;
        };

        class MapGenerator
        {
        public:
            MapGenerator() {
                srand(time(NULL)); // Seed the random number generator
            }

            World generateMap() {
                // Initialize FastNoiseLite
                noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
                noise.SetSeed(rand());
                noise.SetFrequency(0.02f);
                noise.SetFractalOctaves(octaves);
                noise.SetFractalLacunarity(lacunarity);
                noise.SetFractalGain(0.5f);

                World world;
                world.tiles.reserve(width * height);

                // Generate tiles
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        Tile tile;
                        tile.x = x;
                        tile.y = y;
                        tile.groundType = GetGroundType(x, y);
                        tile.resourceType = GetResourceType(x, y);

                        if (tile.groundType == 0)
                            tile.resourceType = 0;

                        // if the tile got a resource, check the sorrounding tiles to see if they have the same resource
                        if (tile.resourceType != 0) {
                            for (int i = -1; i <= 1; i++) {
                                for (int j = -1; j <= 1; j++) {
                                    if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height) {
                                        if (world.tiles[(y + j) * width + (x + i)].resourceType != tile.resourceType
                                            && world.tiles[(y + j) * width + (x + i)].resourceType != 0 && tile.resourceType != 0) {
                                            tile.resourceType = world.tiles[(y + j) * width + (x + i)].resourceType;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        

                        world.tiles.push_back(tile);
                    }
                }

                return world;
            }

            World world;
            int octaves = 4;
            float lacunarity = 2.0f;
            float amplitude = 1.0f;
            float bias = 2.0f;
            int width = 100;
            int height = 100;
        private:
            FastNoiseLite noise;

             int GetGroundType(int x, int y) {
                float value = noise.GetNoise((float)x, (float)y) * amplitude;
                value += noise.GetNoise((float)x * 2, (float)y * 2) * amplitude * 0.5f;
                value += noise.GetNoise((float)x * 4, (float)y * 4) * amplitude * 0.25f;
                value += noise.GetNoise((float)x * 8, (float)y * 8) * amplitude * 0.125f;
                value = std::max(0.0f, std::min(1.0f, (value + 1.0f) / 2.0f)); // Normalize the value to [0, 1]
                if (value < 0.3f) {
                    return 0; // Water
                }
                else if (value < 0.4f) {
                    return 1; // Sand
                }
                else {
                    return 2; // Grass
                }
            }

            int GetResourceType(int x, int y) {
                float value = noise.GetNoise((float)x, (float)y) * amplitude * 0.5f;
                value += noise.GetNoise((float)x * 4, (float)y * 4) * amplitude * 0.25f;
                value = std::max(0.0f, std::min(1.0f, (value + 1.0f) / 2.0f)); // Normalize the value to [0, 1]
                if (value < 0.8f) {
                    return 0; // No resource
                }
                else if (value < 0.9f) {
                    return rand() % 2 + 1; // Iron or copper
                } else {
                    return 0; // No resource
                }
            }
        };
    }
}