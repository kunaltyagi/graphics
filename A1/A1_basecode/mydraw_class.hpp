#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_

#ifdef DEBUG
#include <iostream>
#endif

#include <vector>
#include <tuple>
#include <memory>
#include <iterator>

#include <GL/glut.h>

/**
 * @class color_t
 * @brief Stores the Red, Green and Blue components of a color
 * @detail Each component is normalized between 0 and 1
 *         used to represent current drawing color, background
 *         color, and fill colors
 */
class color_t
{
  private:
    float _r, _g, _b; ///< red, green and blue normalized components of color
  public:
    color_t();
    color_t(const float r_, const float g_, const float b_);

    void set(const float r_, const float g_, const float b_);
    float R(void);
    float G(void);
    float B(void);
};

/**
 * @class pen_t
 * @brief Draws colored lines of variable thickness
 * @detail Has 2 modes: DRAW, ERASER, (default mode: DRAW)
 *         In erase mode, it draws with color of background
 *         (default color: WHITE)
 *         (default thickness: 1)
 */
class pen_t
{
  public:
    enum class mode: bool { DRAW, ERASER };
    pen_t();
    pen_t(int t_, color_t color_, mode mode_);
    void set_color(color_t color_);
    void set_thickness(int t_);
    void set_mode(mode mode_);
    void set(int t_, color_t color_, mode mode_);
  private:
    int _t;          ///< thickness
    color_t _color;  ///< color of the pen
    mode _mode;      ///< mode of drawing
    // bg color??
};

class canvas_t;
/**
 * @class point_t
 * @brief contains the X and Y coordinates of a point
 * @detail can plot the point (X, Y) on the canvas
 *         (default point: (0, 0))
 */
class point_t
{
private:
    int _x, _y;
public:
    point_t();
    point_t(int x_, int y_);
    int X(void);
    int Y(void);
    void X(int x_);
    void Y(int y_);
    void set(int x_, int y_);
    void draw(color_t* color_, canvas_t* canvas_);
};

/**
 * @class fill_t
 * @brief contains a solid fill color
 * @detail The entire fill region is filled with one color
 *         (default fill: WHITE)
 *         (default bg color: BLACK)
 *         (default algo: NONE)
 */
class fill_t
{
  private:
    color_t _fill;  ///< color to be filled
  public:
    fill_t();
    fill_t(color_t color_);
    void draw(color_t* color_, point_t* point_, canvas_t* canvas_);
    void draw(color_t* fill_color_, color_t* edge_color_, canvas_t* canvas_);
    void set_color(color_t color_);
};

/**
 * @class object_t
 * @brief base class for all objects like line/triangle
 */
/*
class object_t
{
  public:
    object_t();
    object_t(point_t* point_, int n);
    void set(point_t* point_, int n_);
    virtual void draw(color_t* color_, canvas_t* canvas_) = 0;
  protected:
    point_t* _vertice;
    int _len;
};
*/

/**
 * @class line_t
 * @brief contains the end points of a line
 * @detail draws line using integer Bresenham in all octants with
 *         the current color using the draw method of point_t
 */
/*
class line_t: public object_t
{
  public:
    line_t();
    line_t(point_t* point_);
    line_t(point_t start_, point_t end_);
    void set(point_t start_, point_t end);
    void set(point_t* point_);
    void draw(color_t* color_, canvas_t* canvas_);
};
*/

/**
 * @class triangle_t
 * @brief contains the vertices and border color of a triangle
 * @detail draws triangle using draw method of line_t and fill
 *         function on fill_t
 */
/*
class triangle_t: public object_t
{
  public:
    triangle_t();
    triangle_t(point_t* vertice_, color_t border_);
    void set_vertices(point_t one_, point_t two_, point_t three_);
    void set(point_t* vertice_);
    void set_border(color_t border_);
    void draw(color_t* fill_color_, canvas_t* canvas_);
  private:
    color_t _border;
};
*/

/**
 * @class drawing_t
 * @brief contains a list of all lines/triangles in a drawing
 */
/*
class drawing_t
{
  public:
    drawing_t();
    void add(std::shared_ptr<object_t> object_, std::shared_ptr<color_t> color_);
    void draw(canvas_t* canvas_);
  private:
    using data = std::tuple<std::shared_ptr<object_t>, std::shared_ptr<color_t>>;
    std::vector<data> _element;

};
*/

/**
 * @class canvas_t
 * @TODO
 */
class canvas_t
{
  public:
    void left_click(int x_, int y_);
    void right_click(int x_, int y_);
    void set_size(int width_, int height_);
    void set_bg(color_t color_) {}
    void edit_pixel(point_t* point_, color_t* color_);
    void draw(void);
    void clear(void)
    {
        // @TODO: empty array
        /* wrapper_set_bg(_bg_color); */
    }
  private:
    color_t _bg_color;
    point_t _window;
    /* struct _data */
    /* { */
    /*     float a, b, c; */
    /* } */
    std::vector<std::vector<std::array<float,3>>> _view_port;  // @TODO: change to float array
    void _left_click(int x_, int y_);
    void _right_click(int x_, int y_);
    void _add_point(point_t point_)
    {
        this->edit_pixel(&point_, new color_t(1.0, 1.0, 1.0));
    }
    void _remove_point(point_t point_) {}
};

#endif  // _MYDRAW_CLASS_HPP_
