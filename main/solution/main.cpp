#include "../parser/parser.h"
#include "../inputData/inputData.h"
#include "../operation/operation.h"
#include "../randomTree/randomTree.h"
#include "../node/node.h"
#include <utility>
#include <map>
#include <chrono>
#include <omp.h>
#include "../tests/tests.h"

extern std::vector<OperationType> operations;

int main(int argc, char *argv[])
{
	std::string mode;
	std::cin >> mode;

	if (mode.compare("run") == 0) {
		Parser parser;
		std::vector<InputData> files;
		std::vector<InputDataLocal> filesLocal;

		files = parser.traverseFiles("../../data/MPS-Global/");
		filesLocal = parser.traverseFilesLocal("../../data/MPS-Local/");

		std::pair<double, std::queue<std::pair<int, OperationType>>> fMeasureByOperationsSequence;
		fMeasureByOperationsSequence.first = -1.0;

		srand(time(NULL));

		// auto start = std::chrono::steady_clock::now();

		std::cout << "Global:\n";
		std::cout << "Numar fisiere: " << files.size() << "\n";
		for (int iteration = 0; iteration < 100; ++iteration) {
			int noLeaves = 45;

			double totalFMeasure = 0.0;

			int noPickedChildren;
			OperationType op;
			std::queue<std::pair<int, OperationType>> choices;

			while (noLeaves > 1) {
				noPickedChildren = rand() % (noLeaves - 1) + 2;
				op = operations[rand() % operations.size()];
				choices.push({noPickedChildren, op});
				noLeaves = noLeaves - noPickedChildren + 1;
			}
			
			noLeaves = 45;

			for (int fileIdx = 0; fileIdx < (int) files.size(); ++fileIdx) {
				std::vector<int> leavesOrder;

				for (int i = 0; i < noLeaves; ++i) {
					leavesOrder.push_back(rand() % files[fileIdx].getThresholds().size());
				}

				RandomTree tree;

				for (auto i = 0; i < (int) files[fileIdx].getThresholds().size(); ++i) {
					tree.getLeafSet().push_back(Node(files[fileIdx].getThresholds()[i]));
				}

				tree.generateTreeHierarchy(choices, leavesOrder);

				tree.applyOp(&tree.getLeavesQueue().front());

				totalFMeasure += files[fileIdx].getFMeasures()[InputData::getFMeasureIndex(tree.getLeavesQueue().front().getValue())];
			}

			double meanTotalFMeasure = totalFMeasure / files.size();
			if (meanTotalFMeasure > fMeasureByOperationsSequence.first) {
				fMeasureByOperationsSequence.first = meanTotalFMeasure;
				fMeasureByOperationsSequence.second = choices;
			}
		}

		std::cout << fMeasureByOperationsSequence.first << "\n";
		RandomTree::printSequenceOp(fMeasureByOperationsSequence.second);
		std::cout << "\n";


		std::cout << "Local:\n";
		std::cout << "Numar fisiere: " << filesLocal.size() << "\n";
		std::pair<double, std::queue<std::pair<int, OperationType>>> fMeasureByOperationsSequenceLocal;
		fMeasureByOperationsSequenceLocal.first = -1.0;
		
		for (int iteration = 0; iteration < 5; ++iteration) {
			std::cout << "iteration " << iteration << "\n";
			double totalFMeasure = 0.0;
			int noLeaves = 45;

			int noPickedChildren;
			OperationType op;
			std::queue<std::pair<int, OperationType>> choices;

			while (noLeaves > 1) {
				noPickedChildren = rand() % (noLeaves - 1) + 2;
				op = operations[rand() % operations.size()];
				choices.push({noPickedChildren, op});
				noLeaves = noLeaves - noPickedChildren + 1;
			}
			
			noLeaves = 45;
			for (int fileIdx = 0; fileIdx < (int) filesLocal.size(); ++fileIdx) {
				std::map<PixelType, int> map;

				InputDataLocal data = filesLocal[fileIdx];
				int noPixels = data.noLines;

				#pragma omp parallel for
				for (int lineIdx = 0; lineIdx < noPixels; ++lineIdx) {
					std::vector<int> leavesOrder;

					for (int i = 0; i < noLeaves; ++i) {
						leavesOrder.push_back(rand() % 10);
					}

					RandomTree tree;
					std::vector<double> crtThresholds = data.getThresholds()[lineIdx];

					for (auto i = 0; i < 10; ++i) {
						tree.getLeafSet().emplace_back(crtThresholds[i]);
					}

					tree.generateTreeHierarchy(choices, leavesOrder);

					tree.applyOp(&tree.getLeavesQueue().front());

					double lineValue = tree.getLeavesQueue().front().getValue();

					PixelType p = RandomTree::getPixelType(lineValue, data.getPixelsClass()[lineIdx]);

					#pragma omp critical
					map[p]++;
				}

				double tmpFMeasure = map[TRUE_POSITIVE] / (map[TRUE_POSITIVE] + 0.5 * (map[FALSE_POSITIVE] + map[FALSE_NEGATIVE]));
				totalFMeasure += tmpFMeasure;
			}

			double meanTotalFMeasure = totalFMeasure / filesLocal.size();
			if (meanTotalFMeasure > fMeasureByOperationsSequenceLocal.first) {
				fMeasureByOperationsSequenceLocal.first = meanTotalFMeasure;
				fMeasureByOperationsSequenceLocal.second = choices;
			}
		}

		std::cout << fMeasureByOperationsSequenceLocal.first << "\n";
		RandomTree::printSequenceOp(fMeasureByOperationsSequenceLocal.second);
		std::cout << "\n";
	}

	

	// auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end - start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

	if (mode.compare("test") == 0) {
		return run_tests(argc, argv);
	}

	return 0;
}
