#include "bitmapfont.hpp"



//------------------------------------------------------------------------------
BitmapFont::BitmapFont()
{
}
//------------------------------------------------------------------------------
BitmapFont::~BitmapFont()
{
}
//------------------------------------------------------------------------------
void BitmapFont::_free()
{
}
void BitmapFont::load(std::string aPath)
{
  if (m_bitmap_texture.load(aPath))
  {
    _build();
  }
}
//------------------------------------------------------------------------------
bool BitmapFont::_build()
{
  if (!m_bitmap_texture.lock())
    return false;

  Uint32 bgColor = m_bitmap_texture.get_pixel32(0, 0);

  int cellW = m_bitmap_texture.width() / 16;
  int cellH = m_bitmap_texture.height() / 16;

  int top = cellH;
  int baseA = cellH;
  int currentChar = 0;

  for (int rows = 0; rows < 16; ++rows)
  {
    for (int cols = 0; cols < 16; ++cols)
    {
      m_chars[currentChar].x = cellW * cols;
      m_chars[currentChar].y = cellH * rows;

      m_chars[currentChar].w = cellW;
      m_chars[currentChar].h = cellH;

      //Find Left Side
      for (int pCol = 0; pCol < cellW; ++pCol)
      {
        //Go through pixel rows
        for (int pRow = 0; pRow < cellH; ++pRow)
        {
          int pX = (cellW * cols) + pCol;
          int pY = (cellH * rows) + pRow;

          if (m_bitmap_texture.get_pixel32(pX, pY) != bgColor)
          {
            m_chars[currentChar].x = pX;

            pCol = cellW;
            pRow = cellH;
          }
        }
      }

      //Find Right Side
      //Go through pixel columns
      for (int pColW = cellW - 1; pColW >= 0; --pColW)
      {
        //Go through pixel rows
        for (int pRowW = 0; pRowW < cellH; ++pRowW)
        {
          int pX = (cellW * cols) + pColW;
          int pY = (cellH * rows) + pRowW;

          if (m_bitmap_texture.get_pixel32(pX, pY) != bgColor)
          {
            m_chars[currentChar].w = (pX - m_chars[currentChar].x) + 1;

            pColW = -1;
            pRowW = cellH;
          }
        }
      }

      //Find Top
      //Go through pixel rows
      for (int pRow = 0; pRow < cellH; ++pRow)
      {
        //Go through pixel columns
        for (int pCol = 0; pCol < cellW; ++pCol)
        {
          int pX = (cellW * cols) + pCol;
          int pY = (cellH * rows) + pRow;

          if (m_bitmap_texture.get_pixel32(pX, pY) != bgColor)
          {
            if (pRow < top)
            {
              top = pRow;
            }
            pCol = cellW;
            pRow = cellH;
          }
        }
      }

      if (currentChar == 'A')
      {
        //Go through pixel rows
        for (int pRow = cellH - 1; pRow >= 0; --pRow)
        {
          //Go through pixel columns
          for (int pCol = 0; pCol < cellW; ++pCol)
          {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            //If a non colorkey pixel is found
            if (m_bitmap_texture.get_pixel32(pX, pY) != bgColor)
            {
              baseA = pRow;

              pCol = cellW;
              pRow = -1;
            }
          }
        }
      }
      ++currentChar;
    }
  }

  m_space = cellW / 2;

  m_new_line = baseA - top;

  for (int i = 0; i < 256; ++i)
  {
    m_chars[i].y += top;
    m_chars[i].h -= top;
  }

  m_bitmap_texture.unlock();

  return true;
}
//------------------------------------------------------------------------------
void BitmapFont::render_text(int x, int y, std::string text)
{
  int curX = x, curY = y;

  for (int i = 0; i < text.length(); ++i)
  {
    if (text[i] == ' ')
    {
      curX += m_space;
    }
    else if (text[i] == '\n')
    {
      curY += m_new_line;

      curX = x;
    }
    else
    {
      int ascii = (unsigned char)text[i];

      m_bitmap_texture.draw(curX, curY, &m_chars[ascii]);

      curX += m_chars[ascii].w + 1;
    }
  }
}

