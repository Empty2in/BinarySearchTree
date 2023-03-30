#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"

void readTree(BinarySearchTree<int>& tree);
void printAllAboutTree(BinarySearchTree<int>& tree);
void deletTest(BinarySearchTree<int>& tree);
void searchTest(BinarySearchTree<int>& tree);
void compareTrees(BinarySearchTree<int>& tree1, BinarySearchTree<int>& tree2);

int main() {

	try {
		BinarySearchTree<int> tree1;
		readTree(tree1);
		printAllAboutTree(tree1);
		deletTest(tree1);
		searchTest(tree1);

		BinarySearchTree<int> tree2_other;
		readTree(tree2_other);
		printAllAboutTree(tree2_other);

		compareTrees(tree1, tree2_other);

		BinarySearchTree<int> tree2_sim;
		readTree(tree2_sim);
		printAllAboutTree(tree2_sim);

		compareTrees(tree2_sim, tree2_other);
	}
	catch (std::exception& e) {
		std::cerr << "ERROR: " << e.what() << '\n';
		exit(-1);
	}
	return 0;
}

void readTree(BinarySearchTree<int>& tree) {
	std::fstream in;
	std::string fileName;
	std::cout << "\nEnter file name: ";
	std::cin >> fileName;
	in.open(fileName);
	if (!in.is_open()) {
		throw std::exception("failed to open file.");
	}
	if (in.peek() == EOF) {
		throw std::exception("file is empty.");
	}
	while (!in.eof()) {
		int data;
		in >> data;
		if (!in) {
			throw std::exception("incorrect data.");
		}
		tree.insert(data);
	}
	in.close();
}
void printAllAboutTree(BinarySearchTree<int>& tree) {
	std::cout << "Print: ";
	tree.print(std::cout);
	std::cout << "\niterative Inorder Walk: ";
	tree.iterativeInorderWalk();
	std::cout << "\nInorder Walk: ";
	tree.inorderWalk();
	std::cout << "\nCount: " << tree.getCount();
	std::cout << "\nHeigh: " << tree.getHeight();
}
void deletTest(BinarySearchTree<int>& tree) {
	int del;
	std::cout << "\n\nTry delete different elements.";
	std::cout << "\nDelete unreal key: ";
	std::cin >> del;
	tree.deleteKey(del);
	tree.print(std::cout);

	std::cout << "\nDelete node with 0 child: ";
	std::cin >> del;
	std::cout << (tree.deleteKey(del) ? "SUCCSSES\n" : "FAILED\n");
	tree.print(std::cout);

	std::cout << "\nDelete node with 1 child: ";
	std::cin >> del;
	std::cout << (tree.deleteKey(del) ? "SUCCSSES\n" : "FAILED\n");
	tree.print(std::cout);

	std::cout << "\nDelete node with 2 child: ";
	std::cin >> del;
	std::cout << (tree.deleteKey(del) ? "SUCCSSES\n" : "FAILED\n");
	tree.print(std::cout);

	std::cout << "\nDelete node with root: ";
	std::cin >> del;
	std::cout << (tree.deleteKey(del) ? "SUCCSSES\n" : "FAILED\n");
	tree.print(std::cout);
}
void searchTest(BinarySearchTree<int>& tree) {
	int ser;
	std::cout << "\n\nTest Search Method.";
	std::cout << "\nEnter the data for search: ";
	std::cin >> ser;
	std::cout << (tree.iterativeSearch(ser) ? "FOUND" : "NOT FOUND");

	std::cout << "\nEnter the data for search: ";
	std::cin >> ser;
	std::cout << (tree.iterativeSearch(ser) ? "FOUND" : "NOT FOUND");
	std::cout << '\n';
}
void compareTrees(BinarySearchTree<int>& tree1, BinarySearchTree<int>& tree2) {
	std::cout << "\n\nCompare two trees.";
	std::cout << "\nTree 1: ";
	tree1.iterativeInorderWalk();
	std::cout << "\nTree 2: ";
	tree2.iterativeInorderWalk();
	std::cout << (tree1.isSimilar(tree2) ? "\ntrees are similar" : "\ntrees aren't similar");
	std::cout << (tree1.isIdenticalKey(tree2) ? "\ntrees have similar keys" : "\ntrees haven't similar keys");
	std::cout << '\n';
}