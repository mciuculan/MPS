#include "../parser/parser.h"
#include "../inputData/inputData.h"
#include "../operation/operation.h"
#include "../randomTree/randomTree.h"
#include "../node/node.h"
#include <utility>
#include "../tests/tests.h"

#define THRESHOLDS 15

extern std::vector<OperationType> operations;

int main(int argc, char *argv[])
{
	std::string mode;
	std::cin >> mode;

	if (mode.compare("run") == 0)
	{

		Parser parser;
		std::vector<InputData> files;

		files = parser.traverseFiles("../data/MPS-Global/");

		std::pair<double, Node> fMeasureByOperationsSequence;
		fMeasureByOperationsSequence.first = -1.0;

		for (int iteration = 0; iteration < 10; ++iteration) {
			std::cout << iteration << "\n";

			int noLeaves = 45;
			srand(time(NULL));
			std::vector<int> leavesOrder;
			double totalFMeasure = 0.0;

			for (int i = 0; i < noLeaves; ++i) {
				leavesOrder.push_back(rand() % THRESHOLDS);
			}

			int noPickedChildren;
			OperationType op;
			std::queue<std::pair<int, OperationType>> choices;

			while (noLeaves > 1) {
				noPickedChildren = rand() % (noLeaves - 1) + 2;
				op = operations[rand() % operations.size()];
				choices.push({noPickedChildren, op});
				noLeaves = noLeaves - noPickedChildren + 1;
			}
			
			Node finalRoot = Node();
			for (int fileIdx = 0; fileIdx < (int) files.size(); ++fileIdx) {
				RandomTree tree = RandomTree();

				for (auto i = 0; i < (int) files[fileIdx].getThresholds().size(); ++i) {
					tree.getLeafSet().push_back(Node(files[fileIdx].getThresholds()[i]));
				}

				tree.generateTreeHierarchy(choices, leavesOrder);

				if (fileIdx == 0) {
					finalRoot = tree.getLeavesQueue().front();
				}

				tree.applyOp(&tree.getLeavesQueue().front());

				totalFMeasure += files[fileIdx].getFMeasures()[InputData::getFMeasureIndex(tree.getLeavesQueue().front().getValue())];
			}

			double meanTotalFMeasure = totalFMeasure / files.size();
			if (meanTotalFMeasure > fMeasureByOperationsSequence.first) {
				fMeasureByOperationsSequence.first = meanTotalFMeasure;
				fMeasureByOperationsSequence.second = finalRoot;
			}
		}

		std::cout << fMeasureByOperationsSequence.first << "\n";
		RandomTree().printTree(fMeasureByOperationsSequence.second);
		std::cout << "\n";
	}

	if (mode.compare("test") == 0)
	{
		return run_tests(argc, argv);
	}

	return 0;
}
