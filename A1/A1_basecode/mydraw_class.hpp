#ifndef _MYDRAW_CLASS_HPP_
#define _MYDRAW_CLASS_HPP_

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
    void draw(color_t color_, point_t point_, unsigned int algorithm_ = 0);
    inline void set_color(color_t color_);
};

#endif  // _MYDRAW_CLASS_HPP_
