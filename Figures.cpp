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
    for(long int i = get_base_x()-range; i<=get_base_x()+range; i++)
    {
        for(long int j = get_base_y()-range; j<=get_base_y()+range; j++)
        {
            if(i>=0 && i<=drawing.get_width() && j>=0 && j<=drawing.get_height() && range*range >= ((get_base_x()-i)*(get_base_x()-i)+(get_base_y()-j)*get_base_y()-j))
                drawing.draw(monako::filled, j, i);
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

}
