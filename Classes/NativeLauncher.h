//
//  NativeLauncher.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/16.
//
//

#ifndef WitchRace_NativeLauncher_h
#define WitchRace_NativeLauncher_h
#include <string>


class NativeLauncher{
public:
    static void openReview();
    static void loginGameCenter();
    static void openRanking();
    static void postHighScore(std::string key ,int score);

};

#endif
