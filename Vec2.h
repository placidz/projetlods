#ifndef Vec2_H
#define Vec2_H

#include <math.h>

#define MIN(A, B) ((A < B) ? A : B )
#define MAX(A, B) ((A > B) ? A : B )
#define SQUARE(A) ((A)*(A))

template <typename T>
class Vec2
{
private:
    T m_values[2];

public:
    Vec2(const T& _value1 = T(), const T& _value2 = T());
    Vec2(const Vec2<T>& _vector);
    ~Vec2();

    T x() const { return m_values[0]; }
    T y() const { return m_values[1]; }

    void setX(T _value) { m_values[0] = _value; }
    void setY(T _value) { m_values[1] = _value; }
    void set(Vec2<T> _vector) { setX(_vector.x()); setY(_vector.y()); }
    void set(T _k) { setX(_k); setY(_k); }
    void setZero() { set(0); }

    T* toArray() { return m_values; }
};

// CONSTRUCTEURS
template <typename T>
Vec2<T>::Vec2(const T& _value1, const T& _value2)
{
    setX(_value1);
    setY(_value2);
}

template <typename T>
Vec2<T>::Vec2(const Vec2<T>& _vector)
{
    set(_vector);
}

// DESTRUCTEUR
template <typename T>
Vec2<T>::~Vec2()
{
}

// DISTANCE
template <typename T>
double distance(const Vec2<T>& _vec1, const Vec2<T>& _vec2)
{
    return (sqrt(SQUARE(_vec2.x() - _vec1.x()) + SQUARE(_vec2.y() - _vec1.y()) ));
}

// PRODUIT SCALAIRE
template <typename T>
double dotProduct(const Vec2<T>& _vec1, const Vec2<T>& _vec2)
{
    return (_vec1.x * _vec2.x + _vec1.y * _vec2.y);
}


typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<unsigned char> Vec2uc;

#endif // Vec2_H
