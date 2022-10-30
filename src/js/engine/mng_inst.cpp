#include "precompile.h"



#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/filename.h>
#include <wx/ffile.h>
#include <wx/tokenzr.h>

#include "js/engine/mng_inst.h"
#include "js/engine/scrcxpriv.h"
#include "js/common/conf.h"
#include "js/common/type.h"

#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/zzzjs_gui_init.h"
#include "js/io/zzzjs_io_init.h"
#include "js/expat/zzzjs_expat_init.h"
#include "js/xml/zzzjs_xml_init.h"
#include "js/log/wxlog_init.h"



using namespace zzzJs;


MngInst*	MngInst::gs_pManager = NULL;

static JSBool print(JSContext *cx, unsigned argc, JS::Value *vp);
static JSBool include(JSContext *cx, unsigned argc, JS::Value *vp);
static JSBool jsexit(JSContext *cx, unsigned argc, JS::Value *vp);
static JSBool create_namespace(JSContext *cx, unsigned argc, JS::Value *vp);
static JSBool require(JSContext *cx, unsigned argc, JS::Value *vp);

JSClass gs_zzzjs_global_class = {
	"global",  JSCLASS_GLOBAL_FLAGS,
	ZzzJs_JS_PropertyStub,
	ZzzJs_JS_DeletePropertyStub,
	ZzzJs_JS_PropertyStub,
	ZzzJs_JS_StrictPropertyStub,
	JS_EnumerateStub,
	ZzzJs_JS_ResolveStub,
	JS_ConvertStub,
	NULL,
	JSCLASS_NO_OPTIONAL_MEMBERS
}; /* global_class */




MngInst::MngInst()
	:	m_pJSRuntime( NULL )
	,	m_pJSContext( NULL )
	,	m_pGlobalJSObject( NULL )
	,	m_pScript( NULL )

	,	m_pConsoleObject( NULL )
{

}

MngInst::~MngInst()
{
	close();
}

MngInst* MngInst::instance()
{
	if( gs_pManager == NULL ) {
		gs_pManager = new MngInst();
	}
	return gs_pManager;
}

void MngInst::release()
{
	if( gs_pManager != NULL ) {
		delete gs_pManager;
	}
	gs_pManager = NULL;
}

bool MngInst::initRuntime(unsigned long ulMaxMemSize /*= 0*/,  unsigned long ulStackChunkSize /*= 0*/)
{

	if( ulMaxMemSize == 0 ) {
		ulMaxMemSize = (8L * 1024L * 1024L);
	}
	if( ulStackChunkSize == 0 ) {
		ulStackChunkSize = 8192;
	}
	
	// ランタイムを生成
	//  - 引数にはスタックのサイズを指定しますが、一般的に以下のような値をもちいるといいでしょう（公式リファレンスより）。
	m_pJSRuntime = JS_NewRuntime( ulMaxMemSize, JS_NO_HELPER_THREADS );
	if( m_pJSRuntime == NULL ) {
		wxLogError(_T("fail to call JS_NewRuntime."));
		return false;
	}
	// 実行コンテキストの生成
	//  
	m_pJSContext = JS_NewContext(m_pJSRuntime, ulStackChunkSize);
	if( m_pJSContext == NULL ) {
		wxLogError(_T("fail to call JS_NewContext."));		
		return false;
	}
//	JS_SetOptions(m_pJSContext, JSOPTION_VAROBJFIX | JSOPTION_JIT | JSOPTION_METHODJIT);
	// コンテキスト操作を開始する前には、必ずコールする。
//    JSAutoRequest ar(m_pJSContext);
	// 
//	JS::RootedObject global(m_pJSContext);
	
	{
        JS_SetContextPrivate(m_pJSContext, new ScriptContextPrivate(this));
		JS_SetErrorReporter(m_pJSContext, printError);
	}


	// ローバルオブジェクトを生成し、
	// コンテキストに関連付けます。
	// そして、標準で提供されるいくつかのクラスやオブジェクトを登録します。
	//m_pGlobalJSObject = JS_NewGlobalObject(m_pJSContext, &gs_zzzjs_global_class, nullptr);
	m_pGlobalJSObject = JS_NewGlobalObject(m_pJSContext, &gs_zzzjs_global_class, nullptr);
	if( m_pGlobalJSObject == NULL ) {
		wxLogError(_T("fail to call JS_NewObject(Grobal)."));	
		return false;
	}
	JSAutoCompartment ac(m_pJSContext, m_pGlobalJSObject);	// トランザクション


	jsval jswxjs = OBJECT_TO_JSVAL(m_pGlobalJSObject);
	JS_SetProperty(m_pJSContext, m_pGlobalJSObject, "wxjs", &jswxjs);


    // Define global methods
    JS_DefineFunction(m_pJSContext, m_pGlobalJSObject, "print", print, 0, 0);
    JS_DefineFunction(m_pJSContext, m_pGlobalJSObject, "exit", jsexit, 0, 0);
    JS_DefineFunction(m_pJSContext, m_pGlobalJSObject, "include", include, 2, 0);
    JS_DefineFunction(m_pJSContext, m_pGlobalJSObject, "namespace", create_namespace, 1, 0);
	JS_DefineFunction(m_pJSContext, m_pGlobalJSObject, "require", require, 1, 0);

	JS_InitStandardClasses(m_pJSContext, m_pGlobalJSObject);
#ifdef JS_HAS_CTYPES
    if (!JS_InitCTypesClass(m_pJSContext, m_pGlobalJSObject))
		return false;
#endif



	return true;
}

JSScript* MngInst::compileFromFile(const TCHAR* p_filename)
{
	JSScript* pScript = NULL;

	JSAutoCompartment ac(m_pJSContext, m_pGlobalJSObject);

	if( p_filename == NULL ) {
		wxLogError( _T("argument error."));
		return NULL;
	}
	if( m_pJSContext == NULL ) {
		wxLogError( _T("not initilize script."));
		return NULL;
	}


	wxString strBuff;
	wxFFile  file;
	if( file.Open(p_filename) == false ) {
		wxLogError( _T("fail to open script[%s]."), p_filename);
		return NULL;
	}
	file.ReadAll(&strBuff);
#ifdef UNICODE
	wxString strFName("");
	strFName = p_filename;
	pScript = JS_CompileUCScript(m_pJSContext, m_pGlobalJSObject,
		(const jschar *)strBuff, strBuff.Length(),
		strFName, 0);
#else
	pScript = JS_CompileScript(m_pJSContext, m_pGlobalJSObject,
		p_script, XStrBuff::StrLen(p_script),
		pfileName, 0);
#endif
	if( pScript == NULL ) {
		wxLogError( _T("fail to compile [%s]."), p_filename);
		return false;
	}
	// スクリプトを実行して、初期化を行う。
	jsval result;
	if( JS_ExecuteScript(m_pJSContext, m_pGlobalJSObject, pScript, &result) == JS_FALSE ) {
		wxLogError( _T("fail to call [%s]."), p_filename);
	}
		
//	m_pScript = pScript;
	

	return pScript;
}

jsval MngInst::RunScript(JSContext *cx, const wxFileName &file, wxMBConv &conv)
{
	jsval rval = JSVAL_VOID;

    ScriptSource script;
	script.SetFile(file, conv);
	if ( script.HasSource() )
	{
	  wxString message(wxT("wxJS: Running Scriptfile "));
	  message << file.GetFullPath();
	  wxLogVerbose(message);
	  DoRun(cx, script, &rval);
	}
	else
	{
		wxString message(wxT("wxJS: Unknown scriptfile or empty file "));
        message << file.GetFullPath();
		wxLogError(message);
	}

	return rval;
}

jsval MngInst::RunScript(JSContext *cx, const wxString &scriptText, const wxString &path)
{
	jsval rval = JSVAL_VOID;

    ScriptSource script;
	script.SetSource(scriptText);
    script.SetPath(path);
	if ( script.HasSource() )
	{
		wxString message(wxT("wxJS: Running Scripttext"));
		wxLogVerbose(message);
		DoRun(cx, script, &rval);
	}
	else
	{
		wxString message(wxT("wxJS: empty script"));
		wxLogError(message);
	}

	return rval;
}

void MngInst::DoRun(JSContext *cx, const ScriptSource &script, jsval *rval)
{

	JSAutoCompartment ac(m_pJSContext, m_pGlobalJSObject);

//	JS::RootedValue r(m_pJSContext);


    jsval jspath = ToJS(cx, script.GetPath());
    JS_SetProperty(cx, 
		//JS_GetGlobalObject(cx), 
		this->getGlobalJSObject(cx),
		"root", &jspath);
    ScriptContextPrivate *priv = (ScriptContextPrivate *) JS_GetContextPrivate(cx);
    priv->AddIncludePath(script.GetPath());

    if ( script.HasSource() )
    {
        wxString source(script.GetSource());
	    wxCharBuffer filename = script.GetFileName().ToAscii();

        wxMBConvUTF16 utf;

        int length = script.GetSource().length();
        wxCharBuffer sourceBuffer = script.GetSource().mb_str(utf);

		JSAutoRequest autoReq( cx );
//        JS_BeginRequest(cx);
        if ( JS_EvaluateUCScript(cx,
								this->getGlobalJSObject(cx), 
								//JS_GetGlobalObject(cx),
                                 (jschar *) sourceBuffer.data(), 
				                 length, filename, 1, rval) == JS_FALSE )
	    {
		    wxLogError(wxT("Evaluating script failed"));
	    }
//        JS_EndRequest(cx);
    }
}





bool MngInst::close()
{
	if( m_pJSContext != NULL ) {
		ScriptContextPrivate* pScriptContextPrivate = (ScriptContextPrivate*)JS_GetContextPrivate(m_pJSContext);
		if( pScriptContextPrivate != NULL ) {
			delete pScriptContextPrivate;
		}
		JS_SetContextPrivate(m_pJSContext, NULL);

		//JS_ClearNewbornRoots(m_pJSContext);
//		JS_ClearRegExpStatics(m_pJSContext);
		if ( JS_IsExceptionPending(m_pJSContext) )
		{
			//TODO: test this!
			JS_ReportPendingException(m_pJSContext);
		}
		JS_ClearPendingException(m_pJSContext);
//		JS_ClearScope(cx, m_pGlobalJSObject);
//		JS_EndRequest(m_pJSContext);
		//JS_ClearContextThread(m_pJSContext);

		JS_DestroyContext(m_pJSContext);
	}
	if( m_pJSRuntime != NULL ) {
		JS_DestroyRuntime(m_pJSRuntime);
	}
	JS_ShutDown();


	return true;
}

void MngInst::printError(JSContext *cx, const char *message, JSErrorReport *report)
{
	wxString strFName(_T(""));
	wxString strMessage( message );

	if( report->filename != NULL ) {
		strFName = report->filename;
	} else {
		strFName = _T("NULL");
	}

	wxLogError( _T("JavaScript: %s:%d:\n  %s")
		, (const TCHAR*)strFName, report->lineno+1
		, (const TCHAR*)strMessage);
	wxLogDebug( _T("JavaScript: %s:%d:\n  %s")
		, (const TCHAR*)strFName, report->lineno+1
		, (const TCHAR*)strMessage);
}



JSBool print(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSString *str = NULL;
	wxString dst;
	wxString strBuff(_T(""));
    JS::CallArgs args = CallArgsFromVp(argc, vp);
	// プライベートデータの取得
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    if (!obj) {
        return JS_FALSE;
	}	


    wxString text;

	for(uintN i = 0; i < argc; i++)
	{
/*
		if( args[i].isNumber() ) {
			if( args[i].isBoolean() ) {
				int fdksop = 0;
			}
			if( args[i].isDouble() ) {
				int fdksop = 0;
				double dd = args[i].toDouble();
				float f, f2;
				f2 = modff(dd, &f);
				if( f2 == 0 ) {
					uint64_t aaaa = (uint64_t)dd;
					::memcpy_s(&aaaa, sizeof(aaaa), &dd, sizeof(dd));
					int fsdkoif = 0;
				}
//				int sdf = _fpclass(dd);

				int fdjio = 1;
			}
			if( args[i].isInt32() ) {
				int fdksop = 0;
			}
			uint64_t b = (uint64_t)-1;
			int64_t b1 = -1;
			if( JS_ValueToUint64(cx, args[i], &b) == true ) {
				int fdksop = 0;

			}
			if( JS::ToInt64(cx, args[i], &b1) == true ) {
				int fdksop = 0;

			}
		}
		if( args[i].isObject() ) {
				
			JSClass* pC = JS_GetClass(args[i].toObjectOrNull());
			int fsdjio = 0;
		}
*/
		wxString to;
		FromJS(cx, args[i], to);
        text += to;
	}

	wxLogDebug(text);
	wxLogMessage(text);

	return JS_TRUE;
}

JSBool include(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject*		objScript = NULL;
	ScriptSource	script;
	wxString		filename;
	int				argFileName = 0;
	int				argEncoding = 1;
	
	JSAutoCompartment ac(cx, MngInst::instance()->getGlobalJSObject(cx));


	JS::CallArgs args = CallArgsFromVp(argc, vp);
	// プライベートデータの取得
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	if (!obj) {
		return JS_FALSE;
	}

	if( argc < 0 ) {
	return JS_FALSE;
	}

	if( args[0].isObject() ) {
		objScript = JSVAL_TO_OBJECT(args[0]);
		if ( argc < 2 )
		{
			JS_ReportError(cx, "Scriptfile name missing in include");
			return JS_FALSE;
		}
		argFileName = 1;
		argEncoding = 2;
	}
	
	FromJS(cx, args[argFileName], filename);
	
	ScriptContextPrivate *cxp = (ScriptContextPrivate *) JS_GetContextPrivate(cx);
	wxASSERT_MSG(cxp != NULL, wxT("This is not a ScriptContext"));
	
	wxFileName scriptFile(filename);
	if ( scriptFile.IsRelative() )
	{
		wxString path;
		wxString currentPath = cxp->GetCurrentIncludePath();
		if ( currentPath.Length() > 0 )
		{
			scriptFile.Normalize(wxPATH_NORM_ALL, currentPath);
		}
	}
	cxp->AddIncludePath(scriptFile.GetPath());

	wxString encoding(WXJS_INTERNAL_ENCODING);
	if ( argc > argEncoding )
	{
		FromJS(cx, args[argEncoding], encoding);
	}
	
	wxCSConv conv(encoding);
	script.SetFile(scriptFile.GetFullPath(), conv);
	
	if ( script.GetSource().Length() > 0 )
	{
		wxMBConvUTF16 utf;
		int length = script.GetSource().length();
		wxCharBuffer source = script.GetSource().mb_str(utf);
		jschar* p_script_path = (jschar *) source.data();
		JSScript *jsscript = JS_CompileUCScript(cx, obj, (jschar *) source.data(),
								length, 
								scriptFile.GetFullPath().ToAscii(), 0);
		if( jsscript == NULL ) {
			JS_ReportPendingException(cx);
			JS_ReportError(cx, "Error occurred compile %s", (const char *) scriptFile.GetFullPath().ToAscii());
			return JS_FALSE;
		}


		if ( objScript == NULL )
		{
			//objScript = JS_NewScriptObject(cx, jsscript);
			// JS_NewScriptObjectがなくなったので、以下のコードに置き換え。
			objScript = JS_NewObject(cx, NULL, NULL, NULL);
			JS_SetPrivate(objScript, jsscript);


			*vp = OBJECT_TO_JSVAL(objScript);
			JS_SetParent(cx, objScript, 
					MngInst::instance()->getGlobalJSObject(cx)
					//JS_GetGlobalObject(cx)
			);
		}
		jsval vresult;
		JSBool ok = JS_ExecuteScript(cx, objScript, jsscript, &vresult);
		if ( ok == JS_FALSE )
		{
			JS_ReportPendingException(cx);
			JS_ReportError(cx, "Error occurred while including %s", (const char *) scriptFile.GetFullPath().ToAscii());
		}
	}

	cxp->RemoveCurrentIncludePath();
	return JS_TRUE;
}
JSBool jsexit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	return JS_TRUE;
}
JSBool create_namespace(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxString name;
    JS::CallArgs argv = CallArgsFromVp(argc, vp);
    FromJS(cx, argv[0], name);

	JSObject *nsObject = MngInst::instance()->getGlobalJSObject(cx);//JS_GetGlobalObject(cx);

    wxStringTokenizer tokenizer(name, wxT("."));
    wxString part = tokenizer.GetNextToken();
    while(part.Length() > 0)
    {
	    wxMBConvUTF16 utf16;
        int length = part.length();
        wxCharBuffer ns = part.mb_str(utf16);
        jsval vns;
        if ( JS_GetUCProperty(cx, nsObject, (const jschar *) ns.data(), length, &vns) ==  JS_FALSE )
            return JS_FALSE;

        if ( vns != JSVAL_VOID )
        {
			if ( vns.isObject() /*JSVAL_IS_OBJECT(vns)*/ )
            {
                nsObject = JSVAL_TO_OBJECT(vns);
            }
            else
            {
                JS_ReportError(cx, "Invalid object %s used as namespace", (const char *) part.ToAscii());
                return JS_FALSE;
            }
        }
        else
        {
            JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);
            vns = OBJECT_TO_JSVAL(newObject);
            if ( JS_SetUCProperty(cx, nsObject, (const jschar *) ns.data(), length, &vns) == JS_FALSE )
            {
                JS_ReportError(cx, "Invalid object %s used as namespace", (const char *) part.ToAscii());
                return JS_FALSE;
            }
            nsObject = newObject;
        }
        part = tokenizer.GetNextToken();
    }
    return JS_TRUE;
}

static JSBool require(JSContext *cx, unsigned argc, JS::Value *vp)
{
    wxString name;
    JS::CallArgs argv = CallArgsFromVp(argc, vp);
	JSObject *nsObject = MngInst::instance()->getGlobalJSObject(cx);//JS_GetGlobalObject(cx);

	
    FromJS(cx, argv[0], name);

	if( name == _T("wx") ) {
		JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);

		// Initialize our extension library
		zzzJs::ext::InitClass(cx, newObject);
		zzzJs::ext::InitObject(cx, newObject);
	
		// Initialize our extension library
		zzzJs::gui::InitClass(cx, newObject);
		zzzJs::gui::InitObject(cx, newObject);
		// Initialize our extension library
		zzzJs::io::InitClass(cx, newObject);
		zzzJs::io::InitObject(cx, newObject);
		
		zzzJs::log::InitClass(cx, newObject);
		zzzJs::log::InitObject(cx, newObject);


		*vp = OBJECT_TO_JSVAL(newObject);
	} else
	if( name == _T("expat") ) {
		JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);
		zzzJs::xml::InitClass(cx, newObject);
		zzzJs::xml::InitObject(cx, newObject);

		*vp = OBJECT_TO_JSVAL(newObject);
	} else
	if( name == _T("xml") ) {
		JSObject *newObject = JS_NewObject(cx, NULL, NULL, NULL);
		zzzJs::wxxml::InitClass(cx, newObject);
		zzzJs::wxxml::InitObject(cx, newObject);

		*vp = OBJECT_TO_JSVAL(newObject);
	} else {
		JS_ReportError(cx, "unkown module %s", (const char *)name.ToAscii());
		return JS_TRUE;
	}

	return JS_TRUE;
}
