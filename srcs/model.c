/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:04:06 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/16 17:58:39 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include "scop.h"

static void	parse_line(t_model *model, char *str)
{
	char *tab;

	if (!(tab = ft_strsplit(str, ' ')))
		ft_exiterror("Split error", 2);
	if (!tab[0] || !tab[1] || !tab[2] || !tab[3])
	{
		ft_strdelpp(&tab);
		return ;
	}
	if (tab[0] == 'v' && tab[1] && tab[1] == ' ')
	{
		model->vertices[model->vert_len++] = atof(tab[1]);
		model->vertices[model->vert_len++] = atof(tab[2]);
		model->vertices[model->vert_len++] = atof(tab[3]);
	}
	else if (tab[0] = 'f')
	{
		model->faces[model->face_len++] = atoi(tab[1]); // PRB ICI si pas int
		model->faces[model->face_len++] = atoi(tab[2]);
		model->faces[model->face_len++] = atoi(tab[3]);
		if (tab[4])
			model->faces[model->face_len++] = atoi(tab[4]);
	}
	ft_strdelpp(&tab);
}

static void	init_model_struct(t_model *model, size_t len)
{
	if (!(model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * (model->vert_len * 3))))
		ft_exiterror("Malloc failed.", 2);
	if (!(model->faces = (GLuint*)malloc(sizeof(GLuint) * (model->face_len * 4))))
		ft_exiterror("Malloc failed.", 2);
	model->vert_len = 0;
	model->face_len = 0;
}

static sie_t	count_line_obj(char **tab, char c)
{
	size_t		i;
	size_t		count;

	count = 0;
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == c)
			++count;
	}
	return (count);
}

static void	parse_model(t_model *model, char *path)
{
	int		fd;
	char	*str;
	char	**file;
	struct stat	buff;

	if ((fd = open(path, O_RDONLY)) == -1)
		ft_exiterror("Model file open failed", 2);
	if ((fstat(fd, &buff)) == -1)
		ft_exiterror("Stat open failed", 2);
	init_model_struct(model, buff.st_size);
	if (!(str = (char*)malloc(buff.st_size)))
		ft_exiterror("Malloc failed", 2);
	if (read(fd, str, buff.st_size) == -1)
		ft_exiterror("Model file read failed", 2);
	close(fd);
	if (!(file = ft_strsplit(str, '\n')))
		ft_exiterror("Model file split failed", 2);
	free(file);
	model->vert_len = count_line_obj(tab, 'v');
	model->face_len = count_line_obj(tab, 'f');
	init_model_struct(model);
	fd = -1;
	while (file[++fd])
		parse_line(model, file[fd]);

}

void	init_model(char *model_path, t_core *core)
{
	t_model	model;

	parse_model(model_path, &model);

}