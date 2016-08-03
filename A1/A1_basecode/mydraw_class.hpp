#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_

#ifdef DEBUG
#include <iostream>
#endif

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

    inline void set(const float r_, const float g_, const float b_);
    inline float R(void);
    inline float G(void);
    inline float B(void);
};

// color_t inline functions
float color_t::R(void)
{
    return _r;
}

float color_t::G(void)
{
    return _g;
}

float color_t::B(void)
{
    return _b;
}


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
    inline void set_color(color_t color_);
    inline void set_thickness(int t_);
    inline void set_mode(mode mode_);
    inline void set(int t_, color_t color_, mode mode_);
  private:
    int _t;          ///< thickness
    color_t _color;  ///< color of the pen
    mode _mode;      ///< mode of drawing
    // bg color??
};

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
    inline int X(void);
    inline int Y(void);
    inline void X(int x_);
    inline void Y(int y_);
    inline void set(int x_, int y_);
    void draw(color_t color_);
};

// inline point_t methods
int point_t::X(void)
{
    return _x;
}

int point_t::Y(void)
{
    return _y;
}

void point_t::X(int x_)
{
    _x = x_;
}

void point_t::Y(int y_)
{
    _y = y_;
}

void point_t::set(int x_, int y_)
{
    _x = x_;
    _y = y_;
}


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
    void draw(color_t color_, point_t point_);
    void draw(color_t fill_color_, color_t edge_color_);
    inline void set_color(color_t color_);
};

/**
 * @class canvas_t
 * @TODO
 */
class canvas_t
{
  public:
    inline void left_click(int x_, int y_);
    inline void right_click(int x_, int y_);
    inline void set_size(int width_, int height_);
    inline void set_bg(color_t color_) {}
    void draw(void) {}
    void clear(void)
    {
        // @TODO: empty array
        /* wrapper_set_bg(_bg_color); */
    }
  private:
    color_t _bg_color;
    point_t _window;
    inline void _left_click(int x_, int y_);
    inline void _right_click(int x_, int y_);
    void _add_point(point_t point_) {}
    void _remove_point(point_t point_) {}
};

// canvas_t inline functions
void canvas_t::left_click(int x_, int y_)
{
    _left_click(x_, _window.Y() - y_);
}
void canvas_t::right_click(int x_, int y_)
{
    _right_click(x_, _window.Y() - y_);
}
void canvas_t::_left_click(int x_, int y_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Left Mouse @ " << x_ << '\t' << y_ << '\n';
#endif
    _add_point(point_t(x_, y_));
}
void canvas_t::_right_click(int x_, int y_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Right Mouse @ " << x_ << '\t' << y_ << '\n';
#endif
    _remove_point(point_t(x_, y_));
}
void canvas_t::set_size(int width_, int height_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Window size: " << width_ << " X " << height_ << '\n';
#endif
    _window.set(width_, height_);
}

#endif  // _MYDRAW_CLASS_HPP_
