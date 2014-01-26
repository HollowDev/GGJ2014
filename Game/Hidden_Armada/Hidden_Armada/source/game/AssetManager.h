#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

enum Assets
{
	Asset_Asteroid01 = 0, Asset_Asteroid02, Asset_Asteroid03, Asset_Asteroid04,
	Asset_SmallAsteroids, Asset_CrimsonDoom, Asset_EnemyShip01, Asset_EnemyShip02, 
	Asset_EnemyShip03, Asset_Explosion01, Asset_Explosion02, Asset_HudHealthNotch,
	Asset_HudOutline, Asset_HudShieldBar, Asset_Planet01, Asset_Planet02, 
	Asset_Planet03, Asset_Planet04, Asset_Star01, Asset_HexParticle,
	Asset_LaserProjectile, Asset_MachineGunProjectile, Asset_MissleProjectile,
	Asset_ShipThrust, Asset_PlayerShip01, Asset_PlayerShip02, Asset_PlayerShip03,
	Asset_Powerups01, Asset_DragonPlayerSelect, Asset_LightingPlayerSelect,
	Asset_MainTitle, Asset_TitleLabels, Asset_TurtlePlayerSelect,
	Asset_WeaponLaser01, Asset_WeaponLaser02, Asset_WeaponLaser03,
	Asset_WeaponMachineGun01, Asset_WeaponMachineGun02, Asset_WeaponMachineGun03,
	Asset_WeaponMissle01, Asset_WeaponMissle02, Asset_WeaponMissle03,
	Asset_Font,

	Asset_NumAssets
};

class AssetManager
{
	int m_Assets[Asset_NumAssets];

	static AssetManager m_Instance;

	AssetManager( void ) {}
	~AssetManager( void ) {}
public:
	static AssetManager* GetInstance( void ) { return &m_Instance; }

	void Initialize( void );
	void Release( void );

	int GetAsset( Assets _type );
};

#endif