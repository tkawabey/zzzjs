/*
 * wxJavaScript - gridszr.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://wxjs.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: gridszr.cpp 733 2007-06-05 21:17:25Z fbraem $
 */
// gridszr.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 




#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/gridszr.h"
#include "js/gui/misc/size.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// for object
#define PROP_NM_COLS			"cols"
#define PROP_NM_ROWS			"rows"
#define PROP_NM_VGAP			"vgap"
#define PROP_NM_HGAP			"hgap"
#define PROP_NM_GAP				"gap"




/***
 * <file>misc/gridszr</file>
 * <module>gui</module>
 * <class name="wxGridSizer" prototype="@wxSizer">
 *  A grid sizer is a sizer which lays out its children in a two-dimensional table with 
 *  all table fields having the same size, i.e. the width of each field is the width of 
 *  the widest child, the height of each field is the height of the tallest child.
 * </class>
 */
ZZZJS_INIT_CLASS(GridSizer, "GridSizer", 1)

/***
 * <ctor>
 *  <function>
 *   <arg name="Rows" type=ZZZJS_TYPE_NUMBER>
 *    The number of rows.
 *   </arg>
 *   <arg name="Cols" type=ZZZJS_TYPE_NUMBER>
 *    The number of columns.
 *   </arg>
 *   <arg name="Vgap" type=ZZZJS_TYPE_NUMBER>
 *    The space between the columns
 *   </arg>
 *   <arg name="Hgap" type=ZZZJS_TYPE_NUMBER>
 *    The space between the rows
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Cols" type=ZZZJS_TYPE_NUMBER>
 *    The number of columns.
 *   </arg>
 *   <arg name="Vgap" type=ZZZJS_TYPE_NUMBER>
 *    The space between the columns
 *   </arg>
 *   <arg name="Hgap" type=ZZZJS_TYPE_NUMBER>
 *    The space between the rows
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxGridSizer object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxGridSizer, GridSizer)
{
	/*
 	wxGridSizer (int cols, int vgap, int hgap)
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int cols, const wxSize &gap=wxSize(0, 0))
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int rows, int cols, int vgap, int hgap)
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int rows, int cols, const wxSize &gap)
 	wxGridSizer constructors.
	*/
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxGridSizer *p = NULL;
	
	int argIndex = 0;
	int cols = 0;
	int rows = 0;
	int vgap = 0;
	int hgap = 0;
	JSObject* pObjSize; // <- Size


		
	ZZZJS_CHECK_ARG_COUNT(1, 4)

	if ( JS_ConvertArguments(cx, argc, vp, "iiii", &rows, &cols, &vgap,
							 &hgap) == JS_TRUE )
	{
		// wxGridSizer (int rows, int cols, int vgap, int hgap)
		p = new wxGridSizer(rows, cols, vgap, hgap);
	} else	
	if ( JS_ConvertArguments(cx, argc, vp, "iii", &cols, &vgap, &hgap) == JS_TRUE )
	{
		// wxGridSizer (int cols, int vgap, int hgap)
		p = new wxGridSizer(cols, vgap, hgap);
	} else	
	if ( JS_ConvertArguments(cx, argc, vp, "iio", &rows, &cols, &pObjSize) == JS_TRUE )
	{
		// wxGridSizer (int rows, int cols, const wxSize &gap)
		
		zzzJsPtr<wxSize> apSize;

		if( ZZZJS_PROP_GET_AP(apSize, Size, pObjSize) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, Size::getClassName());
			return NULL;
		}
		p = new wxGridSizer(cols, vgap, *(apSize.get()));
	} else	
	if ( JS_ConvertArguments(cx, argc, vp, "i/o", &cols, &pObjSize) == JS_TRUE )
	{
		// wxGridSizer (int cols, const wxSize &gap=wxSize(0, 0))
		
		zzzJsPtr<wxSize> apSize;

		if( pObjSize != NULL ) {
			if( ZZZJS_PROP_GET_AP(apSize, Size, pObjSize) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, Size::getClassName());
				return NULL;
			}	
		}
		if( apSize.get() == NULL ) {
			p = new wxGridSizer(cols);
		} else {
			p = new wxGridSizer(cols, *(apSize.get()));
		}
	}



	if ( p != NULL )
	{
		p->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
	}

	return p;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxGridSizer, GridSizer)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
 	wxGridSizer (int cols, int vgap, int hgap)
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int cols, const wxSize &gap=wxSize(0, 0))
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int rows, int cols, int vgap, int hgap)
 	wxGridSizer constructors. More...
 
 	wxGridSizer (int rows, int cols, const wxSize &gap)
 	wxGridSizer constructors.
	*/

	// cols ÇÕïKê{
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLS), &v) == JS_FALSE )  
	{
		return NULL;
	}
	int cols = 0;
	ZZZJS_PROP_FROMJS_CHK_AND_ERROR(cols, obj, PROP_NM_COLS, WXJS_TYPE_NUMBER);

	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_ROWS), &v) == JS_TRUE)  
	{
		/*
		wxGridSizer     (int rows, int cols, int vgap, int hgap)
		wxGridSizer     (int rows, int cols, const wxSize &gap)
		*/	

		int rows = 0;
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(rows, obj, PROP_NM_ROWS, WXJS_TYPE_NUMBER);

		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_GAP), &v) == JS_TRUE)  
		{
			// wxGridSizer     (int rows, int cols, const wxSize &gap)

			zzzJsPtr<wxSize> apSize;
			ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_GAP);


			bAllocation = true;
			return new wxGridSizer(rows, cols, *(apSize.get()));
		}
		else
		{
			// wxGridSizer     (int rows, int cols, int vgap, int hgap)
			int vgap = 0;
			int hgap = 0;
			
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(vgap, obj, PROP_NM_VGAP, WXJS_TYPE_NUMBER);		
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(hgap, obj, PROP_NM_HGAP, WXJS_TYPE_NUMBER);
			bAllocation = true;
			return new wxGridSizer(rows, cols, vgap, hgap);
		}
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_GAP), &v) == JS_TRUE)  
	{
		// wxGridSizer (int cols, const wxSize &gap=wxSize(0, 0))

		zzzJsPtr<wxSize> apSize;
		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_GAP);
		
		bAllocation = true;
		return new wxGridSizer(cols, *(apSize.get()));
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_HGAP), &v) == JS_TRUE)  
	{
		// wxGridSizer (int cols, int vgap, int hgap)
		
		int vgap = 0;
		int hgap = 0;
			
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(vgap, obj, PROP_NM_VGAP, WXJS_TYPE_NUMBER);		
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(hgap, obj, PROP_NM_HGAP, WXJS_TYPE_NUMBER);
		bAllocation = true;
		return new wxGridSizer(cols, vgap, hgap);
	}
	

	// wxGridSizer (int cols, const wxSize &gap=wxSize(0, 0))ÇÃÅAgapè»ó™î≈	
	bAllocation = true;
	return new wxGridSizer(cols);
}
ZZZJS_END_O2I