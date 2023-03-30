#pragma once
#include <iostream>
#include "StackArray.h"
#include "QueueArray.h"

template <class T>
class BinarySearchTree
{
private:

	template <class T>
	struct Node {
		T key_;
		Node<T>* left_;
		Node<T>* right_;
		Node<T>* p_;
		Node(T key, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* p = nullptr) : key_(key), left_(left), right_(right), p_(p) {}
	};

	Node<T>* root_;

	Node<T>* iterativeSearchNode(const T& key) const;
	Node<T>* iterativeSearchMin(Node<T>* tree) const;
	Node<T>* iterativeSearchMax(Node<T>* tree) const;
	Node<T>* iterativeSearchParent(const Node<T>* tree) const;

	void printNode(std::ostream& out, Node<T>* root) const;
	int getCount(const Node<T>* node) const;
	int getHeight(const Node<T>* node) const;
	void inorderWalk(Node<T>* node) const;

	void swap(BinarySearchTree<T>& scr);
	bool deleteNode(Node<T>* del);
	bool insertNode(Node<T>* newNode);
	

public:
	BinarySearchTree() : root_(nullptr) {};
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
	virtual ~BinarySearchTree();

	bool iterativeSearch(const T& key) const;
	bool insert(const T& key);
	bool deleteKey(const T& key);
	int getCount() const;
	int getHeight() const;
	void inorderWalk() const;
	void print(std::ostream& out) const;

	bool isEmpty() const;
	bool deleteUnderTree(Node<T>* tree);
	
	void iterativeInorderWalk() const;
	void walkByLevels() const;

	// 10 Являются ли два дерева похожими
	bool isSimilar(const BinarySearchTree<T>& other) const;
	bool isSimilarByNode(const Node<T>* root, const Node<T>* other) const;
	
	// Есть одинаковые ключи в двух деревьях поиска
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;
	bool isIdenticalNode(const Node<T>* node, const BinarySearchTree<T>& other) const;

};

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept
{
	this->root_ = scr.root_;
	scr.root_ = nullptr;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept
{
	if (&src == this) {
		swap(src);
	}
	return *this;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteUnderTree(this->root_);
}

template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key);
}

template<class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* newNode = new Node<T>(key);
	if (insertNode(newNode)) {
		return true;
	}
	delete newNode;
	return false;
}

template<class T>
inline bool BinarySearchTree<T>::insertNode(Node<T>* newNode)
{
	if (newNode == nullptr) {
		return false;
	}
	if (isEmpty()) {
		this->root_ = newNode;
		return true;
	}
	Node<T>* temp = this->root_;
	while (temp != nullptr) {
		if (newNode->key_ < temp->key_) {
			if (temp->left_) {
				temp = temp->left_;
				continue;
			}
			else {
				temp->left_ = newNode;
				newNode->p_ = temp;
				return true;
			}
		}
		else if (newNode->key_ > temp->key_) {
			if (temp->right_) {
				temp = temp->right_;
				continue;
			}
			else {
				temp->right_ = newNode;
				newNode->p_ = temp;
				return true;
			}
		}
	}
	return false;
}

template<class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	if (isEmpty()) {
		return false;
	}
	Node<T>* del = iterativeSearchNode(key);
	if (del == nullptr) {
		return false;
	}
	return deleteNode(del);
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	Node<T>* temp = this->root_;
	while (temp->key_ != key) {
		if (key < temp->key_) {
			if (temp->left_ != nullptr) {
				temp = temp->left_;
				continue;
			}
			else {
				return nullptr;
			}
			
		}
		else {
			if (temp->right_ != nullptr) {
				temp = temp->right_;
				continue;
			}
			else {
				return nullptr;
			}
		}
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchMin(Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	if (tree == nullptr) {
		return tree;
	}
	Node<T>* temp = tree;
	while (temp->left_ != nullptr) {
		temp = temp->left_;
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchMax(Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	Node<T>* temp = tree;
	while (temp->right_ != nullptr) {
		temp = temp->right_;
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchParent(const Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	if (tree == this->root_) {
		return nullptr;
	}
	Node<T>* temp = this->root_;
	Node<T>* parent = nullptr;
	while (temp && temp != tree) {
		parent = temp;
		if (temp->key_ > tree->key_) {
			temp = temp->left_;
		}
		else {
			temp = temp->right_;
		}
	}
	return parent;
}

template<class T>
inline int BinarySearchTree<T>::getCount(const Node<T>* node) const
{
	if (node == nullptr) {
		return 0;
	}
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template<class T>
inline int BinarySearchTree<T>::getHeight(const Node<T>* node) const
{
	if (node == nullptr) {
		return 0;
	}
	return (1 + std::max(getHeight(node->left_), getHeight(node->right_)));
}

template<class T>
inline int BinarySearchTree<T>::getHeight() const
{
	if (!isEmpty()) {
		return getHeight(this->root_);
	}
	return 0;
}

template<class T>
inline int BinarySearchTree<T>::getCount() const
{
	if (!isEmpty()) {
		return getCount(this->root_);
	}
	return 0;
}

template<class T>
inline void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
{
	if (!this->isEmpty()) {
		if (node->left_ != nullptr) {
			inorderWalk(node->left_);
		}
		std::cout << node->key_ << " ";
		if (node->right_ != nullptr) {
			inorderWalk(node->right_);
		}
	}
}

template<class T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& scr)
{
	std::swap(this->root_, scr.root_);
}

template<class T>
inline bool BinarySearchTree<T>::deleteNode(Node<T>* del)
{
	Node<T>* par = iterativeSearchParent(del);
	if (del->right_ && del->left_) {
		Node<T>* newKey = iterativeSearchMin(del->right_);
		del->key_ = newKey->key_;
		deleteNode(newKey);
		return true;
	}
	else if (del->right_) {
		if (del == this->root_) {
			this->root_ = del->right_;
			del->right_->p_ = nullptr;
		}
		if (del == par->left_) {
			par->left_ = del->right_;
			del->right_->p_ = par;
		}
		else {
			par->right_ = del->right_;
			del->right_->p_ = par;
		}
	}
	else if (del->left_) {
		if (del == this->root_) {
			this->root_ = del->left_;
			del->left_->p_ = nullptr;
		}
		else if (del == del->p_->left_) {
			del->p_->left_ = del->left_;
		}
		else {
			del->p_->right_ = del->left_;
		}
	}
	else {
		if (del == this->root_) {
			delete del;
			return true;
		}
		else if (del == par->left_) {
			par->left_ = nullptr;
		}
		else {
			par->right_ = nullptr;
		}
	}
	delete del;
	return true;
}

template<class T>
inline void BinarySearchTree<T>::inorderWalk() const
{
	Node<T>* temp = this->root_;
	inorderWalk(temp);
}

template<class T>
inline bool BinarySearchTree<T>::isEmpty() const
{
	return this->root_ == nullptr;
}

template<class T>
bool BinarySearchTree<T>::deleteUnderTree(Node<T>* tree)
{
	if (tree) {
		deleteUnderTree(tree->left_);
		deleteUnderTree(tree->right_);
		delete tree;
		return true;
	}
	return false;
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const {
	out << '(';
	if (root) {
		out << root->key_;
		printNode(out, root->left_);
		printNode(out, root->right_);
	}
	out << ')';
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const {
	if (isEmpty()) {
		std::cout << "Binary Tree is empty.\n";
		return;
	}
	printNode(out, this->root_);
}

template<class T>
void BinarySearchTree<T>::iterativeInorderWalk() const {
	if (isEmpty()) {
		return;
	}
	StackArray<BinarySearchTree<T>::Node<T>*> stack;
	Node<T>* temp = this->root_;
	while (!stack.isEmpty() || temp != nullptr) {
		if (temp != nullptr) {
			stack.push(temp);
			temp = temp->left_;
		}
		else {
			temp = stack.pop();
			std::cout << temp->key_ << " ";
			temp = temp->right_;
		}
	}
}

template<class T>
void BinarySearchTree<T>::walkByLevels() const {
	if (isEmpty()) {
		return;
	}
	QueueArray<BinarySearchTree<T>::Node<T>*> queue;
	Node<T>* temp = this->root_;
	queue.enQueue(temp);
	while (!queue.isEmpty()) {
		temp = queue.deQueue();
		std::cout << temp->key_ << " ";
		if (temp->left_ != nullptr) {
			queue.enQueue(temp->left_);
		}
		if (temp->right_ != nullptr) {
			queue.enQueue(temp->right_);
		}
	}
}

template<class T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const {
	if (this->isEmpty() && other.isEmpty()) {
		return true;
	}
	else if (this->isEmpty() || other.isEmpty()) {
		return false;
	}
	Node<T>* tempThis = this->root_;
	Node<T>* tempOther = other.root_;
	return isSimilarByNode(tempThis, tempOther);
}

template<class T>
bool BinarySearchTree<T>::isSimilarByNode(const Node<T>* root, const Node<T>* other) const {
	if (root == nullptr && other == nullptr) {
		return true;
	}
	return (root && other) && (root->key_ == other->key_) && isSimilarByNode(root->left_, other->left_) && isSimilarByNode(root->right_, other->right_);
}

template<class T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const {
	if (this->isEmpty() && other.isEmpty()) {
		return true;
	}
	else if (this->isEmpty() || other.isEmpty()) {
		return false;
	}
	Node<T>* tempThis = this->root_;
	return isIdenticalNode(tempThis, other);
}

template<class T>
bool BinarySearchTree<T>::isIdenticalNode(const Node<T>* node, const BinarySearchTree<T>& other) const {
	if (node) {
		if (other.iterativeSearch(node->key_)) {
			return true;
		}
		else {
			return (isIdenticalNode(node->left_, other) || isIdenticalNode(node->right_, other));
		}
	}
	return false;
}

