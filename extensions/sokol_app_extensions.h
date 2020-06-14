#ifndef SOKOL_APP_EXTENSIONS_INCLUDED
/*
    sokol_app_extensions.h


*/
#define SOKOL_APP_EXTENSIONS_INCLUDED (1)
#include <stdint.h>

#ifndef SOKOL_API_DECL
#if defined(_WIN32) && defined(SOKOL_DLL) && defined(SOKOL_IMPL)
#define SOKOL_API_DECL __declspec(dllexport)
#elif defined(_WIN32) && defined(SOKOL_DLL)
#define SOKOL_API_DECL __declspec(dllimport)
#else
#define SOKOL_API_DECL extern
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

SOKOL_API_DECL void sapp_init_extensions(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SOKOL_APP_EXTENSIONS_INCLUDED

/*-- IMPLEMENTATION ----------------------------------------------------------*/
#ifdef SOKOL_IMPL
#define SOKOL_APP_EXTENSIONS_IMPL_INCLUDED (1)

#include <string.h> // memset

#ifndef SOKOL_API_IMPL
    #define SOKOL_API_IMPL
#endif
#ifndef SOKOL_ASSERT
    #include <assert.h>
    #define SOKOL_ASSERT(c) assert(c)
#endif
#ifndef _SOKOL_PRIVATE
    #if defined(__GNUC__)
        #define _SOKOL_PRIVATE __attribute__((unused)) static
    #else
        #define _SOKOL_PRIVATE static
    #endif
#endif

#ifdef _WIN32
#ifdef SOKOL_GLCORE33

/*
    Load extra GL functions
*/

typedef void (GL_APIENTRY *PFN_glGetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
static PFN_glGetTexImage _sapp_glGetTexImage;
#define glGetTexImage _sapp_glGetTexImage

SOKOL_API_IMPL void _sapp_win32_gl_load_extra_funcs(void){
    _SAPP_GLPROC(glGetTexImage);
}

#endif // SOKOL_GLCORE33
#endif // _WIN32

SOKOL_API_IMPL void sapp_init_extensions(void)
{
#ifdef _WIN32
#ifdef SOKOL_GLCORE33
    _sapp_win32_gl_load_extra_funcs();
#endif
#endif
}

#endif // SOKOL_IMPL