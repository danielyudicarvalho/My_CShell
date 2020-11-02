
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char builts[] = {
  "cd",
  "pwd",
  "history"
};


int num_built = sizeof(builts)/sizeof(char *);

int cd(char **args)
{
  chdir(args[1]);
  return 1;
}


int pwd()
{
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL){
        fprintf(stdout, "%s\n", cwd);
    }
    else {
        printf("getcwd() error!\n");
    }
    
    return 1;
}

int history(char **history, int count)
{
  for(int i=0;i<count;i++)
  {
    printf("%s\n",history[i]);
  }
}

int check_in_builts(char **args)
{
  

  if(args[0] ==NULL)
  {
    return 0;
  }

  for(int i = 0;i<num_built;i++)
  {
    if(strcmp(args[0],builts[i])==0)
    {
      return 1;
    }
  }

  return 0;
}

char *read_line(void)
{
  char c;
  char *buffer  = malloc(sizeof(char) * 1024);
  int i = 0;
  

  while(c!='\n')
  {
    c = getchar();
    buffer[i] = c;
    i++;
  }

  return buffer;


}

char **create_command(char *line)
{ 
  char *arg;
  char **args = malloc(sizeof(char)*1024);
  int i = 0;

  arg = strtok(line,"\t\r\n\a");

  while(arg != NULL)
  {
    args[i] = arg;
    i++;
    arg = strtok(NULL,"\t\r\n\a");

  }

  args[i] = NULL;
  return args;

}


int main(int argc, char **args)
{
  char *line = read_line();
  char  **command = create_command(line);
  int flag = 1;
  char **history = malloc(sizeof(char)*1024);
  int count = 0;

  while(flag)
  {
    if(command[0]!= NULL)
    {
      if(check_in_builts(command)) 
      {
        printf("OK");
      };
    };
  };
  
}