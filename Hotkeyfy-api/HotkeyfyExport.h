#pragma once

#ifdef HOTKEYFYAPI_EXPORTS
#define HOTKEYFYAPI_DECLSPEC    __declspec(dllexport)
#else
#define HOTKEYFYAPI_DECLSPEC    __declspec(dllimport)
#endif