#include "cli/parser.h"
#include "core/math_constants.h"
#include "core/types.h"
#include "math/arithmetic.h"
#include "math/stats.h"
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

static result_t set_result(result_status status, double value, const char *msg) {
	result_t r;
	r.status = status;
	r.result_val = value;
	snprintf(r.error_message, sizeof(r.error_message), "%s", msg);
	return r;
}

typedef double (*unary_op)(double);			 // function pointer for all math functions that take single operand
typedef double (*binary_op)(double, double); // function pointer for all math functions that take two operand
typedef double (*stats_op)(double[], int);	 // function pointer for all statistical functions

static result_t dispatch_unary(int argc, char *argv[], unary_op fn, const char *usage) {
	set_result(MATHINATOR_INVALID, NAN, "Unknown error");
	if (argc != 3) {
		return set_result(MATHINATOR_INVALID, NAN, usage);
	}
	double a;
	if (!parse_double(argv[2], &a)) {
		return set_result(MATHINATOR_INVALID, NAN, "Enter valid number");
	}
	double val = fn(a);
	if (isnan(val)) {
		// truly undefined
		return set_result(MATHINATOR_UNDEF, NAN, "Domain Error: Result is mathematically undefined");
	} else if (isinf(val)) {
		// overflow or approaches infinity
		return set_result(MATHINATOR_UNDEF, NAN, "Result exceeds double precision range");
	} else {
		return set_result(MATHINATOR_OK, val, "");
	}
}

static result_t dispatch_binary(int argc, char *argv[], binary_op fn, const char *usage) {
	set_result(MATHINATOR_INVALID, NAN, "Unknown error");
	if (argc != 4) {
		return set_result(MATHINATOR_INVALID, NAN, usage);
	}
	double a, b;
	if (!parse_double(argv[2], &a) || !parse_double(argv[3], &b)) {
		return set_result(MATHINATOR_INVALID, NAN, "Enter valid numbers");
	}
	double val = fn(a, b);
	if (isnan(val)) {
		// truly undefined
		return set_result(MATHINATOR_UNDEF, NAN, "Domain Error: Result is mathematically undefined");
	} else if (isinf(val)) {
		// overflow or approaches infinity
		return set_result(MATHINATOR_UNDEF, NAN, "Result exceeds double precision range");
	} else {
		return set_result(MATHINATOR_OK, val, "");
	}
}

static double deg_to_rad(double deg) {
	deg = fmod(deg, 360.0);
	if (deg < 0)
		deg += 360.0;
	return deg * DEG_TO_RAD;
}

static result_t dispatch_trigo(int argc, char *argv[], unary_op fn, const char *usage) {
	set_result(MATHINATOR_INVALID, NAN, "Unknown error");
	if ((argc != 3) && (argc != 4)) {
		return set_result(MATHINATOR_INVALID, NAN, usage);
	}
	if ((argc == 4) && (strcmp(argv[3], "--rad") != 0 && strcmp(argv[3], "--deg") != 0)) {
		return set_result(MATHINATOR_INVALID, NAN, usage);
	}
	double angle;
	if (!parse_double(argv[2], &angle)) {
		return set_result(MATHINATOR_INVALID, NAN, "Enter valid number");
	}
	if ((argc == 3) || ((argc == 4) && (strcmp(argv[3], "--deg") == 0))) { // degree
		angle = deg_to_rad(angle);
	}
	double val = fn(angle);
	if (isnan(val)) {
		// truly undefined
		return set_result(MATHINATOR_UNDEF, val, "Domain Error: Result is mathematically undefined");
	} else if (isinf(val)) {
		// overflow or approaches infinity
		char msg[256];
		snprintf(msg, sizeof(msg), "Result approaches infinity (undefined at %s angle)", argv[2]);
		return set_result(MATHINATOR_UNDEF, val, msg);
	} else {
		return set_result(MATHINATOR_OK, val, "");
	}
}

	static result_t dispatch_stats(int argc, char *argv[], stats_op fn, const char *usage) {
		set_result(MATHINATOR_INVALID, NAN, "Unknown error");
		if (argc < 3) {
			return set_result(MATHINATOR_INVALID, NAN, usage);
		}
		if (argc > MAX_CLI_ARGS + 2) {
			return set_result(MATHINATOR_INVALID, NAN, "Too many operands. Maximum 18 elements allowed");
		}
		int sample_size = argc - 2;
		double dataset[MAX_CLI_ARGS];
		for (int i = 0; i < sample_size; i++) {
			if (!parse_double(argv[i + 2], &dataset[i])) {
				return set_result(MATHINATOR_INVALID, NAN, "Invalid number in dataset. Please enter valid numbers.");
			}
		}
		// TODO: Accepting dataset via CSV file input in future, which will allow larger datasets. Will need to refactor this function to read from file instead of argv for that.

		double val = fn(dataset, sample_size);
		if(isnan(val)) {
			return set_result(MATHINATOR_UNDEF, val, "Domain Error: Result is mathematically undefined");
		} else {
			return set_result(MATHINATOR_OK, val, "");
		}
	}

	result_t parse_and_dispatch(int argc, char *argv[]) {
		set_result(MATHINATOR_INVALID, NAN, "Unknown error");
		if (argc < 2) {
			return set_result(MATHINATOR_INVALID, NAN, "Usage: mathinator <command> <args>");
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
		} else if (strcmp(argv[1], "mean") == 0) {
			return dispatch_stats(argc, argv, stats_mean, "Usage: mathinator mean <n1> <n2> ... <n18>");
		} else if (strcmp(argv[1], "median") == 0) {
			return dispatch_stats(argc, argv, stats_median, "Usage: mathinator median <n1> <n2> ... <n18>");
		} else if (strcmp(argv[1], "mode") == 0) {
			return dispatch_stats(argc, argv, stats_mode, "Usage: mathinator mode <n1> <n2> ... <n18>");
		} else if (strcmp(argv[1], "variance") == 0) {
			return dispatch_stats(argc, argv, stats_variance, "Usage: mathinator variance <n1> <n2> ... <n18>");
		} else if (strcmp(argv[1], "stddev") == 0) {
			return dispatch_stats(argc, argv, stats_stddev, "Usage: mathinator stddev <n1> <n2> ... <n18>");
		} else {
			char msg[256];
			snprintf(msg, sizeof(msg), "Unknown command '%s'. Available commands:\n"
									   "  add, subtract, multiply, divide, remainder,\n"
									   "  power, log, sqroot, factorial,\n"
									   "  sin, cos, tan, cot, sec, cosec",
					 argv[1]);
			return set_result(MATHINATOR_INVALID, NAN, msg);
		}
	}