#include <iostream>

class Rectangle {
		int width, height;
	public:
		void set_values(int, int);

		int area (){
			return width * height;
		}
};

void Rectangle::set_values(int x, int y) {
	width = x;
	height = y;
}

int main() {
	Rectangle rect;
	rect.set_values(5, 10);

	std::cout << "area:" << rect.area() << std::endl;
	return 0;
}

/*
Tests
1 - Points
throw(3)
throw(0)

score = 3

2
throw(5)
throw(5)

score = 10

3
*/
