/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:51:20 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/16 17:10:17 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "../library/libft/libft.h"

typedef struct		s_model
{
	GLfloat			*start;
	
	GLfloat			*vertices;
	size_t			vert_len;

	GLuint			*faces;
	size_t			face_len;
}					t_model;

typedef struct		s_core
{
	GLFWwindow		*window;
	GLuint			program_id;
	GLuint			vao;
	GLuint			vbo;
}					t_core;

GLuint		load_shaders(const char *vertex_file_path, const char *fragment_file_path);
void		init(t_core *core);
GLFWwindow	*init_window();

#endif