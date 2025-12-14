#include "game.h"
#include "resource_manager.h"
#include "shader.h"
#include "sprite_renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>

namespace core {

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height) {}

Game::~Game() {}

void Game::Init() {
  ResourceManager::LoadShader(SHADER_PATH "/sprite.vs",
                              SHADER_PATH "/sprite.fs", nullptr, "sprite");
  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height),
                 0.0f, -1.0f, 1.0f);
  Shader* shader = ResourceManager::GetShader("sprite");
  shader->Use().SetInteger("image", 0);
  shader->Use().SetMatrix4("projection", projection);

  renderer = new SpriteRenderer(*shader);

  ResourceManager::LoadTexture(TEXTURE_PATH "/awesomeface.png", true, "face");
}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {}

void Game::Render() {
  renderer->DrawSprite(*ResourceManager::GetTexture("face"),
                       glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                       45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
}  // namespace core