#include "ScreenBuffer.h"

using namespace ShootingGame;

void ScreenDrawTest()
{  
    //���� �׸���
	ScreenBuffer& s = ScreenBuffer::GetInstance();
    s.DrawSprite(1, 1, L'@');
    s.Flip();
}