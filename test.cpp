#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;

struct Point
{
    Point() : x(0), y(0), pair1(NULL), pair2(NULL), parent(NULL) {}                   // default constructor
    Point(double x, double y) : x(x), y(y), pair1(NULL), pair2(NULL), parent(NULL) {} // constructor with points
    Point(double x, double y, Point *pair1, Point *pair2) : x(x), y(y), pair1(pair1), pair2(pair2), parent(NULL) {}
    Point(double x, double y, Point *pair1, Point *pair2, double dist) : x(x), y(y), pair1(pair1), pair2(pair2), parent(NULL)
    {
        distance = dist;
        xDist = (pair1->x - pair2->x);
        yDist = (pair1->y - pair2->y);
    }
    Point(double x, double y, Point *pair1, Point *pair2, Point *parent) : x(x), y(y), pair1(pair1), pair2(pair2), parent(parent) {} // constructor with points and pairs and parent

    friend ostream &operator<<(ostream &os, const Point &p) // print function
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    double x;        // x coordinate
    double y;        // y coordinate
    double xDist;    // distance to x
    double yDist;    // distance to y
    double distance; // distance to origin
    Point *pair1;    // pointer to the first pair
    Point *pair2;    // pointer to the second pair
    Point *parent;   // pointer to the parent
};

bool compareX(const Point *p1, const Point *p2) // compare two points by their x coordinate
{
    return p1->x < p2->x;
}

class Network
{
public:
    Network(double *x, double *y, int numSinks) : m_numSinks(numSinks)
    {
        for (int i = 0; i < numSinks; i++)
        {
            Point *p = new Point(x[i], y[i]); // create a new point
            m_sinks.push_back(p);             // add the point to the vector
        }
        sort(m_sinks.begin(), m_sinks.end(), compareX); // sort the vector by x coordinate
        m_origin = new Point();                         // creates the origin
    }

    Network(const string fileName)
    {
        cout << "Loading file" << endl;
        ifstream coord_file(fileName);
        string x, y, num, Nil;
        int counter = 1;
        getline(coord_file, Nil);
        getline(coord_file, Nil);
        getline(coord_file, Nil, ' ');
        getline(coord_file, Nil, ' ');
        getline(coord_file, num);
        m_numSinks = stod(num);
        while (counter != m_numSinks + 1)
        {
            getline(coord_file, num, ' ');
            getline(coord_file, x, ' ');
            getline(coord_file, y, ' ');
            getline(coord_file, Nil);
            Point *p = new Point(stod(x), stod(y));
            m_sinks.push_back(p);
            ++counter;
        }
        sort(m_sinks.begin(), m_sinks.end(), compareX);
        m_origin = new Point();
        cout << "Loaded successfully" << endl;
    }

    ~Network()
    {
        clear(m_origin); // clears the memory
    }

    Point *getOrigin()
    {
        return m_origin;
    }

    void clear(Point *p) // remove all points, including origin
    {
        if (p != NULL)
        {
            if (p->pair1 != NULL)
            {
                clear(p->pair1);
            }
            if (p->pair2 != NULL)
            {
                clear(p->pair2);
            }
            delete p;
        }
    }

    double findM(Point *p1, Point *p2)
    {
        return (p2->y - p1->y) / (p2->x - p1->x);
    }

    void connectSignal()
    {
        Point *p1 = dAndC(m_sinks, m_numSinks); // consolidate the points into one
        p1->parent = m_origin;                  // set the parent of the point to the origin
        m_origin->pair1 = p1;                   // set the origin's pair to the point
        // at this point, all points are connected to the origin
    }

    Point *dAndC(vector<Point *> sinks, int size, Point *p = NULL)
    {
        if (sinks.size() == 2)
        {
            Point *p1 = sinks[0];
            Point *p2 = sinks[1];
            p = new Point((sinks[0]->x + sinks[1]->x) / (2), (sinks[0]->y + sinks[1]->y) / (2), sinks[0], sinks[1], distance(sinks[0], sinks[1])); // creates a new point at the midway of the two points
            sinks[0]->parent = p;                                                                                                                  // sets the parent of the first point to the new point
            sinks[1]->parent = p;                                                                                                                  // sets the parent of the second point to the new point
            return p;
        }
        if (sinks.size() == 1)
        {
            return sinks[0];
        }
        else
        {
            int mid = size / 2;                                       // finds the midpoint
            vector<Point *> left(sinks.begin(), sinks.begin() + mid); // creates a vector of the left half of the points
            vector<Point *> right(sinks.begin() + mid, sinks.end());  // creates a vector of the right half of the points
            Point *p1 = dAndC(left, mid);                             // recursively calls the function on the left half of the points
            Point *p2 = dAndC(right, size - mid);
            double dist = distance(p1, p2);
            if (p1->distance == p2->distance)
            {
                p = new Point((p1->x + p2->x) / (2), (p1->y + p2->y) / (2), p1, p2);
                p1->parent = p;
                p2->parent = p;
                return p;
            }
            double midX = (p1->x + p2->x) / 2;
            double midY = (p1->y + p2->y) / 2;
            double d = distance(p1, p2);
            double ratio = (p2->distance - p1->distance) / 2;
            double T = ratio / d;
            double x = (((1 - T) * midX + T * p2->x));
            double y = ((1 - T) * midY + T * p2->y);
            p = new Point(x, y, p1, p2, dist);
            p1->parent = p;
            p2->parent = p;
            return p;
        }
    }

    // for debugging
    void printNetwork()
    {
        cout << "Origin: " << *m_origin << endl;
        for (int i = 0; i < m_numSinks; i++)
        {
            cout << "Sink: " << *m_sinks[i] << endl;
        }
    }

    // for debugging
    void printPairs()
    {
        printPairs(m_origin); // prints the pairs
    }

    void printPairs2() { printPairs2(m_origin); }
    void printPairs2(Point *p)
    {
        bool pair2;                // boolean to check if the point is the first or second pair
        bool pair1 = pair2 = true; // assumes there are pairs
        cout << "Sink: " << *p << endl;
        if (p->pair1 != NULL)
        {
            cout << "Pair 1: " << *p->pair1 << " ";
        }
        else // if there is not a pair, then print NULL
        {
            cout << "Pair 1: NULL ";
            pair1 = false;
        }
        if (p->pair2 != NULL)
        {
            cout << "Pair 2: " << *p->pair2 << endl;
        }
        else
        {
            cout << "Pair 2: NULL" << endl;
            pair2 = false;
        }
        if (pair1)
        {
            printPairs2(p->pair1);
        }
        if (pair2)
        {
            printPairs2(p->pair2);
        }
    }

    void printPairs(Point *p)
    {
        bool pair2;                // boolean to check if the point is the first or second pair
        bool pair1 = pair2 = true; // assumes there are pairs
        // cout << "Sink: " << *p << endl;
        cout << "ax.text(" << p->x << ", " << p->y << ", '')" << endl;
        pair1 = (p->pair1 != NULL);
        pair2 = (p->pair2 != NULL);
        if (pair1)
        {
            printPairs(p->pair1);
        }
        if (pair2)
        {
            printPairs(p->pair2);
        }
    }

    void printDistances()
    {
        printDistances(m_origin); // prints the distances
    }
    void printDistances(Point *p)
    {
        if (p != NULL)
        {
            if (p->pair1 != NULL)
            {
                cout << "ax.plot([" << p->x << ", " << p->pair1->x << "], [" << p->y << ", " << p->y << "], linewidth=1.000000, color='r')" << endl;
                cout << "ax.plot([" << p->pair1->x << ", " << p->pair1->x << "], [" << p->y << ", " << p->pair1->y << "], linewidth=1.000000, color='b')" << endl;
            }
            if (p->pair2 != NULL)
            {
                cout << "ax.plot([" << p->x << ", " << p->pair2->x << "], [" << p->y << ", " << p->y << "], linewidth=1.000000, color='r')" << endl;
                cout << "ax.plot([" << p->pair2->x << ", " << p->pair2->x << "], [" << p->y << ", " << p->pair2->y << "], linewidth=1.000000, color='b')" << endl;
            }
            if (p->pair1 != NULL)
            {
                printDistances(p->pair1);
            }
            if (p->pair2 != NULL)
            {
                printDistances(p->pair2);
            }
        }
    }

    double distance(Point *p1, Point *p2)
    {
        return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
    }

    void checkDistances(bool test = true)
    {
        checkDistances(m_origin, test);
    }

    void checkDistances(Point *p, bool test = true)
    {
        for (int i = 0; i < m_numSinks; i++)
        {
            if (m_sinks[i] != NULL)
            {
                cout << i + 1 << ": ";
                cout << *m_origin << " to " << *m_sinks[i] << ": ";
                if (m_sinks[i]->parent != NULL)
                {
                    double total = 0;
                    Point *temp = m_sinks[i];
                    while (temp->parent != m_origin)
                    {
                        double dis = distance(temp, temp->parent);
                        if (test)
                        {
                            cout << dis << " + ";
                        }
                        total += dis;
                        temp = temp->parent;
                    };
                    double dis = distance(temp, m_origin);
                    if (test)
                    {
                        cout << " = " << dis << endl;
                    }
                    else
                    {
                        cout << dis << endl;
                    }
                }
            }
        }
    }

private:
    int m_numSinks;          // number of sinks
    Point *m_origin;         // origin
    vector<Point *> m_sinks; // vector of points
};

int main()
{
    // double x[] = {1, 5, 1.5, 8, 1, 9, 2.5, 3};
    // double y[] = {2, 8, 1.8, 9, 0.6, 11, 4.0, 3};
    // double x[] = {1, 5, 1.5, 8};
    // double y[] = {2, 8, 1.8, 9};
    double x[] = {1, 5, 1.5, 8, 1, 9, 2.5};
    double y[] = {2, 8, 1.8, 9, 0.6, 11, 4.0};
    int numSinks = sizeof(x) / sizeof(x[0]);
    Network network = Network(x, y, numSinks);
    // Network network = Network("s1r1.txt");
    network.connectSignal();
    // network.printDistances();
    cout << endl;
    // network.printPairs2();
    // network.printPairs();
    network.checkDistances(false);
}