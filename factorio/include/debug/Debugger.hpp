#pragma once


namespace factorio
{
      class GameState;

      namespace debug
      {
            class Debugger
            {
            public:
                  Debugger(factorio::GameState &gameState);
                  ~Debugger();

                  bool getShowHitbox() const;

                  bool hasComponents(int id);

                  void calculateNumberOfActiveEntities();

                  void update();
                  void draw();

                  void drawEntityWindow();
                  void drawMapWindow();

            private:
                  factorio::GameState &_gameState;

                  int _numberOfActiveEntities = 0;

                  bool _showEntityWindow = false;
                  bool _showHitbox = false;
                  bool _showMapWindow = false;

                  int _selectedEntity = -1;
                  int _selectedComponent = -1;
            };
      }
}