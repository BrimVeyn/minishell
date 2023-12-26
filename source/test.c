#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *cwd;
    char buffer[1024];

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd != NULL) {
        printf("Le répertoire de travail courant est : %s\n", cwd);
    } else {
        perror("getcwd a échoué");
        return 1;
    }

    return 0;
}
