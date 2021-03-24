//-----------------------------------------------------------------------------
#include "System/GameSystem.h"
#include "IO/Log/Log.h"

#include <iostream>
#include <filesystem>

//#define NewDeleteVisible

using namespace BF;

#ifdef NewDeleteVisible

void* operator new(size_t size)
{
    void* p = malloc(size);

    printf(">>> [NEW] Allocated <%p> %u Byte\n", p, size);

    return p;
}

void operator delete(void* p)
{
    printf(">>> [DELETE] Removed <%p>\n", p);
    free(p);
}

#endif // NewDeleteVisible



//-----------------------------------------------------------------------------
int main()
{    
    GameSystem& system = GameSystem::Instance();
    
	try
	{
        system.Start();

        while (system.IsRunning())
        {
            system.Update();
        }

        system.Stop();
	}
    catch (FileNotFound& fileNotFound)
    {
        printf("%s @ %s", &fileNotFound.ErrorMessage[0], &fileNotFound.FilePath[0]);
    } 

    return 0;
}
//-----------------------------------------------------------------------------
/*
System* sys = System::Instance();


GameTickEvent* t = new GameTickEvent();
t->AddListener([&](GameTickData gameTickData) {OnUpdate(gameTickData); });





template <class T> class MyFunctor
{
private:
    T* ObjectPtr;
    void (T::*MemberFunction) ();
public:
    void operator () ()
    {
        return (*this->ObjectPtr.*this->MemberFunction)();
    }
};



*/