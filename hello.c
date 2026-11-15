#include <stdio.h>

#define ANSI_CYAN  "\033[1;36m"
#define ANSI_GRAY  "\033[0;90m"
#define ANSI_RESET "\033[0m"

/* Target OS detection */
#if defined(_WIN32)
#define TARGET_OS "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
#define TARGET_OS "macOS"
#elif defined(__linux__)
#define TARGET_OS "Linux"
#elif defined(__unix__)
#define TARGET_OS "Unix"
#else
#define TARGET_OS "Unknown OS"
#endif

/* Target CPU architecture detection */
#if defined(__x86_64__) || defined(_M_X64)
#define TARGET_ARCH "x86_64"
#elif defined(__aarch64__) || defined(_M_ARM64)
#define TARGET_ARCH "ARM64"
#elif defined(__i386__) || defined(_M_IX86)
#define TARGET_ARCH "x86"
#else
#define TARGET_ARCH "Unknown Arch"
#endif

int main(void) {
    const char *msg = "hello, world";
    const int rainbow[] = {91, 93, 92, 96, 94, 95};
    const int num_colors = (int) (sizeof(rainbow) / sizeof(rainbow[0]));
    int color_idx = 0;
    int i;

    /* 1. Rainbow greeting */
    printf("\n  ");
    for (i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == ' ') {
            printf(" ");
        } else {
            printf("\033[1;%dm%c", rainbow[color_idx % num_colors], msg[i]);
            color_idx++;
        }
    }
    printf(ANSI_RESET "\n\n");

    /* 2. ANSI 16-color palette (Standard & Bright) */
    printf("  ");
    for (i = 0; i < 8; i++) {
        printf("\033[4%dm   ", i);
    }
    printf(ANSI_RESET "\n  ");
    for (i = 0; i < 8; i++) {
        printf("\033[10%dm   ", i);
    }
    printf(ANSI_RESET "\n\n");

    /* 3. Compile environment metadata */
    printf("  " ANSI_GRAY "----------------------------------------" ANSI_RESET "\n");

#if defined(__clang__)
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "Clang %d.%d.%d\n",
           "Compiler", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined(__GNUC__)
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "GCC %d.%d.%d\n",
           "Compiler", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "MSVC %d\n",
           "Compiler", _MSC_VER);
#else
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "Unknown Compiler\n",
           "Compiler");
#endif

#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 202311L
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C23 (%ldL)\n", "Standard", __STDC_VERSION__);
#elif __STDC_VERSION__ >= 201710L
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C17 (%ldL)\n", "Standard", __STDC_VERSION__);
#elif __STDC_VERSION__ >= 201112L
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C11 (%ldL)\n", "Standard", __STDC_VERSION__);
#elif __STDC_VERSION__ >= 199901L
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C99 (%ldL)\n", "Standard", __STDC_VERSION__);
#else
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C95 (%ldL)\n", "Standard", __STDC_VERSION__);
#endif
#else
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "C89/C90\n", "Standard");
#endif

    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "%s (%s)\n",
           "Platform", TARGET_OS, TARGET_ARCH);
    printf("  " ANSI_CYAN "%-10s" ANSI_RESET "%s %s\n",
           "Built On", __DATE__, __TIME__);
    printf("  " ANSI_GRAY "----------------------------------------" ANSI_RESET "\n\n");

    return 0;
}
