#ifndef BASE_H
#define BASE_H

#include <stdexcept>
#include <valarray>
#include <algorithm>

typedef double ColorChannel;
/**
* struct Color
* @brief struct for description of color
*/
struct Color {
    ColorChannel red, green, blue, alpha;

    Color(ColorChannel red, ColorChannel green, ColorChannel blue,
          ColorChannel alpha = 1.
          );
    Color() {

    }

    void setColor(ColorChannel r, ColorChannel g, ColorChannel b,
                  ColorChannel a = 1.) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
    void setColor(Color color) {
        red = color.red;
        green = color.green;
        blue = color.blue;
        alpha = color.alpha;
    }

    static const Color blackColor;
    static const Color whiteColor;
    static const Color grayColor;
};


struct DrawStyle {
    Color lineColor, fillColor;

    DrawStyle(Color lineColor = Color::blackColor,
              Color fillColor = Color::grayColor);

    void setStyle(Color line, Color fill) {
        lineColor = line;
        fillColor = fill;
    }
    void setStyle(DrawStyle d) {
        lineColor = d.lineColor;
        fillColor = d.fillColor;
    }
};

///////////////

template <typename T>
struct Vector2D {
    T x, y;

    Vector2D (const T& value = 0);
    Vector2D (const T& x, const T& y);

    Vector2D< T >& operator += (const Vector2D< T >& value);
    Vector2D< T >& operator -= (const Vector2D< T >& value);
    Vector2D< T >& operator *= (const T& value);

    Vector2D< T >& makePositive();
};

template <typename T>
Vector2D<T> operator + (const Vector2D< T >& left, const Vector2D< T >& right);

template <typename T>
Vector2D<T> operator - (const Vector2D< T >& left, const Vector2D< T >& right);

template <typename T>
Vector2D<T> operator * (const Vector2D< T >& left, const T& right);

template <typename T>
Vector2D<T>::Vector2D(const T& value) : x(value), y(value) {}

template <typename T>
Vector2D<T>::Vector2D(const T& x, const T& y) : x(x), y(y) {}

template <typename T>
Vector2D<T>& Vector2D<T>::makePositive() {
    x = abs(x);
    y = abs(y);
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator += (const Vector2D<T>& value)
{
    x += value.x;
    y += value.y;
    return *this;
}

template< typename T >
Vector2D< T >& Vector2D< T >::operator -= (const Vector2D< T >& value)
{
    x -= value.x;
    y -= value.y;
    return *this;
}

template< typename T >
Vector2D< T >& Vector2D< T >::operator *= (const T& value)
{
    x *= value;
    y *= value;
    return *this;
}
template< typename T >
Vector2D< T > operator + (const Vector2D< T >& left, const Vector2D< T >& right)
{
    Vector2D< T > res(left);
    res += right;
    return res;
}

template< typename T >
Vector2D< T > operator - (const Vector2D< T >& left, const Vector2D< T >& right)
{
    Vector2D< T > res(left);
    res -= right;
    return res;
}

template< typename T >
Vector2D< T > operator * (const Vector2D< T >& left, const T& right)
{
    Vector2D< T > res(left);
    res *= right;
    return res;
}

typedef Vector2D< double > Point2D;


#endif // BASE_H
