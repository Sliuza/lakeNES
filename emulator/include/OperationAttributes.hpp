#ifndef OperationAttribute_hpp
#define OperationAttribute_hpp
#include <stdint.h>

struct OperationAttributes {
  uint8_t id;
  uint8_t addressingMode;
  uint8_t printMode;
  uint8_t cycles;
  string name;
};

#endif
