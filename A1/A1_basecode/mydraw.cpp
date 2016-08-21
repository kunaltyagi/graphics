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
int win_width = 256;   ///< Window width
int win_height = 256;  ///<Window height
bool left_m = false;   ///< is left mouse button active
bool right_m = false;  ///< is right mouse button active
canvas_t canvas(color_t(1,1,1), color_t(0,0,0), point_t(win_width, win_height));

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

color_t read_color()
{
    std::cout << "Enter normalized R G B color: ";
    float r, g, b;
    std::cin >> r >> g >> b;
    return color_t(r, g, b);
}

std::string read_filename()
{
    std::cout << "Enter filename: ";
    std::string line;
    std::getline(std::cin, line);
    if (line == "")
    {
        line = "default.draw";
    }
    return line;
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
        display();
        break;
    case 'N':  // new canvas
        // @TODO: the background color for the canvas as input from the terminal or an initial config file
        break;
    case 'S':  // save
        std::cout << "[Save] ";
        canvas.save(read_filename());
        break;
    case 'L':  // load, input filename on the terminal
        std::cout << "[Load] ";
        // @TODO
        canvas.load(read_filename());
        break;
    case '0':  // debug point mode
        canvas.set_mode(canvas_t::POINT);
        break;
    case '1':  // line drawing mode
        // Left clicks add points, and a line is drawn between two
        // successively clicked points, with the current pen. Right click
        // removes the last added point, and if a line is left incomplete
        // by removing the point, remove the line too.
        canvas.set_mode(canvas_t::LINE);
        break;
    case '2':  // triangle drawing mode
        // Left clicks add vertices. Three successively clicked vertices
        // form a triangle. A right click removes the last added point,
        // and if a triangle is left incomplete by removing the
        // point, the triangle is also removed.
        canvas.set_mode(canvas_t::TRIANGLE);
        break;
    case 'F':  // Fill the current triangle with the current fill color
        // can require a click in the interior of the triangle to initiate a
        // fill, depending on the fill algorithm used.
        std::cout << "[Fill] Click on point to initiate filling";
        canvas.set_mode(canvas_t::NONE);
        break;
    case 'G':  // change current fill color, input color from terminal
        std::cout << "[Fill] ";
        canvas.set_fill_color(read_color());
        break;
    case 'H':  // change current pen color, input color from terminal
        std::cout << "[Foreground] ";
        canvas.set_pen_color(read_color());
        break;
    case 'I':  // change current backgound color, input color from terminal
        std::cout << "[Background] ";
        canvas.set_bg(read_color());
        break;
    case 'J':  // change pen width, input thickness from terminal
        float t;
        std::cout << "[Pen] Enter the thickness: ";
        std::cin >> t;
        canvas.set_pen_width(t);
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
