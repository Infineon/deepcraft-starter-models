#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
/** Compile with gcc runner.c model.c -include model.h -O3 -o model  */

#if defined(IMAI_API_QUEUE_TIME)
#define API_QUEUE_TIME
#define API_ENQUEUE_TIME(data_in, time_in) IMAI_enqueue(data_in, time_in)
#define API_DEQUEUE_TIME(data_out, time_out) IMAI_dequeue(data_out, time_out)
#define API_TIME_OUT_COUNT IMAI_TIME_OUT_COUNT
#define API_TIME_IN_COUNT (1)
#elif defined(IMAI_API_QUEUE)
#define API_QUEUE
#define API_ENQUEUE(data_in) IMAI_enqueue(data_in)
#define API_DEQUEUE(data_out) IMAI_dequeue(data_out)
#define API_TIME_OUT_COUNT (0)
#define API_TIME_IN_COUNT (0)
#elif defined(IMAI_API_FUNCTION)
#define API_FUNCTION
#define API_COMPUTE(data_in, data_out) IMAI_compute(data_in, data_out)
#define API_TIME_OUT_COUNT (0)
#define API_TIME_IN_COUNT (0)
#else
#error "No API defined"
#endif

#define API_INIT() IMAI_init()

#define API_DATA_OUT_COUNT  IMAI_DATA_OUT_COUNT
#define API_DATA_OUT_TYPE  IMAI_DATA_OUT_TYPE
#define API_DATA_OUT_TYPE_ID  IMAI_DATA_OUT_TYPE_ID
#define API_DATA_OUT_IS_QUANTIZED IMAI_DATA_OUT_IS_QUANTIZED
#define API_DATA_OUT_DEQUANTIZE IMAI_DATA_OUT_DEQUANTIZE

#define API_DATA_IN_COUNT IMAI_DATA_IN_COUNT
#define API_DATA_IN_TYPE  IMAI_DATA_IN_TYPE
#define API_DATA_IN_TYPE_ID  IMAI_DATA_IN_TYPE_ID
#define API_DATA_IN_IS_QUANTIZED IMAI_DATA_IN_IS_QUANTIZED
#define API_DATA_IN_QUANTIZE IMAI_DATA_IN_QUANTIZE

#ifndef API_QERROR_MAX
#define API_QERROR_MAX 0
#endif

#ifndef API_QBOUNDS_MAX
#define API_QBOUNDS_MAX 0
#endif

typedef API_DATA_OUT_TYPE dout_t;
typedef API_DATA_IN_TYPE din_t;

#if API_DATA_IN_TYPE_ID == IMAGINET_TYPES_INT8
static void _data_read(void* ptr, int index, double value) {
    ((int8_t*)ptr)[index] = value;
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_INT16
static void _data_read(void* ptr, int index, double value) {
    ((int16_t*)ptr)[index] = value;
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_INT32
static void _data_read(void* ptr, int index, double value) {
    ((int32_t*)ptr)[index] = value;
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_FLOAT32
static void _data_read(void* ptr, int index, double value) {
    ((float*)ptr)[index] = value;
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_FLOAT64
static void _data_read(void* ptr, int index, double value) {
    ((double*)ptr)[index] = value;
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_QDYN8
static void _data_read(void* ptr, int index, double value) {
    ((int8_t*)ptr)[index] = API_DATA_IN_QUANTIZE(value);
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_QDYN16
static void _data_read(void* ptr, int index, double value) {
    ((int16_t*)ptr)[index] = API_DATA_IN_QUANTIZE(value);
}
#elif API_DATA_IN_TYPE_ID == IMAGINET_TYPES_QDYN32
static void _data_read(void* ptr, int index, double value) {
    ((int32_t*)ptr)[index] = API_DATA_IN_QUANTIZE(value);
}
#else
#error "Usupported input API type"
#endif

static void _data_read_f64(void* ptr, int index, double value) {
    ((double*)ptr)[index] = value;
}

#if API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_INT8
static double _data_write(void* ptr, int index) {
    return ((int8_t*)ptr)[index];
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_INT16
static double _data_write(void* ptr, int index) {
    return ((int16_t*)ptr)[index];
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_INT32
static double _data_write(void* ptr, int index) {
    return ((int32_t*)ptr)[index];
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_FLOAT32
static double _data_write(void* ptr, int index) {
    return ((float*)ptr)[index];
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_FLOAT64
static double _data_write(void* ptr, int index) {
    return ((double*)ptr)[index];
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_QDYN8
static double _data_write(void* ptr, int index) {
    return API_DATA_OUT_DEQUANTIZE(((int8_t*)ptr)[index]);
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_QDYN16
static double _data_write(void* ptr, int index) {
    return API_DATA_OUT_DEQUANTIZE(((int16_t*)ptr)[index]);
}
#elif API_DATA_OUT_TYPE_ID == IMAGINET_TYPES_QDYN32
static double _data_write(void* ptr, int index) {
    return API_DATA_OUT_DEQUANTIZE(((int32_t*)ptr)[index]);
}
#else
#error "Usupported input API type"
#endif

static double _data_write_f64(void* ptr, int index) {
    return ((double*)ptr)[index];
}

#ifndef IO_EXPORT
#define IO_EXPORT static
#endif

typedef void convert_read_fn(void* ptr, int index, double value);
typedef double convert_write_fn(void* ptr, int index);

typedef enum { FORMAT_AUTO = 0, FORMAT_CSV = 1, FORMAT_WAV = 2, FORMAT_NPY = 3 } file_format_t;

typedef struct {
	file_format_t format;	
} io_t;

IO_EXPORT io_t* io_open_read(
	file_format_t format,
	char* path,
	int data_column_count,
	bool read_header,
	bool timestamps,
	bool duration,
	convert_read_fn* convert);

IO_EXPORT io_t* io_open_write(
	file_format_t format,
	char* path,
	int data_column_count,
	bool write_header,
	bool timestamps,
	bool duration,
	int column_names_count,
	char** column_names,
	int npy_shape_count,
	size_t* npy_shape,
	convert_write_fn* convert);

IO_EXPORT bool io_can_read(io_t* io);

IO_EXPORT int io_read_data(io_t* io, float* time, float* duration, void* target);

IO_EXPORT void io_write_data(io_t* io, float time, float duration, void* source);

IO_EXPORT void io_close(io_t* io);

#ifndef ARGS_EXPORT
#define ARGS_EXPORT static
#endif

typedef enum { FILE_HEADER = 1, FILE_TIMESTAMP = 2, FILE_DURATION = 4 } file_opt_t;

typedef struct
{
    bool verbose;                   // --verbose
    bool print_top_errors;          // --top-errors
    bool has_test;                  // true if any test is active

    char* input_path;               // --input <path>
    file_format_t input_format;     // --input-format {auto, csv, wav}
    file_opt_t input_file_opt;      // --input-no-header --input-no-timestamp --input-has-duration

    char* expected_path;            // --expected <path>
    file_format_t expected_format;  // --expected-format {auto, csv, wav}
    file_opt_t expected_file_opt;   // --expected-no-header --expected-no-timestamp --expected-has-duration 

    char* output_path;              // --output <path>
    file_format_t output_format;    // --output-format {auto, csv, wav}
    file_opt_t output_file_opt;     // --output-no-header --output-no-timestamps --output-has-duration
    char** output_csv_columns;      // --output-columns {first, second, ...}
    int output_csv_columns_count;   // count(output_csv_columns)
    size_t* output_npy_shape;       // --output-shape {dim0, dim1, ...}
    int output_npy_shape_count;     // count(output_npy_shape)

    double test_timestamp;          // --test-timestamp <max_ms>
    double test_abserr;             // --test-abserr <threshold>
    double test_relerr;             // --test-relerr <threshold>
    double test_meanerr;            // --test-meanerr <threshold>
    double test_argmax;             // --test-argmax {0.0-1.0}

    bool batch_individual_test;     // --batch-individual-test

    char* batch_path;               // --batch <path>
    bool batch_write;               // --batch-write
    bool write_separate_time;       // --write-separate-time

    char* bounds_path;              // --output-bounds
    char* qerror_path;              // --output-qerror  
} args_t;


ARGS_EXPORT void print_usage(char* argv0);
ARGS_EXPORT void parse_args(int argc, char* argv[], args_t* arg);
ARGS_EXPORT bool ends_with(const char* str, const char* suffix);
ARGS_EXPORT void resolve_format(file_format_t* arg, const char* path);

#ifndef STATS_EXPORT
#define STATS_EXPORT static 
#endif

#define TOP_ERROR_COUNT 20

typedef struct
{
    int feature_count;
    int row_count;
    double max_time_error;
    double max_abs_error;
    double max_rel_error;
    double abs_error_sum;
    int argmax_error_count;
} stats_t;

typedef struct
{
    int row;   // First row is 1. 0 is unused slot
    int feature;

    double expected;
    double actual;
    double abs_error;
    double rel_error;
} top_error_t;

typedef struct
{
    stats_t stats;
    top_error_t top_errors[TOP_ERROR_COUNT];
} global_stats_t;

STATS_EXPORT void merge_stats(stats_t* source, stats_t* target);
STATS_EXPORT bool print_and_check_stats(stats_t* stats, args_t* args, const char* passed_prefix, const char* failed_prefix);
STATS_EXPORT void print_top_errors(global_stats_t* glob);
STATS_EXPORT void add_top_error(global_stats_t* glob, int row, int feature, double abs_error, double rel_error, double expected, double actual);

#ifndef UTILS_EXPORT
#define UTILS_EXPORT static 
#endif

UTILS_EXPORT void trim_white_space(char** str);
UTILS_EXPORT float min_f32(float* data, int count);
UTILS_EXPORT float max_f32(float* data, int count);
UTILS_EXPORT int argmax_f64(double* values, int count);
UTILS_EXPORT int argmax_dout(dout_t* values, int count);
UTILS_EXPORT int ensure_dir_path(char* path);

#ifndef QERROR_EXPORT
#define QERROR_EXPORT static
#endif

typedef struct
{
	double min;
	double max;
	double error;
	double first_error;
	long count;
} qerror_t;

QERROR_EXPORT void qerror_f32q16(const float* restrict values, int count, int index, double scale, double offset, const int16_t* restrict quantized);
QERROR_EXPORT int save_qerror_file(char* file_path);

#ifndef RUNNER_EXPORT
#define RUNNER_EXPORT static
#endif

typedef struct
{
    int index;

    char* input_path;
    char* output_path;
    char* expected_path;

    stats_t stats;

    int worst_row;
    int worst_feature;
    float worst_expected;
    float worst_actual;
} task_t;

typedef struct
{
    int count;
    int allocated;
    task_t** items;

    io_t* output_merged;      // if --batch and --output are given 
} tasklist_t;

typedef struct
{
    din_t* input_data;
    dout_t* output_data;
    double* expected_data;
} buffers_t;

ARGS_EXPORT void print_usage(char* argv0)
{
    printf("Usage: %s [options]\n\n", argv0);
    printf("options:\n");
    printf("-h, --help                         Display this text.\n");
    printf("\n");
    printf("-i, --input <file>                 Read from given file. Use - for stdin.\n");
    printf("-if, --input-format <type>         Input file format. One of: csv, wav, npy. Default is csv.\n");
    printf("-inh, --input-no-header            Input file don't have a header row.\n");
    printf("-int, --input-no-timestamp         Input file don't have a timestamp column.\n");
    printf("-ihd, --input-has-duration         Input file have duration column.\n");
    printf("\n");
    printf("-o, --output <file>                Write result to given file. Use - for stdout.\n");
    printf("-of, --output-format <type>        Output file format. One of: csv, wav, npy. Default is csv.\n");
    printf("-onh, --output-no-header           Do not write file header.\n");
    printf("-ont, --output-no-timestamps       Do not write timestamp column.\n");
    printf("-ohd, --output-has-duration        Write duration column.\n");
    printf("-oc, --output-columns <list>       Comma separated list with output column names without space.\n");
    printf("-os, --output-shape <list>         Comma separated list with numpy output shape dimensions without space.\n"
        "                                   The first number will be ignored and replaced by the actual number of rows produced.\n");
    printf("\n");
    printf("-e, --expected <file>              Compare output with given file and print max difference.\n");
    printf("-ef, --expected-format <type>      Expected file format. One of: csv, wav, npy. Default is csv\n");
    printf("-enh, --expected-no-header         Expected file don't have a header row.\n");
    printf("-ent, --expected-no-timestamp      Expected file don't have a timestamp column.\n");
    printf("-ehd, --expected-has-duration      Expected file have duration column.\n");
    printf("\n");
#if defined(API_QUEUE_TIME)
    printf("-tts, --test-timestamp <threshold> Test timestamps (if possible) with given threshold in seconds.\n");
#endif
    printf("-tar, --test-abserr <threshold>    Test max absolute error with given threshold.\n");
    printf("-tre, --test-relerr <threshold>    Test max relative error with given threshold.\n");
    printf("-tme, --test-meanerr <threshold>   Test max mean error with given threshold.\n");
    printf("-tam, --test-argmax <threshold>    Test argmax error factor with given threshold (0.0 ... 1.0).\n");
    printf("-bi, --batch-individual-test       When --batch option is used and you want to test each file independent.\n");
    printf("\n");
    printf("-v, --verbose                      Verbose output.\n");
    printf("-t, --top-errors                   Print top error list.\n");
    printf("-b, --batch <file>                 Run through all file pairs in given listing.\n"
        "                                   First column is input path, second column is optional expected file or output file.\n");
    printf("-bw, --batch-write                 Only relevant with --batch is given. \n"
        "                                   The second column is output file and will be overwritten.\n");
    printf("-wst, --write-separate-time        Write timestamps and duration as separate output files. \n"
        "                                   Only relevant when --batch-write is not given. \n"
        "                                   The second column is output file and will be overwritten.\n");
#ifdef API_QBOUNDS
    printf("-oq, --output-bounds <file>        Save quantization bounds file (.b).\n");
#endif

#ifdef API_QERROR
    printf("-oqe, --output-qerror <file>       Save quantization error file (.qerror).\n");
#endif	
}

ARGS_EXPORT void parse_args(int argc, char* argv[], args_t* arg)
{
    arg->verbose = false;
    arg->print_top_errors = false;

    arg->input_path = NULL;
    arg->input_format = FORMAT_AUTO;
    arg->input_file_opt = FILE_HEADER | FILE_TIMESTAMP;

    arg->expected_path = NULL;
    arg->expected_format = FORMAT_AUTO;
    arg->expected_file_opt = FILE_HEADER | FILE_TIMESTAMP;

    arg->output_path = NULL;
    arg->output_format = FORMAT_AUTO;
    arg->output_file_opt = FILE_HEADER | FILE_TIMESTAMP;
    arg->output_csv_columns = NULL;
    arg->output_csv_columns_count = 0;
    arg->output_npy_shape = NULL;
    arg->output_npy_shape_count = 0;

    arg->test_timestamp = NAN;
    arg->test_abserr = NAN;
    arg->test_relerr = NAN;
    arg->test_meanerr = NAN;
    arg->test_argmax = NAN;

    arg->batch_individual_test = false;

    arg->batch_path = NULL;
    arg->batch_write = false;
    arg->write_separate_time = false;

    arg->bounds_path = NULL;
    arg->qerror_path = NULL;

    for (int i = 1; i < argc; i++) {

        // --help
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            exit(0);
        }

        // --top-errors
        else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--top-errors") == 0) {
            arg->print_top_errors = true;
        }

        // --verbose
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            arg->verbose = true;
        }

        // --input
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -i missing file argument\n");
                exit(1);
            }
            arg->input_path = strdup(argv[i]);
        }

        // --output
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -o missing file argument\n");
                exit(1);
            }
            arg->output_path = strdup(argv[i]);
        }

        // --expected
        else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--expected") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -e missing file argument\n");
                exit(1);
            }
            arg->expected_path = argv[i];
        }

        // --input-format
        else if (strcmp(argv[i], "-if") == 0 || strcmp(argv[i], "--input-format") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -if missing argument\n");
                exit(1);
            }
            if (strcmp(argv[i], "csv") == 0) {
                arg->input_format = FORMAT_CSV;
            }
            else if (strcmp(argv[i], "wav") == 0) {
                arg->input_format = FORMAT_WAV;
            }
            else if (strcmp(argv[i], "npy") == 0) {
                arg->input_format = FORMAT_NPY;
            }
            else {
                fprintf(stderr, "Unknown file type: %s. Must be one of: csv, wav\n", argv[i]);
                exit(1);
            }
        }

        // --output-format
        else if (strcmp(argv[i], "-of") == 0 || strcmp(argv[i], "--output-format") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -of missing argument\n");
                exit(1);
            }
            if (strcmp(argv[i], "csv") == 0) {
                arg->output_format = FORMAT_CSV;
            }
            else if (strcmp(argv[i], "wav") == 0) {
                arg->output_format = FORMAT_WAV;
            }
            else if (strcmp(argv[i], "npy") == 0) {
                arg->output_format = FORMAT_NPY;
            }
            else {
                fprintf(stderr, "Unknown file type: %s. Must be one of: csv, wav\n", argv[i]);
                exit(1);
            }
        }

        // --expected-format
        else if (strcmp(argv[i], "-ef") == 0 || strcmp(argv[i], "--expected-format") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -ef missing argument\n");
                exit(1);
            }
            if (strcmp(argv[i], "csv") == 0) {
                arg->expected_format = FORMAT_CSV;
            }
            else if (strcmp(argv[i], "wav") == 0) {
                arg->expected_format = FORMAT_WAV;
            }
            else if (strcmp(argv[i], "npy") == 0) {
                arg->expected_format = FORMAT_NPY;
            }
            else {
                fprintf(stderr, "Unknown file type: %s. Must be one of: csv, wav\n", argv[i]);
                exit(1);
            }
        }

        // --input-no-header
        else if (strcmp(argv[i], "-inh") == 0 || strcmp(argv[i], "--input-no-header") == 0) {
            arg->input_file_opt &= ~FILE_HEADER;
        }

        // --input-no-timestamp
        else if (strcmp(argv[i], "-int") == 0 || strcmp(argv[i], "--input-no-timestamp") == 0) {
            arg->input_file_opt &= ~FILE_TIMESTAMP;
        }

        // --input-has-duration
        else if (strcmp(argv[i], "-ihd") == 0 || strcmp(argv[i], "--input-has-duration") == 0) {
            arg->input_file_opt |= FILE_DURATION;
        }

        // --output-no-header
        else if (strcmp(argv[i], "-onh") == 0 || strcmp(argv[i], "--output-no-header") == 0) {
            arg->output_file_opt &= ~FILE_HEADER;
        }

        // --output-no-timestamps
        else if (strcmp(argv[i], "-ont") == 0 || strcmp(argv[i], "--output-no-timestamps") == 0) {
            arg->output_file_opt &= ~FILE_TIMESTAMP;
        }

        // --output-has-duration
        else if (strcmp(argv[i], "-ohd") == 0 || strcmp(argv[i], "--output-has-duration") == 0) {
           arg->output_file_opt |= FILE_DURATION;
        }

        // --expected-no-header
        else if (strcmp(argv[i], "-enh") == 0 || strcmp(argv[i], "--expected-no-header") == 0) {
            arg->expected_file_opt &= ~FILE_HEADER;
        }

        // --expected-no-timestamp
        else if (strcmp(argv[i], "-ent") == 0 || strcmp(argv[i], "--expected-no-timestamp") == 0) {
            arg->expected_file_opt &= ~FILE_TIMESTAMP;
        }

        // --expected-has-duration
        else if (strcmp(argv[i], "-ehd") == 0 || strcmp(argv[i], "--expected-has-duration") == 0) {
            arg->expected_file_opt |= FILE_DURATION;
        }

        // --output-columns
        else if (strcmp(argv[i], "-oc") == 0 || strcmp(argv[i], "--output-columns") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -oc missing column names\n");
                exit(1);
            }
            else {
                arg->output_csv_columns_count++;

                for (char* p = argv[i]; *p != '\0'; p++) {
                    if (*p == ',')
                        arg->output_csv_columns_count++;
                }
                if (arg->output_csv_columns_count > 0)
                    arg->output_csv_columns = (char**)malloc(sizeof(char*) * arg->output_csv_columns_count);
                char* start = strdup(argv[i]);
                int col_index = 0;
                for (char* p = start; *p != '\0'; p++) {
                    if (*p == ',') {
                        *p = '\0';
                        arg->output_csv_columns[col_index++] = start;
                        start = ++p;
                    }
                }
                arg->output_csv_columns[col_index] = start;
            }
        }

        // --output-shape
        else if (strcmp(argv[i], "-os") == 0 || strcmp(argv[i], "--output-shape") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -os missing shape dimensions\n");
                exit(1);
            }
            else {
                // argv[i] = "dim0,dim1,..."
                // Determine number of dimensions
                arg->output_npy_shape_count++;
                for (char* p = argv[i]; *p != '\0'; p++) {
                    if (*p == ',')
                        arg->output_npy_shape_count++;
                }

                // Allocate int array to contain the shape
                // Note that arg->output_npy_shape_count > 0 is guaranteed.
                arg->output_npy_shape = (size_t*)malloc(sizeof(size_t) * arg->output_npy_shape_count);
                
                // Fill out the shape array by parsing the comma-separated elements in argv[i]
                int col_index = 0;
                char* token = argv[i];
                for (char* p = argv[i]; *p != '\0'; p++) {
                    if (*p == ',') {
                        arg->output_npy_shape[col_index++] = (size_t)atol(token); // TODO: Check for negative values
                        token = ++p;
                    }
                }
                arg->output_npy_shape[col_index] = (size_t)atol(token); // TODO: Check for negative value
            }
        }

        // --test-timestamp <max_ms>
        else if (strcmp(argv[i], "-tts") == 0 || strcmp(argv[i], "--test-timestamp") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -tts missing argument\n");
                exit(1);
            }
            if (sscanf(argv[i], "%lf", &arg->test_timestamp) != 1) {
                fprintf(stderr, "Unable to parse %s. Must be a number.\n", argv[i]);
                exit(1);
            }
        }

        // --test-abserr <threshold>
        else if (strcmp(argv[i], "-tar") == 0 || strcmp(argv[i], "--test-abserr") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -tar missing argument\n");
                exit(1);
            }
            if (sscanf(argv[i], "%lf", &arg->test_abserr) != 1) {
                fprintf(stderr, "Unable to parse %s. Must be a number.\n", argv[i]);
                exit(1);
            }
        }

        // --test-relerr <threshold>
        else if (strcmp(argv[i], "-tre") == 0 || strcmp(argv[i], "--test-relerr") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -tre missing argument\n");
                exit(1);
            }
            if (sscanf(argv[i], "%lf", &arg->test_relerr) != 1) {
                fprintf(stderr, "Unable to parse %s. Must be a number.\n", argv[i]);
                exit(1);
            }
        }

        // --test-meanerr <threshold>
        else if (strcmp(argv[i], "-tme") == 0 || strcmp(argv[i], "--test-meanerr") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -tme missing argument\n");
                exit(1);
            }
            if (sscanf(argv[i], "%lf", &arg->test_meanerr) != 1) {
                fprintf(stderr, "Unable to parse %s. Must be a number.\n", argv[i]);
                exit(1);
            }
        }

        // --test-argmax <threshold>
        else if (strcmp(argv[i], "-tam") == 0 || strcmp(argv[i], "--test-argmax") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -tam missing argument\n");
                exit(1);
            }
            if (sscanf(argv[i], "%lf", &arg->test_argmax) != 1) {
                fprintf(stderr, "Unable to parse %s. Must be a number.\n", argv[i]);
                exit(1);
            }
        }

        // --batch <file>
        else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--batch") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -b missing file argument\n");
                exit(1);
            }

            arg->batch_path = argv[i];
        }

        // --batch-write
        else if (strcmp(argv[i], "-bw") == 0 || strcmp(argv[i], "--batch-write") == 0) {
            arg->batch_write = true;
        }

        // --batch-individual-test
        else if (strcmp(argv[i], "-bi") == 0 || strcmp(argv[i], "--batch-individual-test") == 0) {
            arg->batch_individual_test = true;
        }

        // --write-separate-time
        else if (strcmp(argv[i], "-wst") == 0 || strcmp(argv[i], "--write-separate-time") == 0) {
            arg->write_separate_time = true;
        }

#ifdef API_QBOUNDS
        // --output-bounds <file>
        else if (strcmp(argv[i], "-ob") == 0 || strcmp(argv[i], "--output-bounds") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -ob missing file argument\n");
                exit(1);
            }

            arg->bounds_path = argv[i];
        }
#endif

#ifdef API_QERROR
        // --output-qerror <file>
        else if (strcmp(argv[i], "-oqe") == 0 || strcmp(argv[i], "--output-qerror") == 0) {
            i++;
            if (argc <= i) {
                fprintf(stderr, "Option -oqe missing file argument\n");
                exit(1);
            }
            arg->qerror_path = argv[i];
        }
#endif

        else {
            fprintf(stderr, "Unknown argument %s. Try --help\n", argv[i]);
            exit(1);
        }
    }

    // --input is required
    if (arg->input_path == NULL && arg->batch_path == NULL)
    {
        fprintf(stderr, "One of --input (-i) or --batch (-b) option is required.\n");
        print_usage(argv[0]);
        exit(0);
    }

    // input format
    if (arg->input_format == FORMAT_AUTO) {
        resolve_format(&arg->input_format, arg->input_path);
    }

    // output format
    if (arg->output_format == FORMAT_AUTO) {
        resolve_format(&arg->output_format, arg->output_path);
    }

    // expected format
    if (arg->expected_format == FORMAT_AUTO) {
        resolve_format(&arg->expected_format, arg->expected_path);
    }

    // --batch-write requires --batch
    if (arg->batch_write && arg->batch_path == NULL)
    {
        fprintf(stderr, "--batch-write requires --batch option. Please specify a batch file with the --batch option.\n");
        exit(1);
    }

    if (arg->batch_path != NULL)
    {
        if (arg->input_path != NULL)
        {
            fprintf(stderr, "--batch can not be used with --input option.\n");
            exit(1);
        }

        if (arg->expected_path != NULL)
        {
            fprintf(stderr, "--batch can not be used with --expected option.\n");
            exit(1);
        }       
    }

    // --batch-write and write-separate-time can't be used together, becuase the second file name column in the file list is used for either.
    if (arg->batch_write && arg->write_separate_time)
    {
        fprintf(stderr, "--batch-write can not be used with --write-separate-time option.\n");
        exit(1);
    }

#if !defined(API_QUEUE_TIME)
    if (!isnan(arg->test_timestamp)) {
        fprintf(stderr, "WARNING: --test-timestamp used with a model does not have timestamp tracking support. Timestamp check disabled!\n");
        arg->test_timestamp = NAN;
    }
#endif

    if (!isnan(arg->test_timestamp)) {
        if (arg->input_format == FORMAT_CSV && ((arg->input_file_opt & FILE_TIMESTAMP) == 0)) {
            fprintf(stderr, "WARNING: --test-timestamp is not compatible with --input-no-timestamp. Timestamp check disabled!\n");
            arg->test_timestamp = NAN;
        }
        else if (arg->expected_format == FORMAT_CSV && ((arg->expected_file_opt & FILE_TIMESTAMP) == 0)) {
            fprintf(stderr, "WARNING: --test-timestamp is not compatible with --expected-no-timestamp. Timestamp check disabled!\n");
            arg->test_timestamp = NAN;
        }
    }

    bool has_test = !isnan(arg->test_timestamp)
        || !isnan(arg->test_abserr)
        || !isnan(arg->test_relerr)
        || !isnan(arg->test_meanerr)
        || !isnan(arg->test_argmax);

    if (!has_test && (!arg->batch_write && arg->expected_path != NULL))
    {
        fprintf(stdout, "Defaults test to --test-abserr 0.001.\n");
        arg->test_abserr = 0.001;
        has_test = true;
    }

    arg->has_test = has_test;

    if (has_test && arg->batch_write)
    {
        fprintf(stderr, "The --batch-write option can not be used with any of the testing options (--test-*)\n");
        exit(1);
    }

    if (has_test && arg->expected_path == NULL && arg->batch_path == NULL)
    {
        fprintf(stderr, "The testing options (--test-*) requires you specify expected input with --expected or --batch option.\n");
        exit(1);
    }
}

ARGS_EXPORT bool ends_with(const char* str, const char* suffix)
{
    int len = strlen(suffix);
    return str != NULL && strncmp(str + strlen(str) - len, suffix, len) == 0;
}

ARGS_EXPORT void resolve_format(file_format_t* arg, const char* path)
{
    if (*arg == FORMAT_AUTO && path != NULL)
    {
        if (ends_with(path, ".wav"))
            *arg = FORMAT_WAV;
        else if (ends_with(path, ".csv"))
            *arg = FORMAT_CSV;
        else if (ends_with(path, ".data"))
            *arg = FORMAT_CSV;
        else if (ends_with(path, ".npy"))
            *arg = FORMAT_NPY;
    }
}

#ifndef CSV_EXPORT
#define CSV_EXPORT static
#endif


typedef struct {
	file_format_t format;
	bool timestamps;
	bool duration;
	int data_column_count;
	int time_column_count;
	FILE* fd;
	bool nan_inf_error;
	convert_read_fn* convert_read;
	convert_write_fn* convert_write;
} csv_t;


CSV_EXPORT csv_t* csv_open_read(
	char* path,
	int data_column_count,
	bool read_header,
	bool timestamps,
	bool duration,
	convert_read_fn* convert);

CSV_EXPORT csv_t* csv_open_write(
	char* path,
	int data_column_count,
	bool write_header,
	bool timestamps,
	bool duration,
	int column_names_count,
	char** column_names,
	convert_write_fn* convert);

CSV_EXPORT bool csv_can_read(csv_t* csv);

CSV_EXPORT int csv_read_data(csv_t* csv, float* time, float* duration, void* target);

CSV_EXPORT void csv_write_data(csv_t* csv, float time, float duration, void* source);

CSV_EXPORT void csv_close(csv_t* csv);

static char _csv_read_buf[1024 * 1024]; // max header row length

static void _csv_write_header(csv_t* csv, int count, char** label_names);
static void _csv_read_header(FILE* input_file);
static void _csv_skip_utf8_bom(FILE* file);

CSV_EXPORT csv_t* csv_open_read(
	char* path, 
	int data_column_count,
	bool read_header, 
	bool timestamps,
	bool duration,
	convert_read_fn* convert)
{
	if (path == NULL)
		return NULL;

	csv_t* csv = malloc(sizeof(csv_t));
	if (csv == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}

	csv->format = FORMAT_CSV;
	csv->timestamps = timestamps;
	csv->duration = duration;
	csv->data_column_count = data_column_count;
	csv->convert_read = convert;
	csv->nan_inf_error = false;
	csv->time_column_count = 0;
	if (timestamps)
		csv->time_column_count++;
	if (duration)
		csv->time_column_count++;

	if (path[0] == '-' && path[1] == '\0') {
		csv->fd = stdin;
	}
	else {
		csv->fd = fopen(path, "r");
		if (csv->fd == NULL) {
			fprintf(stderr, "Error opening file (%s) for reading: %s\n", path, strerror(errno));
			exit(1);
		}
	}

	_csv_skip_utf8_bom(csv->fd);
	if (read_header) {
		_csv_read_header(csv->fd);
	}

	return csv;
}

CSV_EXPORT csv_t* csv_open_write(
	char* path, 
	int data_column_count, 
	bool write_header,
	bool timestamps, 
	bool duration,
	int column_names_count,
	char** column_names,
	convert_write_fn* convert)
{
	if (path == NULL)
		return NULL;

	csv_t* csv = malloc(sizeof(csv_t));
	if (csv == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}

	csv->format = FORMAT_CSV;
	csv->timestamps = timestamps;
	csv->duration = duration;
	csv->data_column_count = data_column_count;
	csv->convert_write = convert;
	csv->nan_inf_error = false;
	csv->time_column_count = 0;
	if (timestamps)
		csv->time_column_count++;
	if (duration)
		csv->time_column_count++;

	if (path[0] == '-' && path[1] == '\0') {
		csv->fd = stdin;
	}
	else {
		csv->fd = fopen(path, "w");
		if (csv->fd == NULL) {
			fprintf(stderr, "Error opening file (%s) for writing: %s\n", path, strerror(errno));
			exit(1);
		}

		/* Clear file?
		 * fseek(csv->fd, 0, SEEK_SET);
		 * ftruncate(fileno(csv->fd), 0);
		 * fflush(output_file);
		 */
	}

	if (write_header) {
		if (column_names_count && column_names)
			_csv_write_header(csv, column_names_count, column_names);
		else
			_csv_write_header(csv, data_column_count, NULL);
	}

	return csv;
}

CSV_EXPORT void csv_close(csv_t* csv)
{
	if (csv == NULL)
		return;

	if (csv->fd != NULL && csv->fd != stdin && csv->fd != stdout && csv->fd != stderr)
		fclose(csv->fd);

	free(csv);
}

CSV_EXPORT bool csv_can_read(csv_t* csv)
{
	return !feof(csv->fd);
}

CSV_EXPORT int csv_read_data(csv_t* csv, float* time, float* duration, void* target)
{
	char* ptr = NULL;
	char* next;
	

	int data_size = csv->data_column_count;

	while (true) {
		_csv_read_buf[0] = '\0';
		if (feof(csv->fd) || fgets(_csv_read_buf, sizeof(_csv_read_buf), csv->fd) == NULL) {
			return 1;
		}
		ptr = _csv_read_buf;

		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r') ptr++;

		if (*ptr == '\0')
			continue;

		break;
	}

	for (int i = 0;ptr; i++) {
		next = NULL;
		double value = strtod(ptr, &next);
		if (next == ptr) {
			fprintf(stderr, "Failed to parse number in line :%s\n", ptr);
			exit(1);
		}

		if (isnan(value) || isinf(value)) {
			if(!csv->nan_inf_error)
				fprintf(stderr, "WARNING: NaN or Inf values found in input data.\n");
			csv->nan_inf_error = true;
		}

		if (i < csv->time_column_count) {
			if (i == 0)
				*time = value;
			if (i == 1)
				*duration = value;
		}
		else if ((i - csv->time_column_count) < data_size) {
			csv->convert_read(target, i - csv->time_column_count, value);
		}
		else {
			fprintf(stderr, "File read error. Shape error. Expected %i columns, found %i:th\n", data_size + csv->time_column_count, i + 1);
			exit(1);
		}

		ptr = next;
		while (*ptr == ' ' || *ptr == '\t' || *ptr == ',' || *ptr == '\n' || *ptr == '\r') ptr++;

		if (*ptr == '\0') {
			if ((i - csv->time_column_count + 1) < data_size)
			{
				fprintf(stderr, "File read error. Shape error. Expected %i columns, found only %i\n", data_size + csv->time_column_count, i + 1);
				exit(1);
			}
			break;
		}
	}

	return 0;
}

CSV_EXPORT void csv_write_data(csv_t* csv, float time, float duration, void* source)
{
	float time_buf[2];
	time_buf[0] = time;
	time_buf[1] = duration;

	for(int i = 0; i < csv->time_column_count; i++) 
	    fprintf(csv->fd, "%g, ", (double)time_buf[i]);

	int count = csv->data_column_count;

	for (int i = 0; i < count; i++) {
		double value = csv->convert_write(source, i);

		if (isnan(value) || isinf(value)) {
			if (!csv->nan_inf_error)
				fprintf(stderr, "WARNING: NaN or Inf values found in output data.\n");
			csv->nan_inf_error = true;
		}

		fprintf(csv->fd, "%g", value);
		if (i != count - 1)
			fprintf(csv->fd, ", ");
	}
	fprintf(csv->fd, "\n");
	fflush(csv->fd);
}

static void _csv_read_header(FILE* input_file)
{
	_csv_read_buf[0] = '\0';
	fgets(_csv_read_buf, sizeof(_csv_read_buf), input_file);

	// Check if first row is headers. Skip 'e' since it may be a number in scientific notation
	if (strpbrk(_csv_read_buf, "#abcd_fghijklmnopqrstuvwxyzABCDFGHIJKLMNOPQRSTUVWXYZ") == NULL)
	{
		printf("Warning: Suspicious first row in CSV file. First row should be a header.\n");
		exit(1);
	}
}

// Checked
static void _csv_write_header(csv_t* csv, int count, char** label_names)
{
	fprintf(csv->fd, "# ");

	if (csv->timestamps)
		fprintf(csv->fd, "Time (seconds), ");
		
	if (csv->duration)
		fprintf(csv->fd, "Duration (seconds), ");

	for (int i = 0; i < count; i++) {
		if (label_names == NULL)
			fprintf(csv->fd, "f%i", i);
		else
			fprintf(csv->fd, "%s", label_names[i]);
		if (i != count - 1)
			fprintf(csv->fd, ", ");
	}

	fprintf(csv->fd, "\n");
}

// Checked
static void _csv_skip_utf8_bom(FILE* file)
{
	fpos_t pos;
	if (feof(file) || fgetpos(file, &pos) != 0) {
		return;
	}

	uint8_t bom[3];
	if (fread(bom, 1, 3, file) != 3 ||
		bom[0] != 0xef ||
		bom[1] != 0xbb ||
		bom[2] != 0xbf) {
		fsetpos(file, &pos);
	}
}

#include <stddef.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <ctype.h>
/******** npio.h begin **********/

#ifndef NPIO_H_
#define NPIO_H_

/******************************************************************************

Simple header-only routines for reading and writing numpy files. This header
can be used with both C and C++ code. There are no external library
dependencies. Just place the header in your include path to use.

Based on the documentation at
  https://docs.scipy.org/doc/numpy-dev/neps/npy-format.html


License: MIT (see LICENSE.txt)


Limitations:

Can only be used for homogenous arrays. Structured arrays and Object arrays are
not supported.  Structured arrays may be supported at some point in the future.

This code does not conform strictly to the specified format.  It is known to
work with files actually generated by numpy, but there are lots of variations
in the header that are not supported by the minimalist parser in this file.

It is safe to use this with numpy files that may contain pickle objects or
executable code - such files will simply result in an error.

This code assumes that a C char is a single octet.  If you are on a system
that does not satisfy this assumption, you should buy a different system.


Authors:

Vishal (vishal@onutechnology.com)

******************************************************************************/


/* Version of this header. */
#define NPIO_MAJOR_VERSION 0
#define NPIO_MINOR_VERSION 1

/* Some defaults */
#define NPIO_DEFAULT_MAX_DIM 32

/* Summary of revisions:

0.1  Initial version

*/


/* This struct represents the contents of a numpy file. */
typedef struct
{
  char   major_version;  /* The npy major version number. */
  char   minor_version;  /* The npy minor version number. */
  size_t header_len;     /* The length of the header in the file. */
  char   *dtype;         /* The unparsed string representation of dtype */
  size_t dim;            /* The number of elements in shape. */
  size_t *shape;         /* The size on each axis. */
  size_t size;           /* The total number of elements.[1] */
  int    fortran_order;  /* Whether or not data is in fortan-ordering. */
  int    little_endian;  /* Whether or not elements are little-endian. */
  int    floating_point; /* Whether data is integral or floating point.*/
  int    is_signed;      /* Whether data is signed or unsigned */
  int    bit_width;      /* The number of bits to this datatype*/
  void   *data;          /* Pointer to contents*/

  /* The following fields are private. */
  int    _fd;        /* File descriptor from which we are loading */
  void*  _buf;       /* Memory buffer from where we are loading */
  size_t _buf_size;  /* Size of memory buffer from where we are loading */
  char*  _hdr_buf;   /* A buffer for the header, if we are loading from fd */
  size_t _shape_capacity;  /* The space allocated for shape */
  int    _mmapped;   /* Whether we mmapped the data into buf */
  int    _malloced;  /* Whether we allocated the buffer */
  int    _opened;    /* Whether we opened the file descriptor */
} npio_Array;

/*

[1]: the size field is only set when you load a numpy file.  If you
    want to save a numpy file, the size field is ignored by the library
    and the size is computed from the shape. Both the npio_array_size() and
    npio_array_memsize() functions do a full computation of the number of
    elements from the shape, so if you are populating the struct yourself,
    you may want to explicitly set the array->size field to cache it.

*/


/*

Some internal notes:

-  The _buf field is set if either loading from memory or from a mapped file.
-  The data field is allocated by us if _buf is null.

*/



/* Compute the total number of elements from the shape. */
static inline size_t npio_array_size(const npio_Array* array)
{
  size_t n = 1, i;
  for (i = 0; i < array->dim; ++i)
    n *= array->shape[i];
  return n;
}


/* Return the memory size in bytes that would be needed by the array data
   Note: this does a full computation of the size from the shape. */
static inline size_t npio_array_memsize(const npio_Array* array)
{
  return npio_array_size(array) * array->bit_width / 8;
}


/* Minimalist parser for python dict in the header. Lots of files that are
valid as per the spec may not be deemed valid by this code. Caveat Emptor. */


/* skip until we see a non-whitespace character. */
static inline const char* npio_ph_skip_spaces_(const char* p, const char* end)
{
  while (p < end && isspace((int) *p))
    ++p;
  return p;
}


/* append a value to array->shape, reallocating if needed. */
static inline int npio_ph_shape_append_(npio_Array* array, size_t val)
{
  size_t *tmp;
  if (array->dim == array->_shape_capacity)
  {
    array->_shape_capacity *= 2;
    tmp = (size_t*) realloc(array->shape, sizeof(size_t) * array->_shape_capacity);
    if (tmp == 0)
      return ENOMEM;
    array->shape = tmp;
  }
  array->shape[array->dim++] = val;
  return 0;
}


/* Parse a python tuple of integers.  Anything else should fail. */
static inline int npio_ph_parse_shape_(npio_Array* array, const char *start
  , const char *end, const char **where)
{
  const char *p = start, *nbeg, *nend;
  size_t val;
  int err;

  if (p == end)
    return EINVAL;

  if (*p++ != '(')
    return EINVAL;

  array->_shape_capacity = 8;
  array->shape = (size_t*) malloc(sizeof(size_t) * array->_shape_capacity);
  if (array->shape == 0)
    return ENOMEM;

  while (1)
  {
    p = npio_ph_skip_spaces_(p, end);

    nbeg = p;
    while (p < end && *p >= '0' && *p <= '9')
      ++p;
    nend = p;

    if (p == end)
      return EINVAL;

    if (nbeg < nend)  /* trailing comma is allowed in python, so must check */
    {
      val = 0;
      while (nbeg < nend)
        val = (*nbeg++ - '0') + val * 10;
      if ((err = npio_ph_shape_append_(array, val)))
        return err;
    }

    p = npio_ph_skip_spaces_(p, end);
    if (p == end)
      return EINVAL;
    if (*p == ',')
      ++p;
    else if (*p == ')')
    {
      ++p;
      break;
    }
    else
      return EINVAL;
  }

  *where = p;
  array->size = npio_array_size(array);
  return 0;
}


/*

Parse a dtype for homogeneous arrays.

The Numpy specification says that the dtype can be any Python object that would
serve as a valid argument to numpy.dtype(). Right now we restrict the dtype to
match strings of the form 'EDN' where E can be '<' or '>' for the endianness, D
can be 'i', 'f' or 'u' for the c-type and N can be 1, 2, 4, or 8. All others we
reject. If we really want support for structured data (tables), then we need a
better parser and a single-header minimalist solution may not be appropriate.

Arguments:
  dtype is the null-terminated string value of the dtype in the header.

Return:
  A parsed type if we understand the dtype, otherwise npio_unknown.

*/
static inline int npio_ph_parse_dtype_(npio_Array* array)
{
  const char* dtype = array->dtype;

  if (strlen(dtype) != 3)
    return ENOTSUP;

  switch (dtype[0])
  {
    case '<': array->little_endian = 1; break;
    case '>': array->little_endian = 0; break;
    default : return ENOTSUP;
  }

  switch (dtype[1])
  {
    case 'i':
      array->is_signed = 1;
      array->floating_point = 0;
      break;

    case 'u':
      array->is_signed = 0;
      array->floating_point = 0;
      break;

    case 'f':
      array->is_signed = 1;
      array->floating_point = 1;
      break;

    default:
      return ENOTSUP;
  }

  switch (dtype[2])
  {
    case '1': array->bit_width = 8; break;
    case '2': array->bit_width = 16; break;
    case '4': array->bit_width = 32; break;
    case '8': array->bit_width = 64; break;
    default: return ENOTSUP;
  }

  return 0;
}


static inline int npio_ph_is_quote_(char p)
{
  return (p == '\'' || p == '"');
}


/* parse a python dictionary containing the specific keys and value we expect */
static inline int npio_ph_parse_dict_(npio_Array* array, const char* start, const char* end)
{
  int err;
  char open_quote;
  const char *p = start;
  const char *dtbeg, *dtend;
  size_t dtsz;
  enum {k_descr, k_shape, k_fortran_order} key;

  if (p >= end)
    return EINVAL;

  if (*p++ != '{')
    return EINVAL;

  /* Go through all key-value pairs. */
  while (1)
  {
    p = npio_ph_skip_spaces_(p, end);
    if (p >= end)
      return EINVAL;

    /* are we done? */
    if (*p == '}')
    {
      ++p;
      break;
    }

    /* Expect the open quote of a key */
    if (!npio_ph_is_quote_(open_quote = *p++))
      return EINVAL;

    /* Check for one of the three possible keys */
    if (p + 5 < end && memcmp(p, "descr", 5) == 0)
    {
      key = k_descr;
      p += 5;
    }
    else if (p + 5 < end && memcmp(p, "shape", 5) == 0)
    {
      key = k_shape;
      p += 5;
    }
    else if (p + 13 < end && memcmp(p, "fortran_order", 13) == 0)
    {
      key = k_fortran_order;
      p += 13;
    }
    else
      return EINVAL;

    /* Expect the close quote of the key */
    if (p >= end || *p++ != open_quote)
      return EINVAL;

    /* Get to the colon */
    p = npio_ph_skip_spaces_(p, end);
    if (p >= end || *p++ != ':')
      return EINVAL;

    /* skip any more spaces */
    p = npio_ph_skip_spaces_(p, end);
    if (p == end)
      return EINVAL;

    switch (key)
    {
      case k_descr:
        if (!npio_ph_is_quote_(open_quote = *p++))
          return EINVAL;
        dtbeg = p;
        while (p < end && *p != open_quote)
          ++p;
        dtend = p;
        if (p == end)
          return EINVAL;
        ++p;
        dtsz = dtend - dtbeg;
        array->dtype = (char*) malloc(dtsz + 1);
        memcpy(array->dtype, dtbeg, dtsz);
        array->dtype[dtsz] = 0;
        break;

      case k_fortran_order:
        if (p + 4 < end && memcmp(p, "True", 4) == 0)
        {
          array->fortran_order = 1;
          p += 4;
        }
        else if (p + 5 < end && memcmp(p, "False", 5) == 0)
        {
          array->fortran_order = 0;
          p += 5;
        }
        else
          return EINVAL;
        break;

      case k_shape:
        if ((err = npio_ph_parse_shape_(array, p, end, &p)))
          return err;
        break;
    }

    /* skip any spaces after end of key : value */
    p = npio_ph_skip_spaces_(p, end);

    if (p == end)
      return EINVAL;

    /* grab that separating comma */
    if (*p == ',')
      ++p;

    /* next iteration takes care of any nonsense that might happen here! */
  }

  /* Parse the (very restricted) numpy dtype and return */
  return npio_ph_parse_dtype_(array);
}



/* Initialize the struct so that we can cleanup correctly. Also provide
defaults for npy_save
*/
static inline void npio_init_array(npio_Array* array)
{
  array->major_version = 1;
  array->minor_version = 0;
  array->header_len = 0;
  array->dtype = 0;
  array->dim = 0;
  array->shape = 0;
  array->size = 0;
  array->fortran_order = 0;
  array->little_endian = (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
  array->floating_point = 1;
  array->is_signed = 1;
  array->bit_width = 32;
  array->data = 0;
  array->_fd = 0;
  array->_buf = 0;
  array->_buf_size = 0;
  array->_hdr_buf = 0;
  array->_shape_capacity = 0;
  array->_mmapped = 0;
  array->_malloced = 0;
}


/*

Release all resources associated with an Array that was initialized with
npio_init_array and then populated via one of the npio_load_* functions.

You should not call this if you manually populated the Array structure for
writing out data that you allocated yourself.

Note: this function does not free any memory associated with the struct itself.

Arguments:
  array: a previously loaded array.
*/
static inline void npio_free_array(npio_Array* array)
{
  if (array->dtype)
  {
    free(array->dtype);
    array->dtype = 0;
  }

  if (array->shape)
  {
    free(array->shape);
    array->shape = 0;
  }

  if (array->data && !array->_buf)
  {
    free(array->data);
    array->data = 0;
  }

  if (array->_mmapped)
  {
    munmap(array->_buf, array->_buf_size);
    array->_buf = 0;
  }

  if (array->_fd >= 0)
  {
    close(array->_fd);
    array->_fd = -1;
  }

  if (array->_hdr_buf)
  {
    free(array->_hdr_buf);
    array->_hdr_buf = 0;
  }
}


/*
Check the magic number, the format version and gets the HEADER_LEN field.
The prelude should have atleast 10 characters for version 1 and 12 characters
for version 2.
*/
static inline int npio_load_header_prelude_(char* p, npio_Array* array, char** end)
{
  /* assert magic string. Basic size check was done above. */
  if (memcmp(p, "\x93NUMPY", 6) != 0)
    return EINVAL;
  p += 6;

  /* get the version numbers */
  array->major_version = *p++;
  array->minor_version = *p++;

  /* get the header length. Version 1 uses 2 bytes, version 2 uses 4 bytes. */
  switch (array->major_version)
  {
    case 1:
      array->header_len = p[0] + (p[1] << 8);
      p += 2;
      break;

    case 2:
      array->header_len = p[0]
        + (p[1] << 8)
        + (p[2] << 16)
        + (p[3] << 24);
      p += 4;
      break;

    default:
      return ENOTSUP;
  }
  *end = p;
  return 0;
}


/* Load the header from a pointer to (partial) file data in memory. */
static inline int npio_load_header_mem4(void* p_, size_t sz
  , npio_Array* array, size_t max_dim)
{
  int err;
  char* p = (char*) p_;
  char *end = p + sz;

  /* sanity check, to avoid some checks a bit later. */
  if (sz < 16)
    return EINVAL;

  /* Store this buffer address for load_data */
  if (!array->_mmapped)
  {
    array->_buf = p;
    array->_buf_size = sz;
  }

  if ((err = npio_load_header_prelude_(p, array, &p)))
    return err;

  /* Ensure that the header_len doesn't make us go out of bounds */
  if (p + array->header_len < end)
    end = p + array->header_len;

  /* Parse the header and return */
  return npio_ph_parse_dict_(array, p, end);
}


/* Same as above, with default max_dim */
static inline int npio_load_header_mem(void *p, size_t sz, npio_Array* array)
{
  return npio_load_header_mem4(p, sz, array, NPIO_DEFAULT_MAX_DIM);
}


/* Loads the header using read calls instead of mmap. */
static inline int npio_load_header_fd_read_(int fd, npio_Array* array, size_t max_dim)
{
  /* Read just enough to know how much more we need to read */
  char prelude[12];
  char *end;
  int nr, err;
  size_t prelude_size;

  nr = read(fd, prelude, sizeof(prelude));
  if (nr < (int) sizeof(prelude))
    return errno;

  if ((err = npio_load_header_prelude_(prelude, array, &end)))
    return err;

  /* Keep track of how many bytes of prelude were present */
  prelude_size = end - prelude;

  /* We suppose here that each dimension in shape should not take more than 20
  characters to estimate a limit on the header_len. Admitted, this is sloppy. */
  if (array->header_len > 1024 + max_dim * 20)
    return ERANGE;

  /* We stick the prelude back together with the rest of the header */
  if ((array->_hdr_buf = (char*) malloc(prelude_size + array->header_len)) == 0)
    return ENOMEM;
  memcpy(array->_hdr_buf, prelude, sizeof(prelude));

  /* Now read in the rest of the header, accounting for excess bytes possibly
     read in with the prelude. */
  nr = read(fd, array->_hdr_buf + sizeof(prelude)
    , array->header_len - (sizeof(prelude) - prelude_size));

  /* Parse the header */
  return npio_ph_parse_dict_(array, array->_hdr_buf + prelude_size, end);
}


/*
Load the header of a numpy file.  If successful, you may call npio_load_data
subsequently to actually obtain the array elements.  Finally you must call
npio_free_array to release all associated resources, even if there was an
error while loading.

Arguments:
  fd: file descriptor of a file in numpy format.
  array: pointer to an Array struct that will be populated (partially) on
    return. The data is not loaded.  You must have called npio_init_array
    on array prior to calling this function.
  max_hdr_size: as a security measure, return an error if the header size
    is larger than this limit.

Return:
  0 on success.
  EINVAL   the file is not a valid numpy file, or we failed to parse.
  ENOTSUP  unsupported npy version
  ERANGE   header exceeded max_hdr_size
  Other errno codes if file could not be accessed etc.
*/
static inline int npio_load_header_fd3(int fd, npio_Array* array, size_t max_dim)
{
  ssize_t file_size;
  char *p;

  /* Store the file descriptor for load_data */
  if (!array->_opened)
    array->_fd = fd;

  /* Get the file size in preparation to mmap */
  file_size = lseek(fd, 0, SEEK_END);

  /* If we could not lseek, fallback on read. */
  if (file_size < 0)
    return npio_load_header_fd_read_(fd, array, max_dim);

  /* map-in the file */
  p = (char*) mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (p == MAP_FAILED)
  {
    if (lseek(fd, 0, SEEK_SET))
      return errno;
    return npio_load_header_fd_read_(fd, array, max_dim);
  }

  array->_mmapped = 1;
  array->_buf = p;
  array->_buf_size = file_size;

  return npio_load_header_mem4(p, file_size, array, max_dim);
}


/* Same as above, with default max_dim */
static inline int npio_load_header_fd(int fd, npio_Array* array)
{
  return npio_load_header_fd3(fd, array, NPIO_DEFAULT_MAX_DIM);
}


/* Load the header of a numpy array from a file. The data is not explicitly
   loaded (although it may be mapped into memory if the specified path is
   mappable). */
static inline int npio_load_header3(const char* filename, npio_Array* array
  , size_t max_dim)
{
  int fd, err;
  fd = open(filename, O_RDONLY);
  if (fd < 0)
    return errno;
  array->_fd = fd;
  array->_opened = 1;
  err = npio_load_header_fd3(fd, array, max_dim);

  /* we don't need to hang on the fd if we managed to map */
  if (array->_mmapped)
  {
    close(fd);
    array->_fd = -1;
    array->_opened = 0;
  }
  return err;
}


/* Same as above, with a default max_dim */
static inline int npio_load_header(const char* filename, npio_Array* array)
{
  return npio_load_header3(filename, array, NPIO_DEFAULT_MAX_DIM);
}


/* Swap two bytes, used for endian conversion below. */
static inline void npio_swap_bytes_(char* p1, char* p2)
{
  char tmp;
  tmp = *p2;
  *p2 = *p1;
  *p1 = tmp;
}


/*

Reverse the bytes of each element in the array to go from little to big or big
to little endian. This is a simple non-optimized implementation for the sake of
portability and ease-of-compilation of this code. Performance will be quite
poor.

Note: assumption: 1 byte == 1 octet.

Arguments:
  n: the number of elements in the array
  bit_width: number of bits per element, with 8 bits == 1 byte
  data: pointer to data.

*/
static inline int npio_swap_bytes(size_t n, size_t bit_width, void* data)
{
  size_t i;
  char *p = (char*) data;

  if (bit_width == 8)
    return 0;

  switch (bit_width)
  {
    case 16:
      for (i = 0; i < n; ++i)
      {
        npio_swap_bytes_(p, p + 1);
        p += 2;
      }
      return 0;

    case 32:
      for (i = 0; i < n; ++i)
      {
        npio_swap_bytes_(p, p + 3);
        npio_swap_bytes_(p + 1, p + 2);
        p += 4;
      }
      return 0;

    case 64:
      for (i = 0; i < n; ++i)
      {
        npio_swap_bytes_(p, p + 7);
        npio_swap_bytes_(p + 1, p + 6);
        npio_swap_bytes_(p + 2, p + 5);
        npio_swap_bytes_(p + 3, p + 4);
        p += 8;
      }
      return 0;

    default:
      return ENOTSUP;
  }
}


/*
Load the array data, having previously read a header via npio_load_header.

If swap_bytes is true, the loaded data is converted to host endian.

*/

static inline int npio_load_data2(npio_Array* array, int swap_bytes)
{
  /* These macros work on both GCC and CLANG without an additional include.
     Right now we do not support any other endianness than big and little.
     Numpy also only supports these two ('<' and '>'). */
  static const int little_endian = (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
  size_t data_offset;
  size_t sz;
  ssize_t nr;

  /* Check that the header_len matches the alignment requirements
     of the format */
  data_offset = array->header_len + 6 + (array->major_version == 1 ? 4 : 6);
  if (data_offset % 16)
    return EINVAL;

  if (array->_buf)
  {
    /* Check that the indicated data is within the mapped bounds. */
    /* We are also checking here that there is no trailing data. */
    if (data_offset + npio_array_memsize(array) != array->_buf_size)
      return EINVAL;

    /* Set the data pointer to the start of data */
    array->data = (char*) array->_buf + data_offset;
  }
  else
  {
    /* we must allocate memory and read in the data */
    sz = array->size * array->bit_width / 8;
    if ((ssize_t) sz < 0)
      return ERANGE;
    array->data = malloc(sz);
    if (!array->data)
      return ENOMEM;
    nr = read(array->_fd, array->data, sz);
    if (nr < 0)
      return errno;
    if (nr != (ssize_t) sz)
      return EINVAL;
  }

  /* Swap bytes if necessary */
  if (swap_bytes && little_endian != array->little_endian)
  {
    array->little_endian = little_endian;
    return npio_swap_bytes(array->size, array->bit_width, array->data);
  }

  return 0;
}


/* Same as above, but always swaps the byte order to match host. */
static inline int npio_load_data(npio_Array* array)
{
  return npio_load_data2(array, 1);
}


/*
Load a numpy file.

Arguments:
  fd: file descriptor of a file in numpy format.
  array: pointer to an Array struct that will be populated on success.

Return:
  0 on success, error code otherwise.
*/
static inline int npio_load_fd3(int fd, npio_Array* array, size_t max_dim)
{
  int err;

  /* First load the header. */
  if ((err = npio_load_header_fd3(fd, array, max_dim)))
    return err;

  return npio_load_data(array);
}


/* Same as above but with defaulted max_dim */
static inline int npio_load_fd(int fd, npio_Array* array)
{
  return npio_load_fd3(fd, array, NPIO_DEFAULT_MAX_DIM);
}


/*
Load a numpy file.

Arguments:
  filename: name of the file to be loaded.
  array: an Array struct that will be populated on return.  You should not
    have called npio_init_array on the array. On success, you can access
    the header information and data in array.  When done with it, you must
    call npio_free_array() on the array to cleanup.

Return:
  0 on success, error code otherwise.
*/

static inline int npio_load3(const char* filename, npio_Array* array
  , size_t max_dim)
{
  int fd, err;
  fd = open(filename, O_RDONLY);
  if (fd < 0)
    return errno;
  err = npio_load_fd3(fd, array, max_dim);
  close(fd);
  return err;
}


/* Same as above, but with a reasonable default for the max_hdr_size
safety parameter. */
static inline int npio_load(const char* filename, npio_Array* array)
{
  /* This covers all version-1 files and should not be in any danger
  of bringing down the calling code. */
  return npio_load3(filename, array, 65536);
}


/* Load an numpy array from a memory buffer.  The contents point to the
   buffer and are not copied. */
static inline int npio_load_mem4(void *p, size_t sz, npio_Array* array
  , size_t max_dim)
{
  int err;
  if ((err = npio_load_header_mem4(p, sz, array, max_dim)))
    return err;
  return npio_load_data(array);
}


/* Same as above, with a default for max_dim. */
static inline int npio_load_mem(void *p, size_t sz, npio_Array* array)
{
  return npio_load_mem4(p, sz, array, NPIO_DEFAULT_MAX_DIM);
}


/* Prepare a numpy header in the designated memory buffer. On success, zero is
returned and out is set to 1 beyond the last written byte of the header. */
static inline int npio_save_header_mem(void* p, size_t sz, const npio_Array* array
  , size_t margin, void **out)
{
  size_t i, hdr_len;
  char* hdr_buf = (char*) p;
  char* hdr_end = hdr_buf + sz;
  char* hdr = hdr_buf;

  /* This is the absolute minimum space for the header the way we write it. */
  if (sz < 64)
    return ERANGE;

  memcpy(hdr, "\x93NUMPY\x1\x0", 8);
  hdr = hdr_buf + 8 + 2; /* leave 2 bytes for header_len, to be filled later*/
  hdr += sprintf(hdr, "{\"descr\": \"%c%c%d\", "
    , array->little_endian ? '<' : '>'
    , array->floating_point ? 'f' : array->is_signed ? 'i' : 'u'
    , array->bit_width / 8);
  /* There is no way hdr can overflow at this point! */

  hdr += sprintf(hdr, "\"fortran_order\": %s, "
    , array->fortran_order ? "True" : "False");
  /* Again, no need to check for overflow here. */

  hdr += sprintf(hdr, "\"shape\": (");
  for (i = 0; i < array->dim; ++i)
  {
    hdr += snprintf(hdr, hdr_end - hdr, "%ld, ", array->shape[i]);
    if (hdr >= hdr_end - 3)
      return ERANGE;
  }
  hdr += sprintf(hdr, ")} ");  /* hence the -3 above. */

  /* insert margin (added by Jerker 2023-09-21, see explanation in npy.c:_write_npy_header() */
  while (margin-- && hdr < hdr_end)
    *hdr++ = ' ';

  /* insert pad spaces */
  while (hdr < hdr_end && ((hdr - hdr_end) % 16))
    *hdr++ = ' ';

  /* check that we still have space */
  if ((hdr - hdr_end) % 16)
    return ERANGE;

  /* terminate with a \n.  The npy specification is vague on this. One
  interpretation is that the \n can occur first and then be followed by
  spaces, but that causes "IndentationError: unexpected indent" from the
  python loader. */
  hdr[-1] = '\n';

  /* Fill in the header_len field */
  hdr_len = hdr - hdr_buf - 10;
  hdr_buf[8] = hdr_len & 0xff;
  hdr_buf[9] = hdr_len >> 8;

  *out = hdr;
  return 0;
}


/*
Save a numpy file.

Arguments:
  fd: file descriptor of file to be saved to.
  array: array to be saved.

Return:
  0 on success.
  ERANGE: the array has too many dimensions.
  Other IO error from the OS.
*/
static inline int npio_save_fd(int fd, const npio_Array* array)
{
  /*
  We save in version 1 for now, so no need for dynamic allocation.
  hdr_buf should be no smaller than 128 and should be divisible by 16.
  */
  char hdr_buf[65536];
  void *end;
  char* hdr;
  int err;
  ssize_t nw;
  size_t sz;

  if ((err = npio_save_header_mem(hdr_buf, sizeof(hdr_buf), array, 0, &end)))
    return err;

  hdr = (char*) end;
  nw = write(fd, hdr_buf, hdr - hdr_buf);
  if (nw < hdr - hdr_buf)
    return errno;

  /* Ok, now write out the data */
  sz = npio_array_memsize(array);
  if ((ssize_t) sz < 0)
    return ERANGE;  /* We can break it up into multiple writes,
                       but this is pretty damn large and will surely
                       exceed filesystem limits! */
  nw = write(fd, array->data, sz);
  if (nw != (ssize_t) sz)
    return errno;

  /* all done */
  return 0;
}


/*
Save a numpy file.

Arguments:
  filename: name of the file to be saved to.
  array: the array to be saved.

Return:
  0 on success, error code otherwise.
*/
static inline int npio_save(const char* filename, const npio_Array* array)
{
  int fd, err;
  fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0)
    return errno;
  err = npio_save_fd(fd, array);
  close(fd);
  return err;
}


#ifdef __cplusplus

// Convenience wrappers for C++

// Enable additional convenience functions for C++11
#define NPIO_CXX11 __cplusplus >= 201103L

// You must define this macro if you want the C++ API to use exceptions instead
// of return values.
#ifdef NPIO_CXX_ENABLE_EXCEPTIONS
  #include <typeinfo>
  #include <system_error>
#endif

#if NPIO_CXX11
  #include <initializer_list>
#endif


namespace npio
{


// Not relying on C++11 type_traits for compatibilty with legacy code-bases.


//For integral types.
template <class T>
struct Traits
{
  static const bool is_signed = T(-1) < T(0);
  static const bool floating_point = false;
  static const size_t bit_width = sizeof(T) * 8;
  static const char spec = is_signed ? 'i' : 'u';
};


template <>
struct Traits<float>
{
  static const bool is_signed = true;
  static const bool floating_point = true;
  static const size_t bit_width = 32;
  static const char spec = 'f';
};


template <>
struct Traits<double>
{
  static const bool is_signed = true;
  static const bool floating_point = true;
  static const size_t bit_width = 64;
  static const char spec = 'f';
};


// Save the array specicied by nDim, shape and data to a file descriptor
// opened for writing.
template <class T>
int save(int fd, size_t nDim, const size_t *shape, const T* data)
{
  npio_Array array;
  npio_init_array(&array);
  array.dim = nDim;
  array.shape = (size_t*) shape;
  array.floating_point = Traits<T>::floating_point;
  array.is_signed = Traits<T>::is_signed;
  array.bit_width = Traits<T>::bit_width;
  array.data = (char*) data;

  return npio_save_fd(fd, &array);
}


#if NPIO_CXX11
// Same as above, but with initializer_list for convenience
template <class T>
int save(int fd, std::initializer_list<size_t> shape, const T* data)
{
  return save(fd, shape.size(), shape.begin(), data);
}
#endif


// Save the array specified by nDim, shape and data to the specified file.
template <class T>
int save(const char* fn, size_t nDim, const size_t *shape, const T* data)
{
  int fd = open(fn, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0)
    return errno;
  int ret = save(fd, nDim, shape, data);
  close(fd);
  return ret;
}


#if NPIO_CXX11
// Same as above, but with initializer_list
template <class T>
int save(const char* fn, std::initializer_list<size_t> shape, const T* data)
{
  return save(fn, shape.size(), shape.begin(), data);
}
#endif


// Simple untyped class wrapper for npio_load*
class Array
{
  private:
    npio_Array array;

    #ifndef NPIO_CXX_ENABLE_EXCEPTIONS
      int err;
    #endif


  public:
    Array(const char* filename, size_t max_dim = NPIO_DEFAULT_MAX_DIM)
    {
      npio_init_array(&array);
      #ifdef NPIO_CXX_ENABLE_EXCEPTIONS
        if (int err = npio_load3(filename, &array, max_dim))
          throw std::system_error(err, std::system_category());
      #else
        err = npio_load3(filename, &array, max_dim);
      #endif
    }


    Array(int fd, size_t max_dim = NPIO_DEFAULT_MAX_DIM)
    {
      npio_init_array(&array);
      #ifdef NPIO_CXX_ENABLE_EXCEPTIONS
        if (int err = npio_load_fd3(fd, &array, max_dim))
          throw std::system_error(err, std::system_category());
      #else
        err = npio_load_fd3(fd, &array, max_dim);
      #endif
    }


    Array(void *p, size_t sz, size_t max_dim = NPIO_DEFAULT_MAX_DIM)
    {
      npio_init_array(&array);
      #ifdef NPIO_CXX_ENABLE_EXCEPTIONS
        if (int err = npio_load_mem4(p, sz, &array, max_dim))
          throw std::system_error(err, std::system_category());
      #else
        err = npio_load_mem4(p, sz, &array, max_dim);
      #endif
    }


    // Read-only accessors

    #ifndef NPIO_CXX_ENABLE_EXCEPTIONS
      // Get any error that occurred during construction.  You must check this
      // if you are not using exceptions.
      int error() const { return err; }
    #endif

    // Get the total number of elements
    size_t size() const { return array.size; }

    // Get the dimensionality of the array
    size_t dim() const { return array.dim; }

    // Whether the array is in fortran order
    bool fortran_order() const { return array.fortran_order; }

    // Whether the array is in little endian order
    bool little_endian() const { return array.little_endian; }

    // Whether the data type is a float type.
    bool floating_point() const { return array.floating_point; }

    // Whether the data is signed.
    bool is_signed() const { return array.is_signed; }

    // Number of bits per element.
    size_t bit_width() const { return array.bit_width; }

    // The size along each dimension.
    const size_t* shape() const { return array.shape; }

    // The raw data pointer.
    const void* data() const { return array.data; }

    // The major and minor version of the loaded file's format.
    char major_version() const { return array.major_version; }
    char minor_version() const { return array.minor_version; }


    // Some convenience functions


    // Get the size along ith dimension.  Implicitly all dimensions are 1
    // beyond the dimensionality of the array.
    size_t shape(size_t i)
    {
      if (i < array.dim)
        return array.shape[i];
      else
        return 1;
    }


    // Returns whether the underlying data is of the specified type T.
    template <class T>
    bool isType() const
    {
      return Traits<T>::floating_point == array.floating_point
        && Traits<T>::is_signed == array.is_signed
        && Traits<T>::bit_width == array.bit_width;
    }


    // Get a typed pointer to the data.  If the type does not match the
    // underlying data, throws a bad_cast if exceptions are enabled.
    template <class T>
    T* get() const
    {
      if (!isType<T>())
      {
        #ifdef NPIO_CXX_ENABLE_EXCEPTIONS
          throw std::bad_cast();
        #else
          return 0;
        #endif
      }
      return (T*) array.data;
    }


    #if NPIO_CXX11
      template <class T>
      class ValueRange
      {
        T* _begin;
        T* _end;

        ValueRange(T* begin, T* end)
          : _begin(begin)
          , _end(end)
        {}

        friend class Array;

        public:
          ~ValueRange() = default;
          T* begin() const { return _begin; }
          T* end() const { return _end; }
      };

      // For C++11 range-based for loops
      template <class T>
      ValueRange<T> values() const
      {
        if (isType<T>())
          return ValueRange<T>((T*) array.data, (T*) array.data + array.size);
        else
        {
          #ifdef NPIO_CXX_ENABLE_EXCEPTIONS
            throw std::bad_cast();
          #else
            return ValueRange<T>(0, 0);
          #endif
        }
      }

    #endif


    // Save the array back to file
    int save(const char* filename)
    {
      return npio_save(filename, &array);
    }


    // Save the array back to fd
    int save(int fd)
    {
      return npio_save_fd(fd, &array);
    }


    ~Array()
    {
      npio_free_array(&array);
    }
};



}  // namespace npio
#endif





#endif

/******** npio.h end **********/

#ifndef NPY_EXPORT
#define NPY_EXPORT static 
#endif

typedef struct {
	file_format_t format;
	npio_Array array;
	int fd;
	int row_count;
	int data_column_count;
	int time_column_count;
	bool timestamps;
	bool duration;
	convert_read_fn* convert_read;
	convert_write_fn* convert_write;
	float* tmp_row;
} npy_t;

NPY_EXPORT npy_t* npy_open_read(
	char* path,
	int data_column_count,
	bool timestamps,
	bool duration,
	convert_read_fn* convert);

NPY_EXPORT npy_t* npy_open_write(
	char* path,
	int data_column_count,
	bool timestamps,
	bool duration,
	int npy_shape_count,
	size_t* npy_shape,
	convert_write_fn* convert);


NPY_EXPORT void npy_close(npy_t* handle);

NPY_EXPORT bool npy_can_read(npy_t* handle);

NPY_EXPORT int npy_read_data(npy_t* npy, float* time, float* duration, void* target);

NPY_EXPORT void npy_write_data(npy_t* npy, float time, float duration, void* source);

#ifndef WAV_EXPORT
#define WAV_EXPORT static
#endif

typedef struct __attribute__((packed))
{
	uint32_t id;
	uint32_t size;
	uint32_t format;
} wave_riff_t;

typedef struct __attribute__((packed))
{
	uint32_t id;
	uint32_t size;
	uint16_t format;
	uint16_t channels;
	uint32_t frequency;
	uint32_t byterate;
	uint16_t align;
	uint16_t bps;
} wave_fmt_t;

typedef struct __attribute__((packed))
{
	uint32_t id;
	uint32_t size;
} wave_data_t;

typedef struct
{
	file_format_t format;
	FILE* fd;
	wave_riff_t header;
	wave_fmt_t fmt;
	wave_data_t data;
	double time;
	int data_column_count;
	convert_read_fn* convert_read;
} wav_t;

WAV_EXPORT wav_t* wav_open_read(char* path, int data_column_count, convert_read_fn* convert);

WAV_EXPORT void wav_close(wav_t* wav);

WAV_EXPORT bool wav_can_read(wav_t* wav);

WAV_EXPORT int wav_read_data(wav_t* wav, float* time, float* duration, void* target);

IO_EXPORT io_t* io_open_read(
	file_format_t format,
	char* path,
	int data_column_count,
	bool read_header,
	bool timestamps,
	bool duration,
	convert_read_fn* convert)
{
	switch (format)
	{
	case FORMAT_CSV:	
		return (io_t*)csv_open_read(
			path,
			data_column_count,
			read_header,
			timestamps,
			duration,
			convert);
	case FORMAT_NPY:
		/*return (io_t*)npy_open_read( // Not implemented, work in progress
			path,
			data_column_count,
			timestamps,
			duration,
			convert);*/
	case FORMAT_WAV:
		return (io_t*)wav_open_read(
			path,
			data_column_count,
			convert);
	default:
		fprintf(stderr, "io_open_read: Unsupported format\n");
		exit(1);
		break;
	}
}

IO_EXPORT io_t* io_open_write(
	file_format_t format,
	char* path,
	int data_column_count,
	bool write_header,
	bool timestamps,
	bool duration,
	int column_names_count,
	char** column_names,
	int npy_shape_count,
	size_t* npy_shape,
	convert_write_fn* convert)
{
	switch (format)
	{
	case FORMAT_CSV:
		return (io_t*)csv_open_write(
			path, 
			data_column_count, 
			write_header,
			timestamps,
			duration, 
			column_names_count,
			column_names,
			convert);
	case FORMAT_NPY:
		return (io_t*)npy_open_write(
			path,
			data_column_count,
			timestamps,
			duration,
			npy_shape_count,
			npy_shape,
			convert);
	case FORMAT_WAV:
	default:
		fprintf(stderr, "io_open_write: Unsupported format\n");
		exit(1);
		break;
	}
}

IO_EXPORT bool io_can_read(io_t* io) 
{
	switch (io->format)
	{
	case FORMAT_CSV:
		return csv_can_read((csv_t *)io);
	case FORMAT_NPY:
		return npy_can_read((npy_t*)io);
	case FORMAT_WAV:
		return wav_can_read((wav_t*)io);
	default:
		fprintf(stderr, "io_can_read: Unsupported format\n");
		exit(1);
		break;
	}
}

IO_EXPORT int io_read_data(io_t* io, float* time, float* duration, void* target)
{
	if (io == NULL)
		return 0;

	switch (io->format)
	{
	case FORMAT_CSV:
		return csv_read_data((csv_t*)io, time, duration, target);
	case FORMAT_NPY:
		return npy_read_data((npy_t*)io, time, duration, target);
	case FORMAT_WAV:
		return wav_read_data((wav_t*)io, time, duration, target);
	default:
		fprintf(stderr, "io_read_data: Unsupported format\n");
		exit(1);
		break;
	}
}

IO_EXPORT void io_write_data(io_t* io, float time, float duration, void* source)
{
	if (io == NULL)
		return;

	switch (io->format)
	{
	case FORMAT_CSV:
		csv_write_data((csv_t*)io, time, duration, source);
		break;
	case FORMAT_NPY:
		npy_write_data((npy_t*)io, time, duration, source);
		break;
	case FORMAT_WAV:
		//wav_write_data((wav_t*)io, time, duration, source);
		//break;
	default:
		fprintf(stderr, "io_write_data: Unsupported format\n");
		exit(1);
		break;
	}
}

IO_EXPORT void io_close(io_t* io) 
{
	if (io == NULL)
		return;

	switch (io->format)
	{
	case FORMAT_CSV:
		csv_close((csv_t*)io);
		break;
	case FORMAT_NPY:
		npy_close((npy_t*)io);
		break;
	case FORMAT_WAV:
		wav_close((wav_t*)io);
		break;
	default:
		fprintf(stderr, "io_close: Unsupported format\n");
		exit(1);
		break;
	}
}

static void _write_npy_header(npy_t* npy);

NPY_EXPORT npy_t* npy_open_read(
	char* path,
	int data_column_count,
	bool timestamps,
	bool duration,
	convert_read_fn* convert)
{
	if (path == NULL)
		return NULL;

	npy_t* npy = malloc(sizeof(npy_t));
	if (npy == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}

	npy->format = FORMAT_NPY;
	npy->timestamps = timestamps;
	npy->duration = duration;
	npy->row_count = 0;
	npy->data_column_count = data_column_count;
	npy->time_column_count = 0;
	if (timestamps)
		npy->time_column_count++;
	if (duration)
		npy->time_column_count++;
	npy->convert_read = convert;
	npy->tmp_row = NULL;
	
	// Work in progress...
	fprintf(stderr, "npy_open_read: Not implemented.\n");
	exit(1);

	return npy;
}

NPY_EXPORT npy_t* npy_open_write(
	char* path, 
	int data_column_count,
	bool timestamps,
	bool duration,
	int npy_shape_count,
	size_t* npy_shape,
	convert_write_fn* convert)
{
	if (path == NULL)
		return NULL;

	npy_t* npy = malloc(sizeof(npy_t));
	if (npy == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}

	npy->format = FORMAT_NPY;
	npy->row_count = 0;
	npy->data_column_count = data_column_count;
	npy->timestamps = timestamps;
	npy->duration = duration;
	npy->time_column_count = 0;
	if (timestamps)
		npy->time_column_count++;
	if (duration)
		npy->time_column_count++;
	npy->convert_write = convert;

	npy->tmp_row = malloc(sizeof(float) * data_column_count);

	npy->fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (npy->fd < 0) {
		fprintf(stderr, "Error opening file (%s) for writing: %s\n", path, strerror(errno));
		exit(1);
	}

	npio_init_array(&npy->array);

	// If no shape was given in the args, set it to [0,total column count]
	if (npy_shape_count == 0 || npy_shape == NULL)
	{
		npy_shape_count = 2;
		npy_shape = malloc(sizeof(size_t) * 2);
		npy_shape[0] = 0;
		npy_shape[1] = npy->data_column_count + npy->time_column_count;
	}
	
	npy->array.dim = npy_shape_count;
	npy->array.shape = npy_shape;
	npy->array.floating_point = true;
	npy->array.is_signed = true;
	npy->array.bit_width = 32;

	_write_npy_header(npy);
	
	return npy;
}


static void _write_npy_header(npy_t* npy) {
	// We save in version 1 for now, so no need for dynamic allocation.
	// hdr_buf should be no smaller than 128 and should be divisible by 16.
	char hdr_buf[65536];
	void* end;
	int err;

	npy->array.shape[0] = (size_t)npy->row_count;

	// Compute header size margin to allow for future header writes without chaning the total
	// header size
	// A bugfix hack added by Jerker 2023-09-21. We write the header twice; once in the beginning
	// of the file write, but also in the end, once we know the number of rows (see npy_close()
	// below). However, the header size, which depends on the row count because it's written as
	// text, must not change, because then the first row of data would be overwritten. To ensure
	// consistent header size, we add a margin to ensure that the row count with the margin takes
	// up a total of 8 characters. This works for up to 99,999,999 rows.
	size_t row_count_margin = 7;
	size_t power10 = 10;
	while (row_count_margin && npy->row_count >= power10)
	{
		power10 *= 10;
		row_count_margin--;
	}

	if ((err = npio_save_header_mem(hdr_buf, sizeof(hdr_buf), &npy->array, row_count_margin, &end)))
	{
		fprintf(stderr, "Error npio_save_header_mem() %i\n", err);
		exit(1);
	}

	char*  hdr = (char*)end;
	ssize_t nw = write(npy->fd, hdr_buf, hdr - hdr_buf);
	if (nw < hdr - hdr_buf)
	{
		fprintf(stderr, "Error write() %i\n", err);
		exit(1);
	}
}


NPY_EXPORT void npy_close(npy_t* npy)
{
	if (npy == NULL)
		return;

	//flush(npy->fd);
	lseek(npy->fd, 0, SEEK_SET);
	
	_write_npy_header(npy);

	if (npy->fd >= 0)
		close(npy->fd);

	if (npy->tmp_row != NULL) 
		free(npy->tmp_row);

	// Note: Don't free npy->array.shape; it's a pointer to the shape array passed in to npy_open_write().

	free(npy);
}

NPY_EXPORT bool npy_can_read(npy_t* npy)
{
	// return !feof(npy->fd);
	return false;
}

NPY_EXPORT int npy_read_data(npy_t* npy, float* time, float* duration, void* target) 
{
	return 0;
}

NPY_EXPORT void npy_write_data(npy_t* npy, float time, float duration, void* source)
{
	if (npy == NULL)
		return;

	if (npy->time_column_count > 0) {
		float time_buf[2];
		time_buf[0] = time;
		time_buf[1] = duration;
		write(npy->fd, time_buf, npy->time_column_count * sizeof(float));
	}

	if (npy->convert_write == NULL) {
		write(npy->fd, (float *)source, npy->data_column_count * sizeof(float));
	}
	else 
	{		
		for (int i = 0; i < npy->data_column_count; i++) {
			npy->tmp_row[i] = npy->convert_write(source, i);
		}
		write(npy->fd, npy->tmp_row, npy->data_column_count * sizeof(float));
	}
	
	npy->row_count++;
}

#ifndef QBOUNDS_EXPORT
#define QBOUNDS_EXPORT static
#endif

typedef struct
{
    float min;
    float max;
} qbounds_t;

void qbounds_f32(const float* restrict src, int count, int index);
QBOUNDS_EXPORT void reset_qbounds(void);
QBOUNDS_EXPORT int save_qbounds_file(char* file_path);

static qbounds_t _qbounds[API_QBOUNDS_MAX + 1];

void qbounds_f32(const float* restrict src, int count, int index)
{
    qbounds_t* current = _qbounds + index;

    float min = current->min;
    float max = current->max;
    for (int i = 0; i < count; i++)
    {
        float value = src[i];
        if (value > max)
            max = value;
        if (value < min)
            min = value;
    }

    current->max = max;
    current->min = min;
}

QBOUNDS_EXPORT void reset_qbounds(void)
{
    for (int i = 0; i < API_QBOUNDS_MAX; i++)
    {
        _qbounds[i].max = FLT_MIN;
        _qbounds[i].min = FLT_MAX;
    }
}

QBOUNDS_EXPORT int save_qbounds_file(char* file_path)
{
    if (file_path == NULL)
        return 0;

    fprintf(stdout, "Saving file %s\n", file_path);

    FILE* output_file = fopen(file_path, "w");
    int errnum = errno;
    if (output_file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", strerror(errnum));
        return 1;
    }

    fprintf(output_file, "# name, data_min, data_max\n");
    for (int i = 0; i < API_QBOUNDS_MAX; i++)
    {
        qbounds_t param = _qbounds[i];
        if (param.min > param.max)
            continue;

        fprintf(output_file, "_K%i, %.20e, %.20e\n", i, param.min, param.max);
    }
    fflush(output_file);
    fclose(output_file);
    return 0;
}

static qerror_t _qerror[API_QERROR_MAX + 1];

QERROR_EXPORT void qerror_f32q16(const float* restrict values, int count, int index, double scale, double offset, const int16_t* restrict quantized)
{
	qerror_t* current = _qerror + index;

	current->count++;
	double min = current->min;
	double max = current->max;
	for (int i = 0; i < count; i++)
	{
		double value = values[i];
		double dequantized = (quantized[i] - offset) * scale;

		double error = fabs(value - dequantized);

		if (error > current->error)
			current->error = error;

		if (value > max)
			max = value;
		if (value < min)
			min = value;
	}

	if (current->count == 1)
		current->first_error = current->error;

	current->max = max;
	current->min = min;
}

QERROR_EXPORT int save_qerror_file(char* file_path)
{
	if (file_path == NULL)
		return 0;

	fprintf(stdout, "Saving file %s\n", file_path);

	FILE* output_file = fopen(file_path, "w");
	int errnum = errno;
	if (output_file == NULL) {
		fprintf(stderr, "Error opening file for writing: %s\n", strerror(errnum));
		return 1;
	}

	fprintf(output_file, "# name, data_min, data_max, abs_error, first_error, count\n");
	for (int i = 0; i < API_QERROR_MAX; i++)
	{
		qerror_t param = _qerror[i];
		if (param.count == 0)
			continue;

		fprintf(output_file, "_K%i, %.20e, %.20e, %.20e, %.20e, %li\n", i, param.min, param.max, param.error, param.first_error, param.count);
	}
	fflush(output_file);
	fclose(output_file);
	return 0;
}

STATS_EXPORT void merge_stats(stats_t* source, stats_t* target)
{
    target->argmax_error_count += source->argmax_error_count;
    target->row_count += source->row_count;
    target->abs_error_sum += source->abs_error_sum;
    target->feature_count += source->feature_count;

    if (source->max_abs_error > target->max_abs_error)
        target->max_abs_error = source->max_abs_error;

    if (source->max_rel_error > target->max_rel_error)
        target->max_rel_error = source->max_rel_error;

    if (source->max_time_error > target->max_time_error)
        target->max_time_error = source->max_time_error;
}

STATS_EXPORT bool print_and_check_stats(stats_t* stats, args_t* args, const char* passed_prefix, const char* failed_prefix)
{
    bool passed = true;

    // Argmax test
    if (!isnan(args->test_argmax)) {
        double argmax_err = stats->argmax_error_count / (double)stats->row_count;
        if (argmax_err > args->test_argmax) {
            fprintf(stderr, "%sArgmax test failed on %i of total %i rows (%g > %g).\n",
                failed_prefix, stats->argmax_error_count, stats->row_count, argmax_err, args->test_argmax);
            passed = false;
        }
        else {
            fprintf(stdout, "%sArgmax (%i/%i) %g <= %g\n", passed_prefix, stats->argmax_error_count, stats->row_count, argmax_err, args->test_argmax);
        }
    }

    // Max Abs test
    if (!isnan(args->test_abserr)) {
        if (stats->max_abs_error > args->test_abserr) {
            fprintf(stderr, "%sMax absolute error test failed %g > %g.\n", failed_prefix, stats->max_abs_error, args->test_abserr);
            passed = false;
        }
        else {
            fprintf(stdout, "%sMax Abs error %g <= %g\n", passed_prefix, stats->max_abs_error, args->test_abserr);
        }
    }

    // Mean err
    if (!isnan(args->test_meanerr)) {
        double mean_error = stats->abs_error_sum / (double)stats->feature_count;
        if (mean_error > args->test_meanerr) {
            fprintf(stderr, "%sMax mean error test failed %g > %g.\n", failed_prefix, mean_error, args->test_meanerr);
            passed = false;
        }
        else {
            fprintf(stdout, "%sMax mean error %g <= %g\n", passed_prefix, mean_error, args->test_meanerr);
        }
    }

    // Relative error
    if (!isnan(args->test_relerr)) {
        if (stats->max_rel_error > args->test_relerr) {
            fprintf(stderr, "%sMax relative error test failed %g > %g.\n", failed_prefix, stats->max_rel_error, args->test_relerr);
            passed = false;
        }
        else {
            fprintf(stdout, "%sMax relative error %g <= %g\n", passed_prefix, stats->max_rel_error, args->test_relerr);
        }
    }

    // Timestamp
    if (!isnan(args->test_timestamp)) {
        if (stats->max_time_error > args->test_timestamp) {
            fprintf(stderr, "%sMax timestamp test failed %g > %g.\n", failed_prefix, stats->max_time_error, args->test_timestamp);
            passed = false;
        }
        else {
            fprintf(stdout, "%sTimestamp error %g <= %g", passed_prefix, stats->max_time_error, args->test_timestamp);
        }
    }

    return passed;
}

STATS_EXPORT void print_top_errors(global_stats_t* glob)
{
    if (glob->top_errors[0].row == 0)
        return;

    const char* table = "%-13s | %-7s | %-8s | %-11s | %-11s | %s\n";
    fprintf(stdout, table, "Top Abs Error", "Row", "Feature", "Actual", "Expected", "File");
    char abs_err[50], row[50], feature[50], actual[50], expected[50], file[255];
    for (int i = 0; i < TOP_ERROR_COUNT; i++)
    {
        top_error_t err = glob->top_errors[i];

        if (err.row == 0)
            return;

        snprintf(abs_err, sizeof(abs_err), "%f", err.abs_error);
        snprintf(row, sizeof(row), "%i", err.row);
        snprintf(feature, sizeof(feature), "%i", err.feature);
        snprintf(actual, sizeof(actual), "%f", err.actual);
        snprintf(expected, sizeof(expected), "%f", err.expected);
        /*snprintf(file, sizeof(file), "#%i", err.task->index + 1);*/

        fprintf(stdout, table, abs_err, row, feature, actual, expected, file);
    }
}


STATS_EXPORT void add_top_error(global_stats_t* glob, int row, int feature, double abs_error, double rel_error, double expected, double actual)
{
    for (int i = 0; i < TOP_ERROR_COUNT; i++)
    {
        if (glob->top_errors[i].row != 0) {
            if (glob->top_errors[i].abs_error < abs_error)
                memmove(&glob->top_errors[i + 1], &glob->top_errors[i], sizeof(top_error_t) * (TOP_ERROR_COUNT - i - 1));
            else
                continue;
        }

        if (glob->top_errors[i].row == 0 || glob->top_errors[i].abs_error < abs_error)
        {
            glob->top_errors[i].row = row;
            glob->top_errors[i].feature = feature;
            glob->top_errors[i].expected = expected;
            glob->top_errors[i].actual = actual;
            glob->top_errors[i].abs_error = abs_error;
            glob->top_errors[i].rel_error = rel_error;
            return;
        }
    }
}

UTILS_EXPORT void trim_white_space(char** str)
{
    while (**str == ' ' || **str == '\t' || **str == '\r' || **str == '\n') (*str)++;
    for (char* i = *str + strlen(*str) - 1; *i == '\n' || *i == '\r' || *i == ' ' || *i == '\t'; i--) *i = '\0';
}


UTILS_EXPORT float min_f32(float* data, int count)
{
    float value = data[0];
    for (int i = 1; i < count; i++)
    {
        if (data[i] < value)
            value = data[i];
    }

    return value;
}

UTILS_EXPORT float max_f32(float* data, int count)
{
    float value = data[0];
    for (int i = 1; i < count; i++)
    {
        if (data[i] > value)
            value = data[i];
    }

    return value;
}

UTILS_EXPORT int argmax_f64(double* values, int count)
{
    int index = 0;
    double max = values[0];
    for (int i = 1; i < count; i++)
    {
        if (values[i] > max)
        {
            index = i;
            max = values[i];
        }
    }
    return index;
}

UTILS_EXPORT int argmax_dout(dout_t* values, int count)
{
    int index = 0;
    dout_t max = values[0];
    for (int i = 1; i < count; i++)
    {
        if (values[i] > max)
        {
            index = i;
            max = values[i];
        }
    }
    return index;
}

UTILS_EXPORT int ensure_dir_path(char* path)
{
    char subpath[PATH_MAX];
    char tmppath[PATH_MAX];
    char* start = path;
    char* token = strchr(start, '/');
    while (token != NULL)
    {
        int len = token - path;
        memcpy(subpath, path, len);
        subpath[len] = '\0';

        if (strncmp(start, ".", token - start) != 0 || strncmp(start, "..", token - start) != 0)
        {
            char* abspath = realpath(subpath, tmppath);
            if (abspath == NULL)
            {
                if (mkdir(subpath, 0777) != 0)
                {
                    fprintf(stderr, "Failed to create directory %s", subpath);
                    return 1;
                }
            }
        }

        start = token + 1;
        token = strchr(start, '/');
    }

    return 0;
}

WAV_EXPORT wav_t* wav_open_read(char* path, int data_column_count, convert_read_fn* convert)
{
	if (path == NULL) {
		return NULL;
	}

	wav_t* wav = malloc(sizeof(wav_t));
	if (wav == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}

	wav->format = FORMAT_WAV;
	wav->time = 0;
	wav->data_column_count = data_column_count;
	wav->convert_read = convert;

	if (path[0] == '-' && path[1] == '\0') {
		wav->fd = stdin;
	}
	else {
		wav->fd = fopen(path, "r");
		if (wav->fd == NULL) {
			fprintf(stderr, "Error opening file (%s) for reading: %s\n", path, strerror(errno));
			exit(1);
		}
	}	

	if (fread((char*)(&wav->header), sizeof(wave_riff_t), 1, wav->fd) != 1) {
		fprintf(stderr, "Wave RIFF read error.\n");
		exit(1);
	}

	if (wav->header.id != 0x46464952) { // RIFF
		fprintf(stderr, "Wave RIFF header error. 0x%08x\n", wav->header.id);
		exit(1);
	}

	if (wav->header.format != 0x45564157) {	// WAVE
		fprintf(stderr, "Wave RIFF header error. Unsupported format.\n");
		exit(1);
	}

	while (true)
	{
		if (fread((char*)(&wav->fmt), 8, 1, wav->fd) != 1) {
			fprintf(stderr, "Wave format chunk scan error (fmt).\n");
			exit(1);
		}

		if (wav->fmt.id == 0x20746D66) { // fmt
			if (fread((char*)(&wav->fmt) + 8, sizeof(wave_fmt_t) - 8, 1, wav->fd) != 1) {
				fprintf(stderr, "Wave format chunk read error (fmt).\n");
				exit(1);
			}
			if (sizeof(wave_fmt_t) - 8 != wav->fmt.size) {
				char discard[20];
				
				if (fread(discard, wav->fmt.size - (sizeof(wave_fmt_t) - 8), 1, wav->fd) != 1) {
					fprintf(stderr, "Wave format chunk read error (fmt).\n");
					exit(1);
				}

			}
			break;
		}
		else
		{
			/*fprintf(stderr, "skip> %x (%i)\n", wav->fmt.id, wav->fmt.size);*/
			if (fseek(wav->fd, wav->fmt.size, SEEK_CUR) != 0) {
				fprintf(stderr, "Wave format chunk scan-skip error (fmt).\n");
				exit(1);
			}
		}
	}

	if (wav->fmt.format != 1 && wav->fmt.format != 3) {
		fprintf(stderr, "Unsupported Wave file. Only PCM and IeeeFloat is supported.\n");
		exit(1);
	}

	if (wav->fmt.channels == 0) {
		fprintf(stderr, "Unsupported Wave file. No channels found.\n");
		exit(1);
	}

	if (wav->fmt.format == 1 && wav->fmt.bps != 16 && wav->fmt.bps != 8) {
		fprintf(stderr, "Unsupported Wave file. Only 8 or 16 bit PCM is supported.\n");
		exit(1);
	}
	else if (wav->fmt.format == 3 && wav->fmt.bps != 32) {
		fprintf(stderr, "Unsupported Wave file. Only 32 bit float is supported.\n");
		exit(1);
	}
	
	while (true)
	{
		if (fread((char*)(&wav->data), 8, 1, wav->fd) != 1) {
			fprintf(stderr, "Wave data chunk scan error (data).\n");
			exit(1);
		}
		
		if (wav->data.id == 0x61746164) { // data
			break;
		}
		else
		{
			if (fseek(wav->fd, wav->data.size, SEEK_CUR) != 0) {
				fprintf(stderr, "Wave format chunk scan-skip error (data).\n");
				exit(1);
			}
		}
	}
	
    return wav;
}

WAV_EXPORT void wav_close(wav_t* wav)
{	
	if (wav == NULL) {
		return;
	}

	if(wav->fd != NULL && wav->fd != stdin && wav->fd != stdout && wav->fd != stderr)
		fclose(wav->fd);

	free(wav);
}

WAV_EXPORT bool wav_can_read(wav_t* wav)
{
	return !feof(wav->fd);
}

// return 0 success
WAV_EXPORT int wav_read_data(wav_t* wav, float* time, float* duration, void* target)
{
	int data_size = wav->data_column_count;

	if (data_size != wav->fmt.channels) {
		fprintf(stderr, "WAVE Read error. File has %i channels, but expected input is %i channels\n", wav->fmt.channels, data_size);
		return -1;
	}

	for (int i = 0; i < data_size; i++) {
		if (wav->fmt.format == 1 && wav->fmt.bps == 8)
		{
			uint8_t value;
			if (fread(&value, sizeof(uint8_t), 1, wav->fd) != 1) {
				if (i == 0 && feof(wav->fd)) {
					return 1;	// EOF
				}
				else {
					fprintf(stderr, "WAVE Read error\n");
					return -1;
				}
			}
			wav->convert_read(target, i, ((float)value - 128) / 128.0);
		}
		else if (wav->fmt.format == 1 && wav->fmt.bps == 16) {
			int16_t value;
			if (fread(&value, sizeof(int16_t), 1, wav->fd) != 1) {
				if (i == 0 && feof(wav->fd)) {
					return 1;	// EOF
				}
				else {
					fprintf(stderr, "WAVE Read error\n");
					return -1;
				}
			}
			wav->convert_read(target, i, value / 32768.0);
		}
		else if (wav->fmt.format == 3 && wav->fmt.bps == 32) {
			float value;
			if (fread(&value, sizeof(float), 1, wav->fd) != 1) {
				if (i == 0 && feof(wav->fd)) {
					return 1;	// EOF
				}
				else {
					fprintf(stderr, "WAVE Read error\n");
					return -1;
				}
			}
			wav->convert_read(target, i, value);
		}
		else {
			fprintf(stderr, "Unsupported format. Only 16 and 8 bit PCM and IeeeFloat are supported.");
			exit(1);
		}
	}

	if(time != NULL)
		*time = (float)wav->time;

	if(duration != NULL)
		*duration = 1 / (double)wav->fmt.frequency;

	wav->time += 1 / (double)wav->fmt.frequency;

	return 0;	// Success
}

/* VERSION: 1.5 */

static buffers_t* allocate_buffers();
static void free_buffers(buffers_t* buf);
static task_t* create_task(tasklist_t* list);
static void load_tasks(args_t* args, tasklist_t* list);
static void compare_data(task_t* task, buffers_t* buf, global_stats_t* glob, float actual_time, float expected_time);
static void run_task(args_t* args, task_t* task, buffers_t* buf, global_stats_t* glob, io_t* output_merged);

int main(int argc, char* argv[]);

static buffers_t *allocate_buffers()
{
    buffers_t* ret = (buffers_t*)calloc(1, sizeof(buffers_t));

    ret->input_data = (din_t*)calloc(API_DATA_IN_COUNT, sizeof(din_t));
    ret->output_data = (dout_t*)calloc(API_DATA_OUT_COUNT, sizeof(dout_t));
    ret->expected_data = (double*)calloc(API_DATA_OUT_COUNT, sizeof(double));

    return ret;
}

static void free_buffers(buffers_t* buf)
{
    free(buf->input_data);
    free(buf->output_data);
    free(buf->expected_data);
    free(buf);
}

static void compare_data(task_t* task, buffers_t* buf, global_stats_t* glob, float actual_time, float expected_time)
{
    int size = API_DATA_OUT_COUNT;

    task->stats.row_count++;

    if (argmax_f64(buf->expected_data, size) != argmax_dout(buf->output_data, size))
    {
        task->stats.argmax_error_count++;
    }

    const double time_error = fabs(actual_time - expected_time);
    if (time_error > task->stats.max_time_error)
        task->stats.max_time_error = time_error;

    for (int i = 0; i < size; i++)
    {
        task->stats.feature_count++;

#if API_DATA_OUT_IS_QUANTIZED
        double actual_value = API_DATA_OUT_DEQUANTIZE(buf->output_data[i]);
#else
        dout_t actual_value = buf->output_data[i];
#endif

        double abs_error = fabs(buf->expected_data[i] - actual_value);
        double abs_expected = fabs(buf->expected_data[i]);

        task->stats.abs_error_sum += abs_error;

        // Save max error
        if (abs_error > task->stats.max_abs_error) {
            task->stats.max_abs_error = abs_error;
            task->worst_row = task->stats.row_count;
            task->worst_feature = i;
            task->worst_expected = buf->expected_data[i];
            task->worst_actual = actual_value;
        }

        // Compute relative error
        double rel_err;
        if (abs_error == 0)		// 0 / 0 -> no error
            rel_err = 0;
        else if (abs_expected == 0)
            rel_err = abs_error;
        else
            rel_err = abs_error / abs_expected;

        if (rel_err > task->stats.max_rel_error)
            task->stats.max_rel_error = rel_err;

        add_top_error(glob, task->stats.row_count, i, abs_error, rel_err, (double)buf->expected_data[i], (double)actual_value);
    }
 
}

static void run_task(args_t* args, task_t* task, buffers_t* buf, global_stats_t* glob, io_t* output_merged)
{
    io_t* input_file = NULL;
    io_t* output_file = NULL;
    io_t* expected_file = NULL;
    int status = 0;
    float time_in_start;
    float time_in_duration;
    float time_exp_start;
    float time_exp_duration;

    if (task->output_path && ensure_dir_path(task->output_path)) {
        fprintf(stderr, "Failed to create directory for file %s\n", task->output_path);
        exit(1);
    }

    API_INIT();
   
    resolve_format(&args->input_format, task->input_path);
    if (args->input_format == FORMAT_AUTO) {
        fprintf(stderr, "Unknown input format. Please specify with --input-format.");
        exit(1);
    }

    // Create input file reader
    input_file = io_open_read(
        args->input_format, 
        task->input_path, 
        API_DATA_IN_COUNT, 
        args->input_file_opt & FILE_HEADER, 
        args->input_file_opt & FILE_TIMESTAMP,
        args->input_file_opt & FILE_DURATION,
        _data_read);

    // Create expected file reader
    if (task->expected_path) {
        resolve_format(&args->expected_format, task->expected_path);
        if (args->input_format == FORMAT_AUTO) {
            fprintf(stderr, "Unknown expected format. Please specify with --expected-format.");
            exit(1);
        }
        expected_file = io_open_read(
            args->expected_format,
            task->expected_path,
            API_DATA_OUT_COUNT,
            args->expected_file_opt & FILE_HEADER,
            args->expected_file_opt & FILE_TIMESTAMP,
            args->expected_file_opt & FILE_DURATION,
            _data_read_f64);
    }

    // Create output file writer
    if (task->output_path) {
        resolve_format(&args->output_format, task->output_path);
        if (args->output_format == FORMAT_AUTO) {
            fprintf(stderr, "Unknown output format. Please specify with --output-format.");
            exit(1);
        }

        if (args->write_separate_time)
        {
            output_file = io_open_write(
                FORMAT_CSV,
                task->output_path,
                0, // data_column_count
                true, // write_header
                true, // timestamp
                true, // duration
                0, // column_names_count
                NULL, // column_names
                0, // npy_shape_count
                NULL, // npy_shape
                _data_write);
        }
        else // args->batch_write
        {
            output_file = io_open_write(
                args->output_format,
                task->output_path,
                API_DATA_OUT_COUNT,
                args->output_file_opt & FILE_HEADER,
                args->output_file_opt & FILE_TIMESTAMP,
                args->output_file_opt & FILE_DURATION,
                args->output_csv_columns_count,
                args->output_csv_columns,
                args->output_npy_shape_count,
                args->output_npy_shape,
                _data_write);
        }
    }

    // Check can read input
    if (!io_can_read(input_file))
    {
        fprintf(stderr, "Unexpected input file EOF. %s", task->input_path);
        exit(1);
    }

    while (io_can_read(input_file)) {
        if (io_read_data(
            input_file,
            &time_in_start,
            &time_in_duration,
            buf->input_data))
            break;


#if defined(API_FUNCTION)
        API_COMPUTE(buf->input_data, buf->output_data);

        if (output_file != NULL)
            io_write_data(
                output_file,
                time_in_start,
                time_in_duration,
                buf->output_data);

        if (output_merged != NULL)
            io_write_data(
                output_merged,
                time_in_start,
                time_in_duration,
                buf->output_data);

        if (expected_file != NULL)
        {
            if (io_read_data(
                expected_file,
                &time_exp_start,
                &time_exp_duration,
                buf->expected_data))
                break;

            compare_data(task, buf, glob, time_in_start, time_exp_start);
        }

#elif defined(API_QUEUE_TIME)

        float time_in_buf[API_TIME_IN_COUNT];
        float time_out_buf[API_TIME_OUT_COUNT];

        if (API_TIME_IN_COUNT == 1) {
            time_in_buf[0] = time_in_start;
        }
        else if (API_TIME_IN_COUNT == 2) {
            time_in_buf[0] = time_in_start;
            time_in_buf[1] = time_in_start + time_in_duration;
        }
        else {
            fprintf(stderr, "API_TIME_IN_COUNT must be 2 or 1.\n");
            exit(1);
        }

        status = API_ENQUEUE_TIME(buf->input_data, time_in_buf);

        if (status != 0) {
            fprintf(stderr, "enqueue function returned OUT_OF_MEMORY.\n");
            exit(1);
        }

        while (true)
        {
            status = API_DEQUEUE_TIME(buf->output_data, time_out_buf);
            if (status != 0)
                break;

            float time_out_start = min_f32(time_out_buf, API_TIME_OUT_COUNT);
            float time_out_duration = max_f32(time_out_buf, API_TIME_OUT_COUNT) - time_out_start;

            if (output_file != NULL)
                io_write_data(
                    output_file,
                    time_out_start,
                    time_out_duration,
                    buf->output_data);

            if (output_merged != NULL)
                io_write_data(
                    output_merged,
                    time_out_start,
                    time_out_duration,
                    buf->output_data);

            if (expected_file != NULL)
            {
                if (io_read_data(
                    expected_file,
                    &time_exp_start,
                    &time_exp_duration,
                    buf->expected_data))
                    break;

                compare_data(task, buf, glob, time_out_start, time_exp_start);
            }
        }

#elif defined(API_QUEUE)
        status = API_ENQUEUE(buf->input_data);

        if (status != 0) {
            fprintf(stderr, "enqueue function returned OUT_OF_MEMORY.\n");
            exit(1);
        }

        while (true)
        {
            status = API_DEQUEUE(buf->output_data);

            if (status != 0)
                break;

            if (output_file != NULL)
                io_write_data(
                    output_file,
                    time_in_start,
                    time_in_duration,
                    buf->output_data);

            if (output_merged != NULL)
                io_write_data(
                    output_merged,
                    time_in_start,
                    time_in_duration,
                    buf->output_data);

            if (expected_file != NULL)
            {
                if (io_read_data(
                    expected_file,
                    &time_exp_start,
                    &time_exp_duration,
                    buf->expected_data))
                    break;

                compare_data(task, buf, glob, time_in_start, time_exp_start);
            }
        }

#endif		

    }

    if (status == -2)
    {
        fprintf(stderr, "OUT OF MEMORY. Return code %i.\n", status);
        exit(1);
    }

    if (expected_file != NULL) {
        if (task->stats.feature_count == 0) {
            fprintf(stderr, "  [FAILED] No data was compared\n");
            exit(1);
        }
	}

    merge_stats(&task->stats, &glob->stats);


    io_close(input_file);
    io_close(output_file);
    io_close(expected_file);
}

static task_t* create_task(tasklist_t* list)
{
    task_t* task = (task_t*)malloc(sizeof(task_t));

    if (task == NULL)
    {
        fprintf(stderr, "malloc failed. Unable to allocate memory.\n");
        exit(1);
    }

    memset(task, 0, sizeof(task_t));
    task->stats.max_time_error = 0;
    task->stats.max_abs_error = -DBL_MAX;
    task->stats.max_rel_error = -DBL_MAX;
    task->stats.abs_error_sum = 0;

    if(list->count >= list->allocated)
    {
        list->allocated += 1000;
        list->items = realloc(list->items, sizeof(task_t*) * list->allocated);
        if(list->items == NULL)
        {
            fprintf(stderr, "realloc() failed. Unable to allocate memory.\n");
            exit(1);
        }
    }

    task->index = list->count;
    list->items[task->index] = task;
    list->count++;

    return task;
}

static void load_tasks(args_t *args, tasklist_t* list)
{
    if(args->batch_path != NULL)
    {
        char line[PATH_MAX*2+10] = { 0 };

        if (args->verbose)
            fprintf(stdout, "Loading %s\n", args->batch_path);

        FILE* file = fopen(args->batch_path, "r");

        if (!file)
        {
            perror(args->batch_path);
            exit(1);
        }

        while (fgets(line, sizeof(line), file) != NULL)
        {
            // Split line
            char* input_f = line;
            char* second_f = NULL;
            char* end = strchr(line, ';');
            if (end != NULL) {
                *end = '\0';
                second_f = ++end;
                trim_white_space(&second_f);
            }
            trim_white_space(&input_f);

            if(strlen(input_f) == 0)
                continue;

            task_t* task = create_task(list);
            task->input_path = strdup(input_f);

            if (second_f != NULL) {
                if (args->batch_write || args->write_separate_time)
                    task->output_path = strdup(second_f);
                else
                    task->expected_path = strdup(second_f);
            }
        }

        if (args->output_path != NULL) {

            if (args->verbose)
                fprintf(stdout, "Merged output: %s\n", args->output_path);

            if (args->output_format == FORMAT_AUTO) {
                fprintf(stderr, "Unknown output format. Please specify with --output-format.");
                exit(1);
            }

            list->output_merged = io_open_write(
                args->output_format,
                args->output_path,
                API_DATA_OUT_COUNT,
                args->output_file_opt & FILE_HEADER,
                args->output_file_opt & FILE_TIMESTAMP,
                args->output_file_opt & FILE_DURATION,
                args->output_csv_columns_count,
                args->output_csv_columns,
                args->output_npy_shape_count,
                args->output_npy_shape,
                _data_write);
        }

        if (fclose(file))
        {
            perror(args->batch_path);
            exit(1);
        }
    }
    else
    {
        task_t* task = create_task(list);
        task->input_path = args->input_path;
        task->output_path = args->output_path;
        task->expected_path = args->expected_path;
    }
}

int main(int argc, char* argv[])
{
    args_t args;
    tasklist_t tasklist;
    global_stats_t global;
    buffers_t* buffers;
    int file_fail_count = 0;

    buffers = allocate_buffers();

    // Just to be sure
    memset(&args, 0, sizeof(args_t));
    memset(&tasklist, 0, sizeof(tasklist_t));
    memset(&global, 0, sizeof(global_stats_t));

    // Parse arguments
    parse_args(argc, argv, &args);

    // Load batch
    load_tasks(&args, &tasklist);

#ifdef API_QBOUNDS
    reset_qbounds();
#endif

    for (int i = 0; i < tasklist.count; i++)
    {
        task_t* task = tasklist.items[i];
        if (args.verbose)
        {
            fprintf(stdout, "Processing file #%i of %i:\n", i + 1, tasklist.count);
            fprintf(stdout, "  input   : %s\n", task->input_path);
            if (task->output_path)
                fprintf(stdout, "  output  : %s\n", task->output_path);
            else if (task->expected_path)
                fprintf(stdout, "  expected: %s\n", task->expected_path);
        }

        run_task(&args, task, buffers, &global, tasklist.output_merged);

        if (task->expected_path) {
            if (args.batch_individual_test) {
                if (!print_and_check_stats(&task->stats, &args, "  [PASSED] ", "  [FAILED] "))
                    file_fail_count++;
            }
            else if (args.verbose) {
                print_and_check_stats(&global.stats, &args, "  Aggregated ", "  [!] Aggregated ");
            }
        }
    }

    if (tasklist.output_merged) {
        io_close(tasklist.output_merged);
    }

    if (global.stats.row_count > 0) {
        fprintf(stdout, "Done! Total of %i features in %i predictions in %i file(s)\n",
            global.stats.feature_count, global.stats.row_count, tasklist.count);
    }
    else {
        fprintf(stdout, "Done. All %i files processed.\n", tasklist.count);
    }

    free_buffers(buffers);

    if (args.print_top_errors)
    {
        print_top_errors(&global);
    }

    if (args.has_test)
    {
        if (!args.batch_individual_test)
            print_and_check_stats(&global.stats, &args, "  [PASSED] ", "  [FAILED] ");
    }

#ifdef API_QBOUNDS
    if (args.bounds_path != NULL) {
        if (save_qbounds_file(args.bounds_path) != 0)
            exit(1);
    }
#endif

#ifdef API_QERROR
    if (args.qerror_path != NULL) {
        if (save_qerror_file(args.qerror_path) != 0)
            exit(1);
    }
#endif

    return 0;
}

