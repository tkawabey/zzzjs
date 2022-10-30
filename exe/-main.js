
var wx = require("wx");
var expat = require("expat");
var xml = require("xml");
include(this, wxjs.root + "/RightPane.js", "utf-8");
include(this, wxjs.root + "/LeftPane.js", "utf-8");
include(this, wxjs.root + "/LogPane.js", "utf-8");
include(this, wxjs.root + "/xml.js", "utf-8");
include(this, wxjs.root + "/xsdSchemas.js", "utf-8");

ID_NEW_MENU = wx.NewId();
ID_OPEN_MENU = wx.NewId();
ID_SAVE_MENU = wx.NewId();
ID_ABOUT_MENU = wx.NewId();
         


var g_Schema = new XsdSchema();


wxTheApp.onInit = init;

function fileNewMenu()
{

}

function fileOpenMenu()
{
    var dlg = new wx.FileDialog(this, "Open a file");
    dlg.style = wx.FileDialog.OPEN;
    if( dlg.showModal() != wx.Id.OK ) {
        return;
    }
    var xmlDoc = new xml.XmlDocument();
    xmlDoc.load(dlg.path);

    var rootNode = xmlDoc.root;
    //    this.m_pPanelLeft.setTree(rootNode);


    //    var elms = parseXMLFile(dlg.path);
    g_Schema = new XsdSchema();
    if (g_Schema.load(rootNode) == false) {
        print( "fail to load schema!" );
    }


    this.m_pPanelLeft.panelXsd.setTree(g_Schema);
    //g_dataPrj.load(elms);
    //    this.m_pPanelLeft.setTree(elms);
  
}

function fileSaveMenu()
{
    var dlg = new wx.FileDialog(this, "Save a file");
    dlg.style = wx.FileDialog.SAVE;
    dlg.showModal();
}

/*
var propNames = [];
var o = this;
wxjs.print("o=" + o );
while ( o ) {
	propNames = propNames.concat( Object.getOwnPropertyNames( o ) );
	o = Object.getPrototypeOf( o );
}
print("propNames=" + propNames );
*/

//print(ctypes.UInt64);
//var aaaa = ctypes.UInt64(1012456489415615648);




function init() {
    var frame = new wx.Frame(null, -1, "サンプル", wx.DefaultPosition, 
        {width:600, height:900}
        /*new wx.Size(600, 900)*/);
	var wkPane;
	var wkNoteBook;

    // ローケルの初期化
	frame.locale = new wx.Locale();
	frame.locale.init(wx.Language.DEFAULT);
	frame.locale.addCatalogLookupPathPrefix(wxjs.root);
	frame.locale.addCatalog("internat");


	
	var menuBar = new wx.MenuBar();
	frame.menu = new wx.Menu(); 
	frame.menu.append(ID_NEW_MENU, "New", fileNewMenu, "Creates a new file"); 
	frame.menu.append(ID_OPEN_MENU, "Open", fileOpenMenu, "Opens an existing file");
	frame.menu.append(ID_SAVE_MENU, "Save", fileSaveMenu, "Saves the content to a file");

	menuBar.append(frame.menu, "File");
	frame.menuBar = menuBar;
	
    frame.createStatusBar(2);

//	wxjs.print("o=" + frame.title );
    frame.setStatusWidths(new Array(100, -1, -1));
	frame.title = "さんぷる";
//	wxjs.print("o=" + frame.title );
	
	
	frame.onClose = function(evt) {
		this.auiMgr.unInit();		
		evt.skip = true;
	}	
	
	frame.auiMgr = new wx.Aui.Manager(frame);
	
	//var aaa = frame.auiMgr.dockSizeConstraint
	//o = aaa;
	//propNames = "";
	//while ( o ) {
	//	propNames = propNames.concat( Object.getOwnPropertyNames( o ) );
	//	o = Object.getPrototypeOf( o );
	//}
	//print("propNames=" + propNames );	
	//print("" + aaa.widthpct);
	//print("" + aaa.heightpct);
	//frame.auiMgr.dockSizeConstraint = { widthpct:1.4,  heightpct:0.5 };
	//aaa = frame.auiMgr.dockSizeConstraint	
	//print("" + aaa.widthpct);
	//print("" + aaa.heightpct);
	
	
    //frame.auiMgr.setManagedWindow(frame);




    //　右パネルの作成。	
	frame.m_pPanelRight = new RightPane(frame);
    // 左パネルの作成	
	frame.m_pPanelLeft = new LeftPane(frame);
    // ログパネル
	frame.m_pPanelLog = new LogPane(frame);
	
	frame.autoLayout = true;
	frame.layout();	
	
	
    // Don't forget to show the frame by setting the visible property to true!
	frame.setVisible(true);
    wxTheApp.topWindow = frame;

	frame.auiMgr.update();		
	
	
    // XSDのオブジェクトが選択された。
	frame.notifyXSDItem = function (obj) {
        // 右パネルの更新
	    this.m_pPanelRight.notifyXSDItem(obj);
        // AUIの更新
	    this.auiMgr.update();
	}
//	var aaaa = 0x2fffffffffffff;
//	var aaaa = 0x20000000000000;
//	var aaaa = -0.123;
    //	print(typeof aaaa);

//	print(aaaa);
//	aaaa -= 1;
//	print(aaaa);

    return true;
}

