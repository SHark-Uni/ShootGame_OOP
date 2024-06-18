#include "Player.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;

void PlayerTest()
{
    Player* p = new Player({ 10, 0, 5, 5, 10 });

    while (1)
    {
        ScreenBuffer& s = ScreenBuffer::GetInstance();
        s.Clear();
        p->Update();

        Sleep(30);
        s.Flip();
    }

}