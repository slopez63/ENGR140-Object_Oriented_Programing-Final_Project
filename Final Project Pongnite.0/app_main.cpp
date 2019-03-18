#include "App.h"

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
    
    // Instantiate a new App
    App* myApp = new App("MyApp", 600, 100, 800, 900);

	// Start the app
    myApp->run();
}
