#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define H_ARRAYSIZE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

inline int min(int x, int y)
{
	return x < y ? x : y;
}

// Mountain
struct Mount {
	int  l, r;    // left and right point's coordinate
	int  h;       // Mountain's height
	char lb, rb;  // lb == 1, left point is boundary
};

struct Point {
	int  x, y;
	char l;      // true, Mountain's left point
};

int compMountLeft(const void *a1, const void *a2)
{
	Mount *m1 = (Mount*) a1;
	Mount *m2 = (Mount*) a2;

	if (m1->l < m2->l)
		return -1;
	else if (m1->l == m2->l)
		return m1->h - m2->h;
	else
		return 1;
}

int compMountRight(const void *a1, const void *a2)
{
	Mount *m1 = (Mount*) a1;
	Mount *m2 = (Mount*) a2;

	if (m1->r > m2->r)
		return -1;
	else if (m1->r == m2->r)
		return m1->h - m2->h;
	else
		return 1;
}

int compPoint(const void *a1, const void *a2)
{
	Point *p1 = (Point*) a1;
	Point *p2 = (Point*) a2;

	if (p1->x < p2->x)
		return -1;
	else if (p1->x == p2->x && !p1->l)
		return -1;
	else
		return 1;
}

const char* nextline(const char* p)
{
	while (*p && *p != '\n') p++;
	if (*p) p++;
	return p;
}

int resolve(const char* input)
{
	int nMount, i, j;

	if (sscanf(input, "%d\n", &nMount) != 1)
		return -1;
	if (nMount == 0)
		return 0;

	// input
	Mount *M = new Mount[nMount];
	for (i = 0; i < nMount; i++)
	{
		input = nextline(input);
		if (sscanf(input, "%d,%d,%d\n", &M[i].l, &M[i].r, &M[i].h) != 3)
			return -1;
		M[i].lb = M[i].rb = 1;
	}

	// left boundary
	qsort(M, nMount, sizeof(Mount), compMountLeft);
	for (i = 0; i < nMount; i++)
	{
		for (j = i+1; j < nMount && M[j].l == M[i].l; j++)
			M[j-1].lb = 0;
		for (; j < nMount && M[j].l < M[i].r; j++)
		{
			if (M[i].h >= M[j].h)
				M[j].lb = 0;
		}
	}
	// right boundary
	qsort(M, nMount, sizeof(Mount), compMountRight);
	for (i = 0; i < nMount; i++)
	{
		for (j = i+1; j < nMount && M[j].r == M[i].r; j++)
			M[j-1].rb = 0;
		for (; j < nMount && M[j].r > M[i].l; j++)
		{
			if (M[i].h >= M[j].h)
				M[j].rb = 0;
		}
	}

	// walk length
	int nBound = 0;
	for (i = 0; i < nMount; i++)
		nBound += M[i].lb + M[i].rb;

	Point *P = new Point[nBound];
	for (i = j = 0; i < nMount; i++)
	{
		if (M[i].lb) { P[j].x=M[i].l; P[j].y=M[i].h; P[j++].l=1; }
		if (M[i].rb) { P[j].x=M[i].r; P[j].y=M[i].h; P[j++].l=0; }
	}
	qsort(P, nBound, sizeof(Point), compPoint);

	int walk = P[0].x + P[0].y;
	for (i = 1; i < nBound; i++)
	{
		walk += P[i].x-P[i-1].x + abs(P[i].y-P[i-1].y);
		if (P[i].l && !P[i-1].l && P[i].x!=P[i-1].x)
			walk += (min(P[i].y, P[i-1].y) << 1);
	}
	walk += P[nBound-1].y;

	// return
	delete[] M, P;
	M=NULL; P=NULL;
	return walk;
}

int main(int argc, char* argv[]) 
{
	const char* input[] = {
		"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
		"1\n1,2,1\n",
		"2\n1,2,1\n2,3,2",
		"3\n1,2,1\n2,3,2\n3,6,1",
		"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
		"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
		"1\n0,1,1",
		"2\n0,1,1\n2,4,3",
		"3\n0,1,1\n2,4,3\n3,5,1",
		"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
		"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		//TODO please add more test case here
		"0",
		"1\n0,1,3"
	};

	int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 0, 7};

	for (size_t i = 2; i < H_ARRAYSIZE(input); ++i)
	{
		if (resolve(input[i]) != expectedSteps[i])
		{
			printf("%d\n", (int)i);
		}
	}

	return 0;
}
