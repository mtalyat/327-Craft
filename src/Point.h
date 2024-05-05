#ifndef __POINT_H__
#define __POINT_H__

#include "Object.h"

// A 2D point in space, represented with x and y integers.
class Point
    : public Object
{
public:
    int x, y;

public:
    Point();
    Point(int x, int y);
    ~Point();

    // operators

    Point &operator=(Point const &p);
    Point operator+(Point const &p) const;
    Point &operator+=(Point const &p);
    Point operator-(Point const &p) const;
    Point &operator-=(Point const &p);
    Point operator*(Point const &p) const;
    Point &operator*=(Point const &p);
    Point operator*(int const p) const;
    Point &operator*=(int const p);
    Point operator/(Point const &p) const;
    Point &operator/=(Point const &p);
    Point operator/(int const p) const;
    Point &operator/=(int const p);
    bool operator==(Point const &p) const;
    bool operator!=(Point const &p) const;
    bool operator<(Point const &p) const;

    std::string toString() const override;

    // methods

    int manhattanDistance() const;
    int manhattanDistance(Point const &p) const;

    // shortcuts
    static Point up() { return Point(0, -1); }
    static Point down() { return Point(0, 1); }
    static Point left() { return Point(-1, 0); }
    static Point right() { return Point(1, 0); }
};

#endif // __POINT_H__