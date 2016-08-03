#include "mydraw_class.hpp"

// dummy methods
void _floodFill(color_t, point_t)
{}
void _scanFill(color_t, color_t)
{}

// color_t methods
color_t::color_t(): _r(0.0), _g(0.0), _b(0.0)
{}

color_t::color_t(const float r_, const float g_, const float b_): _r(r_),
                                                                  _g(g_),
                                                                  _b(b_)
{}

void color_t::set(const float r_, const float g_, const float b_)
{
    _r = r_;
    _g = g_;
    _b = b_;
}

// pen_t methods
pen_t::pen_t(): _t(1.0), _color(1.0, 1.0, 1.0), _mode(mode::DRAW)
{}

pen_t::pen_t(int t_, color_t color_, mode mode_): _t(t_),
                                                  _color(color_),
                                                  _mode(mode_)
{}

inline void pen_t::set_color(color_t color_)
{
    _color = color_;
}

inline void pen_t::set_thickness(int t_)
{
    _t = t_;
}

inline void pen_t::set_mode(pen_t::mode mode_)
{
    _mode = mode_;
}

inline void pen_t::set(int t_, color_t color_, pen_t::mode mode_)
{
    set_thickness(t_);
    set_color(color_);
    set_mode(mode_);
}

// point_t methods
point_t::point_t(): _x(0), _y(0)
{}

point_t::point_t(int x_, int y_): _x(x_), _y(y_)
{}

// fill_t methods
fill_t::fill_t(): _fill(1.0, 1.0, 1.0)
{}

fill_t::fill_t(color_t color_): _fill(color_)
{}

void fill_t::draw(color_t color_, point_t point_)
{
    _floodFill(color_, point_);
}

void fill_t::draw(color_t fill_color_, color_t edge_color_)
{
    _scanFill(fill_color_, edge_color_);
}

void fill_t::set_color(color_t color_)
{
    _fill = color_;
}
