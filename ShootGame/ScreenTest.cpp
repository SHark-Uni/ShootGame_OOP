#include "ScreenBuffer.h"

using namespace ShootingGame;

void ScreenDrawTest()
{  
    //���� �׸���
	ScreenBuffer& s = ScreenBuffer::GetInstance();
    s.SpriteDraw(1, 1, L'@');
    s.Flip();
}