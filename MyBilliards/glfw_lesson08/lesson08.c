#include <stdlib.h>    // For malloc() etc.
#include <stdio.h>     // For printf(), fopen() etc.
#include <math.h>      // For sin(), cos() etc.
#include <GL/glfw.h>   // For GLFW, OpenGL and GLU


//----------------------------------------------------------------------
// Draw() - Main OpenGL drawing function that is called each frame
//----------------------------------------------------------------------

void Draw( void )
{
    int    width, height;  // Window dimensions
    double t;              // Time (in seconds)
    GLUquadric *quadric;   // GLU quadrics object
    double field_of_view;  // Camera field of view
    double camera_x, camera_y, camera_z; // Camera position
    int    i;

    // Get current time
    t = glfwGetTime();

    // Get window size
    glfwGetWindowSize( &width, &height );

    // Make sure that height is non-zero to avoid division by zero
    height = height < 1 ? 1 : height;

    // Set viewport
    glViewport( 0, 0, width, height );

    // Clear color and depht buffers
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Calculate field of view as a function of time
    field_of_view = 50.0 + 30.0*sin( 0.5 * t );

    // Set up projection matrix
    glMatrixMode( GL_PROJECTION );    // Select projection matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluPerspective(                   // Set perspective view
        field_of_view,                // Field of view
        (double)width/(double)height, // Window aspect (assumes square pixels)
        1.0,                          // Near Z clipping plane
        100.0                         // Far Z clippling plane
    );

    // Calculate camera position
    camera_x = 20.0 * cos( 0.3 * t );
    camera_z = 20.0 * sin( 0.3 * t );
    camera_y = 4.0 + 1.0 * sin( 1.0 * t );

    // Set up modelview matrix
    glMatrixMode( GL_MODELVIEW );     // Select modelview matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluLookAt(                        // Set camera position and orientation
        camera_x, camera_y, camera_z, // Camera position (x,y,z)
        0.0, 1.0, 0.0,                // View point (x,y,z)
        0.0, 1.0, 0.0                 // Up-vector (x,y,z)
    );

    // Enable Z buffering
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Draw a grid
    glColor3f( 0.7f, 1.0f, 1.0f );
    glBegin( GL_LINES );
    for( i = -10; i <= 10; i ++ )
    {
        glVertex3f( -10.0f, 0.0f, (float)i );  // Line along X axis
        glVertex3f(  10.0f, 0.0f, (float)i );  // -"-
        glVertex3f( (float)i, 0.0f, -10.0f );  // Line along Z axis
        glVertex3f( (float)i, 0.0f,  10.0f );  // -"-
    }
    glEnd();

    // Create a GLU quadrics object
    quadric = gluNewQuadric();

    // Draw a blue cone in the center
    glPushMatrix();
    glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
    glColor3f( 0.0f, 0.0f, 1.0f );
    gluCylinder( quadric, 1.5, 0.0, 4.0, 30, 30 );
    glPopMatrix();

    // Draw four spheres in the corners of the grid
    glColor3f( 1.0f, 0.2f, 0.0f );
    glPushMatrix();
    glTranslatef( -9.0, 1.0, -9.0 );
    gluSphere( quadric, 1.0, 30, 30 );
    glPopMatrix();
    glPushMatrix();
    glTranslatef(  9.0, 1.0, -9.0 );
    gluSphere( quadric, 1.0, 30, 30 );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( -9.0, 1.0,  9.0 );
    gluSphere( quadric, 1.0, 30, 30 );
    glPopMatrix();
    glPushMatrix();
    glTranslatef(  9.0, 1.0,  9.0 );
    gluSphere( quadric, 1.0, 30, 30 );
    glPopMatrix();

    // Destroy the GLU quadrics object
    gluDeleteQuadric( quadric );
}


//----------------------------------------------------------------------
// main() - Program entry point
//----------------------------------------------------------------------

int main( int argc, char **argv )
{
    int    ok;             // Flag telling if the window was opened
    int    running;        // Flag telling if the program is running

    // Initialize GLFW
    glfwInit();

    // Open window
    ok = glfwOpenWindow(
        640, 480,          // Width and height of window
        8, 8, 8,           // Number of red, green, and blue bits for color buffer
        8,                 // Number of bits for alpha buffer
        24,                // Number of bits for depth buffer (Z-buffer)
        0,                 // Number of bits for stencil buffer
        GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
    );

    // If we could not open a window, exit now
    if( !ok )
    {
        glfwTerminate();
        return 0;
    }

    // Set window title
    glfwSetWindowTitle( "My OpenGL program" );

    // Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );

    // Main rendering loop
    do
    {
        // Call our rendering function
        Draw();

        // Swap front and back buffers (we use a double buffered display)
        glfwSwapBuffers();

        // Check if the escape key was pressed, or if the window was closed
        running = !glfwGetKey( GLFW_KEY_ESC ) &&
                  glfwGetWindowParam( GLFW_OPENED );
    }
    while( running );

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    return 0;
}
