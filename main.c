#include <stdio.h>

#include "args.h"
#include "debug.h"

#include "freqCounter.h"

int verify_mode_given(short mode_number)
{
    if(mode_number != 1 && mode_number != 2 && mode_number != 4)
        ERROR(1, "ERROR: invalid value ‘%i’ for -m/--mode.", mode_number);

    return 0;
}

int main(int argc, char *argv[])
{
    struct gengetopt_args_info args_info;

    if(cmdline_parser(argc, argv, &args_info))
    {
        return 1;
    }

    if(args_info.file_given)
    {
        if(args_info.mode_given)
        {
            verify_mode_given(args_info.mode_arg);

            mode_get_listed_files(args_info, argc, argv);
        }
        else
        {
            get_listed_files(args_info, argc, argv);
        }
    }

    if(args_info.dir_given)
    {
        if(args_info.mode_given)
        {
            verify_mode_given(args_info.mode_arg);

            mode_get_listed_directories(argc, argv);
        }
        else
        {
            get_listed_directories(argc, argv);
        }
    }

    cmdline_parser_free(&args_info);

    return 0;
}