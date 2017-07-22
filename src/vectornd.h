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

template <unsigned DIM, typename REAL = double>
class VectorND {
public:
    VectorND ();
    VectorND (const REAL& r);
    VectorND (const VectorND& vec);
    template <typename... T> VectorND (T... r) : v_{r...} {};
    ~VectorND () { }
    const VectorND& operator= (const VectorND& v);
    const VectorND& operator= (const REAL& r);
    const VectorND& operator+= (const VectorND& vec);
    const VectorND& operator-= (const VectorND& vec);
    const VectorND& operator*= (const REAL& r);
    const VectorND& operator/= (const REAL& r);
    VectorND operator- () const;
    VectorND operator+ (const VectorND& vec) const;
    VectorND operator- (const VectorND& vec) const;
    VectorND operator* (const REAL& r) const;
    VectorND operator/ (const REAL& r) const;
    REAL operator* (const VectorND& vec) const;
    REAL& operator[] (unsigned i);
    const REAL& operator[] (unsigned i) const;
    REAL get_magnit_sqr () const;
    REAL get_magnit () const;
    VectorND get_unit () const;
    VectorND mult_elems (const VectorND& vec); // element-wise mutiplication

private:
    REAL v_[DIM];
};

// default constructor
template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>::VectorND ()
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = 0.0;
}

// constructor
template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>::VectorND (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = r;
}

// copy constructor
template <unsigned DIM, typename REAL>
VectorND<DIM, REAL>::VectorND(const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = v.v_[i];
}


template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator= (const VectorND& v)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = v.v_[i];
    return *this;
}


template <unsigned DIM, typename REAL>
const VectorND<DIM, REAL>&
VectorND<DIM, REAL>::operator= (const REAL& r)
{
    for (unsigned i = 0 ; i < DIM; ++i) v_[i] = r;
    return *this;
}


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
VectorND<DIM, REAL>::operator[](unsigned i)
{
    return v_[i];
}

template <unsigned DIM, typename REAL>
const REAL&
VectorND<DIM, REAL>::operator[](unsigned i) const
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


/*
template <unsigned DIM, typename REAL>
std::ostream& 
operator<<( std::ostream& os, const VectorND<DIM, REAL>& vec )
{
    for (unsigned i=0; i< DIM; ++i )
        os << std::setw(10) << vec(i);
    os << std::endl;
    return os;
}
*/


#endif // TYPE_VECTORND_H_
