#include <iostream>
#include <cmath>
using namespace std;
//NAME: Raul Gonzalez Cespedes
//FSUID: RG21D

struct Point {
    float x;
    float y;
    Point(){
        x = 0.0;
        y = 0.0;
    } 
    Point(float _x, float _y){
        x = _x;
        y = _y;
    }
    bool operator==(const Point &p2){
        return (y == p2.y) && (x == p2.x);
    }
};

class Node
{
    public:
    Node(){
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
        minPoint = Point(0.0, 0.0);
        maxPoint = Point(0.0, 0.0);
        leaf = true;
        empty = true;
    }
    Node(Point _minPoint, Point _maxPoint){
        minPoint = _minPoint; 
        maxPoint = _maxPoint;
        leaf = true;
        empty = true;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    void recurse (const Point &temp,const Point &midPoint){
        bool abv = temp.y < midPoint.y;  
        bool lft = temp.x < midPoint.x;

        if (abv && lft) topLeft->insert(temp);
        if (abv && !lft) topRight->insert(temp);  
        if (!abv && lft) bottomLeft->insert(temp);
        if (!abv && !lft) bottomRight->insert(temp);
    }
    
    void insert(const Point &temp){
        if (leaf && empty){
            empty = false;
            point = temp;
            return;
        }

        Point midPoint((minPoint.x + maxPoint.x) /2 , (minPoint.y + maxPoint.y) / 2);

        if (!leaf){
            recurse(temp, midPoint);
            return;
        }

        if (!empty && point == temp) return;

        leaf = false;

        topLeft = new Node(Point(minPoint.x, minPoint.y), Point(midPoint.x, midPoint.y));
        topRight = new Node(Point(midPoint.x, minPoint.y), Point(maxPoint.x, midPoint.y));
        bottomLeft = new Node(Point(minPoint.x, midPoint.y), Point(midPoint.x, maxPoint.y));
        bottomRight = new Node(Point(midPoint.x, midPoint.y), Point(maxPoint.x, maxPoint.y));
   
        recurse(temp, midPoint);
        recurse(point, midPoint);
    }

    void print(){
        if (this == nullptr) return;
        if(point.x == 0.0 || point.y == 0.0) return;
        
        topLeft->print();
        topRight->print();
        bottomLeft->print();
        bottomRight->print();

        if (!leaf) return;


        cout << "Quadrant ( " << minPoint.x << " , " << minPoint.y << " ) of side " << maxPoint.x - minPoint.x << endl
             << "Point: ( " << point.x << " , " << point.y << " )\n";
    }

    private:
    Point point;
    Point minPoint; 
    Point maxPoint;
    bool leaf;
    bool empty;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft; 
    Node *bottomRight;
};


int main(){
    float side;
    int points; 
    cout << "Enter the length of a side of the square: ";
    cin >> side;
    Node quadTree(Point(0.0, 0.0), Point(side, side));

    cout << "Enter the number of points: ";
    cin >> points;

    float x; 
    float y;
    Point temp;
    cout << "Enter the coordinates of the points: ";
    for (int i = 0; i < points; i++){
        cin >> x >> y;
        temp.x = x; 
        temp.y = y;

        quadTree.insert(temp);
    }
    cout << "The Quad Tree is: \n";
    quadTree.print();
    
    return 0;
}