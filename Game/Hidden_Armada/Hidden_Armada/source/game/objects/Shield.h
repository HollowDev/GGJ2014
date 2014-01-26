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
};

#endif