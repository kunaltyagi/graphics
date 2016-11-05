#include <viewport.hpp>
/* #include <torus_old.hpp> */
#include <objects.hpp>
#include <front_handle.hpp>

// these 2 lines are a hack to force loading of pthread
// Somehow, the linker is not adding pthread. For more details, see
// [this](http://stackoverflow.com/questions/31579243/segmentation-fault-before-main-when-using-glut-and-stdstring)
#include <pthread.h>
void* simpleFunc(void*) { return NULL; } void forcePThreadLink() { pthread_t t1; pthread_create(&t1, NULL, &simpleFunc, NULL); }

int main (int argc, char *argv[])
{
    Viewport assignment;
    assignment.setLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, .0);

    Pose far;
    far.R.setPoint(0, 0, 1, 180);
    far.T.setPoint(1, 1, 0, 1);

    std::shared_ptr<FrontHandle> wheel = std::make_shared<FrontHandle>();
    std::shared_ptr<ObjectBase> baseObj = std::static_pointer_cast<ObjectBase>(wheel);

    assignment.setBaseObj(baseObj);
    assignment.startFramework(argc, argv);
    return 0;
}

// for triangle
/*
    Point vertices[Triangle::num_vertex] = {{0, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}};
    std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(vertices);
    triangle->setPose(far);
    std::shared_ptr<ObjectBase> baseObj = std::static_pointer_cast<ObjectBase>(triangle);
 */
// for square
/*
    std::shared_ptr<Square> square = std::make_shared<Square>();
    square->setPose(far);
    std::shared_ptr<ObjectBase> baseObj = std::static_pointer_cast<ObjectBase>(square);
 */
