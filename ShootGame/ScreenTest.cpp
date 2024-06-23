#include "ScreenBuffer.h"

using namespace ShootingGame;

void ScreenDrawTest()
{  
    //단일 그리기
	ScreenBuffer& s = ScreenBuffer::GetInstance();
    s.DrawSprite(1, 1, L'@');
    s.Flip();
}