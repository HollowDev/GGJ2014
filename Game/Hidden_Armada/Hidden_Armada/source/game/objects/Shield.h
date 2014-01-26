#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "BaseEntity.h"

class Shield : public BaseEntity
{
private:
	int	m_MaxShield;
	int m_CurrShield;

public:
	Shield(void);
	~Shield(void);

	int GetMaxShield(void) { return m_MaxShield; }
	void SetMaxShield(const int _maxShield) { m_MaxShield = _maxShield; }

	int GetCurrShield(void) { return m_CurrShield; }
	void SetCurrShield(const int _currShield) { m_CurrShield = _currShield; }
};

#endif