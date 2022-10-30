#ifndef ___ZZZ_JS_COMMON_API_WRAP_H___
#define ___ZZZ_JS_COMMON_API_WRAP_H___


#include <map>
#include <string>
#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/type.h"
#include "js/common/conf.h"
#include "js/common/defs.h"

namespace zzzJs
{
	typedef struct tagInheritCLS
	{

	}InheritCLS;

	template<class T_Port, class T_Priv>
	class ApiWrapper
	{
	private:
		/**
		* コンストラクタの引数
		*/
		static int gs_ctorArguments;
		/**
		* The prototype object of the class
		*/
		static JSObject *gs_classProto;

		/**
		*  The name of the class.
		*  You can use the WXJS_INIT_CLASS macro, to initialize this.
		*/
		static const char* gs_ClassName;

		/**
		* The JSClass structure
		*/
		static JSClass gs_class;


	public:
		typedef ApiWrapper<T_Port, T_Priv> TOBJECT;

		static std::map<std::string, int>		gs_mapProp;

		/**
		 * 指定されたWXクラスを作成する。WXクラスのポインターは戻り値のjavalに保存されます。
		 */
		static jsval CreateObject(JSContext *cx, 
								T_Priv *p, 
								JSObject *parent = NULL)
		{

			JSObject *obj = JS_NewObject(cx, &gs_class, gs_classProto, parent);
			if ( obj == NULL ) {
				return JSVAL_NULL;
			}
			JS_SetPrivate(/*cx, */obj, p);
			return OBJECT_TO_JSVAL(obj);
		}

		// JS_SetPrivateメソッドをコールします
		static void SetPrivate(JSContext *cx, JSObject *obj, T_Priv *p)
		{
			JS_SetPrivate(/*cx,*/ obj, p);
		}

		/**
		 * 指定された WX クラスのオブジェクトを作成し、指定されたオブジェクトのプロパティとして定義します。 
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
		 * オブジェクトのプライベート データから取得したクラスを返します。 check が true の場合、クラスの型をチェックし、クラスが正しい型でない場合は NULL を返します。
		*/
		static T_Priv* GetPrivate(JSContext *cx, 
									JSObject *obj, 
									bool check = true)
		{
			JS::RootedObject proto(cx);
			T_Priv *p = NULL;

			//			
			if ( check )
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
		* オブジェクトのプライベート データから移植されたクラスを返します。
		* 上記と同じことを行いますが、jsval に格納されているオブジェクトに対して行います。
		*/
		static T_Priv* GetPrivate(JSContext *cx, jsval v, bool check = true)
		{
			if (    JSVAL_IS_VOID(v) 
					|| JSVAL_IS_NULL(v) )
			{
				return NULL;
			}
			if( v.isObjectOrNull() == false ) {
				return NULL;
			}

			return JSVAL_TO_OBJECT(v) != NULL ? GetPrivate(cx, JSVAL_TO_OBJECT(v), check)  : NULL;
		}

		/**
		 *  オブジェクトのプロトタイプがこのクラスの場合に true を返します。
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
		* オブジェクトのプロトタイプがこのクラスの場合に true を返します。
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
		* プロパティを追加するためのデフォルトの実装 false を返すと、スクリプトの実行が終了します。
		* デフォルトの実装は true を返します。
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
		* プロパティを削除するためのデフォルトの実装 false を返すと、スクリプトの実行が終了します。 デフォルトの実装は true を返します。
		*/
		static bool DeleteProperty(T_Priv* WXUNUSED(p), 
						JSContext* WXUNUSED(cx), 
						JSObject* WXUNUSED(obj), 
						const wxString& WXUNUSED(prop))
		{
			return true;
		}

		/**
		*  移植されたオブジェクトの Get メソッドの既定の実装。
		*  オブジェクトにプロパティがある場合は、このメソッドを上書きします。
		*  false を返すと、スクリプトの実行が終了します。
		*  デフォルトの実装は true を返します。
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
		*  移植されたオブジェクトの Get メソッドの既定の実装。
		* オブジェクトにプロパティがある場合は、このメソッドを上書きします。
		* false を返すと、スクリプトの実行が終了します。
		* デフォルトの実装は true を返します。
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
		*  移植されたオブジェクトの Set メソッドの既定の実装。
		*  オブジェクトにプロパティがある場合は、このメソッドを上書きします。
		*  @remark false を返すと、スクリプトの実行が終了します。
		*  デフォルトの実装は true を返します。
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
		*  Destruct メソッドの既定の実装。 オブジェクトが破棄される前に何らかのクリーンアップを行う必要がある場合は、これを上書きしてください。
		*  デフォルトの実装は、プライベート オブジェクトのデストラクタを呼び出します。
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
		*  Construct メソッドの既定の実装。 スクリプトが new ステートメントでオブジェクトを作成できる場合は、これを上書きします。
		*  デフォルトの実装は NULL を返します。これは、オブジェクトの作成が許可されていないことを意味します。
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
		*  プロパティを定義するためのデフォルトの実装。
		*  プロパティ定義の複雑さを隠すために、WXJS_DECLARE_PROPERTY_MAP、WXJS_BEGIN_PROPERTY_MAP、および WXJS_END_PROPERTY_MAP マクロを使用します。 デフォルトの実装は何もしません。
		*/
		static void DefineProperties(JSContext* WXUNUSED(cx),
						JSObject* WXUNUSED(obj))
		{
		}

		/**
		* InitClass は、プロトタイプ オブジェクトが作成されるときに呼び出されます。たとえば、このクラスに関連する定数を初期化するために使用できます。
		* 引数 obj は通常、グローバル オブジェクトです。
		* デフォルトの実装は何もしません。
		*/
		static void InitClass(JSContext* WXUNUSED(cx),
						JSObject* WXUNUSED(obj),
						JSObject* WXUNUSED(proto))
		{
		}

		/**
		*  メソッドを定義するためのデフォルトの実装。
		*  メソッド定義の複雑さを隠すために、WXJS_DECLARE_METHOD_MAP、WXJS_BEGIN_METHOD_MAP、および WXJS_END_METHOD_MAP マクロを使用します。
		*  デフォルトの実装は何もしません。
		*/
		static void DefineMethods(JSContext* WXUNUSED(cx),
					JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  定数を定義するためのデフォルトの実装。
		*  定数定義の複雑さを隠すために、WXJS_DECLARE_CONSTANT_MAP、WXJS_BEGIN_CONSTANT_MAP、および WXJS_END_CONSTANT_MAP マクロを使用します。
		*  デフォルトの実装は何もしません。
		*  数値定数のみが許可されます。
		*/
		static void DefineConstants(JSContext* WXUNUSED(cx),
							JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  静的 (クラス) プロパティを定義するためのデフォルトの実装。
		*  プロパティ定義の複雑さを隠すために、WXJS_DECLARE_STATIC_PROPERTY_MAP、WXJS_BEGIN_STATIC_PROPERTY_MAP、および WXJS_END_PROPERTY_MAP マクロを使用します。
		*  デフォルトの実装は何もしません。
		*/
		static void DefineStaticProperties(JSContext* WXUNUSED(cx),
									JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  静的 (クラス) メソッドを定義するためのデフォルトの実装。
		* メソッド定義の複雑さを隠すために、WXJS_DECLARE_STATIC_METHOD_MAP、WXJS_BEGIN_STATIC_METHOD_MAP*、および WXJS_END_METHOD_MAP マクロを使用します。
		* デフォルトの実装は何もしません。
		*/
		static void DefineStaticMethods(JSContext* WXUNUSED(cx),
								JSObject* WXUNUSED(obj))
		{
		}

		/**
		* オブジェクトの JSClass を返します
		*/
		static JSClass* GetClass()
		{
			return &gs_class;
		}

		/**
		*  移植されたオブジェクトの静的 Get メソッドの既定の実装。 オブジェクトに静的プロパティがある場合は、このメソッドを上書きします。
		*  false を返すと、スクリプトの実行が終了します。
		*  デフォルトの実装は true を返します。
		*/
		static bool GetStaticProperty(JSContext* WXUNUSED(cx),
							int WXUNUSED(id),
							JS::MutableHandle<JS::Value>& vp)
		{
			return true;
		}

		/**
		*  移植されたオブジェクトの静的 Set メソッドの既定の実装。
		*  オブジェクトに静的プロパティがある場合は、このメソッドを上書きします。
		*  false を返すと、スクリプトの実行が終了します。
		*  デフォルトの実装は true を返します。
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
		 *  AddProperty コールバック。 これにより、移植されたオブジェクトの AddProperty メソッドが呼び出されます。
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
		 *  AddProperty コールバック。 これにより、移植されたオブジェクトの AddProperty メソッドが呼び出されます。
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
		*  GetProperty コールバック。 これにより、移植されたオブジェクトの Get メソッドが呼び出されます。
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
		 *  SetProperty コールバック。 これにより、移植されたオブジェクトの Set メソッドが呼び出されます。
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
		*  コンストラクターのコールバック。 これにより、移植されたオブジェクトの静的な Construct メソッドが呼び出されます。
		*  これが利用できない場合、移植されたオブジェクトは JavaScript の新しいステートメントで作成できません。
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
		* デストラクタのコールバック。 これにより、移植されたオブジェクトの Destruct メソッドが呼び出されます。
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


// gs_classの初期化を定義しています。
template<class T_Port, class T_Priv>
JSClass zzzJs::ApiWrapper<T_Port, T_Priv>::gs_class =
{ 
    zzzJs::ApiWrapper<T_Port, T_Priv>::gs_ClassName,
    JSCLASS_HAS_PRIVATE /*| JSCLASS_NEW_ENUMERATE*/,
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSAddProperty,
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSDeleteProperty,
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSGetProperty,
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSSetProperty, 
    (JSEnumerateOp) zzzJs::ApiWrapper<T_Port, T_Priv>::JSEnumerate,
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSResolve,
    JS_ConvertStub, 
    zzzJs::ApiWrapper<T_Port, T_Priv>::JSDestructor,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};


// PROPERTY MACROS
//#define WXJS_NORMAL   JSPROP_ENUMERATE | JSPROP_PERMANENT 
#define WXJS_NORMAL   JSPROP_ENUMERATE 
//#define WXJS_READONLY JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY
#define WXJS_READONLY JSPROP_ENUMERATE  | JSPROP_READONLY

// プロパティ マップを宣言する (ヘッダーで使用する)
#define WXJS_DECLARE_PROPERTY_MAP() \
    static void DefineProperties(JSContext *cx, JSObject *obj);

// 静的プロパティ マップを宣言する (ヘッダーで使用する)
#define WXJS_DECLARE_STATIC_PROPERTY_MAP() \
    static void DefineStaticProperties(JSContext *cx, JSObject *obj);

// プロパティ マップを開始します (ソース ファイルで使用します)。
#define WXJS_BEGIN_PROPERTY_MAP(className) \
    void className::DefineProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

// プロパティ マップを終了します (ソース ファイルで使用します)。
#define WXJS_END_PROPERTY_MAP() \
            { 0, 0, 0, 0, 0 } \
        }; \
        JS_DefineProperties(cx, obj, props); \
		for(int i = 0; props[i].name != NULL; i++ ) { \
			gs_mapProp.insert( std::pair<std::string, int>(props[i].name, props[i].tinyid) ); \
		}\
    }

// 静的プロパティ マップを開始します
#define WXJS_BEGIN_STATIC_PROPERTY_MAP(className) \
    void className::DefineStaticProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

//　プロパティを定義
#define WXJS_PROPERTY(id, name) \
    { name, id, WXJS_NORMAL, 0, 0 },

// 静的プロパティーを定義
#define WXJS_STATIC_PROPERTY(id, name) \
    { name, id, WXJS_NORMAL, JSOP_WRAPPER(JSGetStaticProperty), JSOP_WRAPPER(JSSetStaticProperty) },

// ReadOnlyプロパティーを定義
#define WXJS_READONLY_PROPERTY(id, name) \
    { name, id, WXJS_READONLY, 0, 0 },

// ReadOnly静的プロパティーを定義
#define WXJS_READONLY_STATIC_PROPERTY(id, name) \
    { name, id, WXJS_READONLY, JSGetStaticProperty, 0 },

// コンスタント（定数）を定義開始
#define WXJS_DECLARE_CONSTANT_MAP() \
    static void DefineConstants(JSContext *cx, JSObject *obj);

// コンスタント（定数）を定義開始
#define WXJS_BEGIN_CONSTANT_MAP(className)                         \
    void className::DefineConstants(JSContext *cx, JSObject *obj)  \
    {                                                              \
      JSConstDoubleSpec consts[] =                                 \
      {

// コンスタント（定数）を定義終了
#define WXJS_END_CONSTANT_MAP()                 \
            { 0, 0, 0, { 0 } }                      \
        };                                      \
        JS_DefineConstDoubles(cx, obj, consts); \
    }

// コンスタント（定数）を定義
#define WXJS_CONSTANT(prefix, name)	{ prefix##name, #name, WXJS_READONLY, {0,0,0} },
// コンスタント（定数）を定義
#define WXJS_SIMPLE_CONSTANT(name)  { name, #name, WXJS_READONLY, {0,0,0} },

// METHOD MACROS
#define WXJS_DECLARE_METHOD_MAP() \
        static void DefineMethods(JSContext *cx, JSObject *obj);

#define WXJS_BEGIN_METHOD_MAP(className)                         \
    void className::DefineMethods(JSContext *cx, JSObject *obj)  \
    {                                                            \
        JSFunctionSpec methods[] =                               \
        {

#define WXJS_END_METHOD_MAP()                  \
            JS_FS_END                  \
        };                                     \
        JS_DefineFunctions(cx, obj, methods);  \
    }
 
#define WXJS_METHOD(name, fun, args) \
    JS_FS( name, fun, args, 0 ),

// 移植されたクラス ヘッダーのサイズを縮小するマクロ。
#define WXJS_DECLARE_METHOD(name) static JSBool name(JSContext *cx, unsigned argc, JS::Value *vp);

#define WXJS_DECLARE_STATIC_METHOD_MAP() \
    static void DefineStaticMethods(JSContext *cx, JSObject *obj);

#define WXJS_BEGIN_STATIC_METHOD_MAP(className)                       \
    void className::DefineStaticMethods(JSContext *cx, JSObject *obj) \
    {                                                                 \
        JSFunctionSpec methods[] =                                    \
        {
// CLASS MACROS
#define WXJS_INIT_CLASS(type, name, ctor)                         \
    template<> JSObject *type::TOBJECT::gs_classProto = NULL;      \
    template<> int type::TOBJECT::gs_ctorArguments = ctor;         \
    template<> const char* type::TOBJECT::gs_ClassName = name;		\
    template<> std::map<std::string, int> type::TOBJECT::gs_mapProp;

	

//
//	Construct
//	
#define WXJS_DECLARE_CONSTRUCTOR(X) 	static X *Construct(JSContext *cx, \
	JSObject* obj, \
	unsigned int argc, \
	JS::Value *vp,  \
	bool constructing);
#define WXJS_BEGIN_CONSTRUCTOR(X, CLS) X* CLS::Construct(JSContext *cx, \
						  JSObject* obj,\
							unsigned int argc, \
							JS::Value *vp, \
							bool constructing) {

#define WXJS_END_CONSTRUCTOR	}

//
//	Destruct
//	
#define WXJS_DECLARE_DESTRUCTOR(X) 	static void Destruct(X *p, JSObject *obj);

#define WXJS_BEGIN_DESTRUCTOR(X, CLS) void CLS::Destruct(X *p, JSObject *obj) {
#define WXJS_END_DESTRUCTOR	}

//
//	AddProperty
//	
#define WXJS_DECLARE_ADD_PROP(X) 	static bool AddProperty(X *p, JSContext* cx, JSObject* obj, const wxString& prop,JS::MutableHandle<JS::Value>& vp);
#define WXJS_BEGIN_ADD_PROP(X, CLS) bool CLS::AddProperty(X *p, \
                              JSContext* cx, \
                              JSObject* obj, \
                              const wxString& prop,\
                              JS::MutableHandle<JS::Value>& vp) {
#define WXJS_END_ADD_PROP }



//
//	DeleteProperty
//
#define WXJS_DECLARE_DEL_PROP(X) 	static bool DeleteProperty(X *p, JSContext* cx, JSObject* obj, const wxString& prop);
#define WXJS_BEGIN_DEL_PROP(X, CLS) bool CLS::DeleteProperty(X *p, \
                                 JSContext* cx, \
                                 JSObject* obj, \
                                 const wxString& prop) {
#define WXJS_END_DEL_PROP }

//
//	GetProperty
//
#define WXJS_DECLARE_GET_PROP(X) 	static bool GetProperty(X* p, JSContext* cx, JSObject* obj, int id, JS::MutableHandle<JS::Value>& vp);
#define WXJS_BEGIN_GET_PROP(X, CLS) bool CLS::GetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp) {
#define WXJS_END_GET_PROP }

//
//	SetProperty
//
#define WXJS_DECLARE_SET_PROP(X) 	static bool SetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp);
#define WXJS_BEGIN_SET_PROP(X, CLS) bool CLS::SetProperty(X *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value>& vp) {
#define WXJS_END_SET_PROP }

//
//	GetStaticProperty
//
#define WXJS_DECLARE_GET_STATIC_PROP() 	static bool GetStaticProperty(JSContext *cx, int id,JS::MutableHandle<JS::Value>& vp);
#define WXJS_BEGIN_GET_STATIC_PROP(CLS) 	bool CLS::GetStaticProperty(JSContext *cx, \
                                        int id,										\
                                        JS::MutableHandle<JS::Value>& vp) {
#define WXJS_END_GET_STATIC_PROP }

//
//	SetStringProperty
//
#define WXJS_DECLARE_SET_STR_PROP(X) 	static bool SetStringProperty(X* p,\
                                    JSContext* cx, \
                                    JSObject* obj,\
                                    const wxString& propertyName,\
                                    JS::MutableHandle<JS::Value>& vp);
#define WXJS_BEGIN_GET_SET_STR_PROP(X, CLS) 	bool CLS::SetStringProperty(X* p,\
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

