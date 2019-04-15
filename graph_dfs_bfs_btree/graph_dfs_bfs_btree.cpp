// graph_dfs_bfs_btree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>

#define MAXQUEUE	10

struct node {
	int vertex;
	struct node *nextnode;
};
typedef struct node *graph;
struct node head[9];
int visited[9];

int queue[MAXQUEUE];
int front = -1;
int rear  = -1;

/**
 * create the graph with edges array
 */
void creategraph(int *node, int num)
{
	graph newnode;
	graph ptr;
	int   from;
	int   to;
	int   i;

	for (i = 0; i < num; i++) {
		from = node[i*2];
		to = node[i*2+1];
		newnode = (graph)malloc(sizeof(struct node) );
		newnode->vertex = to;
		newnode->nextnode = NULL;
		ptr = &(head[from]);
		while (ptr->nextnode != NULL) {
			ptr = ptr->nextnode;
		}
		ptr->nextnode = newnode;
	}
}

/**
 * deep first search
 */
void dfs(int current)
{
	graph ptr;

	visited[current] = 1;
	printf("vertex[%d] ", current);
	ptr = head[current].nextnode;
	while (ptr != NULL) {
		if (visited[ptr->vertex] == 0) {
			dfs(ptr->vertex);
		}
		ptr = ptr->nextnode;
	}
}

/**
 * span the tree with dfs alorgithm
 */
void spantree_dfs(int current, int pre)
{
	graph ptr;

	visited[current] = 1;
	if (pre != 0) {
		printf("tree branch: from vertex[%d] to vertex[%d]\n", pre, current);
	}
	
	ptr = head[current].nextnode;
	while (ptr != NULL) {
		if (visited[ptr->vertex] == 0) {
			spantree_dfs(ptr->vertex, current);
		}
		ptr = ptr->nextnode;
	}
}

/**
 * put into the queue
 */
void enqueue(int value)
{
	if (front >= MAXQUEUE) {
		return ;
	}

	rear++;
	queue[rear] = value;
}

/**
 * take from the queue
 */
int dequeue()
{
	if (front == rear) {
		return -1;
	}

	front++;
	return queue[front];
}

/**
 * breadth first search
 */
void bfs(int current)
{
	graph ptr;

	enqueue(current);
	visited[current] = 1;
	printf("vertex[%d] ", current);
	while (front != rear) {
		current = dequeue();
		ptr = head[current].nextnode;
		while (ptr != NULL) {
			if (visited[ptr->vertex] == 0) {
				enqueue(ptr->vertex);
				visited[ptr->vertex] = 1;
				printf("vertex[%d] ", ptr->vertex);
			}
			ptr = ptr->nextnode;
		}
	}
}

/**
 * span the tree with bfs alorigthm
 */
void spantree_bfs(int current)
{
	graph ptr;

	enqueue(current);
	visited[current] = 1;
	while (front != rear) {
		current = dequeue();
		ptr = head[current].nextnode;
		while (ptr != NULL) {
			if (visited[ptr->vertex] == 0) {
				enqueue(ptr->vertex);
				visited[ptr->vertex] = 1;
				printf("tree branch: from vertex[%d] to vertex[%d]\n", current, ptr->vertex);
			}
			ptr = ptr->nextnode;
		}
	}
}

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	graph ptr;
	int node[20][2] = { // edges array
		{1, 2}, {2, 1},
		{1, 3}, {3, 1},
		{2, 4}, {4, 2},
		{2, 5}, {5, 2},
		{3, 6}, {6, 3},
		{3, 7}, {7, 3},
		{4, 8}, {8, 4},
		{5, 8}, {8, 5},
		{6, 8}, {8, 6},
		{7, 8}, {8, 7},
	};

	int i;

	for (i = 1; i <= 8; i++) {
		head[i].vertex = i;
		head[i].nextnode = NULL;
		visited[i] = 0;
	}

	creategraph(&node[0][0], 20);

	printf("the graph's adjacence list is: \n");
	for (i = 1; i <= 8; i++) {
		printf("vertex%d => ", head[i].vertex);
		ptr = head[i].nextnode;
		while (ptr != NULL) {
			printf(" %d  ", ptr->vertex);
			ptr = ptr->nextnode;
		}
		printf("\n");
	}

	/*printf("the deepth first search of the graph: \n");
	dfs(1);
	spantree_dfs(1, 0);
	printf("\n");*/

	printf("the breadth first search of the graph: \n");
	//bfs(1);
	spantree_bfs(1);
	printf("\n");

	return 0;
}
