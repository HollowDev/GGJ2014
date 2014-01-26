#include "AssetManager.h"
#include "../engine/renderer/TextureManager.h"
#include "../engine/sound/SoundManager.h"

AssetManager AssetManager::m_Instance;

void AssetManager::Initialize( void )
{
	TextureManager* TM = TextureManager::GetInstance();

	// ASTEROIDS FOLDER
	m_Assets[Asset_Asteroid01] = TM->LoadTexture(L"assets/textures/asteroids/asteroid001.png");
	m_Assets[Asset_Asteroid02] = TM->LoadTexture(L"assets/textures/asteroids/asteroid002.png");
	m_Assets[Asset_Asteroid03] = TM->LoadTexture(L"assets/textures/asteroids/asteroid003.png");
	m_Assets[Asset_Asteroid04] = TM->LoadTexture(L"assets/textures/asteroids/asteroid004.png");
	m_Assets[Asset_SmallAsteroids] = TM->LoadTexture(L"assets/textures/asteroids/small_asteroids.png");

	// ENEMY SHIPS FOLDER
	m_Assets[Asset_CrimsonDoom] = TM->LoadTexture(L"assets/textures/Enemyships/crimsonDOOM.png");
	m_Assets[Asset_EnemyShip01] = TM->LoadTexture(L"assets/textures/Enemyships/enemyship1.png");
	m_Assets[Asset_EnemyShip02] = TM->LoadTexture(L"assets/textures/Enemyships/enemyship2.png");
	m_Assets[Asset_EnemyShip03] = TM->LoadTexture(L"assets/textures/Enemyships/enemyship3.png");

	// EXPLOSIONS FOLDER
	m_Assets[Asset_Explosion01] = TM->LoadTexture(L"assets/textures/Explosions/Explosion01.png");
	m_Assets[Asset_Explosion02] = TM->LoadTexture(L"assets/textures/Explosions/Explosion02.png");
	m_Assets[Asset_Explosion03] = TM->LoadTexture(L"assets/textures/Explosions/Explosion03.png");

	// HUD FOLDER
	m_Assets[Asset_HudHealthNotch] = TM->LoadTexture(L"assets/textures/hud/healthnotch.png");
	m_Assets[Asset_HudOutline] = TM->LoadTexture(L"assets/textures/hud/hud1.png");
	m_Assets[Asset_HudShieldBar] = TM->LoadTexture(L"assets/textures/hud/shieldbar.png");

	// PLANETS FOLDER
	m_Assets[Asset_Planet01] = TM->LoadTexture(L"assets/textures/Planets/planet1.png");
	m_Assets[Asset_Planet02] = TM->LoadTexture(L"assets/textures/Planets/planet2.png");
	m_Assets[Asset_Planet03] = TM->LoadTexture(L"assets/textures/Planets/planet3.png");
	m_Assets[Asset_Planet04] = TM->LoadTexture(L"assets/textures/Planets/planet4.png");
	m_Assets[Asset_Star01] = TM->LoadTexture(L"assets/textures/Planets/star01.png");

	// PLAYER SHIP EFFECTS FOLDER
	m_Assets[Asset_HexParticle] = TM->LoadTexture(L"assets/textures/playershipeffects/hex_particle.png");
	m_Assets[Asset_LaserProjectile] = TM->LoadTexture(L"assets/textures/playershipeffects/Laser_projectiles.png");
	m_Assets[Asset_MachineGunProjectile] = TM->LoadTexture(L"assets/textures/playershipeffects/machinegun_projectiles.png");
	m_Assets[Asset_MissleProjectile] = TM->LoadTexture(L"assets/textures/playershipeffects/missile_projectiles.png");
	m_Assets[Asset_ShipThrust] = TM->LoadTexture(L"assets/textures/playershipeffects/playerships_thrust.png");
	m_Assets[Asset_Reveal] = TM->LoadTexture(L"assets/textures/playershipeffects/revealwave.png");
	m_Assets[Asset_Shield] = TM->LoadTexture(L"assets/textures/playershipeffects/ShipShield.png");
	m_Assets[Asset_BoostTrail] = TM->LoadTexture(L"assets/textures/playershipeffects/boost_trail.png");

	// POWERUPS FOLDER
	m_Assets[Asset_Powerups01] = TM->LoadTexture(L"assets/textures/powerups/powerups1.png");

	// PLAYER SHIPS FOLDER
	m_Assets[Asset_PlayerShip01] = TM->LoadTexture(L"assets/textures/ships/Playership1.png");
	m_Assets[Asset_PlayerShip02] = TM->LoadTexture(L"assets/textures/ships/Playership2.png");
	m_Assets[Asset_PlayerShip03] = TM->LoadTexture(L"assets/textures/ships/Playership3.png");
	
	// TITLES FOLDER
	m_Assets[Asset_DragonPlayerSelect] = TM->LoadTexture(L"assets/textures/titles/Dragon_Playerselect.png");
	m_Assets[Asset_LightingPlayerSelect] = TM->LoadTexture(L"assets/textures/titles/Lightning_Playerselect.png");
	m_Assets[Asset_MainTitle] = TM->LoadTexture(L"assets/textures/titles/maintitle.png");
	m_Assets[Asset_TitleLabels] = TM->LoadTexture(L"assets/textures/titles/titlelabels.png");
	m_Assets[Asset_TurtlePlayerSelect] = TM->LoadTexture(L"assets/textures/titles/Turtle_Playerselect.png");

	// WEAPONS FOLDER
	m_Assets[Asset_WeaponLaser01] = TM->LoadTexture(L"assets/textures/weapons/laser1.png");
	m_Assets[Asset_WeaponLaser02] = TM->LoadTexture(L"assets/textures/weapons/laser2.png");
	m_Assets[Asset_WeaponLaser03] = TM->LoadTexture(L"assets/textures/weapons/laser3.png");

	m_Assets[Asset_WeaponMachineGun01] = TM->LoadTexture(L"assets/textures/weapons/machinegun1.png");
	m_Assets[Asset_WeaponMachineGun02] = TM->LoadTexture(L"assets/textures/weapons/machinegun2.png");
	m_Assets[Asset_WeaponMachineGun03] = TM->LoadTexture(L"assets/textures/weapons/machinegun3.png");
	
	m_Assets[Asset_WeaponMissle01] = TM->LoadTexture(L"assets/textures/weapons/missile1.png");
	m_Assets[Asset_WeaponMissle02] = TM->LoadTexture(L"assets/textures/weapons/missile2.png");
	m_Assets[Asset_WeaponMissle03] = TM->LoadTexture(L"assets/textures/weapons/missile3.png");

	// ROOT
	m_Assets[Asset_Font] = TM->LoadTexture(L"assets/textures/font.png");

	SoundManager* SM = SoundManager::GetInstance();
	// LOAD SOUNDS
	m_Assets[Asset_S_Explosion01] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion01.wav");
	m_Assets[Asset_S_Explosion02] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion02.wav");
	m_Assets[Asset_S_Explosion03] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion03.wav");
	m_Assets[Asset_S_Explosion04] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion04.wav");
	m_Assets[Asset_S_Explosion05] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion05.wav");
	m_Assets[Asset_S_Explosion06] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion06.wav");
	m_Assets[Asset_S_Explosion07] = SM->LoadSFX("assets/sounds/sfx/Explosions/Explosion07.wav");
	m_Assets[Asset_S_ExplosionS] = SM->LoadSFX("assets/sounds/sfx/Explosions/ExplosionS.wav");
	
	m_Assets[Asset_S_MachinegunFire] = SM->LoadSFX("assets/sounds/sfx/weapons/machinegun_fire.wav");
	m_Assets[Asset_S_MissileFire] = SM->LoadSFX("assets/sounds/sfx/weapons/missile_fire.wav");
	m_Assets[Asset_S_AsteroidHit] = SM->LoadSFX("assets/sounds/sfx/weapons/asteroid_hit.wav");
}

void AssetManager::Release( void )
{

}

int AssetManager::GetAsset( Assets _type )
{
	if( _type < Asset_NumAssets && _type >= 0 )
	{
		return m_Assets[_type];
	}
}
