/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:33:27 by slakner           #+#    #+#             */
/*   Updated: 2022/11/30 21:22:20 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H


t_token	*token_new(char *str);
void	delete(t_token *del_elem);
void	tappend(t_token **list, t_token *new_elem);
t_token	*tlist_start(t_token *token);
t_token	*tlist_end(t_token *token);
void	print_list(t_token *tklist);

int		lstsize(t_dlist *lst);
void	lstadd_back(t_dlist **lst, t_dlist *new);
void	lstadd_front(t_dlist **lst, t_dlist *new);
t_dlist	*lstlast(t_dlist *lst);
t_dlist	*lstnew(t_kval *content);
void	lstdel_elem(t_dlist **lst, t_dlist *elem);

#endif
