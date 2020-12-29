#pragma once

#include <stdexcept>
namespace RPS {

//! a helper type for an RPS exception
//! using was choosen instead of subclassing for simplicity
using Exception = std::runtime_error;

}
