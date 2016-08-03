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

void wrapper_set_bg(color_t& bg_color_)
{
    glClearColor(bg_color_.R(), bg_color_.G(), bg_color_.B(), 1.0f);
}

//Display callback
void display( void )
{
    //This clears the colorbuffer (current window)
    glClear(GL_COLOR_BUFFER_BIT);

#ifdef DEBUG_BASIC
    std::cout << "[Event]: Drawing on canvas " << '\n';
#endif
    canvas.draw();

    //Flush the framebuffer to the screen
    glutSwapBuffers();
}

//Reshape callback
void reshape( int w, int h )
{
#ifdef DEBUG_BASIC
    std::cout << "[Event]: Reshape to " << w << " X " << h << '\n';
#endif
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

    canvas.set_size(w, h);

    glutPostRedisplay();
}

//Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
    // x and y are OpenCV not OpenGL
#ifdef DEBUG_BASIC
    std::cout << "[Event]: Key Press: " << key << '\n';
#endif
#ifndef ANY_CASE
    key = std::toupper(key);
#endif
    switch(key)
    {
    case 27:   //Exit on pressing escape
        exit(0);
        break;
    case 'C':  // clear canvas with current back ground color
        canvas.clear();
        break;
    case 'N':  // new canvas
        // @TODO: the background color for the canvas as input from the terminal or an initial config file
        break;
    case 'S':  // save
        // @TODO
        break;
    case 'L':  // load, input filename on the terminal
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
    case 'F':  // Fill the current triangle with the current fill color
        // @TODO: can require
        // a click in the interior of the triangle to initiate a
        // fill, depending on the fill algorithm used.
        break;
    case 'G':  // change current fill color, input color from terminal
        // @TODO
        break;
    case 'H':  // change current pen color, input color from terminal
        // @TODO
        break;
    case 'I':  // change current backgound color, input color from terminal
        // @TODO
        break;
    case 'J':  // change pen width, input thickness from terminal
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
#ifdef DEBUG_BASIC
    std::cout << "[Event]: Mouse Press: ";
#endif
        if (GLUT_LEFT_BUTTON == button)
        {
#ifdef DEBUG_BASIC
            std::cout << "left" << '\n';
#endif
            // left mouse button is pressed
            left_m = true;
            right_m = false;
        }
        else if (GLUT_RIGHT_BUTTON == button)
        {
#ifdef DEBUG_BASIC
            std::cout << "right" << '\n';
#endif
            // right mouse button is pressed
            right_m = true;
            left_m = false;
        }
    }
    else if (GLUT_UP == state)
    {
#ifdef DEBUG_BASIC
    std::cout << "[Event]: Mouse Click: ";
#endif
        if (GLUT_LEFT_BUTTON == button && true == left_m)
        {
#ifdef DEBUG_BASIC
            std::cout << "left\t" << x << '\t' << y << '\n';
#endif
            // left mouse button is clicked
            canvas.left_click(x, y);
        }
        else if (GLUT_RIGHT_BUTTON == button && true == right_m)
        {
#ifdef DEBUG_BASIC
            std::cout << "right\t" << x << '\t' << y << '\n';
#endif
            // right mouse button is clicked
            canvas.right_click(x, y);
        }
        left_m = right_m = false;
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
