#pragma once 

#include <chrono>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include <vector>



#include "Gameplay/MinMaxAI.h"
#include "Gameplay/Board.h"


struct BenchmarkConfig{
    int boardSize;
    int maxDepth;
};

class Benchmark{
public:
static void runBenchmark();
static void runStressTest();
};