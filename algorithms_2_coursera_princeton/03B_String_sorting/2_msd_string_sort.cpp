#include<assert.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class MsdSort
{
private:
		unsigned int SIZE;
		unsigned int MAX_LEN;
		unsigned int MAX_RANGE;
		vector<string> arr_vec;
		char** arr_ptr;
		void MsdStringSort(int start, int end, unsigned int pos);

public:
	MsdSort(const int _size);
	~MsdSort();
	void createRandomArray();
	void sortRandomArray();
};

MsdSort::MsdSort(int _size)
{
	SIZE = _size;
	arr_ptr = new char* [SIZE];
	for (int i = 0; i < SIZE; i++) arr_ptr[i] = NULL;
	MAX_LEN = 10;
	MAX_RANGE = 5;
}

MsdSort::~MsdSort()
{
	for (int i = 0; i < SIZE; i++)
	{
		delete[] arr_ptr[i];
	}
	delete[] arr_ptr;
}

void MsdSort::createRandomArray()
{
		for(unsigned int i=0; i<SIZE; i++)
		{
				unsigned int len = 1 + rand() % MAX_LEN;
				string tmp_str;
				arr_ptr[i] = new char[len+1];
				for(unsigned int j=0; j<len; j++)
				{
					char ch = 'a' + rand()%MAX_RANGE;
					tmp_str.push_back(ch);
					arr_ptr[i][j] = ch;
				}
				arr_ptr[i][len] = '\0';
				arr_vec.push_back(tmp_str);
		}
#if LOG
		cout <<"Random input size = " << SIZE << endl;
		for(unsigned int i=0; i<SIZE; i++)
			cout << "Vec = " << arr_vec[i] <<",    Arr = " << arr_ptr[i] << endl;
#endif
}

void MsdSort::sortRandomArray()
{
	sort(arr_vec.begin(), arr_vec.end());
	MsdStringSort(0, SIZE-1, 0);

	//cout << "\nSorted Strings size = " << SIZE << endl;
	for (unsigned int i = 0; i < SIZE; i++)
	{
		//cout << "Index " << i+1 <<"/" << SIZE <<"  Vec = " << arr_vec[i] << ",    Arr = " << arr_ptr[i] << endl;
		if (arr_vec[i] != string(arr_ptr[i])) assert(false);
	}
}

void MsdSort::MsdStringSort(int start, int end, unsigned int pos)
{
	if (end - start < 1)
		return;
	int* count = new int[256];

	//unsigned int pos = 0;
	bool is_changing = false;

	for (int i = 0; i < 256; i++)
	{
		count[i] = 0;
	}

	for (unsigned int i = start; i <= end; i++)
	{
		if (pos >= strlen(arr_ptr[i]))
		{
			count[1]++;
		}
		else
		{
			count[1 + arr_ptr[i][pos]]++;
			is_changing = true;
		}
	}
	if (is_changing == false)
	{
		delete[] count;
		return;
	}
	for (int i = 1; i < 256; i++)
	{
		count[i] += count[i-1];
	}
	char** aux = new char* [1+ end - start];
	for (unsigned int i = start; i <= end; i++)
	{
		if (pos >= strlen(arr_ptr[i]))
		{
			aux[count[0]] = arr_ptr[i];
			count[0]++;
		}
		else
		{
			aux[count[arr_ptr[i][pos]]] = arr_ptr[i];
			count[arr_ptr[i][pos]]++;
		}
	}
	for (unsigned int i = 0;i <= end-start; i++)
	{
		arr_ptr[start + i] = aux[i];
	}
	delete[] aux;
	int prev = 0;
	for (unsigned int i = 0; i < 256; i++)
	{
		if (start + count[i] - 1 > end)
		{
			cout << "Start= " << start << ", prev= " << prev << ", count[i]= " << count[i] << endl;
			cout << ", end= " << end << endl;
			assert(false);
		}
		MsdStringSort(start + prev, start + count[i] - 1, pos + 1);
		prev = count[i];
	}
	delete[] count;
}

int main()
{
	unsigned int Loop = 10;
	for (unsigned int i = 0; i < Loop; i++)
	{
		MsdSort obj(50000);
		obj.createRandomArray();
		obj.sortRandomArray();
		cout << "Completed Loop " << i + 1 << " of total " << Loop << endl;
	}
	return 0;
}