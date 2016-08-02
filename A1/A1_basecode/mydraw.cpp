/*******************************
 *
 * CS475m Assignment 1 Basecode
 *
 * Parag Chaudhuri, 2016
 *
 *******************************/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include "mydraw_class.hpp"

// Global variables
int win_width = 512;   ///< Window width
int win_height = 512;  ///<Window height
bool left_m = false;   ///< is left mouse button active
bool right_m = false;  ///< is right mouse button active
canvas_t canvas;

//Display callback
void display( void )
{
    //This clears the colorbuffer (current window)
    glClear(GL_COLOR_BUFFER_BIT);

    //Flush the framebuffer to the screen
    glutSwapBuffers();
}

//Reshape callback
void reshape( int w, int h )
{
    if (0 == h)
    {
        h = 1;
    }
    if (0 == w)
    {
        w = 1;
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1. );
    glViewport( 0, 0, w, h );

    win_width = w;
    win_height = h;

    glutPostRedisplay();
}

//Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
    case 27:   //Exit on pressing escape
        exit(0);
        break;
    case 'C':
    case 'c':  // clear canvas with current back ground color
        // @TODO: clear the array with the required color and draw
        // it to the screen.
        break;
    case 'N':
    case 'n':  // new canvas
        // @TODO: the background color for the canvas as input from the terminal or an initial config file
        break;
    case 'S':
    case 's':  // save
        // @TODO
        break;
    case 'L':
    case 'l':  // load, input filename on the terminal
        // @TODO
        break;
    case '1':  // line drawing mode
        // @TODO: Left clicks add points, and a line is
        // drawn between two successively clicked points, with the
        // current pen.
        // Right click removes the last added point, and if a line
        // is left incomplete
        // by removing the point, remove the line too.
        break;
    case '2':  // triangle drawing mode
        // @TODO: Left clicks add vertices. Three
        // successively clicked vertices form a triangle. A right
        // click removes the
        // last added point, and if a triangle is left incomplete
        // by removing the
        // point, the triangle is also removed.
        break;
    case 'F':
    case 'f':  // Fill the current triangle with the current fill color
        // @TODO: can require
        // a click in the interior of the triangle to initiate a
        // fill, depending on the fill algorithm used.
        break;
    case 'G':
    case 'g':  // change current fill color, input color from terminal
        // @TODO
        break;
    case 'H':
    case 'h':  // change current pen color, input color from terminal
        // @TODO
        break;
    case 'I':
    case 'i':  // change current backgound color, input color from terminal
        // @TODO
        break;
    case 'J':
    case 'j':  // change pen width, input thickness from terminal
        // @TODO
        break;
    default:   //Ignore all other keypresses
        break;
    }
}

//Mouse callback
void mouse(int button, int state, int x, int y)
{
    if (GLUT_DOWN == state)
    {
        if (GLUT_LEFT_BUTTON == button)
        {
            // left mouse button is pressed
            left_m = true;
            right_m = false;
        }
        else if (GLUT_RIGHT_BUTTON == button)
        {
            // right mouse button is pressed
            right_m = true;
            left_m = false;
        }
    }
    else if (GLUT_UP == state)
    {
        if (GLUT_LEFT_BUTTON == button && true == left_m)
        {
            // left mouse button is clicked
            canvas.left_click();
            left_m = false;
        }
        else if (GLUT_RIGHT_BUTTON == button && true == right_m)
        {
            // right mouse button is clicked
            canvas.right_click();
            right_m = false;
        }
    }
    glutPostRedisplay();
}


int main (int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( win_width, win_height );

    //Open a GLUT window
    glutCreateWindow( "MyDraw" );

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );

    glutMainLoop();
}
