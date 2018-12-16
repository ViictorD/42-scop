/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:26:31 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/12/14 20:33:23 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "scop.h"

GLuint load_shaders(const char *vertex_file_path, const char *fragment_file_path)
{
	struct stat	buff;

	// Read the Vertex Shader code from the file
	if (stat(vertex_file_path, &buff) == -1)
	{
		ft_fputstr("Invalid vertex path\n", 2);
		exit(1);
	}
	
	char vertexstr[buff.st_size + 1];
	int fd;

	if ((fd = open(vertex_file_path, O_RDONLY)) == -1)
	{
		ft_fputstr("Can't open shader vertex\n", 2);
		exit(1);
	}

	read(fd, vertexstr, buff.st_size);
	vertexstr[buff.st_size] = 0;

	close(fd);

	if (stat(fragment_file_path, &buff) == -1)
	{
		ft_fputstr("Invalid vertex path\n", 2);
		exit(1);
	}
	
	char fragmentstr[buff.st_size + 1];

	if ((fd = open(fragment_file_path, O_RDONLY)) == -1)
	{
		ft_fputstr("Can't open shader vertex\n", 2);
		exit(1);
	}

	read(fd, fragmentstr, buff.st_size);
	fragmentstr[buff.st_size] = 0;

	close(fd);

	// -----------------------

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	char infoLog[512];

	// Compile Vertex Shader
	ft_putstr("Compiling shader\n");
	char const * VertexSourcePointer = vertexstr;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
		ft_fputendl(infoLog, 2);
		exit(1);
	}

	// Compile Fragment Shader
	ft_putstr("Compiling shader\n");
	char const * FragmentSourcePointer = fragmentstr;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if ( InfoLogLength > 0 )
	{
		glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
		ft_fputendl(infoLog, 2);
		exit(1);
	}

	// Link the program
	ft_putstr("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glBindFragDataLocation(ProgramID, 0, "FragColor");
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	
	if ( InfoLogLength > 0 )
	{
		glGetShaderInfoLog(ProgramID, 512, NULL, infoLog);
		ft_fputendl(infoLog, 2);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return (ProgramID);
}