#include <cmath>
#include <numeric>

#include "Canvas.h"

void Linear_function::calculate_from_points(int Ax, int Ay, int Bx, int By)
{
    coefficient_x_numerator = By - Ay;
    coefficient_x_denominator = Bx - Ax;
    coefficient_free_numerator = (Ay*Bx) - (By*Ax) ;
    coefficient_free_denominator = Bx - Ax;

    this->simplify();
}

void Linear_function::simplify()
{
    unsigned int HighestCommonDivisor = std::gcd(coefficient_x_denominator, coefficient_x_numerator);
    coefficient_x_denominator/= HighestCommonDivisor;
    coefficient_x_numerator /= HighestCommonDivisor;

    HighestCommonDivisor = std::gcd(coefficient_free_denominator, coefficient_free_numerator);
    coefficient_free_denominator/= HighestCommonDivisor;
    coefficient_free_numerator /= HighestCommonDivisor;
}

double Linear_function::result_from_x(int argx)
{
    unsigned int LowestCommonMultiple = std::lcm(coefficient_x_denominator, coefficient_free_denominator);
    coefficient_free_numerator *= LowestCommonMultiple/coefficient_free_denominator;
    coefficient_x_numerator *= LowestCommonMultiple/coefficient_x_denominator;
    coefficient_x_denominator = LowestCommonMultiple;

    argx=argx*coefficient_x_numerator + coefficient_free_numerator;
    this->simplify();
    return 1.0*argx/LowestCommonMultiple;
}

double Linear_function::argument_for_y(int argy)
{
    return 1.0*coefficient_x_denominator*(coefficient_free_denominator*argy-coefficient_free_numerator)/(coefficient_x_numerator*coefficient_free_denominator);
}

const double Linear_function::get_coefficient_free() const
{
    return 1.0*coefficient_free_numerator/coefficient_free_denominator;
}

const double Linear_function::get_coefficient_x() const
{
    return 1.0*coefficient_x_numerator/coefficient_x_denominator;
}

bool Linear_function::operator==(const Linear_function& funkcja) const
{
    return this->get_coefficient_x()==funkcja.get_coefficient_x() && this->get_coefficient_free()==funkcja.get_coefficient_free();
}

unsigned int MiddleOfThree(unsigned int a,unsigned  int b,unsigned  int c)
{
    if (a > b)
    {
        if (b > c)
            return b;
        else if (a > c)
            return c;
        else
            return a;
    }
    else
    {
        if (a > c)
            return a;
        else if (b > c)
            return c;
        else
            return b;
    }
}
