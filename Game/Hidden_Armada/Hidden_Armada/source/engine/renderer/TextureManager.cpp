#include "TextureManager.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Title : sTextureManager.cpp
Author : Evan Wright

Description : A wrapper to allow easy 2D rendering. Loads and manages all textures and
			  allows use of textures with a reference to an integer.

Created :  12/09/2013
Modified : 12/09/2013
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "TextureManager.h"
#include "../memory_macros.h"
#include <assert.h>

TextureManager TextureManager::m_Instance;

TextureManager::TextureManager( void )
{
	m_Device = nullptr;
	m_Sprite = nullptr;
}

bool TextureManager::Initialize( LPDIRECT3DDEVICE9 _device, LPD3DXSPRITE _sprite )
{
	// Reference the device
	m_Device = _device;
	m_Device->AddRef();
	// Reference the sprite system
	m_Sprite = _sprite;
	m_Sprite->AddRef();

	return (m_Device != nullptr && m_Sprite != nullptr) ? true : false;
}

void TextureManager::Release( void )
{
	for(unsigned int i = 0; i < m_Textures.size(); ++i)
	{
		// Remove ref
		m_Textures[i].ref = 0;

		// Release the texture if it's not being used.
		SAFE_RELEASE(m_Textures[i].texture);
		m_Textures[i].filename[0] = '\0';
	}
	// Clear the list of all loaded textures
	m_Textures.clear();

	// Release the reference to the sprite and d3d device
	SAFE_RELEASE(m_Sprite);
	SAFE_RELEASE(m_Device);
}

int TextureManager::LoadTexture( const TCHAR* _filename, DWORD _colorkey )
{
	// Make sure it's valid
	if(!_filename) return -1;

	// Make sure the texture isn't already loaded.
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		// compare strings without caring about upper or lowercase.
		if (_tcsicmp(_filename, m_Textures[i].filename) == 0)	// 0 means they are equal.
		{
			m_Textures[i].ref++; // add a reference to this texture.
			return i;	// return the index.
		}
	}

	// Look for an open spot.
	int nID = -1;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		if (m_Textures[i].ref == 0)
		{
			nID = i;
			break;
		}
	}

	// if we didn't find an open spot, load it in a new one
	if (nID == -1)
	{
		// A temp texture object.
		Texture loaded;

		// Copy the filename of the loaded texture.
		_tcscpy_s(loaded.filename, _countof(loaded.filename), _filename);

		// Load the texture from the given file.
		HRESULT hr = 0;
		if (FAILED(hr = D3DXCreateTextureFromFileEx(m_Device, _filename, 0, 0, D3DX_DEFAULT, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
			D3DX_DEFAULT, _colorkey, 0, 0, &loaded.texture)))
		{
			// Failed.
			TCHAR szBuffer[256] = {0};
			_stprintf_s(szBuffer, _countof(szBuffer), _T("Failed to Create Texture - %s"), _filename); 
			MessageBox(0, szBuffer, _T("TextureManager Error"), MB_OK);
			return -1;
		}

		// AddRef.
		loaded.ref = 1;

		// Get surface description (to find Width/Height of the texture)
		D3DSURFACE_DESC d3dSurfDesc;
		ZeroMemory(&d3dSurfDesc, sizeof(d3dSurfDesc));

		loaded.texture->GetLevelDesc(0, &d3dSurfDesc);

		// Remember the Width and Height
		loaded.width	= d3dSurfDesc.Width;
		loaded.height	= d3dSurfDesc.Height;

		// Put the texture into the list.
		m_Textures.push_back(loaded);

		// Return the nID of the texture.
		return (int)m_Textures.size() - 1;
	}
	// we found an open spot
	else
	{
		// Make sure the texture has been released.
		SAFE_RELEASE(m_Textures[nID].texture);

		// Copy the filename of the loaded texture.
		_tcscpy_s(m_Textures[nID].filename, _countof(m_Textures[nID].filename), _filename);

		// Load the texture from the given file.
		HRESULT hr = 0;
		if (FAILED(hr = D3DXCreateTextureFromFileEx(m_Device, _filename, 0, 0, D3DX_DEFAULT, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
			D3DX_DEFAULT, _colorkey, 0, 0, &m_Textures[nID].texture)))
		{
			// Failed.
			TCHAR szBuffer[256] = {0};
			_stprintf_s(szBuffer, _countof( szBuffer ), _T("Failed to Create Texture - %s"), _filename); 
			MessageBox(0, szBuffer, _T("TextureManager Error"), MB_OK);
			return -1;
		}

		// Get surface description (to find Width/Height of the texture)
		D3DSURFACE_DESC d3dSurfDesc;
		ZeroMemory(&d3dSurfDesc, sizeof(d3dSurfDesc));

		m_Textures[nID].texture->GetLevelDesc(0, &d3dSurfDesc);

		// Remember the Width and Height
		m_Textures[nID].width	= d3dSurfDesc.Width;
		m_Textures[nID].height	= d3dSurfDesc.Height;

		// AddRef
		m_Textures[nID].ref = 1;

		// Return the nID of the texture.
		return nID;
	}
}

void TextureManager::UnloadTexture( int _id )
{
	// Make sure the nID is in range.
	assert(_id > -1 && _id < (int)m_Textures.size() && "Texture _id is out of range");
	
	// Remove ref.
	m_Textures[_id].ref--;

	// Release the texture if it's not being used.
	if (m_Textures[_id].ref <= 0)
	{
		// Do a lazy delete and leave this spot empty
		SAFE_RELEASE(m_Textures[_id].texture);
		m_Textures[_id].filename[0] = '\0';
		m_Textures[_id].ref = 0;
	}
}

int TextureManager::GetTextureWidth( int _id )
{
	// Make sure the nID is in range.
	assert(_id > -1 && _id < (int)m_Textures.size() && "Texture _id is out of range");

	return m_Textures[_id].width;
}

int TextureManager::GetTextureHeight( int _id )
{
	// Make sure the nID is in range.
	assert(_id > -1 && _id < (int)m_Textures.size() && "Texture _id is out of range");

	return m_Textures[_id].height;
}

//bool TextureManager::Draw( int _id, int _x, int _y, float _scaleX, float _scaleY,
//			RECT* _section, float _rotCenterX, float _rotCenterY, float _rot, 
//			int _r, int _g, int _b, int _a )
//{
//	return Draw(_id, _x, _y, _scaleX, _scaleY, _section, _rotCenterX, _rotCenterY, _rot, D3DCOLOR_ARGB(_a,_r,_g,_b));
//}

bool TextureManager::Draw( int _id, int _x, int _y, float _scaleX, float _scaleY,
		RECT* _section, float _rotCenterX, float _rotCenterY, float _rot, DWORD _color )
{
	// Make sure the nID is in range
	assert(_id > -1 && _id < (int)m_Textures.size() && "Texture _id is out of range");

	// Make sure that the texture is valid
	assert(m_Textures[_id].texture != NULL && "Attempting to draw released texture id");

	// Make sure the sprite was created and we have a valid texture
	if (!m_Sprite)
		return false;

	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX translate;
	D3DXMATRIX combined;

	// Set combined mat to identity
	D3DXMatrixIdentity(&combined);

	// Scale the sprite
	D3DXMatrixScaling(&scale, _scaleX, _scaleY, 1.0f);
	combined *= scale;

	// Rotate the sprite
	D3DXMatrixTranslation(&translate, -_rotCenterX * _scaleX, -_rotCenterY * _scaleY, 0.0f);
	combined *= translate;
	D3DXMatrixRotationZ(&rotation, _rot);
	combined *= rotation;
	D3DXMatrixTranslation(&translate, _rotCenterX * _scaleX, _rotCenterY * _scaleY, 0.0f);
	combined *= translate;

	// Translate the sprite
	D3DXMatrixTranslation(&translate, (float)_x, (float)_y, 0.0f);
	combined *= translate;

	// Apply the final transform
	m_Sprite->SetTransform(&combined);

	// Draw the sprite
	if (FAILED(m_Sprite->Draw(m_Textures[_id].texture, _section, NULL, NULL, _color)))
		return false;

	// Move the world back to identity
	D3DXMatrixIdentity(&combined);
	m_Sprite->SetTransform(&combined);

	// success
	return true;
}
