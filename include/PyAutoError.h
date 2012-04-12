#ifndef PyAutoError_h
#define PyAutoError_h

#define PyAutoError(MSG, ...) printf("[ERROR] (%s:%i) ", __FILE__, __LINE__); printf(MSG, ##__VA_ARGS__); printf("\n"); fflush(stdout); exit(EXIT_FAILURE);

#endif