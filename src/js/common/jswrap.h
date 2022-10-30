#ifndef ___ZZZ_JS_COMMON_JS_WRAP_H___
#define ___ZZZ_JS_COMMON_JS_WRAP_H___


#include <map>
#include <string>
#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/type.h"
#include "js/common/conf.h"
#include "js/common/defs.h"
#include "js/gui/errors.h"

namespace zzzJs
{

// Utile Macro
	
#define ZZZJS_CHECK_PRIM_NULL(P)	if( P == NULL ) {\
			JS_ReportError(cx, "Internal Error.");\
			return JS_FALSE;\
		}
#define ZZZJS_CHECK_ARG_COUNT(MIN, MAX)	if( argc > MAX ) {\
			argc = MAX;\
		}\
		if( argc < MIN ) {\
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);\
			return JS_FALSE;\
		}

#define ZZZJS_ARG_FROMJS(VALUE) FromJS(cx, argv[argIndex], VALUE)

#define ZZZJS_ARG_FROMJS_CHK_AND_ERROR(VALUE, TYPE_NAME)	 if ( ! FromJS(cx, argv[argIndex], VALUE) ) \
		{\
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, TYPE_NAME);\
			return JS_FALSE;\
		}
#define ZZZJS_ARG_AP_CHK_AND_ERROR(AP, CLASS)	 if ( AP.set(CLASS ## ::getObject2Instance(cx, argv[argIndex], AP.bAllocation)) == false ) \
		{\
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, CLASS ## ::getClassName() );\
			return JS_FALSE;\
		}

#define ZZZJS_ARG_GET_PRIVATE(pOBJ, CLASS)	pOBJ = CLASS ## ::GetPrivate(cx, argv[argIndex], false)
#define ZZZJS_ARG_GET_AP(AP, CLASS)	AP.set(CLASS ## ::getObject2Instance(cx, argv[argIndex], AP.bAllocation))
	


// プロパティ関係
#define ZZZJS_PROP_FROMJS_CHK_AND_ERROR(VALUE, TARGET, NAME, TYPE)  if( GetPropertyWhenPresent( cx, TARGET, _T(##NAME##), &v) == JS_FALSE )  \
		{	\
			ReportError_PropMustError(cx, NAME);\
			return JS_FALSE;\
		}\
		if( FromJS(cx, v, VALUE) == false ) {\
			ReportError_PropTypeError(cx, NAME, TYPE);\
			return JS_FALSE;\
		}	

#define ZZZJS_PROP_FROMJS_IF_EXIST(VALUE, TARGET, NAME, TYPE)  if( GetPropertyWhenPresent( cx, TARGET, _T(##NAME##), &v) == JS_TRUE )  {\
			if( FromJS(cx, v, VALUE ) == false ) {\
				ReportError_PropTypeError(cx, NAME, TYPE);\
				return JS_FALSE;\
			}\
		}

#define ZZZJS_PROP_PRIVATE_IF_EXIST(pOBJ, TARGET, CLASS, NAME, TYPE)  if( GetPropertyWhenPresent( cx, TARGET, _T(##NAME##), &v) == JS_TRUE )  {\
			if( (pOBJ = CLASS ## ::GetPrivate(cx, v)) == NULL ) { \
				ReportError_PropTypeError(cx, NAME, TYPE);\
				return JS_FALSE;\
			}\
		}

#define ZZZJS_PROP_GET_AP(AP, CLASS, TARGET)	AP.set(CLASS ## ::getObject2Instance(cx, TARGET, AP.bAllocation))
#define ZZZJS_PROP_AP_IF_EXIST(AP, CLASS, NAME)  if( GetPropertyWhenPresent( cx, obj, _T(##NAME##), &v) == JS_TRUE )  {\
			if( AP.set(CLASS ## ::getObject2Instance(cx, v, AP.bAllocation)) == false ) { \
				ReportError_PropTypeError(cx, NAME, CLASS ## ::getClassName());\
				return JS_FALSE;\
			}\
		}
#define ZZZJS_PROP_AP_CHK_AND_ERROR(AP, TARGET, CLASS, NAME)  if( GetPropertyWhenPresent( cx, TARGET, _T(##NAME##), &v) == JS_FALSE )  \
		{	\
			ReportError_PropMustError(cx, NAME);\
			return JS_FALSE;\
		}\
		if( AP.set(CLASS ## ::getObject2Instance(cx, v, AP.bAllocation)) == false ) { \
			ReportError_PropTypeError(cx, NAME, CLASS ## ::getClassName() );\
			return JS_FALSE;\
		}	


#define ZZZJS_FUNC_ENT		try {
#define ZZZJS_FUNC_EXIT		} catch(...) { JS_ReportError(cx, "unkown exception. FILE:%s(%d)", __FILE__, __LINE__); }





	template<class _Ty>
	class zzzJsPtr
	{	// wrap an object pointer to ensure destruction
	public:
	typedef zzzJsPtr<_Ty> _Myt;
	typedef _Ty element_type;

	explicit zzzJsPtr(_Ty *_Ptr = 0, const _Ty* _Def = 0) _THROW0()
		: m_pPtr(_Ptr) 
		, m_pDef(_Def)
		, bAllocation( false )
		{	// construct from object pointer
		}

	zzzJsPtr(_Myt& _Right) _THROW0()
		: m_pPtr(_Right.release()) , bAllocation( false )
		{	// construct by assuming pointer from _Right zzzJsPtr
		}


	template<class _Other>
		operator zzzJsPtr<_Other>() _THROW0()
		{	// convert to compatible zzzJsPtr
		return (zzzJsPtr<_Other>(*this));
		}


	template<class _Other>
		_Myt& operator=(zzzJsPtr<_Other>& _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	template<class _Other>
		zzzJsPtr(zzzJsPtr<_Other>& _Right) _THROW0()
		: m_pPtr(_Right.release())
		{	// construct by assuming pointer from _Right
		}

	_Myt& operator=(_Myt& _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}


	~zzzJsPtr() _NOEXCEPT
		{	// destroy the object
			if( bAllocation == true ) {
				delete m_pPtr;
			}
		}

	_Ty& operator*() const _THROW0()
		{	// return designated value
			return (*get());
		}


	_Myt& operator=(_Ty* _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
			m_pPtr = _Right;
			return (*this);
		}


	_Ty *operator->() const _THROW0()
		{	// return pointer to class object
 		return (get());
		}

	_Ty *get() const _THROW0()
		{	// return wrapped pointer
			if( m_pPtr == NULL ) {
				return (_Ty*)m_pDef;
			}
			return (m_pPtr);
		}

	_Ty *release() _THROW0()
		{	// return wrapped pointer and give up ownership
		_Ty *_Tmp = m_pPtr;
		m_pPtr = 0;

		if( _Tmp == NULL ) {
			return (_Ty*)m_pDef;
		}
		return (_Tmp);
		}

	void reset(_Ty *_Ptr = 0)
	{	// destroy designated object and store new pointer
		if (_Ptr != m_pPtr) {
			if( bAllocation == true ) {
				delete m_pPtr;
			}
		}
		m_pPtr = _Ptr;
	}
	bool set(_Ty *_Ptr = 0)
	{	// destroy designated object and store new pointer
		if (_Ptr != m_pPtr) {
			if( bAllocation == true ) {
				delete m_pPtr;
			}
		}
		m_pPtr = _Ptr;
		return m_pPtr != NULL;
	}

	bool	bAllocation;
private:

	_Ty *m_pPtr;	// the wrapped object pointer
	const _Ty *m_pDef;	// the wrapped object pointer
};












	template<class T_Port, class T_Priv>
	class JsWrapper
	{
	private:
		/**
		* コンストラクタの引数
		*/
		static int gs_ctorArguments;
		/**
		 * クラスのプロトタイプ
		 */
		static JSObject *gs_classProto;

		/**
		 *  クラス名
		 */
		static const char* gs_ClassName;

		/**
		 * The JSClass structure
		 */
		static JSClass gs_class;


	public:
		typedef JsWrapper<T_Port, T_Priv> TOBJECT;

		static std::map<std::string, int>		gs_mapProp;

		static const char* getClassName() { return gs_ClassName;}


		static void ReportError_PropMustError(JSContext *cx, const char* p_name)
		{
			JS_ReportError(cx, "%s property  must specify.", p_name);
		}
		static void ReportError_PropTypeError(JSContext *cx, const char* p_name, const char* p_type)
		{
			JS_ReportError(cx, "%s property  must be of type %s", p_name, p_type);
		}

		/**
		 * Creates an object for the given WX class. From now
		 * on wxJS owns the pointer to the WX class. So don't delete it.
		 */
		static jsval CreateObject(JSContext *cx, 
								T_Priv *p, 
								JSObject *parent = NULL)
		{
			JSObject *obj = JS_NewObject(cx, &gs_class, gs_classProto, parent);
			if ( obj == NULL )
				return JSVAL_NULL;

			JS_SetPrivate(/*cx, */obj, p);
			return OBJECT_TO_JSVAL(obj);
		}

		// A type-safe SetPrivate method
		static void SetPrivate(JSContext *cx, JSObject *obj, T_Priv *p)
		{
			JS_SetPrivate(/*cx,*/ obj, p);
		}

		/**
		* Creates an object for the given WX class and defines it as a 
		* property of the given object. From now on wxJS owns the pointer
		* to the WX class. So don't delete it.
		*/
		static JSObject* DefineObject(JSContext *cx, 
									JSObject *obj, 
									const char *name, 
									T_Priv *p)
		{
			JSObject *propObj = JS_DefineObject(cx, obj, name,
												&gs_class, gs_classProto, 
												JSPROP_READONLY | JSPROP_PERMANENT);
			if ( propObj )
			{
				JS_SetPrivate(/*cx,*/ propObj, p);
			}
			return propObj;
		}

      /**
       * Returns the ported class from the private data of an object.
       * When check is true, it will check the type of the class and
       * returns NULL, when the class is not of the correct type.
       */
		static T_Priv* GetPrivate(JSContext *cx, 
								JSObject *obj, 
								bool check = true)
		{
			JS::RootedObject proto(cx);
			T_Priv *p = NULL;

//			if ( check )
			{
				if (  
					! (    JS_InstanceOf(cx, obj, &gs_class, NULL)
					|| HasPrototype(cx, obj)) 
				)
				{
					/*
					JS_ReportError(cx, 
						"The object should be an instance of %s", 
						gs_ClassName);
					*/
					return NULL;
				}
			}

			//JSClass *clazz = JS_GetClass(cx, obj);
			JSClass *clazz = JS_GetClass(obj);
			if ( clazz == NULL )
				return NULL;

			while((clazz->flags & JSCLASS_HAS_PRIVATE) != JSCLASS_HAS_PRIVATE)
			{

				if(!JS_GetPrototype(cx, obj, proto.address()))
					return NULL;
				obj = proto.get();
				//           obj = JS_GetPrototype(cx, obj);
				if ( obj == NULL )
					return NULL;


//           clazz = JS_GetClass(cx, obj);
				clazz = JS_GetClass(obj);
				if ( clazz == NULL )
					return NULL;
			}

//         p = (T_Priv*) JS_GetPrivate(cx, obj);
			p = (T_Priv*) JS_GetPrivate(obj);

			return p;
		}

		/**
		　* Returns the ported class from the private data of an object.
		　* Does the same as above, but for an object which is stored in a jsval.
		　*/
		static T_Priv* GetPrivate(JSContext *cx, jsval v, bool check = true)
		{
			if (    JSVAL_IS_VOID(v)  || JSVAL_IS_NULL(v) )
			{
				return NULL;
			}
			if( v.isObjectOrNull() == false ) {
				return NULL;
			}
			return JSVAL_TO_OBJECT(v) != NULL ? GetPrivate(cx, JSVAL_TO_OBJECT(v), check)  : NULL;
		}

      /**
       *  Returns true when the prototype of the object is this class.
       */
      static bool HasPrototype(JSContext *cx, JSObject *obj)
      {
		  JS::RootedObject proto(cx);
//        JSObject *prototype = JS_GetPrototype(cx, obj);
		JSObject *prototype = NULL;

		if(!JS_GetPrototype(cx, obj, proto.address()))
			return NULL;
		prototype = proto.get();

        while(   prototype != NULL
              && JS_InstanceOf(cx, prototype, &gs_class, NULL)== JS_FALSE )
        {

			if(!JS_GetPrototype(cx, prototype, proto.address()))
				return NULL;
//          prototype = JS_GetPrototype(cx, prototype, proto.address());
			prototype = proto.get();
        }
		
        return proto.get() != NULL;
      }

      /**
       * Same as above, but for an object that is stored in a jsval
       */
      static bool HasPrototype(JSContext *cx, jsval v)
      {
		  return v.isObject() ? HasPrototype(cx, JSVAL_TO_OBJECT(v))
                                  : false;
      }
		/**
		 *	@brief	クラスを定義する
		 */
		static JSObject* define_Class(JSContext *cx, 
							JSObject *obj,
							JSObject *proto = NULL)

		{
			JSAutoCompartment transaction(cx, obj);	// トランザクション

			gs_classProto = JS_InitClass(cx
				, obj
				, proto
				, &gs_class
				, T_Port::JSConstructor
				, gs_ctorArguments
				, NULL, NULL, NULL, NULL);
			if ( gs_classProto != NULL )
			{
				T_Port::DefineProperties(cx, gs_classProto);
				T_Port::DefineMethods(cx, gs_classProto);

				JSObject *ctor = JS_GetConstructor(cx, gs_classProto);
				if ( ctor != NULL )
				{
					T_Port::DefineConstants(cx, ctor);
					T_Port::DefineStaticProperties(cx, ctor);
					T_Port::DefineStaticMethods(cx, ctor);
				}
				T_Port::InitClass(cx, obj, gs_classProto);
			}
			return gs_classProto;
		}
		
      /**
       * Default implementation for adding a property
       * Returning false, will end the execution of the script. 
       * The default implementation returns true.
       */
      static bool AddProperty(T_Priv* WXUNUSED(p), 
                              JSContext* WXUNUSED(cx), 
                              JSObject* WXUNUSED(obj), 
                              const wxString& WXUNUSED(prop),
                              JS::MutableHandle<JS::Value>& vp)
      {
        return true;
      }

      /**
       * Default implementation for deleting a property
       * Returning false, will end the execution of the script. 
       * The default implementation returns true.
       */
      static bool DeleteProperty(T_Priv* WXUNUSED(p), 
                                 JSContext* WXUNUSED(cx), 
                                 JSObject* WXUNUSED(obj), 
                                 const wxString& WXUNUSED(prop))
      {
        return true;
      }

      /**
       *  The default implementation of the Get method for a ported object.
       *  Overwrite this method when your object has properties.
       *  Returning false, will end the execution of the script. 
       *  The default implementation returns true.
       */
      static bool GetProperty(T_Priv* WXUNUSED(p),
                              JSContext* WXUNUSED(cx),
                              JSObject* WXUNUSED(obj),
                              int WXUNUSED(id),
                              JS::MutableHandle<JS::Value>& vp)
      {
        return true;
      }

      /**
       *  The default implementation of the Get method for a ported object.
       *  Overwrite this method when your object has properties.
       *  Returning false, will end the execution of the script. 
       *  The default implementation returns true.
       */
      static bool GetStringProperty(T_Priv* WXUNUSED(p),
                                    JSContext* WXUNUSED(cx),
                                    JSObject* WXUNUSED(obj),
                                    const wxString& WXUNUSED(propertyName), 
                                    JS::MutableHandle<JS::Value>& vp)
      {
        return true;
      }

      /**
       *  The default implementation of the Set method for a ported object.
       *  Overwrite this method when your object has properties.
       *  @remark Returning false, will end the execution of the script. 
       *  The default implementation returns true.
       */
      static bool SetProperty(T_Priv* WXUNUSED(p),
                              JSContext* WXUNUSED(cx),
                              JSObject* WXUNUSED(obj),
                              int WXUNUSED(id),
                              JS::MutableHandle<JS::Value>& vp)
      {
        return true;
      }

      static bool SetStringProperty(T_Priv* p,
                                    JSContext* cx, 
                                    JSObject* obj,
                                    const wxString& propertyName,
                                    JS::MutableHandle<JS::Value>& vp)
      {
		std::map<std::string, int>::iterator ite = gs_mapProp.find((const char*)propertyName);
		if( ite != gs_mapProp.end() ) {
			return T_Port::SetProperty(p, cx, obj, (*ite).second, vp);
		}
        return true;
      }

      static bool Resolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id)
      {
        return true;
      }

      /**
       *  The default implementation of the Destruct method. Overwrite this
       *  when you need to do some cleanup before the object is destroyed.
       *  The default implementation calls the destructor of the private 
       *  object.
       */
		static void Destruct(T_Priv* p, JSObject *obj)
		{
			try {
				if( p != NULL ) {
					delete p;
				}
			} catch( ... ) {
				wxString strCLSName = gs_ClassName;
				wxLogDebug(_T("exception Destruct %s"), (const TCHAR*)strCLSName);
			}
			p = NULL;
		}

      /**
       *  The default implementation of the Construct method. Overwrite this 
       *  when a script is allowed to create an object with the new statement.
       *  The default implementation returns NULL, which means that is not 
       *  allowed to create an object.
       */
      static T_Priv* Construct(	JSContext* WXUNUSED(cx), 
								JSObject* WXUNUSED(obj),
								unsigned int WXUNUSED(argc),
								JS::Value* WXUNUSED(vp), 
								bool WXUNUSED(constructing))
      {
        return NULL;
      }

      /**
       *  Default implementation for defining properties.
       *  Use the WXJS_DECLARE_PROPERTY_MAP, WXJS_BEGIN_PROPERTY_MAP and
       *  WXJS_END_PROPERTY_MAP macro's for hiding the complexity of 
       *  defining properties. The default implementation does nothing.
       */
      static void DefineProperties(JSContext* WXUNUSED(cx),
                                   JSObject* WXUNUSED(obj))
      {
      }

      /**
       * InitClass is called when the prototype object is created
       * It can be used for example to initialize constants related to 
       * this class.
       * The argument obj is normally the global object.
       * The default implementation does nothing.
       */
      static void InitClass(JSContext* WXUNUSED(cx),
                            JSObject* WXUNUSED(obj),
                            JSObject* WXUNUSED(proto))
      {
      }

      /**
       *  Default implementation for defining methods.
       *  Use the WXJS_DECLARE_METHOD_MAP, WXJS_BEGIN_METHOD_MAP and
       *  WXJS_END_METHOD_MAP macro's for hiding the complexity of 
       *  defining methods.
       *  The default implementation does nothing.
       */
      static void DefineMethods(JSContext* WXUNUSED(cx),
                                JSObject* WXUNUSED(obj))
      {
      }

      /**
       *  Default implementation for defining constants.
       *  Use the WXJS_DECLARE_CONSTANT_MAP, WXJS_BEGIN_CONSTANT_MAP and
       *  WXJS_END_CONSTANT_MAP macro's for hiding the complexity of
       *  defining constants.
       *  The default implementation does nothing.
       *  Only numeric constants are allowed.
       */
      static void DefineConstants(JSContext* WXUNUSED(cx),
                                  JSObject* WXUNUSED(obj))
      {
      }

      /**
       *  Default implementation for defining static(class) properties.
       *  Use the WXJS_DECLARE_STATIC_PROPERTY_MAP, 
       *  WXJS_BEGIN_STATIC_PROPERTY_MAP and WXJS_END_PROPERTY_MAP macro's 
       *  for hiding the complexity of defining properties.
       *  The default implementation does nothing.
       */
      static void DefineStaticProperties(JSContext* WXUNUSED(cx),
                                         JSObject* WXUNUSED(obj))
      {
      }

      /**
       *  Default implementation for defining static(class) methods.
       *  Use the WXJS_DECLARE_STATIC_METHOD_MAP, WXJS_BEGIN_STATIC_METHOD_MAP
       *  and WXJS_END_METHOD_MAP macro's for hiding the complexity of 
       *  defining methods.
       *  The default implementation does nothing.
       */
      static void DefineStaticMethods(JSContext* WXUNUSED(cx),
                                      JSObject* WXUNUSED(obj))
      {
      }

      /**
       * Returns the JSClass of the object
       */
      static JSClass* GetClass()
      {
        return &gs_class;
      }

      /**
       *  The default implementation of the static Get method for a ported 
       *  object. Overwrite this method when your object has static 
       *  properties.
       *  Returning false, will end the execution of the script. 
       *  The default implementation returns true.
       */
      static bool GetStaticProperty(JSContext* WXUNUSED(cx),
                                    int WXUNUSED(id),
                                    JS::MutableHandle<JS::Value>& vp)
      {
        return true;
      }

      /**
       *  The default implementation of the static Set method for a ported 
       *  object.
       *  Overwrite this method when your object has static properties.
       *  Returning false, will end the execution of the script. 
       *  The default implementation returns true.
       */
      static bool SetStaticProperty(JSContext* WXUNUSED(cx), 
                                    int WXUNUSED(id),
                                    JS::MutableHandle<JS::Value> &vp)
      {
        return true;
      }

      static bool Enumerate(T_Priv* WXUNUSED(p),
                            JSContext* WXUNUSED(cx),
                            JSObject* WXUNUSED(obj),
                            JSIterateOp WXUNUSED(enum_op),
                            jsval* WXUNUSED(statep),
                            jsid* WXUNUSED(idp))
      {
        return true;
      }

      // The JS API callbacks

      static JSBool JSGetStaticProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JS::MutableHandle<JS::Value> vp)
      {
			jsval idVal;
			if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( idVal.isInt32() == true ) 
			{
				return T_Port::GetStaticProperty(cx, idVal.toInt32(), vp) ? JS_TRUE 
						: JS_FALSE;
			}
			//if( JSID_IS_INT( id ) ) {
			//	return T_Port::GetStaticProperty(cx, id, vp) ? JS_TRUE 
			//			: JS_FALSE;
			//}
/*
		if ( id )
        {
          return T_Port::GetStaticProperty(cx, JSVAL_TO_INT(id), vp) ? JS_TRUE 
                                                                     : JS_FALSE;
        }
*/
        return JS_TRUE;
      }

      static JSBool JSSetStaticProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool strict, JS::MutableHandle<JS::Value> vp)
      {
			if( JSID_IS_INT( id ) ) {
				return T_Port::SetStaticProperty(cx, id, vp) ? JS_TRUE 
															: JS_FALSE;
			}
/*
        if ( JSVAL_IS_INT(id) )
        {
          return T_Port::SetStaticProperty(cx, JSVAL_TO_INT(id), vp) ? JS_TRUE 
                                                                     : JS_FALSE;
        }
*/
        return JS_TRUE;
      }

      static JSObject *GetClassPrototype()
      {
          return gs_classProto;
      }




	private:

		/**
		* Enumeration callback
		*/
		static JSBool JSEnumerate(JSContext *cx, JS::Handle<JSObject*> obj)
		//static JSBool JSEnumerate(JSContext *cx, JSObject *obj,
		//	JSIterateOp enum_op,
		//	jsval *statep, jsid *idp)
		{
			JSBool res = JS_TRUE;
			T_Priv *p = (T_Priv *) GetPrivate(cx, obj, false);
			if ( p != NULL )
			{
				JSIterateOp enum_op = JSENUMERATE_INIT;
				jsval (statep);
				jsid (idp);
				res = T_Port::Enumerate(p, cx, obj, enum_op, &statep, &idp) 
							? JS_TRUE : JS_FALSE;
			}
			return res;
		}

		/**
		 *  AddProperty callback. This will call the AddProperty method of 
		 *  the ported object.
		 */
		static JSBool JSAddProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
				JS::MutableHandle<JS::Value> vp)
		{
			jsval idVal;
			if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( idVal.isString() == true ) 
//			if (JSVAL_IS_STRING(id)) 
			{
				T_Priv *p = (T_Priv *) GetPrivate(cx, obj, false);
				if ( p != NULL )
				{
					wxString str("");
					zzzJs::FromJS(cx, idVal, str);
					JSBool res = T_Port::AddProperty(p, cx, obj, str, vp) ? JS_TRUE 
															: JS_FALSE;
					return res;
				}
			}
			return JS_TRUE;
		}

		/**
		 *  AddProperty callback. This will call the AddProperty method of 
		 *  the ported object.
		 */
		static JSBool JSDeleteProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
		JSBool *succeeded)
		{
			jsval idVal;
			if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( idVal.isString() == true ) 
//			if (JSVAL_IS_STRING(id)) 
			{
				T_Priv *p = (T_Priv *) GetPrivate(cx, obj, false);
				if ( p != NULL )
				{
					wxString str("");
					FromJS(cx, idVal, str);
					JSBool res = T_Port::DeleteProperty(p, cx, obj, str) ? JS_TRUE 
															: JS_FALSE;
					return res;
				}
			}
			return JS_TRUE;
		}

		/**
		*  GetProperty callback. This will call the Get method of the 
		*  ported object.
		*/
		static JSBool JSGetProperty(JSContext *cx, JS::Handle<JSObject*> obj, 
			JS::Handle<jsid> id, 
			JS::MutableHandle<JS::Value> vp)
		{
			T_Priv *p = (T_Priv *) GetPrivate(cx, obj, false);
			jsval idVal;

			if( p == NULL ) {
				return JS_FALSE;
			}

			if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( idVal.isInt32() == true ) 
//			if (JSVAL_IS_INT(id)) 
			{
//				return T_Port::GetProperty(p, cx, obj, JSVAL_TO_INT(id), vp) 
//					? JS_TRUE : JS_FALSE; 
				return T_Port::GetProperty(p, cx, obj, idVal.toInt32(), vp) 
					? JS_TRUE : JS_FALSE; 
			}
			else
			{
				if( idVal.isString() == true ) 
//				if (JSVAL_IS_STRING(id)) 
				{
					wxString str("");
					FromJS(cx, idVal, str);
					JSBool res = T_Port::GetStringProperty(p, cx, obj, str, vp) ? JS_TRUE 
																: JS_FALSE;
					return res;
				}
			} 
			return JS_TRUE;
		}

		/**
		 *  SetProperty callback. This will call the Set method of the ported
		 *  object.
		 */
		static JSBool JSSetProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, 
				JSBool strict, 
				JS::MutableHandle<JS::Value> vp)
		{
			T_Priv *p = (T_Priv *) GetPrivate(cx, obj, false);
			
			if( p == NULL ) {
				return JS_FALSE;
			}
			jsval idVal;
			if( JS_IdToValue(cx, id, &idVal) == JS_FALSE ) {
				return JS_FALSE;
			}
			if( idVal.isInt32() == true ) 
//			if (JSVAL_IS_INT(id)) 
			{
				return T_Port::SetProperty(p, cx, obj, idVal.toInt32(), vp) 
					? JS_TRUE : JS_FALSE; 
			}
			else
			{
				if( idVal.isString() == true ) 
//				if (JSVAL_IS_STRING(id)) 
				{
					wxString str("");
					FromJS(cx, idVal, str);
					JSBool res = T_Port::SetStringProperty(p, cx, obj, str, vp) 
					? JS_TRUE : JS_FALSE;
					return res;
				}
			} 
		return JS_TRUE;
		}

		static JSBool JSResolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id)
		{
			return T_Port::Resolve(cx, obj, id) ? JS_TRUE : JS_FALSE;
		}

		/**
		*  Constructor callback. This will call the static Construct 
		*  method of the ported object.
		*  When this is not available, the ported object can't be created 
		*  with a new statement in JavaScript.
		*/
		static JSBool JSConstructor(JSContext *cx, 
				unsigned argc, JS::Value *vp)
		{
//			JS::RootedObject obj(cx, JS_NewObjectForConstructor(cx, &gs_class, vp) );
			/* SpiderMonkey 31 or older
			 * JSObject *obj = JS_NewObjectForConstructor(cx, &gs_class, vp);
			 * aftrer
			 * JSObject *obj = JS_NewObjectForConstructor(cx, &gs_class, args);
			 */
			JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
			JSObject *obj = JS_NewObjectForConstructor(cx, &gs_class, vp);

			// JS_IsConstructing=現在実行中のJSNativeがコンストラクタとして呼び出されたかどうかを判定します。
			T_Priv *p = T_Port::Construct(cx, obj, argc, vp,  JS_IsConstructing(cx, vp) == JS_TRUE);
#ifdef _DEBUG
			wxString strCLSName = gs_ClassName;
			wxLogDebug(_T("__JSConstructor %s (%p)"), (const TCHAR*)strCLSName, p);
#endif
			if ( p == NULL )
			{
				JS_ReportError(cx, "Class %s can't be constructed", gs_ClassName);
				return JS_FALSE;
			}
			JS_SetPrivate(/*cx,*/ obj, p);

    
			/* SpiderMonkey 31 or older
				* JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
				* After
				*   args.rval().setObject(*obj);
				*/
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
			return JS_TRUE;
		}

		/**
		* Destructor callback. This will call the Destruct method of the
		* ported object.
		*/
		static void JSDestructor(JSFreeOp *fop, JSObject *obj)
		{
			T_Priv *p = (T_Priv *) JS_GetPrivate(obj);
			if ( p != NULL )
			{
#ifdef _DEBUG
				wxString strCLSName = gs_ClassName;
				wxLogDebug(_T("~~~JSDestructor %s (%p)"), (const TCHAR*)strCLSName, p);
#endif
				T_Port::Destruct(p, obj);
			}
			JS_SetPrivate(obj, NULL);
		}
	};

}


// The initialisation of gs_class
template<class T_Port, class T_Priv>
JSClass zzzJs::JsWrapper<T_Port, T_Priv>::gs_class =
{ 
    zzzJs::JsWrapper<T_Port, T_Priv>::gs_ClassName,
    JSCLASS_HAS_PRIVATE /*| JSCLASS_NEW_ENUMERATE*/,
    zzzJs::JsWrapper<T_Port, T_Priv>::JSAddProperty,
    zzzJs::JsWrapper<T_Port, T_Priv>::JSDeleteProperty,
    zzzJs::JsWrapper<T_Port, T_Priv>::JSGetProperty,
    zzzJs::JsWrapper<T_Port, T_Priv>::JSSetProperty, 
    (JSEnumerateOp) zzzJs::JsWrapper<T_Port, T_Priv>::JSEnumerate,
    zzzJs::JsWrapper<T_Port, T_Priv>::JSResolve,
    JS_ConvertStub, 
    zzzJs::JsWrapper<T_Port, T_Priv>::JSDestructor,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

// Some usefull macro's that makes the use of JsWrapper easy
// PROPERTY MACROS
//#define ZZZJS_NORMAL   JSPROP_ENUMERATE | JSPROP_PERMANENT 
#define ZZZJS_NORMAL   JSPROP_ENUMERATE 
//#define WXJS_READONLY JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY
#define ZZZJS_READONLY JSPROP_ENUMERATE  | JSPROP_READONLY


// オブジェクトからインスタンスに変換する関数の宣言と実装のラッパーマクロ
#define ZZZJS_DECLARE_O2I(CLS)	static CLS* getObject2Instance(JSContext *cx, JS::Value v, bool& bAllocation);\
			static CLS* getObject2Instance(JSContext *cx, JSObject *obj, bool& bAllocation);

#define ZZZJS_BEGIN_O2I(PRI,CLS)	PRI* CLS::getObject2Instance(JSContext *cx, JS::Value v, bool& bAllocation)\
{\
	bAllocation = false;\
	if( v.isObjectOrNull() == false ) {\
		return NULL;\
	}\
	return CLS::getObject2Instance(cx, v.toObjectOrNull(), bAllocation);\
}\
PRI* CLS::getObject2Instance(JSContext *cx, JSObject *obj, bool& bAllocation)\
{\
	jsval v;\
	PRI* pRet = NULL;\
	bAllocation = false;


#define ZZZJS_END_O2I }

// Declare a property map (use it in headers)
#define ZZZJS_DECLARE_PROPERTY_MAP() \
    static void DefineProperties(JSContext *cx, JSObject *obj);

// Declare a static property map (use it in headers)
#define ZZZJS_DECLARE_STATIC_PROPERTY_MAP() \
    static void DefineStaticProperties(JSContext *cx, JSObject *obj);

// Begins a property map (use it in source files)
#define ZZZJS_BEGIN_PROPERTY_MAP(className) \
    void className::DefineProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

// Ends a property map (use it in source files)
#define ZZZJS_END_PROPERTY_MAP() \
            { 0, 0, 0, 0, 0 } \
        }; \
        JS_DefineProperties(cx, obj, props); \
		for(int i = 0; props[i].name != NULL; i++ ) { \
			gs_mapProp.insert( std::pair<std::string, int>(props[i].name, props[i].tinyid) ); \
		}\
    }

// Begins a static property map
#define ZZZJS_BEGIN_STATIC_PROPERTY_MAP(className) \
    void className::DefineStaticProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

// Defines a property
#define ZZZJS_PROPERTY(id, name) \
    { name, id, ZZZJS_NORMAL, 0, 0 },

// Defines a static property
#define ZZZJS_STATIC_PROPERTY(id, name) \
    { name, id, ZZZJS_NORMAL, JSOP_WRAPPER(JSGetStaticProperty), JSOP_WRAPPER(JSSetStaticProperty) },

// Defines a readonly property
#define ZZZJS_READONLY_PROPERTY(id, name) \
    { name, id, ZZZJS_READONLY, 0, 0 },

// Defines a readonly static property
#define ZZZJS_READONLY_STATIC_PROPERTY(id, name) \
    { name, id, ZZZJS_READONLY, JSGetStaticProperty, 0 },

// Declares a constant map
#define ZZZJS_DECLARE_CONSTANT_MAP() \
    static void DefineConstants(JSContext *cx, JSObject *obj);

// Begins a constant map
#define ZZZJS_BEGIN_CONSTANT_MAP(className)                         \
    void className::DefineConstants(JSContext *cx, JSObject *obj)  \
    {                                                              \
      JSConstDoubleSpec consts[] =                                 \
      {

// Ends a constant map
#define ZZZJS_END_CONSTANT_MAP()                 \
            { 0, 0, 0, { 0 } }                      \
        };                                      \
        JS_DefineConstDoubles(cx, obj, consts); \
    }

// Defines a constant with a prefix
#define ZZZJS_CONSTANT(prefix, name)	{ prefix##name, #name, ZZZJS_READONLY, {0,0,0} },
// Defines a constant
#define ZZZJS_SIMPLE_CONSTANT(name)  { name, #name, ZZZJS_READONLY, {0,0,0} },

// METHOD MACROS
#define ZZZJS_DECLARE_METHOD_MAP() \
        static void DefineMethods(JSContext *cx, JSObject *obj);

#define ZZZJS_BEGIN_METHOD_MAP(className)                         \
    void className::DefineMethods(JSContext *cx, JSObject *obj)  \
    {                                                            \
        JSFunctionSpec methods[] =                               \
        {

#define ZZZJS_END_METHOD_MAP()                  \
            JS_FS_END                  \
        };                                     \
        JS_DefineFunctions(cx, obj, methods);  \
    }
 
#define ZZZJS_METHOD(name, fun, args) \
    JS_FS( name, fun, args, 0 ),

// A macro to reduce the size of the ported classes header.
#define ZZZJS_DECLARE_METHOD(name) static JSBool name(JSContext *cx, unsigned argc, JS::Value *vp);
#define ZZZJS_BEGIN_METHOD(CLS, name)	JSBool CLS::name(JSContext *cx, unsigned argc, JS::Value *vp) { \
	ZZZJS_FUNC_ENT
#define ZZZJS_END_METHOD	ZZZJS_FUNC_EXIT\
		return JS_FALSE;	\
	}


#define ZZZJS_DECLARE_STATIC_METHOD_MAP() \
    static void DefineStaticMethods(JSContext *cx, JSObject *obj);

#define ZZZJS_BEGIN_STATIC_METHOD_MAP(className)                       \
    void className::DefineStaticMethods(JSContext *cx, JSObject *obj) \
    {                                                                 \
        JSFunctionSpec methods[] =                                    \
        {
// CLASS MACROS
#define ZZZJS_INIT_CLASS(type, name, ctor)                         \
    template<> JSObject *type::TOBJECT::gs_classProto = NULL;      \
    template<> int type::TOBJECT::gs_ctorArguments = ctor;         \
    template<> const char* type::TOBJECT::gs_ClassName = name;		\
    template<> std::map<std::string, int> type::TOBJECT::gs_mapProp;

	

//
//	Construct
//	
#define ZZZJS_DECLARE_CONSTRUCTOR(X) 	static X *Construct(JSContext *cx, \
	JSObject* obj, \
	unsigned int argc, \
	JS::Value *vp,  \
	bool constructing);
#define ZZZJS_BEGIN_CONSTRUCTOR(X, CLS) X* CLS::Construct(JSContext *cx, \
						  JSObject* obj,\
							unsigned int argc, \
							JS::Value *vp, \
							bool constructing) { \
							ZZZJS_FUNC_ENT

#define ZZZJS_END_CONSTRUCTOR	ZZZJS_FUNC_EXIT\
	return NULL;}

//
//	Destruct
//	
#define ZZZJS_DECLARE_DESTRUCTOR(X) 	static void Destruct(X *p, JSObject *obj);

#define ZZZJS_BEGIN_DESTRUCTOR(X, CLS) void CLS::Destruct(X *p, JSObject *obj) {\
	ZZZJS_FUNC_ENT
#define ZZZJS_END_DESTRUCTOR	}catch(...){}\
	}

//
//	AddProperty
//	
#define ZZZJS_DECLARE_ADD_PROP(X) 	static bool AddProperty(X *p, JSContext* cx, JSObject* obj, const wxString& prop,JS::MutableHandle<JS::Value>& vp);
#define ZZZJS_BEGIN_ADD_PROP(X, CLS) bool CLS::AddProperty(X *p, \
                              JSContext* cx, \
                              JSObject* obj, \
                              const wxString& prop,\
                              JS::MutableHandle<JS::Value>& vp) {\
							  ZZZJS_FUNC_ENT
#define ZZZJS_END_ADD_PROP ZZZJS_FUNC_EXIT\
	return false; }



//
//	DeleteProperty
//
#define ZZZJS_DECLARE_DEL_PROP(X) 	static bool DeleteProperty(X *p, JSContext* cx, JSObject* obj, const wxString& prop);
#define ZZZJS_BEGIN_DEL_PROP(X, CLS) bool CLS::DeleteProperty(X *p, \
                                 JSContext* cx, \
                                 JSObject* obj, \
                                 const wxString& prop) { \
								 ZZZJS_FUNC_ENT
#define ZZZJS_END_DEL_PROP  ZZZJS_FUNC_EXIT\
	return false; }

//
//	GetProperty
//
#define ZZZJS_DECLARE_GET_PROP(X) 	static bool GetProperty(X* p, JSContext* cx, JSObject* obj, int id, JS::MutableHandle<JS::Value>& vp);
#define ZZZJS_BEGIN_GET_PROP(X, CLS) bool CLS::GetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp) {\
	ZZZJS_FUNC_ENT
#define ZZZJS_END_GET_PROP ZZZJS_FUNC_EXIT\
	return false;} 

//
//	SetProperty
//
#define ZZZJS_DECLARE_SET_PROP(X) 	static bool SetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp);
#define ZZZJS_BEGIN_SET_PROP(X, CLS) bool CLS::SetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp) {\
	ZZZJS_FUNC_ENT
#define ZZZJS_END_SET_PROP ZZZJS_FUNC_EXIT\
	return false;} 

//
//	GetStaticProperty
//
#define ZZZJS_DECLARE_GET_STATIC_PROP() 	static bool GetStaticProperty(JSContext *cx, int id,JS::MutableHandle<JS::Value>& vp);
#define ZZZJS_BEGIN_GET_STATIC_PROP(CLS) 	bool CLS::GetStaticProperty(JSContext *cx, \
                                        int id,										\
                                        JS::MutableHandle<JS::Value>& vp) {\
										ZZZJS_FUNC_ENT
#define ZZZJS_END_GET_STATIC_PROP ZZZJS_FUNC_EXIT\
	return false;} 

//
//	SetStringProperty
//
#define ZZZJS_DECLARE_SET_STR_PROP(X) 	static bool SetStringProperty(X* p,\
                                    JSContext* cx, \
                                    JSObject* obj,\
                                    const wxString& propertyName,\
                                    JS::MutableHandle<JS::Value>& vp);
#define ZZZJS_BEGIN_GET_SET_STR_PROP(X, CLS) 	bool CLS::SetStringProperty(X* p,\
                                    JSContext* cx, \
                                    JSObject* obj,\
                                    const wxString& propertyName,\
                                    JS::MutableHandle<JS::Value>& vp) { \
		std::map<std::string, int>::iterator ite = gs_mapProp.find((const char*)propertyName);	\
		if( ite != gs_mapProp.end() ) {\
			return CLS::SetProperty(p, cx, obj, (*ite).second, vp);\
		}
#define ZZZJS_END_GET_SET_STR_PROP }
#endif /*___ZZZ_JS_COMMON_API_WRAP_H___*/

