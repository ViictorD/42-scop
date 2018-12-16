/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:35:33 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/14 19:41:06 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLFWwindow	*init_window()
{
	GLFWwindow	*window;

	if (!glfwInit())
		ft_exiterror("Unable to init glfw !", 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(1280, 720, "Hello world", NULL, NULL);
	if (!window)
		ft_exiterror("Unable to init glfw window !", 2);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 1280, 720);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		ft_exiterror("Unable to init glfw window !", 2);
	glfwSwapInterval(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	return (window);
}
