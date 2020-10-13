#include <queue>
#include <assert.h>
#include <time.h>
#include<algorithm>
#include<iostream>
using namespace std;


class MinPq
{
private:
	unsigned int SIZE;
	int* arr;
	void bubble_up(unsigned int index);
	void bubble_down(unsigned int index);

public:
	MinPq() { SIZE=0; arr=NULL;}
	~MinPq() {SIZE=0; delete arr; arr=NULL;}
	MinPq(int MaxSize);
	unsigned int getSize() { return SIZE; }
	int getMin();
	void insert(int key);
	int RemoveMin();

	void test_priority_queue(unsigned int loop);
};

MinPq::MinPq(int MaxElements)
{
	SIZE=0;
	arr = new int [MaxElements+1];
}

int MinPq::getMin()
{
		if(SIZE == 0)
			assert(false);
		return arr[1];
}


void MinPq::bubble_up(unsigned int index)
{
	while(index >1)
	{
		if(arr[index] < arr[index/2])
		{
			std::swap(arr[index], arr[index/2]);
			index = index/2;
		}
		else
			break;
	}
}

void MinPq::bubble_down(unsigned int index)
{
	unsigned int min_index = 0;
	while(2*index <= SIZE) // at-least one child is there.
	{
		min_index = 2*index;
		if(min_index+1 <=SIZE && arr[min_index] > arr[min_index+1])
		{
			min_index += 1;
		}
		if (arr[index] > arr[min_index])
		{
			std::swap(arr[index], arr[min_index]);
			index = min_index;
		}
		else
			return;
	}
	return;
}


void MinPq::insert(int key)
{
	SIZE++;
	arr[SIZE] = key;
	bubble_up(SIZE);
}

int MinPq::RemoveMin()
{
		if(SIZE == 0)
		{
			assert(false);
		}

		int min_key = arr[1];
		arr[1] = arr[SIZE];
		SIZE--;
		if(SIZE > 0)
			bubble_down(1);
		return min_key;
}

struct compare
{
	bool operator()(int a, int b)
	{
		return a > b ? true : false;
	}
};

void MinPq::test_priority_queue(unsigned int loop)
{
	
	for (unsigned int i = 1; i <= loop; i++)
	{
		cout << "Priority-Queue: Running test loop: " << i << endl;
		priority_queue<int, vector<int>, compare> pq;
		const unsigned int PQ_SIZE = 50000;
		MinPq* testObj = new MinPq(PQ_SIZE);

		for (unsigned int count = 0; count < PQ_SIZE; count++)
		{
			int value = rand() % 100;
			int op = rand() % 3;
			int val1, val2;
			cout << "Priority-Queue: Loop: " << i << "=>  Op-count= " << count + 1 <<", Op= " << op << endl;
			switch (op)
			{
			case 0: /* INSERT */
				if (testObj->getSize() != pq.size()) { assert(false); }

				if (testObj->getSize() == PQ_SIZE)
					break;
				testObj->insert(value);
				pq.push(value);
				break;
			case 1: /* remove root */
				if (testObj->getSize() != pq.size()) { assert(false); }

				if (testObj->getSize() == 0)
					break;
				val1 = testObj->RemoveMin();
				val2 = pq.top(); pq.pop();
				if (val1 != val2)
					assert(false);
				break;

			case 2: /* compare root */
				if (testObj->getSize() != pq.size()) { assert(false); }

				if (testObj->getSize() == 0)
					break;
				val1 = testObj->getMin();
				val2 = pq.top();
				if (val1 != val2)
					assert(false);
				break;
			}
		}
		delete testObj;
	}

}


int main()
{
	srand(time(NULL));
#if 0
	priority_queue<int, vector<int>, compare> pq_tmp;
	pq_tmp.push(2);
	pq_tmp.push(1);
	pq_tmp.push(3);
	cout << "Root element: " << pq_tmp.top() << endl;

	while (!pq_tmp.empty())
	{
		cout << pq_tmp.top() << endl;
		pq_tmp.pop();
	}
#endif

#if 1
	MinPq obj;
	obj.test_priority_queue(50);
#endif
	return 0;
}