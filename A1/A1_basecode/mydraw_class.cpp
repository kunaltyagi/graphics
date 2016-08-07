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

// object_t methods
object_t::object_t(): _vertice(nullptr), _len(0)
{}

object_t::object_t(point_t* point_, int n_): _len(n_)
{
    set(point_, n_);

}

void object_t::set(point_t* point_, int n_)
{
    _len = n_;
    if (_vertice != nullptr)
    {
        delete[] _vertice;
    }
    _vertice = new point_t[_len];
    for (int i = 0; i < _len; ++i)
    {
        _vertice[i] = point_[i];
    }
}

// line_t methods
line_t::line_t(): object_t()
{}

line_t::line_t(point_t* vertice_): object_t(vertice_, 2)
{}

line_t::line_t(point_t start_, point_t end_)
{
    set(start_, end_);
}

void line_t::set(point_t start_, point_t end_)
{
    _len = 2;
    point_t pt[2] = { start_, end_};
    set(pt);
}

void line_t::set(point_t* vertice_)
{
    object_t::set(vertice_, 2);
}

void line_t::draw(color_t* color_, canvas_t* canvas_)
{
    point_t* current = _vertice;
    point_t* last = _vertice + _len;
    while(current->X() != last->X() && current->Y() != last->Y())
    {
        current->draw(color_, canvas_);
        current = int_bresenham(current, last);
    }
}

// triangle_t methods
triangle_t::triangle_t()
{}

triangle_t::triangle_t(point_t* vertice_, color_t border_):
        object_t(vertice_, 3), _border(border_)
{}

void triangle_t::set_vertices(point_t one_, point_t two_, point_t three_)
{
    _vertice[0] = one_;
    _vertice[0] = two_;
    _vertice[0] = three_;
}
void triangle_t::set_vertices(point_t* vertice_)
{
    set_vertices(vertice_[0], vertice_[1], vertice_[2]);
}

void triangle_t::set_border(color_t border_)
{
    _border = border_;
}

void triangle_t::draw(color_t* fill_color_, canvas_t* canvas_)
{
    line_t edge[3];
    point_t mean;
    fill_t filler(*fill_color_);
    for (int i = 0; i < 3; ++i)
    {
        edge[i].set(_vertice[i], _vertice[(i + 1) % 3]);
        mean.X(mean.X() + _vertice[i].X());
        mean.Y(mean.Y() + _vertice[i].Y());
        edge[i].draw(&_border, canvas_);
    }
    mean.X(mean.X()/3);
    mean.Y(mean.Y()/3);
    for (int i = 0; i < 3; ++i)
    {
        // check global fill style
        // @TODO
        // fill the triangle
        filler.draw(fill_color_, &_border, canvas_);
        filler.draw(fill_color_, &mean, canvas_);
    }
}

// drawing_t methods
drawing_t::drawing_t()
{}

void drawing_t::add(std::shared_ptr<object_t> object_,
                    std::shared_ptr<color_t> color_)
{
    _element.emplace_back(std::make_tuple(object_, color_));
}

void drawing_t::draw(canvas_t* canvas_)
{
    for (auto& element: _element)
    {
        std::get<0>(element)->draw(std::get<1>(element).get(), canvas_);
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
