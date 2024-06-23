#pragma once

namespace ShootingGame
{
	class GameInitiallizer 
	{
	public:
		virtual void Init() = 0;
		virtual ~GameInitiallizer() {};
	};
}