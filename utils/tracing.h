#ifndef TRACING_H
#define TRACING_H
#include "mbed.h"
#include "mbed_mem_trace.h"
/**
* @file tracing.h
*
* @brief Utilities for memory analysis.
*
* @author Diego Aceituno Seoane
*
* Allows the developer to see the usage of different memory elements such as the stack size for each thread.
* 
*/

/**
* @brief Prints in the serial interface the usage of the stack size for each thread.
*/
extern void print_memory_info();

#endif