#ifndef DROP_FILES_CALLBACK_HPP
#define DROP_FILES_CALLBACK_HPP

#include <string>
#include <windows.h>

#include <Game.hpp>

class DropFilesCallback{
    private:
        static LONG_PTR originalSFMLCallback;
        static LRESULT CALLBACK callback( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
    public:
        DropFilesCallback() = delete;
        static void initialize();
};

#endif