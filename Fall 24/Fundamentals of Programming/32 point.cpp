#include<stdio.h>
#include<math.h>
typedef struct {
	float x;
	float y;
	float z;
} point3D;
typedef struct {
	point3D bblc;
	float legnth;
	float height;
	float width;
} cuboid;
float calcDist(point3D p1, point3D p2) {
	return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z));
}
float findVolume(cuboid c) {
	return (c.height)*(c.legnth)*(c.width);
}
int isPointInside(point3D p, cuboid c) {
	printf("Enter Back Corner Left Bottom Point\n");
	printf("Enter x : ");
	scanf("%d", &c.bblc.x);
	printf("Enter x : ");
	scanf("%d", &c.bblc.y);
	printf("Enter x : ");
	scanf("%d", &c.bblc.z);
	if(p.x >= c.bblc.x || p.z >= c.bblc.y || p.z >= c.bblc.z)	return 0;
	return 1;
}
int main() {
	point3D p1,p2,p;
	cuboid c;
	printf("Enter p1\n");
	printf("Enter x : ");
	scanf("%f", &p1.x);
	printf("Enter y : ");
	scanf("%f", &p1.y);
	printf("Enter z : ");
	scanf("%f", &p1.z);
	printf("Enter p2\n");
	printf("Enter x : ");
	scanf("%f", &p2.x);
	printf("Enter y : ");
	scanf("%f", &p2.y);
	printf("Enter z : ");
	scanf("%f", &p2.z);
	printf("Point P\n");
	printf("Enter x : ");
	scanf("%f", &p.x);
	printf("Enter y : ");
	scanf("%f", &p.y);
	printf("Enter z : ");
	scanf("%f", &p.z);
	printf("Cuboid\n");
	printf("Enter Legnth : ");
	scanf("%f",&c.legnth);
	printf("Enter Height : ");
	scanf("%f",&c.height);
	printf("Enter Width : ");
	scanf("%f",&c.width);
	printf("Distance : %f\n", calcDist(p1,p2));
	printf("Volume : %f\n", findVolume(c));
	printf("is Point Inside? : \n");
	(isPointInside(p,c)) ? printf("Yes") : printf("No");
}