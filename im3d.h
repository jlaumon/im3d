#pragma once
#ifndef im3d_h
#define im3d_h

#include "im3d_config.h"

#define IM3D_VERSION "1.0"

#ifndef IM3D_ASSERT
	#include <cassert>
	#define IM3D_ASSERT(e) assert(e)
#endif

namespace Im3d {

typedef unsigned int U32;
typedef U32 Id;
struct Vec2;
struct Vec3;
struct Vec4;
struct Mat3;
struct Mat4;
struct Color;
struct VertexData;
struct AppData;
class  Context;

extern const Id    Id_Invalid;
extern const Color Color_Black;
extern const Color Color_White;
extern const Color Color_Red;
extern const Color Color_Green;
extern const Color Color_Blue;
extern const Color Color_Magenta;
extern const Color Color_Yellow;
extern const Color Color_Cyan;

Context& GetContext();
void     SetContext(Context& _ctx);
AppData& GetAppData();

// Call at the start of each frame, after filling the AppData struct.
void  NewFrame();
// Call after all Im3d calls have been made for the current frame.
void  Draw();

// Begin primitive. End() *must* be called before starting each new primitive type.
void  BeginPoints();
void  BeginLines();
void  BeginLineLoop();
void  BeginLineStrip();
void  BeginTriangles();
void  BeginTriangleStrip();
// End the current primitive.
void  End();

// Add a vertex to the current primitive (call between Begin*() and End()).
void  Vertex(const Vec3& _position);
void  Vertex(const Vec3& _position, Color _color);
void  Vertex(const Vec3& _position, float _size);
void  Vertex(const Vec3& _position, float _size, Color _color);
void  Vertex(float _x, float _y, float _z);
void  Vertex(float _x, float _y, float _z, Color _color);
void  Vertex(float _x, float _y, float _z, float _size);
void  Vertex(float _x, float _y, float _z, float _size, Color _color);

// Color draw state (per vertex).
void  PushColor(); // push the stack top
void  PushColor(Color _color);
void  PopColor();
void  SetColor(Color _color);
void  SetColor(float _r, float _g, float _b, float _a = 1.0f);
Color GetColor();

// Alpha draw state, multiplies the color draw state's alpha (per vertex).
void  PushAlpha(); // push the stack top
void  PushAlpha(float _alpha);
void  PopAlpha();
void  SetAlpha(float _alpha);
float GetAlpha();

// Size draw state, for points/lines this is the width/radius in pixels (per vertex)
void  PushSize(); // push the stack top
void  PushSize(float _size);
void  PopSize();
void  SetSize(float _size);
float GetSize();

// Sorting draw state, enable depth sorting between primitives (per primitive).
void  PushEnableSorting(); // push the stack top
void  PushEnableSorting(bool _enable);
void  PopEnableSorting();
void  EnableSorting(bool _enable);

// Push/pop all draw states (color, alpha, size, sorting).
void  PushDrawState();
void  PopDrawState();

// Transform state (per vertex).
void  PushMatrix(); // push stack top
void  PushMatrix(const Mat4& _mat4);
void  PopMatrix();
void  SetMatrix(const Mat4& _mat4);
void  SetIdentity();
void  MulMatrix(const Mat4& _mat4);
void  Translate(float _x, float _y, float _z);
void  Rotate(const Vec3& _axis, float _angle);
void  Scale(float _x, float _y, float _z);

// High order shapes.
void  DrawXyzAxes();
void  DrawQuad(const Vec3& _a, const Vec3& _b, const Vec3& _c, const Vec3& _d);
void  DrawQuad(const Vec3& _origin, const Vec3& _normal, const Vec2& _size);
void  DrawQuadFilled(const Vec3& _a, const Vec3& _b, const Vec3& _c, const Vec3& _d);
void  DrawCircle(const Vec3& _origin, const Vec3& _normal, float _radius, int _detail = 24);
void  DrawSphere(const Vec3& _origin, float _radius, int _detail = 24);
void  DrawAlignedBox(const Vec3& _min, const Vec3& _max);
void  DrawCylinder(const Vec3& _start, const Vec3& _end, float _radius, int _detail = 24);
void  DrawCapsule(const Vec3& _start, const Vec3& _end, float _radius, int _detail = 12);
void  DrawArrow(const Vec3& _start, const Vec3& _end, float _headLength);


// Generate an Id from a null-terminated string.
Id    MakeId(const char* _str);
void  PushId(); // push stack top
void  PushId(Id _id);
void  PopId();
Id    GetId();
Id    GetActiveId(); // GetActiveId() != Id_Invalid means that a gizmo is in use

// Manipulate translation/rotation/scale via a gizmo. Return true if the gizmo was used (if it modified its output).
bool  Gizmo(const char* _id, float* _mat4_);
bool  GizmoTranslation(const char* _id, float* _vec3_);
bool  GizmoRotation(const char* _id, const Vec3& _drawAt, float* _mat3_);
bool  GizmoScaleLocal(const char* _id, float* _vec3_);

struct Vec2
{
	float x, y; 
	Vec2()                                                                   {}
	Vec2(float _xy): x(_xy), y(_xy)                                          {}
	Vec2(float _x, float _y): x(_x), y(_y)                                   {}
	operator float*()                                                        { return &x; }
	operator const float*() const                                            { return &x; }
	#ifdef IM3D_VEC2_USER
		IM3D_VEC2_USER
	#endif
};
struct Vec3
{ 
	float x, y, z;
	Vec3()                                                                   {}
	Vec3(float _xyz): x(_xyz), y(_xyz), z(_xyz)                              {}
	Vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z)                  {}
	Vec3(const Vec2& _xy, float _z): x(_xy.x), y(_xy.y), z(_z)               {}
	Vec3(const Vec4& _v); // discards w
	operator float*()                                                        { return &x; }
	operator const float*() const                                            { return &x; }
	#ifdef IM3D_VEC3_USER
		IM3D_VEC3_USER
	#endif
};
struct Vec4
{ 
	float x, y, z, w;
	Vec4()                                                                   {}
	Vec4(float _xyzw): x(_xyzw), y(_xyzw), z(_xyzw), w(_xyzw)                {}
	Vec4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {}
	Vec4(const Vec3& _xyz, float _w): x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}
	Vec4(Color _rgba);
	operator float*()                                                        { return &x; }
	operator const float*() const                                            { return &x; }
	#ifdef IM3D_VEC4_USER
		IM3D_VEC4_USER
	#endif
};
struct Mat3
{
	float m[9]; // column-major unless IM3D_MATRIX_ROW_MAJOR defined
	Mat3()                                                                   {}
	Mat3(float _diagonal);
	Mat3(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22
		);
	Mat3(const Vec3& _colX, const Vec3& _colY, const Vec3& _colZ);
	Mat3(const Mat4& _mat4); // extract upper 3x3
	operator float*()                                                        { return m; }
	operator const float*() const                                            { return m; }

	Vec3 getCol(int _i) const;
	Vec3 getRow(int _i) const;
	void setCol(int _i, const Vec3& _v);
	void setRow(int _i, const Vec3& _v);
	
	float operator()(int _row, int _col) const
	{
		#ifdef IM3D_MATRIX_ROW_MAJOR
			int i = _row * 3 + _col;
		#else
			int i = _col * 3 + _row;
		#endif
		return m[i];
	}
	float& operator()(int _row, int _col)
	{ 
		#ifdef IM3D_MATRIX_ROW_MAJOR
			int i = _row * 3 + _col;
		#else
			int i = _col * 3 + _row;
		#endif
		return m[i];
	}
	
	#ifdef IM3D_MAT3_USER
		IM3D_MAT3_USER
	#endif
};
struct Mat4
{
	float m[16]; // column-major unless IM3D_MATRIX_ROW_MAJOR defined
	Mat4()                                                                   {}
	Mat4(float _diagonal);
	Mat4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f
		);
	Mat4(const Mat3& _mat3);
	operator float*()                                                        { return m; }
	operator const float*() const                                            { return m; }

	Vec4 getCol(int _i) const;
	Vec4 getRow(int _i) const;
	void setCol(int _i, const Vec4& _v);
	void setRow(int _i, const Vec4& _v);
	
	void setRotationScale(const Mat3& _m); // insert upper 3x3
	void setTranslation(const Vec3& _v);   // insert col 3
	
	float operator()(int _row, int _col) const
	{
		#ifdef IM3D_MATRIX_ROW_MAJOR
			int i = _row * 4 + _col;
		#else
			int i = _col * 4 + _row;
		#endif
		return m[i];
	}
	float& operator()(int _row, int _col)
	{ 
		#ifdef IM3D_MATRIX_ROW_MAJOR
			int i = _row * 4 + _col;
		#else
			int i = _col * 4 + _row;
		#endif
		return m[i];
	}
	
	#ifdef IM3D_MAT4_USER
		IM3D_MAT4_USER
	#endif
};
struct Color
{
	U32 v;
	Color(): v(0)                                                            {}
	Color(U32 _rgba): v(_rgba)                                               {}
	Color(const Vec4& _rgba);
	Color(float _r, float _g, float _b, float _a = 1.0f);
	operator U32() const                                                     { return v; }

	void set(int _i, float _val)
	{
		_i *= 8;
		U32 mask = 0xff << _i;
		v = (v & ~mask) | ((U32)(_val * 255.0f) << _i);
	}
	void setR(float _val)                                                    { set(3, _val); }
	void setG(float _val)                                                    { set(2, _val); }
	void setB(float _val)                                                    { set(1, _val); }
	void setA(float _val)                                                    { set(0, _val); }

	float get(int _i) const
	{
		_i *= 8;
		U32 mask = 0xff << _i;
		return (float)((v & mask) >> _i) / 255.0f;
	}
	float getR() const                                                       { return get(3); }
	float getG() const                                                       { return get(2); }
	float getB() const                                                       { return get(1); }
	float getA() const                                                       { return get(0); }
};

struct VertexData
{
	Vec4   m_positionSize; // xyz = position, w = size
	Color  m_color;        // rgba8 (MSB = r)
	
	VertexData() {}
	VertexData(const Vec3& _position, float _size, Color _color): m_positionSize(_position, _size), m_color(_color) {}
};

enum DrawPrimitiveType
{
 // determines the order in which unsorted primitives are drawn
	DrawPrimitive_Triangles,
	DrawPrimitive_Lines,
	DrawPrimitive_Points,

	DrawPrimitive_Count
};
const int DrawPrimitiveSize[DrawPrimitive_Count] = 
{
 // vertices per draw primitive type
	3, //DrawPrimitive_Triangles,
	2, //DrawPrimitive_Lines,
	1  //DrawPrimitive_Points,
};

struct DrawList
{
	DrawPrimitiveType m_primType;
	const VertexData* m_vertexData;
	U32               m_vertexCount;
};
typedef void (DrawPrimitivesCallback)(const DrawList& _drawList);

enum Key
{
	Mouse_Left,
	Key_T,
	Key_R,
	Key_S,

	Key_Count,

 // the following map keys -> 'action' states which may be more intuitive, especially for VR
	Action_Select           = Mouse_Left,
	Action_GizmoTranslation = Key_T,
	Action_GizmoRotation    = Key_R,
	Action_GizmoScale       = Key_S
};
struct AppData
{
	bool  m_keyDown[Key_Count];  // Application-provided key states.

	Vec3  m_cursorRayOrigin;     // World space cursor ray origin.
	Vec3  m_cursorRayDirection;  // World space cursor ray direction.
	Vec3  m_worldUp;             // World space 'up' vector.
	Vec3  m_viewOrigin;          // World space render origin (camera position).
	Vec2  m_viewportSize;        // Viewport size (pixels).
	float m_tanHalfFov;          // tan(fov/2); fov = vertical field of view of the current projection.
	float m_deltaTime;           // Time since previous frame (seconds).
	void* m_userData;            // App-specific data (useful for passing app context to drawPrimitives).

	DrawPrimitivesCallback* drawCallback;
};

// Minimal vector.
template <typename T>
class Vector
{
	T*   m_data;
	U32  m_size;
	U32  m_capacity;

public:
	Vector(): m_size(0), m_capacity(0), m_data(0) {}
	~Vector();

	T&       operator[](U32 _i)                   { IM3D_ASSERT(_i < m_size); return m_data[_i]; }
	const T& operator[](U32 _i) const             { IM3D_ASSERT(_i < m_size); return m_data[_i]; }
	T*       data()                               { return m_data; }
	const T* data() const                         { return m_data; }

	void     push_back(T _v)                      { if (m_size == m_capacity) { reserve(m_capacity + m_capacity / 2); } m_data[m_size++] = _v;}
	void     pop_back()                           { IM3D_ASSERT(m_size > 0); --m_size; }

	T*       begin()                              { return m_data; }
	const T* begin() const                        { return m_data; }
	T*       end()                                { return m_data + m_size; }
	const T* end() const                          { return m_data + m_size; }
	T&       front()                              { IM3D_ASSERT(m_size > 0); return m_data[0]; }
	const T& front() const                        { IM3D_ASSERT(m_size > 0); return m_data[0]; }
	T&       back()                               { IM3D_ASSERT(m_size > 0); return m_data[m_size - 1]; }
	const T& back() const                         { IM3D_ASSERT(m_size > 0); return m_data[m_size - 1]; }

	U32      size() const                         { return m_size; }
	U32      capacity() const                     { return m_capacity; }
	bool     empty() const                        { return m_size == 0; }

	void     clear()                              { m_size = 0; }
	void     reserve(U32 _capacity);
	void     resize(U32 _size, const T& _val);

	template <typename T>
	friend void swap(Vector<T>& _a_, Vector<T>& _b_);
};

enum PrimitiveMode
{
	PrimitiveMode_None,
	PrimitiveMode_Points,
	PrimitiveMode_Lines,
	PrimitiveMode_LineStrip,
	PrimitiveMode_LineLoop,
	PrimitiveMode_Triangles,
	PrimitiveMode_TriangleStrip
};
enum GizmoMode
{
	GizmoMode_Translation,
	GizmoMode_Rotation,
	GizmoMode_Scale
};

// Context stores all relevant state - main interface affects the context currently bound via SetCurrentContext().
class Context
{
public:
	void        begin(PrimitiveMode _mode);
	void        end();
	void        vertex(const Vec3& _position, float _size, Color _color);
	void        vertex(const Vec3& _position )   { vertex(_position, getSize(), getColor()); }

	void        reset();
	void        draw();


	void        pushColor(Color _color)          { m_colorStack.push_back(_color); }
	void        popColor()                       { m_colorStack.pop_back();        }
	void        setColor(Color _color)           { m_colorStack.back() = _color;   }
	Color       getColor() const                 { return m_colorStack.back();     }

	void        pushAlpha(float _alpha)          { m_alphaStack.push_back(_alpha); }
	void        popAlpha()                       { m_alphaStack.pop_back();        }
	void        setAlpha(float _alpha)           { m_alphaStack.back() = _alpha;   }
	float       getAlpha() const                 { return m_alphaStack.back();     }

	void        pushSize(float _size)            { m_sizeStack.push_back(_size);   }
	void        popSize()                        { m_sizeStack.pop_back();         }
	void        setSize(float _size)             { m_sizeStack.back() = _size;     }
	float       getSize() const                  { return m_sizeStack.back();      }

	void        pushEnableSorting(bool _enable);
	void        popEnableSorting();
	void        setEnableSorting(bool _enable);
	bool        getEnableSorting() const         { return m_enableSortingStack.back(); }

	void        pushMatrix(const Mat4& _mat4)    { m_matrixStack.push_back(_mat4); }
	void        popMatrix()                      { m_matrixStack.pop_back();       }
	void        setMatrix(const Mat4& _mat4)     { m_matrixStack.back() = _mat4;   }
	const Mat4& getMatrix() const                { return m_matrixStack.back();    }

	void        pushId(Id _id)                   { m_idStack.push_back(_id); }
	void        popId()                          { m_idStack.pop_back();     }
	void        setId(Id _id)                    { m_idStack.back() = _id;   }
	Id          getId() const                    { return m_idStack.back();  }
	Id          getActiveId() const              { return m_activeId;        }
	Id          getHotId() const                 { return m_hotId;           }
	
	AppData&    getAppData()                     { return m_appData; }

	Context();
	~Context();

 // low-level interface for app-defined gizmos, may be unstable

	// Convert pixels -> world space size based on distance between _position and view origin.
	float pixelsToWorldSize(const Vec3& _position, float _pixels);

	// Translation gizmo for an arbitrary axis.
	bool gizmoAxisTranslation(Id _id, const Vec3& _drawAt, Vec3* _out_, const Vec3& _axis, Color _color, float _worldHeight, float _worldSize);
	// Translation gizmo for an arbitrary plane.
	bool gizmoPlaneTranslation(Id _id, const Vec3& _drawAt, Vec3* _out_, const Vec3& _normal, Color _color, float _worldSize);
	bool gizmoAxisScale(Id _id, const Vec3& _drawAt, float* _out_, const Vec3& _axis, Color _color, float _worldHeight, float _worldSize);
	bool gizmoAxisAngle(Id _id, const Vec3& _drawAt, const Vec3& _axis, float* _out_, Color _color, float _worldRadius, float _worldSize);
	
	// Make _id hot if _depth < m_hotDepth && _intersects.
	bool makeHot(Id _id, float _depth, bool _intersects);
	// Reset the acive/hot ids and the hot depth.
	void resetId();

	// Interpret key state.
	bool isKeyDown(Key _key) const     { return m_keyDownCurr[_key]; }
	bool wasKeyPressed(Key _key) const { return m_keyDownCurr[_key] && !m_keyDownPrev[_key]; }

	// gizmo state
	GizmoMode          m_gizmoMode;                // Global mode selection for gizmos.
	Id                 m_activeId;                 // Currently active gizmo. If set, this is the same as m_hotId.
	Id                 m_hotId;
	float              m_hotDepth;                 // Depth of the current hot gizmo, for handling occlusion.
	Vec3               m_gizmoStateVec3;           // Stored state for the active gizmo.
	Mat3               m_gizmoStateMat3;           //               "
	float              m_gizmoStateFloat;          //               "
	float              m_gizmoHeightPixels;        // Height/radius of gizmos.
	float              m_gizmoSizePixels;          // Thickness of gizmo lines.


 // stats/debugging	

	// Return the total number of primitives (sorted + unsorted) of the given _type.
	U32 getPrimitiveCount(DrawPrimitiveType _type) const; 

private:
 // state stacks
	Vector<Color>      m_colorStack;
	Vector<float>      m_alphaStack;
	Vector<float>      m_sizeStack;
	Vector<bool>       m_enableSortingStack;
	Vector<Mat4>       m_matrixStack;
	Vector<Id>         m_idStack;

 // primitive data: [0] unsorted, [1] sorted
	Vector<VertexData> m_vertexData[DrawPrimitive_Count][2];
	Vector<DrawList>   m_sortedDrawLists;
	bool               m_sortCalled;               // Prevent sorting during every call to draw().
	bool               m_drawCalled;               // For assert if primitives are pushed after draw() was called.

 // primitive state
	PrimitiveMode      m_primMode;   
	int                m_primList;                 // 1 if sorting enabled, else 0.
	U32                m_firstVertThisPrim;        // Index of the first vertex pushed during this primitive.
	U32                m_vertCountThisPrim;        // # calls to vertex() since the last call to begin().

 // app data
	AppData            m_appData;
	bool               m_keyDownCurr[Key_Count];   // Key state captured during reset().
	bool               m_keyDownPrev[Key_Count];   // Key state from previous frame.


	// Sort primitive data.
	void sort();

};

namespace internal {
	extern Context* g_CurrentContext;
}

inline Context& GetContext()                                                 { return *internal::g_CurrentContext; }
inline void     SetContext(Context& _ctx)                                    { internal::g_CurrentContext = &_ctx; }
inline AppData& GetAppData()                                                 { return GetContext().getAppData();   }
inline void     NewFrame()                                                   { GetContext().reset();               }
inline void     Draw()                                                       { GetContext().draw();                }

inline void  BeginPoints()                                                   { GetContext().begin(PrimitiveMode_Points);        }
inline void  BeginLines()                                                    { GetContext().begin(PrimitiveMode_Lines);         }
inline void  BeginLineLoop()                                                 { GetContext().begin(PrimitiveMode_LineLoop);      }
inline void  BeginLineStrip()                                                { GetContext().begin(PrimitiveMode_LineStrip);     }
inline void  BeginTriangles()                                                { GetContext().begin(PrimitiveMode_Triangles);     }
inline void  BeginTriangleStrip()                                            { GetContext().begin(PrimitiveMode_TriangleStrip); }
inline void  End()                                                           { GetContext().end(); }

inline void  Vertex(const Vec3& _position)                                   { GetContext().vertex(_position, GetContext().getSize(), GetContext().getColor()); }
inline void  Vertex(const Vec3& _position, Color _color)                     { GetContext().vertex(_position, GetContext().getSize(), _color); }
inline void  Vertex(const Vec3& _position, float _size)                      { GetContext().vertex(_position, _size, GetContext().getColor()); }
inline void  Vertex(const Vec3& _position, float _size, Color _color)        { GetContext().vertex(_position, _size, _color); }
inline void  Vertex(float _x, float _y, float _z)                            { Vertex(Vec3(_x, _y, _z)); }
inline void  Vertex(float _x, float _y, float _z, Color _color)              { Vertex(Vec3(_x, _y, _z), _color); }
inline void  Vertex(float _x, float _y, float _z, float _size)               { Vertex(Vec3(_x, _y, _z), _size); }
inline void  Vertex(float _x, float _y, float _z, float _size, Color _color) { Vertex(Vec3(_x, _y, _z), _size, _color); }

inline void  PushDrawState()                                                 { Context& ctx = GetContext(); ctx.pushColor(ctx.getColor()); ctx.pushAlpha(ctx.getAlpha()); ctx.pushSize(ctx.getSize()); ctx.pushEnableSorting(ctx.getEnableSorting()); }
inline void  PopDrawState()                                                  { Context& ctx = GetContext(); ctx.popColor(); ctx.popAlpha(); ctx.popSize(); ctx.popEnableSorting(); }

inline void  PushColor()                                                     { GetContext().pushColor(GetContext().getColor()); }
inline void  PushColor(Color _color)                                         { GetContext().pushColor(_color);                  }
inline void  PopColor()                                                      { GetContext().popColor();                         }
inline void  SetColor(Color _color)                                          { GetContext().setColor(_color);                   }
inline void  SetColor(float _r, float _g, float _b, float _a)                { GetContext().setColor(Color(_r, _g, _b, _a));    }
inline Color GetColor()                                                      { return GetContext().getColor();                  }

inline void  PushAlpha()                                                     { GetContext().pushAlpha(GetContext().getAlpha()); }
inline void  PushAlpha(float _alpha)                                         { GetContext().pushAlpha(_alpha);                  }
inline void  PopAlpha()                                                      { GetContext().popAlpha();                         }
inline void  SetAlpha(float _alpha)                                          { GetContext().setAlpha(_alpha);                   }
inline float GetAlpha()                                                      { return GetContext().getAlpha();                  }

inline void  PushSize()                                                      { GetContext().pushSize(GetContext().getAlpha());  }
inline void  PushSize(float _size)                                           { GetContext().pushSize(_size);                    }
inline void  PopSize()                                                       { GetContext().popSize();                          }
inline void  SetSize(float _size)                                            { GetContext().setSize(_size);                     }
inline float GetSize()                                                       { return GetContext().getSize();                   }

inline void  PushEnableSorting()                                             { GetContext().pushEnableSorting(GetContext().getEnableSorting()); }
inline void  PushEnableSorting(bool _enable)                                 { GetContext().pushEnableSorting(_enable); }
inline void  PopEnableSorting()                                              { GetContext().popEnableSorting();         }
inline void  EnableSorting(bool _enable)                                     { GetContext().setEnableSorting(_enable);  }

inline void  PushMatrix()                                                    { GetContext().pushMatrix(GetContext().getMatrix()); }
inline void  PushMatrix(const Mat4& _mat4)                                   { GetContext().pushMatrix(_mat4);                    }
inline void  PopMatrix()                                                     { GetContext().popMatrix();                          }
inline void  SetMatrix(const Mat4& _mat4)                                    { GetContext().setMatrix(_mat4);                     }
inline void  SetIdentity()                                                   { GetContext().setMatrix(Mat4(1.0f));                }

inline void  PushId()                                                        { GetContext().pushId(GetContext().getId()); }
inline void  PushId(Id _id)                                                  { GetContext().pushId(_id);                  }
inline void  PopId()                                                         { GetContext().popId();                      }
inline Id    GetId()                                                         { return GetContext().getId();               }
inline Id    GetActiveId()                                                   { return GetContext().getActiveId();         }

} // namespac Im3d

#endif // im3d_h
