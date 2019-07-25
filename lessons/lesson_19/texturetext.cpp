
#include "sdlengine.hpp"
#include "texturetext.hpp"

//------------------------------------------------------------------------------
TextureText::TextureText()
{
}
//------------------------------------------------------------------------------
TextureText::~TextureText()
{
  _free();
}
//------------------------------------------------------------------------------
bool TextureText::loadFont(std::string path, int size /* = 24 */ )
{
  _free();

  mp_font = TTF_OpenFont(path.c_str(), size);

  if (mp_font == nullptr)
    m_last_error = TTF_GetError();

  return mp_font != nullptr;
}
//------------------------------------------------------------------------------
void TextureText::_free()
{
  if (mp_font != nullptr)
    TTF_CloseFont(mp_font);
  mp_font = nullptr;

  if (mp_texture != nullptr)
  {
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}
//------------------------------------------------------------------------------
void TextureText::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  m_color.r = red;
  m_color.g = green;
  m_color.b = blue;
}
//------------------------------------------------------------------------------
void TextureText::setPos(int x, int y)
{
  m_x = x;
  m_y = y;
}
//------------------------------------------------------------------------------
void TextureText::setAlpha(Uint8 alpha)
{
  SDL_SetTextureAlphaMod(mp_texture, alpha);
}
//------------------------------------------------------------------------------
void TextureText::render(double angle /* = 0.0 */ )
{
  SDL_Rect renderQuad = { m_x, m_y, m_width, m_height };
  
  SDL_RenderCopyEx(SDLEngine::instance().renderer(), 
                   mp_texture, 
                   nullptr, 
                  &renderQuad, 
                   angle, 
                   nullptr, 
                   SDL_FLIP_NONE);
}
//------------------------------------------------------------------------------
void TextureText::setText(std::string text)
{
  m_text = text;

  if (mp_texture)
  {
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
  }

  SDL_Surface* textSurface = TTF_RenderUTF8_Solid(mp_font, m_text.c_str(), m_color);
  if (textSurface != nullptr)
  {
    mp_texture = SDL_CreateTextureFromSurface(SDLEngine::instance().renderer(), textSurface);
    if (mp_texture != nullptr)
    {
      m_width = textSurface->w;
      m_height = textSurface->h;
    }
    SDL_FreeSurface(textSurface);
  }
}
//------------------------------------------------------------------------------
const int &TextureText::width()const
{
  return m_width;
}
//------------------------------------------------------------------------------
const int &TextureText::height()const
{
  return m_height;
}
//------------------------------------------------------------------------------
const int &TextureText::x()const
{
  return m_x;
}
//------------------------------------------------------------------------------
const int &TextureText::y()const
{
  return m_y;
}




