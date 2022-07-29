#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
float theta = 0;
float Thetha;
int radius = 8;
int xpos = 100.0;
int ypos = 420.0;
struct point
{
    GLfloat x, y, z;
};
int factorial (int n)
{
    if (n<=1)
        return (1);
    else
        n = n * factorial ( n-1 );
    return n;
}
void computeNcR (int n, int *hold_ncr_values)
{
    int r;
    for (r=0; r<=n; r++)
    {
        hold_ncr_values [r] = factorial (n) / ( factorial (n-r) * factorial (r) );
    }
}
void computeBezierPoints (float t, point *actual_bezier_point, int number_of_control_points, point *control_points_array, int *hold_ncr_values)
{
    int i, n = number_of_control_points - 1;
    float bernstein_polynomial;
    actual_bezier_point -> x = 0;
    actual_bezier_point -> y = 0;
    actual_bezier_point -> z = 0;
    for ( i=0; i<number_of_control_points; i++ )
    {
        bernstein_polynomial = hold_ncr_values [i] * pow(t, i) * pow( 1-t, n-i);
        actual_bezier_point->x += bernstein_polynomial * control_points_array [i].x;
        actual_bezier_point->y += bernstein_polynomial * control_points_array [i].y;
        actual_bezier_point->z += bernstein_polynomial * control_points_array [i].z;
    }
}
void Bezier (point *control_points_array, int number_of_control_points, int number_of_bezier_points)
{
    point actual_bezier_point;
    float t;
    int *hold_ncr_values, i;
    hold_ncr_values = new int [number_of_control_points];
    computeNcR (number_of_control_points - 1, hold_ncr_values);
    glBegin (GL_LINE_STRIP);
    for(i=0; i<=number_of_bezier_points; i++)
    {
        t=float (i) / float (number_of_bezier_points);
        computeBezierPoints ( t, &actual_bezier_point, number_of_control_points,
        control_points_array, hold_ncr_values );
        glVertex2f (actual_bezier_point.x, actual_bezier_point.y);
    }
    glEnd ();
    delete [] hold_ncr_values;
}
void display()
{
    glClear (GL_COLOR_BUFFER_BIT);
    int number_of_control_points= 4, number_of_bezier_points= 20;
    point control_points_array[4]= {{100, 400, 0}, {150, 450, 0}, {250, 350, 0},{300, 400, 0}};
    control_points_array[1].x += 50 * sin (theta * PI/180.0);
    control_points_array[1].y += 25 * sin (theta * PI/180.0);
    control_points_array[2].x -= 50 * sin ((theta+30) * PI/180.0);
    control_points_array[2].y -= 50 * sin ((theta+30) * PI/180.0);
    control_points_array[3].x -= 25 * sin ((theta-30) * PI/180.0);
    control_points_array[3].y += sin ((theta-30) * PI/180.0);
    theta += 2;
    glPushMatrix ();
    glPointSize (5);
    glColor3f (0.99, 0.48, 0.19); //saffron
    for (int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0 );
        Bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glColor3f(1, 1, 1); //white
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        Bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glColor3f(0.07, 0.7, 0.03); //green
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        Bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glPopMatrix();
    glLineWidth(5);

    glColor3f(0.64, 0.28, 0.17); //pole colour

    glBegin(GL_LINES);
        glVertex2f(100,420);
        glVertex2f(100,40);
    glEnd();

//    glPointSize(12);
//    glColor3f(0.99, 0.21,0.21); //pole dot
//    glBegin(GL_POINTS);
//        glVertex2f(100,420);
//    glEnd();

    glBegin(GL_POLYGON); // circle
    glColor3f(0.99, 0.21,0.21);
        for(int i=0; i<360; i++)
        {
            Thetha = i*PI/180; //convert to radian
            glVertex2f(xpos+radius*cos(Thetha),ypos+radius*sin(Thetha));
        }

    glEnd();

    glutPostRedisplay();
    glutSwapBuffers();
}
void init ()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.6, 0.6, 0.91, 1);
    gluOrtho2D(0,600,0,600);
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(600,600);
    glutCreateWindow ("National Flag");
    init ();
    glutDisplayFunc (display);
    glutMainLoop ();
}
