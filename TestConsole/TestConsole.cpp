#include <Window/Window.h>

#include <unistd.h>

int main()
{
    BF::Window window;

    window.Create(200,200, "Hello i bims");

    while(!window.IsRunning);

    window.FrameBufferContextRegister();

    while(1)
    {
#if 0
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
        glEnd();

        window.FrameBufferSwap();


#endif

        //usleep(100000000000);
    }

    return 0;
}
