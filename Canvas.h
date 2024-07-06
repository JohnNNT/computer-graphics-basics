#ifndef CANVAS
#define CANVAS

#include <vector>

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



#endif
