#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "BaseEntity.h"

class Shield : public BaseEntity
{
private:
	int	m_MaxShield;
	int m_CurrShield;
	bool m_Render;
	float m_RenderTimer;

public:
	Shield(void);
	~Shield(void);

	int GetMaxShield(void) { return m_MaxShield; }
	void SetMaxShield(const int _maxShield) { m_MaxShield = _maxShield; }

	int GetCurrShield(void) { return m_CurrShield; }
	void SetCurrShield(const int _currShield) { m_CurrShield = _currShield; }

	void SetRender(const bool _render) { m_Render = _render; }
	const bool GetRender(void) { return m_Render; }

	void SetRenderTimer(const float _timer) { m_RenderTimer = _timer; }

	virtual void Update(float _dt);
	virtual void Render( int _x, int _y );
};

#endif