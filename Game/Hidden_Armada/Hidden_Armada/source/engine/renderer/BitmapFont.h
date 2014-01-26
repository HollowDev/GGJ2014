#ifndef _BITMAP_FONT_H_
#define _BITMAP_FONT_H_

#include "../directx9.h"

class BitmapFont
{
	int m_ImgID;

	int m_CharWidth;
	int m_CharHeight;
	int m_NumCols;
	int m_NumRows;

	RECT CellAlgorithm( int _id );
	
public:
	BitmapFont( void );
	~BitmapFont( void ) { Release(); }

	void Initialize( int _imgID, const int _charWidth, const int _charHeight, const int _numRows, const int _numCols );
	void Release( void );

	void Print( const char* _text, int _x, int _y, DWORD _color );
};

#endif