#include <iostream>
#include <chrono>

#include "SIIW/RandomSearch.h"
#include "SIIW/GeneticSearch.h"
#include "SIIW/CountStopCondition.h"
#include "SIIW_1/CircutProblem.h"
#include "SIIW/RouletteSelection.h"
#include "SIIW/TournamentSelection.h"

int main()
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	
	SIIW_1::CircutProblem problem(0.5f);
	SIIW::CountStopCondition stopCondition(10000);
	//SIIW::RandomSearch search(&problem, &stopCondition);
	//SIIW::RouletteSelection selection;
	SIIW::TournamentSelection t_selection(25);
	SIIW::GeneticSearch search(&problem, &stopCondition, &t_selection, 100, 0.9f, 0.1f);

	auto t1 = high_resolution_clock::now();
	search.SearchForBestSolution();
	auto t2 = high_resolution_clock::now();

	std::cout << "Best solution quality: " << search.GetBestSolutionQuality() << std::endl << std::endl;
	search.GetBestSolution()->PrettyPrint();

	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << "Time: " << ms_double.count() << "ms" << std::endl;

	system("pause");
}