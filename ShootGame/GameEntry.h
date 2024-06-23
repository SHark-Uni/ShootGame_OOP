#pragma once
#include "GameInitializer.h"

// 게임의 시작시, 로딩해야할 것을 정의합니다.
namespace ShootingGame
{
	class GameEntry : public GameInitiallizer
	{
	public:
		void Init() override;
	};
}