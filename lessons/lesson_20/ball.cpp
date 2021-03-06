#include <SDL_image.h>
#include <ctime>

#include "sdlengine.hpp"
#include "ball.hpp"

//------------------------------------------------------------------------------
ball::ball()
{
  _load_texture();

  const auto &sw{ SDLEngine::instance().windowWidth() };
                                                        
  m_speed = ( sw / 640.f ) * 1.f;
  m_dx = m_dx * m_speed;
  m_dy = m_dy * m_speed;

  std::srand(unsigned(std::time(0)));
  
  if (std::rand() & 0x01)
    m_dx = m_dx * -1;

  if (std::rand() & 0x01)
    m_dy = m_dy * -1;
}
//------------------------------------------------------------------------------
ball::~ball()
{
}
//------------------------------------------------------------------------------
void ball::set_position(float aX, float aY)
{
  m_x = aX;
  m_y = aY;
}
//------------------------------------------------------------------------------
void ball::move()
{
  const auto &sw{ SDLEngine::instance().windowWidth() };
  const auto &sh{ SDLEngine::instance().windowHeight() };

  if ((m_x < 0) || (m_x + m_width > sw))
  {
    m_dx = m_dx * -1.f;
  }
  else
  if ((m_y < 0.f) || (m_y + m_height > sh))
  {
    m_dy = m_dy * -1.f;
  }
  else
  if(_is_collision_with_horizontal_block())
  {
    SDLEngine::instance().play_game_ball_block_collision();
    m_dy = m_dy * -1.f;
  }
  else 
  if(_is_collision_with_vertical_block())
  {
    SDLEngine::instance().play_game_ball_block_collision();
    m_dx = m_dx * -1.f;
  }

  m_x += m_dx;
  m_y += m_dy;
}
//------------------------------------------------------------------------------
bool ball::_is_collision_with_horizontal_block()
{
  float ball_l{ m_x };
  float ball_r{ m_x + m_width };
  float ball_t{m_y};
  float ball_b{m_y + m_height};

  for (const auto &b : mvp_h_blocks)
  {
    float block_l{ b->x() };
    float block_r{ b->x() + b->width() };
    float block_t{ b->y() };
    float block_b{ b->y() + b->height() };

    if (block_b <= ball_t)
    {
      continue;
    }
    else
    if (block_t >= ball_b)
    {
      continue;
    }
    else
    if (block_r <= ball_l)
    {
      continue;
    }
    else
    if (block_l >= ball_r)
    {
      continue;
    }
    else
    {
      return true;
    }
  }
  return false;
}
//------------------------------------------------------------------------------
bool ball::_is_collision_with_vertical_block()
{
  for (const auto &b : mvp_v_blocks)
  {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = b->x();
    rightA = b->x() + b->width();
    topA = b->y();
    bottomA = b->y() + b->height();

    leftB = m_x;
    rightB = m_x + m_width;
    topB = m_y;
    bottomB = m_y + m_height;

    if (bottomA <= topB)
    {
      continue;
    }
    else
      if (topA >= bottomB)
      {
        continue;
      }
      else
        if (rightA <= leftB)
        {
          continue;
        }
        else
          if (leftA >= rightB)
          {
            continue;
          }
          else
          {
            return true;
          }
  }
  return false;
}
//------------------------------------------------------------------------------
const int &ball::x()const
{
  return m_x;
}
//------------------------------------------------------------------------------
const int &ball::y()const
{
  return m_y;
}
//------------------------------------------------------------------------------
const int &ball::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const int &ball::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
void ball::draw()
{
  SDL_Rect renderQuad = { m_x, m_y, static_cast<int>(m_width), static_cast<int>(m_height) };
  SDL_RenderCopy(SDLEngine::instance().renderer(), mp_texture, nullptr, &renderQuad);
}
//------------------------------------------------------------------------------
void ball::add_horizontal_block(const block &aBlock)
{
  mvp_h_blocks.push_back(&aBlock);
}
//------------------------------------------------------------------------------
void ball::add_vertical_block(const block &aBlock)
{
  mvp_v_blocks.push_back(&aBlock);
}
//------------------------------------------------------------------------------
void ball::_load_texture()
{
  _free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load("resources/pics/ball_hight_resolution.png");
  if (loadedSurface == nullptr)
  {
  }
  else
  {
    newTexture = SDL_CreateTextureFromSurface(SDLEngine::instance().renderer(), loadedSurface);
    if (newTexture == nullptr)
    {
    }
    else
    {
      m_original_width = static_cast<size_t>(loadedSurface->w);
      m_original_height = static_cast<size_t>(loadedSurface->h);
    }

    SDL_FreeSurface(loadedSurface);
  }

  m_width = SDLEngine::instance().windowWidth() / 50;
  m_height = SDLEngine::instance().windowHeight() / 50;

  mp_texture = newTexture;
}
//------------------------------------------------------------------------------
void ball::_free()
{
  if (mp_texture != nullptr)
  {
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
    m_original_width = 0;
    m_original_height = 0;
  }
}

