#ifndef SOKOL_GFX_EXTENSIONS_INCLUDED
/*
    sokol_gfx_extensions.h


*/
#define SOKOL_GFX_EXTENSIONS_INCLUDED (1)
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

SOKOL_API_DECL void sgx_read_texture_data(const sg_image img_id, void* pixels);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SOKOL_GFX_EXTENSIONS_INCLUDED

/*-- IMPLEMENTATION ----------------------------------------------------------*/
#ifdef SOKOL_IMPL
#define SOKOL_GFX_EXTENSIONS_IMPL_INCLUDED (1)

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

#ifdef _SOKOL_ANY_GL

SOKOL_API_IMPL void sgx_read_texture_data(const sg_image img_id, void* pixels)
{
    _sg_image_t* img = _sg_lookup_image(&_sg.pools, img_id.id);
    const GLenum gl_img_format = _sg_gl_teximage_format(img->cmn.pixel_format);
    const GLenum gl_img_type = _sg_gl_teximage_type(img->cmn.pixel_format);
    const GLenum gl_img_target = img->gl.target;
    const GLuint mip_level = 0;
    glGetTexImage(gl_img_target, mip_level, gl_img_format, gl_img_type, pixels);
}

#endif // _SOKOL_GL_ANY

#endif // SOKOL_IMPL
