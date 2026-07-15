//Tutorial en youtube: https://youtu.be/Z9SKF4H7pVI

#include "pch.h"

//Obtenemos la direccion de memoria en donde esta FL_ONGROUND
uintptr_t FL_ONGROUND = (uintptr_t)GetModuleHandle(L"client.dll") + 0x23A39C8;
int* ground = (int*)FL_ONGROUND;

//Obtenemos la direccion de memoria en donde esta el control de +JUMP
uintptr_t CL_JUMP = (uintptr_t)GetModuleHandle(L"client.dll") + 0x2094490;
int* cl_jump = (int*)CL_JUMP;


//Funcion para correr dentro del programa objetivo
DWORD WINAPI kgAutobunny(LPVOID x)
{
    while (1)
    {
        //Esperamos la pulsacion de space
        if (GetKeyState(VK_SPACE) & 0x80000)
        {
            //Comprueba si esta tocando el piso o no
            if (*ground > 0)
            {
                //Fuerza el salto xD
                *cl_jump = 65537;
            }
            else {
                *cl_jump = 0;
            }
        }
        Sleep(1);
    }
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        //Iniciamos el hilo dentro del proceso del cs2
        CreateThread(NULL, 0, kgAutobunny, NULL, 0, NULL);
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

