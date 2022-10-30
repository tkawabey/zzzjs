#ifndef ___ZZZ_JS_ENGINE_MNG_INST_H___
#define ___ZZZ_JS_ENGINE_MNG_INST_H___


#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/script.h"



namespace zzzJs
{
	/**
	 *	@brief	JS管理インスタンス
	 */
	class MngInst
	{
	public:
		MngInst();
		virtual ~MngInst();
		

		static MngInst* instance();
		static void release();
	

		bool initRuntime(unsigned long ulMaxMemSize = 0,  unsigned long ulStackChunkSize = 0);
		JSScript* compileFromFile(const TCHAR* p_filename);
		bool close();
	
	    jsval RunScript(JSContext *cx, const wxFileName &file, wxMBConv &conv);
	    jsval RunScript(JSContext *cx, const wxString &script, const wxString &path);
        void DoRun(JSContext *cx, const ScriptSource &script, jsval *rval);

		static void printError(JSContext *cx, const char *message, JSErrorReport *report);

		JSRuntime* getRuntime(){ return m_pJSRuntime; }
		JSContext* getContext(){ return m_pJSContext; }
		JSObject* getGlobalJSObject(JSContext *cx) { return m_pGlobalJSObject; }
	private:
		JSRuntime*		m_pJSRuntime;
		JSContext*		m_pJSContext;
		JSObject*		m_pGlobalJSObject;
		JSObject*		m_pConsoleObject;
		JSScript*		m_pScript;
		
		static MngInst*	gs_pManager;
	};
}



#endif /*___ZZZ_JS_ENGINE_MNG_INST_H___*/