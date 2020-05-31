#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <conio.h>

using namespace std;


class BinomialHeap {
	int data;
	int degree;
	BinomialHeap* child;
	BinomialHeap* sibling;
	BinomialHeap* parent;
public:

	BinomialHeap* creat(int key) {
		BinomialHeap* temp = new BinomialHeap;
		temp->data = key;
		temp->degree = NULL;
		temp->child = temp->parent = temp->sibling = NULL;
		return temp;
	}


	list<BinomialHeap*> sort_degree(list<BinomialHeap*> l1, list<BinomialHeap*> l2) {
		list<BinomialHeap*> _new;
		list<BinomialHeap*>::iterator it = l1.begin();
		list<BinomialHeap*>::iterator ot = l2.begin();
		while (it != l1.end() && ot != l2.end()) {
			if ((*it)->degree <= (*ot)->degree) {
				_new.push_back(*it);
				it++;
			}
			else {
				_new.push_back(*ot);
				ot++;
			}
		}
		while (it != l1.end()) {
			_new.push_back(*it);
			it++;
		}
		while (ot != l2.end()) {
			_new.push_back(*ot);
			ot++;
		}
		return _new;
	}

	BinomialHeap* merge(BinomialHeap* b1, BinomialHeap* b2) {
		if (b1->data > b2->data) {
			BinomialHeap* temp;
			temp = b1;
			b1 = b2;
			b2 = temp;
		}
		b2->parent = b1;
		b2->sibling = b1->child;
		b1->child = b2;
		b1->degree++;
		return b1;
	}

	list<BinomialHeap*> invariant_2(list<BinomialHeap*> heap) {
		if (heap.size() == 1) {
			return heap;
		}
		list<BinomialHeap*> newheap;
		list<BinomialHeap*>::iterator it1, it2, it3;

		it1 = it2 = it3 = heap.begin();
		 
		if (heap.size() == 2) {
			//it2 = it1;
			it2++;
			it3 = heap.end();
		}
		else {
			it2++;
			it3 = it2;
			it3++;
		}
		while (it1 != heap.end()) {
			if (it2 == heap.end()) {
				it1++;
			}
			else if ((*it1)->degree < (*it2)->degree) {
				it1++;
				it2++;
				if (it3 != heap.end())
					it3++;
			}
			else if (it3 != heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree) {
				it1++;
				it2++;
				it3++;
			}
			else if ((*it1)->degree == (*it2)->degree) {
				*it1 = merge(*it1, *it2);
				it2 = heap.erase(it2);
				if (it3 != heap.end()) {
					it3++;
				}
			}
		}
		return heap;
	}

	list<BinomialHeap*> insertInHeap(list<BinomialHeap*> heap, BinomialHeap* tree) {
		list<BinomialHeap*> temp;
		temp.push_back(tree);
		temp = sort_degree(heap, temp);
		list<BinomialHeap*> _temp = invariant_2(temp);
		return _temp;
	}

	list<BinomialHeap*> insert(list<BinomialHeap*> _head, int key) {
		BinomialHeap* temp = creat(key);
		list<BinomialHeap*> _temp = insertInHeap(_head, temp);
		return _temp;
	}

	list<BinomialHeap*> removeMaxPriority(BinomialHeap* tree) {
		list<BinomialHeap*> heap;
		BinomialHeap* temp = tree->child;
		BinomialHeap* lo;
		while (temp) {
			lo = temp;
			temp = temp->sibling;
			lo->sibling = NULL;
			heap.push_front(lo);
			//heap.insert(heap.begin(), lo);
		}
		return heap;
	}

	BinomialHeap* getMaxPriority(list<BinomialHeap*> heap) {
		list<BinomialHeap*>::iterator it = heap.begin();
		BinomialHeap* temp = *it;
		while (it != heap.end()) {
			if ((*it)->data < temp->data) {
				temp = *it;
			}
			it++;
		}
		return temp;
	}

	list<BinomialHeap*> deleteMaxPriority(list<BinomialHeap*> heap) {
		list<BinomialHeap*> newheap, lo;
		BinomialHeap* temp;
		temp = getMaxPriority(heap);
		list<BinomialHeap*>::iterator it;
		it = heap.begin();
		while (it != heap.end()) {
			if (*it != temp) {
				newheap.push_back(*it);
			}
			it++;
		}
		lo = removeMaxPriority(temp);
		newheap = sort_degree(newheap, lo);
		list<BinomialHeap*> _temp = invariant_2(newheap);
		return _temp;
	}

	void Print_BinomialHeap(const string& probel, const BinomialHeap* top, bool childs, bool viv, int l) {
		bool ghg = false;
		while (top != 0) {
			if (top != 0) {
				if (top->child != 0 || top->sibling != 0) {
					viv = true;
				}
				else {
					viv = false;
				}
				cout << probel;
				if (childs) {
					cout << "|----:" << top->data << endl;
				}
				else {
					if (l == 1) {
						cout << "------" << top->data << endl;
						l++;
						if (top->child == 0 && top->parent == 0) {
							ghg = true;
						}
					}
				}
				if (childs) {
					Print_BinomialHeap(probel + "|     ", top->child, true, viv, l);
				}
				else {
					Print_BinomialHeap(probel + "      ", top->child, true, viv, l);
				}
				top = top->sibling;
			}
		}
	}
};