
var wx = require("wx");
var expat = require("expat");
var xml = require("xml");


// メニューID
Widgets_ClearLog　 = wx.NewId();
Widgets_Quit　 = wx.NewId();

Widgets_BookCtrl　 = wx.NewId();

Widgets_SetTooltip　 = wx.NewId();
Widgets_SetFgColour = wx.NewId();
Widgets_SetBgColour = wx.NewId();
Widgets_SetPageBg = wx.NewId();
Widgets_SetFont = wx.NewId();
Widgets_Enable = wx.NewId();
Widgets_Show = wx.NewId();

Widgets_BorderNone = wx.NewId();
Widgets_BorderStatic = wx.NewId();
Widgets_BorderSimple = wx.NewId();
Widgets_BorderRaised = wx.NewId();
Widgets_BorderSunken = wx.NewId();
Widgets_BorderDouble = wx.NewId();
Widgets_BorderDefault = wx.NewId();

Widgets_VariantNormal = wx.NewId();
Widgets_VariantSmall = wx.NewId();
Widgets_VariantMini = wx.NewId();
Widgets_VariantLarge = wx.NewId();

Widgets_LayoutDirection = wx.NewId();

Widgets_GlobalBusyCursor = wx.NewId();
Widgets_BusyCursor = wx.NewId();

Widgets_GoToPage = wx.NewId();
//Widgets_GoToPageLast = Widgets_GoToPage + 100,


//TextEntry_Begin,
TextEntry_DisableAutoComplete = wx.NewId();// = TextEntry_Begin,
TextEntry_AutoCompleteFixed = wx.NewId();
TextEntry_AutoCompleteFilenames = wx.NewId();
TextEntry_AutoCompleteDirectories = wx.NewId();
TextEntry_AutoCompleteCustom = wx.NewId();

TextEntry_SetHint = wx.NewId();
TextEntry_End = wx.NewId();




function fileNewMenu()
{

}

wxTheApp.onInit = function ()
{
    var frame = new wx.Frame(null, -1, "サンプル", wx.DefaultPosition, 
        {width:600, height:900}
        /*new wx.Size(600, 900)*/);
		


	
	frame.onClose = function(evt) {
		this.auiMgr.unInit();		
		evt.skip = true;
	}	
	
	frame.auiMgr = new wx.Aui.Manager(frame);
	
	
	// メニューの作成
	(function () {
		var menuBar = new wx.MenuBar();
		frame.menuWidget = new wx.Menu(); 
		frame.menuWidget.append(
			Widgets_SetTooltip, 	// ID
			"Set &tooltip...\tCtrl-T", // Text
			function(){					// Function
			
			}, 
			"Set &tooltip...\tCtrl-T"	// Help-Text
		); 
		frame.menuWidget.appendSeparator();
		frame.menuWidget.append(Widgets_SetFgColour, "Set &foreground...\tCtrl-F", function(){
			
		}, "Set &foreground...\tCtrl-F"); 
		frame.menuWidget.append(Widgets_SetBgColour, "Set &background...\tCtrl-B", function(){
			
		}, "Set &background...\tCtrl-B"); 
		frame.menuWidget.append(Widgets_SetPageBg, "Set &page background...\tShift-Ctrl-B", function(){
			
		}, "Set &page background...\tShift-Ctrl-B"); 
		frame.menuWidget.append(Widgets_SetFont, "Set f&ont...\tCtrl-O", function(){
			
		}, "Set f&ont...\tCtrl-O");
		frame.menuWidget.appendCheckItem(Widgets_Enable, "&Enable/disable\tCtrl-E", function(){
			
		}, "&Enable/disable\tCtrl-E"); 
		frame.menuWidget.appendCheckItem(Widgets_Show, "Show/Hide", function(){
			
		}, "Show/Hide"); 
		
		// ボーダー設定のサブメニューの作成
		frame.menuBorders = new wx.Menu(); 
		frame.menuBorders.appendRadioItem(Widgets_BorderDefault, "De&fault\tCtrl-Shift-9", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderNone,   "&None\tCtrl-Shift-0", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderSimple, "&Simple\tCtrl-Shift-1", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderDouble, "&Double\tCtrl-Shift-2", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderStatic, "Stati&c\tCtrl-Shift-3", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderRaised, "&Raised\tCtrl-Shift-4", function(){
			
		}, ""); 
		frame.menuBorders.appendRadioItem(Widgets_BorderSunken, "S&unken\tCtrl-Shift-5", function(){
			
		}, ""); 
		frame.menuWidget.appendSubMenu(frame.menuBorders, "Set &border");
		
		
		frame.menuVariants = new wx.Menu(); 
		frame.menuVariants.appendRadioItem(Widgets_VariantMini, "&Mini\tCtrl-Shift-6");
		frame.menuVariants.appendRadioItem(Widgets_VariantSmall, "&Small\tCtrl-Shift-7");
		frame.menuVariants.appendRadioItem(Widgets_VariantNormal, "&Normal\tCtrl-Shift-8");
		frame.menuVariants.appendRadioItem(Widgets_VariantLarge, "&Large\tCtrl-Shift-9");
		frame.menuWidget.appendSubMenu(frame.menuVariants, "Set &variant");
		
		
		frame.menuWidget.appendSeparator();
		
		frame.menuWidget.appendCheckItem(Widgets_LayoutDirection,
								"Toggle &layout direction\tCtrl-L");

		frame.menuWidget.appendSeparator();
		frame.menuWidget.appendCheckItem(Widgets_GlobalBusyCursor,
								"Toggle &global busy cursor\tCtrl-Shift-U");
		frame.menuWidget.appendCheckItem(Widgets_BusyCursor,
								"Toggle b&usy cursor\tCtrl-U");

		frame.menuWidget.appendSeparator();
		frame.menuWidget.append(wx.Id.EXIT, "&Quit\tCtrl-Q", function(){
			// アプリを終了します。
			this.close();
		}, "&Quit\tCtrl-Q"); 
		menuBar.append(frame.menuWidget, "&Widget");
		
		
		frame.menuTextEntry = new wx.Menu();
		frame.menuTextEntry.appendRadioItem(TextEntry_DisableAutoComplete,
									   "&Disable auto-completion");
		frame.menuTextEntry.appendRadioItem(TextEntry_AutoCompleteFixed,
									   "Fixed-&list auto-completion");
		frame.menuTextEntry.appendRadioItem(TextEntry_AutoCompleteFilenames,
									   "&Files names auto-completion");
		frame.menuTextEntry.appendRadioItem(TextEntry_AutoCompleteDirectories,
									   "&Directories names auto-completion");
		frame.menuTextEntry.appendRadioItem(TextEntry_AutoCompleteCustom,
									   "&Custom auto-completion");
		frame.menuTextEntry.appendSeparator();
		frame.menuTextEntry.append(TextEntry_SetHint, "Set help &hint");
		menuBar.append(frame.menuTextEntry, "&Text");

		menuBar.check(Widgets_Enable, true);
		menuBar.check(Widgets_Show, true);
		menuBar.check(Widgets_VariantNormal, true);
		
		frame.menuBar = menuBar;
	}());

	
    // create controls
	frame.m_panel = new wx.Panel(frame, -1);
    var sizerTop = new wx.BoxSizer(wx.Orientation.VERTICAL);
	
	
    // the lower one only has the log listbox and a button to clear it
	var sizerDown = new wx.StaticBoxSizer(
			new wx.StaticBox( frame.m_panel, -1/*wx.Id.ANY*/, "&Log window" )
		,	wx.Orientation.VERTICAL
	);
	
    frame.m_lboxLog = new wx.ListBox(frame.m_panel, -1);
	sizerDown.add(frame.m_lboxLog, 1, wx.Stretch.GROW | wx.Stretch.ALL, 5);
	sizerDown.setMinSize(100, 150);
	
	var sizerBtns = new wx.BoxSizer(wx.Orientation.HORIZONTAL);
	var btn = new wx.Button(frame.m_panel, Widgets_ClearLog, "Clear &log");
	sizerBtns.add(btn);
    sizerBtns.add(10, 0); // spacer
	btn = new wx.Button(frame.m_panel, Widgets_Quit, "E&xit");
	sizerBtns.add(btn);
    sizerDown.add(sizerBtns, 0, wx.Stretch.ALL | wx.Stretch.ALIGN_RIGHT, 5);
	
	
	
    sizerTop.add(sizerDown, 0,  wx.Stretch.GROW | (wx.Stretch.ALL & ~wx.Stretch.TOP), 10);
	
    frame.m_panel.setSizer(sizerTop);
	var sizeMin = frame.m_panel.bestSize;

	frame.autoLayout = true;
	frame.layout();
	
	
    // Don't forget to show the frame by setting the visible property to true!
	frame.setVisible(true);
    wxTheApp.topWindow = frame;
	

	frame.auiMgr.update();		
	
	return true;
};

