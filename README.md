# backup.c

A simple C utility that creates a backup copy of a file while preserving the original file's modification and access times.

## Description

This program reads a source file and creates a backup copy with the `.bak` extension. The key feature is that the backup file's modification and access times are set to match the original file's timestamps, ensuring that the backup is metadata-consistent with the source.

Originally based on exercises from "Understanding Linux/Unix" and modified to add automatic `.bak` extension naming and timestamp preservation.

## Features

- **Simple one-argument interface**: Specify the file to backup
- **Automatic naming**: Backup files are created with a `.bak` extension
- **Timestamp preservation**: Maintains original file's access and modification times
- **Efficient buffered I/O**: Uses 4KB buffer for file operations
- **Error handling**: Provides clear error messages for file operations

## Building

### Prerequisites
- GCC or compatible C compiler
- Standard POSIX libraries (stdio.h, unistd.h, fcntl.h, sys/stat.h, utime.h)

### Compilation

```bash
gcc -o backup backup.c
```

Or with additional warning flags:

```bash
gcc -Wall -Wextra -o backup backup.c
```

## Usage

```bash
./backup <source_file>
```

### Example

```bash
./backup document.txt
```

This creates `document.txt.bak` with identical content and preserves the original file's timestamps.

## How It Works

1. **Opens the source file** in read-only mode
2. **Creates a backup file** with `.bak` extension (mode 0644)
3. **Copies the file** in 4KB chunks for efficiency
4. **Reads the original file's metadata** (access and modification times)
5. **Updates the backup file's timestamps** to match the original
6. **Closes both files**

## Implementation Details

- **Buffer Size**: 4096 bytes (BUFFERSIZE)
- **File Permissions**: 0644 (rw-r--r--)
- **Timestamp Fields Used**:
  - `st_atime`: Last access time
  - `st_mtime`: Last modification time
- **System Calls Used**: `open()`, `read()`, `write()`, `creat()`, `stat()`, `utime()`, `close()`

## Error Handling

The program exits with status code 1 on any error and prints descriptive error messages using `perror()`, including:
- File open failures
- File creation failures
- Read/write errors
- Time update failures

## License

No license specified. See LICENSE file if present.

## Author

Modified from "Understanding Linux/Unix" exercises

---

**Last Updated**: 2016
