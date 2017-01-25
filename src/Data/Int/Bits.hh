///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Int.hh
// Copyright   :  (c) Andy Arvanitis 2016
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// Data.Int.Bits FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef Data_Int_Bits_FFI_HH
#define Data_Int_Bits_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_Int_Bits {
  using namespace PureScript;

  // foreign import and :: Int -> Int -> Int
  inline auto and$(const int n1, const int n2) -> int {
    return n1 & n2;
  }

  // foreign import or :: Int -> Int -> Int
  inline auto or$(const int n1, const int n2) -> int {
    return n1 | n2;
  }

  // foreign import xor :: Int -> Int -> Int
  inline auto xor$(const int n1, const int n2) -> int {
    return n1 ^ n2;
  }

  // foreign import shl :: Int -> Int -> Int
  inline auto shl(const int n1, const int n2) -> int {
    return n1 << n2;
  }

  // foreign import shr :: Int -> Int -> Int
  inline auto shr(const int n1, const int n2) -> int {
    return n1 >> n2;
  }

  // foreign import zshr :: Int -> Int -> Int
  inline auto zshr(const int n1, const int n2) -> int {
    const auto n = static_cast<unsigned>(n1) >> n2;
    assert(n <= std::numeric_limits<int>::max());
    return static_cast<int>(n);
  }

  // foreign import complement :: Int -> Int
  inline auto complement(const int n) -> int {
    return ~n;
  }

}

#endif // Data_Int_Bits_FFI_HH
