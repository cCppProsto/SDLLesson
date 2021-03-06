
#include "sdlengine.hpp"
#include "dot.hpp"

static const char* s_path_texture{ "resources/pics/dot.png" };
static size_t s_particle_count{ 60 };

//------------------------------------------------------------------------------
dot::dot()
{
  m_dx = rand() % 2 ? 1 : -1;
  m_dy = rand() % 2 ? 1 : -1;

  m_particles.reserve(s_particle_count);
  for (int i = 0; i < s_particle_count; ++i)
    m_particles.push_back(particle(m_x - m_dx, m_y - m_dy));

  m_texture.load(s_path_texture);
}
//------------------------------------------------------------------------------
dot::~dot()
{
}
//------------------------------------------------------------------------------
void dot::draw()
{
  m_texture.setPosition(m_x, m_y);
  m_texture.draw();

  for (int i = 0; i < s_particle_count; ++i)
    m_particles[i].draw();
}
//------------------------------------------------------------------------------
void dot::move()
{
  if (m_x < 0 || m_x > SDLEngine::instance().windowWidth())
    m_dx *= -1;

  if (m_y < 0 || m_y > SDLEngine::instance().windowHeight())
    m_dy *= -1;

  m_x += m_dx;
  m_y += m_dy;

  for (int i = 0; i < s_particle_count; ++i)
  {
    if (m_particles[i].is_dead())
    {
        if (rand() % 4 == 1)
        {
          if (m_dx == 1 && m_dy == 1)
          {
            m_particles[i].reinit(m_x - m_dx, m_y - m_dy);
          }
          else
          if (m_dx == -1 && m_dy == -1)
          {
            m_particles[i].reinit(m_x + m_texture.width() - m_dx, m_y + m_texture.height() - m_dy);
          }
          else
          if (m_dx == 1 && m_dy == -1)
          {
            m_particles[i].reinit(m_x - m_dx, m_y + m_texture.height() - m_dy);
          }
          else
          if (m_dx == -1 && m_dy == 1)
          {
            m_particles[i].reinit(m_x + m_texture.width() - m_dx, m_y - m_dy);
          }
          break;
        }
    }
  }
}
