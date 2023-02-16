#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

const char *names[] = {
        "Smith",
        "Johnson",
        "Garcia",
        "Brown",
        "Jones",
        "Davis",
        "Williams",
        "Rodriguez",
        "Miller"
};
const int names_count = sizeof(names) / sizeof(names[0]);

int rename_files(const char *dir, const char *prefix) {
    // Open the directory
    DIR *d = opendir(dir);
    if (d == NULL) {
        fprintf(stderr, "Error opening directory '%s': %s\n", dir, strerror(errno));
        return 1;
    }

    // Read each file in the directory
    struct dirent *entry;
    int file_count = 0;
    while ((entry = readdir(d)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // Construct the full path of the entry
        char path[FILENAME_MAX];
        snprintf(path, FILENAME_MAX, "%s/%s", dir, entry->d_name);
        // Determine the type of the entry
        struct stat sb;
        if (stat(path, &sb) != 0) {
            fprintf(stderr, "Error getting information about '%s': %s\n", path, strerror(errno));
            closedir(d);
            return 1;
        }
        // Skip subdirectories
        if (S_ISDIR(sb.st_mode)) {
            continue;
        }
        // Construct the old and new file names
        char old_file[FILENAME_MAX];
        snprintf(old_file, FILENAME_MAX, "%s", path);
        char new_file[FILENAME_MAX];
        char *dot_pos = strrchr(entry->d_name, '.');
        if (dot_pos != NULL) {
            // File has an extension, preserve it
            snprintf(new_file, FILENAME_MAX, "%s/%s_%d_%s%s", dir, prefix, file_count, names[file_count % names_count],
                     dot_pos);
        } else {
            // File does not have an extension
            snprintf(new_file, FILENAME_MAX, "%s/%s_%d_%s", dir, prefix, file_count, names[file_count % names_count]);
        }

        // Rename the file
        if (rename(old_file, new_file) != 0) {
            fprintf(stderr, "Error renaming '%s' to '%s': %s\n", old_file, new_file, strerror(errno));
            closedir(d);
            return 1;
        }
        ++file_count;
    }
    // Close the directory
    closedir(d);

    return 0;
}

int main(int argc, char *argv[]) {
    // Check the number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s DIR PREFIX\n", argv[0]);
        return 1;
    }

    // Rename the files in the directory
    if (rename_files(argv[1], argv[2]) != 0) {
        return 1;
    }

    return 0;
}


/*
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

// List of names to add to the end of the file names
const char *names[] = {
        "Ramirez",
        "Jenkins",
        "Rossi",
        "Smith",
        "Gupta",
        "Peterson",
        "Chen",
        "Rodriguez",
        "Garcia"
};
// Calculate the number of elements in the `names` array.
// size in bytes of the array / size in bytes of the first element = number of elements in the array
const int names_count = sizeof(names) / sizeof(names[0]);

int main(int argc, char *argv[]) {
    // Check if the user has provided the correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <new_prefix>\n", argv[0]);
        return 1;
    }

    // Open the directory
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Error opening directory '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }

    // Read each file in the directory
    struct dirent *entry;
    int file_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the old and new file names
        char old_file[FILENAME_MAX];
        snprintf(old_file, FILENAME_MAX, "%s/%s", argv[1], entry->d_name);
        char new_file[FILENAME_MAX];
        char *dot_pos = strrchr(entry->d_name, '.');
        if (dot_pos != NULL) {
            // File has an extension, preserve it
            snprintf(new_file, FILENAME_MAX, "%s/%s_%s%s", argv[1], argv[2], names[file_count % names_count], dot_pos);
        } else {
            // File does not have an extension
            snprintf(new_file, FILENAME_MAX, "%s/%s_%d_%s", argv[1], argv[2], file_count, names[file_count % names_count]);
        }

        // Rename the file
        if (rename(old_file, new_file) != 0) {
            fprintf(stderr, "Error renaming '%s' to '%s': %s\n", old_file, new_file, strerror(errno));
            closedir(dir);
            return 1;
        }
        file_count++;
    }

    // Close the directory
    closedir(dir);

    return 0;
}
*/
