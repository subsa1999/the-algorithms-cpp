// author: Subham Santra
// purpose: I am bored, I want to code something without using AI
// date: 2026-06-27 

#include<stdio.h>
#include<stdlib.h>

// sizeof(char*) = 8 bytes
// sizeof(int) = 4 bytes
// sizeof(long long int) = 8 bytes
// therefore, sizeof(t_person) = 8 + 4 + 8 = 20 bytes
typedef struct {
    char* name;
    int age;
    long long int phone_number;
} t_person;


void _use_malloc() {
    t_person* person = (t_person*)malloc(sizeof(t_person));

    // allocate memory for the name
    person->name = (char*)malloc(50 * sizeof(char));

    // by now we have allocated memory for the person struct and the name string
    // we will print the contents of the struct and the size of the allocated memory
    // we have used malloc so initially the contents of the struct will be garbage values
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);


    person->name = "Mr. Subham Santra";
    person->age = 25;
    person->phone_number = 1234567890;

    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);

    // print the size of the allocated memory
    printf("Size of allocated memory: %zu bytes\n", sizeof(t_person));
    printf("Size of allocated memory for name: %zu bytes\n", 50 * sizeof(char));

    // free the allocated memory
    free(person->name);
    free(person);

}

void _use_calloc() {
    t_person* person = (t_person*)calloc(1, sizeof(t_person));

    // allocate memory for the name
    person->name = (char*)calloc(50, sizeof(char));

    // by now we have allocated memory for the person struct and the name string
    // we will print the contents of the struct and the size of the allocated memory
    // we have used calloc so initially the contents of the struct will be zeroed out
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);

    person->name = "Mr. Subham Santra";
    person->age = 25;
    person->phone_number = 1234567890;

    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);

    // print the size of the allocated memory
    printf("Size of allocated memory: %zu bytes\n", sizeof(t_person));
    printf("Size of allocated memory for name: %zu bytes\n", 50 * sizeof(char));

    // free the allocated memory
    free(person->name);
    free(person);
}

void _use_realloc() {
    t_person* person = (t_person*)malloc(sizeof(t_person));

    // allocate memory for the name
    person->name = (char*)malloc(50 * sizeof(char));

    // by now we have allocated memory for the person struct and the name string
    // we will print the contents of the struct and the size of the allocated memory
    // we have used malloc so initially the contents of the struct will be garbage values
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);

    person->name = "Mr. Subham Santra";
    person->age = 25;
    person->phone_number = 1234567890;

    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Phone Number: %lld\n", person->phone_number);

    // reallocate memory for the name
    person->name = (char*)realloc(person->name, 100 * sizeof(char));

    // print the size of the allocated memory
    printf("Size of allocated memory: %zu bytes\n", sizeof(t_person));
    printf("Size of allocated memory for name: %zu bytes\n", 100 * sizeof(char));

    // free the allocated memory
    free(person->name);
    free(person);
}

int main() {
    _use_malloc();
    _use_calloc();
    _use_realloc();
    return 0;
}