#include <viewport.hpp>
#include <cylinder.hpp>

// these 2 lines are a hack to force loading of pthread
// Somehow, the linker is not adding pthread
// For more details, see
// [this](http://stackoverflow.com/questions/31579243/segmentation-fault-before-main-when-using-glut-and-stdstring)
#include <pthread.h>
void* simpleFunc(void*) { return NULL; } void forcePThreadLink() { pthread_t t1; pthread_create(&t1, NULL, &simpleFunc, NULL); }

int main (int argc, char *argv[])
{
    Viewport assignment;
    std::cout << "This is  nuts\n";
    assignment.setLookAt(0.0, 2.0, 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 1.0);
    assignment.setBaseObj(std::static_pointer_cast<ObjectBase>(std::make_shared<Cylinder>()));
    assignment.startFramework(argc, argv);
    return 0;
}
