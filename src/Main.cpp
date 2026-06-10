#include "Game.h"

#include "Benchmark/Benchmark.h"

int main(int argc, char** argv)
{

    bool runBenchmark = false;
    bool runStress= false;

    for(int i = 1; i < argc; i++){
        std::string arg = argv[i];

        if(arg == "-b"){
            runBenchmark = true;
        }

        if(arg == "-s"){
            runStress = true;
        }
    }

    if(runBenchmark && runStress){
        Benchmark::runBenchmark();
        Benchmark::runStressTest();
        return 0;
    }

    if(runBenchmark){
        Benchmark::runBenchmark();
        return 0;
    }

    if(runStress){
        Benchmark::runStressTest();
        return 0;
    }


    Game game;
    game.run();
}