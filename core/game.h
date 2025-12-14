#ifndef GAME_H
#define GAME_H

#include "sprite_renderer.h"

namespace core {
enum GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Game {
 public:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  GameState state;
  bool keys[1024];
  unsigned int width, height;

  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();

  void ProcessInput(float dt);
  void Update(float dt);
  void Render();

 private:
  SpriteRenderer* renderer;
};
}  // namespace core

#endif