#include<assert.h>
#include<random>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

class QuickSort
{
	private:
		const unsigned int R;
		unsigned int Len;
		int* arr;
		vector<int> vec;
	public:
		QuickSort(unsigned int _len);
		~QuickSort();
		void sort_data();
		void qsort(int* arr, int start, int end);
};

QuickSort::~QuickSort()
{
	delete[] arr;
}

QuickSort::QuickSort(unsigned int _len):R(20)
{
	Len = _len;
	arr = new int[Len+1];

	for(unsigned int i=0; i<Len; i++)
	{
		arr[i] = rand() % R;
		vec.push_back(arr[i]);
	}
}

void QuickSort::qsort(int* arr, int start, int end)
{
	if(start >= end)
		return;

	int key = arr[start];
	unsigned int left = start;
	unsigned int right = end;
	while(left <= right)
	{
			if(arr[left] <= key)
				left++;
			else if (arr[right] > key)
				right--;
			else
				swap(arr[left], arr[right]);
	}

	swap(arr[start], arr[left-1]);
	qsort(arr, start, left-2);
	qsort(arr, left, end);
}

void QuickSort::sort_data()
{
	cout << "Input: ";
	for (unsigned int i = 0; i < Len; i++)
		cout << arr[i] << " ";
	cout << endl;
	sort(vec.begin(), vec.end());

	qsort(arr, 0,Len-1);

	cout << "Output: ";
	for (unsigned int i = 0; i < Len; i++)
		cout << arr[i] << " ";
	cout << endl;

	for (unsigned int n = 0; n < Len; n++)
	{
		if (vec[n] != arr[n])
			assert(false);
	}

	return;
}

#if 0
int main()
{
	unsigned int LOOP = 5000;
	for (unsigned int loop = 0; loop < LOOP; loop++)
	{
		cout << "\nRunning loop " << loop + 1 << "/" << LOOP << endl;
		QuickSort obj(50);
		obj.sort_data();
	}
	return 0;
}
#endif