#include "MainSystem.h"

MainSystem *MainSystem::instance = nullptr;

MainSystem::MainSystem()
{
	//预留空间
	friends.reserve(16);
	sessions.reserve(8);

}
