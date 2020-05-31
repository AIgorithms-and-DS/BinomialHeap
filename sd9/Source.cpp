#include "Header.h"

int main() {
	setlocale(0, "");
	list<BinomialHeap*> heap;
	BinomialHeap temp;
	
	int N;
	cout << "Input size of heap\n";
	cin >> N;

	cout << "Input elements of heap\n";
	for (int i = 0, buf; i < N; ++i)
	{
		cin >> buf;
		heap = temp.insert(heap, buf);
	}

	//delete element with maxPriority
	heap = temp.deleteMaxPriority(heap);

	//output heap
	system("cls");
	list<BinomialHeap*>::iterator it;
	for (it = heap.begin(); it != heap.end(); it++) {
		temp.Print_BinomialHeap("", *it, false, false, 1);
		cout << endl << endl << endl;
	}

	system("pause");
	return 0;
}