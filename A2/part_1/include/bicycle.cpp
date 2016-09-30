#include <cylinder.hpp>
#include <cube.hpp>
#include <torus.hpp>
#include <sphere.hpp>
#include <generic_object.hpp>

class mainframe{
	cylinder ver_bar(0.2, 0.2, 5, 2, 1);
	ver_bar.setpose(Pose(Point(0, 0, 0, 1), Point(3.14/2.0, 0, 0, 1)));
	cylinder horz_bar(0.2, 0.2, 9, 2, 1);
	horz_bar.setpose(Pose(Point(-9, 5, 0, 1), Point(0, 0, 0, 1)));
	cylinder downbar1(0.2, 0.2, 10, 2, 1);
	downbar1.setpose(Pose(Point(0, 0, 0, 1), Point(2*3.14/3.0, 0, 0, 1)));
	cylinder downbar2(0.2, 0.2, 6.5, 2, 1);
	downbar2.setpose(Pose(Point(0, 0, 0.5, 1), Point(0, 0, 0, 1)));
	cylinder downbar3(0.2, 0.2, 6.5, 2, 1);
	downbar3.setpose(Pose(Point(0, 0, -0.5, 1), Point(0, 0, 0, 1)));
	cylinder backmain(0.2, 0.2, 2.2, 2, 1);
	backmain.setpose(Pose(Point(0, 5, 0, 1), Point(0.6557, 0, 0, 1)));
	cylinder back1(0.2, 0.2, 6, 2, 1);
	back1.setpose(Pose(Point(1.743, 1.341, -0.5, 1), Point(0.6557, 0, 0, 1)));
	cylinder back2(0.2, 0.2, 6, 2, 1);
	back2.setpose(Pose(Point(1.743, 1.341, 0.5, 1), Point(0.6557, 0, 0, 1)));
	cylinder backsupp(0.2, 0.2, 1, 2, 1);
	backsupp.setpose(Pose(Point(1.743, 1.341, 0.5, 1), Point(3.14/2, 0, 1, 0)));
	cylinder frontbar(0.2, 0.2, 2.5, 2, 1);
	frontbar.setpose(Pose(Point(-9, 3.5, 0, 1), Point(3.14/2, 0, 0, 1)));
	cylinder front1(0.2, 0.2, 3.5, 2, 1);
	front1.setpose(Pose(Point(-9, 0, -0.5, 1), Point(3.14/2, 0, 0, 1)));
	cylinder front2(0.2, 0.2, 3.5,2, 1);
	front2.setpose(Pose(Point(-9, 0, 0.5, 1), Point(3.14/2, 0, 0, 1)));
	cylinder front3(0.2, 0.2, 1, 2, 1);
	front3.setpose(Pose(Point(-9, 3, 0.5, 1), Point(3.14/2, 0, 1, 0)));
	cylinder fronthandle(0.2, 0.2, 2, 2, 1);
	fronthandle.setpose(Pose(-9, 5, 0, 1), Point(3.14, 0, 0, 1));
	cylinder handle(0.2, 0.2, 4, 2, 1);
	handle.setpose(Pose(-11, 5, 2, 1), Point(3.14/2, 0, 1, 0));
}