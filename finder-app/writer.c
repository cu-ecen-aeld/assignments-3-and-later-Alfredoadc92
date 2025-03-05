#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int validate_input_param(int argn, char *argv[]);

int main(int argc, char *argv[])
{
    int retVal = EXIT_FAILURE;
    
    /*Validate number of arguments*/
    retVal = validate_input_param(argc, argv);
    
    if (EXIT_SUCCESS == retVal)
    {
        /*Open syslog*/
        openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

        /* Get the file path and string from arguments */
        const char *filepath = argv[1];
        const char *str = argv[2];

        /* Open the file for writing */
        FILE *file = fopen(filepath, "w");
        if (file == NULL)
        {
            syslog(LOG_ERR, "Error opening file: %s", filepath);
            perror("Error opening file");
            retVal = EXIT_FAILURE;
        }

        if(EXIT_SUCCESS == retVal)
        {
            /* Write the string to the file */
            if (fprintf(file, "%s", str) < 0)
            {
                syslog(LOG_ERR, "Error writing to file: %s", filepath);
                perror("Error writing to file");
                fclose(file);
                retVal = EXIT_FAILURE;
            }
            else
            {
                /* Log the successful write operation */
                syslog(LOG_DEBUG, "Writing %s to %s", str, filepath);

                /* Close the file */
                fclose(file);

                /* Close syslog */
                closelog();
            }
        }
    }

    return retVal;
}

int validate_input_param(int argn, char *argv[]) {
    int retVal = EXIT_SUCCESS;
    
    /* Check the number of arguments */
    if (argn != 3) 
    {
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        retVal = EXIT_FAILURE;
    }

    return retVal;
}