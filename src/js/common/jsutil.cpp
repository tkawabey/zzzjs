#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#include <jsapi.h>
#include <wx/wx.h>

#include "js/common/jsutil.h"
#include "js/common/defs.h"


JSBool zzzJs::GetFunctionProperty(JSContext *cx, JSObject *obj, const char *propertyName, jsval *property)
{
	if (    JS_GetProperty(cx, obj, propertyName, property) == JS_TRUE 
		 && JS_TypeOfValue(cx, *property) == JSTYPE_FUNCTION ) 
	{
		return JS_TRUE;
	}
	else
	{
		return JS_FALSE;
	}
}

JSBool zzzJs::CallFunctionProperty(JSContext *cx, JSObject *obj, const char *propertyName, uintN argc, jsval* args, jsval *rval)
{
	jsval property;
    if ( ( GetFunctionProperty(cx, obj, propertyName, &property) == JS_TRUE ) )
	{
		if ( JS_CallFunctionValue(cx, obj, property, argc, args, rval) == JS_FALSE )
        {
            if ( JS_IsExceptionPending(cx) )
            {
                JS_ReportPendingException(cx);
            }
            return JS_FALSE;
        }
        return JS_TRUE;
	}
	return JS_FALSE;
}

JSClass* zzzJs::GetClass(JSContext *cx, JSObject *obj, const char* className)
{
	jsval ctor, proto;

	JSObject* pCtr = JS_GetConstructor(cx, obj);
	if( pCtr == NULL ) {
		return NULL;
	}
	JSObject* pParent = JS_GetParent(pCtr);
	if( pParent == NULL ) {
		return NULL;
	}
	
//	if (JS_LookupProperty(cx, JS_GetGlobalObject(cx), className, &ctor) == JS_FALSE)
	if (JS_LookupProperty(cx, pParent, className, &ctor) == JS_FALSE)
		return NULL;

	if( ctor.isObject() == false ) {
		return NULL;
	}

	if (JS_LookupProperty(cx, JSVAL_TO_OBJECT(ctor), "prototype", &proto) == JS_FALSE)
		return NULL;

	JSObject *protoObj = JSVAL_TO_OBJECT(proto);
	
	return JS_GetClass(protoObj);//JS_GET_CLASS(cx, protoObj);
}

bool zzzJs::HasPrototype(JSContext *cx, JSObject *obj, const char *className)
{
    JSClass *jsclass = GetClass(cx, obj, className);
    if ( jsclass == NULL )
        return false;

	JSObject *prototype = NULL;//S_GetPrototype(cx, obj);
	JSBool b = JS_GetPrototype(cx, obj, &prototype);
	while(    prototype != NULL
		   && JS_InstanceOf(cx, prototype, jsclass, NULL) == JS_FALSE )
	{
		//prototype = JS_GetPrototype(cx, prototype)
		b = JS_GetPrototype(cx, prototype, &prototype);
		if( b == JS_FALSE ) {
			prototype = NULL;
		}
	}
	return prototype != NULL;
}

bool zzzJs::HasPrototype(JSContext *cx, jsval v, const char *className)
{
//    if ( JSVAL_IS_OBJECT(v) )
	if( v.isObjectOrNull() )
        return HasPrototype(cx, JSVAL_TO_OBJECT(v), className);
    else
        return false;
}

bool zzzJs::GetScriptRoot(JSContext *cx, jsval *v)
{
//  if ( JS_GetProperty(cx, JS_GetGlobalObject(cx), "script", v) == JS_TRUE )
  if ( JS_GetProperty(cx, JS_GetGlobalForScopeChain(cx), "script", v) == JS_TRUE )
  {
    //if ( JSVAL_IS_OBJECT(*v) )
	if( v->isObjectOrNull() )
    {
      JSObject *obj = JSVAL_TO_OBJECT(*v);
      return JS_GetProperty(cx, obj, "root", v) == JS_TRUE;
    }
  }
  return false;
}

JSBool zzzJs::wxDefineProperty(JSContext *cx, 
                              JSObject *obj, 
                              const wxString &propertyName, 
                              jsval *propertyValue)
{
    wxCSConv conv(WXJS_INTERNAL_ENCODING);
    int length = propertyName.length();
    wxCharBuffer s = propertyName.mb_str(conv);
    
/*
    int jsLength = utf16.WC2MB(NULL, propertyName, 0);
    char *jsValue = new char[jsLength + conv.GetMBNulLen()];
    jsLength = conv.WC2MB(jsValue, propertyName, jsLength + conv.GetMBNulLen());
    JSBool ret = JS_DefineUCProperty(cx, obj, (jschar *) jsValue, jsLength / conv.GetMBNulLen(), 
                                     *propertyValue, NULL, NULL, JSPROP_ENUMERATE);
    delete[] jsValue;
    return ret;
*/
    return JS_DefineUCProperty(cx, obj, (const jschar *) s.data(), length, 
                               *propertyValue, NULL, NULL, JSPROP_ENUMERATE);
}

JSBool zzzJs::wxGetProperty(JSContext *cx, 
                           JSObject *obj, 
                           const wxString &propertyName, 
                           jsval *propertyValue)
{
  wxCSConv conv(WXJS_INTERNAL_ENCODING);
  int length = propertyName.length();
  wxCharBuffer s = propertyName.mb_str(conv);

  return JS_GetUCProperty(cx, obj, 
                         (const jschar *) s.data(), length, propertyValue);
}

JSBool zzzJs::wxSetProperty(JSContext *cx, 
                           JSObject *obj, 
                           const wxString &propertyName, 
                           jsval *propertyValue)
{
  wxCSConv conv(WXJS_INTERNAL_ENCODING);
  int length = propertyName.length();
  wxCharBuffer s = propertyName.mb_str(conv);

  return JS_SetUCProperty(cx, obj, 
                         (const jschar *) s.data(), length, propertyValue);
}


JSBool zzzJs::GetPropertyWhenPresent(JSContext *cx, 
                        JSObject *obj, 
                        const wxString &propertyName, 
                        jsval *propertyValue)
{
	JSBool bFound;
	wxCSConv conv(WXJS_INTERNAL_ENCODING);
	int length = propertyName.length();
	wxCharBuffer s = propertyName.mb_str(conv);

	if( JS_HasUCProperty(cx, obj, (const jschar *) s.data(), length, &bFound) == JS_FALSE) {
		return JS_FALSE;
	}
	if( bFound == JS_FALSE ) {
		return JS_FALSE;
	}
	return JS_GetUCProperty(cx, obj, 
							(const jschar *) s.data(), length, propertyValue);
}


