#include "precompile.h"



#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "js/common/type.h"

//template<class T>
//bool FromJS(JSContext *cx, JS::Value v, T& to);

template<>
bool zzzJs::FromJS<int>(JSContext *cx, JS::Value v, int &to)
{
	int32 temp;
	if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
	{
		to = temp;
		return true;
	}
	else
		return false;
}

template<>
bool zzzJs::FromJS<unsigned int>(JSContext *cx, JS::Value v, unsigned int &to)
{
	int32 temp;
	if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
	{
		to = temp;
		return true;
	}
	else
		return false;
}


template<>
bool zzzJs::FromJS<long>(JSContext *cx, JS::Value v, long &to)
{
	int32 temp;
	if ( JS_ValueToInt32(cx, v, &temp) )
	{
		to = temp;
		return JS_TRUE;
	}
	return JS_FALSE;
}

template<>
bool zzzJs::FromJS<double>(JSContext *cx, JS::Value v, double &to)
{
    double d;
    if ( JS_ValueToNumber(cx, v, &d) == JS_TRUE )
    {
        to = d;
        return true;
    }
    else
        return false;
}

template<>
bool zzzJs::FromJS<bool>(JSContext *cx, JS::Value v, bool &to)
{
	JSBool b;
	if ( JS_ValueToBoolean(cx, v, &b) == JS_TRUE )
	{
		to = (b == JS_TRUE);
		return true;
	}
	else
		return false;
}

template<>
bool zzzJs::FromJS<wxString>(JSContext *cx, JS::Value v, wxString &to)
{
	wxMBConvStrictUTF8 conv;
    JSString *str = JS_ValueToString(cx, v);

//	jschar *s = JS_GetStringChars(str);
	// 日本語を扱えるように、UTF8で取得して、ネイティブに変換
	char * pUTFStr = JS_EncodeStringToUTF8(cx, str);
	
	to = wxString(conv.cMB2WX((char *) pUTFStr));
    return true;
}

template<>
bool zzzJs::FromJS<wxDateTime>(JSContext *cx, JS::Value v, wxDateTime& to)
{
    to.SetToCurrent(); // To avoid invalid date asserts.

    JSObject *obj = JSVAL_TO_OBJECT(v);

//    if ( js_DateIsValid(cx, obj) )
    if ( js_DateIsValid(obj) )
    {
	    to.SetYear(js_DateGetYear(cx, obj));
	    to.SetMonth((wxDateTime::Month) js_DateGetMonth(cx, obj));
	    to.SetDay((unsigned short) js_DateGetDate(cx, obj));
	    to.SetHour((unsigned short) js_DateGetHours(cx, obj));
	    to.SetMinute((unsigned short) js_DateGetMinutes(cx, obj));
	    to.SetSecond((unsigned short) js_DateGetSeconds(/*cx,*/ obj));
	    return true;
    }
    else
	    return false;
}

template<>
bool zzzJs::FromJS<zzzJs::StringsPtr>(JSContext*cx, JS::Value v, StringsPtr &to)
{
    //if ( JSVAL_IS_OBJECT(v) )
	if( v.isObjectOrNull() )
    {
	    JSObject *objItems = JSVAL_TO_OBJECT(v);
	    if (    objItems != (JSObject *) NULL
		     && JS_IsArrayObject(cx, objItems) )
	    {
			uint32_t length = 0;
		    JS_GetArrayLength(cx, objItems, &length);
		    to.Allocate(length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, objItems, i, &element);
                zzzJs::FromJS(cx, element, to[i]);
		    }
	    }
	    return true;
    }
    else
	    return false;
}

template<>
bool zzzJs::FromJS<wxArrayString>(JSContext *cx, JS::Value v, wxArrayString &to)
{
    //if ( JSVAL_IS_OBJECT(v) )
	if( v.isObjectOrNull() )
    {
        JSObject *obj = JSVAL_TO_OBJECT(v);
        if (    obj != NULL
             && JS_IsArrayObject(cx, obj) )
        {
		    uint32_t length = 0;
		    JS_GetArrayLength(cx, obj, &length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, obj, i, &element);
                wxString stringElement;
			    if ( FromJS(cx, element, stringElement) )
                    to.Add(stringElement);
		    }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

template<>
bool zzzJs::FromJS<wxArrayInt>(JSContext *cx, JS::Value v, wxArrayInt &to)
{
    //if ( JSVAL_IS_OBJECT(v) )
	if( v.isObjectOrNull() )
    {
        JSObject *obj = JSVAL_TO_OBJECT(v);
        if (    obj != NULL
             && JS_IsArrayObject(cx, obj) )
        {
		    uint32_t length = 0;
		    JS_GetArrayLength(cx, obj, &length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, obj, i, &element);
                int iElement;
			    if ( FromJS(cx, element, iElement) )
                    to.Add(iElement);
		    }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

template<>
bool zzzJs::FromJS<wxStringList>(JSContext *cx, JS::Value v, wxStringList &to)
{
    //if ( JSVAL_IS_OBJECT(v) )
	if( v.isObjectOrNull() )
    {
        JSObject *obj = JSVAL_TO_OBJECT(v);
        if (    obj != NULL
             && JS_IsArrayObject(cx, obj) )
        {
		    uint32_t length = 0;
		    JS_GetArrayLength(cx, obj, &length);
		    for(uint32_t i =0; i < length; i++)
		    {
			    JS::Value element;
			    JS_GetElement(cx, obj, i, &element);
                wxString stringElement;
			    if ( FromJS(cx, element, stringElement) )
                    to.Add(stringElement);
		    }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
template<>
bool zzzJs::FromJS<wxVariant>(JSContext *cx, JS::Value v, wxVariant &to)
{
	return ConvertJs2WxVariant(cx, v, to);
}

template<>
bool zzzJs::FromJS<long long>(JSContext *cx, JS::Value v, long long &to)
{
	int32 temp;
	if( v.isNumber() ) {
		int64_t b = (int64_t)-1;
		if( JS_ValueToInt64(cx, v, &b) == JS_TRUE ) {
			to = (long long)b;
			return true;
		}
		if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
		{
			to = temp;
			return true;
		}
	}
	return false; 
}

template<>
bool zzzJs::FromJS<unsigned long long>(JSContext *cx, JS::Value v, unsigned long long &to)
{
	int32 temp;
	if( v.isNumber() ) {
		uint64_t b = (uint64_t)-1;
		if( JS_ValueToUint64(cx, v, &b) == JS_TRUE ) {
			to = (unsigned long long)b;
			return true;
		}
		if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
		{
			to = temp;
			return true;
		}
	}
	return false; 
}


template<>
bool zzzJs::FromJS<int64_t>(JSContext *cx, JS::Value v, int64_t &to)
{
	int32 temp;
	if( v.isNumber() ) {
		int64_t b = (int64_t)-1;
		if( JS_ValueToInt64(cx, v, &b) == JS_TRUE ) {
			to = (long long)b;
			return true;
		}
		if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
		{
			to = temp;
			return true;
		}
	}
	return false; 
}

template<>
bool zzzJs::FromJS<uint64_t>(JSContext *cx, JS::Value v, uint64_t &to)
{
	int32 temp;
	if( v.isNumber() ) {
		uint64_t b = (uint64_t)-1;
		if( JS_ValueToUint64(cx, v, &b) == JS_TRUE ) {
			to = (unsigned long long)b;
			return true;
		}
		if ( JS_ValueToInt32(cx, v, &temp) == JS_TRUE )
		{
			to = temp;
			return true;
		}
	}
	return false; 
}

//template<>
//bool zzzJs::FromJS<wxPoint>(JSContext *cx, JS::Value v, wxPoint &to)
//{
//    if( v.isObjectOrNull() == false ) {
//		return false;
//	}
//	JSObject *obj = JSVAL_TO_OBJECT(v);
//	JSBool bFound;
//	int x, y;
//	
//	// x or width
//	do {
//		if( JS_HasUCProperty(cx, obj, L"x", ::wcslen(L"x"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"x", ::wcslen(L"x"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, x ) == false ) {
//		return false;
//	}
//		
//	// y
//	do {
//		if( JS_HasUCProperty(cx, obj, L"y", ::wcslen(L"y"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"y", ::wcslen(L"y"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, y ) == false ) {
//		return false;
//	}
//
//
//	to.x = x;
//	to.y = y;
//
//
//	return true;
//}


//template<>
//bool zzzJs::FromJS<wxSize>(JSContext *cx, JS::Value v, wxSize &to)
//{
//    if( v.isObjectOrNull() == false ) {
//		return false;
//	}
//	JSObject *obj = JSVAL_TO_OBJECT(v);
//	JSBool bFound;
//	int x, y;
//
//	// x or width
//	do {
//		if( JS_HasUCProperty(cx, obj, L"x", ::wcslen(L"x"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"x", ::wcslen(L"x"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		if( JS_HasUCProperty(cx, obj, L"width", ::wcslen(L"width"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"width", ::wcslen(L"width"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, x ) == false ) {
//		return false;
//	}
//		
//	// y or height
//	do {
//		if( JS_HasUCProperty(cx, obj, L"y", ::wcslen(L"y"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"y", ::wcslen(L"y"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		if( JS_HasUCProperty(cx, obj, L"height", ::wcslen(L"height"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"height", ::wcslen(L"height"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, y ) == false ) {
//		return false;
//	}
//
//
//	to.x = x;
//	to.y = y;
//
//
//	return true;
//}

//
//template<>
//bool zzzJs::FromJS<wxRect>(JSContext *cx, JS::Value v, wxRect &to)
//{
//    if( v.isObjectOrNull() == false ) {
//		return false;
//	}
//	JSObject *obj = JSVAL_TO_OBJECT(v);
//	int x, y, width, height;
//	JSBool bFound;
//	
//
//	// x
//	do {
//		if( JS_HasUCProperty(cx, obj, L"x", ::wcslen(L"x"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"x", ::wcslen(L"x"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, x ) == false ) {
//		return false;
//	}
//		
//	// y
//	do {
//		if( JS_HasUCProperty(cx, obj, L"y", ::wcslen(L"y"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"y", ::wcslen(L"y"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, y ) == false ) {
//		return false;
//	}
//
//	// width
//	do {
//		if( JS_HasUCProperty(cx, obj, L"width", ::wcslen(L"width"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"width", ::wcslen(L"width"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, width ) == false ) {
//		return false;
//	}
//		
//	// height
//	do {
//		if( JS_HasUCProperty(cx, obj, L"height", ::wcslen(L"height"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"height", ::wcslen(L"height"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, height ) == false ) {
//		return false;
//	}
//
//
//	to.x = x;
//	to.y = y;
//	to.width = width;
//	to.height = height;
//
//
//	return true;
//}


//template<>
//bool zzzJs::FromJS<wxColour>(JSContext *cx, JS::Value v, wxColour &to)
//{
//    if( v.isObjectOrNull() == false ) {
//		return false;
//	}
//	JSObject *obj = JSVAL_TO_OBJECT(v);
//	int r, g, b;
//	int alpha = (int)wxALPHA_OPAQUE;
//	JSBool bFound;
//	
//
//	// r or red
//	do {
//		if( JS_HasUCProperty(cx, obj, L"r", ::wcslen(L"r"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"r", ::wcslen(L"r"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		
//		if( JS_HasUCProperty(cx, obj, L"red", ::wcslen(L"red"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"red", ::wcslen(L"red"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//
//
//
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, r ) == false ) {
//		return false;
//	}
//		
//	// g or green
//	do {
//		if( JS_HasUCProperty(cx, obj, L"g", ::wcslen(L"g"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"g", ::wcslen(L"g"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		if( JS_HasUCProperty(cx, obj, L"green", ::wcslen(L"green"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"green", ::wcslen(L"green"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, g ) == false ) {
//		return false;
//	}
//
//	// b or blue
//	do {
//		if( JS_HasUCProperty(cx, obj, L"b", ::wcslen(L"b"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"b", ::wcslen(L"b"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		if( JS_HasUCProperty(cx, obj, L"blue", ::wcslen(L"blue"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"blue", ::wcslen(L"blue"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//		return JS_FALSE;
//	} while( 0 );
//	if( FromJS(cx, v, b ) == false ) {
//		return false;
//	}
//
//
//	// a or alpha
//	do {
//		if( JS_HasUCProperty(cx, obj, L"a", ::wcslen(L"a"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"a", ::wcslen(L"a"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//
//		if( JS_HasUCProperty(cx, obj, L"alpha", ::wcslen(L"alpha"), &bFound) == JS_FALSE) {
//			return false;
//		}
//		if( bFound == JS_TRUE ) {
//			if( JS_GetUCProperty(cx, obj, L"alpha", ::wcslen(L"alpha"), &v) == JS_FALSE) {
//				return false;
//			}
//			break;
//		}
//	} while( 0 );
//	if( bFound == JS_TRUE ) {
//		if( FromJS(cx, v, alpha ) == false ) {
//			return false;
//		}
//	}
//
//	to.Set(r, g, b, alpha);
//
//	return true;
//}

//template<class T>
//JS::Value ToJS(JSContext *cx, T wx);

template<>
JS::Value zzzJs::ToJS<int>(JSContext* WXUNUSED(cx), const int &from)
{
	JS::Value ret;
	ret.setInt32(from);
	return ret;
//	return INT_TO_JSVAL(from);
}

template<>
bool zzzJs::ToJSVal<int>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const int &from)
{
	v.setInt32(from);
	return true;
}



template<>
JS::Value zzzJs::ToJS<unsigned int>(JSContext* WXUNUSED(cx), const unsigned int&from)
{
    return INT_TO_JSVAL(from);
}


template<>
bool zzzJs::ToJSVal<unsigned int>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const unsigned int &from)
{
	v.setInt32(from);
	return true;
}



template<>
JS::Value zzzJs::ToJS<long>(JSContext* WXUNUSED(cx), const long &from)
{
	return INT_TO_JSVAL(from);
}

template<>
bool zzzJs::ToJSVal<long>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const long &from)
{
	v.setInt32(from);
	return true;
}


template<>
JS::Value zzzJs::ToJS<unsigned long>(JSContext* cx, const unsigned long&from)
{
    JS::Value v;
    v = DOUBLE_TO_JSVAL((double)from);//JS_NewDoubleValue(cx, from, &v);
	return v;
}

template<>
bool zzzJs::ToJSVal<unsigned long>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const unsigned long &from)
{
	v.setDouble((double)from);
	return true;
}

template<>
JS::Value zzzJs::ToJS<float>(JSContext* cx, const float &from)
{
    JS::Value v;
	v = DOUBLE_TO_JSVAL((double)from);
//    JS_NewDoubleValue(cx, from, &v);
	return v;
}


template<>
bool zzzJs::ToJSVal<float>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const float &from)
{
	v.setDouble((double)from);
	return true;
}



template<>
JS::Value zzzJs::ToJS<double>(JSContext* cx, const double &from)
{
    JS::Value v;
	v = DOUBLE_TO_JSVAL((double)from);
//    JS_NewDoubleValue(cx, from, &v);
	return v;
}



template<>
bool zzzJs::ToJSVal<double>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const double &from)
{
	v.setDouble((double)from);
	return true;
}



template<>
JS::Value zzzJs::ToJS<bool>(JSContext* WXUNUSED(cx), const bool &from)
{
	return BOOLEAN_TO_JSVAL(from);
}



template<>
bool zzzJs::ToJSVal<bool>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const bool &from)
{
	v.setBoolean(from);
	return true;
}

template<>
JS::Value zzzJs::ToJS<wxString>(JSContext* cx, const wxString &from)
{
  int length = from.length();
    if ( length == 0 )
    {
        return STRING_TO_JSVAL(JS_NewUCStringCopyN(cx, (jschar *) "", 0));
    }
	JS::Value val = JSVAL_VOID;
	
	wxMBConvUTF16 utf16;
    wxCharBuffer buffer = from.mb_str(utf16);
    val = STRING_TO_JSVAL(JS_NewUCStringCopyN(cx, (jschar *) buffer.data(), length));
    return val;
}



template<>
bool zzzJs::ToJSVal<wxString>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxString &from)
{
	int length = from.length();
	if ( length == 0 )
	{
		v.setString( JS_NewUCStringCopyN(cx, (jschar *) "", 0) );
		return true;
//		return STRING_TO_JSVAL(JS_NewUCStringCopyN(cx, (jschar *) "", 0));
	}
	JS::Value val = JSVAL_VOID;
	
	wxMBConvUTF16 utf16;
	wxCharBuffer buffer = from.mb_str(utf16);

	v.setString( JS_NewUCStringCopyN(cx, (jschar *) buffer.data(), length) );
//	val = STRING_TO_JSVAL(JS_NewUCStringCopyN(cx, (jschar *) buffer.data(), length));
	return true;
}











template<>
JS::Value zzzJs::ToJS<wxDateTime>(JSContext *cx, const wxDateTime &from)
{
    if ( from.IsValid() )
    {
        return OBJECT_TO_JSVAL(js_NewDateObject(cx, 
	    									    from.GetYear(), 
		    								    from.GetMonth(),
			    							    from.GetDay(),
				    				            from.GetHour(),
					    					    from.GetMinute(),
						    				    from.GetSecond()));
    }
    else
        return JSVAL_VOID;
}



template<>
bool zzzJs::ToJSVal<wxDateTime>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxDateTime &from)
{
    if ( from.IsValid() )
    {
		v.setObjectOrNull(js_NewDateObject(cx, 
	    									    from.GetYear(), 
		    								    from.GetMonth(),
			    							    from.GetDay(),
				    				            from.GetHour(),
					    					    from.GetMinute(),
						    				    from.GetSecond()));
/*
        return OBJECT_TO_JSVAL(js_NewDateObject(cx, 
	    									    from.GetYear(), 
		    								    from.GetMonth(),
			    							    from.GetDay(),
				    				            from.GetHour(),
					    					    from.GetMinute(),
						    				    from.GetSecond()));
*/
    }
    else {
		v.setNull();
//        return JSVAL_VOID;
	}
	return true;
}




template<>
JS::Value zzzJs::ToJS<wxArrayString>(JSContext *cx, const wxArrayString &from)
{
    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);
    for(size_t i = 0; i < from.GetCount(); i++)
    {
	    JS::Value element = ToJS(cx, from.Item(i));
	    JS_SetElement(cx, objArray, i, &element);
    }
//  JS_RemoveRoot(cx, &objArray);
    return OBJECT_TO_JSVAL(objArray);
}




template<>
JS::Value zzzJs::ToJS<wxArrayInt>(JSContext *cx, const wxArrayInt &from)
{
    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);
    for(size_t i = 0; i < from.GetCount(); i++)
    {
	    JS::Value element = ToJS(cx, from.Item(i));
	    JS_SetElement(cx, objArray, i, &element);
    }
//  JS_RemoveRoot(cx, &objArray);
    return OBJECT_TO_JSVAL(objArray);
}

template<>
bool zzzJs::ToJSVal<wxArrayInt>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxArrayInt &from)
{

    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);
    for(size_t i = 0; i < from.GetCount(); i++)
    {
	    JS::Value element = ToJS(cx, from.Item(i));
	    JS_SetElement(cx, objArray, i, &element);
    }
	v.setObjectOrNull(objArray);

	return true;
}


template<>
bool zzzJs::ToJSVal<wxArrayString>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxArrayString &from)
{
    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);
    for(size_t i = 0; i < from.GetCount(); i++)
    {
	    JS::Value element = ToJS(cx, from.Item(i));
	    JS_SetElement(cx, objArray, i, &element);
    }
//  JS_RemoveRoot(cx, &objArray);
	v.setObjectOrNull(objArray);
//    return OBJECT_TO_JSVAL(objArray);
	return true;
}

template<>
JS::Value zzzJs::ToJS<wxStringList>(JSContext *cx, const wxStringList &from)
{
    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);

    int i = 0;
    wxStringListNode *node = from.GetFirst();
    while(node)
    {
        wxString s(node->GetData()); 
	    
        JS::Value element = ToJS(cx, s);
	    JS_SetElement(cx, objArray, i++, &element);

        node = node->GetNext();
    }
    //JS_RemoveRoot(cx, &objArray);
    return OBJECT_TO_JSVAL(objArray);
}



template<>
bool zzzJs::ToJSVal<wxStringList>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxStringList &from)
{
    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);

    int i = 0;
    wxStringListNode *node = from.GetFirst();
    while(node)
    {
        wxString s(node->GetData()); 
	    
        JS::Value element = ToJS(cx, s);
	    JS_SetElement(cx, objArray, i++, &element);

        node = node->GetNext();
    }
    //JS_RemoveRoot(cx, &objArray);
	v.setObjectOrNull(objArray);
//    return OBJECT_TO_JSVAL(objArray);
	return true;
}

template<>
JS::Value zzzJs::ToJS<wxVariant>(JSContext* cx, const wxVariant &from)
{
	JS::Value ret;
	ConvertWxVariant2Js(cx, from, ret);
	return ret;
}
template<>
bool zzzJs::ToJSVal<wxVariant>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxVariant &from)
{
	JS::Value ret;
	return ConvertWxVariant2Js(cx, from, ret);
}














bool zzzJs::ConvertJs2WxVariant(JSContext *cx, JS::Value& v, wxVariant& to)
{

	if( v.isBoolean() ) {
		to = v.toBoolean();
	} else 
	if( v.isDouble() ) {
		double dVal = v.toDouble();
		float f, f2;
		f2 = modff(dVal, &f);
		if( f2 == 0 ) {
			int64_t b = -1;
			if( JS::ToInt64(cx, v, &b) == true ) {
				to.GetLongLong() = b;
			} else {
				to = dVal;
			}
		} else {
			to = dVal;
		}		
	} else 
	if( v.isInt32() ) {
		to = (long)v.toInt32();
	} else 
	if( v.isString() ) {
		wxString str;
		FromJS<wxString>(cx, v, str);
		to = str;
	} else 
	if( v.isObject() ) {
		JSObject *obj = JSVAL_TO_OBJECT(v);
		if( obj == NULL ) {
			JS_ReportError(cx, "non suport data type. objectt is null.");
			return false;
		}
		if( JS_IsArrayObject(cx, obj) == JS_TRUE ) {
			wxArrayString arrayStr;
			FromJS(cx, v, arrayStr);
			to = arrayStr;
		} 
	} else {
		JS_ReportError(cx, "non suport data type.");
		return false;
	}
	
	return true;
}

bool zzzJs::ConvertWxVariant2Js(JSContext *cx, const wxVariant& v, JS::Value& to)
{
	//long
	//double
	//bool
	//char
	//string
	//wxObject
	//void*
	//datetime
	//arrstring
	//longlong
	//ulonglong
	//list
	if( v.IsType(_T("bool")) ) {
		to.setBoolean(
			(bool)v
		);
	} else
	if( v.IsType(_T("double")) ) {
		to.setDouble(
			(double)v
		);
	} else
	if( v.IsType(_T("long")) ) {
		to.setInt32(
			(long)v
		);
	} else
	if( v.IsType(_T("string")) ) {
		wxString str = (wxString)v;
		to = ToJS<wxString>(cx, (wxString)v);
	} else
	if( v.IsType(_T("arrstring")) ) {
		to = ToJS(cx, (wxArrayString)v);
	} else
	if( v.IsType(_T("longlong")) ) {
		int64_t value = (int64_t)v.GetLongLong().GetValue();
		to.setNumber( (double)value );
	} else
	if( v.IsType(_T("longlong")) ) {
		uint64_t value = (uint64_t)v.GetULongLong().GetValue();
		to.setNumber( (double)value );
	} else {
		JS_ReportError(cx, "non suport data type.");
		return false;
	}

	return true;
}
