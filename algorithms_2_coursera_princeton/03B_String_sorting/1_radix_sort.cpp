#include<assert.h>
#include<random>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

class RadixSort
{
	private:
		const unsigned int R;
		unsigned int Len;
		unsigned int* arr;
		vector<unsigned int> vec;
	public:
		RadixSort(unsigned int _len);
		~RadixSort();
		void sort_data();
};

RadixSort::~RadixSort()
{
	delete[] arr;
}

RadixSort::RadixSort(unsigned int _len):R(50)
{
	Len = _len;
	arr = new unsigned int[Len+1];

	for(unsigned int i=0; i<Len; i++)
	{
		arr[i] = rand() % R;
		vec.push_back(arr[i]);
	}
}

void RadixSort::sort_data()
{
	cout << "Input: ";
	for (unsigned int i = 0; i < Len; i++)
		cout << arr[i] << " ";
	cout << endl;
	sort(vec.begin(), vec.end());
	unsigned int* count = new unsigned int [R + 1];
	for (unsigned int i = 0; i <= R; i++)
		count[i] = 0;

	for (unsigned int i = 0; i < Len; i++)
	{
		count[1 + arr[i]]++;
	}

	for (unsigned int i = 1; i < R; i++)
	{
		count[i] += count[i-1];
	}

	unsigned int* aux = new unsigned int[Len+1];
	for (unsigned int i = 0; i < Len; i++)
	{
		aux[count[arr[i]]] = arr[i];
		count[arr[i]]++;
	}

	for (unsigned int i = 0; i < Len; i++)
		arr[i] = aux[i];
	
	for (unsigned int n = 0; n < Len; n++)
	{
		if (vec[n] != arr[n])
			assert(false);
	}

	delete[] count;
	delete[] aux;
	cout << "Output: ";
	for (unsigned int i = 0; i < Len; i++)
		cout << arr[i] << " ";
	cout << endl;
	return;
}

#if 0
int main()
{
	unsigned int LOOP = 50;
	for (unsigned int loop = 0; loop < LOOP; loop++)
	{
		cout << "\nRunning loop " << loop + 1 << "/" << LOOP << endl;
		RadixSort obj(20);
		obj.sort_data();
	}
	return 0;
}
#endif