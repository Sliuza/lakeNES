#ifndef AddresingMode_hpp
#define AddresingMode_hpp

enum AddressingMode {
  ABSOLUTE = 1,
  INDEXED_ABSOLUTE_X,
  INDEXED_ABSOLUTE_Y,
  ACCUMULATOR,
  IMMEDIATE,
  IMPLIED,
  INDIRECT,
  INDIRECT_INDEXED,
  INDEXED_INDIRECT,
  RELATIVE,
  ZERO_PAGE,
  INDEXED_ZERO_PAGE_X,
  INDEXED_ZERO_PAGE_Y
};

#endif
