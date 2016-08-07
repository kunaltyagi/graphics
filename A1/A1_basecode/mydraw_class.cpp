#include "mydraw_class.hpp"

// @TODO
// dummy methods
void _floodFill(color_t*, point_t*, canvas_t*)
{}
void _scanFill(color_t*, color_t*, canvas_t*)
{}
point_t* int_bresenham(point_t* current_, point_t* end_)
{
    return current_;
}

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

void point_t::draw(color_t* color_, canvas_t* canvas_)
{
    canvas_->edit_pixel(this, color_);
}

// fill_t methods
fill_t::fill_t(): _fill(1.0, 1.0, 1.0)
{}

fill_t::fill_t(color_t color_): _fill(color_)
{}

void fill_t::draw(color_t* color_, point_t* point_, canvas_t* canvas_)
{
    _floodFill(color_, point_, canvas_);
}

void fill_t::draw(color_t* fill_color_, color_t* edge_color_, canvas_t* canvas_)
{
    _scanFill(fill_color_, edge_color_, canvas_);
}

void fill_t::set_color(color_t color_)
{
    _fill = color_;
}

// line_t methods
line_t::line_t()
{}

line_t::line_t(point_t start_, point_t end_): _start(start_), _end(end_)
{}

void line_t::set(point_t start_, point_t end_)
{
    _start = start_;
    _end = end_;
}

void line_t::draw(color_t* color_, canvas_t* canvas_)
{
    point_t* current = &_start;
    while(current->X() != _end.X() && current->Y() != _end.Y())
    {
        current->draw(color_, canvas_);
        current = int_bresenham(current, &_end);
    }
}

// canvas_t methods
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
#ifdef DEBUG
    std::cout << "Color: " << _view_port[y_][x_][0] << '\t'
                           << _view_port[y_][x_][1] << '\t'
                           << _view_port[y_][x_][2] << '\n';
#endif
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
    _view_port.resize(height_);
#ifdef DEBUG
    std::cout << _view_port.size() << '\n';
#endif
    for (auto it = _view_port.begin(); it != _view_port.end(); ++it)
    {
        it->resize(width_);
#ifdef DEBUG
        std::cout << it->size() << '\t';
#endif
        for (auto jt = it->begin() + _window.X(); jt != it->end(); ++jt)
        {
            if (std::distance(_view_port.begin(), it) >= _window.Y() ||
                std::distance(it->begin(), jt) >= _window.X())
            {
                (*jt) = new float[3]{0, 0, 0};
            }
        }
    }
    _window.set(width_, height_);
}

void canvas_t::edit_pixel(point_t* point_, color_t* color_)
{
    float* color = _view_port[point_->Y()][point_->X()];
    color[0] = color_->R();
    color[1] = color_->G();
    color[2] = color_->B();
}

void canvas_t::draw(void)
{
    // @TODO
    for (int row = 0; row < _window.Y(); ++row)
    {
        glRasterPos2i(row, 0);
#ifdef DEBUG
        for (int i = 0; i < _window.X(); ++i)
        {
            if (_view_port[row][i][0] != 0 ||
                _view_port[row][i][1] != 0 ||
                _view_port[row][i][2] != 0)
                    std::cout << "Row, Col: " << row << ", " << i << '\t'
                              << _view_port[row][i][0] << ' '
                              << _view_port[row][i][1] << ' '
                              << _view_port[row][i][2] << '\n';
        }
#endif
        glDrawPixels(_window.X(), 1, GL_RGB, GL_FLOAT, &(_view_port[row][0][0]));
    }
}
