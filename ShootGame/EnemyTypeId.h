#pragma once

namespace ShootingGame
{
	enum class eEnemyTypeId
	{
		NORMAL,
		ATTACKER,
		DEFENDER,
	};

	enum class eNormalTypeInfo
	{
		AttackPower = 2,
		HP = 5,
		Interval = 30,
	};

	enum class eAttackTypeInfo
	{
		HP = 1,
		AttackPower = 3,
		Interval = 25,
	};

	enum class eDefenderTypeInfo
	{
		AttackPower = 1,
		HP = 8,
		Interval = 35,
	};

}