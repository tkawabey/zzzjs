
var LogPane = function (frame) {
    this.ID_LOG_TXTCTRL = wx.NewId();
    this.panel = new wx.Panel(frame, -1);
    //this.panel.setBackgroundColour(new wx.Colour(50,0,255));
    this.topSizer = new wx.BoxSizer(wx.Orientation.VERTICAL);
    this.pTxtCtrl = new wx.TextCtrl(this.panel, this.ID_LOG_TXTCTRL,
        "", wx.DefaultPosition, wx.DefaultSize, 
        wx.TextCtrl.MULTILINE | wx.TextCtrl.READONLY | wx.TextCtrl.RICH2 | wx.TextCtrl.AUTO_URL | wx.Window.HSCROLL);
    this.topSizer.add(this.pTxtCtrl, 1, wx.Direction.ALL | wx.Stretch.EXPAND | wx.Stretch.GROW);
    this.panel.setSizer(this.topSizer);
    this.panel.fit();

    
    var ulLogLevel = wx.Log.getLogLevel();
    ulLogLevel |= wx.LogLevel.Info;
    wx.Log.setLogLevel(ulLogLevel);
/*
    this.logChanin = new wx.LogChain(new wx.LogText(this.pTxtCtrl));
    wx.Log.setActiveTarget(this.logChanin);
*/
    wx.Log.setActiveTarget(new wx.LogText(this.pTxtCtrl));
    frame.auiMgr.addPane(this.panel, new wx.Aui.PaneInfo().
				name("Log").
				bottom().
				maximizeButton().
				minimizeButton().
				closeButton(false).
				caption("Log")
    );
}



















