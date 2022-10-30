/*
 * wxJavaScript - flexgrid.cpp
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
 * $Id: flexgrid.cpp 733 2007-06-05 21:17:25Z fbraem $
 */
// flexgrid.cpp
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
#include "js/common/clntdata.h"
#include "js/common/jsutil.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/flexgrid.h"
#include "js/gui/misc/size.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/flexgrid</file>
 * <module>gui</module>
 * <class name="wxFlexGridSizer" prototype="@wxGridSizer">
 *  A flex grid sizer is a sizer which lays out its children in a two-dimensional
 *  table with all table fields in one row having the same height and all fields 
 *  in one column having the same width.
 * </class>
 */
ZZZJS_INIT_CLASS(FlexGridSizer, "FlexGridSizer", 1)
	

// プロパティー名
#define PROP_NM_FlexibleDirection		"flexibleDirection"
#define PROP_NM_NonFlexibleGrowMode		"nonFlexibleGrowMode"
#define PROP_NM_RowHeights				"rowHeights"
#define PROP_NM_ColWidths				"colWidths"
// for object
#define PROP_NM_COLS			"cols"
#define PROP_NM_ROWS			"rows"
#define PROP_NM_VGAP			"vgap"
#define PROP_NM_HGAP			"hgap"
#define PROP_NM_GAP				"gap"
// for Arguments
#define PROP_NM_IDX			"idx"
#define PROP_NM_PROPORTION	"proportion"




ZZZJS_BEGIN_PROPERTY_MAP(FlexGridSizer)
  ZZZJS_PROPERTY(P_FlexibleDirection, PROP_NM_FlexibleDirection)
  ZZZJS_PROPERTY(P_NonFlexibleGrowMode, PROP_NM_NonFlexibleGrowMode)
  ZZZJS_READONLY_PROPERTY(P_RowHeights, PROP_NM_RowHeights)
  ZZZJS_READONLY_PROPERTY(P_ColWidths, PROP_NM_ColWidths)
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_METHOD_MAP(FlexGridSizer)
  ZZZJS_METHOD("addGrowableCol", addGrowableCol, 1)
  ZZZJS_METHOD("addGrowableRow", addGrowableRow, 1)
  ZZZJS_METHOD("removeGrowableCol", removeGrowableCol, 1)
  ZZZJS_METHOD("removeGrowableRow", removeGrowableRow, 1)
  ZZZJS_METHOD("isColGrowable", isColGrowable, 1)
  ZZZJS_METHOD("isRowGrowable", isRowGrowable, 1)
  ZZZJS_METHOD("recalcSizes", recalcSizes, 0)
  ZZZJS_METHOD("calcMin", calcMin, 0)
ZZZJS_END_METHOD_MAP()

ZZZJS_BEGIN_GET_PROP(wxFlexGridSizer, FlexGridSizer)
{
    switch(id) 
	{
	case P_FlexibleDirection:
		ToJSVal(cx, vp, p->GetFlexibleDirection());
		break;
	case P_NonFlexibleGrowMode:
		ToJSVal<int>(cx, vp, p->GetNonFlexibleGrowMode());
		break;
	case P_RowHeights:
		ToJSVal(cx, vp, p->GetRowHeights());
		break;
	case P_ColWidths:
		ToJSVal(cx, vp, p->GetColWidths());
		break;
    }
    return true;
}
ZZZJS_END_GET_PROP
ZZZJS_BEGIN_SET_PROP(wxFlexGridSizer, FlexGridSizer)
{
    switch(id) 
	{
	case P_FlexibleDirection:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetFlexibleDirection(value);
			break;
		}
	case P_NonFlexibleGrowMode:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetNonFlexibleGrowMode((wxFlexSizerGrowMode)value);
			break;
		}
    }
    return true;
}
ZZZJS_END_SET_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Rows">
 *    The number of rows.
 *   </arg>
 *   <arg name="Cols">
 *    The number of columns.
 *   </arg>
 *   <arg name="Vgap">
 *    The space between the columns
 *   </arg>
 *   <arg name="Hgap">
 *    The space between the rows
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Cols">
 *    The number of columns.
 *   </arg>
 *   <arg name="Vgap" type=WXJS_TYPE_NUMBER default="0">
 *    The space between the columns
 *   </arg>
 *   <arg name="Hgap" type=WXJS_TYPE_NUMBER default="0">  
 *    The space between the rows
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxFlexGridSizer object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxFlexGridSizer, FlexGridSizer)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxFlexGridSizer *p = NULL;

	int argIndex = 0;


	
	if( argv[argIndex].isNumber() == true ) 
	{
		int cols = 0;
		int rows = 0;
		int vgap = 0;
		int hgap = 0;
		/*
 		wxFlexGridSizer (int cols, int vgap, int hgap)
 		wxFlexGridSizer (int cols, const wxSize &gap=wxSize(0, 0))
 		wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
 		wxFlexGridSizer (int rows, int cols, const wxSize &gap)
		*/
		ZZZJS_CHECK_ARG_COUNT(1, 4);

		if( argv[argIndex+1].isNumber() == true ) 
		{
			/*
 			wxFlexGridSizer (int cols, int vgap, int hgap)
 			wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
 			wxFlexGridSizer (int rows, int cols, const wxSize &gap)
			*/
			
			ZZZJS_CHECK_ARG_COUNT(3, 4);
			if( argv[argIndex+2].isNumber() == false ) 
			{
				/*
 				wxFlexGridSizer (int cols, int vgap, int hgap)
 				wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
				*/

				if( argc == 4 ) {
 					// wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(rows, WXJS_TYPE_NUMBER);
					argIndex++;
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cols, WXJS_TYPE_NUMBER);
					argIndex++;
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(vgap, WXJS_TYPE_NUMBER);
					argIndex++;
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(hgap, WXJS_TYPE_NUMBER);
					argIndex++;

					
					
					p = new wxFlexGridSizer(rows, cols, vgap, hgap);
				} else {
					// wxFlexGridSizer (int cols, int vgap, int hgap)
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cols, WXJS_TYPE_NUMBER);
					argIndex++;
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(vgap, WXJS_TYPE_NUMBER);
					argIndex++;
					ZZZJS_ARG_FROMJS_CHK_AND_ERROR(hgap, WXJS_TYPE_NUMBER);
					argIndex++;
					
					p = new wxFlexGridSizer(cols, vgap, hgap);
				}
			} else {
				ZZZJS_CHECK_ARG_COUNT(3, 3);
				// wxFlexGridSizer (int rows, int cols, const wxSize &gap)
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(rows, WXJS_TYPE_NUMBER);
				argIndex++;
				ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cols, WXJS_TYPE_NUMBER);
				argIndex++;
				zzzJsPtr<wxSize> apSize;
				ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
				argIndex++;
				p = new wxFlexGridSizer(rows, cols, *(apSize.get()));
			}
		} 
		else 
		{
			// wxFlexGridSizer (int cols, const wxSize &gap=wxSize(0, 0))

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(cols, WXJS_TYPE_NUMBER);
			argIndex++;
			if( argc == 1 ) 
			{
				p = new wxFlexGridSizer(cols);
			}
			else
			{
				zzzJsPtr<wxSize> apSize;
				ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
				argIndex++;
				p = new wxFlexGridSizer(cols, *(apSize.get()));
			}
		}

	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
		} while( 0 );
	}


	if( p == NULL ) {
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return NULL;
	} 


	p->SetClientObject(new JavaScriptClientData(cx, obj, false, true));


	return p;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_DESTRUCTOR(wxFlexGridSizer, FlexGridSizer)
{

}
ZZZJS_END_DESTRUCTOR

	
ZZZJS_BEGIN_O2I(wxFlexGridSizer, FlexGridSizer)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	/*
 	wxFlexGridSizer (int cols, int vgap, int hgap)
 	wxFlexGridSizer (int cols, const wxSize &gap=wxSize(0, 0))
 	wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
 	wxFlexGridSizer (int rows, int cols, const wxSize &gap)
	*/	

	// cols は必須
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_COLS), &v) == JS_FALSE )  
	{
		return NULL;
	}


	int cols = 0;
	ZZZJS_PROP_FROMJS_CHK_AND_ERROR(cols, obj, PROP_NM_COLS, WXJS_TYPE_NUMBER);


	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_ROWS), &v) == JS_TRUE)  
	{
		/*
 		wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
 		wxFlexGridSizer (int rows, int cols, const wxSize &gap)
		*/	

		int rows = 0;
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(rows, obj, PROP_NM_ROWS, WXJS_TYPE_NUMBER);

		if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_GAP), &v) == JS_TRUE)  
		{
			// wxFlexGridSizer (int rows, int cols, const wxSize &gap)

			zzzJsPtr<wxSize> apSize;
			ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_GAP);


			bAllocation = true;
			return new wxFlexGridSizer(rows, cols, *(apSize.get()));
		}
		else
		{
			// wxFlexGridSizer (int rows, int cols, int vgap, int hgap)
			int vgap = 0;
			int hgap = 0;
			
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(vgap, obj, PROP_NM_VGAP, WXJS_TYPE_NUMBER);		
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(hgap, obj, PROP_NM_HGAP, WXJS_TYPE_NUMBER);
			bAllocation = true;
			return new wxFlexGridSizer(rows, cols, vgap, hgap);
		}
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_GAP), &v) == JS_TRUE)  
	{
		// wxFlexGridSizer (int cols, const wxSize &gap=wxSize(0, 0))

		zzzJsPtr<wxSize> apSize;
		ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, PROP_NM_GAP);
		
		bAllocation = true;
		return new wxFlexGridSizer(cols, *(apSize.get()));
	}
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_HGAP), &v) == JS_TRUE)  
	{
		// wxFlexGridSizer (int cols, int vgap, int hgap)
		
		int vgap = 0;
		int hgap = 0;
			
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(vgap, obj, PROP_NM_VGAP, WXJS_TYPE_NUMBER);		
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(hgap, obj, PROP_NM_HGAP, WXJS_TYPE_NUMBER);
		bAllocation = true;
		return new wxFlexGridSizer(cols, vgap, hgap);
	}
	

	// wxFlexGridSizer (int cols, const wxSize &gap=wxSize(0, 0))の、gap省略版	
	bAllocation = true;
	return new wxFlexGridSizer(cols);
}
ZZZJS_END_O2I

ZZZJS_BEGIN_METHOD(FlexGridSizer, addGrowableCol )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// void  AddGrowableCol (size_t idx, int proportion=0) 
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;
		int proportion=0;

		ZZZJS_CHECK_ARG_COUNT(1, 2);

		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;


		argIndex = argc - 1;
		switch( argc ) {
		case 2:
			// 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(proportion, PROP_NM_PROPORTION);
			argIndex--;
		}

		p->AddGrowableCol(idx, proportion);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
			, proportion:Number( option. default=0 )
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			int proportion=0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)
			// proportion
			ZZZJS_PROP_FROMJS_IF_EXIST(proportion, pObj, PROP_NM_PROPORTION, WXJS_TYPE_NUMBER)

			p->AddGrowableCol(idx, proportion);
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

ZZZJS_BEGIN_METHOD(FlexGridSizer, addGrowableRow )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// void  AddGrowableCol (size_t idx, int proportion=0) 
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;
		int proportion=0;

		ZZZJS_CHECK_ARG_COUNT(1, 2);

		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;


		argIndex = argc - 1;
		switch( argc ) {
		case 2:
			// 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(proportion, PROP_NM_PROPORTION);
			argIndex--;
		}

		p->AddGrowableRow(idx, proportion);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
			, proportion:Number( option. default=0 )
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			int proportion=0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)
			// proportion
			ZZZJS_PROP_FROMJS_IF_EXIST(proportion, pObj, PROP_NM_PROPORTION, WXJS_TYPE_NUMBER)

			p->AddGrowableRow(idx, proportion);
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(FlexGridSizer, removeGrowableCol )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// void 	RemoveGrowableCol (size_t idx)
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;


		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;
		
		p->RemoveGrowableCol(idx);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)

			p->RemoveGrowableCol(idx);
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
	
ZZZJS_BEGIN_METHOD(FlexGridSizer, removeGrowableRow )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// void 	RemoveGrowableRow (size_t idx)
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;


		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;
		
		p->RemoveGrowableRow(idx);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)

			p->RemoveGrowableRow(idx);
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(FlexGridSizer, isColGrowable )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// bool 	IsColGrowable (size_t idx)
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;


		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;
		
		vp->setBoolean(p->IsColGrowable(idx));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)

			vp->setBoolean(p->IsColGrowable(idx));
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

	
ZZZJS_BEGIN_METHOD(FlexGridSizer, isRowGrowable )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	// bool 	IsRowGrowable (size_t idx)
	
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) {
		int idx = 0;


		// 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, PROP_NM_IDX);
		argIndex++;
		
		vp->setBoolean(p->IsRowGrowable(idx));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Objectの場合
		/*
		{
			  idx:Number
		}
		*/

		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int idx = 0;
			// idx
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(idx, pObj, PROP_NM_IDX, WXJS_TYPE_NUMBER)

			vp->setBoolean(p->IsRowGrowable(idx));
			return JS_TRUE;
		} while( 0 );
	}

	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD
	

	
ZZZJS_BEGIN_METHOD(FlexGridSizer, recalcSizes )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);
	p->RecalcSizes();
	return JS_TRUE;
}
ZZZJS_END_METHOD
	

	
ZZZJS_BEGIN_METHOD(FlexGridSizer, calcMin )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxFlexGridSizer *p = GetPrivate(cx, obj);

	*vp = Size::CreateObject( cx, new wxSize( p->CalcMin() ) );

	return JS_TRUE;
}
ZZZJS_END_METHOD







