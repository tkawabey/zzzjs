

#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include <wx/app.h>
#include <wx/config.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
#include <wx/xrc/xmlres.h>
#include <wx/xml/xml.h>

#include "js/app/app.h"
#include "gui/appmain.h"
#include "js/common/jsutil.h"

#include <string>


//------------------------------------------------------------
//
//	appMain
//
//------------------------------------------------------------

IMPLEMENT_APP(appMain)
appMain::appMain()
{
	//uint64_t aaa = 1;//2^53;

	//aaa <<= 53;

}


appMain::~appMain()
{
}

bool appMain::Initialize(int& argc, wxChar **argv)
{
	int i = 0;
	bool bNextScript = false;
	bool bNextArgv = false;




	for(i = 1; i < argc; i++)
	{
		if( wxStricmp(argv[i], L"-s") == 0 )
		{
			bNextScript = true;
		} 
		else
		if( wxStricmp(argv[i], L"-a") == 0 )
		{
			bNextArgv = true;
		}


		else
		{
			if( bNextScript == true ) 
			{
				bNextScript = false;
				m_strStartupJS = argv[i];
			}
			else
			if( bNextArgv == true ) 
			{
				m_cntArgv.push_back( wxString(argv[i]) );
			}
		}
	}


	return wxApp::Initialize(argc, argv);
}

bool appMain::OnInit(void)
{	
	// Exeのあるディレクトリがベース
	wxString strDir;
	wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(), &strDir, NULL, NULL);
	m_strBaseDir = (const TCHAR*)strDir.c_str();
	
	// ローケルをデフォルトに設定
	if ( !m_locale.Init(wxLANGUAGE_DEFAULT, 0/*wxLOCALE_CONV_ENCODING*/) ) {
		wxLogError(_("This language is not supported by the system."));
		return false;
	}
	wxFileName filenameLocalDir(m_strBaseDir.c_str(), _T("lang"));
	wxLocale::AddCatalogLookupPathPrefix( filenameLocalDir.GetFullPath() );

	m_locale.AddCatalog(wxT("internat"));
#ifdef __LINUX__
	{
		wxLogNull noLog;
		m_locale.AddCatalog(_T("fileutils"));
	}
#endif
	
	// 画像を扱うための初期化
	wxInitAllImageHandlers();

#if wxUSE_STREAMS && wxUSE_ZIPSTREAM && wxUSE_ZLIB
	wxFileSystem::AddHandler(new wxZipFSHandler);
#endif

	// wxConfig のために必要な情報をセット
	SetVendorName( APP_NAME );
	SetAppName( APP_NAME );

	

	// JS管理インスタンスを初期化
	if( zzzJs::MngInst::instance()->initRuntime() == false ) {
		return false;
	}

	
	SetExitOnFrameDelete(true); 

	return wxApp::OnInit();
}





int appMain::OnRun()
{
	{
		int i = 0;
		std::vector<wxString>::iterator iteArg;
		JSContext* cx = zzzJs::MngInst::instance()->getContext();
		JSObject*  pO = zzzJs::MngInst::instance()->getGlobalJSObject(cx);

		zzzJs::App::define_Class(cx, pO );
		JSAutoCompartment protoc(cx, pO );
		JSObject *jsApp = JS_NewObject(cx, 
			zzzJs::App::GetClass(), NULL, NULL);
		JS_SetPrivate( jsApp, wxTheApp);
		JS_DefineProperty(cx, pO, "wxTheApp", OBJECT_TO_JSVAL(jsApp), NULL, NULL, 0);
		zzzJs::App::DefineProperties(cx, jsApp);



		// JSに渡す引数の設定
		JSObject *objOptArr = JS_NewArrayObject(cx, 0, NULL);
		JS_DefineProperty(cx, jsApp, "argv", 
			OBJECT_TO_JSVAL(objOptArr), NULL, NULL, 
			JSPROP_PERMANENT | JSPROP_READONLY); 
		iteArg = m_cntArgv.begin();
		for(i = 0; iteArg != m_cntArgv.end(); iteArg++, i++ )
		{
			wxString& argvVal = *iteArg;
			jsval pval = zzzJs::ToJS(cx, argvVal);
			JS_SetElement(cx, objOptArr, 0, &pval);
		}




		wxCSConv *conv = new wxCSConv(_T("UTF-8"));
		wxString scriptPath = m_strBaseDir;

		if( m_strStartupJS.Length() == 0 ) 
		{
			// 指定が無い場合デフォルトで、カレントディレクトリにある、main.jsを使用する。
			scriptPath += _("\\main.js");
		}
		else
		{
			scriptPath = m_strStartupJS;
		}
		// 起動時のスクリプトが存在するか確認
		if (wxFileName::FileExists(scriptPath) == false )
		{
			wxLogError(_T("FILE:%s dose not exist."), scriptPath.c_str());
			return 0;
		}




		

		wxFileName fname;
		fname.Assign(scriptPath);

		zzzJs::MngInst::instance()->RunScript(cx, fname, *conv);


		// our onInit
		jsval fval;
		if ( zzzJs::GetFunctionProperty(cx, jsApp, "onInit", &fval) == JS_TRUE )
		{
			if( fval.isObject() == true ) 
			{
				jsval rval;
				if ( JS_CallFunctionValue(cx, jsApp, fval, 0, NULL, &rval) == JS_TRUE )
				{
					if ( JSVAL_IS_BOOLEAN(rval) )
					{
						if ( JSVAL_TO_BOOLEAN(rval) == JS_FALSE )
						{
							return 0;
						}
					}
				}
			}
			else
			{
				wxLogError( _T("JavaScript: ") );
				//	, (const TCHAR*)strFName, report->lineno+1
				//	, (const TCHAR*)strMessage);
				JS_ReportPendingException(cx);
				return 0;
			}
		}

		JS_GC( zzzJs::MngInst::instance()->getRuntime() );
	}



	bool initialized = (wxTopLevelWindows.GetCount() != 0);
	if ( initialized )
	{
		if ( GetTopWindow()->IsShown() )
		{
			int bRet = wxApp::MainLoop(); 
			return bRet; 
		}
	}
	return 0;
}
int appMain::OnExit(void)
{
	wxLogDebug(_T("appMain::OnExit"));

	wxTheApp->SetClientObject(NULL); // Unroot the application object
	//engine->FreeContext(cx);

	return 0;
}
void appMain::CleanUp()
{
	wxLogDebug(_T("appMain::CleanUp"));
	zzzJs::MngInst::release();
}



void appMain::writeLog(const TCHAR* p_format, ...)
{
	wxString str;	
	va_list argList;
	va_start(argList, p_format);
	str.PrintfV(p_format, argList);
	va_end(argList);
	str += _T("\n");
/*
	wxWindow* pFram = wxGetApp().GetTopWindow();
	if( ! pFram->IsKindOf(CLASSINFO(FrameMain))  ) {
		return ;
	}
	((FrameMain*)pFram)->writeLog(str);
*/
}

