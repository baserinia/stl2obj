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

#include <cmath>

// interface

template <typename REAL, unsigned DIM>
class VectorND {
    REAL v_[DIM];
public:
    VectorND ();
    VectorND (const REAL& r);
    VectorND (const VectorND& vec);
    ~VectorND () { }
    const VectorND<REAL, DIM>& operator= (const VectorND& v);
    const VectorND<REAL, DIM>& operator= (const REAL& r);
    const VectorND<REAL, DIM>& operator+= (const VectorND& vec);
    const VectorND<REAL, DIM>& operator-= (const VectorND& vec);
    const VectorND<REAL, DIM>& operator*= (const REAL& r);
    const VectorND<REAL, DIM>& operator/= (const REAL& r);
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
};

// default constructor
template <typename REAL, unsigned DIM>
VectorND<REAL, DIM>::VectorND ()
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = 0.0;
}

// constructor
template <typename REAL, unsigned DIM>
VectorND<REAL, DIM>::VectorND (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = r;
}

// copy constructor
template <typename REAL, unsigned DIM>
VectorND<REAL, DIM>::VectorND(const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = v.v_[i];
}


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator= (const VectorND& v)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] = v.v_[i];
    return *this;
}


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator= (const REAL& r)
{
    for (unsigned i = 0 ; i < DIM; ++i) v_[i] = r;
    return *this;
}


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator+= (const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) {
        v_[i] += v.v_[i];
    }
    return *this;
}


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator-= (const VectorND& v) 
{
    for (unsigned i = 0; i < DIM; ++i) v[i] -= v.v_[i];  
}  


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator*= (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] *= r;  
}


template <typename REAL, unsigned DIM>
const VectorND<REAL, DIM>&
VectorND<REAL,DIM>::operator/= (const REAL& r)
{
    for (unsigned i = 0; i < DIM; ++i) v_[i] /= r;  
}


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM> 
VectorND<REAL,DIM>::operator- ( ) const
{
    VectorND<REAL,DIM> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = -v_[i];  
    return v_tmp;
}  


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM> 
VectorND<REAL,DIM>::operator+ (const VectorND& v) const
{
    VectorND<REAL,DIM> v_tmp;
    for ( unsigned i = 0; i < DIM; ++i )
        v_tmp[i] = v_[i] + v.v_[i];  
    return v_tmp;
}


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM>
VectorND<REAL,DIM>::operator-(const VectorND& v) const
{
    VectorND<REAL,DIM> v_tmp;
    for (unsigned i = 0; i < DIM; ++i ) v_tmp.v_[i] = v_[i] - v.v_[i];
    return v_tmp;

}


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM> 
VectorND<REAL,DIM>::operator*(const REAL& r) const
{
    VectorND<REAL,DIM> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = v_[i] * r;  
    return v_tmp;
}


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM> 
VectorND<REAL,DIM>::operator/(const REAL& r) const
{
    VectorND<REAL,DIM> v_tmp;
    for (unsigned i = 0; i < DIM; ++i) v_tmp.v_[i] = v_[i] / r;  
    return v_tmp;
}


template <typename REAL, unsigned DIM>
REAL
VectorND<REAL,DIM>::operator*(const VectorND& v) const
{
    REAL r = 0.0;
    for (unsigned i = 0; i < DIM; ++i ) r += v_[i] * v.v_[i];
    return r;
}


template <typename REAL, unsigned DIM>
REAL&
VectorND<REAL,DIM>::operator[](unsigned i)
{
    return v_[i];
}

template <typename REAL, unsigned DIM>
const REAL&
VectorND<REAL,DIM>::operator[](unsigned i) const
{
    return v_[i];
}


template <typename REAL, unsigned DIM>
REAL
VectorND<REAL,DIM>::get_magnit_sqr() const
{
    REAL r = 0.0;
    for (unsigned i = 0; i < DIM; ++i) r += v_[i] * v_[i];
    return r;
}  


template <typename REAL, unsigned DIM>
REAL
VectorND<REAL,DIM>::get_magnit() const
{
    return std::sqrt(get_magnit_sqr());
}


template <typename REAL, unsigned DIM>
VectorND<REAL,DIM>
VectorND<REAL,DIM>::get_unit() const
{
    return (*this) / get_magnit( ); 
}


template <typename REAL , unsigned DIM>
VectorND< REAL , DIM > 
VectorND< REAL , DIM  >::mult_elems (const VectorND<REAL,DIM>& v)
{
    VectorND<REAL , DIM> v_tmp;
    for (unsigned i = 0 ; i < DIM ; ++i) {
        v_tmp.v_[i] = v_[i] * v.v_[i];
    }
    return v_tmp;
}


/*
template <typename REAL, unsigned DIM>
std::ostream& 
operator<<( std::ostream& os, const VectorND<REAL,DIM>& vec )
{
    for (unsigned i=0; i< DIM; ++i )
        os << std::setw(10) << vec(i);
    os << std::endl;
    return os;
}
*/


#endif // TYPE_VECTORND_H_
