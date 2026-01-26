#pragma once

#define ACROY_ASSERT(x, ...) { if(!(x)) { ACROY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
#define ACROY_CORE_ASSERT(x, ...) { if(!(x)) { ACROY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }