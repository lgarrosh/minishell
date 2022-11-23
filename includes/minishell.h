/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:37:38 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:09 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "struct.h"
# include <limits.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>

//lexer
int				_lx_is_special(const char c);
int				_lx_case_word(t_llist *tokens, const char *line,
					unsigned long i, unsigned long *t);
int				_lx_case_metachar(t_llist *tokens, const char *line,
					unsigned long i, unsigned long *t);
int				_lx_case_quotes(t_llist *tokens, const char *line,
					unsigned long i, unsigned long *t);
int				lexer(t_llist *tokens, const char *line);
//list
t_llist			*llist_new(t_llist_key_comparator_ptr key_cmpr,
					t_llist_key_destructor_ptr key_dstr,
					t_llist_val_destructor_ptr val_dstr);
void			llist_free(t_llist *list);
int				llist_set(t_llist *list, void *key, void *new_val);
int				llist_push(t_llist *list, void *key, void *val);
int				llist_del(t_llist *list, const void *key);
int				llist_haskey(t_llist *list, const void *key);
void			*llist_getval(t_llist *list, const void *key);
void			llist_free_wrapper(void *llist);
int				llist_int_kcmp(const void *k1, const void *k2);
int				llist_str_kcmp(const void *k1, const void *k2);
t_group			*ft_group_new(int type);
void			ft_group_free(void *group);

//Environment
int				ft_parse_envp(t_llist *list, char *envp[]);
char			**ft_compose_envp(t_llist *list);
void			handler(int sig);
void			handler_term(t_info *info);
void			handler_in_executor(int sig);
void			handler_in_heredoc(int sig);
int				prs_exp_field_ret2(t_llist *str);
int				prs_exp_field_ret(t_llist *str);
int				builtin_handler1(char *pwdcopy, char *pathcopy);
void			not_valid_handler(char *a, char *b);
pid_t			executor(t_group *cmds, t_info *info);
pid_t			pipeline(t_group *cmds, t_info *info);
int				ft_common(t_group *cmds, t_info *info);
int				ft_subshell(t_group *cmds, t_info *info);
int				ft_acces(t_ll_elem *cmd, char *path, char **filepath);
int				create_argv(t_ll_elem *cmd, char ***args, char *path);
int				check_if_builtins(t_ll_elem *cmd, t_info *info);
int				ft_callbuiltin(int idx, t_ll_elem *cmd, t_info *info, t_fd *fd);
int				ft_execsubshell(t_ll_elem *cmd, t_info *info, t_fd *fd);
int				ft_execcommon(t_ll_elem *cmd, t_info *info, t_fd *fd, int mode);
int				ft_execve(t_ll_elem *cmd, t_info *info, t_fd *fd);
int				create_heredoc(t_cmd_info *c_info, t_llist *files);
void			prs_only_empty_var(t_llist *str, char **word, t_expi *ei);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_initial(t_info *info, char *envp[]);
int				ft_destroy(t_info *info);
//Built-ins
int				ft_echo(t_llist *args, t_info *info);
int				ft_cd(t_llist *args, t_info *info);
int				ft_pwd(t_llist *args, t_info *info);
int				ft_export(t_llist *args, t_info *info);
int				ft_unset(t_llist *args, t_info *info);
int				ft_env(t_llist *args, t_info *info);
int				ft_exit(t_llist *args, t_info *info);
//parser
int				parse(t_llist *tokens, t_info *info);
t_llist			*prs_expand(t_llist *group, t_info *info);
int				prs_logexec(t_llist *groups, t_info *info);
int				prs_extract_var(const char *s, t_info *info,
					char **envpvar_ptr, unsigned int *j);
t_chunk_info	*prs_chunk_info_new(unsigned int s, unsigned int e);
int				prs_is_delim_token(void *tok_key);
int				prs_handle_group0(t_llist *groups, t_llist *group,
					t_ll_elem *ptr, long type);
int				prs_handle_group1(t_llist *group);
int				prs_dstr(t_llist *groups);
int				prs_field_exp_collect_chunks(char *s, t_info *info,
					t_llist *chunks, unsigned int *size);
int				prs_update_g_exit_str(t_info *info);
int				prs_alloc_ci(t_chunk_info **ci,
					unsigned int i, unsigned int j);
int				prs_field_expansion_prep(t_llist *str, t_info *info,
					t_llist *chunks, t_expi *ei);
int				prs_fecc_return(t_chunk_info *ci);
t_llist			*prs_asterisk_expansion(const char *word);
int				prs_expandable(void *key);
t_llist			*prs_asterisk_expansion_pwd(const char *word);
int				prs_field_expansion_free(t_llist *chunks, char **word);
int				prs_handle_subsh_token(t_ll_elem *ptr, t_llist *expanded);
int				prs_field_expansion_copy(t_llist *chunks, char *word);
void			prs_pattern_match_while(const char *pattern,
					const char *str, char **dp);
int				prs_aep_bool(struct dirent *dirf, const char *word);
int				prs_asterisk_pattern_matches(const char *pattern,
					const char *str);
void			prs_token_handle_loop1(t_llist **str, t_ll_elem **ptr);
void			prs_token_handle_loop2(t_llist *expanded,
					char *word, t_llist *words);
t_ll_elem		*prs_next_token(t_ll_elem *curr);
int				prs_handle_dstr(t_group *group, t_llist *expanded);
int				prs_handle_heredoc(t_group *cmds);
void			prs_waitall(int pid, int *sig);
int				prs_prepare_group(t_llist *expanded, t_group *cmds);
int				prs_group_pipe(t_llist *expanded, t_llist *cmds);
int				prs_group_cmd(t_ll_elem *h, t_llist *cmds);
int				prs_logexec_bonus(t_ll_elem *ptr, int *expect);
void			prs_alloc_cmd_info(t_cmd_info **info);
int				prs_group_cmd_ret1(t_cmd_info *info, t_llist *args);
int				prs_group_cmd_ret2(t_cmd_info *info, t_llist *args);
int				prs_group_cmd_ret3(t_cmd_info *info, t_llist *args);
//utils
int				ft_strlen(const char *s);
char			*ft_strcpy(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			**ft_strsplit(const char *s, const char *delim);
int				ft_strcontains(const char *s, const char c);
int				ft_strslice(const char *s, const char *delim,
					char **a, char **b);
void			*nh_trop(int a, void *b, void *c);
char			**_ft_strdestroy2(char **str2, int j);
char			*ft_strjoin2(const char *s1, const char *s2, char d, char isd);
int				ft_isspace(char c);
char			*ft_substr(const char *s, unsigned long begin,
					unsigned long count);
int				ft_isalnum(char c);
void			*ft_free_char2dem(char **arr, int m);
char			**ft_malloc_char2dem(int m, int n);
int				ft_error(int ret, const char *msg, char liberr, int g_e);
char			*ft_uitoa(unsigned int n);
int				ft_abs(int n);
char			*ft_itoa(int n);
int				remap_fds(int in, int out);
int				get_in_fd(t_cmd_info *c_info);
int				get_out_fd(t_cmd_info *c_info);
int				ft_atoi(const char *s, int *n);
int				ft_is_valid_id(const char *s);

#endif