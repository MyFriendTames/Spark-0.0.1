#include "DropFilesCallback.hpp"

LONG_PTR DropFilesCallback::originalSFMLCallback( 0x0 );

LRESULT CALLBACK DropFilesCallback::callback( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ){
    if( message == WM_DROPFILES ){
        HDROP hdrop = reinterpret_cast< HDROP >( wParam );
        const UINT filescount = DragQueryFile( hdrop, 0xFFFFFFFF, 0, 0 );
        sf::Vector2f &&position( Game::getMousePosition() );
        for( UINT i = 0; i < filescount; ++i ){
            const UINT length = DragQueryFile( hdrop, i, NULL, 0 );
            std::string path( length + 1, 0 );
            if ( DragQueryFile( hdrop, i, &path[ 0 ], length + 1 ) ){
                if ( Game::screen != 0 ){
                    Game::screen->fileDroped( path, position );
                }
            }
        }
        DragFinish( hdrop );
    }
    return CallWindowProcW( reinterpret_cast< WNDPROC >( DropFilesCallback::originalSFMLCallback ), handle, message, wParam, lParam );
}

void DropFilesCallback::initialize(){
    HWND handle = Game::window.getSystemHandle();
    DragAcceptFiles( handle, true );
    originalSFMLCallback = SetWindowLongPtrW( handle, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( DropFilesCallback::callback ) );
}