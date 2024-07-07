#ifndef CANVAS
#define CANVAS

#include <stdint.h>
#include <vector>
#include <compare>

#include "ConfigFile.h"

enum class monako{
    empty,
    filled,
    shadow,
};

class Canvas{
private:
    unsigned int max_y;
    unsigned int max_x;
    std::vector<std::vector<monako>> drawings;
public:
    void set_size(unsigned int height, unsigned int width);
    const unsigned int get_height() noexcept;
    const unsigned int get_width() noexcept;
    monako get_drawing(unsigned int pos_x, unsigned int pos_y);
    virtual void print() = 0;
    void draw(monako object, unsigned int base_pos_x, unsigned int base_pos_y);
};

class ASCIICanvas : public Canvas{
public:
    ASCIICanvas() = default;
    ASCIICanvas(const unsigned int rows, const unsigned int columns);
    ~ASCIICanvas() = default;
    void print() override;
};

class Figure{
private:
    unsigned int base_x;
    unsigned int base_y;
public:
    virtual void draw(Canvas& drawing) = 0;
    void set_base(unsigned int pos_x, unsigned int pos_y);
    const unsigned int get_base_x() noexcept;
    const unsigned int get_base_y() noexcept;
};

class Rectangle : public Figure{
private:
    unsigned int height;
    unsigned int width;
public:
    Rectangle() = default;
    Rectangle(unsigned int base_x, unsigned int base_y, unsigned int Height, unsigned int Width);
    ~Rectangle() = default;
    void draw(Canvas& drawing);
};

class Circle : public Figure
{
private:
    unsigned int range;
public:
    Circle() = default;
    Circle(unsigned int centre_x, unsigned int centre_y, unsigned int range);
    ~Circle() = default;
    void draw(Canvas& drawing);
};

class Linear_function{
private:
    int coefficient_x_numerator;
    int coefficient_x_denominator;
    int coefficient_free_numerator;
    int coefficient_free_denominator;

    void simplify();
public:
    void calculate_from_points(int Ax, int Ay, int Bx, int By);
    const double get_coefficient_x() const;
    const double get_coefficient_free() const;
    double result_from_x(int argx);
    double argument_for_y(int argy);

    bool operator==(const Linear_function& function) const;
};

class Line : public Figure
{
private:
    unsigned int end_x;
    unsigned int end_y;
public:
    Line(unsigned int cornerAx,unsigned int cornerAy,unsigned int cornerBx,unsigned int cornerBy);
    Line() = default;
    ~Line() = default;
    void draw(Canvas &drawing) override;
};

class Triangle : public Figure
{
private:
    Line * line_ptr = nullptr;
    unsigned int corner2x;
    unsigned int corner2y;
    unsigned int corner3x;
    unsigned int corner3y;
public:
    Triangle(unsigned int cornerAx, unsigned int cornerAy, unsigned int cornerBx, unsigned int cornerBy, unsigned int cornerCx, unsigned int cornerCy);
    void draw(Canvas &drawing) override;
};

unsigned int MiddleOfThree(unsigned int a,unsigned  int b,unsigned  int c);

#endif
