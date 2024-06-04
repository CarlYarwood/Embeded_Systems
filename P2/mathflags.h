/*
  Projtect 2 Subroutines
  Carl Yarwood
  allows status.c to know the prototypes of the functions
  defined in mathflags.S and by extention call given math
  flags
*/
uint8_t addflags( uint8_t i, uint8_t j); //Do i+j and return SREG
uint8_t subflags( uint8_t i, uint8_t j); //Do i-j and return SREG
