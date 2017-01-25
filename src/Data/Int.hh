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
// Data.Int FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef Data_Int_FFI_HH
#define Data_Int_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_Int {
  using namespace PureScript;

  // foreign import fromNumberImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Number
  //   -> Maybe Int
  //
  auto fromNumberImpl(const any&, const any&, const double) -> any;

  // foreign import toNumber :: Int -> Number
  //
  inline auto toNumber(const int n) -> double {
    return static_cast<double>(n);
  }

  // foreign import fromStringAsImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Radix
  //   -> String
  //   -> Maybe Int
  //
  auto fromStringAsImpl(const any&,
                        const any&,
                        const int,
                        const string&) -> any;

  // foreign import toStringAs :: Radix -> Int -> String
  //
  auto toStringAs(const int, const int) -> string;

  // foreign import pow :: Int -> Int -> Int
  //
  auto pow(const int, const int) -> int;

}

#endif // Data_Int_FFI_HH
