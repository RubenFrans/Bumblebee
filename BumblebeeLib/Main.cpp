

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#pragma warning(push, 1)
#include <steam_api.h>
#pragma warning(pop)


//int main(int, char*[]) {
//
//	if (!SteamAPI_Init())
//	{
//		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
//		return 1;
//	}
//	else
//		std::cout << "Successfully initialized steam." << std::endl;
//
//	SteamUserStats()->ClearAchievement("ACH_WIN_ONE_GAME");
//	BTEngine::Minigin engine;
//	engine.Run();
//
//	SteamAPI_Shutdown();
//    return 0;
//}