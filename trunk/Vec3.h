#ifndef VEC3_H
#define VEC3_H

#include <math.h>

#define MIN(A, B) ((A < B) ? A : B )
#define MAX(A, B) ((A > B) ? A : B )
#define SQUARE(A) ((A)*(A))

template <typename T>
class Vec3
{
private:
    T m_values[3];

public:
    Vec3(const T& _value1 = T(), const T& _value2 = T(), const T& _value3 = T());
    Vec3(const Vec3<T>& _vector);
    ~Vec3();

    T x() const { return m_values[0]; }
    T y() const { return m_values[1]; }
    T z() const { return m_values[2]; }

    void setX(T _value) { m_values[0] = _value; }
    void setY(T _value) { m_values[1] = _value; }
    void setZ(T _value) { m_values[2] = _value; }
    void set(Vec3<T> _vector) { setX(_vector.x()); setY(_vector.y()); setZ(_vector.z()); }
    void set(T _k) { setX(_k); setY(_k); setZ(_k); }
    void setZero() { set(0); }

    T* toArray() { return m_values; }
};

// CONSTRUCTEURS
template <typename T>
Vec3<T>::Vec3(const T& _value1, const T& _value2, const T& _value3)
{
    setX(_value1);
    setY(_value2);
    setZ(_value3);
}

template <typename T>
Vec3<T>::Vec3(const Vec3<T>& _vector)
{
    set(_vector);
}

// DESTRUCTEUR
template <typename T>
Vec3<T>::~Vec3()
{
}

// DISTANCE
template <typename T>
double distance(const Vec3<T>& _vec1, const Vec3<T>& _vec2)
{
    return (sqrt(SQUARE(_vec2.x() - _vec1.x()) + SQUARE(_vec2.y() - _vec1.y()) + SQUARE(_vec2.z() - _vec1.z())));
}

// PRODUIT SCALAIRE
template <typename T>
double dotProduct(const Vec3<T>& _vec1, const Vec3<T>& _vec2)
{
    return (_vec1.x * _vec2.x + _vec1.y * _vec2.y + _vec1.z * _vec2.z);
}

// PRODUIT VECTORIEL
template <typename T>
Vec3<T> crossProduct(const Vec3<T>& _vec1, const Vec3<T>& _vec2)
{
    Vec3<T> vector;
    vector.setX((_vec1.y * _vec2.z) - (_vec1.z * _vec2.y));
    vector.setY((_vec1.z * _vec2.x) - (_vec1.x * _vec2.z));
    vector.setZ((_vec1.x * _vec2.y) - (_vec1.y * _vec2.x));
    return vector;
}


typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<unsigned char> Vec3uc;

#endif // VEC3_H
