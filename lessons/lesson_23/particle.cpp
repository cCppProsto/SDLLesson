#include "particle.hpp"

static size_t s_frame_count_for_dead{ 60 };
static bool s_texture_is_loaded{ false };

static const size_t s_texture_count{ 12 };
static texture s_textures[s_texture_count];
//------------------------------------------------------------------------------
particle::particle(int aX, int aY)
{
  if (!s_texture_is_loaded)
  {
    s_textures[0].load("resources/pics/red.png");
    s_textures[1].load("resources/pics/red_1.png");
    s_textures[2].load("resources/pics/red_2.png");
    s_textures[3].load("resources/pics/red_3.png");
    s_textures[4].load("resources/pics/red_4.png");
    s_textures[5].load("resources/pics/red_5.png");
    s_textures[6].load("resources/pics/yellow.png");
    s_textures[7].load("resources/pics/yellow_1.png");
    s_textures[8].load("resources/pics/yellow_2.png");
    s_textures[9].load("resources/pics/yellow_3.png");
    s_textures[10].load("resources/pics/yellow_4.png");
    s_textures[11].load("resources/pics/yellow_5.png");

    s_texture_is_loaded = true;
  }

  _init(aX, aY);
}
//------------------------------------------------------------------------------
particle::~particle()
{
}
//------------------------------------------------------------------------------
void particle::draw()
{
  if (m_is_dead)
    return;

  s_textures[m_index].setPosition(m_x, m_y);
  s_textures[m_index].set_alpha(m_alpha);
  s_textures[m_index].draw();

  m_alpha -= m_alpha_dx;
  m_frame++;

  if (m_frame > s_frame_count_for_dead)
    m_is_dead = true;
}
//------------------------------------------------------------------------------
void particle::reinit(int aX, int aY)
{
  _init(aX, aY);
}
//------------------------------------------------------------------------------
void particle::_init(int aX, int aY)
{
  if (m_frame < s_frame_count_for_dead)
    m_alpha = m_alpha;

  if(!m_is_dead)
    m_alpha = m_alpha;

  if (m_is_dead)
    m_alpha = m_alpha;

  m_x = aX - 5 + (rand() % 20);
  m_y = aY - 5 + (rand() % 20);

  m_is_dead = false;
  m_frame = rand() % 30;
  m_index = rand() % 12;
  m_alpha = 255;
  m_alpha_dx = 255 / (s_frame_count_for_dead - m_frame);
}
//------------------------------------------------------------------------------
bool particle::is_dead()
{
  return m_is_dead;
}
