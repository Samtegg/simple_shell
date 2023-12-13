#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


/* this is for reading
 * /writing the buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* this is for, 
 * the command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* this is for, 
 * the convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* then reply 1 if,
 * to use system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - this i,s
 *  singly linked list
 * @num: tis is the numb field
 * @str: this is a string
 * @next: these are the points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - this part of the code contains 
  pseudo-arguements to pass into the function,
 *thus allowing uniform prototype for function pointer struct
 *@arg: this is a string that will be generated 
  from the getline containing the arguements
 *@argv: this is an array of strings that are generated from arg
 *@path: the string path for current command
 *@argc: this is the argument count
 *@line_count: this is the error count
 *@err_num: this is the error code for exit()s
 *@linecount_flag: if there is on count this line of input
 *@fname: this is the program filename
 *@env: this is the linked list local copy of the environ
 *@environ: the custom modified copy of environ from LL env
 *@history: this is the history node
 *@alias: this is the alias node
 *@env_changed: this will on if environ was changed
 *@status: this is the return status of the last exec'd command
 *@cmd_buf: this is the address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: the CMD_type ||, &&, ;
 *@readfd: this is the fd from which to read line input
 *@histcount: this is the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *dpath;
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

	char **cmd_buf; /* this pointer to cmd ; chain 
			   buffer, for memory mangement */
	int cmd_buf_type; /* this CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - this struct contains a builtin
 string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} dbuiltin_table;


/* 
 * just_shell_loop.c 
 * */
int hsh(info_t *, char **);
int dfind_builtin(info_t *);
void dfind_cmd(info_t *);
void dfork_cmd (info_t *);

/* 
 * just_parser.c 
 * */
int dis_cmd(info_t *, char *);
char *ddup_chars(char *, int, int);
char *dfind_path(info_t *, char *, char *);

/* 
 * just_loophsh.c 
 * */
int loophsh(char **);

/*
 * just_errors.c 
 * */
void _deputs(char *);
int _deputchar(char);
int _dputfd(char c, int fd);
int _dputsfd(char *str, int fd);

/*
 * just_string.c 
 * */
int _dstrlen(char *);
int _dstrcmp(char *, char *);
char *dstarts_with(const char *, const char *);
char *_dstrcat(char *, char *);

/*
 *  just_string1.c
 **/
char *_dstrcpy(char *, char *);
char *_dstrdup(const char *);
void _dputs(char *);
int _dputchar(char);

/* 
 * just_exits.c 
 * */
char *_dstrncpy(char *, char *, int);
char *_dstrncat(char *, char *, int);
char *_dstrchr(char *, char);

/* 
 * just_tokenizer.c 
 * */
char **dstrtow(char *, char *);
char **dstrtow2(char *, char);

/* 
 * just_realloc.c 
 * */
char *_dmemset(char *, char, unsigned int);
void dffree(char **);
void *_drealloc(void *, unsigned int, unsigned int);

/* 
 * just_memory.c 
 * */
int dbfree(void **);

/* just_atoi.c 
 * */
int dinteractive(info_t *);
int dis_delim(char, char *);
int _disalpha(int);
int _datoi(char *);

/* 
 * just_errors1.c 
 * */
int _derratoi(char *);
void dprint_error(info_t *, char *);
int dprint_d(int, int);
char *dconvert_number(long int, int, int);
void dremove_comments(char *);

/* 
 * just_builtin.c 
 * */
int _dmyexit(info_t *);
int _dmycd(info_t *);
int _dmyhelp(info_t *);

/* 
 * just_builtin1.c 
 * */
int _dmyhistory(info_t *);
int _dmyalias(info_t *);

/* 
 * just_getline.c 
 * */
ssize_t dget_input(info_t *);
int _dgetline(info_t *, char **, size_t *);
void dsigintHandler(int);

/* 
 * just_getinfo.c 
 * */
void dclear_info(info_t *);
void dset_info(info_t *, char **);
void dfree_info(info_t *, int);

/* 
 * just_environ.c 
 * */
char *_dgetenv(info_t *, const char *);
int _dmyenv(info_t *);
int _dmysetenv(info_t *);
int _dmyunsetenv(info_t *);
int dpopulate_env_list(info_t *);

/* 
 * just_getenv.c 
 * */
char **dget_environ(info_t *);
int _dunsetenv(info_t *, char *);
int _dsetenv(info_t *, char *, char *);

/* 
 * just_history.c 
 * */
char *dget_history_file(info_t *info);
int dwrite_history(info_t *info);
int dread_history(info_t *info);
int dbuild_history_list(info_t *info, char *buf, int linecount);
int drenumber_history(info_t *info);

/* 
 * just_lists.c 
 * */
list_t *dadd_node(list_t **, const char *, int);
list_t *dadd_node_end(list_t **, const char *, int);
size_t dprint_list_str(const list_t *);
int ddelete_node_at_index(list_t **, unsigned int);
void dfree_list(list_t **);

/* 
 * just_lists1.c 
 * */
size_t dlist_len(const list_t *);
char **dlist_to_strings(list_t *);
size_t dprint_list(const list_t *);
list_t *dnode_starts_with(list_t *, char *, char);
ssize_t dget_node_index(list_t *, list_t *);

/* 
 * just_vars.c 
 * */
int dis_chain(info_t *, char *, size_t *);
void dcheck_chain(info_t *, char *, size_t *, size_t, size_t);
int dreplace_alias(info_t *);
int dreplace_vars(info_t *);
int dreplace_string(char **, char *);

#endif
