#ifndef __ZZZ_JS_GUI_APPMAIN_H__
#define __ZZZ_JS_GUI_APPMAIN_H__


#include <vector>
#include <tchar.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>
#include "js/engine/mng_inst.h"




#define	APP_NAME		_T("zzzjs")

class DProject;
class XsdSchema;


/**	@brief	このアプリケーションのインスタンス	 */
class appMain: public wxApp
{
public:
	typedef struct tagSCRIPT
	{
		wxString	m_strScriptPath;
	}SCRIPT;

	typedef struct tagLANG_STYLE
	{
		wxString	m_strRefName;
		wxString	m_strKeywords;
	}LANG_STYLE;

	typedef struct tagLANG
	{
		wxString	m_strLang;
		int			m_lex;
		int			m_fold;
		std::vector<LANG_STYLE>	m_cntStyles;
	}LANG;

	typedef struct tagSTYLE
	{
		wxString	m_strName;
		wxString	m_strForeground;
		wxString	m_strBackground;
		wxString	m_strFontname;
		int			m_nFontsizee;
		int			m_nFontStyle;
		int			m_nLettercase;
	}STYLE;


	appMain();
	virtual ~appMain();

// imple wxApp
    virtual bool Initialize(int& argc, wxChar **argv);
    virtual bool OnInit(void);
    virtual int OnRun();
    virtual int OnExit(void);
	virtual void CleanUp();

	wxPGEditor* getCustomEditor_Params(){ return m_pCustomEditor_Params; }
	wxPGEditor* getCustomEditor_Args(){ return m_pCustomEditor_Args; }

	void writeLog(const TCHAR* p_format, ...);
	bool loadConf();
	bool loadXsd();
	bool reloadScript();
public:
	std::vector<DProject*>& getData(){ return m_data; }
	std::vector<LANG>& getLangs() {return m_langs; }
	std::vector<STYLE>& getStyles() {return m_styles; }
	bool openFile(const wxString& strFilePath);
public:
	XsdSchema* getSchema(){ return m_pSchema; }
private:
	wxString							m_strBaseDir;	// 画面表示のスタイル情報一覧
	wxString							m_strJS;		// Javascriptファイルのパス
	wxLocale							m_locale;		
	std::vector<SCRIPT>					m_scripts;
	std::vector<DProject*>				m_data;
	std::vector<LANG>					m_langs;
	std::vector<STYLE>					m_styles;

	XsdSchema*							m_pSchema;

	
	wxPGEditor*							m_pCustomEditor_Params;
	wxPGEditor*							m_pCustomEditor_Args;


	wxString							m_strStartupJS;
	std::vector<wxString>				m_cntArgv;
//	zzzJs::MngInst						m_jsMngInst;
};
DECLARE_APP( appMain )

#endif /*__ZZZ_JS_GUI_APPMAIN_H__*/