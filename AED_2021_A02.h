//
// Tomás Oliveira e Silva, AED, January 2022
//
// Global stuff for the 2021.A.02 project
//

#ifndef AED_2021_A02

// protect against multiple inclusions of this file
#define AED_2021_A02

#define MAX_NAME_SIZE              31
#define MAX_ZIP_CODE_SIZE          63
#define MAX_TELEPHONE_NUMBER_SIZE  15
#define MAX_NISS  15

// from random_number.c
void aed_srandom(int seed);
int aed_random(void);

// from random_data.c
void random_name(char name[MAX_NAME_SIZE + 1]);
void random_zip_code(char zip_code[MAX_ZIP_CODE_SIZE + 1]);
void random_telephone_number(char telephone_number[MAX_TELEPHONE_NUMBER_SIZE + 1]);
void random_niss(char NISS[MAX_NISS + 1]);


// from elapsed_time.c
double cpu_time(void);

#endif
