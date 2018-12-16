/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:38:54 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/14 20:01:46 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static	void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

static void	main_loop(t_core *core)
{
	while (!glfwWindowShouldClose(core->window))
	{
		processInput(core->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(core->program_id);
		glBindVertexArray(core->vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(core->window);
		glfwPollEvents();
	}
}

int		main(void)
{
	t_core	core;

	init(&core);
	main_loop(&core);

	glDeleteVertexArrays(1, &core.vao);
	glDeleteBuffers(1, &core.vbo);

	glfwTerminate();
	return (0);
}