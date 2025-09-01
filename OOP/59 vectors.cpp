#include <iostream>
using namespace std;
class flexibleVectors {
	int *components;
	int dimensions;
	
	public:
		flexibleVectors() {}
		flexibleVectors(int d) : dimensions(d) {
			components = new int[dimensions];
		}
		friend istream& operator >> (istream &in, flexibleVectors &v) {
			cout << "Input Vector: ";
			for(int i=0; i<v.dimensions; i++) {
				in >> v.components[i];
			}
			return in;
		}
		friend ostream& operator << (ostream &out, const flexibleVectors &v) {
			for(int i=0; i<v.dimensions; i++) {
				out << v.components[i] << "  ";
			}
			cout << endl;
			return out;
		}
		flexibleVectors operator=(const flexibleVectors &v) {
			dimensions = v.dimensions;
			components = new int[dimensions];
			for(int i=0; i<dimensions; i++)	 components[i] = v.components[i];
			return *this;
		}
		flexibleVectors operator+(const flexibleVectors &v) {
			const flexibleVectors *larger = (dimensions >= v.dimensions) ? this : &v;
			const flexibleVectors *smaller = (dimensions < v.dimensions) ? this : &v;
			
			flexibleVectors temp(larger->dimensions);
			for(int i=0; i<larger->dimensions; i++)		temp.components[i] = larger->components[i];
			int diff = larger->dimensions - smaller->dimensions;
			for(int i=0; i<smaller->dimensions; i++) {
				temp.components[i+diff] += smaller->components[i];
			}
			return temp;
		}
		friend flexibleVectors operator*(int n, const flexibleVectors &v) {
			flexibleVectors tempVector(v.dimensions);
			for(int i=0; i<tempVector.dimensions; i++) {
				tempVector.components[i] = n*v.components[i];
			}
			return tempVector;
		}
		~flexibleVectors() {
			delete[] components;
		}
};

int main() {
	flexibleVectors v1, v2(2), v3(5), v4;
	cin >> v2 >> v3;
	v4=v3;
	v1=v2+v3;
	cout << v1;
	cout << 3*v4;
	return 0;
}