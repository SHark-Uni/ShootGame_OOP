#pragma once

namespace ShootingGame
{
	class IPlayable
	{
	public:
		virtual void KeyInput() = 0;
		virtual ~IPlayable()
		{
		}
	};
}