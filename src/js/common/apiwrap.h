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
		* �R���X�g���N�^�̈���
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
		 * �w�肳�ꂽWX�N���X���쐬����BWX�N���X�̃|�C���^�[�͖߂�l��javal�ɕۑ�����܂��B
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

		// JS_SetPrivate���\�b�h���R�[�����܂�
		static void SetPrivate(JSContext *cx, JSObject *obj, T_Priv *p)
		{
			JS_SetPrivate(/*cx,*/ obj, p);
		}

		/**
		 * �w�肳�ꂽ WX �N���X�̃I�u�W�F�N�g���쐬���A�w�肳�ꂽ�I�u�W�F�N�g�̃v���p�e�B�Ƃ��Ē�`���܂��B 
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
		 * �I�u�W�F�N�g�̃v���C�x�[�g �f�[�^����擾�����N���X��Ԃ��܂��B check �� true �̏ꍇ�A�N���X�̌^���`�F�b�N���A�N���X���������^�łȂ��ꍇ�� NULL ��Ԃ��܂��B
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
		* �I�u�W�F�N�g�̃v���C�x�[�g �f�[�^����ڐA���ꂽ�N���X��Ԃ��܂��B
		* ��L�Ɠ������Ƃ��s���܂����Ajsval �Ɋi�[����Ă���I�u�W�F�N�g�ɑ΂��čs���܂��B
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
		 *  �I�u�W�F�N�g�̃v���g�^�C�v�����̃N���X�̏ꍇ�� true ��Ԃ��܂��B
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
		* �I�u�W�F�N�g�̃v���g�^�C�v�����̃N���X�̏ꍇ�� true ��Ԃ��܂��B
		*/
		static bool HasPrototype(JSContext *cx, jsval v)
		{
			return v.isObject() ? HasPrototype(cx, JSVAL_TO_OBJECT(v))
									: false;
		}
		/**
		 *	@brief	�N���X���`����
		 */
		static JSObject* define_Class(JSContext *cx, 
										JSObject *obj,
										JSObject *proto = NULL)

		{
			JSAutoCompartment transaction(cx, obj);	// �g�����U�N�V����

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
		* �v���p�e�B��ǉ����邽�߂̃f�t�H���g�̎��� false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		* �f�t�H���g�̎����� true ��Ԃ��܂��B
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
		* �v���p�e�B���폜���邽�߂̃f�t�H���g�̎��� false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B �f�t�H���g�̎����� true ��Ԃ��܂��B
		*/
		static bool DeleteProperty(T_Priv* WXUNUSED(p), 
						JSContext* WXUNUSED(cx), 
						JSObject* WXUNUSED(obj), 
						const wxString& WXUNUSED(prop))
		{
			return true;
		}

		/**
		*  �ڐA���ꂽ�I�u�W�F�N�g�� Get ���\�b�h�̊���̎����B
		*  �I�u�W�F�N�g�Ƀv���p�e�B������ꍇ�́A���̃��\�b�h���㏑�����܂��B
		*  false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		*  �f�t�H���g�̎����� true ��Ԃ��܂��B
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
		*  �ڐA���ꂽ�I�u�W�F�N�g�� Get ���\�b�h�̊���̎����B
		* �I�u�W�F�N�g�Ƀv���p�e�B������ꍇ�́A���̃��\�b�h���㏑�����܂��B
		* false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		* �f�t�H���g�̎����� true ��Ԃ��܂��B
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
		*  �ڐA���ꂽ�I�u�W�F�N�g�� Set ���\�b�h�̊���̎����B
		*  �I�u�W�F�N�g�Ƀv���p�e�B������ꍇ�́A���̃��\�b�h���㏑�����܂��B
		*  @remark false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		*  �f�t�H���g�̎����� true ��Ԃ��܂��B
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
		*  Destruct ���\�b�h�̊���̎����B �I�u�W�F�N�g���j�������O�ɉ��炩�̃N���[���A�b�v���s���K�v������ꍇ�́A������㏑�����Ă��������B
		*  �f�t�H���g�̎����́A�v���C�x�[�g �I�u�W�F�N�g�̃f�X�g���N�^���Ăяo���܂��B
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
		*  Construct ���\�b�h�̊���̎����B �X�N���v�g�� new �X�e�[�g�����g�ŃI�u�W�F�N�g���쐬�ł���ꍇ�́A������㏑�����܂��B
		*  �f�t�H���g�̎����� NULL ��Ԃ��܂��B����́A�I�u�W�F�N�g�̍쐬��������Ă��Ȃ����Ƃ��Ӗ����܂��B
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
		*  �v���p�e�B���`���邽�߂̃f�t�H���g�̎����B
		*  �v���p�e�B��`�̕��G�����B�����߂ɁAWXJS_DECLARE_PROPERTY_MAP�AWXJS_BEGIN_PROPERTY_MAP�A����� WXJS_END_PROPERTY_MAP �}�N�����g�p���܂��B �f�t�H���g�̎����͉������܂���B
		*/
		static void DefineProperties(JSContext* WXUNUSED(cx),
						JSObject* WXUNUSED(obj))
		{
		}

		/**
		* InitClass �́A�v���g�^�C�v �I�u�W�F�N�g���쐬�����Ƃ��ɌĂяo����܂��B���Ƃ��΁A���̃N���X�Ɋ֘A����萔�����������邽�߂Ɏg�p�ł��܂��B
		* ���� obj �͒ʏ�A�O���[�o�� �I�u�W�F�N�g�ł��B
		* �f�t�H���g�̎����͉������܂���B
		*/
		static void InitClass(JSContext* WXUNUSED(cx),
						JSObject* WXUNUSED(obj),
						JSObject* WXUNUSED(proto))
		{
		}

		/**
		*  ���\�b�h���`���邽�߂̃f�t�H���g�̎����B
		*  ���\�b�h��`�̕��G�����B�����߂ɁAWXJS_DECLARE_METHOD_MAP�AWXJS_BEGIN_METHOD_MAP�A����� WXJS_END_METHOD_MAP �}�N�����g�p���܂��B
		*  �f�t�H���g�̎����͉������܂���B
		*/
		static void DefineMethods(JSContext* WXUNUSED(cx),
					JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  �萔���`���邽�߂̃f�t�H���g�̎����B
		*  �萔��`�̕��G�����B�����߂ɁAWXJS_DECLARE_CONSTANT_MAP�AWXJS_BEGIN_CONSTANT_MAP�A����� WXJS_END_CONSTANT_MAP �}�N�����g�p���܂��B
		*  �f�t�H���g�̎����͉������܂���B
		*  ���l�萔�݂̂�������܂��B
		*/
		static void DefineConstants(JSContext* WXUNUSED(cx),
							JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  �ÓI (�N���X) �v���p�e�B���`���邽�߂̃f�t�H���g�̎����B
		*  �v���p�e�B��`�̕��G�����B�����߂ɁAWXJS_DECLARE_STATIC_PROPERTY_MAP�AWXJS_BEGIN_STATIC_PROPERTY_MAP�A����� WXJS_END_PROPERTY_MAP �}�N�����g�p���܂��B
		*  �f�t�H���g�̎����͉������܂���B
		*/
		static void DefineStaticProperties(JSContext* WXUNUSED(cx),
									JSObject* WXUNUSED(obj))
		{
		}

		/**
		*  �ÓI (�N���X) ���\�b�h���`���邽�߂̃f�t�H���g�̎����B
		* ���\�b�h��`�̕��G�����B�����߂ɁAWXJS_DECLARE_STATIC_METHOD_MAP�AWXJS_BEGIN_STATIC_METHOD_MAP*�A����� WXJS_END_METHOD_MAP �}�N�����g�p���܂��B
		* �f�t�H���g�̎����͉������܂���B
		*/
		static void DefineStaticMethods(JSContext* WXUNUSED(cx),
								JSObject* WXUNUSED(obj))
		{
		}

		/**
		* �I�u�W�F�N�g�� JSClass ��Ԃ��܂�
		*/
		static JSClass* GetClass()
		{
			return &gs_class;
		}

		/**
		*  �ڐA���ꂽ�I�u�W�F�N�g�̐ÓI Get ���\�b�h�̊���̎����B �I�u�W�F�N�g�ɐÓI�v���p�e�B������ꍇ�́A���̃��\�b�h���㏑�����܂��B
		*  false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		*  �f�t�H���g�̎����� true ��Ԃ��܂��B
		*/
		static bool GetStaticProperty(JSContext* WXUNUSED(cx),
							int WXUNUSED(id),
							JS::MutableHandle<JS::Value>& vp)
		{
			return true;
		}

		/**
		*  �ڐA���ꂽ�I�u�W�F�N�g�̐ÓI Set ���\�b�h�̊���̎����B
		*  �I�u�W�F�N�g�ɐÓI�v���p�e�B������ꍇ�́A���̃��\�b�h���㏑�����܂��B
		*  false ��Ԃ��ƁA�X�N���v�g�̎��s���I�����܂��B
		*  �f�t�H���g�̎����� true ��Ԃ��܂��B
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
		 *  AddProperty �R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�� AddProperty ���\�b�h���Ăяo����܂��B
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
		 *  AddProperty �R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�� AddProperty ���\�b�h���Ăяo����܂��B
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
		*  GetProperty �R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�� Get ���\�b�h���Ăяo����܂��B
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
		 *  SetProperty �R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�� Set ���\�b�h���Ăяo����܂��B
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
		*  �R���X�g���N�^�[�̃R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�̐ÓI�� Construct ���\�b�h���Ăяo����܂��B
		*  ���ꂪ���p�ł��Ȃ��ꍇ�A�ڐA���ꂽ�I�u�W�F�N�g�� JavaScript �̐V�����X�e�[�g�����g�ō쐬�ł��܂���B
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

			// JS_IsConstructing=���ݎ��s����JSNative���R���X�g���N�^�Ƃ��ČĂяo���ꂽ���ǂ����𔻒肵�܂��B
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
		* �f�X�g���N�^�̃R�[���o�b�N�B ����ɂ��A�ڐA���ꂽ�I�u�W�F�N�g�� Destruct ���\�b�h���Ăяo����܂��B
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


// gs_class�̏��������`���Ă��܂��B
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

// �v���p�e�B �}�b�v��錾���� (�w�b�_�[�Ŏg�p����)
#define WXJS_DECLARE_PROPERTY_MAP() \
    static void DefineProperties(JSContext *cx, JSObject *obj);

// �ÓI�v���p�e�B �}�b�v��錾���� (�w�b�_�[�Ŏg�p����)
#define WXJS_DECLARE_STATIC_PROPERTY_MAP() \
    static void DefineStaticProperties(JSContext *cx, JSObject *obj);

// �v���p�e�B �}�b�v���J�n���܂� (�\�[�X �t�@�C���Ŏg�p���܂�)�B
#define WXJS_BEGIN_PROPERTY_MAP(className) \
    void className::DefineProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

// �v���p�e�B �}�b�v���I�����܂� (�\�[�X �t�@�C���Ŏg�p���܂�)�B
#define WXJS_END_PROPERTY_MAP() \
            { 0, 0, 0, 0, 0 } \
        }; \
        JS_DefineProperties(cx, obj, props); \
		for(int i = 0; props[i].name != NULL; i++ ) { \
			gs_mapProp.insert( std::pair<std::string, int>(props[i].name, props[i].tinyid) ); \
		}\
    }

// �ÓI�v���p�e�B �}�b�v���J�n���܂�
#define WXJS_BEGIN_STATIC_PROPERTY_MAP(className) \
    void className::DefineStaticProperties(JSContext *cx, JSObject *obj) \
    { \
        JSPropertySpec props[] = \
        {

//�@�v���p�e�B���`
#define WXJS_PROPERTY(id, name) \
    { name, id, WXJS_NORMAL, 0, 0 },

// �ÓI�v���p�e�B�[���`
#define WXJS_STATIC_PROPERTY(id, name) \
    { name, id, WXJS_NORMAL, JSOP_WRAPPER(JSGetStaticProperty), JSOP_WRAPPER(JSSetStaticProperty) },

// ReadOnly�v���p�e�B�[���`
#define WXJS_READONLY_PROPERTY(id, name) \
    { name, id, WXJS_READONLY, 0, 0 },

// ReadOnly�ÓI�v���p�e�B�[���`
#define WXJS_READONLY_STATIC_PROPERTY(id, name) \
    { name, id, WXJS_READONLY, JSGetStaticProperty, 0 },

// �R���X�^���g�i�萔�j���`�J�n
#define WXJS_DECLARE_CONSTANT_MAP() \
    static void DefineConstants(JSContext *cx, JSObject *obj);

// �R���X�^���g�i�萔�j���`�J�n
#define WXJS_BEGIN_CONSTANT_MAP(className)                         \
    void className::DefineConstants(JSContext *cx, JSObject *obj)  \
    {                                                              \
      JSConstDoubleSpec consts[] =                                 \
      {

// �R���X�^���g�i�萔�j���`�I��
#define WXJS_END_CONSTANT_MAP()                 \
            { 0, 0, 0, { 0 } }                      \
        };                                      \
        JS_DefineConstDoubles(cx, obj, consts); \
    }

// �R���X�^���g�i�萔�j���`
#define WXJS_CONSTANT(prefix, name)	{ prefix##name, #name, WXJS_READONLY, {0,0,0} },
// �R���X�^���g�i�萔�j���`
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

// �ڐA���ꂽ�N���X �w�b�_�[�̃T�C�Y���k������}�N���B
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

