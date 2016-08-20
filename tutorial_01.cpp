/*
 * This program draws a white triangle with the help of OpenGL
 *
 * Reference : http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
 *             https://www.opengl.org/sdk/docs/man2/xhtml/
 */

//#include <GLUT/glut.h>	//Include for MAC
#include <GL/glut.h>	//Include for Linux
 #include <iostream>
 #include <fstream>

using namespace std;
void yourRenderFunction(void) {

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	//For other types you may refer to https://www.opengl.org/sdk/docs/man2/xhtml/glBegin.xml
	//But we will only use Lines and Triangles since other primitives are depricated since OpenGL v3.1
	glVertex3f(0.0,  0.5, 0.0); // Vertex of 3 floats viz. x, y & z
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-1.0f,-0.5f, 0.0f);
	glEnd();
	// Swap front and back buffers
	glutSwapBuffers();
}

void yourRenderFunction1(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int pixels[320][320][4];
	ifstream reddata ("red.txt");
	ofstream testdata ("text1.txt");
	if(reddata.is_open())
	{	for(int k = 0; k < 4; k++){
			for(int i = 0; i < 320; i++){
				for(int j = 0; j < 320; j++){
				reddata >> pixels[i][j][k];
				}
			}
		}
		for(int k =0; k < 4; k++){
		for(int i = 0; i < 320; i++){
			for(int j = 0; j < 320; j++){
				testdata << pixels[i][j][k]; ',';
			}
			testdata << '\n';
		}
		testdata << '\n';
	}
}
	glRasterPos2i(-1.0,-1.0);
	glDrawPixels(320, 320,
				 GL_RGBA, GL_INT, &pixels);
	glFlush();
	glutSwapBuffers();
}
	


void mouse( int x, int y )
{
    // 4 bytes per pixel (RGBA), 1x1 bitmap
    glReadBuffer(GL_FRONT);
     int pixels[320];
    glReadPixels
        ( 
        0, glutGet( GLUT_WINDOW_HEIGHT ) - y, 
        320, 1, 
        GL_RED, GL_INT, &pixels 
        );
    for(int j = 0; j < 320; j++){
				std::cout << pixels[j] << ',';
	}
	cout << '\n';

   // cout << "r: " << pixels[0] << '\n';
    //cout << "g: " << pixels[1] << '\n';
    //cout << "b: " << pixels[2] << '\n';
    //cout << "a: " << pixels[3] << '\n';
    //cout << endl;
    
}


GLvoid KeyPressedGL(unsigned char key, GLint x, GLint y) 
{
	if (key == 'S'){
	glReadBuffer(GL_FRONT);
     int pixels[320][320][4];
    glReadPixels
        ( 
        0, 0, 
        320, 320, 
        GL_RGBA, GL_INT, &pixels 
        );
    ofstream myfile;
    myfile.open("red.txt",ios::out);
    for(int k = 0; k < 4 ; k++){
    for(int i =0; i < 320; i++){
    for(int j = 0; j < 320; j++){
				myfile << pixels[i][j][k] << ' ';
	}
	myfile << '\n';
}

}
}
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE| GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Title : Triangle");

	// register callbacks
	glutDisplayFunc(yourRenderFunction);
	glutKeyboardFunc(&KeyPressedGL);
	//glutPassiveMotionFunc(mouse);
	
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
