#include <stdio.h>
#include <unistd.h>

void print_ps1() {
    printf("[%s] > ", get_current_dir_name());
}

void print_ps2() {
    printf(">> ");
}

void print_ps3() {
    printf(">>> ");
}

void print_ps4() {
    printf(">>>> ");
}
