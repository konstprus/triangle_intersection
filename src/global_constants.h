#pragma once

namespace ti {

//! is used for comparison two double values.
//! it means v1 == v2 <=> std::abs(v1-v2)< TOLERANCE
constexpr double TOLERANCE = 1e-7;

}  // namespace ti
