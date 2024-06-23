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
		HP = 5,
		Speed = 10,

		AttackPower = 2,
		AttackSpeed = 10,
	};

	enum class eAttackTypeInfo
	{
		HP = 1,
		Speed = 15,

		AttackPower = 3,
		AttackSpeed = 15,
	};

	enum class eDefenderTypeInfo
	{
		HP = 8,
		Speed = 5,

		AttackPower = 1,
		AttackSpeed = 5,
	};

}