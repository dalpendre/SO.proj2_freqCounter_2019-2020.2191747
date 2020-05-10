#include <stdio.h>

#include "args.h"
#include "debug.h"

#include "freqCounter.h"

int main(int argc, char *argv[])
{
    struct gengetopt_args_info args_info;

    if(cmdline_parser(argc, argv, &args_info))
    {
        return 1;
    }

    if(args_info.file_given)
    {
        verify_parameters(argc, argv);
    }

    cmdline_parser_free(&args_info);

    return 0;
}