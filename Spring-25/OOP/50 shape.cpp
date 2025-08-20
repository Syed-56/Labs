#include <iostream>
using namespace std;

class Shape {
	string color;
	float borderThickness;
	int x,y;
	
	public:
	string getColor() const {return color;}
	float getBorderThickness() const {return borderThickness;}
	int getX() const {return x;}
	int getY() const {return y;}
	
	Shape(string c, float bT, int x, int y) {
		color = c;
		borderThickness = bT;
		this->x = x;
		this->y = y;
	}
	
	virtual void draw() {
		cout << "Drawing shape with center at ("<<x<<","<<y<<")\n";
		cout << "Border Thickness = " << borderThickness << "\tColor: " << color << endl;
	}
	virtual float calculateArea() {
		return 0.0;
	}
	virtual float CalculateParameter() {
		return 0.0;
	}
	
};

class Circle : public Shape {
	int radius;
	int centerX, centerY;
	public:
	Circle(string c, float bT, int x, int y, int r) : Shape(c,bT,x,y) {
		radius = r;
		centerX = x;
		centerY = y;
	}
	
	void draw() {
		cout << "Drawing Circle whose center is at (" << getX() << "," << getY() << ")" << endl;
		cout << "Radius = " << radius << endl;
		cout << "Border Thickness = " << getBorderThickness() << "\tColor: " << getColor() << endl;
	}
	float calculateArea() {
		return 3.14 * (radius*radius);
	}
	float calculateParameter() {
		return 2 * 3.14 * radius;
	}
};
class Rectangle : public Shape {
	int width;
	int height;
	int topLeftX, topLeftY;
	
	public:
	Rectangle(string c, float bT, int x, int y, int w, int h, int topX, int topY) : Shape(c,bT,x,y) {
		width = w;
		height = h;
		topLeftX = topX;
		topLeftY = topY;
	}
	
	void draw() {
		cout << "Drawing Rectangle whose center is at (" << getX() << "," << getY() << ")\n";
		cout << "Starting From: (" << topLeftX << "," << topLeftY << ")" << endl;
		cout << "Border Thickness = " << getBorderThickness() << "\tColor: " << getColor() << endl;
	}
	float calculateArea() {
		return width * height;
	}
	float calculateParameter() {
		return 2*width + 2*height;
	}
};
class Triangle : public Shape {
	int vertexA;
	int vertexB;
	int vertexC;
	
	public:
	Triangle(string c, float bT, int x, int y, int a, int b, int C) : Shape(c,bT,x,y) {
		vertexA = a;
		vertexB = b;
		vertexC = C;
	}
	
	void draw() {
		cout << "Drawing Triangle whose center is at (" << getX() << "," << getY() << ")";
		cout << "\nSides: " << vertexA << "," << vertexB << "," << vertexC << endl;
		cout << "Border Thickness = " << getBorderThickness() << "\tColor: " << getColor() << endl;
	}
	float calculateArea() {
		return vertexA + vertexB + vertexC;
	}
	float calculateParameter() {
		return calculateArea()/2;
	}
};

class Polygon : public Shape {
	float interiorAngle1, interiorAngle2, interiorAngle3, interiorAngle4;
	bool isRegular;
	
	public:
	Polygon(string c, float bT, int x, int y, int a1, int a2, int a3, int a4, bool isReg=false) : Shape(c,bT,x,y) {
		interiorAngle1 = a1;
		interiorAngle2 = a2;
		interiorAngle3 = a3;
		interiorAngle4 = a4;
		if(interiorAngle1==interiorAngle2==interiorAngle3==interiorAngle1) {
			isRegular = true;
		}
	}
	
	void draw() {
		cout << "Drawing polygon with center at (" << getX() << "," << getY() << ")\n";
		cout << "Angles: " << interiorAngle1 << "degrees, " << interiorAngle2 << "degrees, " << interiorAngle3 << "degrees, " << interiorAngle4 << "degrees, ";
		cout << "\nBorder Thickness = " << getBorderThickness() << "\tColor: " << getColor() << endl;
	}
	float calculateArea() {
		return interiorAngle1 * interiorAngle2 * interiorAngle3 * interiorAngle4;
	}
	float calculateParameter() {
		return calculateArea() / 200;
	}
};

int main() {
	Circle c("Red",2.5,4,5,25);
	Rectangle r("Blue",3.4,6,7,8,16,0,0);
	Triangle t("Pink",2.3,3,3,5,10,15);
	Polygon p("Black",4.7,8,9,30,45,60,90);
	
	c.draw();
	cout << "Area of Circle: " << c.calculateArea() << endl;
	cout << "Perimeter of Circle: " << c.calculateParameter() << endl;
	cout << endl;
	r.draw();
	cout << "Area of Rectangle: " << r.calculateArea() << endl;
	cout << "Perimeter of Rectangle: " << r.calculateParameter() << endl;
	cout << endl;
	t.draw();
	cout << "Area of Triangle: " << t.calculateArea() << endl;
	cout << "Perimeter of Triangle: " << t.calculateParameter() << endl;
	cout << endl;
	p.draw();
	cout << "Area of Polygon: " << p.calculateArea() << endl;
	cout << "Perimeter of Polygon: " << p.calculateParameter() << endl;
	cout << endl;
}