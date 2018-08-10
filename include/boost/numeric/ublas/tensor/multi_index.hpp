//
//  Copyright (c) 2018, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen Germany
//

#ifndef _BOOST_UBLAS_TENSOR_MULTI_INDEX_HPP_
#define _BOOST_UBLAS_TENSOR_MULTI_INDEX_HPP_


#include <cstddef>
#include <array>
#include <vector>

#include "multi_index_utility.hpp"

namespace boost {
namespace numeric {
namespace ublas {
namespace index {

template<std::size_t I>
struct index_type;

} // namespace indices
}
}
}


namespace boost {
namespace numeric {
namespace ublas {

/** @brief Proxy class for the einstein summation notation
 *
 * Denotes an array of index_type types ::_a for 0<=K<=16 is used in tensor::operator()
*/
template<std::size_t N>
class multi_index
{
public:
	multi_index() = delete;

	template<std::size_t I, class ... indexes>
	constexpr multi_index(index::index_type<I> const& i, indexes ... is )
			 : _base{i(), is()... }
	{
		static_assert( sizeof...(is)+1 == N,
					   "Static assert in boost::numeric::ublas::multi_index: number of constructor arguments is not equal to the template parameter." );

		static_assert( valid_multi_index<std::tuple<index::index_type<I>, indexes ...> >::value,
									 "Static assert in boost::numeric::ublas::multi_index: indexes occur twice in multi-index." );
	}

	multi_index(multi_index const& other)
		: _base(other._base)
	{
	}

	multi_index& operator=(multi_index const& other)
	{
		this->_base = other._base;
		return *this;
	}

	~multi_index() = default;

	auto const& base() const { return _base; }
	constexpr auto size() const { return _base.size(); }
	constexpr auto at(std::size_t i) const { return _base.at(i); }
	constexpr auto operator[](std::size_t i) const { return _base.at(i); }

private:
	std::array<std::size_t, N> _base;
};

template<std::size_t K, std::size_t N>
constexpr auto get(multi_index<N> const& m) { return std::get<K>(m.base()); }


} // namespace ublas
} // namespace numeric
} // namespace boost

#endif // MULTI_INDEX_HPP
