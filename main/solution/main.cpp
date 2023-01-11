#include "../parser/parser.h"
#include "../inputData/inputData.h"
#include "../operation/operation.h"
#include "../randomTree/randomTree.h"
#include "../node/node.h"
#include <utility>
#include <map>

extern std::vector<OperationType> operations;

int main()
{
	Parser parser;
	std::vector<InputData> files;
	std::vector<InputDataLocal> filesLocal;

	files = parser.traverseFiles("../../data/MPS-Global/");
	filesLocal = parser.traverseFilesLocal("../../data/MPS-Local/");

	std::pair<double, std::queue<std::pair<int, OperationType>>> fMeasureByOperationsSequence;
	fMeasureByOperationsSequence.first = -1.0;

	srand(time(NULL));

	std::cout << "Global:\n";
	std::cout << "Numar fisiere: " << files.size() << "\n";
	for (int iteration = 0; iteration < 20; ++iteration) {
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

		// RandomTree::printSequenceOp(choices);
		
		noLeaves = 45;

		for (int fileIdx = 0; fileIdx < (int) files.size(); ++fileIdx) {
			std::vector<int> leavesOrder;

			for (int i = 0; i < noLeaves; ++i) {
				leavesOrder.push_back(rand() % files[fileIdx].getThresholds().size());
			}

			RandomTree tree = RandomTree();

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
	
	for (int iteration = 0; iteration < 1; ++iteration) {
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

		// RandomTree::printSequenceOp(choices);
		
		noLeaves = 45;
		for (int fileIdx = 0; fileIdx < (int) filesLocal.size(); ++fileIdx) {
			std::map<PixelType, int> map;

			InputDataLocal data = filesLocal[fileIdx];
			int noPixels = data.noLines;

			for (int lineIdx = 0; lineIdx < noPixels; ++lineIdx) {
				std::vector<int> leavesOrder;

				for (int i = 0; i < noLeaves; ++i) {
					leavesOrder.push_back(rand() % 10);
				}

				RandomTree tree = RandomTree();
				std::vector<double> crtThresholds = data.getThresholds()[lineIdx];

				for (auto i = 0; i < 10; ++i) {
					tree.getLeafSet().push_back(Node(crtThresholds[i]));
				}

				tree.generateTreeHierarchy(choices, leavesOrder);

				tree.applyOp(&tree.getLeavesQueue().front());

				double lineValue = tree.getLeavesQueue().front().getValue();

				PixelType p = RandomTree::getPixelType(lineValue, data.getPixelsClass()[lineIdx]);
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

	return 0;
}
