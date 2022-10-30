#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/ext/locale.h"
#include "js/common/conf.h"
#include "js/common/defs.h"
#include "js/gui/errors.h"
#include <wx/string.h>

using namespace zzzJs;
using namespace ext;



void Locale::InitClass(JSContext *cx,
                                  JSObject *obj,
                                  JSObject *proto)
{

	JSConstDoubleSpec wxLocaleCategoryMap[] = 
	{
		WXJS_CONSTANT(wxLOCALE_CAT_, NUMBER)
		WXJS_CONSTANT(wxLOCALE_CAT_, DATE)
		WXJS_CONSTANT(wxLOCALE_CAT_, MONEY)
		WXJS_CONSTANT(wxLOCALE_CAT_, DEFAULT)
		WXJS_CONSTANT(wxLOCALE_CAT_, MAX)
		{ 0 }
	};
	JSObject *constObj = JS_DefineObject(cx, obj, "Category", 
    								NULL, NULL,
									JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxLocaleCategoryMap);


	
	JSConstDoubleSpec wxLocaleInitFlagsMap[] = 
	{
		WXJS_CONSTANT(wxLOCALE_, DONT_LOAD_DEFAULT)
		WXJS_CONSTANT(wxLOCALE_, LOAD_DEFAULT)
		{ 0 }
	};
	constObj = JS_DefineObject(cx, obj, "InitFlag", 
    								NULL, NULL,
									JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxLocaleInitFlagsMap);

	
	JSConstDoubleSpec wxLocaleInfoMap[] = 
	{
		WXJS_CONSTANT(wxLOCALE_, THOUSANDS_SEP)
		WXJS_CONSTANT(wxLOCALE_, DECIMAL_POINT)
		WXJS_CONSTANT(wxLOCALE_, SHORT_DATE_FMT)
		WXJS_CONSTANT(wxLOCALE_, LONG_DATE_FMT)
		WXJS_CONSTANT(wxLOCALE_, DATE_TIME_FMT)
		WXJS_CONSTANT(wxLOCALE_, TIME_FMT)
		{ 0 }
	};
	constObj = JS_DefineObject(cx, obj, "Info", 
    								NULL, NULL,
									JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineConstDoubles(cx, constObj, wxLocaleInfoMap);



}
/***
 * <file>point</file>
 * <module>ext</module>
 * <class name="wxPoint">
 *  A wxPoint is a useful data structure for graphics operations.
 *  It simply contains integer x and y members.
 * </class>
 */
WXJS_INIT_CLASS(Locale, "Locale", 0)

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
WXJS_BEGIN_PROPERTY_MAP(Locale)
  WXJS_READONLY_PROPERTY(P_CanonicalName, "canonicalName")
  WXJS_READONLY_PROPERTY(P_Locale, "locale")
  WXJS_READONLY_PROPERTY(P_Name, "name")
  WXJS_READONLY_PROPERTY(P_SysName, "sysName")
  WXJS_READONLY_PROPERTY(P_SystemEncoding, "systemEncoding")
  WXJS_READONLY_PROPERTY(P_SystemEncodingName, "systemEncodingName")
  WXJS_READONLY_PROPERTY(P_SystemLanguage, "systemLanguage")
  WXJS_READONLY_PROPERTY(P_IsOk, "isOk")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxLocale, Locale)
    switch (id) 
	{
	case P_CanonicalName:
		ToJSVal(cx, vp, p->GetCanonicalName());
		break;
	case P_Locale:		
		ToJSVal(cx, vp, p->GetLocale());
		break;
	case P_Name:		
		ToJSVal(cx, vp, p->GetName());
		break;
	case P_SysName:		
		ToJSVal(cx, vp, p->GetSysName());
		break;
	case P_SystemEncoding:		
		ToJSVal(cx, vp, (int)p->GetSystemEncoding());
		break;
	case P_SystemEncodingName:		
		ToJSVal(cx, vp, p->GetSystemEncodingName());
		break;
	case P_SystemLanguage:		
		ToJSVal(cx, vp, p->GetSystemLanguage());
		break;
	case P_IsOk:		
		ToJSVal(cx, vp, p->IsOk());
		break;
    }
    return true;
WXJS_END_GET_PROP


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
WXJS_BEGIN_CONSTRUCTOR(wxLocale, Locale)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	if ( argv.length()  == 0 )
	{
		return new wxLocale();
	}
	else
	{
		wxString name;
		wxString shortName = wxEmptyString;
		wxString locale = wxEmptyString;
		bool bLoadDefault = true ;
		bool bConvertEncoding = true;

		
		int argIndex = 0;
		if( argc > 5 ) {
			argc = 5;
		}


		argIndex = argc-1;
		switch( argc ) {
		case 5:
			// 5
			if( FromJS(cx, argv[argIndex], bConvertEncoding) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolena");
				return JS_FALSE;
			}
			argIndex--;
		case 4:
			// 4
			if( FromJS(cx, argv[argIndex], bLoadDefault) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolena");
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			// 3
			if( FromJS(cx, argv[argIndex], locale) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		case 2:
			// 2
			if( FromJS(cx, argv[argIndex], shortName) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		}
		argIndex = 0;
		// 2
		if( FromJS(cx, argv[argIndex], name) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}


		return new wxLocale(
			name,
			shortName,
			locale,
			bLoadDefault
#if WXWIN_COMPATIBILITY_2_8
			, bConvertEncoding
#endif
			);
	}
WXJS_END_CONSTRUCTOR
	
// メソッドの定義
WXJS_BEGIN_METHOD_MAP(Locale)
	WXJS_METHOD("addCatalog", addCatalog, 1 )
	WXJS_METHOD("addCatalogLookupPathPrefix", addCatalogLookupPathPrefix, 1 )
	WXJS_METHOD("getLanguageName", getLanguageName, 1 )
	WXJS_METHOD("getString", getString, 1 )
	WXJS_METHOD("getHeaderValue", getHeaderValue, 1 )
	WXJS_METHOD("init", init, 0)
	WXJS_METHOD("isLoaded", isLoaded, 1 )
WXJS_END_METHOD_MAP()
JSBool Locale::addCatalog(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxString szDomain;
	int msgIdLanguage; // wxLanguage
	wxString msgIdCharset;

	// 引数の値を取得
	int argIndex = 0;
	if( argc > 3 ) {
		argc = 3;
	}	

	argIndex = argc-1;
	switch( argc ) {
	case 3:
		// 3
		if( FromJS(cx, argv[argIndex], msgIdCharset) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex--;
	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], msgIdLanguage) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 2
	if( FromJS(cx, argv[argIndex], szDomain) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}


	// APIの実行と、戻り値の設定
	switch( argc ) {
	case 3:
		vp->setBoolean( p->AddCatalog(szDomain, (wxLanguage)msgIdLanguage, msgIdCharset) );
		break;
	case 2:
		vp->setBoolean( p->AddCatalog(szDomain, (wxLanguage)msgIdLanguage) );
		break;
	case 1:
		vp->setBoolean( p->AddCatalog(szDomain) );
		break;
	}
	

	return JS_TRUE;
}
JSBool Locale::addCatalogLookupPathPrefix(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxString prefix;

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], prefix) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	p->AddCatalogLookupPathPrefix(prefix);

	return JS_TRUE;
}
JSBool Locale::getLanguageName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int lang;

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], lang) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}

	// APIの実行と、戻り値の設定
	*vp = ToJS(cx, p->GetLanguageName(lang));

	return JS_TRUE;
}
JSBool Locale::getString(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxString origString;
	wxString origString2;
	unsigned n = 0;
	wxString domain = wxEmptyString;

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], origString) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;

	if( argc == 2 || argc == 1 ) {
		// 2
		if( argc == 2 ) {
			if( FromJS(cx, argv[argIndex], domain) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}		
		}		
		*vp = ToJS(cx,  p->GetString(origString, domain));
	} else {
		if( argc > 4 ) {
			argc = 4;
		}
		argIndex = argc-1;
		switch( argc ) {
		case 4:
			// 4
			if( FromJS(cx, argv[argIndex], domain) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			// 3
			if( FromJS(cx, argv[argIndex], n) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
		case 2:
			// 2
			if( FromJS(cx, argv[argIndex], origString2) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		}
		*vp = ToJS(cx,  p->GetString(origString, origString2, n, domain));
	}



	return JS_TRUE;
}
JSBool Locale::getHeaderValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	wxString szHeader;
	wxString domain = wxEmptyString;

	// 引数の値を取得
	int argIndex = 0;

	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {

	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], domain) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		argIndex--;
	}
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], szHeader) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	*vp = ToJS(cx,  p->GetHeaderValue(szHeader, domain));



	return JS_TRUE;
}
JSBool Locale::init(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	int language = wxLANGUAGE_DEFAULT;
	int flags = wxLOCALE_LOAD_DEFAULT;

	// 引数の値を取得
	int argIndex = 0;

	if( argc > 2 ) {
		argc = 2;
	}
	argIndex = argc-1;
	switch( argc ) {
	case 2:
		// 2
		if( FromJS(cx, argv[argIndex], flags) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	case 1:
		// 1
		if( FromJS(cx, argv[argIndex], language) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		argIndex--;
	}

	*vp = ToJS(cx,  p->Init(language, flags));



	return JS_TRUE;
}
JSBool Locale::isLoaded(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxLocale*p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	wxString domain = wxEmptyString;

	// 引数の値を取得
	int argIndex = 0;

	// 1
	if( FromJS(cx, argv[argIndex], domain) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	*vp = ToJS(cx,  p->IsLoaded(domain));



	return JS_TRUE;
}




WXJS_BEGIN_STATIC_METHOD_MAP(Locale)
	WXJS_METHOD("getTranslation", getTranslation, 1)
WXJS_END_METHOD_MAP()


JSBool Locale::getTranslation(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString origString;
	wxString origString2;
	unsigned n = 0;
	wxString domain = wxEmptyString;

	// 引数の値を取得
	int argIndex = 0;
	argIndex = 0;
	// 1
	if( FromJS(cx, argv[argIndex], origString) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;

	if( argc == 2 || argc == 1 ) {
		// 2
		if( argc == 2 ) {
			if( FromJS(cx, argv[argIndex], domain) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}		
		}		
		*vp = ToJS(cx,  wxGetTranslation(origString, domain));
	} else {
		if( argc > 4 ) {
			argc = 4;
		}
		argIndex = argc-1;
		switch( argc ) {
		case 4:
			// 4
			if( FromJS(cx, argv[argIndex], domain) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		case 3:
			// 3
			if( FromJS(cx, argv[argIndex], n) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
				return JS_FALSE;
			}
			argIndex--;
		case 2:
			// 2
			if( FromJS(cx, argv[argIndex], origString2) == false ) {
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
			argIndex--;
		}
		*vp = ToJS(cx,  wxGetTranslation(origString, origString2, n, domain));
	}



	return JS_TRUE;
}