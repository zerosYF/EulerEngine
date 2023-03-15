#include"EulerGame.h"
#include"../Test/ModelTest/Test_Reflect.h"
using namespace EulerEngine;
int main() {
	EulerGame *game = new EulerGame();
	game->startEngine();
	game->run();
	return 0;
}