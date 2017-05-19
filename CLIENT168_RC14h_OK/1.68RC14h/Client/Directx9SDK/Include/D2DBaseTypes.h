#pragma once


#ifndef _D2DBASETYPES_INCLUDED
#define _D2DBASETYPES_INCLUDED

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#endif // #ifndef COM_NO_WINDOWS_H

#ifndef D3DCOLORVALUE_DEFINED

//+-----------------------------------------------------------------------------
//
//  Struct:
//      D3DCOLORVALUE
//
//------------------------------------------------------------------------------
typedef struct D3DCOLORVALUE
{
    FLOAT r;
    FLOAT g;
    FLOAT b;
    FLOAT a;

} D3DCOLORVALUE;

#define D3DCOLORVALUE_DEFINED
#endif


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_POINT_2U
//
//------------------------------------------------------------------------------
typedef struct D2D_POINT_2U
{
    UINT32 x;
    UINT32 y;

} D2D_POINT_2U;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_POINT_2F
//
//------------------------------------------------------------------------------
typedef struct D2D_POINT_2F
{
    FLOAT x;
    FLOAT y;

} D2D_POINT_2F;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_RECT_F
//
//------------------------------------------------------------------------------
typedef struct D2D_RECT_F
{
    FLOAT left;
    FLOAT top;
    FLOAT right;
    FLOAT bottom;

} D2D_RECT_F;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_RECT_U
//
//------------------------------------------------------------------------------
typedef struct D2D_RECT_U
{
    UINT32 left;
    UINT32 top;
    UINT32 right;
    UINT32 bottom;

} D2D_RECT_U;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_SIZE_F
//
//------------------------------------------------------------------------------
typedef struct D2D_SIZE_F
{
    FLOAT width;
    FLOAT height;

} D2D_SIZE_F;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_SIZE_U
//
//------------------------------------------------------------------------------
typedef struct D2D_SIZE_U
{
    UINT32 width;
    UINT32 height;

} D2D_SIZE_U;

typedef D3DCOLORVALUE D2D_COLOR_F;

//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D_MATRIX_3X2_F
//
//------------------------------------------------------------------------------
typedef struct D2D_MATRIX_3X2_F
{
    FLOAT _11;
    FLOAT _12;
    FLOAT _21;
    FLOAT _22;
    FLOAT _31;
    FLOAT _32;

} D2D_MATRIX_3X2_F;

#endif // #ifndef _D2DBASETYPES_INCLUDED
