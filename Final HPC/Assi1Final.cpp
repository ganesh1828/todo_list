#include<iostream>
#include<omp.h>
#include<queue>
using namespace std;

class Node
{
	public:
		int data;
		Node * left;
		Node * right;
		Node()
		{

		}
};

Node * createRec()
{
	int data;
	cout<<"Enter data\n";
	cin>>data;
	if(data==-1)
	{
		return NULL;
	}

	Node * cur=new Node();
	cur->data=data;

	cout<<"For left of "<<cur->data<<"\n";
	cur->left=createRec();

	cout<<"For right of "<<cur->data<<"\n";
	cur->right=createRec();

	return cur;
}

Node * create()
{
	return createRec();
}

void bfs(Node * root)
{
	queue<Node *>q;
	q.push(root);

	while(!q.empty())
	{
		int qsize=q.size();

		for(int i=0;i<qsize;i++)
		{
			Node * cur=q.front();
			q.pop();
			cout<<cur->data<<" ";

			if(cur->left)
			{
				q.push(cur->left);
			}
			if(cur->right)
			{
				q.push(cur->right);
			}
		}
	}
}


void parallelbfs(Node * root)
{
	queue<Node *>q;
	q.push(root);

	while(!q.empty())
	{
		int qsize=q.size();
		#pragma omp parallel for
		for(int i=0;i<qsize;i++)
		{
			Node * cur;
			#pragma omp critical
			{
				cur=q.front();
				q.pop();
				cout<<cur->data<<" ";
			}

			#pragma omp critical
			{
				if(cur->left)
				{
					q.push(cur->left);
				}
				if(cur->right)
				{
					q.push(cur->right);
				}
			}
		}
	}
}


void dfs(int start,vector<int>graph[],bool visited[])
{
	cout<<"Visited "<<start;
	visited[start]=true;

	for(int i=0;i<graph[start].size();i++)
	{
		int v=graph[start][i];
		if(!visited[v])
		{
			dfs(v,graph,visited);
		}
	}
}

void paralleldfs(int start,vector<int>graph[],bool visited[])
{
	cout<<"Visited "<<start;
	visited[start]=true;
	#pragma omp parallel for
	for(int i=0;i<graph[start].size();i++)
	{
		int v=graph[start][i];
		if(!visited[v])
		{
			dfs(v,graph,visited);
		}
	}
}



int main()
{
	// Node * root=create();
	// bfs(root);
	// double start=omp_get_wtime();
	// parallelbfs(root);
	// double end=omp_get_wtime();


	int vertex;
	cin>>vertex;
	vector<int> graph[vertex];

	while(true)
	{
		cout<<"Enter edges\n";
		int u,v;
		cin>>u>>v;
		if(u==-1 && v==-1)
		{
			break;
		}
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for(int i=0;i<vertex;i++)
	{
		for(int j=0;j<graph[i].size();j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<"\n";
	}

	bool *visited=new bool[vertex];
	for(int i=0;i<vertex;i++)
	{
		visited[i]=false;
	}

	// dfs(0,graph,visited);

	// paralleldfs(0,graph,visited);
}