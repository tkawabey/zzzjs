#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/ext/point.h"
#include "js/common/conf.h"
#include "js/common/defs.h"
#include "js/common/jsutil.h"
#include <wx/string.h>

using namespace zzzJs;
using namespace ext;

// プロパティー名
#define PROP_NM_X				"x"
#define PROP_NM_Y				"y"



/***
 * <file>point</file>
 * <module>ext</module>
 * <class name="wxPoint">
 *  A wxPoint is a useful data structure for graphics operations.
 *  It simply contains integer x and y members.
 * </class>
 */
ZZZJS_INIT_CLASS(Point, "Point", 0)

/***
 * <properties>
 *  <property name="x" type=WXJS_TYPE_NUMBER>
 *   The x-coordinate.
 *  </property>
 *  <property name="y" type=WXJS_TYPE_NUMBER>
 *   The y-coordinate.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Point)
  ZZZJS_PROPERTY(P_X, PROP_NM_X)
  ZZZJS_PROPERTY(P_Y, PROP_NM_Y)
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_GET_PROP(wxPoint, Point)
{
    switch (id) 
	{
	case P_X:
		ToJSVal(cx, vp, p->x);
		break;
	case P_Y:
		ToJSVal(cx, vp, p->y);
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP

ZZZJS_BEGIN_SET_PROP(wxPoint, Point)
{
    switch (id) 
	{
	case P_X:
		FromJS(cx, vp, p->x);
		break;
	case P_Y:
		FromJS(cx, vp, p->y);
		break;
    }
    return true;
}
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER default="wxDefaultPosition.x">
 *    The X-coordinate
 *   </arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER default="0">
 *    The Y-coordinate.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a new wxPoint. When no arguments are given then wxPoint gets the same value
 *   as wxDefaultPosition.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxPoint, Point)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	if ( argv.length()  == 0 )
	{
		return new wxPoint();
	}
	else
	{
		int x = 0;
		int y = 0;
		if ( argc > 0 )
		{
			FromJS(cx, argv[0], x);
		}
		
		if ( argc > 1 )
		{
			FromJS(cx, argv[1], y);
		}
		return new wxPoint(x, y);
	}
}
ZZZJS_END_CONSTRUCTOR
	
	
ZZZJS_BEGIN_O2I(wxPoint, Point)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_X), &v) == JS_TRUE )  
	{
		int width = 0,  height = 0;

		// x
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, obj, PROP_NM_X, WXJS_TYPE_NUMBER);
		// y
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_Y, WXJS_TYPE_NUMBER);

		bAllocation = true;
		return new wxPoint(width, height);
	}
	
	return NULL;
}
ZZZJS_END_O2I