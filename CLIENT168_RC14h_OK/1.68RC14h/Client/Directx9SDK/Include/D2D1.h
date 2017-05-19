#pragma once


#ifndef _D2D1_H_
#define _D2D1_H_

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#endif // #ifndef COM_NO_WINDOWS_H
#include <unknwn.h>
#include <dcommon.h>
#include <D2DErr.h>
#include <D2DBaseTypes.h>
#include <dxgiformat.h>
#ifndef D2D_NO_INCLUDE_D3D10
#include <d3d10_1.h>
#endif // #ifndef D2D_NO_INCLUDE_D3D10

#ifndef D2D_USE_C_DEFINITIONS

//
// We use the 'C' definitions if C++ is not defined
// 
#ifndef __cplusplus
#define D2D_USE_C_DEFINITIONS
#endif

#endif // #ifndef D2D_USE_C_DEFINITIONS

#ifndef D2D1_DECLARE_INTERFACE
#define D2D1_DECLARE_INTERFACE(X) DECLSPEC_UUID(X) DECLSPEC_NOVTABLE
#endif

//
// Forward declarations here
//

typedef interface IDWriteTextFormat IDWriteTextFormat;
typedef interface IDWriteTextLayout IDWriteTextLayout;
typedef interface IDWriteRenderingParams IDWriteRenderingParams;
typedef interface IDXGISurface IDXGISurface;
typedef interface IWICBitmap IWICBitmap;
typedef interface IWICBitmapSource IWICBitmapSource;

typedef struct DWRITE_GLYPH_RUN DWRITE_GLYPH_RUN;

#ifndef D2D_USE_C_DEFINITIONS

interface ID2D1Factory;
interface ID2D1RenderTarget;
interface ID2D1BitmapRenderTarget;
interface ID2D1SimplifiedGeometrySink;
interface ID2D1TessellationSink;
interface ID2D1Geometry;
interface ID2D1Brush;

#else

typedef interface ID2D1Factory ID2D1Factory;
typedef interface ID2D1RenderTarget ID2D1RenderTarget;
typedef interface ID2D1BitmapRenderTarget ID2D1BitmapRenderTarget;
typedef interface ID2D1SimplifiedGeometrySink ID2D1SimplifiedGeometrySink;; 
typedef interface ID2D1TessellationSink ID2D1TessellationSink; 
typedef interface ID2D1Geometry ID2D1Geometry; 
typedef interface ID2D1Brush ID2D1Brush; 

#endif
        
#define D2D1_INVALID_TAG ULONGLONG_MAX
#define D2D1_DEFAULT_FLATTENING_TOLERANCE (0.25f)

//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_ALPHA_MODE
//
//  Synopsis:
//      Qualifies how alpha is to be treated in a bitmap or render target containing
//      alpha.
//
//------------------------------------------------------------------------------
typedef enum D2D1_ALPHA_MODE
{
        
        //
        // Alpha mode should be determined implicitly. Some target surfaces do not supply
        // or imply this information in which case alpha must be specified.
        //
        D2D1_ALPHA_MODE_UNKNOWN = 0,
        
        //
        // Treat the alpha as premultipled.
        //
        D2D1_ALPHA_MODE_PREMULTIPLIED = 1,
        
        //
        // Opacity is in the 'A' component only.
        //
        D2D1_ALPHA_MODE_STRAIGHT = 2,
        
        //
        // Ignore any alpha channel information.
        //
        D2D1_ALPHA_MODE_IGNORE = 3,
        D2D1_ALPHA_MODE_FORCE_DWORD = 0xffffffff

} D2D1_ALPHA_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_GAMMA
//
//  Synopsis:
//      This determines what gamma is used for interpolation/blending.
//
//------------------------------------------------------------------------------
typedef enum D2D1_GAMMA
{
        
        //
        // Colors are manipulated in 2.2 gamma color space.
        //
        D2D1_GAMMA_2_2 = 0,
        
        //
        // Colors are manipulated in 1.0 gamma color space.
        //
        D2D1_GAMMA_1_0 = 1,
        D2D1_GAMMA_FORCE_DWORD = 0xffffffff

} D2D1_GAMMA;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_OPACITY_MASK_CONTENT
//
//  Synopsis:
//      Specifies what the contents are of an opacity mask.
//
//------------------------------------------------------------------------------
typedef enum D2D1_OPACITY_MASK_CONTENT
{
        
        //
        // The mask contains geometries or bitmaps.
        //
        D2D1_OPACITY_MASK_CONTENT_GRAPHICS = 0,
        
        //
        // The mask contains text rendered using one of the natural text modes.
        //
        D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL = 1,
        
        //
        // The mask contains text rendered using one of the GDI compatible text modes.
        //
        D2D1_OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2,
        D2D1_OPACITY_MASK_CONTENT_FORCE_DWORD = 0xffffffff

} D2D1_OPACITY_MASK_CONTENT;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_EXTEND_MODE
//
//  Synopsis:
//      Enum which descibes how to sample from a source outside it's base tile.
//
//------------------------------------------------------------------------------
typedef enum D2D1_EXTEND_MODE
{
        
        //
        // Extend the edges of the source out by clamping sample points outside the source
        // to the edges.
        //
        D2D1_EXTEND_MODE_CLAMP = 0,
        
        //
        // The base tile is drawn untransformed and the remainder are filled by repeating
        // the base tile.
        //
        D2D1_EXTEND_MODE_WRAP = 1,
        
        //
        // The same as wrap, but alternate tiles are flipped  The base tile is drawn
        // untransformed.
        //
        D2D1_EXTEND_MODE_MIRROR = 2,
        D2D1_EXTEND_MODE_FORCE_DWORD = 0xffffffff

} D2D1_EXTEND_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_ANTIALIAS_MODE
//
//  Synopsis:
//      Enum which descibes the manner in which we render edges of non-text primitives.
//
//------------------------------------------------------------------------------
typedef enum D2D1_ANTIALIAS_MODE
{
        
        //
        // The edges of each primitive are antialiased sequentially.
        //
        D2D1_ANTIALIAS_MODE_PER_PRIMITIVE = 0,
        
        //
        // Each pixel is rendered if its pixel center is contained by the geometry.
        //
        D2D1_ANTIALIAS_MODE_ALIASED = 1,
        D2D1_ANTIALIAS_MODE_FORCE_DWORD = 0xffffffff

} D2D1_ANTIALIAS_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_TEXT_ANTIALIAS_MODE
//
//------------------------------------------------------------------------------
typedef enum D2D1_TEXT_ANTIALIAS_MODE
{
        
        //
        // Render text using the current system setting.
        //
        D2D1_TEXT_ANTIALIAS_MODE_DEFAULT = 0,
        
        //
        // Render text using ClearType.
        //
        D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE = 1,
        
        //
        // Render text using gray-scale.
        //
        D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE = 2,
        
        //
        // Render text aliased.
        //
        D2D1_TEXT_ANTIALIAS_MODE_ALIASED = 3,
        D2D1_TEXT_ANTIALIAS_MODE_FORCE_DWORD = 0xffffffff

} D2D1_TEXT_ANTIALIAS_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_BITMAP_INTERPOLATION_MODE
//
//------------------------------------------------------------------------------
typedef enum D2D1_BITMAP_INTERPOLATION_MODE
{
        
        //
        // Nearest Neighbor filtering. Also known as nearest pixel or nearest point
        // sampling.
        //
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
        
        //
        // Linear filtering.
        //
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR = 1,
        D2D1_BITMAP_INTERPOLATION_MODE_FORCE_DWORD = 0xffffffff

} D2D1_BITMAP_INTERPOLATION_MODE;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_DRAW_TEXT_OPTIONS
//
//  Synopsis:
//      Modifications made to the draw text call that influence how the text is
//      rendered.
//
//------------------------------------------------------------------------------
typedef enum D2D1_DRAW_TEXT_OPTIONS
{
        
        //
        // Do not snap the baseline of the text vertically.
        //
        D2D1_DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001,
        
        //
        // Clip the text to the content bounds.
        //
        D2D1_DRAW_TEXT_OPTIONS_CLIP = 0x00000002,
        D2D1_DRAW_TEXT_OPTIONS_NONE = 0x00000000,
        D2D1_DRAW_TEXT_OPTIONS_FORCE_DWORD = 0xffffffff

} D2D1_DRAW_TEXT_OPTIONS;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_DRAW_TEXT_OPTIONS);


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_PIXEL_FORMAT
//
//------------------------------------------------------------------------------
typedef struct D2D1_PIXEL_FORMAT
{
    DXGI_FORMAT format;
    D2D1_ALPHA_MODE alphaMode;

} D2D1_PIXEL_FORMAT;

typedef D2D_POINT_2U D2D1_POINT_2U;
typedef D2D_POINT_2F D2D1_POINT_2F;
typedef D2D_RECT_F D2D1_RECT_F;
typedef D2D_RECT_U D2D1_RECT_U;
typedef D2D_SIZE_F D2D1_SIZE_F;
typedef D2D_SIZE_U D2D1_SIZE_U;
typedef D2D_COLOR_F D2D1_COLOR_F;
typedef D2D_MATRIX_3X2_F D2D1_MATRIX_3X2_F;
typedef UINT64 D2D1_TAG;

//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_BITMAP_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_BITMAP_PROPERTIES
{
    D2D1_PIXEL_FORMAT pixelFormat;
    FLOAT dpiX;
    FLOAT dpiY;

} D2D1_BITMAP_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_GRADIENT_STOP
//
//------------------------------------------------------------------------------
typedef struct D2D1_GRADIENT_STOP
{
    FLOAT position;
    D2D1_COLOR_F color;

} D2D1_GRADIENT_STOP;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_BRUSH_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_BRUSH_PROPERTIES
{
    FLOAT opacity;
    D2D1_MATRIX_3X2_F transform;

} D2D1_BRUSH_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_BITMAP_BRUSH_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_BITMAP_BRUSH_PROPERTIES
{
    D2D1_EXTEND_MODE extendModeX;
    D2D1_EXTEND_MODE extendModeY;
    D2D1_BITMAP_INTERPOLATION_MODE interpolationMode;

} D2D1_BITMAP_BRUSH_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES
{
    D2D1_POINT_2F startPoint;
    D2D1_POINT_2F endPoint;

} D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES
{
    D2D1_POINT_2F center;
    D2D1_POINT_2F gradientOriginOffset;
    FLOAT radiusX;
    FLOAT radiusY;

} D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_ARC_SIZE
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------
typedef enum D2D1_ARC_SIZE
{
        D2D1_ARC_SIZE_SMALL = 0,
        D2D1_ARC_SIZE_LARGE = 1,
        D2D1_ARC_SIZE_FORCE_DWORD = 0xffffffff

} D2D1_ARC_SIZE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_CAP_STYLE
//
//  Synopsis:
//      Enum which descibes the drawing of the ends of a line.
//
//------------------------------------------------------------------------------
typedef enum D2D1_CAP_STYLE
{
        
        //
        // Flat line cap.
        //
        D2D1_CAP_STYLE_FLAT = 0,
        
        //
        // Square line cap.
        //
        D2D1_CAP_STYLE_SQUARE = 1,
        
        //
        // Round line cap.
        //
        D2D1_CAP_STYLE_ROUND = 2,
        
        //
        // Triangle line cap.
        //
        D2D1_CAP_STYLE_TRIANGLE = 3,
        D2D1_CAP_STYLE_FORCE_DWORD = 0xffffffff

} D2D1_CAP_STYLE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_DASH_STYLE
//
//------------------------------------------------------------------------------
typedef enum D2D1_DASH_STYLE
{
        D2D1_DASH_STYLE_SOLID = 0,
        D2D1_DASH_STYLE_DASH = 1,
        D2D1_DASH_STYLE_DOT = 2,
        D2D1_DASH_STYLE_DASH_DOT = 3,
        D2D1_DASH_STYLE_DASH_DOT_DOT = 4,
        D2D1_DASH_STYLE_CUSTOM = 5,
        D2D1_DASH_STYLE_FORCE_DWORD = 0xffffffff

} D2D1_DASH_STYLE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_LINE_JOIN
//
//  Synopsis:
//      Enum which descibes the drawing of the corners on the line.
//
//------------------------------------------------------------------------------
typedef enum D2D1_LINE_JOIN
{
        
        //
        // Miter join.
        //
        D2D1_LINE_JOIN_MITER = 0,
        
        //
        // Bevel join.
        //
        D2D1_LINE_JOIN_BEVEL = 1,
        
        //
        // Round join.
        //
        D2D1_LINE_JOIN_ROUND = 2,
        
        //
        // Miter/Bevel join.
        //
        D2D1_LINE_JOIN_MITER_OR_BEVEL = 3,
        D2D1_LINE_JOIN_FORCE_DWORD = 0xffffffff

} D2D1_LINE_JOIN;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_COMBINE_MODE
//
//  Synopsis:
//      This enumeration describes the type of combine operation to be performed.
//
//------------------------------------------------------------------------------
typedef enum D2D1_COMBINE_MODE
{
        
        //
        // Produce a geometry representing the set of points contained in either
        // the first or the second geometry.
        //
        D2D1_COMBINE_MODE_UNION = 0,
        
        //
        // Produce a geometry representing the set of points common to the first
        // and the second geometries.
        //
        D2D1_COMBINE_MODE_INTERSECT = 1,
        
        //
        // Produce a geometry representing the set of points contained in the
        // first geometry or the second geometry, but not both.
        //
        D2D1_COMBINE_MODE_XOR = 2,
        
        //
        // Produce a geometry representing the set of points contained in the
        // first geometry but not the second geometry.
        //
        D2D1_COMBINE_MODE_EXCLUDE = 3,
        D2D1_COMBINE_MODE_FORCE_DWORD = 0xffffffff

} D2D1_COMBINE_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_GEOMETRY_RELATION
//
//------------------------------------------------------------------------------
typedef enum D2D1_GEOMETRY_RELATION
{
        
        //
        // The relation between the geometries couldn't be determined. This value is never
        // returned by any D2D method.
        //
        D2D1_GEOMETRY_RELATION_UNKNOWN = 0,
        
        //
        // The two geometries do not intersect at all.
        //
        D2D1_GEOMETRY_RELATION_DISJOINT = 1,
        
        //
        // The passed in geometry is entirely contained by the object.
        //
        D2D1_GEOMETRY_RELATION_IS_CONTAINED = 2,
        
        //
        // The object entirely contains the passed in geometry.
        //
        D2D1_GEOMETRY_RELATION_CONTAINS = 3,
        
        //
        // The two geometries overlap but neither completely contains the other.
        //
        D2D1_GEOMETRY_RELATION_OVERLAP = 4,
        D2D1_GEOMETRY_RELATION_FORCE_DWORD = 0xffffffff

} D2D1_GEOMETRY_RELATION;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_GEOMETRY_SIMPLIFICATION_OPTION
//
//  Synopsis:
//      Specifies how simple the output of a simplified geometry sink should be.
//
//------------------------------------------------------------------------------
typedef enum D2D1_GEOMETRY_SIMPLIFICATION_OPTION
{
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES = 0,
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES = 1,
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION_FORCE_DWORD = 0xffffffff

} D2D1_GEOMETRY_SIMPLIFICATION_OPTION;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_FIGURE_BEGIN
//
//  Synopsis:
//      Indicates whether the given figure is filled or hollow.
//
//------------------------------------------------------------------------------
typedef enum D2D1_FIGURE_BEGIN
{
        D2D1_FIGURE_BEGIN_FILLED = 0,
        D2D1_FIGURE_BEGIN_HOLLOW = 1,
        D2D1_FIGURE_BEGIN_FORCE_DWORD = 0xffffffff

} D2D1_FIGURE_BEGIN;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_FIGURE_END
//
//  Synopsis:
//      Indicates whether the figure ir open or closed on its end point.
//
//------------------------------------------------------------------------------
typedef enum D2D1_FIGURE_END
{
        D2D1_FIGURE_END_OPEN = 0,
        D2D1_FIGURE_END_CLOSED = 1,
        D2D1_FIGURE_END_FORCE_DWORD = 0xffffffff

} D2D1_FIGURE_END;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_BEZIER_SEGMENT
//
//  Synopsis:
//      Describes a cubic bezier in a path.
//
//------------------------------------------------------------------------------
typedef struct D2D1_BEZIER_SEGMENT
{
    D2D1_POINT_2F point1;
    D2D1_POINT_2F point2;
    D2D1_POINT_2F point3;

} D2D1_BEZIER_SEGMENT;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_TRIANGLE
//
//  Synopsis:
//      Describes a triangle.
//
//------------------------------------------------------------------------------
typedef struct D2D1_TRIANGLE
{
    D2D1_POINT_2F point1;
    D2D1_POINT_2F point2;
    D2D1_POINT_2F point3;

} D2D1_TRIANGLE;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_PATH_SEGMENT
//
//  Synopsis:
//      Indicates whether the given segment should be stroked, or, if the join between
//      this segment and the previous one should be smooth.
//
//------------------------------------------------------------------------------
typedef enum D2D1_PATH_SEGMENT
{
        D2D1_PATH_SEGMENT_NONE = 0x00000000,
        D2D1_PATH_SEGMENT_FORCE_UNSTROKED = 0x00000001,
        D2D1_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN = 0x00000002,
        D2D1_PATH_SEGMENT_FORCE_DWORD = 0xffffffff

} D2D1_PATH_SEGMENT;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_PATH_SEGMENT);


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_SWEEP_DIRECTION
//
//------------------------------------------------------------------------------
typedef enum D2D1_SWEEP_DIRECTION
{
        D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,
        D2D1_SWEEP_DIRECTION_CLOCKWISE = 1,
        D2D1_SWEEP_DIRECTION_FORCE_DWORD = 0xffffffff

} D2D1_SWEEP_DIRECTION;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_FILL_MODE
//
//------------------------------------------------------------------------------
typedef enum D2D1_FILL_MODE
{
        D2D1_FILL_MODE_ALTERNATE = 0,
        D2D1_FILL_MODE_WINDING = 1,
        D2D1_FILL_MODE_FORCE_DWORD = 0xffffffff

} D2D1_FILL_MODE;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_ARC_SEGMENT
//
//  Synopsis:
//      Describes an arc that is defined as part of a path.
//
//------------------------------------------------------------------------------
typedef struct D2D1_ARC_SEGMENT
{
    D2D1_POINT_2F point;
    D2D1_SIZE_F size;
    FLOAT rotationAngle;
    D2D1_SWEEP_DIRECTION sweepDirection;
    D2D1_ARC_SIZE arcSize;

} D2D1_ARC_SEGMENT;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_QUADRATIC_BEZIER_SEGMENT
//
//------------------------------------------------------------------------------
typedef struct D2D1_QUADRATIC_BEZIER_SEGMENT
{
    D2D1_POINT_2F point1;
    D2D1_POINT_2F point2;

} D2D1_QUADRATIC_BEZIER_SEGMENT;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_ELLIPSE
//
//------------------------------------------------------------------------------
typedef struct D2D1_ELLIPSE
{
    D2D1_POINT_2F point;
    FLOAT radiusX;
    FLOAT radiusY;

} D2D1_ELLIPSE;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_ROUNDED_RECT
//
//------------------------------------------------------------------------------
typedef struct D2D1_ROUNDED_RECT
{
    D2D1_RECT_F rect;
    FLOAT radiusX;
    FLOAT radiusY;

} D2D1_ROUNDED_RECT;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_STROKE_STYLE_PROPERTIES
//
//  Synopsis:
//      Properties, aside from the width, that allow geometric penning to be specified.
//
//------------------------------------------------------------------------------
typedef struct D2D1_STROKE_STYLE_PROPERTIES
{
    D2D1_CAP_STYLE startCap;
    D2D1_CAP_STYLE endCap;
    D2D1_CAP_STYLE dashCap;
    D2D1_LINE_JOIN lineJoin;
    FLOAT miterLimit;
    D2D1_DASH_STYLE dashStyle;
    FLOAT dashOffset;

} D2D1_STROKE_STYLE_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_LAYER_OPTIONS
//
//  Synopsis:
//      Specified options that can be applied when a layer resource is applied to create
//      a layer.
//
//------------------------------------------------------------------------------
typedef enum D2D1_LAYER_OPTIONS
{
        D2D1_LAYER_OPTIONS_NONE = 0x00000000,
        
        //
        // The layer will render correctly for ClearType text. If the render target was set
        // to ClearType previously, the layer will continue to render ClearType. If the
        // render target was set to ClearType and this option is not specified, the render
        // target will be set to render gray-scale until the layer is popped. The caller
        // can override this default by calling SetTextAntialiasMode while within the
        // layer. This flag is slightly slower than the default.
        //
        D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 0x00000001,
        D2D1_LAYER_OPTIONS_FORCE_DWORD = 0xffffffff

} D2D1_LAYER_OPTIONS;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_LAYER_OPTIONS);


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_LAYER_PARAMETERS
//
//------------------------------------------------------------------------------
typedef struct D2D1_LAYER_PARAMETERS
{
    
    //
    // The rectangular clip that will be applied to the layer. The clip is affected by
    // the world transform. Content outside of the content bounds will not render.
    //
    D2D1_RECT_F contentBounds;
    
    //
    // A general mask that can be optionally applied to the content. Content not inside
    // the fill of the mask will not be rendered.
    //
    __field_ecount_opt(1) ID2D1Geometry *geometricMask;
    
    //
    // Specifies whether the mask should be aliased or antialiased.
    //
    D2D1_ANTIALIAS_MODE maskAntialiasMode;
    
    //
    // An additional transform that may be applied to the mask in addition to the
    // current world transform.
    //
    D2D1_MATRIX_3X2_F maskTransform;
    
    //
    // The opacity with which all of the content in the layer will be blended back to
    // the target when the layer is popped.
    //
    FLOAT opacity;
    
    //
    // An additional brush that can be applied to the layer. Only the opacity channel
    // is sampled from this brush and multiplied both with the layer content and the
    // over-all layer opacity.
    //
    __field_ecount_opt(1) ID2D1Brush *opacityBrush;
    
    //
    // Specifies if ClearType will be rendered into the layer.
    //
    D2D1_LAYER_OPTIONS layerOptions;

} D2D1_LAYER_PARAMETERS;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_WINDOW_STATE
//
//------------------------------------------------------------------------------
typedef enum D2D1_WINDOW_STATE
{
        D2D1_WINDOW_STATE_NONE = 0x0000000,
        D2D1_WINDOW_STATE_OCCLUDED = 0x0000001,
        D2D1_WINDOW_STATE_FORCE_DWORD = 0xffffffff

} D2D1_WINDOW_STATE;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_WINDOW_STATE);


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_RENDER_TARGET_TYPE
//
//------------------------------------------------------------------------------
typedef enum D2D1_RENDER_TARGET_TYPE
{
        
        //
        // D2D is free to choose the render target type for the caller.
        //
        D2D1_RENDER_TARGET_TYPE_DEFAULT = 0,
        
        //
        // The render target will render using the CPU.
        //
        D2D1_RENDER_TARGET_TYPE_SOFTWARE = 1,
        
        //
        // The render target will render using the GPU.
        //
        D2D1_RENDER_TARGET_TYPE_HARDWARE = 2,
        D2D1_RENDER_TARGET_TYPE_FORCE_DWORD = 0xffffffff

} D2D1_RENDER_TARGET_TYPE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_FEATURE_LEVEL
//
//------------------------------------------------------------------------------
typedef enum D2D1_FEATURE_LEVEL
{
        
        //
        // The caller does not require a particular underlying D3D device level.
        //
        D2D1_FEATURE_LEVEL_DEFAULT = 0,
        
        //
        // The D3D device level is DX9 compatible.
        //
        D2D1_FEATURE_LEVEL_9 = D3D10_FEATURE_LEVEL_9_1,
        
        //
        // The D3D device level is DX10 compatible.
        //
        D2D1_FEATURE_LEVEL_10 = D3D10_FEATURE_LEVEL_10_0,
        D2D1_FEATURE_LEVEL_FORCE_DWORD = 0xffffffff

} D2D1_FEATURE_LEVEL;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_RENDER_TARGET_USAGE
//
//------------------------------------------------------------------------------
typedef enum D2D1_RENDER_TARGET_USAGE
{
        D2D1_RENDER_TARGET_USAGE_NONE = 0x00000000,
        
        //
        // Rendering will occur locally, if a terminal-services session is established, the
        // bitmap updates will be sent to the terminal services client.
        //
        D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING = 0x00000001,
        
        //
        // The render target will allow a call to GetDC on the IGdiInteropRenderTarget
        // interface. Rendering will also occur locally.
        //
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE = 0x00000002,
        D2D1_RENDER_TARGET_USAGE_FORCE_DWORD = 0xffffffff

} D2D1_RENDER_TARGET_USAGE;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_RENDER_TARGET_USAGE);


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_PRESENT_OPTIONS
//
//  Synopsis:
//      Describes how present should behave.
//
//------------------------------------------------------------------------------
typedef enum D2D1_PRESENT_OPTIONS
{
        D2D1_PRESENT_OPTIONS_NONE = 0x00000000,
        
        //
        // Keep the target contents intact through present.
        //
        D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS = 0x00000001,
        
        //
        // Do not wait for display refresh to commit changes to display.
        //
        D2D1_PRESENT_OPTIONS_IMMEDIATELY = 0x00000002,
        D2D1_PRESENT_OPTIONS_FORCE_DWORD = 0xffffffff

} D2D1_PRESENT_OPTIONS;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_PRESENT_OPTIONS);


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_RENDER_TARGET_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_RENDER_TARGET_PROPERTIES
{
    D2D1_RENDER_TARGET_TYPE type;
    D2D1_PIXEL_FORMAT pixelFormat;
    FLOAT dpiX;
    FLOAT dpiY;
    D2D1_RENDER_TARGET_USAGE usage;
    D2D1_FEATURE_LEVEL minLevel;

} D2D1_RENDER_TARGET_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_HWND_RENDER_TARGET_PROPERTIES
//
//------------------------------------------------------------------------------
typedef struct D2D1_HWND_RENDER_TARGET_PROPERTIES
{
    HWND hwnd;
    D2D1_SIZE_U pixelSize;
    D2D1_PRESENT_OPTIONS presentOptions;

} D2D1_HWND_RENDER_TARGET_PROPERTIES;


//+-----------------------------------------------------------------------------
//
//  Flag:
//      D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS
//
//------------------------------------------------------------------------------
typedef enum D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS
{
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE = 0x00000000,
        
        //
        // The compatible render target will allow a call to GetDC on the
        // IGdiInteropRenderTarget interface. This can be specified even if the parent
        // render target is not GDI compatible.
        //
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE = 0x00000001,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_FORCE_DWORD = 0xffffffff

} D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS;

DEFINE_ENUM_FLAG_OPERATORS(D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS);


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_DRAWING_STATE_DESCRIPTION
//
//  Synopsis:
//      Allows the drawing state to be atomically created. This also specifies the
//      drawing state that is saved into an IDrawingStateBlock object.
//
//------------------------------------------------------------------------------
typedef struct D2D1_DRAWING_STATE_DESCRIPTION
{
    D2D1_ANTIALIAS_MODE antialiasMode;
    D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode;
    D2D1_TAG tag1;
    D2D1_TAG tag2;
    D2D1_MATRIX_3X2_F transform;

} D2D1_DRAWING_STATE_DESCRIPTION;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_DC_INITIALIZE_MODE
//
//------------------------------------------------------------------------------
typedef enum D2D1_DC_INITIALIZE_MODE
{
        
        //
        // The contents of the D2D render target will be copied to the DC.
        //
        D2D1_DC_INITIALIZE_MODE_COPY = 0,
        
        //
        // The contents of the DC will be cleared.
        //
        D2D1_DC_INITIALIZE_MODE_CLEAR = 1,
        D2D1_DC_INITIALIZE_MODE_FORCE_DWORD = 0xffffffff

} D2D1_DC_INITIALIZE_MODE;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_DEBUG_LEVEL
//
//  Synopsis:
//      Indicates the debug level to be outputed by the debug layer.
//
//------------------------------------------------------------------------------
typedef enum D2D1_DEBUG_LEVEL
{
        D2D1_DEBUG_LEVEL_NONE = 0,
        D2D1_DEBUG_LEVEL_ERROR = 1,
        D2D1_DEBUG_LEVEL_WARNING = 2,
        D2D1_DEBUG_LEVEL_INFORMATION = 3,
        D2D1_DEBUG_LEVEL_FORCE_DWORD = 0xffffffff

} D2D1_DEBUG_LEVEL;


//+-----------------------------------------------------------------------------
//
//  Enum:
//      D2D1_FACTORY_TYPE
//
//  Synopsis:
//      Specifies the threading model of the created factory and all of its derived
//      resources.
//
//------------------------------------------------------------------------------
typedef enum D2D1_FACTORY_TYPE
{
        
        //
        // The resulting factory and derived resources may only be invoked serially.
        // Reference counts on resources are interlocked, however, resource and render
        // target state is not protected from multi-threaded access.
        //
        D2D1_FACTORY_TYPE_SINGLE_THREADED = 0,
        
        //
        // The resulting factory may be invoked from multiple threads. Returned resources
        // use interlocked reference counting and their state is protected.
        //
        D2D1_FACTORY_TYPE_MULTI_THREADED = 1,
        D2D1_FACTORY_TYPE_FORCE_DWORD = 0xffffffff

} D2D1_FACTORY_TYPE;


//+-----------------------------------------------------------------------------
//
//  Struct:
//      D2D1_FACTORY_OPTIONS
//
//  Synopsis:
//      Allows additional parameters for factory creation.
//
//------------------------------------------------------------------------------
typedef struct D2D1_FACTORY_OPTIONS
{
    
    //
    // Requests a certain level of debugging information from the debug layer. This
    // parameter is ignored if the debug layer DLL is not present.
    //
    D2D1_DEBUG_LEVEL debugLevel;

} D2D1_FACTORY_OPTIONS;


#ifndef D2D_USE_C_DEFINITIONS



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Resource
//
//  Synopsis:
//      The root interface for all resources in D2D.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd90691-12e2-11dc-9fed-001143a055f9") ID2D1Resource  : public IUnknown
{
    
    
    //
    // Retrieve the factory associated with this resource.
    //
    STDMETHOD_(void, GetFactory)(
        __deref_out ID2D1Factory **factory 
        ) CONST PURE;
}; // interface ID2D1Resource



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Bitmap
//
//  Synopsis:
//      Root bitmap resource, linearly scaled on a draw call.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("a2296057-ea42-4099-983b-539fb6505426") ID2D1Bitmap  : public ID2D1Resource
{
    
    
    //
    // Returns the size of the bitmap in resolution independent units.
    //
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ) CONST PURE;
    
    
    //
    // Returns the size of the bitmap in resolution dependent units, (pixels).
    //
    STDMETHOD_(D2D1_SIZE_U, GetPixelSize)(
        ) CONST PURE;
    
    
    //
    // Retrieve the format of the bitmap.
    //
    STDMETHOD_(D2D1_PIXEL_FORMAT, GetPixelFormat)(
        ) CONST PURE;
    
    
    //
    // Return the DPI of the bitmap.
    //
    STDMETHOD_(void, GetDpi)(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) CONST PURE;
    
    STDMETHOD(CopyFromBitmap)(
        __in_opt CONST D2D1_POINT_2U *destPoint,
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_RECT_U *srcRect 
        ) PURE;
    
    STDMETHOD(CopyFromRenderTarget)(
        __in_opt CONST D2D1_POINT_2U *destPoint,
        __in ID2D1RenderTarget *renderTarget,
        __in_opt CONST D2D1_RECT_U *srcRect 
        ) PURE;
    
    STDMETHOD(CopyFromMemory)(
        __in_opt CONST D2D1_RECT_U *dstRect,
        __in CONST void *srcData,
        UINT32 pitch 
        ) PURE;
}; // interface ID2D1Bitmap



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1GradientStopCollection
//
//  Synopsis:
//      Represents an collection of gradient stops that can then be the source resource
//      for either a linear or radial gradient brush.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a7-12e2-11dc-9fed-001143a055f9") ID2D1GradientStopCollection  : public ID2D1Resource
{
    
    
    //
    // Returns the number of stops in the gradient.
    //
    STDMETHOD_(UINT32, GetGradientStopCount)(
        ) CONST PURE;
    
    
    //
    // Copies the gradient stops from the collection into the caller's interface.
    //
    STDMETHOD_(void, GetGradientStops)(
        __out_ecount(gradientStopsCount) D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount 
        ) CONST PURE;
    
    
    //
    // Returns whether the interpolation occurs with 1.0 or 2.2 gamma.
    //
    STDMETHOD_(D2D1_GAMMA, GetColorInterpolationGamma)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendMode)(
        ) CONST PURE;
}; // interface ID2D1GradientStopCollection



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Brush
//
//  Synopsis:
//      The root brush interface. All brushes can be used to fill or pen a geometry.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a8-12e2-11dc-9fed-001143a055f9") ID2D1Brush  : public ID2D1Resource
{
    
    
    //
    // Sets the opacity for when the brush is drawn over the entire fill of the brush.
    //
    STDMETHOD_(void, SetOpacity)(
        FLOAT opacity 
        ) PURE;
    
    
    //
    // Sets the transform that applies to everything drawn by the brush.
    //
    STDMETHOD_(void, SetTransform)(
        __in CONST D2D1_MATRIX_3X2_F *transform 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetOpacity)(
        ) CONST PURE;
    
    STDMETHOD_(void, GetTransform)(
        __out D2D1_MATRIX_3X2_F *transform 
        ) CONST PURE;
    
    void
    SetTransform(
        CONST D2D1_MATRIX_3X2_F &transform 
        ) 
    {
        SetTransform(&transform);
    }
}; // interface ID2D1Brush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1BitmapBrush
//
//  Synopsis:
//      A bitmap brush allows a bitmap to be used to fill a geometry.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906aa-12e2-11dc-9fed-001143a055f9") ID2D1BitmapBrush  : public ID2D1Brush
{
    
    
    //
    // Sets how the bitmap is to be treated outside of its natural extent on the X
    // axis.
    //
    STDMETHOD_(void, SetExtendModeX)(
        D2D1_EXTEND_MODE extendModeX 
        ) PURE;
    
    
    //
    // Sets how the bitmap is to be treated outside of its natural extent on the X
    // axis.
    //
    STDMETHOD_(void, SetExtendModeY)(
        D2D1_EXTEND_MODE extendModeY 
        ) PURE;
    
    
    //
    // Sets the interpolation mode used when this brush is used.
    //
    STDMETHOD_(void, SetInterpolationMode)(
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode 
        ) PURE;
    
    
    //
    // Sets the bitmap associated as the source of this brush.
    //
    STDMETHOD_(void, SetBitmap)(
        __in ID2D1Bitmap *bitmap 
        ) PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendModeX)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendModeY)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_BITMAP_INTERPOLATION_MODE, GetInterpolationMode)(
        ) CONST PURE;
    
    STDMETHOD_(void, GetBitmap)(
        __deref_out ID2D1Bitmap **bitmap 
        ) CONST PURE;
}; // interface ID2D1BitmapBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1SolidColorBrush
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a9-12e2-11dc-9fed-001143a055f9") ID2D1SolidColorBrush  : public ID2D1Brush
{
    
    STDMETHOD_(void, SetColor)(
        __in CONST D2D1_COLOR_F *color 
        ) PURE;
    
    STDMETHOD_(D2D1_COLOR_F, GetColor)(
        ) CONST PURE;
    
    void
    SetColor(
        CONST D2D1_COLOR_F &color 
        ) 
    {
        SetColor(&color);
    }
}; // interface ID2D1SolidColorBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1LinearGradientBrush
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906ab-12e2-11dc-9fed-001143a055f9") ID2D1LinearGradientBrush  : public ID2D1Brush
{
    
    STDMETHOD_(void, SetStartPoint)(
        D2D1_POINT_2F startPoint 
        ) PURE;
    
    
    //
    // Sets the end point of the gradient in local coordinate space. This is not
    // influenced by the geometry being filled.
    //
    STDMETHOD_(void, SetEndPoint)(
        D2D1_POINT_2F endPoint 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetStartPoint)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetEndPoint)(
        ) CONST PURE;
    
    STDMETHOD_(void, GetGradientStopCollection)(
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) CONST PURE;
}; // interface ID2D1LinearGradientBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1RadialGradientBrush
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906ac-12e2-11dc-9fed-001143a055f9") ID2D1RadialGradientBrush  : public ID2D1Brush
{
    
    
    //
    // Sets the center of the radial gradient. This will be in local coordinates and
    // will not depend on the geometry being filled.
    //
    STDMETHOD_(void, SetCenter)(
        D2D1_POINT_2F center 
        ) PURE;
    
    
    //
    // Sets offset of the origin relative to the radial gradient center.
    //
    STDMETHOD_(void, SetGradientOriginOffset)(
        D2D1_POINT_2F gradientOriginOffset 
        ) PURE;
    
    STDMETHOD_(void, SetRadiusX)(
        FLOAT radiusX 
        ) PURE;
    
    STDMETHOD_(void, SetRadiusY)(
        FLOAT radiusY 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetCenter)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetGradientOriginOffset)(
        ) CONST PURE;
    
    STDMETHOD_(FLOAT, GetRadiusX)(
        ) CONST PURE;
    
    STDMETHOD_(FLOAT, GetRadiusY)(
        ) CONST PURE;
    
    STDMETHOD_(void, GetGradientStopCollection)(
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) CONST PURE;
}; // interface ID2D1RadialGradientBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1StrokeStyle
//
//  Synopsis:
//      Resource interface that holds pen style properties.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd9069d-12e2-11dc-9fed-001143a055f9") ID2D1StrokeStyle  : public ID2D1Resource
{
    
    STDMETHOD_(D2D1_CAP_STYLE, GetStartCap)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_CAP_STYLE, GetEndCap)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_CAP_STYLE, GetDashCap)(
        ) CONST PURE;
    
    STDMETHOD_(FLOAT, GetMiterLimit)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_LINE_JOIN, GetLineJoin)(
        ) CONST PURE;
    
    STDMETHOD_(FLOAT, GetDashOffset)(
        ) CONST PURE;
    
    STDMETHOD_(D2D1_DASH_STYLE, GetDashStyle)(
        ) CONST PURE;
    
    STDMETHOD_(UINT32, GetDashesCount)(
        ) CONST PURE;
    
    
    //
    // Returns the dashes from the object into a user allocated array. The user must
    // call GetDashesCount to retrieve the required size.
    //
    STDMETHOD_(void, GetDashes)(
        __out_ecount(dashesCount) FLOAT *dashes,
        UINT dashesCount 
        ) CONST PURE;
}; // interface ID2D1StrokeStyle



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Geometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a1-12e2-11dc-9fed-001143a055f9") ID2D1Geometry  : public ID2D1Resource
{
    
    
    //
    // Retrieve the bounds of the geometry, with an optional applied transform.
    //
    STDMETHOD(GetBounds)(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out D2D1_RECT_F *bounds 
        ) CONST PURE;
    
    
    //
    // Get the bounds of the corresponding geometry after it has been widened or have
    // an optional pen style applied.
    //
    STDMETHOD(GetWidenedBounds)(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out D2D1_RECT_F *bounds 
        ) CONST PURE;
    
    
    //
    // Checks to see whether the corresponding penned and widened geometry contains the
    // given point.
    //
    STDMETHOD(StrokeContainsPoint)(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) CONST PURE;
    
    
    //
    // Test whether the given fill of this geometry would contain this point.
    //
    STDMETHOD(FillContainsPoint)(
        D2D1_POINT_2F point,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) CONST PURE;
    
    
    //
    // Compare how one geometry intersects or contains another geometry.
    //
    STDMETHOD(CompareWithGeometry)(
        __in ID2D1Geometry *inputGeometry,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) CONST PURE;
    
    
    //
    // Converts a geometry to a simplified geometry that has arcs and quadratic beziers
    // removed.
    //
    STDMETHOD(Simplify)(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST PURE;
    
    
    //
    // Tessellates a geometry into triangles.
    //
    STDMETHOD(Tessellate)(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1TessellationSink *tessellationSink 
        ) CONST PURE;
    
    
    //
    // Performs a combine operation between the two geometries to produce a resulting
    // geometry.
    //
    STDMETHOD(CombineWithGeometry)(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST PURE;
    
    
    //
    // Computes the outline of the geometry. The result is written back into a
    // simplified geometry sink.
    //
    STDMETHOD(Outline)(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST PURE;
    
    
    //
    // Computes the area of the geometry.
    //
    STDMETHOD(ComputeArea)(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *area 
        ) CONST PURE;
    
    
    //
    // Computes the length of the geometry.
    //
    STDMETHOD(ComputeLength)(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *length 
        ) CONST PURE;
    
    
    //
    // Computes the point and tangent a given distance along the path.
    //
    STDMETHOD(ComputePointAtLength)(
        FLOAT length,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) CONST PURE;
    
    
    //
    // Get the geometry and widen it as well as apply an optional pen style.
    //
    STDMETHOD(Widen)(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST PURE;
    
    
    //
    // Retrieve the bounds of the geometry, with an optional applied transform.
    //
    HRESULT
    GetBounds(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out D2D1_RECT_F *bounds 
        ) CONST 
    {
        return GetBounds(&worldTransform, bounds);
    }
    
    
    //
    // Get the bounds of the corresponding geometry after it has been widened or have
    // an optional pen style applied.
    //
    HRESULT
    GetWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out D2D1_RECT_F *bounds 
        ) CONST 
    {
        return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, bounds);
    }
    
    
    //
    // Get the bounds of the corresponding geometry after it has been widened or have
    // an optional pen style applied.
    //
    HRESULT
    GetWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out D2D1_RECT_F *bounds 
        ) CONST 
    {
        return GetWidenedBounds(strokeWidth, strokeStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, bounds);
    }
    
    
    //
    // Get the bounds of the corresponding geometry after it has been widened or have
    // an optional pen style applied.
    //
    HRESULT
    GetWidenedBounds(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out D2D1_RECT_F *bounds 
        ) CONST 
    {
        return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, bounds);
    }
    
    HRESULT
    StrokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) CONST 
    {
        return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, contains);
    }
    
    
    //
    // Checks to see whether the corresponding penned and widened geometry contains the
    // given point.
    //
    HRESULT
    StrokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out BOOL *contains 
        ) CONST 
    {
        return StrokeContainsPoint(point, strokeWidth, strokeStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, contains);
    }
    
    HRESULT
    StrokeContainsPoint(
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out BOOL *contains 
        ) CONST 
    {
        return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, contains);
    }
    
    HRESULT
    FillContainsPoint(
        D2D1_POINT_2F point,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) CONST 
    {
        return FillContainsPoint(point, &worldTransform, flatteningTolerance, contains);
    }
    
    
    //
    // Test whether the given fill of this geometry would contain this point.
    //
    HRESULT
    FillContainsPoint(
        D2D1_POINT_2F point,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out BOOL *contains 
        ) CONST 
    {
        return FillContainsPoint(point, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, contains);
    }
    
    HRESULT
    FillContainsPoint(
        D2D1_POINT_2F point,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out BOOL *contains 
        ) CONST 
    {
        return FillContainsPoint(point, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, contains);
    }
    
    
    //
    // Compare how one geometry intersects or contains another geometry.
    //
    HRESULT
    CompareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        FLOAT flatteningTolerance,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) CONST 
    {
        return CompareWithGeometry(inputGeometry, &inputGeometryTransform, flatteningTolerance, relation);
    }
    
    
    //
    // Compare how one geometry intersects or contains another geometry.
    //
    HRESULT
    CompareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) CONST 
    {
        return CompareWithGeometry(inputGeometry, inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, relation);
    }
    
    
    //
    // Compare how one geometry intersects or contains another geometry.
    //
    HRESULT
    CompareWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) CONST 
    {
        return CompareWithGeometry(inputGeometry, &inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, relation);
    }
    
    
    //
    // Converts a geometry to a simplified geometry that has arcs and quadratic beziers
    // removed.
    //
    HRESULT
    Simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Simplify(simplificationOption, &worldTransform, flatteningTolerance, geometrySink);
    }
    
    
    //
    // Converts a geometry to a simplified geometry that has arcs and quadratic beziers
    // removed.
    //
    HRESULT
    Simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Simplify(simplificationOption, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Converts a geometry to a simplified geometry that has arcs and quadratic beziers
    // removed.
    //
    HRESULT
    Simplify(
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Simplify(simplificationOption, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Tessellates a geometry into triangles.
    //
    HRESULT
    Tessellate(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1TessellationSink *tessellationSink 
        ) CONST 
    {
        return Tessellate(&worldTransform, flatteningTolerance, tessellationSink);
    }
    
    
    //
    // Tessellates a geometry into triangles.
    //
    HRESULT
    Tessellate(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1TessellationSink *tessellationSink 
        ) CONST 
    {
        return Tessellate(worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, tessellationSink);
    }
    
    
    //
    // Tessellates a geometry into triangles.
    //
    HRESULT
    Tessellate(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1TessellationSink *tessellationSink 
        ) CONST 
    {
        return Tessellate(&worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, tessellationSink);
    }
    
    
    //
    // Performs a combine operation between the two geometries to produce a resulting
    // geometry.
    //
    HRESULT
    CombineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, flatteningTolerance, geometrySink);
    }
    
    
    //
    // Performs a combine operation between the two geometries to produce a resulting
    // geometry.
    //
    HRESULT
    CombineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return CombineWithGeometry(inputGeometry, combineMode, inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Performs a combine operation between the two geometries to produce a resulting
    // geometry.
    //
    HRESULT
    CombineWithGeometry(
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        CONST D2D1_MATRIX_3X2_F &inputGeometryTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Computes the outline of the geometry. The result is written back into a
    // simplified geometry sink.
    //
    HRESULT
    Outline(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Outline(&worldTransform, flatteningTolerance, geometrySink);
    }
    
    
    //
    // Computes the outline of the geometry. The result is written back into a
    // simplified geometry sink.
    //
    HRESULT
    Outline(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Outline(worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Computes the outline of the geometry. The result is written back into a
    // simplified geometry sink.
    //
    HRESULT
    Outline(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Outline(&worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Computes the area of the geometry.
    //
    HRESULT
    ComputeArea(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *area 
        ) CONST 
    {
        return ComputeArea(&worldTransform, flatteningTolerance, area);
    }
    
    
    //
    // Computes the area of the geometry.
    //
    HRESULT
    ComputeArea(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out FLOAT *area 
        ) CONST 
    {
        return ComputeArea(worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, area);
    }
    
    
    //
    // Computes the area of the geometry.
    //
    HRESULT
    ComputeArea(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out FLOAT *area 
        ) CONST 
    {
        return ComputeArea(&worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, area);
    }
    
    
    //
    // Computes the length of the geometry.
    //
    HRESULT
    ComputeLength(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *length 
        ) CONST 
    {
        return ComputeLength(&worldTransform, flatteningTolerance, length);
    }
    
    
    //
    // Computes the length of the geometry.
    //
    HRESULT
    ComputeLength(
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out FLOAT *length 
        ) CONST 
    {
        return ComputeLength(worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, length);
    }
    
    
    //
    // Computes the length of the geometry.
    //
    HRESULT
    ComputeLength(
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out FLOAT *length 
        ) CONST 
    {
        return ComputeLength(&worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, length);
    }
    
    
    //
    // Computes the point and tangent a given distance along the path.
    //
    HRESULT
    ComputePointAtLength(
        FLOAT length,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) CONST 
    {
        return ComputePointAtLength(length, &worldTransform, flatteningTolerance, point, unitTangentVector);
    }
    
    
    //
    // Computes the point and tangent a given distance along the path.
    //
    HRESULT
    ComputePointAtLength(
        FLOAT length,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) CONST 
    {
        return ComputePointAtLength(length, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector);
    }
    
    
    //
    // Computes the point and tangent a given distance along the path.
    //
    HRESULT
    ComputePointAtLength(
        FLOAT length,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) CONST 
    {
        return ComputePointAtLength(length, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector);
    }
    
    
    //
    // Get the geometry and widen it as well as apply an optional pen style.
    //
    HRESULT
    Widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Widen(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, geometrySink);
    }
    
    
    //
    // Get the geometry and widen it as well as apply an optional pen style.
    //
    HRESULT
    Widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Widen(strokeWidth, strokeStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
    
    
    //
    // Get the geometry and widen it as well as apply an optional pen style.
    //
    HRESULT
    Widen(
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        CONST D2D1_MATRIX_3X2_F &worldTransform,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) CONST 
    {
        return Widen(strokeWidth, strokeStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
    }
}; // interface ID2D1Geometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1RectangleGeometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a2-12e2-11dc-9fed-001143a055f9") ID2D1RectangleGeometry  : public ID2D1Geometry
{
    
    STDMETHOD_(void, GetRect)(
        __out D2D1_RECT_F *rect 
        ) CONST PURE;
}; // interface ID2D1RectangleGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1RoundedRectangleGeometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a3-12e2-11dc-9fed-001143a055f9") ID2D1RoundedRectangleGeometry  : public ID2D1Geometry
{
    
    STDMETHOD_(void, GetRoundedRect)(
        __out D2D1_ROUNDED_RECT *roundedRect 
        ) CONST PURE;
}; // interface ID2D1RoundedRectangleGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1EllipseGeometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a4-12e2-11dc-9fed-001143a055f9") ID2D1EllipseGeometry  : public ID2D1Geometry
{
    
    STDMETHOD_(void, GetEllipse)(
        __out D2D1_ELLIPSE *ellipse 
        ) CONST PURE;
}; // interface ID2D1EllipseGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1GeometryGroup
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a6-12e2-11dc-9fed-001143a055f9") ID2D1GeometryGroup  : public ID2D1Geometry
{
    
    STDMETHOD_(D2D1_FILL_MODE, GetFillMode)(
        ) CONST PURE;
    
    STDMETHOD_(UINT32, GetSourceGeometryCount)(
        ) CONST PURE;
    
    STDMETHOD_(void, GetSourceGeometries)(
        __out_ecount(geometriesCount) ID2D1Geometry **geometries,
        UINT geometriesCount 
        ) CONST PURE;
}; // interface ID2D1GeometryGroup



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1TransformedGeometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906bb-12e2-11dc-9fed-001143a055f9") ID2D1TransformedGeometry  : public ID2D1Geometry
{
    
    STDMETHOD_(void, GetSourceGeometry)(
        __deref_out ID2D1Geometry **sourceGeometry 
        ) CONST PURE;
    
    STDMETHOD_(void, GetTransform)(
        __out D2D1_MATRIX_3X2_F *transform 
        ) CONST PURE;
}; // interface ID2D1TransformedGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1SimplifiedGeometrySink
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd9069e-12e2-11dc-9fed-001143a055f9") ID2D1SimplifiedGeometrySink  : public IUnknown
{
    
    STDMETHOD_(void, SetFillMode)(
        D2D1_FILL_MODE fillMode 
        ) PURE;
    
    STDMETHOD_(void, SetSegmentFlags)(
        D2D1_PATH_SEGMENT vertexFlags 
        ) PURE;
    
    STDMETHOD_(void, BeginFigure)(
        D2D1_POINT_2F startPoint,
        D2D1_FIGURE_BEGIN figureBegin 
        ) PURE;
    
    STDMETHOD_(void, AddLines)(
        __in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
        UINT pointsCount 
        ) PURE;
    
    STDMETHOD_(void, AddBeziers)(
        __in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        ) PURE;
    
    STDMETHOD_(void, EndFigure)(
        D2D1_FIGURE_END figureEnd 
        ) PURE;
    
    STDMETHOD(Close)(
        ) PURE;
}; // interface ID2D1SimplifiedGeometrySink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1GeometrySink
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd9069f-12e2-11dc-9fed-001143a055f9") ID2D1GeometrySink  : public ID2D1SimplifiedGeometrySink
{
    
    STDMETHOD_(void, AddLine)(
        D2D1_POINT_2F point 
        ) PURE;
    
    STDMETHOD_(void, AddBezier)(
        __in CONST D2D1_BEZIER_SEGMENT *bezier 
        ) PURE;
    
    STDMETHOD_(void, AddQuadraticBezier)(
        __in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier 
        ) PURE;
    
    STDMETHOD_(void, AddQuadraticBeziers)(
        __in_ecount(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        ) PURE;
    
    STDMETHOD_(void, AddArc)(
        __in CONST D2D1_ARC_SEGMENT *arc 
        ) PURE;
    
    void
    AddBezier(
        CONST D2D1_BEZIER_SEGMENT &bezier 
        ) 
    {
        AddBezier(&bezier);
    }
    
    void
    AddQuadraticBezier(
        CONST D2D1_QUADRATIC_BEZIER_SEGMENT &bezier 
        ) 
    {
        AddQuadraticBezier(&bezier);
    }
    
    void
    AddArc(
        CONST D2D1_ARC_SEGMENT &arc 
        ) 
    {
        AddArc(&arc);
    }
}; // interface ID2D1GeometrySink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1TessellationSink
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906c1-12e2-11dc-9fed-001143a055f9") ID2D1TessellationSink  : public IUnknown
{
    
    STDMETHOD_(void, AddTriangles)(
        __in_ecount(trianglesCount) CONST D2D1_TRIANGLE *triangles,
        UINT trianglesCount 
        ) PURE;
    
    STDMETHOD(Close)(
        ) PURE;
}; // interface ID2D1TessellationSink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1PathGeometry
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906a5-12e2-11dc-9fed-001143a055f9") ID2D1PathGeometry  : public ID2D1Geometry
{
    
    
    //
    // Opens a geometry sink that will be used to create this path geometry.
    //
    STDMETHOD(Open)(
        __deref_out ID2D1GeometrySink **geometrySink 
        ) PURE;
    
    
    //
    // Retrieve the contents of this geometry. The caller passes an implementation of a
    // ID2D1GeometrySink interface to receive the data.
    //
    STDMETHOD(Stream)(
        __in ID2D1GeometrySink *geometrySink 
        ) CONST PURE;
    
    STDMETHOD(GetSegmentCount)(
        __out UINT32 *count 
        ) CONST PURE;
    
    STDMETHOD(GetFigureCount)(
        __out UINT32 *count 
        ) CONST PURE;
}; // interface ID2D1PathGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Mesh
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd906c2-12e2-11dc-9fed-001143a055f9") ID2D1Mesh  : public ID2D1Resource
{
    
    
    //
    // Opens the mesh for population.
    //
    STDMETHOD(Open)(
        __deref_out ID2D1TessellationSink **tessellationSink 
        ) PURE;
}; // interface ID2D1Mesh



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Layer
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd9069b-12e2-11dc-9fed-001143a055f9") ID2D1Layer  : public ID2D1Resource
{
    
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ) CONST PURE;
}; // interface ID2D1Layer



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1DrawingStateBlock
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("28506e39-ebf6-46a1-bb47-fd85565ab957") ID2D1DrawingStateBlock  : public ID2D1Resource
{
    
    
    //
    // Retrieves the state currently contained within this state block resource.
    //
    STDMETHOD_(void, GetDescription)(
        __out D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        ) CONST PURE;
    
    
    //
    // Sets the state description of this state block resource.
    //
    STDMETHOD_(void, SetDescription)(
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        ) PURE;
    
    
    //
    // Sets the text rendering parameters of this state block resource.
    //
    STDMETHOD_(void, SetTextRenderingParams)(
        __in_opt IDWriteRenderingParams *textRenderingParams = NULL 
        ) PURE;
    
    
    //
    // Retrieves the text rendering parameters contained within this state block
    // resource. If a NULL text rendering parameter was specified, NULL will be
    // returned.
    //
    STDMETHOD_(void, GetTextRenderingParams)(
        __deref_out_opt IDWriteRenderingParams **textRenderingParams 
        ) CONST PURE;
    
    void
    SetDescription(
        CONST D2D1_DRAWING_STATE_DESCRIPTION &stateDescription 
        ) 
    {
        SetDescription(&stateDescription);
    }
}; // interface ID2D1DrawingStateBlock



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1RenderTarget
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd90694-12e2-11dc-9fed-001143a055f9") ID2D1RenderTarget  : public ID2D1Resource
{
    
    
    //
    // Create a D2D bitmap by copying from memory, or create uninitialized.
    //
    STDMETHOD(CreateBitmap)(
        D2D1_SIZE_U size,
        __in_opt CONST void *srcData,
        UINT32 pitch,
        __in CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    
    //
    // Create a D2D bitmap by copying a WIC bitmap.
    //
    STDMETHOD(CreateBitmapFromWicBitmap)(
        __in IWICBitmapSource *wicBitmapSource,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    
    //
    // Create a D2D bitmap by sharing bits from another resource. The bitmap must be
    // compatible with the render target for the call to succeed.
    // For example, an IWICBitmap can be shared with a software target, or a DXGI
    // surface can be shared with a DXGI render target.
    //
    STDMETHOD(CreateSharedBitmap)(
        __in REFIID riid,
        __inout void *data,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    
    //
    // Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
    // or pen a geometry.
    //
    STDMETHOD(CreateBitmapBrush)(
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __deref_out ID2D1BitmapBrush **bitmapBrush 
        ) PURE;
    
    STDMETHOD(CreateSolidColorBrush)(
        __in CONST D2D1_COLOR_F *color,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __deref_out ID2D1SolidColorBrush **solidColorBrush 
        ) PURE;
    
    
    //
    // A gradient stop collection represents a set of stops in an ideal unit length.
    // This is the source resource for a linear gradient and radial gradient brush.
    //
    STDMETHOD(CreateGradientStopCollection)(
        __in_ecount(gradientStopsCount) CONST D2D1_GRADIENT_STOP *gradientStops,
        __range(>=,1) UINT gradientStopsCount,
        
        //
        // Specifies which space the color interpolation occurs in.
        //
        D2D1_GAMMA colorInterpolationGamma,
        
        //
        // Specifies how the gradient will be extended outside of the unit length.
        //
        D2D1_EXTEND_MODE extendMode,
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) PURE;
    
    STDMETHOD(CreateLinearGradientBrush)(
        __in CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1LinearGradientBrush **linearGradientBrush 
        ) PURE;
    
    STDMETHOD(CreateRadialGradientBrush)(
        __in CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1RadialGradientBrush **radialGradientBrush 
        ) PURE;
    
    
    //
    // Creates a bitmap render target whose bitmap can be used as a source for
    // rendering in the API.
    //
    STDMETHOD(CreateCompatibleRenderTarget)(
        
        //
        // The requested size of the target in DIPs. If the pixel size is not specified,
        // the DPI is inherited from the parent target. However, the render target will
        // never contain a fractional number of pixels.
        //
        __in_opt CONST D2D1_SIZE_F *desiredSize,
        
        //
        // The requested size of the render target in pixels. If the DIP size is also
        // specified, the DPI is calculated from these two values. If the desired size is
        // not specified, the DPI is inherited from the parent render target. If neither
        // value is specified, the compatible render target will be the same size and have
        // the same DPI as the parent target.
        //
        __in_opt CONST D2D1_SIZE_U *desiredPixelSize,
        
        //
        // The desired pixel format. The format must be compatible with the parent render
        // target type. If the format is not specified, it will be inherited from the
        // parent render target.
        //
        __in_opt CONST D2D1_PIXEL_FORMAT *desiredFormat,
        
        //
        // Allows the caller to retrieve a GDI compatible render target.
        //
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        
        //
        // The returned bitmap render target.
        //
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) PURE;
    
    
    //
    // Creates a layer resource that can be used on any target and which will resize
    // under the covers if necessary.
    //
    STDMETHOD(CreateLayer)(
        
        //
        // The resolution independent minimum size hint for the layer resource. Specify
        // this to prevent unwanted reallocation of the layer backing store. The size is in
        // DIPs, but, it is unaffected by the current world transform. If the size is
        // unspecified, the returned resource is a placeholder and the backing store will
        // be allocated to be the minimum size that can hold the content when the layer is
        // pushed.
        //
        __in_opt CONST D2D1_SIZE_F *size,
        __deref_out ID2D1Layer **layer 
        ) PURE;
    
    
    //
    // Create a D2D mesh.
    //
    STDMETHOD(CreateMesh)(
        __deref_out ID2D1Mesh **mesh 
        ) PURE;
    
    STDMETHOD_(void, DrawLine)(
        D2D1_POINT_2F point0,
        D2D1_POINT_2F point1,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) PURE;
    
    STDMETHOD_(void, DrawRectangle)(
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) PURE;
    
    STDMETHOD_(void, FillRectangle)(
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawRoundedRectangle)(
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) PURE;
    
    STDMETHOD_(void, FillRoundedRectangle)(
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawEllipse)(
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) PURE;
    
    STDMETHOD_(void, FillEllipse)(
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawGeometry)(
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) PURE;
    
    STDMETHOD_(void, FillGeometry)(
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        
        //
        // An optionally specified opacity brush. Only the alpha channel of the
        // corresponding brush will be sampled and will be applied to the entire fill of
        // the geometry. If this brush is specified, the fill brush must be a bitmap brush
        // with an extend mode of D2D1_EXTEND_MODE_CLAMP.
        //
        __in_opt ID2D1Brush *opacityBrush = NULL 
        ) PURE;
    
    
    //
    // Fill a mesh. Since meshes can only render aliased content, the render target
    // antialiasing mode must be set to aliased.
    //
    STDMETHOD_(void, FillMesh)(
        __in ID2D1Mesh *mesh,
        __in ID2D1Brush *brush 
        ) PURE;
    
    
    //
    // Fill using the opacity channel of the supplied bitmap as a mask. The alpha
    // channel of the bitmap is used to represent the coverage of the geometry at each
    // pixel, and this is filled appropriately with the brush. The render target
    // antialiasing mode must be set to aliased.
    //
    STDMETHOD_(void, FillOpacityMask)(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        D2D1_OPACITY_MASK_CONTENT content,
        __in_opt CONST D2D1_RECT_F *destinationRectangle = NULL,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        ) PURE;
    
    STDMETHOD_(void, DrawBitmap)(
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_RECT_F *destinationRectangle = NULL,
        FLOAT opacity = 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        ) PURE;
    
    
    //
    // Draws the text within the given layout rectangle and by default also snaps and
    // clips it to the content bounds.
    //
    STDMETHOD_(void, DrawText)(
        __in_ecount(stringLength) CONST WCHAR *string,
        UINT stringLength,
        __in IDWriteTextFormat *textFormat,
        __in CONST D2D1_RECT_F *layoutRect,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        ) PURE;
    
    
    //
    // Draw a snapped text layout object. Since the layout is not subsequently changed,
    // this can be more effecient than DrawText when drawing the same layout
    // repeatedly.
    //
    STDMETHOD_(void, DrawTextLayout)(
        D2D1_POINT_2F origin,
        __in IDWriteTextLayout *textLayout,
        __in ID2D1Brush *defaultForegroundBrush,
        
        //
        // The specified text options. NOTE: By default the text is clipped to the layout
        // bounds. This is derived from the origin and the layout bounds of the
        // corresponding IDWriteTextLayout object.
        //
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE 
        ) PURE;
    
    STDMETHOD_(void, DrawGlyphRun)(
        D2D1_POINT_2F baselineOrigin,
        __in CONST DWRITE_GLYPH_RUN *glyphRun,
        __in ID2D1Brush *foregroundBrush,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        ) PURE;
    
    STDMETHOD_(void, SetTransform)(
        __in CONST D2D1_MATRIX_3X2_F *transform 
        ) PURE;
    
    STDMETHOD_(void, GetTransform)(
        __out D2D1_MATRIX_3X2_F *transform 
        ) CONST PURE;
    
    STDMETHOD_(void, SetAntialiasMode)(
        D2D1_ANTIALIAS_MODE antialiasMode 
        ) PURE;
    
    STDMETHOD_(D2D1_ANTIALIAS_MODE, GetAntialiasMode)(
        ) CONST PURE;
    
    STDMETHOD_(void, SetTextAntialiasMode)(
        D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode 
        ) PURE;
    
    STDMETHOD_(D2D1_TEXT_ANTIALIAS_MODE, GetTextAntialiasMode)(
        ) CONST PURE;
    
    STDMETHOD_(void, SetTextRenderingParams)(
        __in_opt IDWriteRenderingParams *textRenderingParams = NULL 
        ) PURE;
    
    
    //
    // Retrieve the text render parameters. NOTE: If NULL is specified to
    // SetTextRenderingParameters, NULL will be returned.
    //
    STDMETHOD_(void, GetTextRenderingParams)(
        __deref_out_opt IDWriteRenderingParams **textRenderingParams 
        ) CONST PURE;
    
    
    //
    // Set a tag to correspond to the succeeding primitives. If an error occurs
    // rendering a primtive, the tags can be returned from the Flush or EndDraw call.
    //
    STDMETHOD_(void, SetTags)(
        D2D1_TAG tag1,
        D2D1_TAG tag2 
        ) PURE;
    
    
    //
    // Retrieves the currently set tags. This does not retrieve the tags corresponding
    // to any primitive that is in error.
    //
    STDMETHOD_(void, GetTags)(
        __out_opt D2D1_TAG *tag1 = NULL,
        __out_opt D2D1_TAG *tag2 = NULL 
        ) CONST PURE;
    
    
    //
    // Start a layer of drawing calls. The way in which the layer must be resolved is
    // specified first as well as the logical resource that stores the layer
    // parameters. The supplied layer resource might grow if the specified content
    // cannot fit inside it. The layer will grow monitonically on each axis.
    //
    STDMETHOD_(void, PushLayer)(
        __in CONST D2D1_LAYER_PARAMETERS *layerParameters,
        __in ID2D1Layer *layer 
        ) PURE;
    
    
    //
    // Ends a layer that was defined with particular layer resources.
    //
    STDMETHOD_(void, PopLayer)(
        ) PURE;
    
    STDMETHOD(Flush)(
        __out_opt D2D1_TAG *tag1 = NULL,
        __out_opt D2D1_TAG *tag2 = NULL 
        ) PURE;
    
    
    //
    // Gets the current drawing state and saves it into the supplied
    // IDrawingStatckBlock.
    //
    STDMETHOD_(void, SaveDrawingState)(
        __inout ID2D1DrawingStateBlock *drawingStateBlock 
        ) CONST PURE;
    
    
    //
    // Copies the state stored in the block interface.
    //
    STDMETHOD_(void, RestoreDrawingState)(
        __in ID2D1DrawingStateBlock *drawingStateBlock 
        ) PURE;
    
    
    //
    // Pushes a clip. The clip can be antialiased. The clip must be axis aligned. If
    // the current world transform is not axis preserving, then the bounding box of the
    // transformed clip rect will be used. The clip will remain in effect until a
    // PopAxisAligned clip call is made.
    //
    STDMETHOD_(void, PushAxisAlignedClip)(
        __in CONST D2D1_RECT_F *clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode 
        ) PURE;
    
    STDMETHOD_(void, PopAxisAlignedClip)(
        ) PURE;
    
    STDMETHOD_(void, Clear)(
        __in_opt CONST D2D1_COLOR_F *clearColor = NULL 
        ) PURE;
    
    
    //
    // Start drawing on this render target. Draw calls can only be issued between a
    // BeginDraw and EndDraw call.
    //
    STDMETHOD_(void, BeginDraw)(
        ) PURE;
    
    
    //
    // Ends drawing on the render target, error results can be retrieved at this time,
    // or when calling flush.
    //
    STDMETHOD(EndDraw)(
        __out_opt D2D1_TAG *tag1 = NULL,
        __out_opt D2D1_TAG *tag2 = NULL 
        ) PURE;
    
    STDMETHOD_(D2D1_PIXEL_FORMAT, GetPixelFormat)(
        ) CONST PURE;
    
    
    //
    // Sets the DPI on the render target. This results in the render target being
    // interpretted to a different scale. Neither DPI can be negative. If zero is
    // specified for both, the system DPI is chosen. If one is zero and the other
    // unspecified, the DPI is not changed.
    //
    STDMETHOD_(void, SetDpi)(
        FLOAT dpiX,
        FLOAT dpiY 
        ) PURE;
    
    
    //
    // Return the current DPI from the target.
    //
    STDMETHOD_(void, GetDpi)(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) CONST PURE;
    
    
    //
    // Returns the size of the render target in DIPs.
    //
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ) CONST PURE;
    
    
    //
    // Returns the size of the render target in pixels.
    //
    STDMETHOD_(D2D1_SIZE_U, GetPixelSize)(
        ) CONST PURE;
    
    
    //
    // Returns the maximum bitmap and render target size that is guaranteed to be
    // supported by the render target.
    //
    STDMETHOD_(UINT32, GetMaximumBitmapSize)(
        ) CONST PURE;
    
    
    //
    // Returns true if the given properties are supported by this render target. The
    // DPI is ignored. NOTE: If the render target type is software, then neither
    // D2D1_FEATURE_LEVEL_9 nor D2D1_FEATURE_LEVEL_10 will be considered to be
    // supported.
    //
    STDMETHOD_(BOOL, IsSupported)(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties 
        ) CONST PURE;
    
    HRESULT
    CreateBitmap(
        D2D1_SIZE_U size,
        __in_opt CONST void *srcData,
        UINT32 pitch,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) 
    {
        return CreateBitmap(size, srcData, pitch, &bitmapProperties, bitmap);
    }
    
    HRESULT
    CreateBitmap(
        D2D1_SIZE_U size,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) 
    {
        return CreateBitmap(size, NULL, 0, &bitmapProperties, bitmap);
    }
    
    
    //
    // Create a D2D bitmap by copying a WIC bitmap.
    //
    HRESULT
    CreateBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        CONST D2D1_BITMAP_PROPERTIES &bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) 
    {
        return CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap);
    }
    
    
    //
    // Create a D2D bitmap by copying a WIC bitmap.
    //
    HRESULT
    CreateBitmapFromWicBitmap(
        __in IWICBitmapSource *wicBitmapSource,
        __deref_out ID2D1Bitmap **bitmap 
        ) 
    {
        return CreateBitmapFromWicBitmap(wicBitmapSource, NULL, bitmap);
    }
    
    
    //
    // Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
    // or pen a geometry.
    //
    HRESULT
    CreateBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        __deref_out ID2D1BitmapBrush **bitmapBrush 
        ) 
    {
        return CreateBitmapBrush(bitmap, NULL, NULL, bitmapBrush);
    }
    
    
    //
    // Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
    // or pen a geometry.
    //
    HRESULT
    CreateBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
        __deref_out ID2D1BitmapBrush **bitmapBrush 
        ) 
    {
        return CreateBitmapBrush(bitmap, &bitmapBrushProperties, NULL, bitmapBrush);
    }
    
    
    //
    // Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
    // or pen a geometry.
    //
    HRESULT
    CreateBitmapBrush(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __deref_out ID2D1BitmapBrush **bitmapBrush 
        ) 
    {
        return CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush);
    }
    
    HRESULT
    CreateSolidColorBrush(
        CONST D2D1_COLOR_F &color,
        __deref_out ID2D1SolidColorBrush **solidColorBrush 
        ) 
    {
        return CreateSolidColorBrush(&color, NULL, solidColorBrush);
    }
    
    HRESULT
    CreateSolidColorBrush(
        CONST D2D1_COLOR_F &color,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __deref_out ID2D1SolidColorBrush **solidColorBrush 
        ) 
    {
        return CreateSolidColorBrush(&color, &brushProperties, solidColorBrush);
    }
    
    HRESULT
    CreateGradientStopCollection(
        __in_ecount(gradientStopsCount) CONST D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount,
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) 
    {
        return CreateGradientStopCollection(gradientStops, gradientStopsCount, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, gradientStopCollection);
    }
    
    HRESULT
    CreateLinearGradientBrush(
        CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1LinearGradientBrush **linearGradientBrush 
        ) 
    {
        return CreateLinearGradientBrush(&linearGradientBrushProperties, NULL, gradientStopCollection, linearGradientBrush);
    }
    
    HRESULT
    CreateLinearGradientBrush(
        CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1LinearGradientBrush **linearGradientBrush 
        ) 
    {
        return CreateLinearGradientBrush(&linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush);
    }
    
    HRESULT
    CreateRadialGradientBrush(
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1RadialGradientBrush **radialGradientBrush 
        ) 
    {
        return CreateRadialGradientBrush(&radialGradientBrushProperties, NULL, gradientStopCollection, radialGradientBrush);
    }
    
    HRESULT
    CreateRadialGradientBrush(
        CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
        CONST D2D1_BRUSH_PROPERTIES &brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1RadialGradientBrush **radialGradientBrush 
        ) 
    {
        return CreateRadialGradientBrush(&radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush);
    }
    
    HRESULT
    CreateCompatibleRenderTarget(
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) 
    {
        return CreateCompatibleRenderTarget(NULL, NULL, NULL, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
    }
    
    HRESULT
    CreateCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) 
    {
        return CreateCompatibleRenderTarget(&desiredSize, NULL, NULL, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
    }
    
    HRESULT
    CreateCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) 
    {
        return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, NULL, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
    }
    
    HRESULT
    CreateCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        D2D1_PIXEL_FORMAT desiredFormat,
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) 
    {
        return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
    }
    
    HRESULT
    CreateCompatibleRenderTarget(
        D2D1_SIZE_F desiredSize,
        D2D1_SIZE_U desiredPixelSize,
        D2D1_PIXEL_FORMAT desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) 
    {
        return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, options, bitmapRenderTarget);
    }
    
    HRESULT
    CreateLayer(
        D2D1_SIZE_F size,
        __deref_out ID2D1Layer **layer 
        ) 
    {
        return CreateLayer(&size, layer);
    }
    
    HRESULT
    CreateLayer(
        __deref_out ID2D1Layer **layer 
        ) 
    {
        return CreateLayer(NULL, layer);
    }
    
    void
    DrawRectangle(
        CONST D2D1_RECT_F &rect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) 
    {
        DrawRectangle(&rect, brush, strokeWidth, strokeStyle);
    }
    
    void
    FillRectangle(
        CONST D2D1_RECT_F &rect,
        __in ID2D1Brush *brush 
        ) 
    {
        FillRectangle(&rect, brush);
    }
    
    void
    DrawRoundedRectangle(
        CONST D2D1_ROUNDED_RECT &roundedRect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) 
    {
        DrawRoundedRectangle(&roundedRect, brush, strokeWidth, strokeStyle);
    }
    
    void
    FillRoundedRectangle(
        CONST D2D1_ROUNDED_RECT &roundedRect,
        __in ID2D1Brush *brush 
        ) 
    {
        FillRoundedRectangle(&roundedRect, brush);
    }
    
    void
    DrawEllipse(
        CONST D2D1_ELLIPSE &ellipse,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth = 1.0f,
        __in_opt ID2D1StrokeStyle *strokeStyle = NULL 
        ) 
    {
        DrawEllipse(&ellipse, brush, strokeWidth, strokeStyle);
    }
    
    void
    FillEllipse(
        CONST D2D1_ELLIPSE &ellipse,
        __in ID2D1Brush *brush 
        ) 
    {
        FillEllipse(&ellipse, brush);
    }
    
    void
    FillOpacityMask(
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        D2D1_OPACITY_MASK_CONTENT content,
        CONST D2D1_RECT_F &destinationRectangle,
        CONST D2D1_RECT_F &sourceRectangle 
        ) 
    {
        FillOpacityMask(opacityMask, brush, content, &destinationRectangle, &sourceRectangle);
    }
    
    void
    DrawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity = 1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        __in_opt CONST D2D1_RECT_F *sourceRectangle = NULL 
        ) 
    {
        DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle);
    }
    
    void
    DrawBitmap(
        __in ID2D1Bitmap *bitmap,
        CONST D2D1_RECT_F &destinationRectangle,
        FLOAT opacity,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
        CONST D2D1_RECT_F &sourceRectangle 
        ) 
    {
        DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle);
    }
    
    void
    SetTransform(
        CONST D2D1_MATRIX_3X2_F &transform 
        ) 
    {
        SetTransform(&transform);
    }
    
    void
    PushLayer(
        CONST D2D1_LAYER_PARAMETERS &layerParameters,
        __in ID2D1Layer *layer 
        ) 
    {
        PushLayer(&layerParameters, layer);
    }
    
    void
    PushAxisAlignedClip(
        CONST D2D1_RECT_F &clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode 
        ) 
    {
        return PushAxisAlignedClip(&clipRect, antialiasMode);
    }
    
    void
    Clear(
        CONST D2D1_COLOR_F &clearColor 
        ) 
    {
        return Clear(&clearColor);
    }
    
    
    //
    // Draws the text within the given layout rectangle and by default also snaps and
    // clips it.
    //
    void
    DrawText(
        __in_ecount(stringLength) CONST WCHAR *string,
        UINT stringLength,
        __in IDWriteTextFormat *textFormat,
        CONST D2D1_RECT_F &layoutRect,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE,
        DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
        ) 
    {
        return DrawText(string, stringLength, textFormat, &layoutRect, defaultForegroundBrush, options, measuringMode);
    }
    
    BOOL
    IsSupported(
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties 
        ) CONST 
    {
        return IsSupported(&renderTargetProperties);
    }
}; // interface ID2D1RenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1BitmapRenderTarget
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd90695-12e2-11dc-9fed-001143a055f9") ID2D1BitmapRenderTarget  : public ID2D1RenderTarget
{
    
    STDMETHOD(GetBitmap)(
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
}; // interface ID2D1BitmapRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1HwndRenderTarget
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("2cd90698-12e2-11dc-9fed-001143a055f9") ID2D1HwndRenderTarget  : public ID2D1RenderTarget
{
    
    STDMETHOD_(D2D1_WINDOW_STATE, CheckWindowState)(
        ) PURE;
    
    
    //
    // Resize the buffer underlying the render target. This operation might fail if
    // there is insufficent video memory or system memory, or if the render target is
    // resized beyond the maximum bitmap size. If the method fails, the render target
    // will be placed in a zombie state and D2DERR_RECREATE_TARGET will be returned
    // from it when EndDraw is called. In addition an appropriate failure result will
    // be returned from Resize.
    //
    STDMETHOD(Resize)(
        __in CONST D2D1_SIZE_U *pixelSize 
        ) PURE;
    
    STDMETHOD_(HWND, GetHwnd)(
        ) CONST PURE;
    
    HRESULT
    Resize(
        CONST D2D1_SIZE_U &pixelSize 
        ) 
    {
        return Resize(&pixelSize);
    }
}; // interface ID2D1HwndRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1GdiInteropRenderTarget
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("e0db51c3-6f77-4bae-b3d5-e47509b35838") ID2D1GdiInteropRenderTarget  : public IUnknown
{
    
    STDMETHOD(GetDC)(
        D2D1_DC_INITIALIZE_MODE mode,
        __out HDC *hdc 
        ) PURE;
    
    STDMETHOD(ReleaseDC)(
        __in_opt CONST RECT *update 
        ) PURE;
}; // interface ID2D1GdiInteropRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1DCRenderTarget
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("1c51bc64-de61-46fd-9899-63a5d8f03950") ID2D1DCRenderTarget  : public ID2D1RenderTarget
{
    
    STDMETHOD(BindDC)(
        __in CONST HDC hDC,
        __in CONST RECT *pSubRect 
        ) PURE;
}; // interface ID2D1DCRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      ID2D1Factory
//
//  Synopsis:
//      The root factory interface for all of D2D's objects.
//
//------------------------------------------------------------------------------
interface D2D1_DECLARE_INTERFACE("06152247-6f50-465a-9245-118bfd3b6007") ID2D1Factory  : public IUnknown
{
    
    
    //
    // Cause the factory to refresh any system metrics that it might have been snapped
    // on factory creation.
    //
    STDMETHOD(ReloadSystemMetrics)(
        ) PURE;
    
    
    //
    // Retrieves the current desktop DPI. To refresh this, call ReloadSystemMetrics.
    //
    STDMETHOD_(void, GetDesktopDpi)(
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) PURE;
    
    STDMETHOD(CreateRectangleGeometry)(
        __in CONST D2D1_RECT_F *rectangle,
        __deref_out ID2D1RectangleGeometry **rectangleGeometry 
        ) PURE;
    
    STDMETHOD(CreateRoundedRectangleGeometry)(
        __in CONST D2D1_ROUNDED_RECT *roundedRectangle,
        __deref_out ID2D1RoundedRectangleGeometry **roundedRectangleGeometry 
        ) PURE;
    
    STDMETHOD(CreateEllipseGeometry)(
        __in CONST D2D1_ELLIPSE *ellipse,
        __deref_out ID2D1EllipseGeometry **ellipseGeometry 
        ) PURE;
    
    
    //
    // Create a geometry which holds other geometries.
    //
    STDMETHOD(CreateGeometryGroup)(
        D2D1_FILL_MODE fillMode,
        __in_ecount(geometriesCount) ID2D1Geometry **geometries,
        UINT geometriesCount,
        __deref_out ID2D1GeometryGroup **geometryGroup 
        ) PURE;
    
    STDMETHOD(CreateTransformedGeometry)(
        __in ID2D1Geometry *sourceGeometry,
        __in CONST D2D1_MATRIX_3X2_F *transform,
        __deref_out ID2D1TransformedGeometry **transformedGeometry 
        ) PURE;
    
    
    //
    // Returns an initially empty path geometry interface. A geometry sink is created
    // off the interface to populate it.
    //
    STDMETHOD(CreatePathGeometry)(
        __deref_out ID2D1PathGeometry **pathGeometry 
        ) PURE;
    
    
    //
    // Allows a non-default stroke style to be specified for a given geometry at draw
    // time.
    //
    STDMETHOD(CreateStrokeStyle)(
        __in CONST D2D1_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
        __in_ecount_opt(dashesCount) CONST FLOAT *dashes,
        UINT dashesCount,
        __deref_out ID2D1StrokeStyle **strokeStyle 
        ) PURE;
    
    
    //
    // Creates a new drawing state block, this can be used in subsequent
    // SaveDrawingState and RestoreDrawingState operations on the render target.
    //
    STDMETHOD(CreateDrawingStateBlock)(
        __in_opt CONST D2D1_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
        __in_opt IDWriteRenderingParams *textRenderingParams,
        __deref_out ID2D1DrawingStateBlock **drawingStateBlock 
        ) PURE;
    
    
    //
    // Creates a render target which is a source of bitmaps.
    //
    STDMETHOD(CreateWicBitmapRenderTarget)(
        __in IWICBitmap *target,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) PURE;
    
    
    //
    // Creates a render target that appears on the display.
    //
    STDMETHOD(CreateHwndRenderTarget)(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __in CONST D2D1_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties,
        __deref_out ID2D1HwndRenderTarget **hwndRenderTarget 
        ) PURE;
    
    
    //
    // Creates a render target that draws to a DXGI Surface. The device that owns the
    // surface is used for rendering.
    //
    STDMETHOD(CreateDxgiSurfaceRenderTarget)(
        __in IDXGISurface *dxgiSurface,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) PURE;
    
    
    //
    // Creates a render target that draws to a GDI device context.
    //
    STDMETHOD(CreateDCRenderTarget)(
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1DCRenderTarget **dcRenderTarget 
        ) PURE;
    
    HRESULT
    CreateRectangleGeometry(
        CONST D2D1_RECT_F &rectangle,
        __deref_out ID2D1RectangleGeometry **rectangleGeometry 
        ) 
    {
        return CreateRectangleGeometry(&rectangle, rectangleGeometry);
    }
    
    HRESULT
    CreateRoundedRectangleGeometry(
        CONST D2D1_ROUNDED_RECT &roundedRectangle,
        __deref_out ID2D1RoundedRectangleGeometry **roundedRectangleGeometry 
        ) 
    {
        return CreateRoundedRectangleGeometry(&roundedRectangle, roundedRectangleGeometry);
    }
    
    HRESULT
    CreateEllipseGeometry(
        CONST D2D1_ELLIPSE &ellipse,
        __deref_out ID2D1EllipseGeometry **ellipseGeometry 
        ) 
    {
        return CreateEllipseGeometry(&ellipse, ellipseGeometry);
    }
    
    HRESULT
    CreateTransformedGeometry(
        __in ID2D1Geometry *sourceGeometry,
        CONST D2D1_MATRIX_3X2_F &transform,
        __deref_out ID2D1TransformedGeometry **transformedGeometry 
        ) 
    {
        return CreateTransformedGeometry(sourceGeometry, &transform, transformedGeometry);
    }
    
    HRESULT
    CreateStrokeStyle(
        CONST D2D1_STROKE_STYLE_PROPERTIES &strokeStyleProperties,
        __in_ecount(dashesCount) CONST FLOAT *dashes,
        UINT dashesCount,
        __deref_out ID2D1StrokeStyle **strokeStyle 
        ) 
    {
        return CreateStrokeStyle(&strokeStyleProperties, dashes, dashesCount, strokeStyle);
    }
    
    HRESULT
    CreateDrawingStateBlock(
        CONST D2D1_DRAWING_STATE_DESCRIPTION &drawingStateDescription,
        __deref_out ID2D1DrawingStateBlock **drawingStateBlock 
        ) 
    {
        return CreateDrawingStateBlock(&drawingStateDescription, NULL, drawingStateBlock);
    }
    
    HRESULT
    CreateDrawingStateBlock(
        __deref_out ID2D1DrawingStateBlock **drawingStateBlock 
        ) 
    {
        return CreateDrawingStateBlock(NULL, NULL, drawingStateBlock);
    }
    
    HRESULT
    CreateWicBitmapRenderTarget(
        __in IWICBitmap *target,
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) 
    {
        return CreateWicBitmapRenderTarget(target, &renderTargetProperties, renderTarget);
    }
    
    HRESULT
    CreateHwndRenderTarget(
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        CONST D2D1_HWND_RENDER_TARGET_PROPERTIES &hwndRenderTargetProperties,
        __deref_out ID2D1HwndRenderTarget **hwndRenderTarget 
        ) 
    {
        return CreateHwndRenderTarget(&renderTargetProperties, &hwndRenderTargetProperties, hwndRenderTarget);
    }
    
    HRESULT
    CreateDxgiSurfaceRenderTarget(
        __in IDXGISurface *dxgiSurface,
        CONST D2D1_RENDER_TARGET_PROPERTIES &renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) 
    {
        return CreateDxgiSurfaceRenderTarget(dxgiSurface, &renderTargetProperties, renderTarget);
    }
}; // interface ID2D1Factory



#endif


EXTERN_C CONST IID IID_ID2D1Resource;
EXTERN_C CONST IID IID_ID2D1Bitmap;
EXTERN_C CONST IID IID_ID2D1GradientStopCollection;
EXTERN_C CONST IID IID_ID2D1Brush;
EXTERN_C CONST IID IID_ID2D1BitmapBrush;
EXTERN_C CONST IID IID_ID2D1SolidColorBrush;
EXTERN_C CONST IID IID_ID2D1LinearGradientBrush;
EXTERN_C CONST IID IID_ID2D1RadialGradientBrush;
EXTERN_C CONST IID IID_ID2D1StrokeStyle;
EXTERN_C CONST IID IID_ID2D1Geometry;
EXTERN_C CONST IID IID_ID2D1RectangleGeometry;
EXTERN_C CONST IID IID_ID2D1RoundedRectangleGeometry;
EXTERN_C CONST IID IID_ID2D1EllipseGeometry;
EXTERN_C CONST IID IID_ID2D1GeometryGroup;
EXTERN_C CONST IID IID_ID2D1TransformedGeometry;
EXTERN_C CONST IID IID_ID2D1SimplifiedGeometrySink;
EXTERN_C CONST IID IID_ID2D1GeometrySink;
EXTERN_C CONST IID IID_ID2D1TessellationSink;
EXTERN_C CONST IID IID_ID2D1PathGeometry;
EXTERN_C CONST IID IID_ID2D1Mesh;
EXTERN_C CONST IID IID_ID2D1Layer;
EXTERN_C CONST IID IID_ID2D1DrawingStateBlock;
EXTERN_C CONST IID IID_ID2D1RenderTarget;
EXTERN_C CONST IID IID_ID2D1BitmapRenderTarget;
EXTERN_C CONST IID IID_ID2D1HwndRenderTarget;
EXTERN_C CONST IID IID_ID2D1GdiInteropRenderTarget;
EXTERN_C CONST IID IID_ID2D1DCRenderTarget;
EXTERN_C CONST IID IID_ID2D1Factory;


#ifdef D2D_USE_C_DEFINITIONS


typedef interface ID2D1Resource ID2D1Resource;

typedef struct ID2D1ResourceVtbl
{
    
    IUnknownVtbl Base;
    
    
    STDMETHOD_(void, GetFactory)(
        ID2D1Resource *This,
        __deref_out ID2D1Factory **factory 
        ) PURE;
} ID2D1ResourceVtbl;

interface ID2D1Resource
{
    CONST struct ID2D1ResourceVtbl *lpVtbl;
};


#define ID2D1Resource_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Resource_AddRef(This) \
    ((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define ID2D1Resource_Release(This) \
    ((This)->lpVtbl->Base.Release((IUnknown *)This))

#define ID2D1Resource_GetFactory(This, factory) \
    ((This)->lpVtbl->GetFactory(This, factory))

typedef interface ID2D1Bitmap ID2D1Bitmap;

typedef struct ID2D1BitmapVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ID2D1Bitmap *This 
        ) PURE;
    
    STDMETHOD_(D2D1_SIZE_U, GetPixelSize)(
        ID2D1Bitmap *This 
        ) PURE;
    
    STDMETHOD_(D2D1_PIXEL_FORMAT, GetPixelFormat)(
        ID2D1Bitmap *This 
        ) PURE;
    
    STDMETHOD_(void, GetDpi)(
        ID2D1Bitmap *This,
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) PURE;
    
    STDMETHOD(CopyFromBitmap)(
        ID2D1Bitmap *This,
        __in_opt CONST D2D1_POINT_2U *destPoint,
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_RECT_U *srcRect 
        ) PURE;
    
    STDMETHOD(CopyFromRenderTarget)(
        ID2D1Bitmap *This,
        __in_opt CONST D2D1_POINT_2U *destPoint,
        __in ID2D1RenderTarget *renderTarget,
        __in_opt CONST D2D1_RECT_U *srcRect 
        ) PURE;
    
    STDMETHOD(CopyFromMemory)(
        ID2D1Bitmap *This,
        __in_opt CONST D2D1_RECT_U *dstRect,
        __in CONST void *srcData,
        UINT32 pitch 
        ) PURE;
} ID2D1BitmapVtbl;

interface ID2D1Bitmap
{
    CONST struct ID2D1BitmapVtbl *lpVtbl;
};


#define ID2D1Bitmap_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Bitmap_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1Bitmap_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1Bitmap_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1Bitmap_GetSize(This) \
    ((This)->lpVtbl->GetSize(This))

#define ID2D1Bitmap_GetPixelSize(This) \
    ((This)->lpVtbl->GetPixelSize(This))

#define ID2D1Bitmap_GetPixelFormat(This) \
    ((This)->lpVtbl->GetPixelFormat(This))

#define ID2D1Bitmap_GetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->GetDpi(This, dpiX, dpiY))

#define ID2D1Bitmap_CopyFromBitmap(This, destPoint, bitmap, srcRect) \
    ((This)->lpVtbl->CopyFromBitmap(This, destPoint, bitmap, srcRect))

#define ID2D1Bitmap_CopyFromRenderTarget(This, destPoint, renderTarget, srcRect) \
    ((This)->lpVtbl->CopyFromRenderTarget(This, destPoint, renderTarget, srcRect))

#define ID2D1Bitmap_CopyFromMemory(This, dstRect, srcData, pitch) \
    ((This)->lpVtbl->CopyFromMemory(This, dstRect, srcData, pitch))

typedef interface ID2D1GradientStopCollection ID2D1GradientStopCollection;

typedef struct ID2D1GradientStopCollectionVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(UINT32, GetGradientStopCount)(
        ID2D1GradientStopCollection *This 
        ) PURE;
    
    STDMETHOD_(void, GetGradientStops)(
        ID2D1GradientStopCollection *This,
        __out_ecount(gradientStopsCount) D2D1_GRADIENT_STOP *gradientStops,
        UINT gradientStopsCount 
        ) PURE;
    
    STDMETHOD_(D2D1_GAMMA, GetColorInterpolationGamma)(
        ID2D1GradientStopCollection *This 
        ) PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendMode)(
        ID2D1GradientStopCollection *This 
        ) PURE;
} ID2D1GradientStopCollectionVtbl;

interface ID2D1GradientStopCollection
{
    CONST struct ID2D1GradientStopCollectionVtbl *lpVtbl;
};


#define ID2D1GradientStopCollection_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1GradientStopCollection_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1GradientStopCollection_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1GradientStopCollection_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1GradientStopCollection_GetGradientStopCount(This) \
    ((This)->lpVtbl->GetGradientStopCount(This))

#define ID2D1GradientStopCollection_GetGradientStops(This, gradientStops, gradientStopsCount) \
    ((This)->lpVtbl->GetGradientStops(This, gradientStops, gradientStopsCount))

#define ID2D1GradientStopCollection_GetColorInterpolationGamma(This) \
    ((This)->lpVtbl->GetColorInterpolationGamma(This))

#define ID2D1GradientStopCollection_GetExtendMode(This) \
    ((This)->lpVtbl->GetExtendMode(This))

typedef interface ID2D1Brush ID2D1Brush;

typedef struct ID2D1BrushVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(void, SetOpacity)(
        ID2D1Brush *This,
        FLOAT opacity 
        ) PURE;
    
    STDMETHOD_(void, SetTransform)(
        ID2D1Brush *This,
        __in CONST D2D1_MATRIX_3X2_F *transform 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetOpacity)(
        ID2D1Brush *This 
        ) PURE;
    
    STDMETHOD_(void, GetTransform)(
        ID2D1Brush *This,
        __out D2D1_MATRIX_3X2_F *transform 
        ) PURE;
} ID2D1BrushVtbl;

interface ID2D1Brush
{
    CONST struct ID2D1BrushVtbl *lpVtbl;
};


#define ID2D1Brush_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Brush_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1Brush_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1Brush_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1Brush_SetOpacity(This, opacity) \
    ((This)->lpVtbl->SetOpacity(This, opacity))

#define ID2D1Brush_SetTransform(This, transform) \
    ((This)->lpVtbl->SetTransform(This, transform))

#define ID2D1Brush_GetOpacity(This) \
    ((This)->lpVtbl->GetOpacity(This))

#define ID2D1Brush_GetTransform(This, transform) \
    ((This)->lpVtbl->GetTransform(This, transform))

typedef interface ID2D1BitmapBrush ID2D1BitmapBrush;

typedef struct ID2D1BitmapBrushVtbl
{
    
    ID2D1BrushVtbl Base;
    
    
    STDMETHOD_(void, SetExtendModeX)(
        ID2D1BitmapBrush *This,
        D2D1_EXTEND_MODE extendModeX 
        ) PURE;
    
    STDMETHOD_(void, SetExtendModeY)(
        ID2D1BitmapBrush *This,
        D2D1_EXTEND_MODE extendModeY 
        ) PURE;
    
    STDMETHOD_(void, SetInterpolationMode)(
        ID2D1BitmapBrush *This,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode 
        ) PURE;
    
    STDMETHOD_(void, SetBitmap)(
        ID2D1BitmapBrush *This,
        __in ID2D1Bitmap *bitmap 
        ) PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendModeX)(
        ID2D1BitmapBrush *This 
        ) PURE;
    
    STDMETHOD_(D2D1_EXTEND_MODE, GetExtendModeY)(
        ID2D1BitmapBrush *This 
        ) PURE;
    
    STDMETHOD_(D2D1_BITMAP_INTERPOLATION_MODE, GetInterpolationMode)(
        ID2D1BitmapBrush *This 
        ) PURE;
    
    STDMETHOD_(void, GetBitmap)(
        ID2D1BitmapBrush *This,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
} ID2D1BitmapBrushVtbl;

interface ID2D1BitmapBrush
{
    CONST struct ID2D1BitmapBrushVtbl *lpVtbl;
};


#define ID2D1BitmapBrush_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1BitmapBrush_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1BitmapBrush_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1BitmapBrush_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1BitmapBrush_SetOpacity(This, opacity) \
    ((This)->lpVtbl->Base.SetOpacity((ID2D1Brush *)This, opacity))

#define ID2D1BitmapBrush_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1Brush *)This, transform))

#define ID2D1BitmapBrush_GetOpacity(This) \
    ((This)->lpVtbl->Base.GetOpacity((ID2D1Brush *)This))

#define ID2D1BitmapBrush_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1Brush *)This, transform))

#define ID2D1BitmapBrush_SetExtendModeX(This, extendModeX) \
    ((This)->lpVtbl->SetExtendModeX(This, extendModeX))

#define ID2D1BitmapBrush_SetExtendModeY(This, extendModeY) \
    ((This)->lpVtbl->SetExtendModeY(This, extendModeY))

#define ID2D1BitmapBrush_SetInterpolationMode(This, interpolationMode) \
    ((This)->lpVtbl->SetInterpolationMode(This, interpolationMode))

#define ID2D1BitmapBrush_SetBitmap(This, bitmap) \
    ((This)->lpVtbl->SetBitmap(This, bitmap))

#define ID2D1BitmapBrush_GetExtendModeX(This) \
    ((This)->lpVtbl->GetExtendModeX(This))

#define ID2D1BitmapBrush_GetExtendModeY(This) \
    ((This)->lpVtbl->GetExtendModeY(This))

#define ID2D1BitmapBrush_GetInterpolationMode(This) \
    ((This)->lpVtbl->GetInterpolationMode(This))

#define ID2D1BitmapBrush_GetBitmap(This, bitmap) \
    ((This)->lpVtbl->GetBitmap(This, bitmap))

typedef interface ID2D1SolidColorBrush ID2D1SolidColorBrush;

typedef struct ID2D1SolidColorBrushVtbl
{
    
    ID2D1BrushVtbl Base;
    
    
    STDMETHOD_(void, SetColor)(
        ID2D1SolidColorBrush *This,
        __in CONST D2D1_COLOR_F *color 
        ) PURE;
    
    STDMETHOD_(D2D1_COLOR_F, GetColor)(
        ID2D1SolidColorBrush *This 
        ) PURE;
} ID2D1SolidColorBrushVtbl;

interface ID2D1SolidColorBrush
{
    CONST struct ID2D1SolidColorBrushVtbl *lpVtbl;
};


#define ID2D1SolidColorBrush_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1SolidColorBrush_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1SolidColorBrush_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1SolidColorBrush_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1SolidColorBrush_SetOpacity(This, opacity) \
    ((This)->lpVtbl->Base.SetOpacity((ID2D1Brush *)This, opacity))

#define ID2D1SolidColorBrush_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1Brush *)This, transform))

#define ID2D1SolidColorBrush_GetOpacity(This) \
    ((This)->lpVtbl->Base.GetOpacity((ID2D1Brush *)This))

#define ID2D1SolidColorBrush_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1Brush *)This, transform))

#define ID2D1SolidColorBrush_SetColor(This, color) \
    ((This)->lpVtbl->SetColor(This, color))

#define ID2D1SolidColorBrush_GetColor(This) \
    ((This)->lpVtbl->GetColor(This))

typedef interface ID2D1LinearGradientBrush ID2D1LinearGradientBrush;

typedef struct ID2D1LinearGradientBrushVtbl
{
    
    ID2D1BrushVtbl Base;
    
    
    STDMETHOD_(void, SetStartPoint)(
        ID2D1LinearGradientBrush *This,
        D2D1_POINT_2F startPoint 
        ) PURE;
    
    STDMETHOD_(void, SetEndPoint)(
        ID2D1LinearGradientBrush *This,
        D2D1_POINT_2F endPoint 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetStartPoint)(
        ID2D1LinearGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetEndPoint)(
        ID2D1LinearGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(void, GetGradientStopCollection)(
        ID2D1LinearGradientBrush *This,
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) PURE;
} ID2D1LinearGradientBrushVtbl;

interface ID2D1LinearGradientBrush
{
    CONST struct ID2D1LinearGradientBrushVtbl *lpVtbl;
};


#define ID2D1LinearGradientBrush_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1LinearGradientBrush_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1LinearGradientBrush_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1LinearGradientBrush_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1LinearGradientBrush_SetOpacity(This, opacity) \
    ((This)->lpVtbl->Base.SetOpacity((ID2D1Brush *)This, opacity))

#define ID2D1LinearGradientBrush_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1Brush *)This, transform))

#define ID2D1LinearGradientBrush_GetOpacity(This) \
    ((This)->lpVtbl->Base.GetOpacity((ID2D1Brush *)This))

#define ID2D1LinearGradientBrush_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1Brush *)This, transform))

#define ID2D1LinearGradientBrush_SetStartPoint(This, startPoint) \
    ((This)->lpVtbl->SetStartPoint(This, startPoint))

#define ID2D1LinearGradientBrush_SetEndPoint(This, endPoint) \
    ((This)->lpVtbl->SetEndPoint(This, endPoint))

#define ID2D1LinearGradientBrush_GetStartPoint(This) \
    ((This)->lpVtbl->GetStartPoint(This))

#define ID2D1LinearGradientBrush_GetEndPoint(This) \
    ((This)->lpVtbl->GetEndPoint(This))

#define ID2D1LinearGradientBrush_GetGradientStopCollection(This, gradientStopCollection) \
    ((This)->lpVtbl->GetGradientStopCollection(This, gradientStopCollection))

typedef interface ID2D1RadialGradientBrush ID2D1RadialGradientBrush;

typedef struct ID2D1RadialGradientBrushVtbl
{
    
    ID2D1BrushVtbl Base;
    
    
    STDMETHOD_(void, SetCenter)(
        ID2D1RadialGradientBrush *This,
        D2D1_POINT_2F center 
        ) PURE;
    
    STDMETHOD_(void, SetGradientOriginOffset)(
        ID2D1RadialGradientBrush *This,
        D2D1_POINT_2F gradientOriginOffset 
        ) PURE;
    
    STDMETHOD_(void, SetRadiusX)(
        ID2D1RadialGradientBrush *This,
        FLOAT radiusX 
        ) PURE;
    
    STDMETHOD_(void, SetRadiusY)(
        ID2D1RadialGradientBrush *This,
        FLOAT radiusY 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetCenter)(
        ID2D1RadialGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(D2D1_POINT_2F, GetGradientOriginOffset)(
        ID2D1RadialGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetRadiusX)(
        ID2D1RadialGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetRadiusY)(
        ID2D1RadialGradientBrush *This 
        ) PURE;
    
    STDMETHOD_(void, GetGradientStopCollection)(
        ID2D1RadialGradientBrush *This,
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) PURE;
} ID2D1RadialGradientBrushVtbl;

interface ID2D1RadialGradientBrush
{
    CONST struct ID2D1RadialGradientBrushVtbl *lpVtbl;
};


#define ID2D1RadialGradientBrush_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1RadialGradientBrush_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1RadialGradientBrush_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1RadialGradientBrush_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1RadialGradientBrush_SetOpacity(This, opacity) \
    ((This)->lpVtbl->Base.SetOpacity((ID2D1Brush *)This, opacity))

#define ID2D1RadialGradientBrush_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1Brush *)This, transform))

#define ID2D1RadialGradientBrush_GetOpacity(This) \
    ((This)->lpVtbl->Base.GetOpacity((ID2D1Brush *)This))

#define ID2D1RadialGradientBrush_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1Brush *)This, transform))

#define ID2D1RadialGradientBrush_SetCenter(This, center) \
    ((This)->lpVtbl->SetCenter(This, center))

#define ID2D1RadialGradientBrush_SetGradientOriginOffset(This, gradientOriginOffset) \
    ((This)->lpVtbl->SetGradientOriginOffset(This, gradientOriginOffset))

#define ID2D1RadialGradientBrush_SetRadiusX(This, radiusX) \
    ((This)->lpVtbl->SetRadiusX(This, radiusX))

#define ID2D1RadialGradientBrush_SetRadiusY(This, radiusY) \
    ((This)->lpVtbl->SetRadiusY(This, radiusY))

#define ID2D1RadialGradientBrush_GetCenter(This) \
    ((This)->lpVtbl->GetCenter(This))

#define ID2D1RadialGradientBrush_GetGradientOriginOffset(This) \
    ((This)->lpVtbl->GetGradientOriginOffset(This))

#define ID2D1RadialGradientBrush_GetRadiusX(This) \
    ((This)->lpVtbl->GetRadiusX(This))

#define ID2D1RadialGradientBrush_GetRadiusY(This) \
    ((This)->lpVtbl->GetRadiusY(This))

#define ID2D1RadialGradientBrush_GetGradientStopCollection(This, gradientStopCollection) \
    ((This)->lpVtbl->GetGradientStopCollection(This, gradientStopCollection))

typedef interface ID2D1StrokeStyle ID2D1StrokeStyle;

typedef struct ID2D1StrokeStyleVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(D2D1_CAP_STYLE, GetStartCap)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(D2D1_CAP_STYLE, GetEndCap)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(D2D1_CAP_STYLE, GetDashCap)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetMiterLimit)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(D2D1_LINE_JOIN, GetLineJoin)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(FLOAT, GetDashOffset)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(D2D1_DASH_STYLE, GetDashStyle)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(UINT32, GetDashesCount)(
        ID2D1StrokeStyle *This 
        ) PURE;
    
    STDMETHOD_(void, GetDashes)(
        ID2D1StrokeStyle *This,
        __out_ecount(dashesCount) FLOAT *dashes,
        UINT dashesCount 
        ) PURE;
} ID2D1StrokeStyleVtbl;

interface ID2D1StrokeStyle
{
    CONST struct ID2D1StrokeStyleVtbl *lpVtbl;
};


#define ID2D1StrokeStyle_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1StrokeStyle_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1StrokeStyle_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1StrokeStyle_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1StrokeStyle_GetStartCap(This) \
    ((This)->lpVtbl->GetStartCap(This))

#define ID2D1StrokeStyle_GetEndCap(This) \
    ((This)->lpVtbl->GetEndCap(This))

#define ID2D1StrokeStyle_GetDashCap(This) \
    ((This)->lpVtbl->GetDashCap(This))

#define ID2D1StrokeStyle_GetMiterLimit(This) \
    ((This)->lpVtbl->GetMiterLimit(This))

#define ID2D1StrokeStyle_GetLineJoin(This) \
    ((This)->lpVtbl->GetLineJoin(This))

#define ID2D1StrokeStyle_GetDashOffset(This) \
    ((This)->lpVtbl->GetDashOffset(This))

#define ID2D1StrokeStyle_GetDashStyle(This) \
    ((This)->lpVtbl->GetDashStyle(This))

#define ID2D1StrokeStyle_GetDashesCount(This) \
    ((This)->lpVtbl->GetDashesCount(This))

#define ID2D1StrokeStyle_GetDashes(This, dashes, dashesCount) \
    ((This)->lpVtbl->GetDashes(This, dashes, dashesCount))

typedef interface ID2D1Geometry ID2D1Geometry;

typedef struct ID2D1GeometryVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD(GetBounds)(
        ID2D1Geometry *This,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        __out D2D1_RECT_F *bounds 
        ) PURE;
    
    STDMETHOD(GetWidenedBounds)(
        ID2D1Geometry *This,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out D2D1_RECT_F *bounds 
        ) PURE;
    
    STDMETHOD(StrokeContainsPoint)(
        ID2D1Geometry *This,
        D2D1_POINT_2F point,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) PURE;
    
    STDMETHOD(FillContainsPoint)(
        ID2D1Geometry *This,
        D2D1_POINT_2F point,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out BOOL *contains 
        ) PURE;
    
    STDMETHOD(CompareWithGeometry)(
        ID2D1Geometry *This,
        __in ID2D1Geometry *inputGeometry,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __out D2D1_GEOMETRY_RELATION *relation 
        ) PURE;
    
    STDMETHOD(Simplify)(
        ID2D1Geometry *This,
        D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) PURE;
    
    STDMETHOD(Tessellate)(
        ID2D1Geometry *This,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1TessellationSink *tessellationSink 
        ) PURE;
    
    STDMETHOD(CombineWithGeometry)(
        ID2D1Geometry *This,
        __in ID2D1Geometry *inputGeometry,
        D2D1_COMBINE_MODE combineMode,
        __in_opt CONST D2D1_MATRIX_3X2_F *inputGeometryTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) PURE;
    
    STDMETHOD(Outline)(
        ID2D1Geometry *This,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) PURE;
    
    STDMETHOD(ComputeArea)(
        ID2D1Geometry *This,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *area 
        ) PURE;
    
    STDMETHOD(ComputeLength)(
        ID2D1Geometry *This,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out FLOAT *length 
        ) PURE;
    
    STDMETHOD(ComputePointAtLength)(
        ID2D1Geometry *This,
        FLOAT length,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __out_opt D2D1_POINT_2F *point,
        __out_opt D2D1_POINT_2F *unitTangentVector 
        ) PURE;
    
    STDMETHOD(Widen)(
        ID2D1Geometry *This,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle,
        __in_opt CONST D2D1_MATRIX_3X2_F *worldTransform,
        FLOAT flatteningTolerance,
        __in ID2D1SimplifiedGeometrySink *geometrySink 
        ) PURE;
} ID2D1GeometryVtbl;

interface ID2D1Geometry
{
    CONST struct ID2D1GeometryVtbl *lpVtbl;
};


#define ID2D1Geometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Geometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1Geometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1Geometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1Geometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->GetBounds(This, worldTransform, bounds))

#define ID2D1Geometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1Geometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1Geometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1Geometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1Geometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1Geometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Tessellate(This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1Geometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1Geometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Outline(This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1Geometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->ComputeArea(This, worldTransform, flatteningTolerance, area))

#define ID2D1Geometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->ComputeLength(This, worldTransform, flatteningTolerance, length))

#define ID2D1Geometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1Geometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

typedef interface ID2D1RectangleGeometry ID2D1RectangleGeometry;

typedef struct ID2D1RectangleGeometryVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD_(void, GetRect)(
        ID2D1RectangleGeometry *This,
        __out D2D1_RECT_F *rect 
        ) PURE;
} ID2D1RectangleGeometryVtbl;

interface ID2D1RectangleGeometry
{
    CONST struct ID2D1RectangleGeometryVtbl *lpVtbl;
};


#define ID2D1RectangleGeometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1RectangleGeometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1RectangleGeometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1RectangleGeometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1RectangleGeometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1RectangleGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1RectangleGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1RectangleGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1RectangleGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1RectangleGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RectangleGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1RectangleGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1RectangleGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RectangleGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1RectangleGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1RectangleGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1RectangleGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RectangleGeometry_GetRect(This, rect) \
    ((This)->lpVtbl->GetRect(This, rect))

typedef interface ID2D1RoundedRectangleGeometry ID2D1RoundedRectangleGeometry;

typedef struct ID2D1RoundedRectangleGeometryVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD_(void, GetRoundedRect)(
        ID2D1RoundedRectangleGeometry *This,
        __out D2D1_ROUNDED_RECT *roundedRect 
        ) PURE;
} ID2D1RoundedRectangleGeometryVtbl;

interface ID2D1RoundedRectangleGeometry
{
    CONST struct ID2D1RoundedRectangleGeometryVtbl *lpVtbl;
};


#define ID2D1RoundedRectangleGeometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1RoundedRectangleGeometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1RoundedRectangleGeometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1RoundedRectangleGeometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1RoundedRectangleGeometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1RoundedRectangleGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1RoundedRectangleGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1RoundedRectangleGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1RoundedRectangleGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1RoundedRectangleGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RoundedRectangleGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1RoundedRectangleGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1RoundedRectangleGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RoundedRectangleGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1RoundedRectangleGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1RoundedRectangleGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1RoundedRectangleGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1RoundedRectangleGeometry_GetRoundedRect(This, roundedRect) \
    ((This)->lpVtbl->GetRoundedRect(This, roundedRect))

typedef interface ID2D1EllipseGeometry ID2D1EllipseGeometry;

typedef struct ID2D1EllipseGeometryVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD_(void, GetEllipse)(
        ID2D1EllipseGeometry *This,
        __out D2D1_ELLIPSE *ellipse 
        ) PURE;
} ID2D1EllipseGeometryVtbl;

interface ID2D1EllipseGeometry
{
    CONST struct ID2D1EllipseGeometryVtbl *lpVtbl;
};


#define ID2D1EllipseGeometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1EllipseGeometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1EllipseGeometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1EllipseGeometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1EllipseGeometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1EllipseGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1EllipseGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1EllipseGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1EllipseGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1EllipseGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1EllipseGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1EllipseGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1EllipseGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1EllipseGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1EllipseGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1EllipseGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1EllipseGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1EllipseGeometry_GetEllipse(This, ellipse) \
    ((This)->lpVtbl->GetEllipse(This, ellipse))

typedef interface ID2D1GeometryGroup ID2D1GeometryGroup;

typedef struct ID2D1GeometryGroupVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD_(D2D1_FILL_MODE, GetFillMode)(
        ID2D1GeometryGroup *This 
        ) PURE;
    
    STDMETHOD_(UINT32, GetSourceGeometryCount)(
        ID2D1GeometryGroup *This 
        ) PURE;
    
    STDMETHOD_(void, GetSourceGeometries)(
        ID2D1GeometryGroup *This,
        __out_ecount(geometriesCount) ID2D1Geometry **geometries,
        UINT geometriesCount 
        ) PURE;
} ID2D1GeometryGroupVtbl;

interface ID2D1GeometryGroup
{
    CONST struct ID2D1GeometryGroupVtbl *lpVtbl;
};


#define ID2D1GeometryGroup_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1GeometryGroup_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1GeometryGroup_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1GeometryGroup_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1GeometryGroup_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1GeometryGroup_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1GeometryGroup_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1GeometryGroup_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1GeometryGroup_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1GeometryGroup_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1GeometryGroup_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1GeometryGroup_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1GeometryGroup_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1GeometryGroup_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1GeometryGroup_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1GeometryGroup_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1GeometryGroup_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1GeometryGroup_GetFillMode(This) \
    ((This)->lpVtbl->GetFillMode(This))

#define ID2D1GeometryGroup_GetSourceGeometryCount(This) \
    ((This)->lpVtbl->GetSourceGeometryCount(This))

#define ID2D1GeometryGroup_GetSourceGeometries(This, geometries, geometriesCount) \
    ((This)->lpVtbl->GetSourceGeometries(This, geometries, geometriesCount))

typedef interface ID2D1TransformedGeometry ID2D1TransformedGeometry;

typedef struct ID2D1TransformedGeometryVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD_(void, GetSourceGeometry)(
        ID2D1TransformedGeometry *This,
        __deref_out ID2D1Geometry **sourceGeometry 
        ) PURE;
    
    STDMETHOD_(void, GetTransform)(
        ID2D1TransformedGeometry *This,
        __out D2D1_MATRIX_3X2_F *transform 
        ) PURE;
} ID2D1TransformedGeometryVtbl;

interface ID2D1TransformedGeometry
{
    CONST struct ID2D1TransformedGeometryVtbl *lpVtbl;
};


#define ID2D1TransformedGeometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1TransformedGeometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1TransformedGeometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1TransformedGeometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1TransformedGeometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1TransformedGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1TransformedGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1TransformedGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1TransformedGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1TransformedGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1TransformedGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1TransformedGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1TransformedGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1TransformedGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1TransformedGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1TransformedGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1TransformedGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1TransformedGeometry_GetSourceGeometry(This, sourceGeometry) \
    ((This)->lpVtbl->GetSourceGeometry(This, sourceGeometry))

#define ID2D1TransformedGeometry_GetTransform(This, transform) \
    ((This)->lpVtbl->GetTransform(This, transform))

typedef interface ID2D1SimplifiedGeometrySink ID2D1SimplifiedGeometrySink;

typedef struct ID2D1SimplifiedGeometrySinkVtbl
{
    
    IUnknownVtbl Base;
    
    
    STDMETHOD_(void, SetFillMode)(
        ID2D1SimplifiedGeometrySink *This,
        D2D1_FILL_MODE fillMode 
        ) PURE;
    
    STDMETHOD_(void, SetSegmentFlags)(
        ID2D1SimplifiedGeometrySink *This,
        D2D1_PATH_SEGMENT vertexFlags 
        ) PURE;
    
    STDMETHOD_(void, BeginFigure)(
        ID2D1SimplifiedGeometrySink *This,
        D2D1_POINT_2F startPoint,
        D2D1_FIGURE_BEGIN figureBegin 
        ) PURE;
    
    STDMETHOD_(void, AddLines)(
        ID2D1SimplifiedGeometrySink *This,
        __in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
        UINT pointsCount 
        ) PURE;
    
    STDMETHOD_(void, AddBeziers)(
        ID2D1SimplifiedGeometrySink *This,
        __in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        ) PURE;
    
    STDMETHOD_(void, EndFigure)(
        ID2D1SimplifiedGeometrySink *This,
        D2D1_FIGURE_END figureEnd 
        ) PURE;
    
    STDMETHOD(Close)(
        ID2D1SimplifiedGeometrySink *This 
        ) PURE;
} ID2D1SimplifiedGeometrySinkVtbl;

interface ID2D1SimplifiedGeometrySink
{
    CONST struct ID2D1SimplifiedGeometrySinkVtbl *lpVtbl;
};


#define ID2D1SimplifiedGeometrySink_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1SimplifiedGeometrySink_AddRef(This) \
    ((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define ID2D1SimplifiedGeometrySink_Release(This) \
    ((This)->lpVtbl->Base.Release((IUnknown *)This))

#define ID2D1SimplifiedGeometrySink_SetFillMode(This, fillMode) \
    ((This)->lpVtbl->SetFillMode(This, fillMode))

#define ID2D1SimplifiedGeometrySink_SetSegmentFlags(This, vertexFlags) \
    ((This)->lpVtbl->SetSegmentFlags(This, vertexFlags))

#define ID2D1SimplifiedGeometrySink_BeginFigure(This, startPoint, figureBegin) \
    ((This)->lpVtbl->BeginFigure(This, startPoint, figureBegin))

#define ID2D1SimplifiedGeometrySink_AddLines(This, points, pointsCount) \
    ((This)->lpVtbl->AddLines(This, points, pointsCount))

#define ID2D1SimplifiedGeometrySink_AddBeziers(This, beziers, beziersCount) \
    ((This)->lpVtbl->AddBeziers(This, beziers, beziersCount))

#define ID2D1SimplifiedGeometrySink_EndFigure(This, figureEnd) \
    ((This)->lpVtbl->EndFigure(This, figureEnd))

#define ID2D1SimplifiedGeometrySink_Close(This) \
    ((This)->lpVtbl->Close(This))

typedef interface ID2D1GeometrySink ID2D1GeometrySink;

typedef struct ID2D1GeometrySinkVtbl
{
    
    ID2D1SimplifiedGeometrySinkVtbl Base;
    
    
    STDMETHOD_(void, AddLine)(
        ID2D1GeometrySink *This,
        D2D1_POINT_2F point 
        ) PURE;
    
    STDMETHOD_(void, AddBezier)(
        ID2D1GeometrySink *This,
        __in CONST D2D1_BEZIER_SEGMENT *bezier 
        ) PURE;
    
    STDMETHOD_(void, AddQuadraticBezier)(
        ID2D1GeometrySink *This,
        __in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier 
        ) PURE;
    
    STDMETHOD_(void, AddQuadraticBeziers)(
        ID2D1GeometrySink *This,
        __in_ecount(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
        UINT beziersCount 
        ) PURE;
    
    STDMETHOD_(void, AddArc)(
        ID2D1GeometrySink *This,
        __in CONST D2D1_ARC_SEGMENT *arc 
        ) PURE;
} ID2D1GeometrySinkVtbl;

interface ID2D1GeometrySink
{
    CONST struct ID2D1GeometrySinkVtbl *lpVtbl;
};


#define ID2D1GeometrySink_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1GeometrySink_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1GeometrySink_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1GeometrySink_SetFillMode(This, fillMode) \
    ((This)->lpVtbl->Base.SetFillMode((ID2D1SimplifiedGeometrySink *)This, fillMode))

#define ID2D1GeometrySink_SetSegmentFlags(This, vertexFlags) \
    ((This)->lpVtbl->Base.SetSegmentFlags((ID2D1SimplifiedGeometrySink *)This, vertexFlags))

#define ID2D1GeometrySink_BeginFigure(This, startPoint, figureBegin) \
    ((This)->lpVtbl->Base.BeginFigure((ID2D1SimplifiedGeometrySink *)This, startPoint, figureBegin))

#define ID2D1GeometrySink_AddLines(This, points, pointsCount) \
    ((This)->lpVtbl->Base.AddLines((ID2D1SimplifiedGeometrySink *)This, points, pointsCount))

#define ID2D1GeometrySink_AddBeziers(This, beziers, beziersCount) \
    ((This)->lpVtbl->Base.AddBeziers((ID2D1SimplifiedGeometrySink *)This, beziers, beziersCount))

#define ID2D1GeometrySink_EndFigure(This, figureEnd) \
    ((This)->lpVtbl->Base.EndFigure((ID2D1SimplifiedGeometrySink *)This, figureEnd))

#define ID2D1GeometrySink_Close(This) \
    ((This)->lpVtbl->Base.Close((ID2D1SimplifiedGeometrySink *)This))

#define ID2D1GeometrySink_AddLine(This, point) \
    ((This)->lpVtbl->AddLine(This, point))

#define ID2D1GeometrySink_AddBezier(This, bezier) \
    ((This)->lpVtbl->AddBezier(This, bezier))

#define ID2D1GeometrySink_AddQuadraticBezier(This, bezier) \
    ((This)->lpVtbl->AddQuadraticBezier(This, bezier))

#define ID2D1GeometrySink_AddQuadraticBeziers(This, beziers, beziersCount) \
    ((This)->lpVtbl->AddQuadraticBeziers(This, beziers, beziersCount))

#define ID2D1GeometrySink_AddArc(This, arc) \
    ((This)->lpVtbl->AddArc(This, arc))

typedef interface ID2D1TessellationSink ID2D1TessellationSink;

typedef struct ID2D1TessellationSinkVtbl
{
    
    IUnknownVtbl Base;
    
    
    STDMETHOD_(void, AddTriangles)(
        ID2D1TessellationSink *This,
        __in_ecount(trianglesCount) CONST D2D1_TRIANGLE *triangles,
        UINT trianglesCount 
        ) PURE;
    
    STDMETHOD(Close)(
        ID2D1TessellationSink *This 
        ) PURE;
} ID2D1TessellationSinkVtbl;

interface ID2D1TessellationSink
{
    CONST struct ID2D1TessellationSinkVtbl *lpVtbl;
};


#define ID2D1TessellationSink_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1TessellationSink_AddRef(This) \
    ((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define ID2D1TessellationSink_Release(This) \
    ((This)->lpVtbl->Base.Release((IUnknown *)This))

#define ID2D1TessellationSink_AddTriangles(This, triangles, trianglesCount) \
    ((This)->lpVtbl->AddTriangles(This, triangles, trianglesCount))

#define ID2D1TessellationSink_Close(This) \
    ((This)->lpVtbl->Close(This))

typedef interface ID2D1PathGeometry ID2D1PathGeometry;

typedef struct ID2D1PathGeometryVtbl
{
    
    ID2D1GeometryVtbl Base;
    
    
    STDMETHOD(Open)(
        ID2D1PathGeometry *This,
        __deref_out ID2D1GeometrySink **geometrySink 
        ) PURE;
    
    STDMETHOD(Stream)(
        ID2D1PathGeometry *This,
        __in ID2D1GeometrySink *geometrySink 
        ) PURE;
    
    STDMETHOD(GetSegmentCount)(
        ID2D1PathGeometry *This,
        __out UINT32 *count 
        ) PURE;
    
    STDMETHOD(GetFigureCount)(
        ID2D1PathGeometry *This,
        __out UINT32 *count 
        ) PURE;
} ID2D1PathGeometryVtbl;

interface ID2D1PathGeometry
{
    CONST struct ID2D1PathGeometryVtbl *lpVtbl;
};


#define ID2D1PathGeometry_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1PathGeometry_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1PathGeometry_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1PathGeometry_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1PathGeometry_GetBounds(This, worldTransform, bounds) \
    ((This)->lpVtbl->Base.GetBounds((ID2D1Geometry *)This, worldTransform, bounds))

#define ID2D1PathGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
    ((This)->lpVtbl->Base.GetWidenedBounds((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define ID2D1PathGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.StrokeContainsPoint((ID2D1Geometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define ID2D1PathGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
    ((This)->lpVtbl->Base.FillContainsPoint((ID2D1Geometry *)This, point, worldTransform, flatteningTolerance, contains))

#define ID2D1PathGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
    ((This)->lpVtbl->Base.CompareWithGeometry((ID2D1Geometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define ID2D1PathGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Simplify((ID2D1Geometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1PathGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
    ((This)->lpVtbl->Base.Tessellate((ID2D1Geometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define ID2D1PathGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.CombineWithGeometry((ID2D1Geometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define ID2D1PathGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Outline((ID2D1Geometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1PathGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
    ((This)->lpVtbl->Base.ComputeArea((ID2D1Geometry *)This, worldTransform, flatteningTolerance, area))

#define ID2D1PathGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
    ((This)->lpVtbl->Base.ComputeLength((ID2D1Geometry *)This, worldTransform, flatteningTolerance, length))

#define ID2D1PathGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
    ((This)->lpVtbl->Base.ComputePointAtLength((ID2D1Geometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define ID2D1PathGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
    ((This)->lpVtbl->Base.Widen((ID2D1Geometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define ID2D1PathGeometry_Open(This, geometrySink) \
    ((This)->lpVtbl->Open(This, geometrySink))

#define ID2D1PathGeometry_Stream(This, geometrySink) \
    ((This)->lpVtbl->Stream(This, geometrySink))

#define ID2D1PathGeometry_GetSegmentCount(This, count) \
    ((This)->lpVtbl->GetSegmentCount(This, count))

#define ID2D1PathGeometry_GetFigureCount(This, count) \
    ((This)->lpVtbl->GetFigureCount(This, count))

typedef interface ID2D1Mesh ID2D1Mesh;

typedef struct ID2D1MeshVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD(Open)(
        ID2D1Mesh *This,
        __deref_out ID2D1TessellationSink **tessellationSink 
        ) PURE;
} ID2D1MeshVtbl;

interface ID2D1Mesh
{
    CONST struct ID2D1MeshVtbl *lpVtbl;
};


#define ID2D1Mesh_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Mesh_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1Mesh_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1Mesh_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1Mesh_Open(This, tessellationSink) \
    ((This)->lpVtbl->Open(This, tessellationSink))

typedef interface ID2D1Layer ID2D1Layer;

typedef struct ID2D1LayerVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ID2D1Layer *This 
        ) PURE;
} ID2D1LayerVtbl;

interface ID2D1Layer
{
    CONST struct ID2D1LayerVtbl *lpVtbl;
};


#define ID2D1Layer_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Layer_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1Layer_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1Layer_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1Layer_GetSize(This) \
    ((This)->lpVtbl->GetSize(This))

typedef interface ID2D1DrawingStateBlock ID2D1DrawingStateBlock;

typedef struct ID2D1DrawingStateBlockVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD_(void, GetDescription)(
        ID2D1DrawingStateBlock *This,
        __out D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        ) PURE;
    
    STDMETHOD_(void, SetDescription)(
        ID2D1DrawingStateBlock *This,
        __in CONST D2D1_DRAWING_STATE_DESCRIPTION *stateDescription 
        ) PURE;
    
    STDMETHOD_(void, SetTextRenderingParams)(
        ID2D1DrawingStateBlock *This,
        __in_opt IDWriteRenderingParams *textRenderingParams 
        ) PURE;
    
    STDMETHOD_(void, GetTextRenderingParams)(
        ID2D1DrawingStateBlock *This,
        __deref_out_opt IDWriteRenderingParams **textRenderingParams 
        ) PURE;
} ID2D1DrawingStateBlockVtbl;

interface ID2D1DrawingStateBlock
{
    CONST struct ID2D1DrawingStateBlockVtbl *lpVtbl;
};


#define ID2D1DrawingStateBlock_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1DrawingStateBlock_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1DrawingStateBlock_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1DrawingStateBlock_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1DrawingStateBlock_GetDescription(This, stateDescription) \
    ((This)->lpVtbl->GetDescription(This, stateDescription))

#define ID2D1DrawingStateBlock_SetDescription(This, stateDescription) \
    ((This)->lpVtbl->SetDescription(This, stateDescription))

#define ID2D1DrawingStateBlock_SetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->SetTextRenderingParams(This, textRenderingParams))

#define ID2D1DrawingStateBlock_GetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->GetTextRenderingParams(This, textRenderingParams))

typedef interface ID2D1RenderTarget ID2D1RenderTarget;

typedef struct ID2D1RenderTargetVtbl
{
    
    ID2D1ResourceVtbl Base;
    
    
    STDMETHOD(CreateBitmap)(
        ID2D1RenderTarget *This,
        D2D1_SIZE_U size,
        __in_opt CONST void *srcData,
        UINT32 pitch,
        __in CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    STDMETHOD(CreateBitmapFromWicBitmap)(
        ID2D1RenderTarget *This,
        __in IWICBitmapSource *wicBitmapSource,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    STDMETHOD(CreateSharedBitmap)(
        ID2D1RenderTarget *This,
        __in REFIID riid,
        __inout void *data,
        __in_opt CONST D2D1_BITMAP_PROPERTIES *bitmapProperties,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
    
    STDMETHOD(CreateBitmapBrush)(
        ID2D1RenderTarget *This,
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __deref_out ID2D1BitmapBrush **bitmapBrush 
        ) PURE;
    
    STDMETHOD(CreateSolidColorBrush)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_COLOR_F *color,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __deref_out ID2D1SolidColorBrush **solidColorBrush 
        ) PURE;
    
    STDMETHOD(CreateGradientStopCollection)(
        ID2D1RenderTarget *This,
        __in_ecount(gradientStopsCount) CONST D2D1_GRADIENT_STOP *gradientStops,
        __range(>=,1) UINT gradientStopsCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        __deref_out ID2D1GradientStopCollection **gradientStopCollection 
        ) PURE;
    
    STDMETHOD(CreateLinearGradientBrush)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1LinearGradientBrush **linearGradientBrush 
        ) PURE;
    
    STDMETHOD(CreateRadialGradientBrush)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
        __in_opt CONST D2D1_BRUSH_PROPERTIES *brushProperties,
        __in ID2D1GradientStopCollection *gradientStopCollection,
        __deref_out ID2D1RadialGradientBrush **radialGradientBrush 
        ) PURE;
    
    STDMETHOD(CreateCompatibleRenderTarget)(
        ID2D1RenderTarget *This,
        __in_opt CONST D2D1_SIZE_F *desiredSize,
        __in_opt CONST D2D1_SIZE_U *desiredPixelSize,
        __in_opt CONST D2D1_PIXEL_FORMAT *desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        __deref_out ID2D1BitmapRenderTarget **bitmapRenderTarget 
        ) PURE;
    
    STDMETHOD(CreateLayer)(
        ID2D1RenderTarget *This,
        __in_opt CONST D2D1_SIZE_F *size,
        __deref_out ID2D1Layer **layer 
        ) PURE;
    
    STDMETHOD(CreateMesh)(
        ID2D1RenderTarget *This,
        __deref_out ID2D1Mesh **mesh 
        ) PURE;
    
    STDMETHOD_(void, DrawLine)(
        ID2D1RenderTarget *This,
        D2D1_POINT_2F point0,
        D2D1_POINT_2F point1,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle 
        ) PURE;
    
    STDMETHOD_(void, DrawRectangle)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle 
        ) PURE;
    
    STDMETHOD_(void, FillRectangle)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_RECT_F *rect,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawRoundedRectangle)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle 
        ) PURE;
    
    STDMETHOD_(void, FillRoundedRectangle)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_ROUNDED_RECT *roundedRect,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawEllipse)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle 
        ) PURE;
    
    STDMETHOD_(void, FillEllipse)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_ELLIPSE *ellipse,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, DrawGeometry)(
        ID2D1RenderTarget *This,
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        FLOAT strokeWidth,
        __in_opt ID2D1StrokeStyle *strokeStyle 
        ) PURE;
    
    STDMETHOD_(void, FillGeometry)(
        ID2D1RenderTarget *This,
        __in ID2D1Geometry *geometry,
        __in ID2D1Brush *brush,
        __in_opt ID2D1Brush *opacityBrush 
        ) PURE;
    
    STDMETHOD_(void, FillMesh)(
        ID2D1RenderTarget *This,
        __in ID2D1Mesh *mesh,
        __in ID2D1Brush *brush 
        ) PURE;
    
    STDMETHOD_(void, FillOpacityMask)(
        ID2D1RenderTarget *This,
        __in ID2D1Bitmap *opacityMask,
        __in ID2D1Brush *brush,
        D2D1_OPACITY_MASK_CONTENT content,
        __in_opt CONST D2D1_RECT_F *destinationRectangle,
        __in_opt CONST D2D1_RECT_F *sourceRectangle 
        ) PURE;
    
    STDMETHOD_(void, DrawBitmap)(
        ID2D1RenderTarget *This,
        __in ID2D1Bitmap *bitmap,
        __in_opt CONST D2D1_RECT_F *destinationRectangle,
        FLOAT opacity,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
        __in_opt CONST D2D1_RECT_F *sourceRectangle 
        ) PURE;
    
    STDMETHOD_(void, DrawText)(
        ID2D1RenderTarget *This,
        __in_ecount(stringLength) CONST WCHAR *string,
        UINT stringLength,
        __in IDWriteTextFormat *textFormat,
        __in CONST D2D1_RECT_F *layoutRect,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options,
        DWRITE_MEASURING_MODE measuringMode 
        ) PURE;
    
    STDMETHOD_(void, DrawTextLayout)(
        ID2D1RenderTarget *This,
        D2D1_POINT_2F origin,
        __in IDWriteTextLayout *textLayout,
        __in ID2D1Brush *defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options 
        ) PURE;
    
    STDMETHOD_(void, DrawGlyphRun)(
        ID2D1RenderTarget *This,
        D2D1_POINT_2F baselineOrigin,
        __in CONST DWRITE_GLYPH_RUN *glyphRun,
        __in ID2D1Brush *foregroundBrush,
        DWRITE_MEASURING_MODE measuringMode 
        ) PURE;
    
    STDMETHOD_(void, SetTransform)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_MATRIX_3X2_F *transform 
        ) PURE;
    
    STDMETHOD_(void, GetTransform)(
        ID2D1RenderTarget *This,
        __out D2D1_MATRIX_3X2_F *transform 
        ) PURE;
    
    STDMETHOD_(void, SetAntialiasMode)(
        ID2D1RenderTarget *This,
        D2D1_ANTIALIAS_MODE antialiasMode 
        ) PURE;
    
    STDMETHOD_(D2D1_ANTIALIAS_MODE, GetAntialiasMode)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(void, SetTextAntialiasMode)(
        ID2D1RenderTarget *This,
        D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode 
        ) PURE;
    
    STDMETHOD_(D2D1_TEXT_ANTIALIAS_MODE, GetTextAntialiasMode)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(void, SetTextRenderingParams)(
        ID2D1RenderTarget *This,
        __in_opt IDWriteRenderingParams *textRenderingParams 
        ) PURE;
    
    STDMETHOD_(void, GetTextRenderingParams)(
        ID2D1RenderTarget *This,
        __deref_out_opt IDWriteRenderingParams **textRenderingParams 
        ) PURE;
    
    STDMETHOD_(void, SetTags)(
        ID2D1RenderTarget *This,
        D2D1_TAG tag1,
        D2D1_TAG tag2 
        ) PURE;
    
    STDMETHOD_(void, GetTags)(
        ID2D1RenderTarget *This,
        __out_opt D2D1_TAG *tag1,
        __out_opt D2D1_TAG *tag2 
        ) PURE;
    
    STDMETHOD_(void, PushLayer)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_LAYER_PARAMETERS *layerParameters,
        __in ID2D1Layer *layer 
        ) PURE;
    
    STDMETHOD_(void, PopLayer)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD(Flush)(
        ID2D1RenderTarget *This,
        __out_opt D2D1_TAG *tag1,
        __out_opt D2D1_TAG *tag2 
        ) PURE;
    
    STDMETHOD_(void, SaveDrawingState)(
        ID2D1RenderTarget *This,
        __inout ID2D1DrawingStateBlock *drawingStateBlock 
        ) PURE;
    
    STDMETHOD_(void, RestoreDrawingState)(
        ID2D1RenderTarget *This,
        __in ID2D1DrawingStateBlock *drawingStateBlock 
        ) PURE;
    
    STDMETHOD_(void, PushAxisAlignedClip)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_RECT_F *clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode 
        ) PURE;
    
    STDMETHOD_(void, PopAxisAlignedClip)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(void, Clear)(
        ID2D1RenderTarget *This,
        __in_opt CONST D2D1_COLOR_F *clearColor 
        ) PURE;
    
    STDMETHOD_(void, BeginDraw)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD(EndDraw)(
        ID2D1RenderTarget *This,
        __out_opt D2D1_TAG *tag1,
        __out_opt D2D1_TAG *tag2 
        ) PURE;
    
    STDMETHOD_(D2D1_PIXEL_FORMAT, GetPixelFormat)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(void, SetDpi)(
        ID2D1RenderTarget *This,
        FLOAT dpiX,
        FLOAT dpiY 
        ) PURE;
    
    STDMETHOD_(void, GetDpi)(
        ID2D1RenderTarget *This,
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) PURE;
    
    STDMETHOD_(D2D1_SIZE_F, GetSize)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(D2D1_SIZE_U, GetPixelSize)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(UINT32, GetMaximumBitmapSize)(
        ID2D1RenderTarget *This 
        ) PURE;
    
    STDMETHOD_(BOOL, IsSupported)(
        ID2D1RenderTarget *This,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties 
        ) PURE;
} ID2D1RenderTargetVtbl;

interface ID2D1RenderTarget
{
    CONST struct ID2D1RenderTargetVtbl *lpVtbl;
};


#define ID2D1RenderTarget_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1RenderTarget_AddRef(This) \
    ((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define ID2D1RenderTarget_Release(This) \
    ((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define ID2D1RenderTarget_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1RenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
    ((This)->lpVtbl->CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap))

#define ID2D1RenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
    ((This)->lpVtbl->CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap))

#define ID2D1RenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
    ((This)->lpVtbl->CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap))

#define ID2D1RenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
    ((This)->lpVtbl->CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define ID2D1RenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
    ((This)->lpVtbl->CreateSolidColorBrush(This, color, brushProperties, solidColorBrush))

#define ID2D1RenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
    ((This)->lpVtbl->CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define ID2D1RenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
    ((This)->lpVtbl->CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define ID2D1RenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
    ((This)->lpVtbl->CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define ID2D1RenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
    ((This)->lpVtbl->CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define ID2D1RenderTarget_CreateLayer(This, size, layer) \
    ((This)->lpVtbl->CreateLayer(This, size, layer))

#define ID2D1RenderTarget_CreateMesh(This, mesh) \
    ((This)->lpVtbl->CreateMesh(This, mesh))

#define ID2D1RenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle))

#define ID2D1RenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->DrawRectangle(This, rect, brush, strokeWidth, strokeStyle))

#define ID2D1RenderTarget_FillRectangle(This, rect, brush) \
    ((This)->lpVtbl->FillRectangle(This, rect, brush))

#define ID2D1RenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle))

#define ID2D1RenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
    ((This)->lpVtbl->FillRoundedRectangle(This, roundedRect, brush))

#define ID2D1RenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle))

#define ID2D1RenderTarget_FillEllipse(This, ellipse, brush) \
    ((This)->lpVtbl->FillEllipse(This, ellipse, brush))

#define ID2D1RenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle))

#define ID2D1RenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
    ((This)->lpVtbl->FillGeometry(This, geometry, brush, opacityBrush))

#define ID2D1RenderTarget_FillMesh(This, mesh, brush) \
    ((This)->lpVtbl->FillMesh(This, mesh, brush))

#define ID2D1RenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
    ((This)->lpVtbl->FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define ID2D1RenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
    ((This)->lpVtbl->DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define ID2D1RenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
    ((This)->lpVtbl->DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define ID2D1RenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
    ((This)->lpVtbl->DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options))

#define ID2D1RenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
    ((This)->lpVtbl->DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define ID2D1RenderTarget_SetTransform(This, transform) \
    ((This)->lpVtbl->SetTransform(This, transform))

#define ID2D1RenderTarget_GetTransform(This, transform) \
    ((This)->lpVtbl->GetTransform(This, transform))

#define ID2D1RenderTarget_SetAntialiasMode(This, antialiasMode) \
    ((This)->lpVtbl->SetAntialiasMode(This, antialiasMode))

#define ID2D1RenderTarget_GetAntialiasMode(This) \
    ((This)->lpVtbl->GetAntialiasMode(This))

#define ID2D1RenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
    ((This)->lpVtbl->SetTextAntialiasMode(This, textAntialiasMode))

#define ID2D1RenderTarget_GetTextAntialiasMode(This) \
    ((This)->lpVtbl->GetTextAntialiasMode(This))

#define ID2D1RenderTarget_SetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->SetTextRenderingParams(This, textRenderingParams))

#define ID2D1RenderTarget_GetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->GetTextRenderingParams(This, textRenderingParams))

#define ID2D1RenderTarget_SetTags(This, tag1, tag2) \
    ((This)->lpVtbl->SetTags(This, tag1, tag2))

#define ID2D1RenderTarget_GetTags(This, tag1, tag2) \
    ((This)->lpVtbl->GetTags(This, tag1, tag2))

#define ID2D1RenderTarget_PushLayer(This, layerParameters, layer) \
    ((This)->lpVtbl->PushLayer(This, layerParameters, layer))

#define ID2D1RenderTarget_PopLayer(This) \
    ((This)->lpVtbl->PopLayer(This))

#define ID2D1RenderTarget_Flush(This, tag1, tag2) \
    ((This)->lpVtbl->Flush(This, tag1, tag2))

#define ID2D1RenderTarget_SaveDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->SaveDrawingState(This, drawingStateBlock))

#define ID2D1RenderTarget_RestoreDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->RestoreDrawingState(This, drawingStateBlock))

#define ID2D1RenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
    ((This)->lpVtbl->PushAxisAlignedClip(This, clipRect, antialiasMode))

#define ID2D1RenderTarget_PopAxisAlignedClip(This) \
    ((This)->lpVtbl->PopAxisAlignedClip(This))

#define ID2D1RenderTarget_Clear(This, clearColor) \
    ((This)->lpVtbl->Clear(This, clearColor))

#define ID2D1RenderTarget_BeginDraw(This) \
    ((This)->lpVtbl->BeginDraw(This))

#define ID2D1RenderTarget_EndDraw(This, tag1, tag2) \
    ((This)->lpVtbl->EndDraw(This, tag1, tag2))

#define ID2D1RenderTarget_GetPixelFormat(This) \
    ((This)->lpVtbl->GetPixelFormat(This))

#define ID2D1RenderTarget_SetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->SetDpi(This, dpiX, dpiY))

#define ID2D1RenderTarget_GetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->GetDpi(This, dpiX, dpiY))

#define ID2D1RenderTarget_GetSize(This) \
    ((This)->lpVtbl->GetSize(This))

#define ID2D1RenderTarget_GetPixelSize(This) \
    ((This)->lpVtbl->GetPixelSize(This))

#define ID2D1RenderTarget_GetMaximumBitmapSize(This) \
    ((This)->lpVtbl->GetMaximumBitmapSize(This))

#define ID2D1RenderTarget_IsSupported(This, renderTargetProperties) \
    ((This)->lpVtbl->IsSupported(This, renderTargetProperties))

typedef interface ID2D1BitmapRenderTarget ID2D1BitmapRenderTarget;

typedef struct ID2D1BitmapRenderTargetVtbl
{
    
    ID2D1RenderTargetVtbl Base;
    
    
    STDMETHOD(GetBitmap)(
        ID2D1BitmapRenderTarget *This,
        __deref_out ID2D1Bitmap **bitmap 
        ) PURE;
} ID2D1BitmapRenderTargetVtbl;

interface ID2D1BitmapRenderTarget
{
    CONST struct ID2D1BitmapRenderTargetVtbl *lpVtbl;
};


#define ID2D1BitmapRenderTarget_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1BitmapRenderTarget_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1BitmapRenderTarget_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1BitmapRenderTarget_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1BitmapRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmap((ID2D1RenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define ID2D1BitmapRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((ID2D1RenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define ID2D1BitmapRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateSharedBitmap((ID2D1RenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define ID2D1BitmapRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
    ((This)->lpVtbl->Base.CreateBitmapBrush((ID2D1RenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define ID2D1BitmapRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
    ((This)->lpVtbl->Base.CreateSolidColorBrush((ID2D1RenderTarget *)This, color, brushProperties, solidColorBrush))

#define ID2D1BitmapRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
    ((This)->lpVtbl->Base.CreateGradientStopCollection((ID2D1RenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define ID2D1BitmapRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
    ((This)->lpVtbl->Base.CreateLinearGradientBrush((ID2D1RenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define ID2D1BitmapRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
    ((This)->lpVtbl->Base.CreateRadialGradientBrush((ID2D1RenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define ID2D1BitmapRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
    ((This)->lpVtbl->Base.CreateCompatibleRenderTarget((ID2D1RenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define ID2D1BitmapRenderTarget_CreateLayer(This, size, layer) \
    ((This)->lpVtbl->Base.CreateLayer((ID2D1RenderTarget *)This, size, layer))

#define ID2D1BitmapRenderTarget_CreateMesh(This, mesh) \
    ((This)->lpVtbl->Base.CreateMesh((ID2D1RenderTarget *)This, mesh))

#define ID2D1BitmapRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawLine((ID2D1RenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define ID2D1BitmapRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRectangle((ID2D1RenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define ID2D1BitmapRenderTarget_FillRectangle(This, rect, brush) \
    ((This)->lpVtbl->Base.FillRectangle((ID2D1RenderTarget *)This, rect, brush))

#define ID2D1BitmapRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define ID2D1BitmapRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
    ((This)->lpVtbl->Base.FillRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush))

#define ID2D1BitmapRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawEllipse((ID2D1RenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define ID2D1BitmapRenderTarget_FillEllipse(This, ellipse, brush) \
    ((This)->lpVtbl->Base.FillEllipse((ID2D1RenderTarget *)This, ellipse, brush))

#define ID2D1BitmapRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawGeometry((ID2D1RenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define ID2D1BitmapRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
    ((This)->lpVtbl->Base.FillGeometry((ID2D1RenderTarget *)This, geometry, brush, opacityBrush))

#define ID2D1BitmapRenderTarget_FillMesh(This, mesh, brush) \
    ((This)->lpVtbl->Base.FillMesh((ID2D1RenderTarget *)This, mesh, brush))

#define ID2D1BitmapRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
    ((This)->lpVtbl->Base.FillOpacityMask((ID2D1RenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define ID2D1BitmapRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
    ((This)->lpVtbl->Base.DrawBitmap((ID2D1RenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define ID2D1BitmapRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
    ((This)->lpVtbl->Base.DrawText((ID2D1RenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define ID2D1BitmapRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
    ((This)->lpVtbl->Base.DrawTextLayout((ID2D1RenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define ID2D1BitmapRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
    ((This)->lpVtbl->Base.DrawGlyphRun((ID2D1RenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define ID2D1BitmapRenderTarget_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1BitmapRenderTarget_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1BitmapRenderTarget_SetAntialiasMode(This, antialiasMode) \
    ((This)->lpVtbl->Base.SetAntialiasMode((ID2D1RenderTarget *)This, antialiasMode))

#define ID2D1BitmapRenderTarget_GetAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
    ((This)->lpVtbl->Base.SetTextAntialiasMode((ID2D1RenderTarget *)This, textAntialiasMode))

#define ID2D1BitmapRenderTarget_GetTextAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetTextAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.SetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1BitmapRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.GetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1BitmapRenderTarget_SetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.SetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1BitmapRenderTarget_GetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.GetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1BitmapRenderTarget_PushLayer(This, layerParameters, layer) \
    ((This)->lpVtbl->Base.PushLayer((ID2D1RenderTarget *)This, layerParameters, layer))

#define ID2D1BitmapRenderTarget_PopLayer(This) \
    ((This)->lpVtbl->Base.PopLayer((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_Flush(This, tag1, tag2) \
    ((This)->lpVtbl->Base.Flush((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1BitmapRenderTarget_SaveDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.SaveDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1BitmapRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.RestoreDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1BitmapRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
    ((This)->lpVtbl->Base.PushAxisAlignedClip((ID2D1RenderTarget *)This, clipRect, antialiasMode))

#define ID2D1BitmapRenderTarget_PopAxisAlignedClip(This) \
    ((This)->lpVtbl->Base.PopAxisAlignedClip((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_Clear(This, clearColor) \
    ((This)->lpVtbl->Base.Clear((ID2D1RenderTarget *)This, clearColor))

#define ID2D1BitmapRenderTarget_BeginDraw(This) \
    ((This)->lpVtbl->Base.BeginDraw((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_EndDraw(This, tag1, tag2) \
    ((This)->lpVtbl->Base.EndDraw((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1BitmapRenderTarget_GetPixelFormat(This) \
    ((This)->lpVtbl->Base.GetPixelFormat((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_SetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.SetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1BitmapRenderTarget_GetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.GetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1BitmapRenderTarget_GetSize(This) \
    ((This)->lpVtbl->Base.GetSize((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_GetPixelSize(This) \
    ((This)->lpVtbl->Base.GetPixelSize((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_GetMaximumBitmapSize(This) \
    ((This)->lpVtbl->Base.GetMaximumBitmapSize((ID2D1RenderTarget *)This))

#define ID2D1BitmapRenderTarget_IsSupported(This, renderTargetProperties) \
    ((This)->lpVtbl->Base.IsSupported((ID2D1RenderTarget *)This, renderTargetProperties))

#define ID2D1BitmapRenderTarget_GetBitmap(This, bitmap) \
    ((This)->lpVtbl->GetBitmap(This, bitmap))

typedef interface ID2D1HwndRenderTarget ID2D1HwndRenderTarget;

typedef struct ID2D1HwndRenderTargetVtbl
{
    
    ID2D1RenderTargetVtbl Base;
    
    
    STDMETHOD_(D2D1_WINDOW_STATE, CheckWindowState)(
        ID2D1HwndRenderTarget *This 
        ) PURE;
    
    STDMETHOD(Resize)(
        ID2D1HwndRenderTarget *This,
        __in CONST D2D1_SIZE_U *pixelSize 
        ) PURE;
    
    STDMETHOD_(HWND, GetHwnd)(
        ID2D1HwndRenderTarget *This 
        ) PURE;
} ID2D1HwndRenderTargetVtbl;

interface ID2D1HwndRenderTarget
{
    CONST struct ID2D1HwndRenderTargetVtbl *lpVtbl;
};


#define ID2D1HwndRenderTarget_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1HwndRenderTarget_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1HwndRenderTarget_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1HwndRenderTarget_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1HwndRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmap((ID2D1RenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define ID2D1HwndRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((ID2D1RenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define ID2D1HwndRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateSharedBitmap((ID2D1RenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define ID2D1HwndRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
    ((This)->lpVtbl->Base.CreateBitmapBrush((ID2D1RenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define ID2D1HwndRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
    ((This)->lpVtbl->Base.CreateSolidColorBrush((ID2D1RenderTarget *)This, color, brushProperties, solidColorBrush))

#define ID2D1HwndRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
    ((This)->lpVtbl->Base.CreateGradientStopCollection((ID2D1RenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define ID2D1HwndRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
    ((This)->lpVtbl->Base.CreateLinearGradientBrush((ID2D1RenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define ID2D1HwndRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
    ((This)->lpVtbl->Base.CreateRadialGradientBrush((ID2D1RenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define ID2D1HwndRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
    ((This)->lpVtbl->Base.CreateCompatibleRenderTarget((ID2D1RenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define ID2D1HwndRenderTarget_CreateLayer(This, size, layer) \
    ((This)->lpVtbl->Base.CreateLayer((ID2D1RenderTarget *)This, size, layer))

#define ID2D1HwndRenderTarget_CreateMesh(This, mesh) \
    ((This)->lpVtbl->Base.CreateMesh((ID2D1RenderTarget *)This, mesh))

#define ID2D1HwndRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawLine((ID2D1RenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define ID2D1HwndRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRectangle((ID2D1RenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define ID2D1HwndRenderTarget_FillRectangle(This, rect, brush) \
    ((This)->lpVtbl->Base.FillRectangle((ID2D1RenderTarget *)This, rect, brush))

#define ID2D1HwndRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define ID2D1HwndRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
    ((This)->lpVtbl->Base.FillRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush))

#define ID2D1HwndRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawEllipse((ID2D1RenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define ID2D1HwndRenderTarget_FillEllipse(This, ellipse, brush) \
    ((This)->lpVtbl->Base.FillEllipse((ID2D1RenderTarget *)This, ellipse, brush))

#define ID2D1HwndRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawGeometry((ID2D1RenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define ID2D1HwndRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
    ((This)->lpVtbl->Base.FillGeometry((ID2D1RenderTarget *)This, geometry, brush, opacityBrush))

#define ID2D1HwndRenderTarget_FillMesh(This, mesh, brush) \
    ((This)->lpVtbl->Base.FillMesh((ID2D1RenderTarget *)This, mesh, brush))

#define ID2D1HwndRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
    ((This)->lpVtbl->Base.FillOpacityMask((ID2D1RenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define ID2D1HwndRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
    ((This)->lpVtbl->Base.DrawBitmap((ID2D1RenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define ID2D1HwndRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
    ((This)->lpVtbl->Base.DrawText((ID2D1RenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define ID2D1HwndRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
    ((This)->lpVtbl->Base.DrawTextLayout((ID2D1RenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define ID2D1HwndRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
    ((This)->lpVtbl->Base.DrawGlyphRun((ID2D1RenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define ID2D1HwndRenderTarget_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1HwndRenderTarget_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1HwndRenderTarget_SetAntialiasMode(This, antialiasMode) \
    ((This)->lpVtbl->Base.SetAntialiasMode((ID2D1RenderTarget *)This, antialiasMode))

#define ID2D1HwndRenderTarget_GetAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
    ((This)->lpVtbl->Base.SetTextAntialiasMode((ID2D1RenderTarget *)This, textAntialiasMode))

#define ID2D1HwndRenderTarget_GetTextAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetTextAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.SetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1HwndRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.GetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1HwndRenderTarget_SetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.SetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1HwndRenderTarget_GetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.GetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1HwndRenderTarget_PushLayer(This, layerParameters, layer) \
    ((This)->lpVtbl->Base.PushLayer((ID2D1RenderTarget *)This, layerParameters, layer))

#define ID2D1HwndRenderTarget_PopLayer(This) \
    ((This)->lpVtbl->Base.PopLayer((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_Flush(This, tag1, tag2) \
    ((This)->lpVtbl->Base.Flush((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1HwndRenderTarget_SaveDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.SaveDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1HwndRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.RestoreDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1HwndRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
    ((This)->lpVtbl->Base.PushAxisAlignedClip((ID2D1RenderTarget *)This, clipRect, antialiasMode))

#define ID2D1HwndRenderTarget_PopAxisAlignedClip(This) \
    ((This)->lpVtbl->Base.PopAxisAlignedClip((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_Clear(This, clearColor) \
    ((This)->lpVtbl->Base.Clear((ID2D1RenderTarget *)This, clearColor))

#define ID2D1HwndRenderTarget_BeginDraw(This) \
    ((This)->lpVtbl->Base.BeginDraw((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_EndDraw(This, tag1, tag2) \
    ((This)->lpVtbl->Base.EndDraw((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1HwndRenderTarget_GetPixelFormat(This) \
    ((This)->lpVtbl->Base.GetPixelFormat((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_SetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.SetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1HwndRenderTarget_GetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.GetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1HwndRenderTarget_GetSize(This) \
    ((This)->lpVtbl->Base.GetSize((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_GetPixelSize(This) \
    ((This)->lpVtbl->Base.GetPixelSize((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_GetMaximumBitmapSize(This) \
    ((This)->lpVtbl->Base.GetMaximumBitmapSize((ID2D1RenderTarget *)This))

#define ID2D1HwndRenderTarget_IsSupported(This, renderTargetProperties) \
    ((This)->lpVtbl->Base.IsSupported((ID2D1RenderTarget *)This, renderTargetProperties))

#define ID2D1HwndRenderTarget_CheckWindowState(This) \
    ((This)->lpVtbl->CheckWindowState(This))

#define ID2D1HwndRenderTarget_Resize(This, pixelSize) \
    ((This)->lpVtbl->Resize(This, pixelSize))

#define ID2D1HwndRenderTarget_GetHwnd(This) \
    ((This)->lpVtbl->GetHwnd(This))

typedef interface ID2D1GdiInteropRenderTarget ID2D1GdiInteropRenderTarget;

typedef struct ID2D1GdiInteropRenderTargetVtbl
{
    
    IUnknownVtbl Base;
    
    
    STDMETHOD(GetDC)(
        ID2D1GdiInteropRenderTarget *This,
        D2D1_DC_INITIALIZE_MODE mode,
        __out HDC *hdc 
        ) PURE;
    
    STDMETHOD(ReleaseDC)(
        ID2D1GdiInteropRenderTarget *This,
        __in_opt CONST RECT *update 
        ) PURE;
} ID2D1GdiInteropRenderTargetVtbl;

interface ID2D1GdiInteropRenderTarget
{
    CONST struct ID2D1GdiInteropRenderTargetVtbl *lpVtbl;
};


#define ID2D1GdiInteropRenderTarget_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1GdiInteropRenderTarget_AddRef(This) \
    ((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define ID2D1GdiInteropRenderTarget_Release(This) \
    ((This)->lpVtbl->Base.Release((IUnknown *)This))

#define ID2D1GdiInteropRenderTarget_GetDC(This, mode, hdc) \
    ((This)->lpVtbl->GetDC(This, mode, hdc))

#define ID2D1GdiInteropRenderTarget_ReleaseDC(This, update) \
    ((This)->lpVtbl->ReleaseDC(This, update))

typedef interface ID2D1DCRenderTarget ID2D1DCRenderTarget;

typedef struct ID2D1DCRenderTargetVtbl
{
    
    ID2D1RenderTargetVtbl Base;
    
    
    STDMETHOD(BindDC)(
        ID2D1DCRenderTarget *This,
        __in CONST HDC hDC,
        __in CONST RECT *pSubRect 
        ) PURE;
} ID2D1DCRenderTargetVtbl;

interface ID2D1DCRenderTarget
{
    CONST struct ID2D1DCRenderTargetVtbl *lpVtbl;
};


#define ID2D1DCRenderTarget_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1DCRenderTarget_AddRef(This) \
    ((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define ID2D1DCRenderTarget_Release(This) \
    ((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define ID2D1DCRenderTarget_GetFactory(This, factory) \
    ((This)->lpVtbl->Base.Base.GetFactory((ID2D1Resource *)This, factory))

#define ID2D1DCRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmap((ID2D1RenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define ID2D1DCRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((ID2D1RenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define ID2D1DCRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
    ((This)->lpVtbl->Base.CreateSharedBitmap((ID2D1RenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define ID2D1DCRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
    ((This)->lpVtbl->Base.CreateBitmapBrush((ID2D1RenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define ID2D1DCRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
    ((This)->lpVtbl->Base.CreateSolidColorBrush((ID2D1RenderTarget *)This, color, brushProperties, solidColorBrush))

#define ID2D1DCRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
    ((This)->lpVtbl->Base.CreateGradientStopCollection((ID2D1RenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define ID2D1DCRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
    ((This)->lpVtbl->Base.CreateLinearGradientBrush((ID2D1RenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define ID2D1DCRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
    ((This)->lpVtbl->Base.CreateRadialGradientBrush((ID2D1RenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define ID2D1DCRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
    ((This)->lpVtbl->Base.CreateCompatibleRenderTarget((ID2D1RenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define ID2D1DCRenderTarget_CreateLayer(This, size, layer) \
    ((This)->lpVtbl->Base.CreateLayer((ID2D1RenderTarget *)This, size, layer))

#define ID2D1DCRenderTarget_CreateMesh(This, mesh) \
    ((This)->lpVtbl->Base.CreateMesh((ID2D1RenderTarget *)This, mesh))

#define ID2D1DCRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawLine((ID2D1RenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define ID2D1DCRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRectangle((ID2D1RenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define ID2D1DCRenderTarget_FillRectangle(This, rect, brush) \
    ((This)->lpVtbl->Base.FillRectangle((ID2D1RenderTarget *)This, rect, brush))

#define ID2D1DCRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define ID2D1DCRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
    ((This)->lpVtbl->Base.FillRoundedRectangle((ID2D1RenderTarget *)This, roundedRect, brush))

#define ID2D1DCRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawEllipse((ID2D1RenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define ID2D1DCRenderTarget_FillEllipse(This, ellipse, brush) \
    ((This)->lpVtbl->Base.FillEllipse((ID2D1RenderTarget *)This, ellipse, brush))

#define ID2D1DCRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
    ((This)->lpVtbl->Base.DrawGeometry((ID2D1RenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define ID2D1DCRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
    ((This)->lpVtbl->Base.FillGeometry((ID2D1RenderTarget *)This, geometry, brush, opacityBrush))

#define ID2D1DCRenderTarget_FillMesh(This, mesh, brush) \
    ((This)->lpVtbl->Base.FillMesh((ID2D1RenderTarget *)This, mesh, brush))

#define ID2D1DCRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
    ((This)->lpVtbl->Base.FillOpacityMask((ID2D1RenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define ID2D1DCRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
    ((This)->lpVtbl->Base.DrawBitmap((ID2D1RenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define ID2D1DCRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
    ((This)->lpVtbl->Base.DrawText((ID2D1RenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define ID2D1DCRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
    ((This)->lpVtbl->Base.DrawTextLayout((ID2D1RenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define ID2D1DCRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
    ((This)->lpVtbl->Base.DrawGlyphRun((ID2D1RenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define ID2D1DCRenderTarget_SetTransform(This, transform) \
    ((This)->lpVtbl->Base.SetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1DCRenderTarget_GetTransform(This, transform) \
    ((This)->lpVtbl->Base.GetTransform((ID2D1RenderTarget *)This, transform))

#define ID2D1DCRenderTarget_SetAntialiasMode(This, antialiasMode) \
    ((This)->lpVtbl->Base.SetAntialiasMode((ID2D1RenderTarget *)This, antialiasMode))

#define ID2D1DCRenderTarget_GetAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
    ((This)->lpVtbl->Base.SetTextAntialiasMode((ID2D1RenderTarget *)This, textAntialiasMode))

#define ID2D1DCRenderTarget_GetTextAntialiasMode(This) \
    ((This)->lpVtbl->Base.GetTextAntialiasMode((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.SetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1DCRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
    ((This)->lpVtbl->Base.GetTextRenderingParams((ID2D1RenderTarget *)This, textRenderingParams))

#define ID2D1DCRenderTarget_SetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.SetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1DCRenderTarget_GetTags(This, tag1, tag2) \
    ((This)->lpVtbl->Base.GetTags((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1DCRenderTarget_PushLayer(This, layerParameters, layer) \
    ((This)->lpVtbl->Base.PushLayer((ID2D1RenderTarget *)This, layerParameters, layer))

#define ID2D1DCRenderTarget_PopLayer(This) \
    ((This)->lpVtbl->Base.PopLayer((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_Flush(This, tag1, tag2) \
    ((This)->lpVtbl->Base.Flush((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1DCRenderTarget_SaveDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.SaveDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1DCRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
    ((This)->lpVtbl->Base.RestoreDrawingState((ID2D1RenderTarget *)This, drawingStateBlock))

#define ID2D1DCRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
    ((This)->lpVtbl->Base.PushAxisAlignedClip((ID2D1RenderTarget *)This, clipRect, antialiasMode))

#define ID2D1DCRenderTarget_PopAxisAlignedClip(This) \
    ((This)->lpVtbl->Base.PopAxisAlignedClip((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_Clear(This, clearColor) \
    ((This)->lpVtbl->Base.Clear((ID2D1RenderTarget *)This, clearColor))

#define ID2D1DCRenderTarget_BeginDraw(This) \
    ((This)->lpVtbl->Base.BeginDraw((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_EndDraw(This, tag1, tag2) \
    ((This)->lpVtbl->Base.EndDraw((ID2D1RenderTarget *)This, tag1, tag2))

#define ID2D1DCRenderTarget_GetPixelFormat(This) \
    ((This)->lpVtbl->Base.GetPixelFormat((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_SetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.SetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1DCRenderTarget_GetDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->Base.GetDpi((ID2D1RenderTarget *)This, dpiX, dpiY))

#define ID2D1DCRenderTarget_GetSize(This) \
    ((This)->lpVtbl->Base.GetSize((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_GetPixelSize(This) \
    ((This)->lpVtbl->Base.GetPixelSize((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_GetMaximumBitmapSize(This) \
    ((This)->lpVtbl->Base.GetMaximumBitmapSize((ID2D1RenderTarget *)This))

#define ID2D1DCRenderTarget_IsSupported(This, renderTargetProperties) \
    ((This)->lpVtbl->Base.IsSupported((ID2D1RenderTarget *)This, renderTargetProperties))

#define ID2D1DCRenderTarget_BindDC(This, hDC, pSubRect) \
    ((This)->lpVtbl->BindDC(This, hDC, pSubRect))

typedef interface ID2D1Factory ID2D1Factory;

typedef struct ID2D1FactoryVtbl
{
    
    IUnknownVtbl Base;
    
    
    STDMETHOD(ReloadSystemMetrics)(
        ID2D1Factory *This 
        ) PURE;
    
    STDMETHOD_(void, GetDesktopDpi)(
        ID2D1Factory *This,
        __out FLOAT *dpiX,
        __out FLOAT *dpiY 
        ) PURE;
    
    STDMETHOD(CreateRectangleGeometry)(
        ID2D1Factory *This,
        __in CONST D2D1_RECT_F *rectangle,
        __deref_out ID2D1RectangleGeometry **rectangleGeometry 
        ) PURE;
    
    STDMETHOD(CreateRoundedRectangleGeometry)(
        ID2D1Factory *This,
        __in CONST D2D1_ROUNDED_RECT *roundedRectangle,
        __deref_out ID2D1RoundedRectangleGeometry **roundedRectangleGeometry 
        ) PURE;
    
    STDMETHOD(CreateEllipseGeometry)(
        ID2D1Factory *This,
        __in CONST D2D1_ELLIPSE *ellipse,
        __deref_out ID2D1EllipseGeometry **ellipseGeometry 
        ) PURE;
    
    STDMETHOD(CreateGeometryGroup)(
        ID2D1Factory *This,
        D2D1_FILL_MODE fillMode,
        __in_ecount(geometriesCount) ID2D1Geometry **geometries,
        UINT geometriesCount,
        __deref_out ID2D1GeometryGroup **geometryGroup 
        ) PURE;
    
    STDMETHOD(CreateTransformedGeometry)(
        ID2D1Factory *This,
        __in ID2D1Geometry *sourceGeometry,
        __in CONST D2D1_MATRIX_3X2_F *transform,
        __deref_out ID2D1TransformedGeometry **transformedGeometry 
        ) PURE;
    
    STDMETHOD(CreatePathGeometry)(
        ID2D1Factory *This,
        __deref_out ID2D1PathGeometry **pathGeometry 
        ) PURE;
    
    STDMETHOD(CreateStrokeStyle)(
        ID2D1Factory *This,
        __in CONST D2D1_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
        __in_ecount_opt(dashesCount) CONST FLOAT *dashes,
        UINT dashesCount,
        __deref_out ID2D1StrokeStyle **strokeStyle 
        ) PURE;
    
    STDMETHOD(CreateDrawingStateBlock)(
        ID2D1Factory *This,
        __in_opt CONST D2D1_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
        __in_opt IDWriteRenderingParams *textRenderingParams,
        __deref_out ID2D1DrawingStateBlock **drawingStateBlock 
        ) PURE;
    
    STDMETHOD(CreateWicBitmapRenderTarget)(
        ID2D1Factory *This,
        __in IWICBitmap *target,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) PURE;
    
    STDMETHOD(CreateHwndRenderTarget)(
        ID2D1Factory *This,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __in CONST D2D1_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties,
        __deref_out ID2D1HwndRenderTarget **hwndRenderTarget 
        ) PURE;
    
    STDMETHOD(CreateDxgiSurfaceRenderTarget)(
        ID2D1Factory *This,
        __in IDXGISurface *dxgiSurface,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1RenderTarget **renderTarget 
        ) PURE;
    
    STDMETHOD(CreateDCRenderTarget)(
        ID2D1Factory *This,
        __in CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties,
        __deref_out ID2D1DCRenderTarget **dcRenderTarget 
        ) PURE;
} ID2D1FactoryVtbl;

interface ID2D1Factory
{
    CONST struct ID2D1FactoryVtbl *lpVtbl;
};


#define ID2D1Factory_QueryInterface(This, riid, ppv) \
    ((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define ID2D1Factory_AddRef(This) \
    ((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define ID2D1Factory_Release(This) \
    ((This)->lpVtbl->Base.Release((IUnknown *)This))

#define ID2D1Factory_ReloadSystemMetrics(This) \
    ((This)->lpVtbl->ReloadSystemMetrics(This))

#define ID2D1Factory_GetDesktopDpi(This, dpiX, dpiY) \
    ((This)->lpVtbl->GetDesktopDpi(This, dpiX, dpiY))

#define ID2D1Factory_CreateRectangleGeometry(This, rectangle, rectangleGeometry) \
    ((This)->lpVtbl->CreateRectangleGeometry(This, rectangle, rectangleGeometry))

#define ID2D1Factory_CreateRoundedRectangleGeometry(This, roundedRectangle, roundedRectangleGeometry) \
    ((This)->lpVtbl->CreateRoundedRectangleGeometry(This, roundedRectangle, roundedRectangleGeometry))

#define ID2D1Factory_CreateEllipseGeometry(This, ellipse, ellipseGeometry) \
    ((This)->lpVtbl->CreateEllipseGeometry(This, ellipse, ellipseGeometry))

#define ID2D1Factory_CreateGeometryGroup(This, fillMode, geometries, geometriesCount, geometryGroup) \
    ((This)->lpVtbl->CreateGeometryGroup(This, fillMode, geometries, geometriesCount, geometryGroup))

#define ID2D1Factory_CreateTransformedGeometry(This, sourceGeometry, transform, transformedGeometry) \
    ((This)->lpVtbl->CreateTransformedGeometry(This, sourceGeometry, transform, transformedGeometry))

#define ID2D1Factory_CreatePathGeometry(This, pathGeometry) \
    ((This)->lpVtbl->CreatePathGeometry(This, pathGeometry))

#define ID2D1Factory_CreateStrokeStyle(This, strokeStyleProperties, dashes, dashesCount, strokeStyle) \
    ((This)->lpVtbl->CreateStrokeStyle(This, strokeStyleProperties, dashes, dashesCount, strokeStyle))

#define ID2D1Factory_CreateDrawingStateBlock(This, drawingStateDescription, textRenderingParams, drawingStateBlock) \
    ((This)->lpVtbl->CreateDrawingStateBlock(This, drawingStateDescription, textRenderingParams, drawingStateBlock))

#define ID2D1Factory_CreateWicBitmapRenderTarget(This, target, renderTargetProperties, renderTarget) \
    ((This)->lpVtbl->CreateWicBitmapRenderTarget(This, target, renderTargetProperties, renderTarget))

#define ID2D1Factory_CreateHwndRenderTarget(This, renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget) \
    ((This)->lpVtbl->CreateHwndRenderTarget(This, renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget))

#define ID2D1Factory_CreateDxgiSurfaceRenderTarget(This, dxgiSurface, renderTargetProperties, renderTarget) \
    ((This)->lpVtbl->CreateDxgiSurfaceRenderTarget(This, dxgiSurface, renderTargetProperties, renderTarget))

#define ID2D1Factory_CreateDCRenderTarget(This, renderTargetProperties, dcRenderTarget) \
    ((This)->lpVtbl->CreateDCRenderTarget(This, renderTargetProperties, dcRenderTarget))


#endif


#ifdef __cplusplus
extern "C"
{
#endif

    //
    // This export cannot be in a namespace because compiler name mangling isn't consistent
    // also, this must be 'C' callable.
    // 
    HRESULT WINAPI
    D2D1CreateFactory(
        __in D2D1_FACTORY_TYPE factoryType,
        __in REFIID riid,
        __in_opt CONST D2D1_FACTORY_OPTIONS *pFactoryOptions,
        __out void **ppIFactory
        );

        
    void WINAPI
    D2D1MakeRotateMatrix(
        __in FLOAT angle,
        __in D2D1_POINT_2F center,
        __out D2D1_MATRIX_3X2_F *matrix
        );
        
    void WINAPI
    D2D1MakeSkewMatrix(
        __in FLOAT angleX,
        __in FLOAT angleY,
        __in D2D1_POINT_2F center,
        __out D2D1_MATRIX_3X2_F *matrix
        );

    BOOL WINAPI
    D2D1IsMatrixInvertible(
        __in CONST D2D1_MATRIX_3X2_F *matrix
        );

    BOOL WINAPI
    D2D1InvertMatrix(
        __inout D2D1_MATRIX_3X2_F *matrix
        );

#ifdef __cplusplus
}
#endif

#ifndef D2D1FORCEINLINE
#define D2D1FORCEINLINE FORCEINLINE
#endif // #ifndef D2D1FORCEINLINE 

        
#include <d2d1helper.h>


#ifndef D2D_USE_C_DEFINITIONS

inline
HRESULT
D2D1CreateFactory(
    __in D2D1_FACTORY_TYPE factoryType,
    __in REFIID riid,
    __out void **factory
    )
{
    return 
        D2D1CreateFactory(
            factoryType,
            riid,
            NULL,
            factory);
}


template<class Factory>
HRESULT
D2D1CreateFactory(
    __in D2D1_FACTORY_TYPE factoryType,
    __out Factory **factory
    )
{
    return
        D2D1CreateFactory(
            factoryType,
            __uuidof(Factory),
            reinterpret_cast<void **>(factory));
}

template<class Factory>
HRESULT
D2D1CreateFactory(
    __in D2D1_FACTORY_TYPE factoryType,
    __in CONST D2D1_FACTORY_OPTIONS &factoryOptions,
    __out Factory **ppFactory
    )
{
    return
        D2D1CreateFactory(
            factoryType,            
            __uuidof(Factory),
            &factoryOptions,
            reinterpret_cast<void **>(ppFactory));
}

#endif // #ifndef D2D_USE_C_DEFINITIONS
#endif // #ifndef _D2D1_H_
