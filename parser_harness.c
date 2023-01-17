#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

int
main(int argc, char *argv[])
{
    int code;
    yaml_event_type_t status;
    yaml_parser_t parser;
    yaml_document_t document;
    bool done = false;
    FILE *fd;

    //open filename passed via cmdline for reading
    fd = fopen(argv[1], "rb");

    //initialize yaml parser and parse the given input file
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, fd);
    yaml_parser_load(&parser, &document);

    while (!done)
    {
        if (!yaml_parser_load(&parser, &document)) {
            break;
        }

        done = (!yaml_document_get_root_node(&document));

        yaml_document_delete(&document);
    }

    //clean up after ourselves
    yaml_parser_delete(&parser);
    fclose(fd);

    return 0;
}
