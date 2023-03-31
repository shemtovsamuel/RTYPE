#pragma once

namespace rtype
{
      class Game;

      namespace debug
      {
            class Debugger
            {
            public:
                  static Debugger &getInstance()
                  {
                        static Debugger instance;
                        return instance;
                  }

                  bool getShowHitbox() const;

                  bool hasComponents(rtype::Game &game, int id);

                  void calculateNumberOfActiveEntities(rtype::Game &game);

                  void update(rtype::Game &game);
                  void draw(rtype::Game &game);

                  void drawEntityWindow(rtype::Game &game);

            private:
                  Debugger() {}
                  Debugger(const Debugger &) = delete;
                  Debugger &operator=(const Debugger &) = delete;

                  int _numberOfActiveEntities = 0;

                  bool _showEntityWindow = false;
                  bool _showHitbox = false;

                  int _selectedEntity = -1;
                  int _selectedComponent = -1;
            };
      }
}