#include "Point.h"

Point::~Point()
{
}

Point &Point::operator=(Point const &p)
{
    if (this != &p)
    {
        x = p.x;
        y = p.y;
    }

    return *this;
}

Point &Point::operator*=(int const p)
{
    x *= p;
    y *= p;

    return *this;
}

Point &Point::operator+=(Point const &p)
{
    x += p.x;
    y += p.y;

    return *this;
}

Point Point::operator-(Point const &p) const
{
    return Point(x - p.x, y - p.y);
}

Point &Point::operator-=(Point const &p)
{
    x -= p.x;
    y -= p.y;

    return *this;
}

Point &Point::operator*=(Point const &p)
{
    x *= p.x;
    y *= p.y;

    return *this;
}

Point Point::operator/(Point const &p) const
{
    return Point(x / p.x, y / p.y);
}

Point Point::operator/(int const p) const
{
    return Point(x / p, y / p);
}

Point &Point::operator/=(int const p)
{
    x /= p;
    y /= p;

    return *this;
}

Point &Point::operator/=(Point const &p)
{
    x /= p.x;
    y /= p.y;

    return *this;
}

bool Point::operator==(Point const &p) const
{
    return x == p.x && y == p.y;
}

bool Point::operator!=(Point const &p) const
{
    return x != p.x || y != p.y;
}

bool Point::operator<(Point const &p) const
{
    return x < p.x || (x == p.x && y < p.y);
}

std::string Point::toString() const
{
    return std::string("(").append(std::to_string(x)).append(", ").append(std::to_string(y)).append(")");
}

int Point::manhattanDistance() const
{
    // distance from origin
    return abs(x) + abs(y);
}

int Point::manhattanDistance(Point const &p) const
{
    // distance from other point
    return abs(x - p.x) + abs(y - p.y);
}

Point Point::operator*(int const p) const
{
    return Point(x * p, y * p);
}

Point Point::operator*(Point const &p) const
{
    return Point(x * p.x, y * p.y);
}

Point Point::operator+(Point const &p) const
{
    return Point(x + p.x, y + p.y);
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point()
{
    x = 0;
    y = 0;
}
