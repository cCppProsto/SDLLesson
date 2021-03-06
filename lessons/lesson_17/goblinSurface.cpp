#include <SDL2/SDL_image.h>

#include "goblinSurface.hpp"
#include "renderer.hpp"
                      
static std::string gs_sprite_path{"pics/goblin_all.png"};


static size_t dir_to_size_t(goblinSurface::eDirection aDirection)
{
  using dir = goblinSurface::eDirection;
  switch (aDirection)
  {
    case dir::Left:       { return static_cast<size_t>(dir::Left); }
    case dir::Left_Up:    { return static_cast<size_t>(dir::Left_Up); }
    case dir::Up:         { return static_cast<size_t>(dir::Up); }
    case dir::Up_Right:   { return static_cast<size_t>(dir::Up_Right); }
    case dir::Right:      { return static_cast<size_t>(dir::Right); }
    case dir::Right_Down: { return static_cast<size_t>(dir::Right_Down); }
    case dir::Down:       { return static_cast<size_t>(dir::Down); }
    case dir::Down_Left:  { return static_cast<size_t>(dir::Down_Left); }
  }
  return 0;
}

//------------------------------------------------------------------------------
goblinSurface::goblinSurface()
{
}
//------------------------------------------------------------------------------
goblinSurface::~goblinSurface()
{
  _free();
}
//------------------------------------------------------------------------------
void goblinSurface::handleEvent(SDL_Event &aEvent)
{
  switch (aEvent.type)
  {
    case SDL_MOUSEMOTION:
    {
      int x, y;
      SDL_GetMouseState(&x, &y);
      
      if (x >= m_x && x <= m_x_right)
      {
        if (y >= m_y && y <= m_y_down)
        {
          move();
          break;
        }
      }
      stop();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void goblinSurface::draw() const
{
  SDL_Rect renderQuad = { m_x, m_y, static_cast<int>(m_width), static_cast<int>(m_height) };

  SDL_RenderCopy(renderer::sdl_renderer(), mp_texture, mp_current_rect, &renderQuad);
}
//------------------------------------------------------------------------------
void goblinSurface::process()
{
  if (m_is_attack)
  {
    m_frame_count++;
    if (m_frame_count >= 10)
    {
      if (m_current_frame < 4 || m_current_frame == 7)
        m_current_frame = 3;

      mp_current_rect = &(_get_rects(m_direction))[m_current_frame];

      m_frame_count = 0;
      m_current_frame++;
      if (m_current_frame >= 7)
      {
        m_is_attack = false;
        m_current_frame = 0;
      }
    }
  }
  else if (m_is_moving)
  {
    m_frame_count++;
    if (m_frame_count >= 10)
    {
      m_current_frame++;
      if (m_current_frame >= 4)
        m_current_frame = 0;

      mp_current_rect = &(_get_rects(m_direction))[m_current_frame];

      m_frame_count = 0;
    }
  }
  else
    mp_current_rect = &(_get_rects(m_direction))[7];
}
//------------------------------------------------------------------------------
void goblinSurface::setDirection(eDirection aDirection)
{
  m_direction = aDirection;
}
//------------------------------------------------------------------------------
void goblinSurface::setPosition(int aX, int aY)
{
  m_x = aX;
  m_y = aY;
  _update_geometry_values();
}
//------------------------------------------------------------------------------
void goblinSurface::move()
{
  if (!m_is_moving)
    m_is_moving = true;
}
//------------------------------------------------------------------------------
void goblinSurface::stop()
{
  if (m_is_moving)
  {
    m_is_moving = false;
    m_current_frame = 7;
    m_frame_count = 0;
  }
}
//------------------------------------------------------------------------------
void goblinSurface::attack()
{
  if (!m_is_attack)
    m_is_attack = true;
}
//------------------------------------------------------------------------------
void goblinSurface::loadTexture()
{
  m_data_is_loaded = false;
  _free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(gs_sprite_path.c_str());

  if (loadedSurface == nullptr)
    return;

  newTexture = SDL_CreateTextureFromSurface(renderer::sdl_renderer(), loadedSurface);
  if (newTexture == nullptr)
  {
    SDL_FreeSurface(loadedSurface);
    return;
  }

  m_width = 256;
  m_height = 256;
  _update_geometry_values();
  m_frame_count = 8;

  mv_sprite_rects.resize(8);

  int x = 0;
  int y = 0;
  _get_rects(eDirection::Left).resize(8);
  for (auto & r : _get_rects(eDirection::Left))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Left_Up).resize(8);
  for (auto & r : _get_rects(eDirection::Left_Up))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Up).resize(8);
  for (auto & r : _get_rects(eDirection::Up))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Up_Right).resize(8);
  for (auto & r : _get_rects(eDirection::Up_Right))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Right).resize(8);
  for (auto & r : _get_rects(eDirection::Right))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Right_Down).resize(8);
  for (auto & r : _get_rects(eDirection::Right_Down))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Down).resize(8);
  for (auto & r : _get_rects(eDirection::Down))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  x = 0;
  y += 256;
  _get_rects(eDirection::Down_Left).resize(8);
  for (auto & r : _get_rects(eDirection::Down_Left))
  {
    r.x = x;
    r.y = y;
    r.w = m_width;
    r.h = m_height;
    x += m_width;
  }

  m_direction = eDirection::Up;
  m_current_frame = 7;
  mp_current_rect = &(_get_rects(m_direction))[m_current_frame];

  mp_texture = newTexture;
  SDL_FreeSurface(loadedSurface);

  m_data_is_loaded = true;
}
//------------------------------------------------------------------------------
const int &goblinSurface::x()const
{
  return m_x;
}
//------------------------------------------------------------------------------
const int &goblinSurface::y()const
{
  return m_y;
}
//------------------------------------------------------------------------------
const int &goblinSurface::x_center()const
{
  return m_x_center;
}
//------------------------------------------------------------------------------
const int &goblinSurface::y_center()const
{
  return m_y_center;
}
//------------------------------------------------------------------------------
const int &goblinSurface::x_right()const
{
  return m_x_right;
}
//------------------------------------------------------------------------------
const int &goblinSurface::y_down()const
{
  return m_y_down;
}
//------------------------------------------------------------------------------
const size_t &goblinSurface::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const size_t &goblinSurface::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
void goblinSurface::_free()
{
  if(mp_texture != nullptr)
    SDL_DestroyTexture(mp_texture);
  mp_texture = nullptr;
  m_width = 0;
  m_height = 0;
}
//------------------------------------------------------------------------------
std::vector<SDL_Rect> &goblinSurface::_get_rects(eDirection aDirection)
{
  size_t index = dir_to_size_t(aDirection);
  return mv_sprite_rects[index];
}
//------------------------------------------------------------------------------
void goblinSurface::_update_geometry_values()
{
  m_x_right = m_width + m_x;
  m_y_down = m_height + m_y;
  m_x_center = m_x + m_width  / 2;
  m_y_center = m_y + m_height / 2;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

