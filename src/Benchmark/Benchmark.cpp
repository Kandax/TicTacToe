#include "Benchmark.h"


void Benchmark::runBenchmark(){

    std::ofstream file("benchmark_results.csv");

    if(!file.is_open()){
        std::cerr <<"Cannor open benchmark_results.csv"<<std::endl;
    }

    file << "BoardSize, Depth, AverageTimeMs\n";

    const std::vector<BenchmarkConfig> configs= {
        {3,10},
        {4, 10},
        {5,8},
        {6,6},
        {7, 5},
        {8,4},
        {9,3},
        {10,3}
    };

    const int runsPerTest = 5;

    for(const auto& config : configs){
        for(int depth = 1; depth <= config.maxDepth; depth++){

            double totalTimeMs = 0.0;

            for(int run = 0; run < runsPerTest; run++){
                Board board(config.boardSize, 3);

                MinMaxAI ai(Cell::X, depth);

                auto start = std::chrono::high_resolution_clock::now();


                ai.chooseMove(board);


                auto end = std::chrono::high_resolution_clock::now();


                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


                totalTimeMs += duration;

            }


            double averageTime = totalTimeMs / runsPerTest;

            file 
                << config.boardSize << ","
                << config.maxDepth << ","
                << std::fixed
                << std::setprecision(3)
                << averageTime
                << "\n" ;

            std::cout
                << "Board "<< config.boardSize <<"x"<< config.boardSize
                << " Depth "<< depth 
                << " Avg " << averageTime<< "ms\n";
        }
    }

    file.close();

    std::cout<<"Benchmark finished. \n";
}


void Benchmark::runStressTest(){

    std::cout<<"Starting stress testing. \n";


    std::ofstream file("stress_test.csv");
    file << "BoardSize,Depth,TimeMs\n";

    const std::vector<BenchmarkConfig> stressTests= {
    {5,9},
    {6, 7},
    {7, 6},
    {8 ,5 },
    {9, 4},
    {10, 4}
    };

    // stres test
    /*
    5 10
    6 7
    7 6
    8 5 
    9 4
    10 4
    */

    for(const auto& stressTest: stressTests){
        Board board(stressTest.boardSize, 3);

        MinMaxAI ai(Cell::X, stressTest.maxDepth);

        auto start = std::chrono::high_resolution_clock::now();


        ai.chooseMove(board);


        auto end = std::chrono::high_resolution_clock::now();


        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        file 
            << stressTest.boardSize<<","
            << stressTest.maxDepth<<","
            << duration<<"\n";

        std::cout
            << "[Stress] "
            << stressTest.boardSize<<" depth"
            << stressTest.maxDepth<<" -> "
            << duration<<" ms\n";

    }

    file.close();

    std::cout<<"Stress test finished."<<std::endl;
}