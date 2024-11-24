#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    MessageBox(NULL, "Hello, World!", "My Message Box", MB_WARNING);
    return 0;
}
