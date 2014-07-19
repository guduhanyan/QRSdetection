/*
 * qrstest.c
 *
 *  Created on: Jul 19, 2014
 *      Author: Dusan Kostic
 */
#include <stdio.h>
#include <stdlib.h>
#include "qrs_definitions.h"
#include "qrs_utils.h"
#include "qrs_detection.h"

/* TODO:
 * Acquire input filename, output filename,
 * length and frequency from command line or ini file.
 */
#define INPUT_FILENAME  "./testdb/rec_1.txt"
#define OUTPUT_FILENAME "./test/out_1.txt"
#define INPUT_LENGTH    (10000)
#define INPUT_FREQUENCY (500)

int main(int argc, char * argv[])
{
    qrs_status status = qrs_no_err;
    qrs_signal * input_signal = NULL;
    qrs_signal * output_signal = NULL;

    printf("Pan-Tompkins QRS detection algorithm\n");

    input_signal  = qrs_alloc_signal(INPUT_LENGTH, INPUT_FREQUENCY);
    output_signal = qrs_alloc_signal(INPUT_LENGTH, INPUT_FREQUENCY);
    if (input_signal == NULL || output_signal == NULL)
    {
        printf("Memory allocation failed.\n");
        goto bail;
    }

    printf("Reading input data from file...\n");
    status = qrs_read_signal_from_file(input_signal, INPUT_FILENAME);
    if (status != qrs_no_err)
    {
        printf("Read signal from file failed.\n");
        goto bail;
    }
    printf("Done.\n");

    printf("QRS detection start...\n");
    status = qrs_detection_core(input_signal, output_signal);
    if (status != qrs_no_err)
    {
        printf("QRS detection failed.\n");
        goto bail;
    }
    printf("Done.\n");

    printf("Writing output data to file...\n");
    status = qrs_write_signal_to_file(output_signal, OUTPUT_FILENAME);
    if (status != qrs_no_err)
    {
        printf("Write signal to file failed.\n");
        goto bail;
    }
    printf("Done.\n");

bail:
    qrs_free_signal(input_signal);
    qrs_free_signal(output_signal);

    return 0;
}
