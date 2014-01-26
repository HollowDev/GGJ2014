#include "BitmapFont.h"
#include "TextureManager.h"

BitmapFont::BitmapFont( void )
{

}

void BitmapFont::Initialize( int _imgID, const int _charWidth, const int _charHeight, const int _numRows, const int _numCols )
{
	m_ImgID = _imgID;

	m_CharWidth = _charWidth;
	m_CharHeight = _charHeight;
	m_NumRows = _numRows;
	m_NumCols = _numCols;
}

void BitmapFont::Release( void )
{

}

RECT BitmapFont::CellAlgorithm( int _id )
{
	RECT rCell;
	rCell.left	 = LONG((_id % m_NumCols) * m_CharWidth);
	rCell.top	 = LONG((_id / m_NumCols) * m_CharHeight);
	rCell.right  = LONG(rCell.left + m_CharWidth);
	rCell.bottom = LONG(rCell.top + m_CharHeight);
	return rCell;
}

void BitmapFont::Print( const char* _text, int _x, int _y, DWORD _color )
{
	int colStart = (int)_x;
	int textLength = strlen(_text);

	for( int i = 0; i < textLength; i++)
	{		
		if(_text[i] == ' ' )
			_x += m_CharWidth/2 + 1;
		else if( _text[i] == '\n')
		{
			_y += m_CharHeight;
			_x = colStart;
			continue;
		}

		RECT rTile = CellAlgorithm(_text[i]);
		TextureManager::GetInstance()->Draw(m_ImgID,_x,_y,1.0f,1.0f,&rTile,0,0,0,_color);	
		_x += float(m_CharWidth);
	}
}
