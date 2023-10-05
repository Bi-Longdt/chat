#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef SLEEP
#define SLEEP 10
#endif

void createFolder() {
    const char *fdName = "./midterm";

    printf("Checking if '%s' exists...\n", fdName);
    if (mkdir(fdName, 0777) == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "'%s' already exists.\n", fdName);
        } else {
            fprintf(stderr, "Unable to create '%s': %s\n", fdName, strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else {
        printf("'%s' created.\n", fdName);
    }
}

void printFilePermissions() {
    struct stat st;
    const char *filePath = "./midterm/hello";

    if (stat(filePath, &st) == 0) {
        printf("File Permissions for '%s':\n", filePath);
        printf("Owner Read: %s\n", (st.st_mode & S_IRUSR) ? "Yes" : "No");
        printf("Owner Write: %s\n", (st.st_mode & S_IWUSR) ? "Yes" : "No");
        printf("Owner Execute: %s\n", (st.st_mode & S_IXUSR) ? "Yes" : "No");
    } else {
        perror("Unable to get file permissions");
    }
}

void createFile() {
	int fd;
	char* studentID = "21IT289_21IT283_21IT586"; // MaSV
	FILE* file = fopen("./midterm/hello", "w");
	printf("Checking if './midterm/hello' exists...\n");
	system("ls -l ./midterm/hello");
	printf("Trying to create './hello' with O_RDONLY | O_CREAT...\n");

	if ((fd = open("./midterm/hello", O_RDONLY | O_CREAT,
					S_IRUSR | S_IWUSR)) == -1) {
		fprintf(stderr, "Unable to create './midterm/hello': %s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
		
	}
	ssize_t bytesWritten = write(fd, studentID, strlen(studentID));
	if (bytesWritten == -1) {
        	fprintf(file, "Ma Sinh Vien: %s \n", studentID);
        	exit(EXIT_FAILURE);
    	}
	printf("'./midterm/hello' created. File descriptor is: %d\n", fd);
	printf("'%d' created with content: %s\n", fd, studentID);

}

void failExclFileCreation() {
	int fd;

	printf("Checking if './midterm/hello' exists...\n");
	system("ls -l ./midterm/hello");
	printf("Trying to create './hello' with O_RDONLY | O_CREAT | O_EXCL...\n");

	if ((fd = open("./hello", O_RDONLY | O_CREAT | O_EXCL,
					S_IRUSR | S_IWUSR)) == -1) {
		fprintf(stderr, "Unable to create './midterm/hello': %s\n",
				strerror(errno));
	}

	/* We expect this to fail! */
	if (close(fd) == -1) {
		fprintf(stderr, "Closing failed: %s\n", strerror(errno));
	}
}

void failOpenNonexistingFile() {
	int fd;

	printf("Trying to open (non-existant) './nosuchfile' with O_RDONLY...\n");

	if ((fd = open("./nosuchfile", O_RDONLY)) == -1) {
		fprintf(stderr, "Unable to open './nosuchfile': %s\n",
				strerror(errno));
	}

	/* We know this is going to fail, but no need to complain. */
	(void)close(fd);
}

void openFile() {
	int fd;

	printf("Trying to open './question1.c' with O_RDONLY...\n");

	if ((fd = open("./question1.c", O_RDONLY)) == -1) {
		fprintf(stderr, "Unable to open './question1.c': %s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("'./question1.c' opened. File descriptor is: %d\n", fd);

	if (close(fd) == 0) {
		printf("'./question1.c' closed again\n");
	}
}

void truncateFile() {
	int fd;
	char* studentID = "21IT289_21IT283_21IT586"; // MaSV
	FILE* file = fopen("./midterm/hello", "w");
	system("cp question1.c hello");
	printf("Copied 'question1.c' to 'hello'.\n");
	system("ls -l hello");

	printf("Trying to open './midterm/hello' with O_RDONLY | O_TRUNC...\n");

	if ((fd = open("./midterm/hello", O_RDONLY | O_TRUNC)) == -1) {
		fprintf(file, "Ma Sinh Vien: %s \n", studentID);
		exit(EXIT_FAILURE);
		
	}
	ssize_t bytesWritten = write(fd, studentID, strlen(studentID));
	if (bytesWritten == -1) {
        	fprintf(file, "Unable to write content to '%s': %s\n", studentID, strerror(errno));
        	exit(EXIT_FAILURE);
    	}
	printf("'./midterm/hello' truncated -- see 'ls -l hello'\n");
	printf("'%d' created with content: %s\n", fd, studentID);
	system("ls -l hello");

	(void)close(fd);
}

char *
getType(const struct stat sb) {
	if (S_ISREG(sb.st_mode))
		return "regular file";
	else if (S_ISDIR(sb.st_mode))
		return "directory";
	else if (S_ISCHR(sb.st_mode))
		return "character special";
	else if (S_ISBLK(sb.st_mode))
		return "block special";
	else if (S_ISFIFO(sb.st_mode))
		return "FIFO";
	else if (S_ISLNK(sb.st_mode))
		return "symbolic link";
	else if (S_ISSOCK(sb.st_mode))
		return "socket";
	else
		return "unknown";
}

int main(int argc, char **argv) {
	char* studentID = "21IT289_21IT283_21IT586"; // MaSV
    	createFolder();
	system("ls -l midterm");
	printf("\n");
	sleep(SLEEP);

	createFile();
	system("ls -l hello");
	printf("\n");
	sleep(SLEEP);

	failExclFileCreation();
	printf("\n");
	sleep(SLEEP);

	openFile();
	printf("\n");
	sleep(SLEEP);

	failOpenNonexistingFile();
	printf("\n");
	sleep(SLEEP);

	truncateFile();
	
	printFilePermissions();

	return 0;
}
