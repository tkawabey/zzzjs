/*
 * wxJavaScript - imagelst.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id: imagelst.cpp 734 2007-06-06 20:09:13Z fbraem $
 */
// imagelst.cpp
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
#include "js/gui/misc/imagelst.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/size.h"
#include "js/gui/gdi/dc.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_WIDTH			"width"
#define PROP_NM_MASK			"mask"
#define PROP_NM_INITIAL_COUNT	"initialCount"
#define PROP_NM_INDEX			"index"
#define PROP_NM_SIZE			"size"
#define PROP_NM_BITMAP			"bitmap"
#define PROP_NM_ICON			"icon"
#define PROP_NM_MASK			"mask"
#define PROP_NM_INDEX			"index"
#define PROP_NM_DC				"dc"
#define PROP_NM_X				"x"
#define PROP_NM_Y				"y"
#define PROP_NM_POS				"pos"
#define PROP_NM_FLAGS			"flags"
#define PROP_NM_SOLID_BACKGROUND			"solidBackground"


ImageList::ImageList() : wxClientDataContainer()
{
}

/***
 * <file>control/imagelst</file>
 * <module>gui</module>
 * <class name="wxImageList">
 *  A wxImageList contains a list of images, which are stored in an unspecified form.
 *  Images can have masks for transparent drawing, and can be made from a variety of 
 *  sources including bitmaps and icons.
 *  <br /><br />
 *  wxImageList is used principally in conjunction with @wxTreeCtrl and 
 *  @wxListCtrl classes.
 * </class>
 */
ZZZJS_INIT_CLASS(ImageList, "ImageList", 2)

/***
 * <properties>
 *  <property name="imageCount" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Returns the number of the images.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(ImageList)
    ZZZJS_READONLY_PROPERTY(P_IMAGE_COUNT, "imageCount")
ZZZJS_END_PROPERTY_MAP()

//bool ImageList::GetProperty(wxImageList *p,
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(ImageList, ImageList)
    if ( id == P_IMAGE_COUNT )
        ToJSVal(cx, vp, p->GetImageCount());
    return true;
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Width" type=ZZZJS_TYPE_NUMBER>
 *    The width of the images in the list
 *   </arg>
 *   <arg name="Height" type=ZZZJS_TYPE_NUMBER>
 *    The height of the images in the list.
 *   </arg>
 *   <arg name="Mask" type="Boolean" default="true">
 *    When true (default) a mask is created for each image.
 *   </arg>
 *   <arg name="Count" type=ZZZJS_TYPE_NUMBER default="1">
 *    The size of the list.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxImageList object.
 *  </desc>
 * </ctor>
 */
//ImageList* ImageList::Construct(JSContext *cx,
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(ImageList, ImageList)
{
	//JSObject *obj = JS_THIS_OBJECT(cx, vp);
	/*JS::CallArgs argv = CallArgsFromVp(argc, vp);*/
  ImageList *p = new ImageList();



    SetPrivate(cx, obj, p);

    if ( argc > 0 )
    {
        jsval rval;
        if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
        {
          return NULL;
        }
    }

	return p;
}
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(ImageList)
    ZZZJS_METHOD("create", create, 2)
    ZZZJS_METHOD("add", add, 1)
    ZZZJS_METHOD("draw", draw, 4)
    ZZZJS_METHOD("getSize", getSize, 2)
    ZZZJS_METHOD("remove", remove, 1)
    ZZZJS_METHOD("removeAll", removeAll, 0)
    ZZZJS_METHOD("replace", replace, 2)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function>
 *   <arg name="Width" type=ZZZJS_TYPE_NUMBER>
 *    The width of the images in the list
 *   </arg>
 *   <arg name="Height" type=ZZZJS_TYPE_NUMBER>
 *    The height of the images in the list.
 *   </arg>
 *   <arg name="Mask" type="Boolean" default="true">
 *    When true (default) a mask is created for each image.
 *   </arg>
 *   <arg name="Count" type=ZZZJS_TYPE_NUMBER default="1">
 *    The size of the list.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates an image list. Width and Height specify the size of the images
 *   in the list (all the same). Mask specifies whether the images have masks or not.
 *   Count is the initial number of images to reserve.
 *  </desc>
 * </method>
 */
JSBool ImageList::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool ImageList::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    ImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	// bool 	Create (
	//		int width, 
	//		int height, 
	//		bool mask=true, 
	//		int initialCount=1)
	int argIndex = 0;

	if( argv[argIndex].isNumber() == true ) 
	{
		int width = 0, height = 0, initialCount = 1;
		bool mask = true;
		ZZZJS_CHECK_ARG_COUNT(2, 4)
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		// 1
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;


		argIndex = argc -1;
		switch( argc ) 
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(mask, WXJS_TYPE_BOOLEAN);
			argIndex--;
			break;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(initialCount, WXJS_TYPE_NUMBER);
			argIndex--;
			break;
		}

        p->Create(width, height, mask, initialCount);
        p->SetClientObject(new JavaScriptClientData(cx, obj, false, false));
        return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			zzzJsPtr<ImageList> apImageList;

			if( apImageList.set( 
				ImageList::getObject2Instance(cx, pObj, apImageList.bAllocation) ) == true 
			) {
				if( apImageList.bAllocation == true ) {
					delete p;
					SetPrivate(cx, obj, NULL);
					p = apImageList.release();
					SetPrivate(cx, obj, p);
				} else {
					// 引数に、ImageListのコピーは指定不可なので、ここはエラー。
				}
			}			
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}

ZZZJS_BEGIN_O2I(ImageList, ImageList)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	// bool 	Create (int width, int height, bool mask=true, int initialCount=1)
	/*
	{
			width:Number
		,	height:height
		,	mask:Boolean[Option. Default=true]
		,	initialCount[Option. Default=1]
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_HEIGHT), &v) == JS_TRUE )  
	{
		int width = 0, height = 0, initialCount = 1;
		bool mask = true;

		// width
		if( FromJS(cx, v, width) == false ) {
			ReportError_PropTypeError(cx, PROP_NM_WIDTH, WXJS_TYPE_NUMBER);
			return NULL;
		}
		// height
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)	
		// mask
		ZZZJS_PROP_FROMJS_IF_EXIST(mask, obj, PROP_NM_HEIGHT, WXJS_TYPE_BOOLEAN)
		// initialCount
		ZZZJS_PROP_FROMJS_IF_EXIST(initialCount, obj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)		
		

		bAllocation = true;
		pRet = new ImageList();
		pRet->Create(width, height, mask, initialCount );
        pRet->SetClientObject(new JavaScriptClientData(cx, obj, false, false));

		return pRet;
	}
	
	return NULL;
}
ZZZJS_END_O2I
	
/***
 * <method name="add">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Bitmap" type="@wxBitmap" />
 *   <arg name="Mask" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Bitmap" type="@wxBitmap" />
 *   <arg name="Colour" type="@wxColour" />
 *  </function>
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Icon" type="@wxIcon" />
 *  </function>
 *  <desc>
 *   Adds a new image using a bitmap and an optional mask bitmap
 *   or adds a new image using a bitmap and a mask colour
 *   or adds a new image using an icon.
 *   Returns the new zero-based index of the image.
 *  </desc>
 * </method>
 */
JSBool ImageList::add(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	/*
	int 	Add (const wxBitmap &bitmap, const wxBitmap &mask=wxNullBitmap)
 		Adds a new image or images using a bitmap and optional mask bitmap. More...
 
	int 	Add (const wxBitmap &bitmap, const wxColour &maskColour)
 		Adds a new image or images using a bitmap and mask colour. More...
 
	int 	Add (const wxIcon &icon)
 		Adds a new image using an icon.
	*/
	
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;
	zzzJsPtr<wxIcon>   apIcon;
	zzzJsPtr<wxColour>   apColour;
	zzzJsPtr<wxBitmap>   apMask;


	if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == true )
	{
		ZZZJS_CHECK_ARG_COUNT(1, 2)
		
		argIndex++;

		if( argc == 1 ) 
		{
			vp->setInt32(
				p->Add( *(apBitmap.get()) )
			);
			return JS_TRUE;
		}
		else
		{
			if( ZZZJS_ARG_GET_AP(apMask, Bitmap) == true )
			{
				vp->setInt32(
					p->Add( *(apBitmap.get()), *(apMask.get()) )
				);
				return JS_TRUE;
			}
			else
			if( ZZZJS_ARG_GET_AP(apColour, Colour) == true )
			{
				vp->setInt32(
					p->Add( *(apBitmap.get()), *(apColour.get()) )
				);
				return JS_TRUE;
			}
			else
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap or Colour" );
				return JS_FALSE;
			}
		}
	}
	else
	if( ZZZJS_ARG_GET_AP(apIcon, Icon) == true )
	{
		vp->setInt32(
			p->Add( *(apIcon.get()) )
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_BITMAP), &v) == JS_TRUE )  
			{
				/*
				{
					bitmap: Bitmap, 
					mask: Bitmap or Colour[Option. default is null.]
				}
				*/
				ZZZJS_PROP_AP_CHK_AND_ERROR(apBitmap, pObj, Bitmap, PROP_NM_BITMAP);


				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MASK), &v) == JS_TRUE )  
				{
					if( ZZZJS_PROP_GET_AP(apMask, Bitmap, v) == true )
					{
						vp->setInt32(
							p->Add( *(apBitmap.get()), *(apMask.get()) )
						);
						return JS_TRUE;
					} 
					else
					if( ZZZJS_PROP_GET_AP(apColour, Colour, v) == true )
					{
						vp->setInt32(
							p->Add( *(apBitmap.get()), *(apColour.get()) )
						);
						return JS_TRUE;

					}
				}
				else
				{
					vp->setInt32(
						p->Add( *(apBitmap.get()))
					);
					return JS_TRUE;
				}
			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_ICON), &v) == JS_TRUE )  
			{
				ZZZJS_PROP_AP_CHK_AND_ERROR(apIcon, pObj, Icon, PROP_NM_ICON);

				vp->setInt32(
					p->Add( *(apIcon.get()))
				);
				return JS_TRUE;
			}			
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

JSBool ImageList::draw(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual bool 	Draw (int index, wxDC &dc, int x, int y, int flags=wxIMAGELIST_DRAW_NORMAL, bool solidBackground=false)
 		Draws a specified image onto a device context. 
	*/
	
	int argIndex = 0;
	wxDC* pDC = NULL;
	int index = 0;
	int x = 0;
	int y = 0;
	int flags=wxIMAGELIST_DRAW_NORMAL;
	bool solidBackground=false;


	if( argv[argIndex].isNumber() )
	{
		ZZZJS_CHECK_ARG_COUNT(4, 6)

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
		argIndex++;
		if( (pDC = zzzJs::gui::gdi::DC::GetPrivate(cx, argv[argIndex], false)) != NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
			return JS_FALSE;
		}
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;

		argIndex = argc - 1;
		switch( argc )
		{
		case 6:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(solidBackground, WXJS_TYPE_BOOLEAN);
			argIndex--;
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flags, WXJS_TYPE_NUMBER);
			argIndex--;
		}


		vp->setBoolean( 
			p->Draw(index, *pDC, x, y, flags, solidBackground)
		);
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
			{
				index : Number
				dc : DC
				x : Number
				y : Number
				flags : Number[Option. Default=wx.IMAGELIST_DRAW_NORMAL]
				solidBackground : Boolean
			}
			*/
			
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
			{
				// index
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
				// dc
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_DC), &v) == JS_FALSE ) 
				{
					ReportError_PropMustError(cx, PROP_NM_DC);
					return JS_FALSE;
				}
				if( (pDC = zzzJs::gui::gdi::DC::GetPrivate(cx, v, false)) != NULL )
				{
					ReportError_PropTypeError(cx, PROP_NM_DC, "DC" );
					return JS_FALSE;
				}
				// x
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
				// y
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
				// flags
				ZZZJS_PROP_FROMJS_IF_EXIST(flags, pObj, PROP_NM_FLAGS, WXJS_TYPE_NUMBER)
				// solidBackground
				ZZZJS_PROP_FROMJS_IF_EXIST(solidBackground, pObj, PROP_NM_FLAGS, WXJS_TYPE_BOOLEAN)


				
				vp->setBoolean( 
					p->Draw(index, *pDC, x, y, flags, solidBackground)
				);
				
				return JS_TRUE;
			}
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="getSize">
 *  <function returns="Boolean">
 *   <arg name="Index" type=ZZZJS_TYPE_NUMBER>
 *    The index parameter is ignored as all images in the list have the same size.
 *   </arg>
 *   <arg name="Size" type="@wxSize">
 *    Receives the size of the image.
 *   </arg>
 *  </function>
 *  <desc>
 *   The size is put in the <I>Size</I> argument. This method differs from the wxWindow function
 *   GetSize which uses 3 arguments: index, width and height. wxJS uses @wxSize because JavaScript
 *   can't pass primitive types by reference.
 *  </desc>
 * </method>
 */
JSBool ImageList::getSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	int argIndex = 0;
    int width;
    int height;
	int index = 0;	

	wxSize* pSize =NULL;

	if( argv[argIndex].isNumber() == true )
	{
		ZZZJS_CHECK_ARG_COUNT(1, 2)



		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
		argIndex++;
		
		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			// 第二引数の指定は、Sizeのインスタンスでなければならない。
			/*
				{ x:0, y:0 }のような指定は出来ない。

				var sz = new Size();
				p.getSize(0, sz);
			*/
			if( (ZZZJS_ARG_GET_PRIVATE(pSize, Size)) == NULL )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, Size::getClassName() );
				return false;
			}
			argIndex--;
		}

		bool bRet = p->GetSize(index, width, height);
		if( pSize != NULL ) {
			pSize->SetWidth(width);
			pSize->SetHeight(height);
			*vp = ToJS(cx, bRet);
		} else {
			// オブジェクトとして返す
			if( bRet == false )
			{
				vp->setNull();
			} else {
				JSObject *objAttr = JS_NewObject(cx, NULL, NULL, NULL);
				JS::RootedObject jsvaAttr(cx, objAttr);
				{
					wxString strName(_T("width"));
					jsval attrValue = ToJS(cx, width );
					JS_SetUCProperty(cx, 
						objAttr, 
						(const jschar *) strName.c_str(), 
						strName.Length(), &attrValue);
				}
				{
					wxString strName(_T("height"));
					jsval attrValue = ToJS(cx, height );
					JS_SetUCProperty(cx, 
						objAttr, 
						(const jschar *) strName.c_str(), 
						strName.Length(), &attrValue);
				}
				vp->setObjectOrNull(objAttr);
			}
		}
		
        return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
				{
					index: Number, 
					size: Size[Option. must be instance.]
				}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
			{
				// index
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)

			}
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_SIZE), &v) == JS_TRUE )  
			{
				pSize = Size::GetPrivate(cx, v, false);
				if( pSize == NULL ) 
				{
					ReportError_PropTypeError(cx, PROP_NM_SIZE, Size::getClassName() );
					return JS_FALSE;
				}
			}



			bool bRet = p->GetSize(index, width, height);
			if( pSize != NULL ) {
				pSize->SetWidth(width);
				pSize->SetHeight(height);
				*vp = ToJS(cx, bRet);
			} else {
				// オブジェクトとして返す
				if( bRet == false )
				{
					vp->setNull();
				} else {
					JSObject *objAttr = JS_NewObject(cx, NULL, NULL, NULL);
					JS::RootedObject jsvaAttr(cx, objAttr);
					{
						wxString strName(_T(PROP_NM_WIDTH));
						jsval attrValue = ToJS(cx, width );
						JS_SetUCProperty(cx, 
							objAttr, 
							(const jschar *) strName.c_str(), 
							strName.Length(), &attrValue);
					}
					{
						wxString strName(_T(PROP_NM_HEIGHT));
						jsval attrValue = ToJS(cx, height );
						JS_SetUCProperty(cx, 
							objAttr, 
							(const jschar *) strName.c_str(), 
							strName.Length(), &attrValue);
					}
					vp->setObjectOrNull(objAttr);
				}
			}
		
			return JS_TRUE;
		} while( 0 );
	}
	
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="remove">
 *  <function returns="Boolean">
 *   <arg name="Index" type=ZZZJS_TYPE_NUMBER>
 *    The index of the image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Removes the image with the given index. Returns true on success.
 *  </desc>
 * </method>
 */
JSBool ImageList::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	
	int argIndex = 0;
	int index = 0;	

	wxSize* pSize =NULL;

	if( argv[argIndex].isNumber() == true )
	{
		ZZZJS_CHECK_ARG_COUNT(1, 1)
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
		argIndex++;
		
		vp->setBoolean( p->Remove(index) );
        return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			/*
			{
				index: Number, 
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
			{
				// index
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
					
				vp->setBoolean( p->Remove(index) );
				return JS_TRUE;
			}
		} while( 0 );
	}
	
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}

/***
 * <method name="removeAll">
 *  <function returns="Boolean" />
 *  <desc>
 *   Removes all images. Returns true on success.
 *  </desc>
 * </method>
 */
JSBool ImageList::removeAll(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxImageList *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    *vp = ToJS(cx, p->RemoveAll());
    return JS_TRUE;
}

/***
 * <method name="replace">
 *  <function returns="Boolean">
 *   <arg name="Index" type=ZZZJS_TYPE_NUMBER>
 *    The index of the image to replace.
 *   </arg>
 *   <arg name="Bitmap" type="@wxBitmap">
 *    The new bitmap.
 *   </arg>
 *   <arg name="Mask" type="@wxBitmap">
 *    Monochrome mask bitmap, representing the transparent areas of the image.
 *    Windows only.
 *   </arg>
 *  </function>
 *  <function returns="Boolean">
 *   <arg name="Index" type=ZZZJS_TYPE_NUMBER>
 *    The index of the image to replace.
 *   </arg>
 *   <arg name="Icon" type="@wxIcon">
 *    Icon to use as image.
 *   </arg>
 *  </function>
 *  <desc>
 *   Replaces the image at the given index with a new image.
 *  </desc>
 * </method>
 */
JSBool ImageList::replace(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxImageList *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	/*
	bool 	Replace (int index, const wxBitmap &bitmap, const wxBitmap &mask=wxNullBitmap)
 		Replaces the existing image with the new image. More...
 
	bool 	Replace (int index, const wxIcon &icon)
 		Replaces the existing image with the new image.
	*/

	
	int argIndex = 0;
	zzzJsPtr<wxBitmap> apBitmap;
	zzzJsPtr<wxIcon>   apIcon;
	zzzJsPtr<wxBitmap>   apMask;

	int index = 0;
	if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 3)
		// 0
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);
		argIndex++;


		if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == true )
		{
			// bool 	Replace (int index, const wxBitmap &bitmap, const wxBitmap &mask=wxNullBitmap)
			argIndex++;

			if( argc == 2 ) 
			{
				vp->setInt32(
					p->Replace(index, *(apBitmap.get()) )
				);
				return JS_TRUE;
			}
			else
			{
				if( ZZZJS_ARG_GET_AP(apMask, Bitmap) == true )
				{
					vp->setInt32(
						p->Replace(index, *(apBitmap.get()), *(apMask.get()) )
					);
					return JS_TRUE;
				}
				else
				{
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Bitmap or Colour" );
					return JS_FALSE;
				}
			}
		}
		else
		if( ZZZJS_ARG_GET_AP(apIcon, Icon) == true )
		{
			//bool 	Replace (int index, const wxIcon &icon)
			vp->setInt32(
				p->Replace(index, *(apIcon.get()) )
			);
			return JS_TRUE;
		}
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			// Objectの場合
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}

			/*
			{
				index : Number
				bitmap : Bitmap[icon or this]
				icon : Icon[bitmap or this]
				mask : Bitmap[Option. Default=null]
			}
			*/
			if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_INDEX), &v) == JS_TRUE )  
			{
				// index
				ZZZJS_PROP_FROMJS_CHK_AND_ERROR(index, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
					
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_BITMAP), &v) == JS_TRUE )  
				{
					ZZZJS_PROP_AP_CHK_AND_ERROR(apBitmap, pObj, Bitmap, PROP_NM_BITMAP);
					if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_MASK), &v) == JS_TRUE )
					{
						if( ZZZJS_PROP_GET_AP(apMask, Bitmap, v) == true )
						{
							vp->setInt32(
								p->Add( *(apBitmap.get()), *(apMask.get()) )
							);
							return JS_TRUE;
						} 
					}
					else
					{
						vp->setInt32(
							p->Add( *(apBitmap.get()))
						);
						return JS_TRUE;
					}
				} 
				else
				if( GetPropertyWhenPresent( cx, pObj, _T(PROP_NM_ICON), &v) == JS_TRUE )  
				{
					ZZZJS_PROP_AP_CHK_AND_ERROR(apIcon, pObj, Icon, PROP_NM_ICON);
					vp->setInt32(
						p->Replace(index, *(apIcon.get()) )
					);
					return JS_TRUE;
				}
			}			
		} while( 0 );
	}

	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
    return JS_FALSE;
}
