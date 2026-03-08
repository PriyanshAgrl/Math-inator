#include "cli/parser.h"
#include "core/types.h"
#include "math/arithmetic.h"
#include "math/trigo.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_double(const char *str, double *out) {
	char *endptr;
	*out = strtod(str, &endptr);
	return *endptr == '\0';
}

typedef double (*unary_op)(double);			 // function pointer for all math functions that take single operand
typedef double (*binary_op)(double, double); // function pointer for all math functions that take two operand

static result_t dispatch_unary(int argc, char *argv[], unary_op fn, const char *usage) {
	result_t result = {MATHINATOR_INVALID, NAN, "Unknown error"};
	if (argc != 3) {
		snprintf(result.error_message, sizeof(result.error_message), "%s", usage); //
		return result;
	}
	double a;
	if (!parse_double(argv[2], &a)) {
		snprintf(result.error_message, sizeof(result.error_message), "Enter valid number");
		return result;
	}
	result.result_val = fn(a);
	if (isnan(result.result_val)) {
		// truly undefined
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Domain Error: Result is mathematically undefined");
	} else if (isinf(result.result_val)) {
		// overflow or approaches infinity
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Result exceeds double precision range");
	} else {
		result.status = MATHINATOR_OK;
	}
	return result;
}

static result_t dispatch_binary(int argc, char *argv[], binary_op fn, const char *usage) {
	result_t result = {MATHINATOR_INVALID, NAN, "Unknown error"};
	if (argc != 4) {
		snprintf(result.error_message, sizeof(result.error_message), "%s", usage); //
		return result;
	}
	double a, b;
	if (!parse_double(argv[2], &a) || !parse_double(argv[3], &b)) {
		snprintf(result.error_message, sizeof(result.error_message), "Enter valid numbers");
		return result;
	}
	result.result_val = fn(a, b);
	if (isnan(result.result_val)) {
		// truly undefined
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Domain Error: Result is mathematically undefined");
	} else if (isinf(result.result_val)) {
		// overflow or approaches infinity
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Result exceeds double precision range");
	} else {
		result.status = MATHINATOR_OK;
	}
	return result;
}

static double deg_to_rad(double deg) {
	deg = fmod(deg, 360.0);
	if (deg < 0)
		deg += 360.0;
	return deg * DEG_TO_RAD;
}

static result_t dispatch_trigo(int argc, char *argv[], unary_op fn, const char *usage) {
	result_t result = {MATHINATOR_INVALID, NAN, "Unknown error"};
	if ((argc != 3) && (argc != 4)) {
		snprintf(result.error_message, sizeof(result.error_message), "%s", usage); //
		return result;
	}
	if ((argc == 4) && (strcmp(argv[3], "--rad") != 0 && strcmp(argv[3], "--deg") != 0)) {
		snprintf(result.error_message, sizeof(result.error_message), "%s", usage); //
		return result;
	}
	double angle;
	if (!parse_double(argv[2], &angle)) {
		snprintf(result.error_message, sizeof(result.error_message), "Enter valid number");
		return result;
	}
	if ((argc == 3) || ((argc == 4) && (strcmp(argv[3], "--deg") == 0))) { // degree
		angle = deg_to_rad(angle);
	}
	result.result_val = fn(angle);
	if (isnan(result.result_val)) {
		// truly undefined
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Domain Error: Result is mathematically undefined");
	} else if (isinf(result.result_val)) {
		// overflow or approaches infinity
		result.status = MATHINATOR_UNDEF;
		snprintf(result.error_message, sizeof(result.error_message), "Result approaches infinity (undefined at %s angle)", argv[2]);
	} else {
		result.status = MATHINATOR_OK;
	}
	return result;
}

result_t parse_and_dispatch(int argc, char *argv[]) {
	result_t result = {MATHINATOR_INVALID, NAN, "Unknown error"};
	if (argc < 2) {
		snprintf(result.error_message, sizeof(result.error_message), "Usage: mathinator <command> <args>");
		return result;
	}
	if (strcmp(argv[1], "add") == 0) {
		return dispatch_binary(argc, argv, add, "Usage: mathinator add <n1> <n2>");
	} else if (strcmp(argv[1], "subtract") == 0) {
		return dispatch_binary(argc, argv, subtract, "Usage: mathinator subtract <n1> <n2>");
	} else if (strcmp(argv[1], "multiply") == 0) {
		return dispatch_binary(argc, argv, product, "Usage: mathinator multiply <n1> <n2>");
	} else if (strcmp(argv[1], "divide") == 0) {
		return dispatch_binary(argc, argv, divide, "Usage: mathinator divide <n1> <n2>");
	} else if (strcmp(argv[1], "remainder") == 0) {
		return dispatch_binary(argc, argv, rem, "Usage: mathinator remainder <n1> <n2>");
	} else if (strcmp(argv[1], "power") == 0) {
		return dispatch_binary(argc, argv, power, "Usage: mathinator power <n1> <n2>");
	} else if (strcmp(argv[1], "log") == 0) {
		return dispatch_binary(argc, argv, logarithm, "Usage: mathinator log <n1> <n2>");
	} else if (strcmp(argv[1], "sqroot") == 0) {
		return dispatch_unary(argc, argv, sqroot, "Usage: mathinator sqroot <n1>");
	} else if (strcmp(argv[1], "factorial") == 0) {
		return dispatch_unary(argc, argv, fact, "Usage: mathinator factorial <n1>");
	} else if (strcmp(argv[1], "sin") == 0) {
		return dispatch_trigo(argc, argv, trigo_sin, "Usage: mathinator sin <angle> [--deg|--rad]");
	} else if (strcmp(argv[1], "cos") == 0) {
		return dispatch_trigo(argc, argv, trigo_cos, "Usage: mathinator cos <angle> [--deg|--rad]");
	} else if (strcmp(argv[1], "tan") == 0) {
		return dispatch_trigo(argc, argv, trigo_tan, "Usage: mathinator tan <angle> [--deg|--rad]");
	} else if (strcmp(argv[1], "cot") == 0) {
		return dispatch_trigo(argc, argv, trigo_cot, "Usage: mathinator cot <angle> [--deg|--rad]");
	} else if (strcmp(argv[1], "sec") == 0) {
		return dispatch_trigo(argc, argv, trigo_sec, "Usage: mathinator sec <angle> [--deg|--rad]");
	} else if (strcmp(argv[1], "cosec") == 0) {
		return dispatch_trigo(argc, argv, trigo_cosec, "Usage: mathinator cosec <angle> [--deg|--rad]");
	} else {
		result.status = MATHINATOR_INVALID;
		snprintf(result.error_message, sizeof(result.error_message),
				 "Unknown command '%s'. Available commands:\n"
				 "  add, subtract, multiply, divide, remainder,\n"
				 "  power, log, sqroot, factorial,\n"
				 "  sin, cos, tan, cot, sec, cosec",
				 argv[1]);
		return result;
	}
}