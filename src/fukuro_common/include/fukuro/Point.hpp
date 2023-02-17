#ifndef FUKURO_CORE_POINT_HPP
#define FUKURO_CORE_POINT_HPP

#include <iostream>
#include <cmath>

namespace fukuro
{

template<typename _Tp> 
class Point_
{
public:
    typedef _Tp value_type;

    //! default constructor
    Point_();
    template <typename _Tp2> Point_(_Tp2 _x, _Tp2 _y);
    template <typename _Tp2> Point_(const Point_<_Tp2> &pt);
    template <typename _Tp2> Point_(Point_<_Tp>&& pt) noexcept;
    template <typename _Tp2> Point_(const std::vector<_Tp2> &v);

    template <typename _Tp2> operator Point_<_Tp2>() const;
    template <typename _Tp2> Point_<_Tp> &operator=(const Point_<_Tp2> &pt);
    template <typename _Tp2> bool &operator<(const Point_<_Tp2> &pt);

    // !dot product
    _Tp dot(const Point_ &pt) const;
    //! dot product computed in double-precision arithmetics
    double ddot(const Point_ &pt) const;
    //! cross-product
    double cross(const Point_ &pt) const;
    //! distance between (x,y) and pt
    double distance(const Point_<_Tp> &pt) const;
    //! value of norm;
    double norm() const;

    _Tp x;
    _Tp y; 
    // ^ the point coordinates
};

typedef Point_<int> Point2i;
typedef Point_<double> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;

//////////////////////////////// Cartesian  Point ////////////////////////////////

template <typename _Tp> inline Point_<_Tp>::Point_() : x(0), y(0) {}
template <typename _Tp> template <typename _Tp2> inline Point_<_Tp>::Point_(_Tp2 _x, _Tp2 _y) : x(_Tp(_x)), y(_Tp(_y)) {}
template <typename _Tp> template <typename _Tp2> inline Point_<_Tp>::Point_(const Point_<_Tp2> &pt)
    : x(_Tp(pt.x)), y(_Tp(pt.y)) {}

template <typename _Tp> template <typename _Tp2> inline Point_<_Tp>::operator Point_<_Tp2>() const
{
    return Point_<_Tp>(_Tp(x), _Tp(y));
}

template <typename _Tp> template<typename _Tp2> inline Point_<_Tp> &Point_<_Tp>::operator=(const Point_<_Tp2> &pt)
{
    x = _Tp(pt.x);
    y = _Tp(pt.y);
    return *this;
}

template <typename _Tp> template<typename _Tp2> inline bool &Point_<_Tp>::operator<(const Point_<_Tp2> &pt)
{
    return _Tp(pt.x) < _Tp(pt.y);
}

}

#endif // FUKURO_CORE_POINT_HPP