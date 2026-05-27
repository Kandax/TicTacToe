#pragma once

enum class GameMode{
    PvP,
    PvAI
};

struct AIConfig{
    int depth;
};

struct GameConfig{
    GameMode gameMode;

    int boardSize = 3;
    int symbolsToWin = 3;

    AIConfig ai = {3};
};

