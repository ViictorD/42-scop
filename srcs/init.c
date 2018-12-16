/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:32:15 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/16 14:15:48 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	init_core(t_core *core)
{
	core->window = NULL;
	core->program_id = 0;
	core->vao = 0;
	core->vbo = 0;
}

void		init(t_core *core)
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	// left
		0.5f, -0.5f, 0.0f,	// right
		0.0f, 0.5f, 0.0f	// top
	}; 

	init_core(core);
	core->window = init_window();
	core->program_id = load_shaders("../srcs/file.vert", "../srcs/file.frag");
	init_model(core);


	glGenVertexArrays(1, &core->vao);
	glGenBuffers(1, &core->vbo);
	glBindVertexArray(core->vao);

	glBindBuffer(GL_ARRAY_BUFFER, core->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 
}