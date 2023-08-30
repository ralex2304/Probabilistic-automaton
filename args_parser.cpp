#include "args_parser.h"

Status::Statuses args_parse(int argc, char* argv[],
                            int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    assert(argv);
    assert(argc);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    /**
     * @brief This array contains console options, their functions and descriptions
     */
    static Argument args_dict[] = {
        {"-f", set_filename, "#   -f <name> - required - sets filename\n"},              ///< Set automat max level

        {"-l", set_level,    "#   -l <lvl> - required - sets automaton max level\n"},    ///< Set automat max level

        {"-n", set_symb_num, "#   -n <num> - required - sets printed symbols number\n"}, ///< Set printed symbols num

        {"-v", enable_voice, "#   -v - enables voiceover\n"},                            ///< Enable voiceover

        {"-h", print_help,   "#   -h - prints help information\n"},                      ///< Help option
    };

    static const int ARGS_DICT_LEN = sizeof(args_dict) / sizeof(args_dict[0]); ///< args_dict array len

    bool exit = false;
    for (int i = 1; i < argc; i++) {
        bool is_found = false;

        for (int j = 0; j < ARGS_DICT_LEN; j++) {
            if (strcmp(argv[i], args_dict[j].arg) == 0) {
                switch (args_dict[j].func(args_dict, ARGS_DICT_LEN, &i, argc, argv, auto_level, output_cnt, filename, voice)) {
                    case ArgsMode::CONTINUE:
                        break;
                    case ArgsMode::EXIT:
                        exit = true;
                        break;
                    case ArgsMode::ERR:
                        return Status::ARGS_ERROR;
                    default:
                        assert(0 && "args[j].func() returned wrong ArgsMode");
                        break;
                }
                is_found = true;
                break;
            }
        }
        if (is_found)
            continue;

        printf("Wrong console argument: %s\n"
               "Use -h for help\n", argv[i]);
        return Status::ARGS_ERROR;
    }
    if (exit)
        return Status::OK_EXIT;

    return Status::NORMAL_WORK;
}

ArgsMode print_help(const Argument args_dict[], const int args_dict_len,
                    int* arg_i, const int argc, char* argv[],
                    int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    (void) auto_level;
    (void) output_cnt;
    (void) filename;
    (void) voice;

    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    printf("# This program generates text with probabilistic automaton\n"
           "# Console args:\n");

    for (int i = 0; i < args_dict_len; i++)
        printf("%s", args_dict[i].description);

    printf("# End of help.\n");
    return ArgsMode::EXIT;
}

ArgsMode set_level(const Argument args_dict[], const int args_dict_len,
                   int* arg_i, const int argc, char* argv[],
                   int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    (void) args_dict;
    (void) args_dict_len;
    (void) output_cnt;
    (void) filename;
    (void) voice;

    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    if (++(*arg_i) >= argc || sscanf(argv[*arg_i], "%d", auto_level) != 1) {
        printf("No test level found\n");
        return ArgsMode::ERR;
    }
    return ArgsMode::CONTINUE;
}

ArgsMode set_symb_num(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    (void) args_dict;
    (void) args_dict_len;
    (void) auto_level;
    (void) filename;
    (void) voice;

    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    if (++(*arg_i) >= argc || sscanf(argv[*arg_i], "%zd", output_cnt) != 1) {
        printf("No output symbols number found\n");
        return ArgsMode::ERR;
    }
    return ArgsMode::CONTINUE;
}

ArgsMode set_filename(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    (void) args_dict;
    (void) args_dict_len;
    (void) auto_level;
    (void) output_cnt;
    (void) voice;

    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    if (++(*arg_i) >= argc) {
        printf("No filename found\n");
        return ArgsMode::ERR;
    }
    *filename = argv[*arg_i];
    return ArgsMode::CONTINUE;
}

ArgsMode enable_voice(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, const char** filename, bool* voice) {
    (void) args_dict;
    (void) args_dict_len;
    (void) arg_i;
    (void) argc;
    (void) argv;
    (void) auto_level;
    (void) output_cnt;
    (void) filename;

    assert(args_dict);
    assert(arg_i);
    assert(argc);
    assert(argv);
    assert(auto_level);
    assert(output_cnt);
    assert(filename);
    assert(voice);

    *voice = true;
    return ArgsMode::CONTINUE;
}
