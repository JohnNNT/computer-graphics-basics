#include <cstdlib>
#include <iostream>

#include "Canvas.h"

ASCIICanvas::ASCIICanvas(const unsigned int rows,const unsigned int columns)
{
    set_size(rows, columns);
}

void Canvas::set_size(unsigned int height, unsigned int width)
{
    max_x = width;
    max_y = height;

    drawings.reserve(height);
    for(auto& row : drawings)
    {
        row.reserve(width);
        for(int i = 0; i < width; i++)
        {
            row.push_back(monako::empty);
        }
    }
}

void Canvas::draw(monako object, unsigned int pos_x, unsigned int pos_y)
{
    drawings[pos_y][pos_x] = object;
}

void ASCIICanvas::print()
{
    for(int i = 0; i<this->get_width()+2; i++)
    {
        std::cout << '/';
    }

    std::cout << '\n';
    for(int i = 0; i < this->get_height(); i++)
    {
        std::cout << '/';
        for(int j = 0; j<this->get_width(); j++)
        {
            switch(this->get_drawing(j, i))
            {
                case monako::empty:
                    std::cout << ' ';
                    break;
                case monako::filled:
                    std::cout << '#';
                    break;
                case monako::shadow:
                    std::cout << '*';
                    break;
                default:
                    std::cerr << "Unknown character\n";
                    std::exit(EXIT_FAILURE);
                    break;
            }
        }
        std::cout << "/\n";
    }

    for(int i = 0; i<this->get_width()+2; i++)
    {
        std::cout << '/';
    }

    std::cout << '\n';
}


monako Canvas::get_drawing(unsigned int pos_x, unsigned int pos_y) noexcept
{
    return drawings[pos_y][pos_x];
}
