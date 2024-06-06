// Course: Advanced C programming
// exercise 1, question 2
// file name: ex1_q2.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------------------------- //
//

//
// --------------------------- //

// structs and function declarations section:
typedef struct point
{
	int x, y;
}point;

typedef struct polygon
{
	int n;
	point* points;
	double scope;
}polygon;

void scanPoint(point* p);
polygon* createPolygon();
double distance(point* p1, point* p2);
double calculateScope(point* points, int n);
int addPoint(polygon* poly);
int removePoint(polygon* poly, int idx);
void freeMemory(polygon* poly);

// --------------------------- //

int main()
{
	int i, n, idx;
	polygon* poly;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	poly = createPolygon();
	printf("How many points to add: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Point #%d: \n", i + 1);
		addPoint(poly);
	}

	printf("Enter index value to remove, invalid index to stop: ");
	do
	{
		scanf("%d", &idx);
	} while (removePoint(poly, idx));

	// write output:
	printf("Output: Scope of polygon: %.2lf\n", poly->scope);
	freeMemory(poly);

	return 0;
}
// --------------------------- //


/// <summary>
/// Function scan a point in the plane,
/// Used as auxiliary function for createPolygon.
/// </summary>
/// <param>point* p - pointer to p</param>
/// <returns>None</returns>

void scanPoint(point* p)
{
	// your code:
	printf("Enter a point in the plane\n");
	printf("Enter x: ");
	scanf_s("%d", &p->x);
	printf("Enter y: ");
	scanf_s("%d", &p->y);

}

// --------------------------- //


/// <summary>
/// Function allocate an empty polygon.
/// </summary>
/// <returns>New allocated polygon</returns>
polygon* createPolygon()
{
	// your code:
	polygon* new_polygon;
	new_polygon = (polygon*)malloc(sizeof(polygon));

	//initialize newpolygon
	if (new_polygon)
	{
		new_polygon->n = 0;
		new_polygon->points = NULL;
		new_polygon->scope = 0.0;
		return new_polygon;
	}
	//if not allocated
	else
	{
		printf("No memory allocation space!\n");
		return NULL;
	}

}
// --------------------------- //


/// <summary>
/// Function calculates distance between 2 adjacent points  
/// </summary>
/// <param>point* p1 - pointer to the first point</param>
/// <param>point* p2 - pointer to the second point</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
double distance(point* p1, point* p2)
{
	// your code:
	double distance, powX, powY;;

	powX = pow(p1->x - p2->x, 2);
	powY = pow(p1->y - p2->y, 2);
	distance = sqrt(powX + powY);
	return distance;
}
// --------------------------- //


/// <summary>
/// Function calculates and returns the Scope of a polygon.
/// </summary>
/// <param>point* points - array of points</param>
/// <param>int n - size of the array</param>
/// <returns>The Scope of a polygon</returns>
double calculateScope(point* points, int n)
{
	// your code:
	double scope = 0;
	int i;
	if (n < 3)
		scope = 0;
	else
	{
		for (i = 0; i < n - 1; i++)
		{
			scope += distance(points + i, points + i + 1);
		}
		scope += distance(points, points + i);//calculating the distance between last and first point
	}
	
	return scope;

}
// --------------------------- //


/// <summary>
/// Function add a new point at the end of the polygon,
/// and update the scope falue.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>1- success, 0- failure</returns>
int addPoint(polygon* poly)
{
	// your code:
	static int i = 0;
	poly->points = (point*)realloc(poly->points, sizeof(point) * ((poly->n) + 1));

	if (poly->points)//if realloc succeded
	{
		poly->n = (poly->n) + 1;
		scanPoint(poly->points + i);
		if (i > 0)
		{
			//no need to calculate one point by itself,only if there are at least two point i will calculate the scope
			poly->scope = calculateScope(poly->points, poly->n);
		}
		i++;
		return 1;
	}
	else {
		printf("No memory allocation space!\n");
		return 0;
	}
}
// --------------------------- //


/// <summary>
/// Function remove a point from the polygon,
/// at spesific index.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <param>int idx - the index to remove</param>
/// <returns>1- success, 0- failure</returns>
int removePoint(polygon* poly, int idx)
{
	// your code:
	int size = poly->n;

	if (idx >= 0 && idx <= size - 1)//index valid
	{
		while (idx < size)
		{

			if ( idx!= (size - 1))
			{
				poly->points[idx] = poly->points[idx + 1];
			}
			idx++;
		}
		poly->points = (point*)realloc(poly->points, sizeof(point) * (size - 1));
		poly->n = size - 1;
		
		poly->scope = calculateScope(poly->points, poly->n);
		return 1;
	}
	return 0;
}
// --------------------------- //


/// <summary>
/// Function free alocated memory. 
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void freeMemory(polygon* poly)
{
	// your code:
	free(poly->points);
	free(poly);
}
// --------------------------- //
