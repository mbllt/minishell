/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:20:27 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/21 20:19:36 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define ERR_HOME "HOME not set"
# define ERR_MSG_CD "minishell: cd"
# define ERR_ERR "minishell: failed to print error message"
# define ERR_EXEC "minishell: error in exec"
# define ERR_COMM_NOT_FOUND "command not found"
# define ERR_MEM "a memory error occurred"
# define ERR_TOO_ARG "too many arguments"
# define ERR_SIGINT "Cannot catch sigint"
# define ERR_SIGQUIT "Cannot catch sigquit"
# define ERR_IDENT "not a valid identitifier"
# define ERR_REDIR "minishell: failed to perform redirection"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_NUM "numeric argument required"
# define ERR_PARSING 2

#endif
