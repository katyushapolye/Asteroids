//Maybe use macros for the collidertag
#pragma once
const unsigned int mScreenX = 600;
const unsigned int mScreenY = 600;

struct Point
{
	Point(float initX, float InitY)
	{
		X = initX;
		Y = InitY;
	}
	float X;
	float Y;
};

enum ColliderTag
{
	PlayerCollider,
	EnemyCollider,
	MissileCollider,
};

enum TextureID{
	PlayerTexture,
	EnemyTexture,
	MissileTexture

};

const int MAX_TEXTURES = 10;








