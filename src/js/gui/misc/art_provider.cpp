/*
 * wxJavaScript - art_provider.cpp
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
 * $Id: art_provider.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// ArtProvider.cpp
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
#include "js/gui/misc/art_provider.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/image.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/size.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/ArtProvider</file>
 * <module>gui</module>
 * <class name="wxArtProvider">
 *  This class encapsulates the concept of a platform-dependent ArtProvider, either monochrome or colour.
 *  See @wxIcon and @wxBitmapType
 * </class>
 */
ZZZJS_INIT_CLASS(ArtProvider, "ArtProvider", 0)

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Name" type=WXJS_TYPE_STRING>Filename</arg>
 *   <arg name="Type" type=WXJS_TYPE_NUMBER>The type of the ArtProvider.</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxArtProvider object.
 *   See @wxBitmapType
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxArtProvider, ArtProvider)
{
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_STATIC_PROPERTY_MAP(ArtProvider)
	ZZZJS_READONLY_STATIC_PROPERTY(P_ADD_BOOKMARK, "ADD_BOOKMARK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_DEL_BOOKMARK, "DEL_BOOKMARK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_SIDE_PANEL, "HELP_SIDE_PANEL")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_SETTINGS, "HELP_SETTINGS")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_BOOK, "HELP_BOOK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_FOLDER, "HELP_FOLDER")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_PAGE, "HELP_PAGE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_BACK, "GO_BACK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_FORWARD, "GO_FORWARD")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_UP, "GO_UP")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_DOWN, "GO_DOWN")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_TO_PARENT, "GO_TO_PARENT")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_HOME, "GO_HOME")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GOTO_FIRST, "GOTO_FIRST")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GOTO_LAST, "GOTO_LAST")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FILE_OPEN, "FILE_OPEN")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FILE_SAVE, "FILE_SAVE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FILE_SAVE_AS, "FILE_SAVE_AS")
	ZZZJS_READONLY_STATIC_PROPERTY(P_PRINT, "PRINT")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP, "HELP")
	ZZZJS_READONLY_STATIC_PROPERTY(P_TIP, "TIP")
	ZZZJS_READONLY_STATIC_PROPERTY(P_REPORT_VIEW, "REPORT_VIEW")
	ZZZJS_READONLY_STATIC_PROPERTY(P_LIST_VIEW, "LIST_VIEW")
	ZZZJS_READONLY_STATIC_PROPERTY(P_NEW_DIR, "NEW_DIR")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HARDDISK, "HARDDISK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FLOPPY, "FLOPPY")
	ZZZJS_READONLY_STATIC_PROPERTY(P_CDROM, "CDROM")
	ZZZJS_READONLY_STATIC_PROPERTY(P_REMOVABLE, "REMOVABLE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FOLDER, "FOLDER")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FOLDER_OPEN, "FOLDER_OPEN")
	ZZZJS_READONLY_STATIC_PROPERTY(P_GO_DIR_UP, "GO_DIR_UP")
	ZZZJS_READONLY_STATIC_PROPERTY(P_EXECUTABLE_FILE, "EXECUTABLE_FILE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_NORMAL_FILE, "NORMAL_FILE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_TICK_MARK, "TICK_MARK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_CROSS_MARK, "CROSS_MARK")
	ZZZJS_READONLY_STATIC_PROPERTY(P_ERROR, "ERROR")
	ZZZJS_READONLY_STATIC_PROPERTY(P_QUESTION, "QUESTION")
	ZZZJS_READONLY_STATIC_PROPERTY(P_WARNING, "WARNING")
	ZZZJS_READONLY_STATIC_PROPERTY(P_INFORMATION, "INFORMATION")
	ZZZJS_READONLY_STATIC_PROPERTY(P_MISSING_IMAGE, "MISSING_IMAGE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_COPY, "COPY")
	ZZZJS_READONLY_STATIC_PROPERTY(P_CUT, "CUT")
	ZZZJS_READONLY_STATIC_PROPERTY(P_PASTE, "PASTE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_DELETE, "DELETE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_NEW, "NEW")
	ZZZJS_READONLY_STATIC_PROPERTY(P_UNDO, "UNDO")
	ZZZJS_READONLY_STATIC_PROPERTY(P_REDO, "REDO")
	ZZZJS_READONLY_STATIC_PROPERTY(P_PLUS, "PLUS")
	ZZZJS_READONLY_STATIC_PROPERTY(P_MINUS, "MINUS")
	ZZZJS_READONLY_STATIC_PROPERTY(P_CLOSE, "CLOSE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_QUIT, "QUIT")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FIND, "FIND")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FIND_AND_REPLACE, "FIND_AND_REPLACE")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FULL_SCREEN, "FULL_SCREEN")
	ZZZJS_READONLY_STATIC_PROPERTY(P_EDIT, "EDIT")
	ZZZJS_READONLY_STATIC_PROPERTY(P_TOOLBAR, "TOOLBAR")
	ZZZJS_READONLY_STATIC_PROPERTY(P_MENU, "MENU")
	ZZZJS_READONLY_STATIC_PROPERTY(P_FRAME_ICON, "FRAME_ICON")
	ZZZJS_READONLY_STATIC_PROPERTY(P_CMN_DIALOG, "CMN_DIALOG")
	ZZZJS_READONLY_STATIC_PROPERTY(P_HELP_BROWSER, "HELP_BROWSER")
	ZZZJS_READONLY_STATIC_PROPERTY(P_MESSAGE_BOX, "MESSAGE_BOX")
	ZZZJS_READONLY_STATIC_PROPERTY(P_BUTTON, "BUTTON")
	ZZZJS_READONLY_STATIC_PROPERTY(P_LIST, "LIST")
	ZZZJS_READONLY_STATIC_PROPERTY(P_OTHER, "OTHER")
ZZZJS_END_PROPERTY_MAP()

bool ArtProvider::GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp)
{
	wxString str;
#define MY_SET_PRPOP(X)			case P_##X:	\
	str = wxART_##X;	\
		ToJSVal(cx, vp, str);break;


	switch( id  )
	{
	MY_SET_PRPOP(ADD_BOOKMARK)
	MY_SET_PRPOP(DEL_BOOKMARK)
	MY_SET_PRPOP(HELP_SIDE_PANEL)
	MY_SET_PRPOP(HELP_SETTINGS)
	MY_SET_PRPOP(HELP_BOOK)
	MY_SET_PRPOP(HELP_FOLDER)
	MY_SET_PRPOP(HELP_PAGE)
	MY_SET_PRPOP(GO_BACK)
	MY_SET_PRPOP(GO_FORWARD)
	MY_SET_PRPOP(GO_UP)
	MY_SET_PRPOP(GO_DOWN)
	MY_SET_PRPOP(GO_TO_PARENT)
	MY_SET_PRPOP(GO_HOME)
	MY_SET_PRPOP(GOTO_FIRST)
	MY_SET_PRPOP(GOTO_LAST)
	MY_SET_PRPOP(FILE_OPEN)
	MY_SET_PRPOP(FILE_SAVE)
	MY_SET_PRPOP(FILE_SAVE_AS)
	MY_SET_PRPOP(PRINT)
	MY_SET_PRPOP(HELP)
	MY_SET_PRPOP(TIP)
	MY_SET_PRPOP(REPORT_VIEW)
	MY_SET_PRPOP(LIST_VIEW)
	MY_SET_PRPOP(NEW_DIR)
	MY_SET_PRPOP(HARDDISK)
	MY_SET_PRPOP(FLOPPY)
	MY_SET_PRPOP(CDROM)
	MY_SET_PRPOP(REMOVABLE)
	MY_SET_PRPOP(FOLDER)
	MY_SET_PRPOP(FOLDER_OPEN)
	MY_SET_PRPOP(GO_DIR_UP)
	MY_SET_PRPOP(EXECUTABLE_FILE)
	MY_SET_PRPOP(NORMAL_FILE)
	MY_SET_PRPOP(TICK_MARK)
	MY_SET_PRPOP(CROSS_MARK)
	MY_SET_PRPOP(ERROR)
	MY_SET_PRPOP(QUESTION)
	MY_SET_PRPOP(WARNING)
	MY_SET_PRPOP(INFORMATION)
	MY_SET_PRPOP(MISSING_IMAGE)
	MY_SET_PRPOP(COPY)
	MY_SET_PRPOP(CUT)
	MY_SET_PRPOP(PASTE)
	MY_SET_PRPOP(DELETE)
	MY_SET_PRPOP(NEW)
	MY_SET_PRPOP(UNDO)
	MY_SET_PRPOP(REDO)
	MY_SET_PRPOP(PLUS)
	MY_SET_PRPOP(MINUS)
	MY_SET_PRPOP(CLOSE)
	MY_SET_PRPOP(QUIT)
	MY_SET_PRPOP(FIND)
	MY_SET_PRPOP(FIND_AND_REPLACE)
	MY_SET_PRPOP(FULL_SCREEN)
	MY_SET_PRPOP(EDIT)
	MY_SET_PRPOP(TOOLBAR)
	MY_SET_PRPOP(MENU)
	MY_SET_PRPOP(FRAME_ICON)
	MY_SET_PRPOP(CMN_DIALOG)
	MY_SET_PRPOP(HELP_BROWSER)
	MY_SET_PRPOP(MESSAGE_BOX)
	MY_SET_PRPOP(BUTTON)
	MY_SET_PRPOP(LIST)
	MY_SET_PRPOP(OTHER)
	}
#undef MY_SET_PRPOP
	return true;
}


ZZZJS_BEGIN_STATIC_METHOD_MAP(ArtProvider)
	ZZZJS_METHOD("delete", Delete, 1)
	ZZZJS_METHOD("getBitmap", getBitmap, 1)
	ZZZJS_METHOD("getIcon", getIcon, 1)
	ZZZJS_METHOD("getNativeSizeHint", getNativeSizeHint, 1)
	ZZZJS_METHOD("getSizeHint", getSizeHint, 1)
	//ZZZJS_METHOD("getIconBundle", getIconBundle, 1)
	ZZZJS_METHOD("hasNativeProvider", hasNativeProvider, 0)
	ZZZJS_METHOD("pop", pop, 0)
	ZZZJS_METHOD("push", push, 1)
	ZZZJS_METHOD("pushBack", pushBack, 1)
	ZZZJS_METHOD("remove", remove, 1)
	ZZZJS_METHOD("getMessageBoxIconId", getMessageBoxIconId, 1)
	ZZZJS_METHOD("getMessageBoxIcon", getMessageBoxIcon, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::Delete(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;


	// 0
	wxArtProvider* pArtProvider = ArtProvider::GetPrivate(cx, argv[argIndex]);
	if( pArtProvider != NULL ) 
	{
		vp->setBoolean( wxArtProvider::Delete(pArtProvider) );
		return JS_TRUE;
	} 
	else 
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();


		// provider
		if( GetPropertyWhenPresent( cx, obj, _T("provider"), &v) == JS_FALSE )  
		{			
			JS_ReportError(cx, "provider property  must specify.");
			return JS_FALSE;
		}
		pArtProvider = ArtProvider::GetPrivate(cx, v);
		if( pArtProvider != NULL ) 
		{
			JS_ReportError(cx, "provider property  must be of type ArtProvider");
			return JS_FALSE;
		}
		vp->setBoolean( wxArtProvider::Delete(pArtProvider) );
		return JS_TRUE;
	} else {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "ArtProvider or { provider : ArtProvider }");
		return JS_FALSE;
	}
	argIndex++;

	

	return JS_TRUE;
}


/***
 * <method name="getBitmap">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getBitmap(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	/*
	static wxBitmap 	GetBitmap (const wxArtID &id, const wxArtClient &client=wxART_OTHER, const wxSize &size=wxDefaultSize)
 		Query registered providers for bitmap with given ID.
	*/
	// 引数の値を取得
	int argIndex = 0;
	


	if( cx, argv[argIndex].isString() == true ) {


		wxArtID id;
		wxArtClient client=wxART_OTHER;
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		if( argc > 3 ) {
			argc = 3;
		}

		// 0
		if( FromJS(cx, argv[argIndex], id) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex++;

		argIndex = argc -1;
		switch( argc ) 
		{
		case 3:
			// 2
			ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
			argIndex--;
		case 2:
			// 2
			if( FromJS(cx, argv[argIndex], client) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		}

		*vp = Bitmap::CreateObject(cx, 
			new wxBitmap(
				wxArtProvider::GetBitmap(id, client, *(apSize.get()))
			)
		);
	}
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull(); 
		
		wxArtID id;
		wxArtClient client=wxART_OTHER;
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);


		// id
		if( GetPropertyWhenPresent( cx, obj, _T("id"), &v) == JS_FALSE )  
		{			
			JS_ReportError(cx, "id property  must specify.");
			return JS_FALSE;
		}
		if( FromJS(cx, v, id) == false ) 
		{
			JS_ReportError(cx, "id property  must be of type String");
			return JS_FALSE;
		}


		// client
		if( GetPropertyWhenPresent( cx, obj, _T("client"), &v) == JS_FALSE )  
		{			
			if( FromJS(cx, v, client) == false ) 
			{
				JS_ReportError(cx, "client property  must be of type String");
				return JS_FALSE;
			}
		}

		// size
		if( GetPropertyWhenPresent( cx, obj, _T("size"), &v) == JS_FALSE )  
		{			
			ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, "size");
		}



		*vp = Bitmap::CreateObject(cx, 
			new wxBitmap(
				wxArtProvider::GetBitmap(id, client, *(apSize.get()))
			)
		);


	} else {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "String or { id : String, client:String(option), size:Size(option) }");
		return JS_FALSE;
	}

	return JS_TRUE;
}


/***
 * <method name="getIcon">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	
	/*
	static wxIcon 	GetIcon (const wxArtID &id, const wxArtClient &client=wxART_OTHER, const wxSize &size=wxDefaultSize)
 		Same as wxArtProvider::GetBitmap, but return a wxIcon object (or wxNullIcon on failure).
	*/


	if( cx, argv[argIndex].isString() == true ) {


		wxArtID id;
		wxArtClient client=wxART_OTHER;
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);

		if( argc > 3 ) {
			argc = 3;
		}

		// 0
		if( FromJS(cx, argv[argIndex], id) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex++;

		argIndex = argc -1;
		switch( argc ) 
		{
		case 3:
			// 2
			ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
			argIndex--;
		case 2:
			// 2
			if( FromJS(cx, argv[argIndex], client) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		}

		*vp = Icon::CreateObject(cx, 
			new wxIcon(
				wxArtProvider::GetIcon(id, client, *(apSize.get()))
			)
		);
	} else
	if( argv[argIndex].isObjectOrNull() == true ) 
	{
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull(); 
		
		wxArtID id;
		wxArtClient client=wxART_OTHER;
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);


		// id
		if( GetPropertyWhenPresent( cx, obj, _T("id"), &v) == JS_FALSE )  
		{			
			JS_ReportError(cx, "id property  must specify.");
			return JS_FALSE;
		}
		if( FromJS(cx, v, id) == false ) 
		{
			JS_ReportError(cx, "id property  must be of type String");
			return JS_FALSE;
		}


		// client
		if( GetPropertyWhenPresent( cx, obj, _T("client"), &v) == JS_FALSE )  
		{			
			if( FromJS(cx, v, client) == false ) 
			{
				JS_ReportError(cx, "client property  must be of type String");
				return JS_FALSE;
			}
		}

		// size
		if( GetPropertyWhenPresent( cx, obj, _T("size"), &v) == JS_FALSE )  
		{			
			ZZZJS_PROP_AP_CHK_AND_ERROR(apSize, obj, Size, "size");
		}



		*vp = Icon::CreateObject(cx, 
			new wxIcon(
				wxArtProvider::GetIcon(id, client, *(apSize.get()))
			)
		);


	} else {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "String or { id : String, client:String(option), size:Size(option) }");
		return JS_FALSE;
	}

	return JS_TRUE;
}


/***
 * <method name="getNativeSizeHint">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getNativeSizeHint(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;


	wxArtClient client;
	
	// 0
	if( FromJS(cx, argv[argIndex], client) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;


	*vp = Size::CreateObject(cx, 
		new wxSize(
			wxArtProvider::GetNativeSizeHint(client)
		)
	);

	return JS_TRUE;
}


/***
 * <method name="getSizeHint">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getSizeHint(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	/*
	static wxSize 	GetSizeHint (const wxArtClient &client, bool platform_default=false)
 		Returns a suitable size hint for the given wxArtClient. 
	*/
	wxArtClient client=wxART_OTHER;
	bool platform_default=false;

	if( argc > 2 ) {
		argc = 2;
	}


	// 0
	if( FromJS(cx, argv[argIndex], client) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;


	argIndex = argc -1;
	switch( argc ) 
	{
	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], platform_default) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
			return JS_FALSE;
		}
		argIndex--;
	}
	*vp = Size::CreateObject(cx, 
		new wxSize(
			wxArtProvider::GetSizeHint(client, platform_default)
		)
	);

	return JS_TRUE;
}


/***
 * <method name="hasNativeProvider">
 *  <function returns="Boolean">
 *  </function>
 *  <desc>
 *   Returns true if the platform uses native icons provider that should take precedence over any customizations. 
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::hasNativeProvider(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	/*
	static bool 	HasNativeProvider ()
 		Returns true if the platform uses native icons provider that should take precedence over any customizations. 
	*/

	vp->setBoolean(wxArtProvider::HasNativeProvider());

	return JS_TRUE;
}

/***
 * <method name="pop">
 *  <function returns="Boolean">
 *  </function>
 *  <desc>
 *   Returns true if the platform uses native icons provider that should take precedence over any customizations. 
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::pop(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	/*
	static bool 	HasNativeProvider ()
 		Returns true if the platform uses native icons provider that should take precedence over any customizations. 
	*/

	vp->setBoolean(wxArtProvider::Pop());

	return JS_TRUE;
}
 
/***
 * <method name="push">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::push(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	// 0
	wxArtProvider* pArtProvider = ArtProvider::GetPrivate(cx, argv[0]);
	if( pArtProvider == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "ArtProvider");
		return JS_FALSE;
	}
	argIndex++;


	wxArtProvider::Push(pArtProvider);
//	vp->setBoolean( wxArtProvider::Push(pArtProvider) );
	
	return JS_TRUE;
}
 
/***
 * <method name="pushBack">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::pushBack(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	// 0
	wxArtProvider* pArtProvider = ArtProvider::GetPrivate(cx, argv[0]);
	if( pArtProvider == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "ArtProvider");
		return JS_FALSE;
	}
	argIndex++;
	

	wxArtProvider::PushBack(pArtProvider);
//	vp->setBoolean( wxArtProvider::Push(pArtProvider) );
	
	return JS_TRUE;
}
 
/***
 * <method name="remove">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;

	// 0
	wxArtProvider* pArtProvider = ArtProvider::GetPrivate(cx, argv[0]);
	if( pArtProvider == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "ArtProvider");
		return JS_FALSE;
	}
	argIndex++;
	


	vp->setBoolean( wxArtProvider::Remove(pArtProvider) );
	
	return JS_TRUE;
}

 


/***
 * <method name="getMessageBoxIconId">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getMessageBoxIconId(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;


	int flags;


	// 0
	if( FromJS(cx, argv[argIndex], flags) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;


	*vp = ToJS(cx, wxArtProvider::GetMessageBoxIconId(flags));

	return JS_TRUE;
}

 


/***
 * <method name="getMessageBoxIcon">
 *  <function returns="Boolean">
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *    The width of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *    The height of the ArtProvider in pixels.
 *   </arg>
 *   <arg name="Depth" type=WXJS_TYPE_NUMBER default="-1">
 *    The depth of the ArtProvider in pixels. When omitted (or a value -1) , the screen depth is used.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a fresh ArtProvider.
 *  </desc>
 * </method>
 */
 JSBool ArtProvider::getMessageBoxIcon(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;


	int flags;


	// 0
	if( FromJS(cx, argv[argIndex], flags) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;

	*vp = Icon::CreateObject(cx, 
		new wxIcon(
			wxArtProvider::GetMessageBoxIcon(flags)
		)
	);

	return JS_TRUE;
}