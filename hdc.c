#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Использование: %s <имя_файла>\n", argv[0]);
		return 1;
	}

	FILE* file = fopen(argv[1], "rb");
	if (file == NULL) {
		perror("Ошибка при открытии файла.");
		return 1;
	}

	unsigned char buffer[16];
	size_t total_bytes = 0;

	while (1) {
		size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

		if (bytesRead == 0) {
			break;
		}

		printf("%08zx  ", total_bytes);

		for (size_t i = 0; i < 16; i++) {
			if (i < bytesRead) {
        	        	printf("%02x ", buffer[i]);
            		} else {
                		printf("   ");
            		}

            		if (i == 7) {
                		printf(" ");
            		}
        	}

        	printf(" ");

	        for (size_t i = 0; i < bytesRead; i++) {
        		if (isprint(buffer[i]) && buffer[i] != '\t' && buffer[i] != '\n') {
                		printf("%c", buffer[i]);
            		} else {
                		printf(".");
            		}
		}


		printf("\n");

		total_bytes += bytesRead;

		if (bytesRead < sizeof(buffer)) {
			break;
		}
	}

	fclose(file);

	return 0;
}
