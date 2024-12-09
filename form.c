#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

void header(char *MYME_type);
void start_page(char *title);
void end_page(void);

int main(int argc, char **argv, char **envp) {
	header("text/html");
	start_page("Usando CGI action");

	char *qEnv;

	if ((qEnv = getenv("QUERY_STRING"))) {
		char buffer[MAX_SIZE];
		strncpy(buffer, qEnv, MAX_SIZE-1);

		char nome[100];
		int idade = 0;

		//separar o buffer com &
		char *separate_buffer = strtok(buffer, "&");
		sscanf(separate_buffer, "nome=%s", nome);
		printf("<p>O nome: %s</p>", nome);

		//próxima chamada com NULL
		separate_buffer = strtok(NULL, "&");
		sscanf(separate_buffer, "idade=%d", &idade);
		printf("<p>A idade: %d</p>", idade);
	} else {
		printf("<p>Deu errado.</p>");
	}

	end_page();
	return 0;
}

void header(char *MYME_type) {
	printf("Content-type:%s\n\n", MYME_type);
}

void start_page(char *title) {
	printf("<html>");
	printf("<head>");
	printf("<title>%s</title>", title);
	printf("</head>");
	printf("<body>");
}

void end_page(void) {
	printf("</body>");
	printf("</html>");
}
