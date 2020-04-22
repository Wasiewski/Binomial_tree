#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdio.h>
using namespace std;
#define SIZE 1000

struct Wezel {
	int value;
	int  degree;//ilosc potomkow
	Wezel*child;//wsk na potomka
	Wezel*sibling;//wsk na 1 brata
	Wezel*parent;//wsk na rodzica

	Wezel() {
		value = 0;
		degree = NULL;
		child = NULL;
		sibling = NULL;
		parent = NULL;
	}
};
class BinominalTree {
public:


	void link(Wezel *child, Wezel *parent) { //polaczenie dwoch poddrzew 
		child->parent = parent;
		child->sibling = NULL;
		Wezel *tmp = parent->child;
		if (tmp == NULL) {
			parent->child = child;
		}
		else {
			while (tmp->sibling != NULL) {
				tmp = tmp->sibling;
			}
			tmp->sibling = child;
		}
		parent->degree++;

	}
	Wezel* insert(int value) {
		Wezel*temp = new Wezel();
		temp->value = value;
		return temp;
	}
	Wezel* insert(Wezel*node2, int value) {
		Wezel*node = initheap();
		node->degree = 0;
		node->parent = NULL;
		node->child = NULL;
		node->value = value;
		node->sibling = NULL;
		return mergeHeap(node2, node);

	}
	Wezel*initheap() {
		Wezel*temp = new Wezel();
		temp->parent = NULL;
		return temp;
	}

	void heapify(Wezel *node, bool ifUp) {
		if (ifUp) {
			while (node->parent != NULL) {
				if (node->value > node->parent->value) {
					int tmp = node->value;
					node->value = node->parent->value;
					node->parent->value = tmp;
					node = node->parent;
				}
				else {
					return;
				}
			}
		}
		else {
			while (node->child != NULL) {
				Wezel *maxChild = node->child;
				Wezel *currentChild = maxChild->sibling;
				while (currentChild != NULL) {
					if (currentChild->value > maxChild->value) {
						maxChild = currentChild;
					}
					currentChild = currentChild->sibling;
				}
				if (maxChild->value > node->value) {
					int tmp = node->value;
					node->value = maxChild->value;
					maxChild->value = tmp;
					node = maxChild;
				}
			}
		}
	}

	bool ChangeValue(Wezel* node, int oldValue, int newValue) {
		if (node == NULL) {
			return false;
		}
		if (oldValue == newValue) {
			return true;
		}
		Wezel* x = node;
		if (x->value == oldValue) {
			x->value = newValue;
			heapify(x, oldValue < newValue);
			return true;
			/*p = x;
			p->value = newValue;
			if (p->value > p->child->value)
			{
					temp->value = p->value;
					p->value = p->child->value;
					p->child->value = temp->value;
			}*/


		}
		bool valueChanged = false;
		if (x->child != NULL && x->value > oldValue) {
			valueChanged = ChangeValue(x->child, oldValue, newValue);
			if (valueChanged) {
				return true;
			}
		}

		if (x->sibling != NULL) {
			valueChanged = ChangeValue(x->sibling, oldValue, newValue);
			if (valueChanged) {
				return true;
			}
		}
		return false;

	}
	Wezel*extractMax(Wezel*node, int * max) {
		if (node == NULL) {
			return NULL;
		}

		Wezel*maxNode = node;
		Wezel*maxPrex = NULL;
		Wezel*current = node;

		if (maxNode->sibling == NULL && maxNode->child == NULL) {//root
			*max = maxNode->value;
			maxNode = NULL;
			delete maxNode;
			return NULL;
		}

		while (current->sibling != NULL)
		{
			if (current->sibling->value > maxNode->value) {
				maxPrex = current;
				maxNode = current->sibling;
			}
			current = current->sibling;
		}
		Wezel *retVal;
		if (maxPrex == NULL) {
			retVal = mergeHeap(node->sibling, node->child);
		}
		else {
			maxPrex->sibling = maxNode->sibling;
			retVal = mergeHeap(node, maxNode->child);
		}
		*max = maxNode->value;
		delete maxNode;
		return retVal;
	}

	Wezel *mergeHeap(Wezel *master, Wezel *secondary)
	{
		if (master == NULL)
		{
			if (secondary != NULL) {
				secondary->parent = NULL;
			}
			return secondary;
		}
		if (secondary == NULL)
		{
			if (master == NULL)
			{
				master->parent = NULL;
			}
			return master;
		}
		if (master->degree > secondary->degree)
		{

			Wezel *tmp = master;
			master = secondary;
			secondary = tmp;
		}


		Wezel *mergedIterator = master;
		Wezel *iteratorMaster = master->sibling;
		Wezel *iteratorSecondary = secondary;
		if (iteratorMaster == NULL)
		{
			mergedIterator->sibling = iteratorSecondary;
		}
		else
		{
			while (iteratorMaster != NULL && iteratorSecondary != NULL)
			{
				if (iteratorMaster->degree <= iteratorSecondary->degree)
				{
					mergedIterator->sibling = iteratorMaster;
					mergedIterator = mergedIterator->sibling;
					iteratorMaster = iteratorMaster->sibling;
					if (iteratorMaster == NULL)
					{
						mergedIterator->sibling = iteratorSecondary;
					}
				}
				else
				{
					mergedIterator->sibling = iteratorSecondary;
					mergedIterator = mergedIterator->sibling;
					iteratorSecondary = iteratorSecondary->sibling;
					if (iteratorSecondary == NULL)
					{
						mergedIterator->sibling = iteratorMaster;
					}
				}
			}
		}


		iteratorMaster = master;
		Wezel * prev = NULL;
		while (iteratorMaster->sibling != NULL)
		{
			iteratorMaster->parent = NULL;
			if (iteratorMaster->degree == iteratorMaster->sibling->degree)
			{
				Wezel *parent;
				Wezel *child;
				if (iteratorMaster->value < iteratorMaster->sibling->value)
				{
					parent = iteratorMaster->sibling;
					child = iteratorMaster;
				}
				else
				{
					parent = iteratorMaster;
					child = iteratorMaster->sibling;
					parent->sibling = child->sibling;
					child->sibling = NULL;
				}
				link(child, parent);
				if (master == child)
				{
					master = parent;
				}
				if (prev != NULL) {
					prev->sibling = parent;
				}
				iteratorMaster = parent;
			}
			else
			{
				prev = iteratorMaster;
				iteratorMaster = iteratorMaster->sibling;
			}
		}

		return master;
	}


};

int main()
{
	BinominalTree tree;

	int testy;
	//scanf("%d", &testy);
	cin >> testy;
	//getchar();
	int firstgroup;
	int value;
	char znak;
	int max;
	Wezel * tablica[SIZE] = { NULL };
	int nextGroup;
	int oldValue, newValue;
	Wezel * tmp = NULL;
	for (int i = 0; i < testy; i++) {
		getchar();
		cin >> znak;
		switch (znak)
		{
		case'a':
			//scanf("%d %d", &firstgroup, &newValue);
			cin >> firstgroup >> newValue;
			//newValue = newValue*-1;
			if (tablica[firstgroup] == NULL) {
				Wezel*wsk = tree.insert(newValue);
				tablica[firstgroup] = wsk;
			}
			else {
				tablica[firstgroup] = tree.insert(tablica[firstgroup], newValue);
			}
			break;
		case'e':
			//scanf("%d", &firstgroup);
			cin >> firstgroup;
			if (tablica[firstgroup] == NULL)
			{
				printf("na\n");
			}
			else {
				tablica[firstgroup] = tree.extractMax(tablica[firstgroup], &max);
				printf("%d\n", max);

			}
			break;
		case'p':
			//scanf("%d", &firstgroup);
			cin >> firstgroup;
			tmp = NULL;
			if (tablica[firstgroup] != NULL) {
				while (tablica[firstgroup] != NULL) {
					tablica[firstgroup] = tree.extractMax(tablica[firstgroup], &max);
					printf("%d ", max);
					tmp = tree.insert(tmp, max);
				}
				printf("\n");
				tablica[firstgroup] = tmp;
			}
			else {
				printf("na\n");
			}
			break;
		case'm':
			//scanf("%d %d", &firstgroup, &nextGroup);
			cin >> firstgroup >> nextGroup;
			tablica[firstgroup] = tree.mergeHeap(tablica[firstgroup], tablica[nextGroup]);
			tablica[nextGroup] = NULL;
			break;
		case'i':
			//scanf("%d %d %d", &firstgroup, &oldValue, &newValue);
			cin >> firstgroup >> oldValue >> newValue;
			//newValue = newValue*-1;
			//oldValue = oldValue*-1;
			if (tree.ChangeValue(tablica[firstgroup], oldValue, newValue) == false) {
				printf("na\n");
			}
			break;

		default:
			break;
		}
		//getchar();

	}
	system("pause");
	return 0;
}