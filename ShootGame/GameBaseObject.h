#pragma once

namespace ShootingGame
{
	class GameBaseObject
	{ 
		friend class GameObjectManager;
	public:
		// �������簡 �ʿ��� ����� ����.
		GameBaseObject(int ObjectType, int x, int y);
		virtual ~GameBaseObject();

		const int GetX() const;
		const int GetY() const;

		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void OnCollision(GameBaseObject* object) = 0;

	protected:
		int mTypeId;
		int mX;
		int mY;

		bool mIsAlive;
	};
}