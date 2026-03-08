#ifndef MATHINATOR_CORE_TYPES_H
#define MATHINATOR_CORE_TYPES_H

typedef enum {
  MATHINATOR_OK,
  MATHINATOR_INVALID,
  MATHINATOR_UNDEF,
} result_status;

typedef struct {
   result_status status;
   double result_val;
   char error_message[256];
} result_t;

typedef enum {
  MATHINATOR_EXIT_SUCCESS = 0, //successful computation
  MATHINATOR_EXIT_INVALID = 1, // invalid arguments or unknown command
  MATHINATOR_EXIT_UNDEFINED = 2, // mathematically undefined result or out of function domain
} mathinator_exit_code;

#endif