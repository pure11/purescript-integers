///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Int.cc
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
#include <limits>
#include <cmath>
#include <bitset>
#include <sstream>
#include <iostream>
#include "Int.hh"

namespace Data_Int {
  using namespace PureScript;

  // foreign import fromNumberImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Number
  //   -> Maybe Int
  //
  auto fromNumberImpl(const any& just, const any& nothing, const double n) -> any {
    return (n >= std::numeric_limits<int>::min() &&
            n <= std::numeric_limits<int>::max() &&
            std::trunc(n) == n) ? just(std::lround(n)) : nothing;
  }

  // foreign import fromStringAsImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Radix
  //   -> String
  //   -> Maybe Int
  //
  auto fromStringAsImpl(const any& just,
                        const any& nothing,
                        const int radix,
                        const string& s) -> any {
    int i;
    std::stringstream ss;
    switch (radix) {
      case 2:
        try {
          const auto n = std::bitset<32>(s).to_ulong();
          return n <= std::numeric_limits<int>::max() ? just(static_cast<int>(n)) : nothing;
        } catch (std::exception&) {
          return nothing;
        }
        break;
      case 8:
        ss << std::oct << s;
        break;
      case 10:
        ss << std::dec << s;
        break;
      case 16:
        ss << std::hex << s;
        break;
      default:
        std::cerr << "fromStringAsImpl radix " << radix << " not supported" << std::endl;
        return nothing;
        break;
    }
    ss >> i;
    return ss.fail() || !ss.eof() ? nothing : just(i);
  }

  // foreign import toStringAs :: Radix -> Int -> String
  //
  auto toStringAs(const int radix, const int i) -> string {
    if (radix != 10 && i < 0) {
      std::cerr << "toStringAs warning: negative values for radix "
                << radix
                << " may give unexpected results" << std::endl;
    }
    std::stringstream ss;
    switch (radix) {
      case 2: {
        const auto s = std::bitset<32>(i).to_string();
        const auto p = s.find('1');
        return p == string::npos ? "0" : s.substr(p);
        }
        break;
      case 8:
        ss << std::oct << i;
        break;
      case 10:
        ss << std::dec << i;
        break;
      case 16:
        ss << std::hex << i;
        break;
      default:
        ss << "toStringAs radix " << radix << " not supported" << std::endl;
        throw runtime_error(ss.str());
        break;
    }
    return ss.str();
  }

  // foreign import pow :: Int -> Int -> Int
  //
  auto pow(const int x, const int y) -> int {
    const auto n = std::pow(x, y);
    assert(n >= std::numeric_limits<int>::min() &&
           n <= std::numeric_limits<int>::max());
    return std::trunc(n);
  }

}
