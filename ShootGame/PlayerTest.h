#pragma once
#include "Player.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"

using namespace ShootingGame;

inline void PlayerTest()
{
    Player* p = new Player({ 10, 0, 5, 10, 5, 10 });

    GameObjectManager& gm = GameObjectManager::GetInstance();
    ScreenBuffer& s = ScreenBuffer::GetInstance();


    gm.CreateObject(p);
    while (1)
    {
        s.Clear();
        gm.Update();

        gm.DestroyColliedObject();
        Sleep(30);
        s.Flip();
    }

}