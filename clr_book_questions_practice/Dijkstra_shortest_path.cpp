//https://www.hackerrank.com/challenges/dijkstrashortreach/problem

#include<vector>
#include <queue>
using namespace std;
// Complete the shortestReach function below.
struct src
{
	int weight;
	int dst;
	src(int _weight, int _dst)
	{
		weight = _weight;
		dst = _dst;
	}
};

struct node {
	int n;
	int len;
	node(int _n, int _len) { n = _n; len = _len; }
	bool operator < (const struct node rhs) const
	{
		return len > rhs.len;
	}
};

vector<int> shortestReach(int n, vector<vector<int> > edges, int s)
{
	const int MAX_DIST = 1 + 5000 * 100000;
	vector<struct src>* graph = new vector<struct src> [n+1];
	for(int i=0; i<edges.size(); i++)
	{
		int begin = edges[i][0];
		int end = edges[i][1];
		int weight = edges[i][2];
		graph[begin].push_back(src(weight, end));
	}

	int* dist = new int[n+1];
	for(int i=0; i<=n; i++)
		dist[i] = MAX_DIST;
	dist[s] = 0;


	std::priority_queue<node> pq;
	for(int i=1; i<=n; i++)
	{
		pq.push(node(i, dist[i]));
	}
	dist[s] = MAX_DIST;

	while(pq.size())
	{
		node cur_node = pq.top(); pq.pop();
		if(cur_node.len >= dist[cur_node.n])
			continue;
		for(int i=0; i<graph[cur_node.n].size(); i++)
		{
			src tmp = graph[cur_node.n][i];
			if(dist[tmp.dst] > dist[cur_node.n] + tmp.weight)
			{
				dist[tmp.dst] = dist[cur_node.n] + tmp.weight;
				pq.push(node(tmp.dst, dist[tmp.dst]));
			}
		}
	}
	vector<int> ret_vec;
	for(int i=1; i<=n; i++)
	{
		if(i == s) 
			continue;
		if(dist[i] == MAX_DIST)
			ret_vec.push_back(-1);
		else
			ret_vec.push_back(dist[i]);
	}
	delete [] dist;
	delete [] graph;
	return ret_vec;
}
