#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @argc: the argument count
* @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *info, char **av)
int find_builtin(info_t *info)
void find_cmd(info_t *info)
void fork_cmd(info_t *info)

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void eputs(char *str)
int eputchar(char c)
int putfd(char c, int fd)
int putsfd(char *str, int fd)

/* toem_string.c */
int _strlen(char *s)
int _strcmp(char *s1, char *s2)
char *starts_with(const char *haystack, const char *needle)
char *_strcat(char *dest, char *src)

/* toem_string1.c */
char *_strcpy(char *dest, char *src)
char *_strdup(const char *str)
void _puts(char *str)
int _putchar(char c)


/* toem_exits.c */
char *strncpy(char *destination, char *source, int n)
char *strncat(char *destination, char *source, int n)
char *strchr(char *string, char character)


/* toem_tokenizer.c */
char **strtow(char *str, char *d)
char **strtow2(char *str, char d)


/* toem_realloc.c */
char *_memset(char *s, char b, unsigned int n)
void ffree(char **pp)
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)

/* toem_memory.c */
int bfree(void **ptr_addr);

/* toem_atoi.c */
int isInteractive(info_t *shellInfo);
int isDelimiter(char c, char *delim);
int isAlpha(int c);
int customAtoi(char *s);

/* toem_errors1.c */
int errAtoi(char *s)
void printError(ShellInfo *shellInfo, char *errorMsg)
int printDecimal(int input, int fd)
char *convertNumber(long int num, int base, int flags)
void removeComments(char *buf)

/* toem_builtin.c */
int myExit(ShellInfo *shellInfo)
int myCd(ShellInfo *shellInfo)
int myHelp(ShellInfo *shellInfo)

/* toem_builtin1.c */
int myHistory(ShellInfo *shellInfo)
int unsetAlias(ShellInfo *shellInfo, char *str)
int setAlias(ShellInfo *shellInfo, char *str)
int printAlias(ListNode *node)
int myAlias(ShellInfo *shellInfo)

/*toem_getline.c */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
ssize_t readBuffer(info_t *info, char *buffer, size_t *x)
int _getline(info_t *info, char **ptr, size_t *length)
void sigintHandler(__attribute__((unused))int sigNum)

/* toem_getinfo.c */
void initializeInfo(info_t *info)
void setupInfo(info_t *info, char **av)
void releaseInfo(info_t *info, int all)

/* toem_environ.c */
int myEnv(ShellInfo *shellInfo)
char *getEnv(ShellInfo *shellInfo, const char *name)
int mySetEnv(ShellInfo *shellInfo)
int myUnsetEnv(ShellInfo *shellInfo)
int populateEnvList(ShellInfo *shellInfo)

/* toem_getenv.c */
char **obtainEnvironment(info_t *info)
int removeEnvironmentVariable(info_t *info, char *variable)
int setEnvironmentVariable(info_t *info, char *variable, char *value)

/* toem_history.c */
char *getHistoryFile(info_t *info)
int writeHistory(info_t *info)
int readHistory(info_t *info)
int buildHistoryList(info_t *info, char *buf, int y)
int renumberHistory(info_t *info)

/* toem_lists.c */
list_t *add_node(list_t **head, const char *str, int num)
list_t *add_node_end(list_t **head, const char *str, int num)
size_t print_list_str(const list_t *h)
int delete_node_at_index(list_t **head, unsigned int index)
void free_list(list_t **head_ptr)

/* toem_lists1.c */
size_t listLen(const list_t *h)
char **listToStrings(list_t *head)
size_t printList(const list_t *h)
list_t *nodeStartsWith(list_t *node, char *prefix, char c)
ssize_t getNodeIndex(list_t *head, list_t *node)

/* toem_vars.c */
int is_chain(info_t *info, char *buf, size_t *p)
void check_chain(info_t *info, char *buf, size_t *p, size_t start, size_t len)
int replace_alias(info_t *info)
int replace_vars(info_t *info)
int replace_string(char **old, char *new)

#endif
