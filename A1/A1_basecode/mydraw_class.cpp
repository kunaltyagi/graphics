#include "mydraw_class.hpp"

// @TODO
// dummy methods
void _floodFill(color_t*, color_t, point_t*, canvas_t*);
void _floodFill(color_t* color_, point_t* point_, canvas_t* canvas_)
{
    _floodFill(color_, canvas_->get_pixel(point_), point_, canvas_);
}
void _floodFill(color_t* replacement_color_, color_t target_color,
                point_t* point_, canvas_t* canvas_)
{
    if (*replacement_color_ == canvas_->get_pixel(point_) ||
        !(canvas_->get_pixel(point_) == target_color))
    {
        return;
    }
    point_->draw(replacement_color_, canvas_);
    // paint current point
    point_t temp;
    int x[4] = { 1, -1, 0, 0};
    int y[4] = { 0, 0, 1, -1};

    for (int i = 0; i < 4; ++i)
    {
        temp.X(point_->X() + x[i]);
        temp.Y(point_->Y() + y[i]);
        if (canvas_->is_valid(&temp))
        {
            if (!(*replacement_color_ == canvas_->get_pixel(&temp)))
            {
                _floodFill(replacement_color_, target_color, &temp, canvas_);
            }
        }
    }
    return;
}
void _scanFill(color_t*, color_t*, canvas_t*)
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

bool color_t::operator ==(const color_t &b) const
{
    return _r == b._r && _g == b._g && _b == b._b;
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
pen_t::pen_t(): _t(1.0), _fg_color(1, 1, 1), _bg_color(0, 0, 0),
        _mode(mode::DRAW)
{}

pen_t::pen_t(int t_, color_t fg_color_, color_t bg_color_, mode mode_):
    _t(t_), _fg_color(fg_color_), _bg_color(bg_color_), _mode(mode_)
{}

void pen_t::set_fg_color(color_t color_)
{
    _fg_color = color_;
}

color_t pen_t::get_fg_color(void)
{
    return _fg_color;
}

void pen_t::set_bg_color(color_t color_)
{
    _bg_color = color_;
}

color_t pen_t::get_bg_color(void)
{
    return _bg_color;
}

color_t pen_t::get_color()
{
    if (_mode == mode::DRAW)
    {
        return _fg_color;
    }
    return _bg_color;
}

float pen_t::get_width(void)
{
    return _t;
}

void pen_t::set_width(float t_)
{
    _t = t_;
}

pen_t::mode pen_t::get_mode()
{
    return _mode;
}

void pen_t::set_mode(pen_t::mode mode_)
{
    _mode = mode_;
}

void pen_t::set(int t_, color_t fg_color_, color_t bg_color_, pen_t::mode mode_)
{
    set_width(t_);
    set_fg_color(fg_color_);
    set_bg_color(bg_color_);
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
    canvas_->save_pen();
    canvas_->set_pen_width(1);
    _floodFill(color_, point_, canvas_);
    canvas_->restore_pen();
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
object_t::object_t(): _vertice(nullptr), _len(0), _pen(), _fill_center(-1,-1)
{}

object_t::object_t(point_t* point_, int n_, pen_t pen_):
    _vertice(nullptr), _len(n_), _pen(pen_), _fill_center(-1,-1)
{
    set(point_, n_, pen_);

}

void object_t::set(point_t* point_, int n_, pen_t pen_)
{
    _len = n_;
    _pen = pen_;
    if (_vertice != nullptr)
    {
        delete[] _vertice;
    }
    _vertice = new point_t[_len];
    for (int i = 0; i < _len; ++i)
    {
        _vertice[i] = point_[i];
    }
    _fill_center.X(-1);
    _fill_center.Y(-1);
}

// line_t methods
line_t::line_t(): object_t()
{}

line_t::line_t(point_t* vertice_, pen_t pen_): object_t(vertice_, 2, pen_)
{}

line_t::line_t(point_t start_, point_t end_, pen_t pen_)
{
    set(start_, end_, pen_);
}

void line_t::set(point_t start_, point_t end_, pen_t pen_)
{
    _len = 2;
    point_t pt[2] = { start_, end_};
    set(pt, pen_);
}

void line_t::set(point_t* vertice_, pen_t pen_)
{
    object_t::set(vertice_, 2, pen_);
}

void line_t::draw(canvas_t* canvas_)
{
    point_t* current = new point_t(_vertice[0]);
    point_t* last = _vertice + 1;

    int dx = last->X() - current->X(), dy = last->Y() - current->Y();
    int inc = 1;
    if (dx < 0)
    {
        dx *= -1;
        dy *= -1;
        last = _vertice;
        current = new point_t(_vertice[1]);
    }
    if (dy < 0)
    {
        inc = -1;
    }

    int error = 0;
    canvas_->save_pen();
    canvas_->set_pen(_pen);

    while((current->X() != last->X()) || (current->Y() != last->Y()))
    {
        current->draw(new color_t(_pen.get_color()), canvas_);
        if (dx >= inc*dy)
        {
            error += inc*dy;
            if (dy == 0)
            {
            }
            if ((error << 1) >= dx)
            {
                error -= dx;
                current->Y(current->Y() + inc);
            }
            current->X(current->X() + 1);
        }
        else
        {
            error += dx;
            if ((error << 1) >= inc*dy)
            {
                error -= inc*dy;
                current->X(current->X() + 1);
            }
            current->Y(current->Y() + inc);
        }
    }
    current->draw(new color_t(_pen.get_color()), canvas_);
    canvas_->restore_pen();
    delete current;
}

// triangle_t methods
triangle_t::triangle_t(): object_t()
{}

triangle_t::triangle_t(point_t* vertice_, pen_t pen_):
        object_t(vertice_, 3, pen_)
{}

void triangle_t::set(point_t* vertice_, pen_t pen_)
{
    object_t::set(vertice_, 3, pen_);
}

void triangle_t::draw(canvas_t* canvas_)
{
    line_t edge[3];
    point_t mean;
    for (int i = 0; i < 3; ++i)
    {
        edge[i].set(_vertice[i], _vertice[(i + 1) % 3], _pen);
        mean.X(mean.X() + _vertice[i].X());
        mean.Y(mean.Y() + _vertice[i].Y());
        edge[i].draw(canvas_);
    }
    if (_fill_center.X() != -1)
    {
        fill(&_fill_center, canvas_);
    }
}

void triangle_t::fill(point_t* mean_, canvas_t* canvas_)
{
    _fill_center = *mean_;
    fill_t filler(_pen.get_bg_color());
    filler.draw(new color_t(_pen.get_bg_color()), mean_, canvas_);
}

// drawing_t methods
drawing_t::drawing_t()
{}

void drawing_t::add(object_t* object_)
{
    _element.emplace_back(object_);
}

void drawing_t::draw(canvas_t* canvas_)
{
#ifdef DEBUG
    std::cout << "[Drawing] Painting the canvas\n";
    int i = 0;
#endif
    for (auto& element: _element)
    {
#ifdef DEBUG
        std::cout << i++ << " Element\n";
#endif
        element->draw(canvas_);
    }
}

void drawing_t::clear()
{
    for (auto& element: _element)
    {
        delete element;
    }
    _element.clear();
}

void drawing_t::save(std::string file_)
{
    std::ofstream file;
    file.open(file_, std::ofstream::out | std::ofstream::app);
    int i = 0;
    for (auto& element: _element)
    {
        /* file << "*** Element " << i++ << " ***\n"; */
        file << *element << '\n';
    }
    file.close();
}

void drawing_t::load(std::string file_, canvas_t* canvas_)
{
    _element.clear();
    // @TODO
    // use
    // canvas_->add_point(point_t);
    // canvas_->set_mode(Mode);
    // canvas_->set_size(int, int);
    // canvas_->set_fill_color(color_t);
    // canvas_->set_pen(pen_t);
    // canvas_->fill(point_t* point_);
}
void drawing_t::fill(point_t* point_, canvas_t* canvas_)
{
    _element.back()->fill(point_, canvas_);
}

// canvas_t methods
canvas_t::canvas_t():
    _pen(1, color_t(1, 1, 1), color_t(0, 0, 0), pen_t::mode::DRAW),
    _window(64, 64), _mode(POINT)
{}

canvas_t::canvas_t(color_t fg_color_, color_t bg_color_, point_t window_):
    _mode(POINT), _pen(1, fg_color_, bg_color_, pen_t::mode::DRAW)
{
    set_size(window_.X(), window_.Y());
    clear();
}

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
    std::cout << "[Canvas] Left Mouse @ " << x_ << " X " << y_ << '\n';
#endif
    add_point(point_t(x_, y_));
}

void canvas_t::_right_click(int x_, int y_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Right Mouse @ " << x_ << " X " << y_ << '\n';
#endif
    _remove_point(point_t(x_, y_));
}

void canvas_t::set_size(int width_, int height_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Window size: " << width_ << " X " << height_ << '\n';
#endif
    _view_port.resize(height_);
    std::array<float, 3> color;
    color[0] = _pen.get_bg_color().R();
    color[1] = _pen.get_bg_color().G();
    color[2] = _pen.get_bg_color().B();
    for (int row = 0; row < height_; ++row)
    {
        _view_port[row].resize(width_, color);
    }
    _window.set(width_, height_);
}

void canvas_t::set_bg(color_t color_)
{
    _pen.set_bg_color(color_);
}

void canvas_t::set_pen_color(color_t color_)
{
    _pen.set_fg_color(color_);
}

void canvas_t::set_pen_width(float t_)
{
    _pen.set_width(t_);
}

void canvas_t::edit_pixel(point_t* point_, color_t* color_)
{
    float semi_t = _pen.get_width()/2;
    if (semi_t == 0)
    {
        return;
    }
    if (semi_t <= 0.5 && semi_t >= 0.25)
    {
        semi_t = 0;  // use only one pixel for 1 > width > 0.5
    }
    for (int i = round(std::max((float)0, point_->Y() - semi_t));
            i <= round(std::min((float)_window.Y()-1, point_->Y() + semi_t));
            ++i)
    {
        for (int j = round(std::max((float)0, point_->X() - semi_t));
                j <= round(std::min((float)_window.X()-1, point_->X() + semi_t));
                ++j)
        {
            auto& color = _view_port.at(i).at(j); //[i][j];
            color[0] = color_->R();
            color[1] = color_->G();
            color[2] = color_->B();
        }
    }
}

void canvas_t::draw(void)
{
    _drawing.draw(this);
    for (int row = 0; row < _window.Y(); ++row)
    {
        glRasterPos2i(0, row);
#ifdef DEBUG_BASIC
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

void canvas_t::add_point(point_t point_)
{
    if (_mode == NONE)
    {
        fill(&point_);
        return;
    }
    _points.push_back(point_);
    if (_points.size() == _mode)
    {
        switch(_mode)
        {
        case POINT:
            this->edit_pixel(&point_, new color_t(_pen.get_fg_color()));
            break;
        case LINE:
            _drawing.add((object_t*)new line_t(_points.data(), _pen));
            break;
        case TRIANGLE:
            _drawing.add((object_t*)new triangle_t(_points.data(),
                         pen_t(_pen.get_width(), _pen.get_fg_color(),
                               _fill_color, pen_t::mode::DRAW)));
            break;
        default:
            break;
        }
        _points.clear();
    }
}

void canvas_t::_remove_point(point_t point_)
{
    if (_points.size())
    {
        _points.pop_back();
    }
    return;
}

void canvas_t::clear(void)
{
#ifdef DEBUG
    std::cout << "[Canvas] Cleared\n";
#endif
    _drawing.clear();
    point_t temp(0, 0);
    for (int i = 0; i < _window.Y(); ++i)
    {
        for (int j = 0; j < _window.X(); ++j)
        {
            temp.set(j, i);
            edit_pixel(&temp, new color_t(_pen.get_bg_color()));
        }
    }
}

void canvas_t::set_mode(Mode mode_)
{
#ifdef DEBUG
    std::cout << "[Canvas] Mode updated to " << mode_ << '\n';
#endif
    _mode = mode_;
    if (_mode == NONE)
    {
        mode_ = POINT;
    }
    while (_points.size() > mode_)
    {
        _points.pop_back();
    }
    if (_points.size() == mode_)
    {
        point_t back = _points.back();
        _points.pop_back();
        add_point(back);
    }
}

void canvas_t::save_pen()
{
    _bkp_pen = _pen;
}

void canvas_t::restore_pen()
{
    _pen = _bkp_pen;
}

bool canvas_t::is_valid(point_t* point_)
{
    if (point_->X() < _window.X() && point_->Y() < _window.Y() &&
        point_->X() >= 0 && point_->Y() >= 0)
    {
        return true;
    }
    return false;
}

color_t canvas_t::get_pixel(point_t* point_)
{
    auto& color = _view_port[point_->Y()][point_->X()];
    return color_t(color[0], color[1], color[2]);
}

void canvas_t::set_pen(pen_t pen_)
{
    _pen = pen_;
}

void canvas_t::set_fill_color(color_t color_)
{
    _fill_color = color_;
}

void canvas_t::fill(point_t* point_)
{
    _drawing.fill(point_, this);
    set_mode(TRIANGLE);
}

void canvas_t::save(std::string file_)
{
    std::ofstream file;
    file.open(file_);
    file << _window << ',' << _pen <<'\n';
    file.close();
    _drawing.save(file_);
}

void canvas_t::load(std::string file_)
{
    // @TODO
    _drawing.load(file_, this);
}

// stream overloads
std::ostream& operator<< (std::ostream& o_, const color_t& color_)
{
    o_ << "color: " << color_._r << ',' << color_._g << ',' << color_._b;
}

std::ostream& operator<< (std::ostream& o_, const pen_t& pen_)
{
    o_ << "pen: " << (int)pen_._mode << ',' << pen_._t << ',' << pen_._fg_color << ',' << pen_._bg_color;
}

std::ostream& operator<< (std::ostream& o_, const point_t& point_)
{
    o_ << "point: " << point_._x << ',' << point_._y;
}

std::ostream& operator<< (std::ostream& o_, const fill_t& fill_)
{
    o_ << "fill: " << fill_._fill;
}

std::ostream& operator<< (std::ostream& o_, const object_t& object_)
{
    o_ << "object: " << object_._len << ',';
    for (int i = 0; i < object_._len; ++i)
    {
        o_ << object_._vertice[i]<<',';
    }
    o_ << object_._pen << ',' << object_._fill_center;
}
