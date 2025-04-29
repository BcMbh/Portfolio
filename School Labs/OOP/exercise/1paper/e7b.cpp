#include <iostream>
using namespace std;

class Shape {
protected: // Make these protected so derived classes can access them
    int height, length;

public:
    void SetHeight(int hgt) {
        height = hgt;
    }

    void SetLength(int lth) {
        length = lth;
    }
};

class Shape3D : public Shape { // Renamed from 3D to Shape3D
private:
    int depth;

public:
    void SetDepth(int dpth) {
        depth = dpth;
    }

    int CalculateVolume() {
        return height * length * depth;
    }
};

int main() {
    Shape3D myShape;
    myShape.SetHeight(10);
    myShape.SetLength(5);
    myShape.SetDepth(3);

    cout << "Volume: " << myShape.CalculateVolume() << endl;

    return 0;
}
