#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "options.h"

struct user_options;

void userOptions(int argc, char* argv[], struct user_options* uo){

    uo->fn = false;
    uo->sn = false;
    uo->rn = false;

    int opt;
    int option_index = 0;

	static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"load", required_argument, 0, 'l'},
        {"print", no_argument, 0, 'p'},
		{"rule", required_argument, 0, 'r'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

	 while ((opt = getopt_long(argc, argv, "hl:pr:o:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                printf("Usage: %s [options]\n", argv[0]);
                printf("Options:\n");
                printf("  -h, --help\t\tDisplay this help message\n");
                printf("  -l, --load\t\tLoad a snapshot to resume from\n");
				printf("  -p, --print\t\tPrint a list of standard rules\n");
				printf("  -r, --rule\t\tSpecify a standard rule eg. conway\n");
                printf("  -o, --output=FILE\tSpecify output file(snapshot) name in case you create one\n");
                exit(EXIT_SUCCESS);
            case 'l':
                strcpy(uo->snapname, optarg);
                uo->sn = true;
                printf("Snapshot path set: %s\n", optarg);
                exit(EXIT_SUCCESS);
			case 'p':
                printf("Rule list:\n");
				printf("conway\n");
                exit(EXIT_SUCCESS);
			case 'r':
                printf("Standard rule set: %s\n", optarg);
                uo->rn = true;
                exit(EXIT_SUCCESS);
            case 'o':
				/*Add buffer overflow check*/
				strcpy(uo->filename, optarg);
                uo->fn = true;
                printf("Output file name set: %s\n", uo->filename);
                break;
            case '?':
                /*Handle unknown arguments*/
                fprintf(stderr, "Invalid option: %c\n", optopt);
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }
    }
	for (; optind < argc; optind++) {
        printf("Non-option argument: %s\n", argv[optind]);
    }

}