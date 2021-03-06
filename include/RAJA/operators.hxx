/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Header file for RAJA operator definitions
 *
 *          Definitions in this file will propagate to all RAJA header files.
 *
 ******************************************************************************
 */

#ifndef RAJA_operators_HXX
#define RAJA_operators_HXX

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2016, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-689114
//
// All rights reserved.
//
// This file is part of RAJA.
//
// For additional details, please also read RAJA/LICENSE.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the disclaimer below.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include "RAJA/config.hxx"

#include "RAJA/internal/defines.hxx"

#include <cfloat>
#include <cstdint>
#include <type_traits>

namespace RAJA
{

namespace operators
{

namespace detail
{

struct associative_tag {
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
  using first_argument_type = Arg1;
  using second_argument_type = Arg2;
  using result_type = Result;
};

template <typename Argument, typename Result>
struct unary_function {
  using argument_type = Argument;
  using result_type = Result;
};

template <typename Arg1, typename Arg2>
struct comparison_function : public binary_function<Arg1, Arg2, bool> {
};

}  // closing brace for detail namespace

namespace types
{

template <typename T>
struct is_unsigned_int {
  constexpr static const bool value =
      std::is_unsigned<T>::value && std::is_integral<T>::value;
};

template <typename T>
struct is_signed_int {
  constexpr static const bool value =
      !std::is_unsigned<T>::value && std::is_integral<T>::value;
};

// given a type, T, return a similar type whose size is >= sizeof(T)
/*!
        \brief type lookup to return the next largest similar type (or the same
   type)
*/
template <typename T, bool GPU = false>
struct larger {
};

template <>
struct larger<uint8_t> {
  using type = uint16_t;
};

template <>
struct larger<uint16_t> {
  using type = uint32_t;
};

template <>
struct larger<uint32_t> {
  using type = uint64_t;
};

template <>
struct larger<int8_t> {
  using type = int16_t;
};

template <>
struct larger<int16_t> {
  using type = int32_t;
};

template <>
struct larger<int32_t> {
  using type = int64_t;
};

template <>
struct larger<float> {
  using type = double;
};

template <>
struct larger<double> {
  using type = long double;
};

template <>
struct larger<double, true> {
  using type = double;
};

namespace detail
{

template <typename T, bool isInt, bool isSigned, bool isFP, bool gpu = false>
struct largest {
};

template <typename T>
struct largest<T, true, false, false> {
  using type = uint64_t;
};

template <typename T>
struct largest<T, true, true, false> {
  using type = int64_t;
};

template <typename T>
struct largest<T, false, false, true, false> {
  using type = long double;
};

template <typename T>
struct largest<T, false, false, true, true> {
  using type = double;
};
}

/*!
        \brief type lookup to return largest similar type. If running on GPU,
   pass 'true' as second template argument
*/
template <typename T, bool gpu = false>
struct largest {
  using type = typename detail::largest<T,
                                        std::is_integral<T>::value,
                                        std::is_signed<T>::value,
                                        std::is_floating_point<T>::value,
                                        gpu>::type;
};


template <typename T>
struct size_of {
  enum { value = sizeof(T) };
};

namespace detail
{

template <typename T, typename U, bool lhsLarger>
struct larger_of {
};

template <typename T, typename U>
struct larger_of<T, U, true> {
  using type = T;
};

template <typename T, typename U>
struct larger_of<T, U, false> {
  using type = U;
};
}

template <typename T, typename U>
struct larger_of {
  using type =
      typename detail::larger_of<T,
                                 U,
                                 (size_of<T>::value > size_of<U>::value)>::type;
};

}  // closing brace for types namespace

namespace constants
{

template <typename T>
RAJA_HOST_DEVICE constexpr T min()
{
  return 0;
};
template <>
RAJA_HOST_DEVICE constexpr int16_t min<int16_t>()
{
  return 0xFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint16_t min<uint16_t>()
{
  return 0x0000;
}
template <>
RAJA_HOST_DEVICE constexpr int32_t min<int32_t>()
{
  return 0xFFFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint32_t min<uint32_t>()
{
  return 0x00000000;
}
template <>
RAJA_HOST_DEVICE constexpr int64_t min<int64_t>()
{
  return 0xFFFFFFFFFFFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint64_t min<uint64_t>()
{
  return 0x0000000000000000;
}
template <>
RAJA_HOST_DEVICE constexpr float min<float>()
{
  return -FLT_MAX;
}
template <>
RAJA_HOST_DEVICE constexpr double min<double>()
{
  return -DBL_MAX;
}
template <>
RAJA_HOST_DEVICE constexpr long double min<long double>()
{
  return -LDBL_MAX;
}

template <typename T>
RAJA_HOST_DEVICE constexpr T max()
{
  return 0;
};
template <>
RAJA_HOST_DEVICE constexpr int16_t max<int16_t>()
{
  return 0x7FFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint16_t max<uint16_t>()
{
  return 0xFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr int32_t max<int32_t>()
{
  return 0x7FFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint32_t max<uint32_t>()
{
  return 0xFFFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr int64_t max<int64_t>()
{
  return 0x7FFFFFFFFFFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr uint64_t max<uint64_t>()
{
  return 0xFFFFFFFFFFFFFFFF;
}
template <>
RAJA_HOST_DEVICE constexpr float max<float>()
{
  return FLT_MAX;
}
template <>
RAJA_HOST_DEVICE constexpr double max<double>()
{
  return DBL_MAX;
}
template <>
RAJA_HOST_DEVICE constexpr long double max<long double>()
{
  return LDBL_MAX;
}

}  // closing brace for constants namespace

// Arithmetic

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct plus : public detail::binary_function<Arg1, Arg2, Ret>,
              detail::associative_tag {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return Ret{lhs} + rhs;
  }
  static constexpr const Ret identity = Ret{0};
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct minus : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return Ret{lhs} - rhs;
  }
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct multiplies : public detail::binary_function<Arg1, Arg2, Ret>,
                    detail::associative_tag {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return Ret{lhs} * rhs;
  }
  static constexpr const Ret identity = Ret{1};
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct divides : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return Ret{lhs} / rhs;
  }
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct modulus : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return Ret{lhs} % rhs;
  }
};

// Conditions

template <typename Arg1, typename Arg2 = Arg1>
struct logical_and : public detail::comparison_function<Arg1, Arg2>,
                     detail::associative_tag {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs && rhs;
  }
  static constexpr const bool identity = true;
};

template <typename Arg1, typename Arg2 = Arg1>
struct logical_or : public detail::comparison_function<Arg1, Arg2>,
                    detail::associative_tag {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs || rhs;
  }
  static constexpr const bool identity = false;
};

template <typename T>
struct logical_not : public detail::unary_function<T, bool> {
  RAJA_HOST_DEVICE bool operator()(const T& lhs) { return !lhs; }
};

// Bitwise

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct bit_or : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs | rhs;
  }
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct bit_and : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs & rhs;
  }
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct bit_xor : public detail::binary_function<Arg1, Arg2, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs ^ rhs;
  }
};

// comparison

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct minimum : public detail::binary_function<Arg1, Arg2, Ret>,
                 detail::associative_tag {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return (lhs < rhs) ? lhs : rhs;
  }
  static constexpr const Ret identity = constants::max<Ret>();
};

template <typename Ret, typename Arg1 = Ret, typename Arg2 = Arg1>
struct maximum : public detail::binary_function<Arg1, Arg2, Ret>,
                 detail::associative_tag {
  RAJA_HOST_DEVICE Ret operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return (lhs < rhs) ? rhs : lhs;
  }
  static constexpr const Ret identity = constants::min<Ret>();
};

// Logical Comparison

template <typename Arg1, typename Arg2 = Arg1>
struct equal_to : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs == rhs;
  }
};

template <typename Arg1, typename Arg2 = Arg1>
struct not_equal_to : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs != rhs;
  }
};

template <typename Arg1, typename Arg2 = Arg1>
struct greater : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs >= rhs;
  }
};

template <typename Arg1, typename Arg2 = Arg1>
struct less : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs <= rhs;
  }
};


template <typename Arg1, typename Arg2 = Arg1>
struct greater_equal : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs >= rhs;
  }
};

template <typename Arg1, typename Arg2 = Arg1>
struct less_equal : public detail::comparison_function<Arg1, Arg2> {
  RAJA_HOST_DEVICE bool operator()(const Arg1& lhs, const Arg2& rhs)
  {
    return lhs <= rhs;
  }
};

// Filters

template <typename Ret, typename Orig = Ret>
struct identity : public detail::unary_function<Orig, Ret> {
  RAJA_HOST_DEVICE Ret operator()(const Orig& lhs) { return lhs; }
};

template <typename T, typename U>
struct project1st : public detail::binary_function<T, U, T> {
  RAJA_HOST_DEVICE T operator()(const T& lhs, const U& RAJA_UNUSED_ARG(rhs)) { return lhs; }
};

template <typename T, typename U = T>
struct project2nd : public detail::binary_function<T, U, U> {
  RAJA_HOST_DEVICE U operator()(const T& RAJA_UNUSED_ARG(lhs), const U& rhs) { return rhs; }
};

// Type Traits

template <typename T>
struct is_associative {
  constexpr static const bool value =
      std::is_base_of<detail::associative_tag, T>::value;
};

template <typename Arg1, typename Arg2 = Arg1>
struct safe_plus
    : public plus<Arg1,
                  Arg2,
                  typename types::larger<
                      typename types::larger_of<Arg1, Arg2>::type>::type> {
};

}  // closing brace for operators namespace

}  // closing brace for RAJA namespace

#endif  // closing endif for header file include guard
