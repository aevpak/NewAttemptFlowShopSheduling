// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Job.h"
#include "FlowShop.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <numeric>
#include <time.h>
#include <string>
using namespace std;
int calcFunction(std::vector<Job> vec) {
    FlowShop flowShop;
    flowShop.setData(vec);
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        flowShop.pushInput(it->getName());
    }
    //flowShop.toString();
    flowShop.run();
	//flowShop.printProcess();
    return flowShop.getTime();
}
int calcAndPrintFunction(std::vector<Job> vec, bool firstly, std::string dir) {
	FlowShop flowShop;
	flowShop.setData(vec);
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		flowShop.pushInput(it->getName());
	}
	//flowShop.toString();
	flowShop.run();
	flowShop.printProcess(firstly, dir);
	return flowShop.getTime();
}
namespace ch = std::chrono;

template <typename duration = ch::seconds, typename clock = ch::high_resolution_clock>
class timer
{
	typename clock::time_point m_start, m_stop;

	typename clock::rep get_time() const
	{
		return ch::duration_cast<duration>(m_stop - m_start).count();
	}

public:
	void         start() { m_start = clock::now(); }
	const timer& stop() { m_stop = clock::now(); return *this; }

	std::ostream& print() const
	{
		return std::cout << "Time running: [" << get_time() << "]";
	}
};

int main()
{
	for (int it = 1; it < 2; it++) {
		srand((unsigned)time(NULL));
		//timer<ch::milliseconds> aTimer;
		std::vector<Job> initial;
		string line;
		ifstream in("inst" + std::to_string(it) + "/inst" + std::to_string(it) + "converted.txt"); // окрываем файл для чтения
		int iterCount = 300;
		int skipSize = 10;
		int minShakeNumber = 10;
		int maxShakeNumber = 50;
		int minMoveNumber = 10;
		int maxMoveNumber = 50;
		std::string conf("333");
		ofstream fout;
		fout.open("inst" + std::to_string(it) + "/inst" + std::to_string(it) + "_" + std::to_string(iterCount) + "_" + conf + "_" + std::to_string(skipSize) + "_" + std::to_string(minShakeNumber) + "_" + std::to_string(maxShakeNumber) + "_" + std::to_string(minMoveNumber) + "_" + std::to_string(maxMoveNumber) + ".txt");//имя файла_число итераций_пик буф пэк_число пропуска
		ofstream fgraph;
		fgraph.open("inst" + std::to_string(it) + "/g_inst" + std::to_string(it) + "_" + std::to_string(iterCount) + "_" + conf + "_" + std::to_string(skipSize) + "_" + std::to_string(minShakeNumber) + "_" + std::to_string(maxShakeNumber) + "_" + std::to_string(minMoveNumber) + "_" + std::to_string(maxMoveNumber) + ".txt");
		if (in.is_open())
		{
			while (getline(in, line))
			{
				if (line[0] != '/') {
					istringstream ist(line);
					std::string arg1, arg2, arg3;
					getline(ist, arg1, ' ');
					getline(ist, arg2, ' ');
					getline(ist, arg3, ' ');
					Job j(stoi(arg1), stoi(arg2), stoi(arg3));
					initial.push_back(j);
				}
			}
		}
		in.close();     // закрываем
		int countJob = initial.size();
		std::vector<Job> start = initial;
		std::vector<Job> bestRes = initial;
		std::vector<Job> currentBestRes;
		std::vector<Job> usingInput;
		std::vector<Job> startHelp;
		std::vector<Job> start2;
		int bestTime = calcAndPrintFunction(initial, true, "inst" + std::to_string(it) + "/inst" + std::to_string(it) + "_" + std::to_string(iterCount) + "_" + conf + "_" + std::to_string(skipSize) + "_" + std::to_string(minShakeNumber) + "_" + std::to_string(maxShakeNumber) + "_" + std::to_string(minMoveNumber) + "_" + std::to_string(maxMoveNumber));
		cout << bestTime;
		int currentBestTime = bestTime * 2;
		int startBestTime = bestTime;
		int needShake = true;
		int neighbourNumber = 0;
		int countMoveNumber = 2;
		//aTimer.start();
		for (int l = 0; l < iterCount; l++) {
			if (needShake == 1) {
				if (neighbourNumber <= maxShakeNumber - minShakeNumber) {
					start2 = start;
					int countRandomPositions = neighbourNumber + minShakeNumber;
					std::vector<int> allIndexes(countJob);
					std::vector<int> indexes;
					std::iota(allIndexes.begin(), allIndexes.end(), 0);
					for (int i = 0; i < countRandomPositions; i++) {
						int toRemove = rand() % allIndexes.size();
						indexes.push_back(allIndexes.at(toRemove));
						allIndexes.erase(allIndexes.begin() + toRemove, allIndexes.begin() + toRemove + 1);
					}
					std::vector<Job> elementsToShuffle;
					for (std::vector<int>::const_iterator k = indexes.begin(); k != indexes.end(); ++k)
						elementsToShuffle.push_back(start2.at(*k));
					std::random_shuffle(elementsToShuffle.begin(), elementsToShuffle.end());

					for (int i = 0; i < countRandomPositions; i++) {
						start2.erase(start2.begin() + indexes.at(i), start2.begin() + indexes.at(i) + 1);
						start2.emplace(start2.begin() + indexes.at(i), elementsToShuffle.at(i));
					}
					start = start2;
				}
				else {
					start2 = start;
					int countNumbers = neighbourNumber - maxShakeNumber + minShakeNumber + minMoveNumber;
					int i = rand() % (countJob - countNumbers + 1);
					int j = rand() % (countJob - countNumbers + 1);
					std::vector<Job> partToCut(start2.begin() + i, start2.begin() + i + countNumbers);
					start2.erase(start2.begin() + i, start2.begin() + i + countNumbers);
					for (int k = 0; k < countNumbers; k++) {
						start2.emplace(start2.begin() + j + k, partToCut.at(k));
					}
					start = start2;
				}
			}
			//в fout выводим start
			needShake = false;
			startBestTime = calcFunction(start);
			currentBestTime = startBestTime;
			for (int i = 0; i < countJob - countMoveNumber + 1; i++) {//i - индекс старовой позиции
				for (int j = 0; j < countJob - countMoveNumber + 1; j++) {//j - индекс позиции вставки в исходном векторе
					if (j != i && rand() % skipSize == 1) {
						usingInput = start;
						std::vector<Job> partToCut(usingInput.begin() + i, usingInput.begin() + i + countMoveNumber);
						usingInput.erase(usingInput.begin() + i, usingInput.begin() + i + countMoveNumber);
						for (int k = 0; k < countMoveNumber; k++) {
							Job test = partToCut.at(k);//а тут может быть косяк...
							usingInput.emplace(usingInput.begin() + j + k, test);
						}
						int currentTime = calcFunction(usingInput);
						if (currentTime < currentBestTime) {
							currentBestTime = currentTime;
							currentBestRes = usingInput;
						}
					}
				}
			}
			if (currentBestTime < startBestTime) {
				start = currentBestRes;
			}
			else {
				//нашли локальный оптимум
				if (bestTime > currentBestTime) {
					bestRes = currentBestRes;
					start = currentBestRes;
					bestTime = currentBestTime;
					neighbourNumber = 0;
					needShake = true;
				}
				else {
					start = bestRes;
					currentBestRes = bestRes;
					currentBestTime = bestTime;
					//Вот тут нужно шэйк перенести на новую окр
					needShake = true;
					neighbourNumber++;
					if (neighbourNumber > maxShakeNumber - minShakeNumber + maxMoveNumber - minMoveNumber + 2) {//тут возможна ошибка
						neighbourNumber = 0;
					}
				}
			}
			// типа тут выводим в файл
			fout << l << ": ";
			for (int i = 0; i < countJob; i++) {
				fout << currentBestRes[i].getName() << " ";
			}
			fout << endl << currentBestTime << endl;
			fgraph << l << " " << currentBestTime << endl;
		}
		//aTimer.stop().print() << " milliseconds" << endl;
		fout << endl << "Best res: " << bestTime << endl;
		//aTimer.stop().print() << " milliseconds" << endl;

		fout.close();
		fgraph.close();
		int test = calcAndPrintFunction(bestRes, false, "inst" + std::to_string(it) + "/inst" + std::to_string(it) + "_" + std::to_string(iterCount) + "_" + conf + "_" + std::to_string(skipSize) + "_" + std::to_string(minShakeNumber) + "_" + std::to_string(maxShakeNumber) + "_" + std::to_string(minMoveNumber) + "_" + std::to_string(maxMoveNumber));
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
