#include <algorithm>
#include <cmath>

#include "Canvas.h"

void Figure::set_base(unsigned int pos_x, unsigned int pos_y)
{
    base_x = pos_x;
    base_y = pos_y;
}

Circle::Circle(unsigned int centre_x, unsigned int centre_y, unsigned int Range)
{
    this->range = Range;
    set_base(centre_x, centre_y);
}

void Circle::draw(Canvas& drawing)
{
    for(long int i = std::max(static_cast<int>(get_base_x()-range), 0); i<=std::min(get_base_x()+range, drawing.get_width()); i++)
    {
        for(long int j = std::max(static_cast<int>(get_base_y()-range), 0); j<=std::min(get_base_y()+range, drawing.get_height()); j++)
        {
            if(((i-get_base_x())*(i-get_base_x())+(j-get_base_y())*(j-get_base_y()))<=range*range)
                drawing.draw(pointState::filled, i, j);
        }
    }
}

Rectangle::Rectangle(unsigned int base_x, unsigned int base_y, unsigned int Height, unsigned int Width)
{
    set_base(base_x, base_y);
    height = Height;
    width = Width;
}

void Rectangle::draw(Canvas& drawing)
{
    for(int i = get_base_x(); i<std::min(drawing.get_width(), get_base_x()+width); i++)
        for(int j = get_base_y(); j<std::min(drawing.get_height(), get_base_y()+height);j++)
            drawing.draw(pointState::filled, i, j);
}

const unsigned int Figure::get_base_x() noexcept
{
    return base_x;
}

const unsigned int Figure::get_base_y() noexcept
{
    return base_y;
}

Line::Line(unsigned int cornerAx,unsigned int cornerAy,unsigned int cornerBx,unsigned int cornerBy)
{
    set_base(cornerAx, cornerAy);
    end_x = cornerBx;
    end_y = cornerBy;
}

void Line::draw(Canvas &drawing)
{
    Linear_function straight_line;
    straight_line.calculate_from_points(get_base_x(), get_base_y(), end_x, end_y);
    unsigned int j;
    for(unsigned int i = std::min(get_base_x(), end_x);i<=std::min(std::max(get_base_x(), end_x), drawing.get_width()-1); ++i)
    {
        j = static_cast<unsigned int>(std::round(straight_line.result_from_x(i)));
        if(j<drawing.get_height()-1)
        drawing.draw(pointState::filled, i,j);
    }

    return;
}


