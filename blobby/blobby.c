// blobby.c
// blob file archiver
// COMP1521 20T3 Assignment 2
// Written by Zheng Luo (z5206267@ad.unsw.edu.au) at 7/Nov/2020

/*
^
+ ====================================== +
+ Give a rundown of your approaches here +
+ ====================================== +
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// the first byte of every blobette has this value
#define BLOBETTE_MAGIC_NUMBER          0x42

// maximum number of bytes in variable-length blobette fields
#define BLOBETTE_MAX_PATHNAME_LENGTH   65535
#define BLOBETTE_MAX_CONTENT_LENGTH    281474976710655


// ADD YOUR #defines HERE
#define BYTE2BIT 8
#define METASIZE 128362
#define POS_MAGIC_NUMBER 0
#define START_POS_MODE 1
#define END_POS_MODE 3
#define START_POS_PATHNAME_LENGTH 4
#define END_POS_PATHNAME_LENGTH 5
#define START_POS_CONTENT_LENGTH 6
#define END_POS_CONTENT_LENGTH 11
#define START_POS_PATHNAME 12
#define END_POS_PATHNAME (START_POS_PATHNAME + pathname_length - 1)
#define START_POS_CONTENT (END_POS_PATHNAME + 1)
#define END_POS_CONTENT (START_POS_CONTENT + content_length - 1)
#define POS_HASH (END_POS_CONTENT + 1)

typedef enum action {
    a_invalid,
    a_list,
    a_extract,
    a_create
} action_t;

///////////////////////////////////////////////////////////////////////
void usage(char *myname);
action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob);

void list_blob(char *blob_pathname);
void extract_blob(char *blob_pathname);
void create_blob(char *blob_pathname, char *pathnames[], int compress_blob);

uint8_t blobby_hash(uint8_t hash, uint8_t byte);

// Self-created functions below, 
// its detailed introductions are located in Self-Created functions
void read_blob(FILE *input_stream);
uint64_t mode_recognition(int counter_field_length, uint64_t input_integer, 
uint64_t mode);
uint16_t pathname_length_recognition(int counter_field_length, 
uint64_t input_integer, uint16_t pathname_length);
uint64_t content_length_recognition(int counter_field_length, 
uint64_t input_integer, uint64_t content_length);
int pathname_recognition(int counter_field_length, 
uint64_t input_integer, int counter_pathname_length, 
char *pathname, uint16_t pathname_length);
int content_recognition(int counter_field_length, 
uint64_t input_integer, int counter_content_length, 
char *content, uint16_t pathname_length, uint64_t content_length);
uint8_t hash_recognition(int counter_field_length, uint64_t input_integer, 
uint8_t hash, uint8_t calculated_hash, uint16_t pathname_length, 
uint64_t content_length);
int new_blob_recognition(uint64_t input_integer, int counter_field_length, 
uint16_t pathname_length, int counter_pathname_length, uint64_t content_length, 
int counter_content_length);
void create_extracted_blob(char *pathname, char *content, 
uint64_t content_length, uint8_t calculated_hash, uint8_t hash, uint64_t mode);
///////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    char *blob_pathname = NULL;
    char **pathnames = NULL;
    int compress_blob = 0;
    action_t action = process_arguments(argc, argv, &blob_pathname, &pathnames,
                                        &compress_blob);

    switch (action) {
    case a_list:
        list_blob(blob_pathname);
        break;

    case a_extract:
        extract_blob(blob_pathname);
        break;

    case a_create:
        create_blob(blob_pathname, pathnames, compress_blob);
        break;

    default:
        usage(argv[0]);
    }

    return 0;
}

// print a usage message and exit

void usage(char *myname) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\t%s -l <blob-file>\n", myname);
    fprintf(stderr, "\t%s -x <blob-file>\n", myname);
    fprintf(stderr, "\t%s [-z] -c <blob-file> pathnames [...]\n", myname);
    exit(1);
}

// process command-line arguments
// check we have a valid set of arguments
// and return appropriate action
// **blob_pathname set to pathname for blobfile
// ***pathname set to a list of pathnames for the create action
// *compress_blob set to an integer for create action

action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob) {
    extern char *optarg;
    extern int optind, optopt;
    int create_blob_flag = 0;
    int extract_blob_flag = 0;
    int list_blob_flag = 0;
    int opt;
    while ((opt = getopt(argc, argv, ":l:c:x:z")) != -1) {
        switch (opt) {
        case 'c':
            create_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'x':
            extract_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'l':
            list_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'z':
            (*compress_blob)++;
            break;

        default:
            return a_invalid;
        }
    }

    if (create_blob_flag + extract_blob_flag + list_blob_flag != 1) {
        return a_invalid;
    }

    if (list_blob_flag && argv[optind] == NULL) {
        return a_list;
    } else if (extract_blob_flag && argv[optind] == NULL) {
        return a_extract;
    } else if (create_blob_flag && argv[optind] != NULL) {
        *pathnames = &argv[optind];
        return a_create;
    }

    return a_invalid;
}
////////////////////////////////////////////////////////////////////////
//                              Subset 0                              //
////////////////////////////////////////////////////////////////////////

// list the contents of blob_pathname
void list_blob(char *blob_pathname) {

    FILE *input_stream = fopen(blob_pathname, "rb");
    if (input_stream == NULL) {
        perror(blob_pathname);
        exit(EXIT_FAILURE);
    }
    read_blob(input_stream);
    
}


////////////////////////////////////////////////////////////////////////
//                              Subset 1                              //
////////////////////////////////////////////////////////////////////////

// extract the contents of blob_pathname
void extract_blob(char *blob_pathname) {
    FILE *input_stream = fopen(blob_pathname, "rb");
    if (input_stream == NULL) {
        perror(blob_pathname);
        exit(EXIT_FAILURE);
    }
    // General variables.
    int counter_field_length = 0;
    uint64_t input_integer;
    uint64_t mode = 0;
    // Variables for pathname.
    uint16_t pathname_length = 0;
    int counter_pathname_length = 0;
    char pathname[BLOBETTE_MAX_PATHNAME_LENGTH] = {'\0'};
    // Variables for content.
    uint64_t content_length = 0;
    int counter_content_length = 0;
    char content[METASIZE];
    // Varibles for hash.
    uint8_t calculated_hash = 0;
    uint8_t hash = 0;
    while ((input_integer = fgetc(input_stream)) != EOF) {
        // Error if blob not start with 'B'.
        if (counter_field_length == POS_MAGIC_NUMBER && 
        input_integer != BLOBETTE_MAGIC_NUMBER) {
            fprintf(stderr, "ERROR: Magic byte of blobette incorrect\n");
            exit(EXIT_FAILURE);
        }
        // Mode recognition.
        mode = mode_recognition(counter_field_length, input_integer, mode);
        // Pathname length recognition.
        pathname_length = pathname_length_recognition(counter_field_length, 
        input_integer, pathname_length); 
        // Content length recognition.
        content_length = content_length_recognition(counter_field_length, 
        input_integer, content_length);
        // Path name recognition.
        counter_pathname_length = pathname_recognition(
        counter_field_length, input_integer, counter_pathname_length, pathname, 
        pathname_length);
        // Content recognition.
        counter_content_length = content_recognition(counter_field_length, 
        input_integer, counter_content_length, content, pathname_length, 
        content_length); 
        // Hash recognition.
        hash = hash_recognition(counter_field_length, input_integer, hash, 
        calculated_hash, pathname_length, content_length);
        // Recognition of next blob.
        if (new_blob_recognition(input_integer, counter_field_length, 
        pathname_length, counter_pathname_length, content_length, 
        counter_content_length) == 1) {
            create_extracted_blob(pathname, content, content_length, 
            calculated_hash, hash, mode);
            // Reset all the variables for next blob.
            counter_field_length = 0;
            mode = 0;
            // Reset pathname variables.
            pathname_length = 0;
            counter_pathname_length = 0;
            memset(pathname, '\0', BLOBETTE_MAX_PATHNAME_LENGTH);
            // Reset content variables.
            content_length = 0;
            counter_content_length = 0;
            // Reset hash variables.
            calculated_hash = 0;
            hash = 0;
            
        }
        // Hash vertification.
        if (counter_field_length != POS_HASH) {
            calculated_hash = blobby_hash(calculated_hash, 
            (uint8_t)input_integer);
        }
        counter_field_length++;
    }
    // create blob for the last file which excluded from loop.
    create_extracted_blob(pathname, content, content_length, calculated_hash, 
    hash, mode);
}

////////////////////////////////////////////////////////////////////////
//                              Subset 2                              //
////////////////////////////////////////////////////////////////////////

// create blob_pathname from NULL-terminated array pathnames
// compress with xz if compress_blob non-zero (subset 4)

void create_blob(char *blob_pathname, char *pathnames[], int compress_blob) {
    // Create a string to store information in blob format.
    int counter_blob = 0;
    uint16_t blob[METASIZE] = {'\0'};
    // preview_counter is used to store the amount of bytes have been counter,
    // in the previews blobs, for the sake of calculating hash value.
    int previews_counter = 0;
    // Open each file to read their bytes and convert into blob.
    for (int counter_adding_files = 0; pathnames[counter_adding_files]; 
    counter_adding_files++) {
        FILE *input_stream = fopen(pathnames[counter_adding_files], "rb");
        if (input_stream == NULL) {
            perror(pathnames[counter_adding_files]);
            exit(EXIT_FAILURE);
        }
        // Obtain information of the file via stat function.
        struct stat s;
        if (stat(pathnames[counter_adding_files], &s) != 0) {
            perror(pathnames[counter_adding_files]);
            exit(EXIT_FAILURE);
        }
        // Store magic number indicates the start of file.
        blob[counter_blob] = BLOBETTE_MAGIC_NUMBER;
        counter_blob++;
        // Store mode of the current file into blob.
        for (int counter_mode = START_POS_MODE; counter_mode <= END_POS_MODE; 
        counter_mode++) {
            blob[counter_blob] = (s.st_mode >> 
            ((END_POS_MODE - counter_mode) * BYTE2BIT)) & 0xFF;
            counter_blob++;
        }
        // Store pathname length into blob.
        uint32_t pathname_length = strlen(pathnames[counter_adding_files]);
        for (int counter_pathname_length = START_POS_PATHNAME_LENGTH; 
        counter_pathname_length <= END_POS_PATHNAME_LENGTH; 
        counter_pathname_length++) {
            blob[counter_blob] = (pathname_length >> 
            ((END_POS_PATHNAME_LENGTH - counter_pathname_length) * BYTE2BIT));
            counter_blob++;
        }
        // Store content length into blob.
        for (int counter_content_length = START_POS_CONTENT_LENGTH; 
        counter_content_length <= END_POS_CONTENT_LENGTH; 
        counter_content_length++) {
            blob[counter_blob] = (s.st_size >> 
            ((END_POS_CONTENT_LENGTH - counter_content_length) * BYTE2BIT));
            counter_blob++;
        }
        // Store pathname into blob.
        for (int counter_pathname = 0; counter_pathname < pathname_length;
        counter_pathname++) {
            blob[counter_blob] = pathnames[counter_adding_files][counter_pathname];
            counter_blob++;
        }
        // Store the contents into blob.
        for (int counter_content = 0; counter_content < s.st_size; 
        counter_content++) {
            blob[counter_blob] = fgetc(input_stream);
            counter_blob++;
        }
        // Store hash number into blob.
        uint8_t calculated_hash = 0;
        for (int counter_hash = previews_counter; counter_hash < 
        counter_blob; counter_hash++) {
            calculated_hash = blobby_hash(calculated_hash, 
            (uint8_t)blob[counter_hash]);
            
        }
        blob[counter_blob] = calculated_hash;
        counter_blob++;
        previews_counter = counter_blob;
        printf("Adding: %s\n", pathnames[counter_adding_files]);
        
    }
    // Transfer the blob array into new file.
    FILE *output_stream = fopen(blob_pathname, "wb");
    if (output_stream == NULL) {
        perror(blob_pathname);
        exit(EXIT_FAILURE);
    }
    for (int counter_output = 0; counter_output < counter_blob; 
    counter_output++) {
        fputc(blob[counter_output], output_stream);
    }

}


////////////////////////////////////////////////////////////////////////
//                       Self-Created Functions                       //
////////////////////////////////////////////////////////////////////////

// Subset 0.
void read_blob(FILE *input_stream) {
    // General variables.
    int counter_field_length = 0;
    uint64_t input_integer;
    uint64_t mode = 0;
    // Variables for pathname.
    uint16_t pathname_length = 0;
    int counter_pathname_length = 0;
    char pathname[BLOBETTE_MAX_PATHNAME_LENGTH] = {'\0'};
    // Variables for content.
    uint64_t content_length = 0;
    int counter_content_length = 0;
    char content[METASIZE];
    // Varibles for hash.
    uint8_t calculated_hash = 0;
    uint8_t hash = 0;
    while ((input_integer = fgetc(input_stream)) != EOF) {
        // Error if blob not start with 'B'.
        if (counter_field_length == POS_MAGIC_NUMBER && 
        input_integer != BLOBETTE_MAGIC_NUMBER) {
            fprintf(stderr, "ERROR: Magic byte of blobette incorrect\n");
            exit(EXIT_FAILURE);
        }
        // Mode.
        mode = mode_recognition(counter_field_length, input_integer, mode);
        // Pathname length.
        pathname_length = pathname_length_recognition(counter_field_length, 
        input_integer, pathname_length); 
        // Content length.
        content_length = content_length_recognition(counter_field_length, 
        input_integer, content_length);
        // Path name.
        counter_pathname_length = pathname_recognition(
        counter_field_length, input_integer, counter_pathname_length, pathname, 
        pathname_length);
        // Content.
        counter_content_length = content_recognition(counter_field_length, 
        input_integer, counter_content_length, content, pathname_length, 
        content_length); 
        // Hash.
        hash = hash_recognition(counter_field_length, input_integer, hash, 
        calculated_hash, pathname_length, content_length);
        // Recognition of next blob.
        if (new_blob_recognition(input_integer, counter_field_length, 
        pathname_length, counter_pathname_length, content_length, 
        counter_content_length) == 1) {
            // Print out required message.
            printf("%06lo %5lu %s\n", mode, content_length, pathname);
            // Reset all the variables for next blob.
            counter_field_length = 0;
            mode = 0;
            // Reset pathname variables.
            pathname_length = 0;
            counter_pathname_length = 0;
            memset(pathname, '\0', BUFSIZ);
            // Reset content variables.
            content_length = 0;
            counter_content_length = 0;
            // Reset hash variables.
            calculated_hash = 0;
            hash = 0;
        }
        counter_field_length++;
    }
   
    printf("%06lo %5lu %s\n", mode, content_length, pathname);
}


int new_blob_recognition(uint64_t input_integer, int counter_field_length, 
uint16_t pathname_length, int counter_pathname_length, uint64_t content_length, 
int counter_content_length) {
    if (input_integer == BLOBETTE_MAGIC_NUMBER && 
    counter_field_length > START_POS_PATHNAME && 
    pathname_length == counter_pathname_length &&
    content_length == counter_content_length) {
        return 1;
    }
    else {
        return 0;
    }
}

uint64_t mode_recognition(int counter_field_length, uint64_t input_integer, 
uint64_t mode) {
    if (counter_field_length >= START_POS_MODE && 
    counter_field_length <= END_POS_MODE) {
        mode |= input_integer << 
        ((END_POS_MODE - counter_field_length) * BYTE2BIT);
    }
    return mode;
}
uint16_t pathname_length_recognition(int counter_field_length, 
uint64_t input_integer, uint16_t pathname_length) {
    if (counter_field_length >= START_POS_PATHNAME_LENGTH &&
    counter_field_length <= END_POS_PATHNAME_LENGTH) {
        pathname_length |= input_integer << 
        ((END_POS_PATHNAME_LENGTH - counter_field_length) * BYTE2BIT);
    }
    return pathname_length;
}
uint64_t content_length_recognition(int counter_field_length, 
uint64_t input_integer, uint64_t content_length) {
    if (counter_field_length >= START_POS_CONTENT_LENGTH && 
    counter_field_length <= END_POS_CONTENT_LENGTH) {
        content_length |= input_integer << 
        (END_POS_CONTENT_LENGTH - counter_field_length) * BYTE2BIT;
    }
    return content_length;
}
int pathname_recognition(int counter_field_length, 
uint64_t input_integer, int counter_pathname_length, 
char *pathname, uint16_t pathname_length) {
    if (counter_field_length >= START_POS_PATHNAME &&
    counter_field_length <= END_POS_PATHNAME) {
        pathname[counter_pathname_length] = input_integer;
        counter_pathname_length++;
    }
    return counter_pathname_length;
}
int content_recognition(int counter_field_length, 
uint64_t input_integer, int counter_content_length, 
char *content, uint16_t pathname_length, uint64_t content_length) {
    if (counter_field_length >= START_POS_CONTENT &&
    counter_field_length <= END_POS_CONTENT) {
        content[counter_content_length] = input_integer;
        counter_content_length++;
    }
    return counter_content_length;
}
uint8_t hash_recognition(int counter_field_length, uint64_t input_integer, 
uint8_t hash, uint8_t calculated_hash, uint16_t pathname_length, 
uint64_t content_length) {
    if (counter_field_length == POS_HASH) {
        hash = input_integer;
    }
    
    return hash;
}

// Subset 1
void create_extracted_blob(char *pathname, char *content, 
uint64_t content_length, uint8_t calculated_hash, uint8_t hash, uint64_t mode) {
    // Open the file.
    FILE *output_stream = fopen(pathname, "w");
    if (output_stream == NULL) {
        perror(pathname);
        exit(EXIT_FAILURE);
    }
    // Change the permission.
    if (chmod(pathname, mode) != 0) {
        perror(pathname);  
        exit(EXIT_FAILURE);
    }
    
    for (int counter_output = 0; counter_output < content_length; 
    counter_output++) {
        fputc(content[counter_output], output_stream);
    }
    
    printf("Extracting: %s\n", pathname);
    if (hash != calculated_hash) {
        fprintf(stderr, "ERROR: blob hash incorrect\n");
        exit(EXIT_FAILURE);
    }
}

// Lookup table for a simple Pearson hash
// https://en.wikipedia.org/wiki/Pearson_hashing
// This table contains an arbitrary permutation of integers 0..255

const uint8_t blobby_hash_table[256] = {
    241, 18,  181, 164, 92,  237, 100, 216, 183, 107, 2,   12,  43,  246, 90,
    143, 251, 49,  228, 134, 215, 20,  193, 172, 140, 227, 148, 118, 57,  72,
    119, 174, 78,  14,  97,  3,   208, 252, 11,  195, 31,  28,  121, 206, 149,
    23,  83,  154, 223, 109, 89,  10,  178, 243, 42,  194, 221, 131, 212, 94,
    205, 240, 161, 7,   62,  214, 222, 219, 1,   84,  95,  58,  103, 60,  33,
    111, 188, 218, 186, 166, 146, 189, 201, 155, 68,  145, 44,  163, 69,  196,
    115, 231, 61,  157, 165, 213, 139, 112, 173, 191, 142, 88,  106, 250, 8,
    127, 26,  126, 0,   96,  52,  182, 113, 38,  242, 48,  204, 160, 15,  54,
    158, 192, 81,  125, 245, 239, 101, 17,  136, 110, 24,  53,  132, 117, 102,
    153, 226, 4,   203, 199, 16,  249, 211, 167, 55,  255, 254, 116, 122, 13,
    236, 93,  144, 86,  59,  76,  150, 162, 207, 77,  176, 32,  124, 171, 29,
    45,  30,  67,  184, 51,  22,  105, 170, 253, 180, 187, 130, 156, 98,  159,
    220, 40,  133, 135, 114, 147, 75,  73,  210, 21,  129, 39,  138, 91,  41,
    235, 47,  185, 9,   82,  64,  87,  244, 50,  74,  233, 175, 247, 120, 6,
    169, 85,  66,  104, 80,  71,  230, 152, 225, 34,  248, 198, 63,  168, 179,
    141, 137, 5,   19,  79,  232, 128, 202, 46,  70,  37,  209, 217, 123, 27,
    177, 25,  56,  65,  229, 36,  197, 234, 108, 35,  151, 238, 200, 224, 99,
    190
};

// Given the current hash value and a byte
// blobby_hash returns the new hash value
//
// Call repeatedly to hash a sequence of bytes, e.g.:
// uint8_t hash = 0;
// hash = blobby_hash(hash, byte0);
// hash = blobby_hash(hash, byte1);
// hash = blobby_hash(hash, byte2);
// ...

uint8_t blobby_hash(uint8_t hash, uint8_t byte) {
    return blobby_hash_table[hash ^ byte];
}
