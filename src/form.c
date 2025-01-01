#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/form.h"
#include "../header/url_enc_dec.h"

int main(int argc, char **argv, char **envp) {
	header("text/html");
	start_page("Usando CGI action");

	char *qEnv;

	if ((qEnv = getenv("QUERY_STRING"))) {
		char buffer[strlen(qEnv) + 1];
		strncpy(buffer, qEnv, strlen(qEnv) + 1);

		char name[MAX_SIZE];
		char value[MAX_SIZE];
		PAIR *pair = (PAIR *)malloc(MAX_SIZE * sizeof(*pair));

		int param_count = 0;

		char *token = strtok(buffer, "&");
		while (token) {
			if (!(param_count % 2)) {
				pair = realloc(pair, (param_count + MAX_SIZE) * sizeof(*pair));
			}

			sscanf(token, "%[^'=']=%s", name, value);

            char *value_decode = (char *)malloc(sizeof (*value) * 2);
            decode(value, value_decode);

			strncpy(pair[param_count].value, value_decode, MAX_SIZE);
			strncpy(pair[param_count].name, name, MAX_SIZE);

			++param_count;

			token = strtok(NULL, "&");

			free(value_decode);
		}

		for (int i = 0; i < param_count; ++i) {
			printf("<p>%s - %s</p>", pair[i].name, pair[i].value);
		}
		free(pair);
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
