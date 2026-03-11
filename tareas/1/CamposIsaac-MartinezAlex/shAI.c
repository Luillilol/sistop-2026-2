#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <signal.h>

char **parsearEntrada(char *);

void sigint_handler(int);
void configurarHijoSigintStruct();
void configurarInicioSigintStruct();
void getCWD(char *, size_t);

int main(void){
  char *entrada;
  char **comando;
  pid_t pid_hijo;
  int status;
  char cwd[BUFSIZ]; /*Para mostrar directorio*/
  char prompt[BUFSIZ];

  configurarInicioSigintStruct();

	while(1){

	  getCWD(cwd,sizeof(cwd));
	  snprintf(prompt, sizeof(prompt), "%s ♥ ", cwd);
	  entrada = readline(prompt);
 
          if(entrada == NULL){
		printf("byeeeeee\n");
		exit(0);
	  }


	  comando = parsearEntrada(entrada);
	
	  if(comando[0]==NULL){
		free(entrada);
		free(comando);
		continue;
	  }
	
	  if(strcmp(comando[0],"exit") == 0){
	  	free(entrada);
		free(comando);
		printf("byeeee\n");
		exit(0);
	  }

	  if(strcmp(comando[0],"cd") == 0){ /*Necesario para cd*/
		if(chdir(comando[1]) < 0){
			perror(comando[1]);
		}


		/*Si da tiempo agregar funcionalidad para HOME*/
		continue; /*Salta fork*/
	  }

	  
	  pid_hijo = fork();
	  
	  if(pid_hijo < 0){
		perror("Error al ejecutar fork()");
		exit(1);
	  }


	  if(pid_hijo == 0){
		configurarHijoSigintStruct();
		if(execvp(comando[0],comando) < 0){
			perror(comando[0]);
			exit(1);
		}
	  }else{
		waitpid(pid_hijo, &status, WUNTRACED);
	}

	  free(entrada);
	  free(comando);

	}
  return 0;
}

char **parsearEntrada(char *entrada){
	char **comando = malloc(10 * sizeof(char *));
	if(comando == NULL){
		perror("Error al alocar memoria");
		exit(1);
	}
	char *divisor = " ";
	char *parseado;
	int indice = 0;

	parseado  = strtok(entrada, divisor);

	while(parseado != NULL){
		comando[indice] = parseado;
		indice++;

		parseado = strtok(NULL, divisor);
	}

	comando[indice] = NULL; /*Necesario para execvp()*/
	return comando;
}



void configurarInicioSigintStruct(){
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);
}


void configurarHijoSigintStruct(){
	struct sigaction s_hijo;
        s_hijo.sa_handler = sigint_handler;
        sigemptyset(&s_hijo.sa_mask);
        s_hijo.sa_flags = SA_RESTART;
        sigaction(SIGINT, &s_hijo, NULL);
}

void sigint_handler(int sig){
    printf("\n");
    rl_on_new_line();
    rl_replace_line("",0);
    rl_redisplay();
}

void getCWD(char *buf, size_t size){
	if(getcwd(buf, size) == NULL){
	 perror("getcwd()");
	}
}


