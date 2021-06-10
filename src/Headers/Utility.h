//Maybe use macros for the collidertag

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








