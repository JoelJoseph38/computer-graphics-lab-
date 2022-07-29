#include<GL/glut.h>
#include<windows.h>
void teapot(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix (); //save the current state
    glTranslatef (x, y, z); //move your item appropriately
    glutSolidTeapot (0.1); //render your teapot
    glPopMatrix (); //get back your state with the recent changes that you have done
}

void tableTop(GLfloat x, GLfloat y, GLfloat z) // table top which is actually a CUBE
{
    glPushMatrix ();
    glTranslatef (x, y, z);
    glScalef (0.6, 0.02, 0.5);
    glutSolidCube (1);
    glPopMatrix ();
}

void tableLeg(GLfloat x, GLfloat y, GLfloat z) // table leg (CUBE)
{
    glPushMatrix ();
    glTranslatef (x, y, z);
    glScalef (0.02, 0.3, 0.02);
    glutSolidCube (1);
    glPopMatrix ();
}

void wall(GLfloat x, GLfloat y, GLfloat z) // wall which is actually a CUBE
{
    glPushMatrix ();
    glTranslatef (x, y, z);
    glScalef (1, 1, 0.02);
    glutSolidCube (1);
    glPopMatrix ();
}

void light() // set the lighting arrangements
{
    //glColor3f(0.33, 0.43, 0.9);
    GLfloat mat_ambient[] = {1, 1, 1, 1}; // ambient colour
    GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1};
    GLfloat mat_specular[] = {1, 0.87, 0, 1};
    GLfloat mat_shininess[] = {10.0f}; // shininess value

    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light_position[] = {3, 7, 4, 1};
    GLfloat light_intensity[] = {0.7, 0.7, 0.7, 1};

    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_intensity);
}

void display()
{
    GLfloat teapotP = -0.07, tabletopP = -0.15, tablelegP = 0.2, wallP = 0.5;
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt (-3, 2, 2, 0, 0, 0, 0, 2, 0); // camera position & viewing

    light (); //Adding light source to your project

    teapot (0, teapotP, 0); //Create teapot

    tableTop (0, tabletopP, 0); //Create table’s top
    tableLeg (tablelegP, -0.3, tablelegP); //Create 1st leg
    tableLeg (-tablelegP, -0.3, tablelegP); //Create 2nd leg
    tableLeg (-tablelegP, -0.3, -tablelegP); //Create 3rd leg
    tableLeg (tablelegP, -0.3, -tablelegP); //Create 4th leg

    wall (0, 0, -wallP); //Create 1st wall

    glRotatef (90, 1, 0, 0);

    wall (0, 0, wallP); //Create 2nd wall

    glRotatef (90, 0, 1, 0);

    wall (0, 0, wallP); //Create 3rd wall
    glFlush (); // show the output to the user
}

void init()
{
    glClearColor (0, 0, 0, 1); // black colour background
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (-1, 1, -1, 1, -1,10);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("Teapot");

    init();

    glutDisplayFunc(display);
    glEnable(GL_LIGHTING); //enable lighting properties
    glEnable(GL_LIGHT0);   //enable light source

    glShadeModel(GL_SMOOTH); //smooth shading

    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST); //do depth comparisons and update depth buf

    glutMainLoop();
}
