// Generic N-dimensional vector class

// Copyright (c) 2017 Amir Baserinia

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TYPE_VECTORND_H_
#define TYPE_VECTORND_H_
#pragma once

#include <cmath>

// interface

template <unsigned DIM = 3, typename REAL = double>
class VectorND {
public:
//  default constructor; set all elements to zero
    VectorND () : v_{} {};

//  use default compiler-generated copy constructor
    VectorND (const VectorND& vec) = default;

//  variadic template constructor for intializing componenets
    template <typename... T>
        VectorND (T... r) : v_{r...} {};

//  use default compiler-generated destructor
    ~VectorND () = default;

//  user default compiler-generated copy constructor
    VectorND& operator= (const VectorND& v) = default;

//  vector assignment operators
    const VectorND& operator+= (const VectorND& vec);
    const VectorND& operator-= (const VectorND& vec);
    const VectorND& operator*= (const REAL& r);
    const VectorND& operator/= (const REAL& r);

//  return negative vector
    VectorND operator- () const;

//  add vectors
    VectorND operator+ (const VectorND& vec) const;

//  subtract vectos
    VectorND operator- (const VectorND& vec) const;

//  multiply by scalar
    VectorND operator* (const REAL& r) const;

//  divide by scalar
    VectorND operator/ (const REAL& r) const;

//  dot product
    REAL operator* (const VectorND& vec) const;

//  mutable component operator
    REAL& operator[] (unsigned i);

//  const component operator
    const REAL& operator[] (unsigned i) const;

//  return square of magnitude
    REAL get_magnit_sqr () const;

//  return magnitude
    REAL get_magnit () const;

//  return normalized vector
    VectorND get_unit () const;

//  element-wise multiplication
    VectorND mult_elems (const VectorND& vec);

//  get distance squared between two points
    static REAL
    get_dist_sqr(const VectorND<3, REAL>& v1, const VectorND<3, REAL>& v2)
    {
        return (v1 - v2).get_magnit_sqr();
    }

//  get distance between two points
    static REAL
    get_dist(const VectorND<3, REAL>& v1, const VectorND<3, REAL>& v2)
    {
        return (v1 - v2).get_magnit();
    }

//  cross-product of 3D vectors
    static VectorND<3, REAL>
    cross (const VectorND<3, REAL>& v1, const VectorND<3, REAL>& v2)
    {
        static_assert(DIM == 3);
        return VectorND<3, REAL> (
            v1[1] * v2[2] - v1[2] * v2[1],
            v1[2] * v2[0] - v1[0] * v2[2],
            v1[0] * v2[1] - v1[1] * v2[0]
        );
    }

//  cross product for 2D vectors
    static REAL
    cross (const VectorND<2, REAL>& v1, const VectorND<2, REAL>& v2)
    {
        static_assert(DIM == 2);
        return v1[1] * v2[2] - v1[2] * v2[1];
    }

private:
    REAL v_[DIM]; // actual data in vector
};

template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator+= (const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) {
        v_[i] += v.v_[i];
    }
    return *this;
}


template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator-= (const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) v[i] -= v.v_[i];  
}


template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator*= (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] *= r;  
}


template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator/= (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] /= r;  
}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL> 
VectorND<DIM, REAL>::operator- ( ) const
{
    VectorND<DIM, REAL> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = -v_[i];  
    return v_tmp;
}  


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL> 
VectorND<DIM, REAL>::operator+ (const VectorND& v) const
{
    VectorND<DIM, REAL> v_tmp;
    for ( unsigned i = 0; i < DIM; ++i )
        v_tmp[i] = v_[i] + v.v_[i];  
    return v_tmp;
}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>
VectorND<DIM, REAL>::operator-(const VectorND& v) const
{
    VectorND<DIM, REAL> v_tmp;
    for (unsigned i = 0; i < DIM; ++i ) v_tmp.v_[i] = v_[i] - v.v_[i];
    return v_tmp;

}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL> 
VectorND<DIM, REAL>::operator*(const REAL& r) const
{
    VectorND<DIM, REAL> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = v_[i] * r;  
    return v_tmp;
}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL> 
VectorND<DIM, REAL>::operator/(const REAL& r) const
{
    VectorND<DIM, REAL> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = v_[i] / r;  
    return v_tmp;
}


template <unsigned DIM, typename REAL>
REAL
VectorND<DIM, REAL>::operator*(const VectorND& v) const
{
    REAL r = 0.0;
    for (unsigned i = 0; i < DIM; ++i ) r += v_[i] * v.v_[i];
    return r;
}


template <unsigned DIM, typename REAL>
REAL&
VectorND<DIM, REAL>::operator[] (unsigned i)
{
    return v_[i];
}

template <unsigned DIM, typename REAL>
const REAL&
VectorND<DIM, REAL>::operator[] (unsigned i) const
{
    return v_[i];
}


template <unsigned DIM, typename REAL>
REAL
VectorND<DIM, REAL>::get_magnit_sqr() const
{
    REAL r = 0.0;
    for (unsigned i = 0; i < DIM; ++i) r += v_[i] * v_[i];
    return r;
}  


template <unsigned DIM, typename REAL>
REAL
VectorND<DIM, REAL>::get_magnit() const
{
    return std::sqrt(get_magnit_sqr());
}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>
VectorND<DIM, REAL>::get_unit() const
{
    return (*this) / get_magnit( ); 
}


template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>
VectorND<DIM, REAL>::mult_elems (const VectorND<DIM, REAL>& v)
{
    VectorND<DIM, REAL> v_tmp;
    for (unsigned i = 0 ; i < DIM ; ++i) {
        v_tmp.v_[i] = v_[i] * v.v_[i];
    }
    return v_tmp;
}



#endif // TYPE_VECTORND_H_
