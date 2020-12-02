/*
 Author: Shyam Patel
 Class: ECE4122
 Last Date Modified: 10/28/20
 Description:
 This header file will make it easier to run on either windows, linux, or macos.
 */

#ifndef openGLheader_h
#define openGLheader_h

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#endif /* openGLheader_h */
