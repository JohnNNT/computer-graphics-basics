#include <algorithm>
#include <cmath>

#include "Canvas.h"

Triangle::Triangle(unsigned int cornerAx, unsigned int cornerAy, unsigned int cornerBx, unsigned int cornerBy, unsigned int cornerCx, unsigned int cornerCy)
{

    Linear_function line1, line2;
    line1.calculate_from_points(cornerAx, cornerAy, cornerBx, cornerBy);
    line2.calculate_from_points(cornerBx, cornerBy, cornerCx, cornerCy);
    if(line1==line2)
    {
        unsigned int lowest_point = std::min({cornerAy, cornerBy, cornerCy});
        if(lowest_point==cornerAy)
        {
            if(cornerAx<=std::min(cornerBx, cornerCx))
            {
                Line exTriangle(cornerAx,cornerAy, std::max(cornerBx, cornerCx),std::max(cornerBy,cornerCy));
                line_ptr = &exTriangle;
                return;
            }
            else
            {
                Line exTriangle(cornerAx, cornerAy, std::min(cornerBx, cornerCx), std::max(cornerBy, cornerCy));
                line_ptr = &exTriangle;
                return;
            }

        }
        else if (lowest_point==cornerBy) {
            if(cornerBx<=std::min(cornerAx, cornerCx))
            {
                Line exTriangle(cornerBx,cornerBy, std::max(cornerAx, cornerCx),std::max(cornerAy,cornerCy));
                line_ptr = &exTriangle;
                return;
            }
            else
            {
                Line exTriangle(cornerBx, cornerBy, std::min(cornerAx, cornerCx), std::max(cornerAy, cornerCy));
                line_ptr = &exTriangle;
                return;
            }
        }
        else
        {
            if(cornerCx<=std::min(cornerAx, cornerBx))
            {
                Line exTriangle(cornerCx,cornerCy, std::max(cornerAx, cornerBx),std::max(cornerAy,cornerBy));
                line_ptr = &exTriangle;
                return;
            }
            else
            {
                Line exTriangle(cornerCx, cornerCy, std::min(cornerAx, cornerBx), std::max(cornerAy, cornerBy));
                line_ptr = &exTriangle;
                return;
            }
        }
    }

    set_base(cornerAx, cornerAy);
    corner2x = cornerBx;
    corner2y = cornerBy;
    corner3x = cornerCx;
    corner3y = cornerCy;
}

void Triangle::draw(Canvas &drawing)
{
    if(line_ptr!=nullptr)
    {
        line_ptr->draw(drawing);
        return;
    }

    unsigned int edge_left_x = std::min({get_base_x(), corner2x, corner3x});
    unsigned int edge_left_y = (edge_left_x==get_base_x() ? get_base_y() : (edge_left_x==corner2x ? corner2y : corner3y));
    unsigned int edge_right_x = std::max({get_base_x(), corner2x, corner3x});;
    unsigned int edge_right_y = (edge_right_x==get_base_x() ? get_base_y() : (edge_right_x==corner2x ? corner2y : corner3y));;

    unsigned int centre_corner_x = MiddleOfThree(get_base_x(), corner2x, corner3x);
    unsigned int cente_corner_y = centre_corner_x==get_base_x()? get_base_y() : (centre_corner_x==corner2x ? corner2y : corner3y);

    Linear_function left_to_centre;
    Linear_function left_to_right;
    Linear_function right_to_centre;

    left_to_centre.calculate_from_points(edge_left_x, edge_left_y, centre_corner_x, cente_corner_y);
    left_to_right.calculate_from_points(edge_left_x, edge_left_y,edge_right_x ,edge_right_y );
    right_to_centre.calculate_from_points(centre_corner_x, cente_corner_y,edge_right_x, edge_right_y );

    if(static_cast<double>(cente_corner_y)< left_to_right.result_from_x(centre_corner_x))
    {
        for(unsigned int i = edge_left_x; i<=std::min(centre_corner_x, drawing.get_width()-1); i++)
            for(unsigned int j = std::min(edge_left_y, cente_corner_y); j<=std::min(static_cast<unsigned int>(std::ceil(left_to_right.result_from_x(centre_corner_x))),drawing.get_height()-1);j++)
            {
                if(static_cast<double>(j)>=left_to_centre.result_from_x(i) && static_cast<double>(j)<=left_to_right.result_from_x(i))
                {
                    drawing.draw(pointState::filled, i, j);
                }
            }

        for(unsigned int i = centre_corner_x; i<=std::min(edge_right_x,drawing.get_width()-1); i++)
            for(unsigned int j = centre_corner_x; j<=std::min(edge_right_y, drawing.get_height()-1);j++)
            {
                if(static_cast<double>(j)>=left_to_centre.result_from_x(i) && static_cast<double>(j)<=left_to_right.result_from_x(i))
                {
                    drawing.draw(pointState::filled, i, j);
                }
            }
    }
    else {
        for(unsigned int i = edge_left_x; i<=std::min(centre_corner_x,drawing.get_width()-1); i++)
        {
            for(unsigned int j = edge_left_y; j<=std::min(cente_corner_y, drawing.get_height()-1); j++)
            {
                if(static_cast<double>(j)>=left_to_right.result_from_x(i) && static_cast<double>(j)<=left_to_centre.result_from_x(i))
                {
                    drawing.draw(pointState::filled, i,j);
                }
            }
        }

        for(unsigned int i = centre_corner_x; i<=std::min(edge_right_x, drawing.get_width()-1); i++)
        {
            for(unsigned int j = static_cast<unsigned int>(std::trunc(left_to_right.result_from_x(centre_corner_x))); j<=std::min(std::max(cente_corner_y, edge_right_y), drawing.get_height()-1); j++)
            {
                if(static_cast<double>(j)>=left_to_right.result_from_x(i) && static_cast<double>(j)<=right_to_centre.result_from_x(i))
                {
                    drawing.draw(pointState::filled, i,j);
                }
            }
        }
    }

    return;
}
