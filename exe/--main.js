
var wx = require("wx");
var xml = require("xml");


ID_NEW_MENU = wx.NewId();
ID_OPEN_MENU = wx.NewId();
ID_SAVE_MENU = wx.NewId();
ID_ABOUT_MENU = wx.NewId();


wxTheApp.onInit = init;

MENUID = {
    // menu items
    File_Quit:0,// = wxID_EXIT,
    File_About : 1,// = wxID_ABOUT,

    MenuShow_First : 2,// = wxID_HIGHEST,
    File_ShowDefault :  3,//= MenuShow_First,
    File_ShowText : 4,
    File_ShowLines : 5,
    File_ShowBrushes : 6,
    File_ShowPolygons : 7,
    File_ShowMask : 8,
    File_ShowMaskStretch : 9,
    File_ShowOps : 10,
    File_ShowRegions : 11,
    File_ShowCircles : 12,
    File_ShowSplines : 13,
//#if wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
    File_ShowAlpha : 14,
//#endif // wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
//#if wxUSE_GRAPHICS_CONTEXT
   File_ShowGraphics : 15,
//#endif
   File_ShowSystemColours : 16,
   File_ShowGradients : 17,
   MenuShow_Last : 18,// = File_ShowGradients,

//#if wxUSE_GRAPHICS_CONTEXT
    File_DC : 19,
    File_GC_Default : 20,
//#if wxUSE_CAIRO
    File_GC_Cairo : 21,
//#endif // wxUSE_CAIRO
//#ifdef __WXMSW__
//#if wxUSE_GRAPHICS_GDIPLUS
    File_GC_GDIPlus : 22,
//#endif
//#if wxUSE_GRAPHICS_DIRECT2D
    File_GC_Direct2D : 23,
//#endif
//#endif // __WXMSW__
//#endif // wxUSE_GRAPHICS_CONTEXT
    File_Clip : 24,
    File_Buffer : 25,
    File_Copy : 26,
    File_Save : 27,

    MenuOption_First : 28,

    MapMode_Text : 29,// = MenuOption_First,
    MapMode_Lometric : 30,
    MapMode_Twips : 31,
    MapMode_Points : 32,
    MapMode_Metric : 33,

    UserScale_StretchHoriz : 34,
    UserScale_ShrinkHoriz : 35,
    UserScale_StretchVertic : 36,
    UserScale_ShrinkVertic : 37,
    UserScale_Restore : 38,

    AxisMirror_Horiz : 39,
    AxisMirror_Vertic : 40,

    LogicalOrigin_MoveDown : 41,
    LogicalOrigin_MoveUp : 42,
    LogicalOrigin_MoveLeft : 43,
    LogicalOrigin_MoveRight : 44,
    LogicalOrigin_Set : 45,
    LogicalOrigin_Restore : 46,

//#if wxUSE_COLOURDLG
    Colour_TextForeground : 47,
    Colour_TextBackground : 48,
    Colour_Background : 49,
//#endif // wxUSE_COLOURDLG
    Colour_BackgroundMode : 50,
    Colour_TextureBackgound : 51,

    MenuOption_Last: 52// = Colour_TextureBackgound
};


// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------
gs_bmpNoMask = wx.Bitmap();
gs_bmpWithColMask= wx.Bitmap();
gs_bmpMask= wx.Bitmap();
gs_bmpWithMask= wx.Bitmap();
gs_bmp4= wx.Bitmap();
gs_bmp4_mono= wx.Bitmap();
gs_bmp36= wx.Bitmap();

rasterOperations = [
    ["wxAND", wx.RasterOperationMode.AND],
    ["wxAND_INVERT", wx.RasterOperationMode.AND_INVERT],
    ["wxAND_REVERSE", wx.RasterOperationMode.AND_REVERSE],
    ["wxCLEAR", wx.RasterOperationMode.CLEAR],
    ["wxCOPY", wx.RasterOperationMode.COPY],
    ["wxEQUIV", wx.RasterOperationMode.EQUIV],
    ["wxINVERT", wx.RasterOperationMode.INVERT],
    ["wxNAND", wx.RasterOperationMode.NAND],
    ["wxNO_OP", wx.RasterOperationMode.NO_OP],
    ["wxOR", wx.RasterOperationMode.OR],
    ["wxOR_INVERT", wx.RasterOperationMode.OR_INVERT],
    ["wxOR_REVERSE", wx.RasterOperationMode.OR_REVERSE],
    ["wxSET", wx.RasterOperationMode.SET],
    ["wxSRC_INVERT", wx.RasterOperationMode.SRC_INVERT],
    ["wxXOR", wx.RasterOperationMode.XOR],
];


function wxT(v) {
    return v;
}

function loadImages() {
    /* 4 colour bitmap */
    gs_bmpNoMask.loadFile(wxjs.root + "\\pat4.bmp", wx.Bitmap.BMP);
    /* turn into mono-bitmap */
    gs_bmp4_mono.loadFile(wxjs.root + "\\pat4.bmp", wx.Bitmap.BMP);
    var mask4 = new wx.Mask(gs_bmp4_mono, wx.BLACK);
    gs_bmp4_mono.setMask(mask4);




    gs_bmp36.loadFile(wxjs.root + "\\pat36.bmp", wx.Bitmap.BMP);
    mask36 = new wx.Mask(gs_bmp36, wx.BLACK);
    gs_bmp36.setMask(mask36);

    gs_bmpNoMask.loadFile(wxjs.root + "\\image.bmp", wx.Bitmap.BMP);
    gs_bmpWithMask.loadFile(wxjs.root + "\\image.bmp", wx.Bitmap.BMP);
    gs_bmpWithColMask.loadFile(wxjs.root + "\\image.bmp", wx.Bitmap.BMP);


    gs_bmpMask.loadFile(wxjs.root + "\\mask.bmp", wx.Bitmap.BMP);
    mask = new wx.Mask(gs_bmpMask, wx.BLACK);
    gs_bmpWithMask.setMask(mask);

    mask = new wx.Mask(gs_bmpWithColMask, wx.WHITE);
    gs_bmpWithColMask.setMask(mask);

}

function init() {
    var frame = new wx.Frame();

    loadImages();

    frame.m_backgroundMode = wx.SOLID;
    frame.m_textureBackground = false;
    frame.m_mapMode = wx.MappingMode.TEXT;
    frame.m_xUserScale = 1.0;
    frame.m_yUserScale = 1.0;
    frame.m_xLogicalOrigin = 0;
    frame.m_yLogicalOrigin = 0;
    frame.m_xAxisReversed = false;
    frame.m_yAxisReversed = false;
    frame.m_colourForeground = wx.BLACK; // wxColour
    frame.m_colourBackground = wx.LIGHT_GREY; // wxColour
    frame.m_backgroundBrush = new wx.Brush(); // wxBrush
    frame.m_menuItemUseDC = null;// wxMenuItem

    frame.create(null, -1, "サンプル",
        wx.DefaultPosition,
        {width:550, height:840},
        wx.Frame.DEFAULT_FRAME_STYLE | wx.Window.NO_FULL_REPAINT_ON_RESIZ);

    // 
    frame.onMenuShow = function (evt) {
        this.canvas.toShow(evt.id);
    }
    menuScreen = new wx.Menu();
    menuScreen.append(MENUID.File_ShowDefault, "&Default screen\tF1", 
        frame.onMenuShow, "Default screen");
    menuScreen.append(MENUID.File_ShowText, "&Text screen\tF2",
        frame.onMenuShow, "Text screen");
    menuScreen.append(MENUID.File_ShowLines, "&Lines screen\tF3",
        frame.onMenuShow, "Lines screen");
    menuScreen.append(MENUID.File_ShowBrushes, "&Brushes screen\tF4",
        frame.onMenuShow, "Polygons screen");
    menuScreen.append(MENUID.File_ShowPolygons, "&Polygons screen\tF5",
        frame.onMenuShow, "Polygons screen");
    menuScreen.append(MENUID.File_ShowMask, "&Mask screen\tF6",
        frame.onMenuShow, "Mask screen");
    menuScreen.append(MENUID.File_ShowMaskStretch, "1/&2 scaled mask\tShift-F6",
        frame.onMenuShow, "1/&2 scaled mask");
    menuScreen.append(MENUID.File_ShowOps, "&Raster operations screen\tF7",
        frame.onMenuShow, "Raster operations screen");
    menuScreen.append(MENUID.File_ShowRegions, "Re&gions screen\tF8",
        frame.onMenuShow, "Regions screen");
    menuScreen.append(MENUID.File_ShowCircles, "&Circles screen\tF9",
        frame.onMenuShow, "Circles screen");
    // MENUID.File_ShowAlpha
    menuScreen.append(MENUID.File_ShowSplines, "Spl&ines screen\tF11",
        frame.onMenuShow, "Splines screen");
    menuScreen.append(MENUID.File_ShowGradients, "&Gradients screen\tF12",
        frame.onMenuShow, "Gradients screen");

    menuFile = new wx.Menu();
    menuFile.append(MENUID.File_GC_Default, "Use wx&DC\tShift-Ctrl-Y",
        frame.onMenuShow, "Gradients screen");

    menuBar = new wx.MenuBar();
    menuBar.append(menuFile, wxT("&Drawing"));
    menuBar.append(menuScreen, "Scree&n");
    frame.menuBar = menuBar;


    // ScrolledWindowを拡張して、キャンバスを作成
    frame.canvas = new wx.ScrolledWindow(frame,
        -1, wx.DefaultPosition, wx.DefaultSize,
        wx.Window.HSCROLL | wx.Window.VSCROLL | wx.Window.NO_FULL_REPAINT_ON_RESIZE);
    frame.canvas.m_owner = frame;
    frame.canvas.m_smile_bmp = new wx.Bitmap({ filepath: wxjs.root + "\\smile.xpm", type: wx.Bitmap.XPM });
    frame.canvas.m_std_icon = wx.ArtProvider.getIcon(wx.ArtProvider.INFORMATION);
    frame.canvas.setScrollbars(10, 10, 100, 240);

    frame.canvas.m_show = MENUID.File_ShowRegions; // 初期デフォルト




    frame.setIcon(frame.canvas.m_std_icon);

    frame.canvas.toShow = function (show) {
        this.m_show = show;
        this.refresh();
    }
    // Callbackの実装
    frame.canvas.onPaint = function (evt) {
        var dc =  new wx.PaintDC(this);
        try {
            this.draw(dc);
        } finally {
            dc.release();
        }
    }
    frame.canvas.onMotion = function (evt) {

    }
    // canvasのメンバー関数の実装
    frame.canvas.draw = function (dc) {

        this.prepareDC(dc);
        this.m_owner.prepareDC(dc);

        dc.backgroundMode = this.m_owner.m_backgroundMode;
        if (this.m_owner.m_backgroundBrush.isOk == true) {
            dc.setBackground(this.m_owner.m_backgroundBrush);
        }
        if (this.m_owner.m_colourForeground.isOk == true) {
            dc.textForeground = this.m_owner.m_colourForeground;
        }
        if (this.m_owner.m_colourBackground.isOk == true) {
            dc.textBackground = this.m_owner.m_colourBackground;
        }

        //dc.setClippingRegion(100, 100, 100, 100);

        dc.clear();

        dc.setPen(wx.MEDIUM_GREY_PEN);
        //dc.setPen({ colour: wx.GREEN, width: 5 });
        for (var i = 0; i < 200; i++) {
            dc.drawLine(0, i * 10, i * 10, 0);
        }
        switch (this.m_show) {
            case MENUID.File_ShowDefault:
                this.drawDefault(dc);
                break;
            case MENUID.File_ShowCircles:
                this.drawCircles(dc);
                break;
            case MENUID.File_ShowText:
                this.drawText(dc);
                break;
            case MENUID.File_ShowSplines:
                this.drawSplines(dc);
                break;
            case MENUID.File_ShowLines:
                this.drawTestLines(0, 100, 0, dc);
                this.drawTestLines(0, 320, 1, dc);
                this.drawTestLines(0, 540, 2, dc);
                this.drawTestLines(0, 760, 6, dc);
                break;
            case MENUID.File_ShowBrushes:
                this.drawTestBrushes(dc);
                break;
            case MENUID.File_ShowPolygons:
                this.drawTestPoly(dc);
                break;
            case MENUID.File_ShowGradients:
                this.drawGradients(dc);
                break;
            case MENUID.File_ShowMask:
                this.drawImages(dc, false);
                break;
            case MENUID.File_ShowMaskStretch:
                this.drawImages(dc, true);
                break;
            case MENUID.File_ShowOps:
                this.drawWithLogicalOps(dc);
                break;
            case MENUID.File_ShowRegions:
                this.drawRegions(dc);
                break;
        }
        //        dc.clear();

    }
    
    frame.canvas.drawDefault = function (dc) {
//        var img = new wx.Image(21, 21, false);
        var bmp = new wx.Bitmap({ img: new wx.Image(21, 21, false) });
        var mdc = new wx.MemoryDC(bmp);
        try {
//            dc.setPen({ colour: wx.RED, width: 1 });
            mdc.setBrush(dc.getBrush());
            mdc.setPen(dc.getPen());
            mdc.setPen({ colour: wx.RED, width: 1 });
            mdc.drawCircle(10, 10, 10);
            var c = mdc.getPixel(11, 11);
            if (c != null)
            {
                mdc.setBrush({ colour: { r: 128, g: 128, b: 0 }} );
                mdc.floodFill(11, 11, c, 1/*wx.FLOOD_SURFACE*/);
            }
        } finally {
            mdc.release();
        }
        //            bmp.SetMask(new wxMask(bmp, wxColour(1, 1, 1)));
        dc.drawBitmap(bmp, 10, 10, true);

        dc.drawCheckMark(5, 80, 15, 15);
        dc.drawCheckMark(25, 80, 30, 30);
        dc.drawCheckMark(60, 80, 60, 60);


        dc.setBrush( wx.BLACK_BRUSH );
        dc.drawRectangle(0, 160, 1000, 300);

        // draw lines
        var bitmap = new wx.Bitmap(20,70);
        var memdc = new wx.MemoryDC();
        try {
            memdc.selectObject( bitmap );
            memdc.setBrush( wx.BLACK_BRUSH );
            memdc.setPen( wx.WHITE_PEN );
            memdc.drawRectangle(0,0,20,70);
            memdc.drawLine(10, 0, 10, 70);

            // draw lines


            // to the right
            memdc.setPen(wx.RED_PEN);
            memdc.drawLine( 10, 5,10, 5 );
            memdc.drawLine( 10,10,11,10 );
            memdc.drawLine( 10,15,12,15 );
            memdc.drawLine(10, 20, 13, 20);


            // same to the left
            memdc.drawLine(10, 25, 10, 25);
            memdc.drawLine(10, 30, 9, 30);
            memdc.drawLine(10, 35, 8, 35);
            memdc.drawLine(10, 40, 7, 40);
            
            // XOR draw lines
            dc.setPen(wx.WHITE_PEN);
            memdc.logicalFunction = 2;//wx.INVERT;
            memdc.setPen( wx.WHITE_PEN );
            memdc.drawLine( 10,50,10,50 );
            memdc.drawLine( 10,55,11,55 );
            memdc.drawLine( 10,60,12,60 );
            memdc.drawLine( 10,65,13,65 );

            memdc.drawLine( 12,50,12,50 );
            memdc.drawLine( 12,55,13,55 );
            memdc.drawLine( 12,60,14,60 );
            memdc.drawLine( 12,65,15,65 );
        } finally {
            memdc.release();
        }
        dc.drawBitmap(bitmap, 10, 170);

        //

        // test the rectangle outline drawing - there should be one pixel between
        // the rect and the lines
        dc.setPen(wx.WHITE_PEN);
        dc.setBrush( wx.TRANSPARENT_BRUSH );
        dc.drawRectangle(150, 170, 49, 29);
        dc.drawRectangle(200, 170, 49, 29);
        dc.setPen(wx.WHITE_PEN);
        dc.drawLine(250, 210, 250, 170);
        dc.drawLine(260, 200, 150, 200);

        // test the rectangle filled drawing - there should be one pixel between
        // the rect and the lines
        dc.setPen(wx.TRANSPARENT_PEN);
        dc.setBrush( wx.WHITE_BRUSH );
        dc.drawRectangle(300, 170, 49, 29);
        dc.drawRectangle(350, 170, 49, 29);
        dc.setPen(wx.WHITE_PEN);
        dc.drawLine(400, 170, 400, 210);
        dc.drawLine(300, 200, 410, 200);

        // a few more tests of this kind
        dc.setPen(wx.RED_PEN);
        dc.setBrush( wx.WHITE_BRUSH );
        dc.drawRectangle(300, 220, 1, 1);
        dc.drawRectangle(310, 220, 2, 2);
        dc.drawRectangle(320, 220, 3, 3);
        dc.drawRectangle(330, 220, 4, 4);

        dc.setPen(wx.TRANSPARENT_PEN);
        dc.setBrush( wx.WHITE_BRUSH );
        dc.drawRectangle(300, 230, 1, 1);
        dc.drawRectangle(310, 230, 2, 2);
        dc.drawRectangle(320, 230, 3, 3);
        dc.drawRectangle(330, 230, 4, 4);

        // and now for filled rect with outline
        dc.setPen(wx.RED_PEN);
        dc.setBrush( wx.WHITE_BRUSH );
        dc.drawRectangle(500, 170, 49, 29);
        dc.drawRectangle(550, 170, 49, 29);
        dc.setPen(wx.WHITE_PEN);
        dc.drawLine(600, 170, 600, 210);
        dc.drawLine(500, 200, 610, 200);

        // test the rectangle outline drawing - there should be one pixel between
        // the rect and the lines
        dc.setPen(wx.WHITE_PEN);
        dc.setBrush( wx.TRANSPARENT_BRUSH );
        dc.drawRoundedRectangle(150, 270, 49, 29, 6);
        dc.drawRoundedRectangle(200, 270, 49, 29, 6);
        dc.setPen(wx.WHITE_PEN);
        dc.drawLine(250, 270, 250, 310);
        dc.drawLine(150, 300, 260, 300);

        // test the rectangle filled drawing - there should be one pixel between
        // the rect and the lines
        dc.setPen(wx.TRANSPARENT_PEN);
        dc.setBrush( wx.WHITE_BRUSH );
        dc.drawRoundedRectangle(300, 270, 49, 29, 6);
        dc.drawRoundedRectangle(350, 270, 49, 29, 6);
        dc.setPen(wx.WHITE_PEN);
        dc.drawLine(400, 270, 400, 310);
        dc.drawLine(300, 300, 410, 300);


        // Added by JACS to demonstrate bizarre behaviour.
        // With a size of 70, we get a missing red RHS,
        // and the height is too small, so we get yellow
        // showing. With a size of 40, it draws as expected:
        // it just shows a white rectangle with red outline.
        var totalWidth = 70;
        var totalHeight = 70;
        var bitmap2 = new wx.Bitmap(totalWidth, totalHeight);

        var memdc2 = new wx.MemoryDC();
        try {
            memdc2.selectObject(bitmap2);

            memdc2.background = (wx.YELLOW_BRUSH);
            memdc2.clear();

            // Now draw a white rectangle with red outline. It should
            // entirely eclipse the yellow background.
            memdc2.setPen(wx.RED_PEN);
            memdc2.setBrush(wx.WHITE_BRUSH);

            memdc2.drawRectangle(0, 0, totalWidth, totalHeight);

            //memdc2.setPen(wx.NullPen);
            //memdc2.setBrush(wx.NullBrush);
            //memdc2.selectObject(wx.NullBitmap);
        } finally {
            memdc2.release();
        }

        dc.drawBitmap(bitmap2, 500, 270);

        // Repeat, but draw directly on dc
        // Draw a yellow rectangle filling the bitmap

        x = 600; 
        var y = 270;
        dc.setPen(wx.YELLOW_PEN);
        dc.setBrush(wx.YELLOW_BRUSH);
        dc.drawRectangle(x, y, totalWidth, totalHeight);

        // Now draw a white rectangle with red outline. It should
        // entirely eclipse the yellow background.
        dc.setPen(wx.RED_PEN);
        dc.setBrush(wx.WHITE_BRUSH);

        dc.drawRectangle(x, y, totalWidth, totalHeight);

    }

    frame.canvas.drawTestBrushes = function (dc) {
        var WIDTH = 200;
        var HEIGHT = 80;

        var x = 10;
        var y = 10;

        dc.setBrush(wx.GREEN_BRUSH);
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Solid green"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(wx.RED, wx.BRUSHSTYLE.CROSSDIAG_HATCH));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Diagonally hatched red"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(wx.BLUE, wx.BRUSHSTYLE.CROSS_HATCH));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Cross hatched blue"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(wx.CYAN, wx.BRUSHSTYLE.VERTICAL_HATCH));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Vertically hatched cyan"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(wx.BLACK, wx.BRUSHSTYLE.HORIZONTAL_HATCH));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Horizontally hatched black"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(gs_bmpMask));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Stipple mono"), x + 10, y + 10);

        y += HEIGHT;
        dc.setBrush(new wx.Brush(gs_bmpNoMask));
        dc.drawRectangle(x, y, WIDTH, HEIGHT);
        dc.drawText(wxT("Stipple colour"), x + 10, y + 10);
    }

    frame.canvas.drawTestLines = function (x, y, width, dc) {
        dc.setPen({ colour: wx.GREEN, width: width });
        dc.setBrush(wx.BLACK_BRUSH);
        dc.drawText("Testing lines of width " + width, x + 10, y - 10);
        dc.drawRectangle(x + 10, y + 10, 100, 190);

        dc.drawText("Solid/dot/short dash/long dash/dot dash", x + 150, y + 10);
        dc.setPen({ colour: wx.RED, width: width });
        dc.drawLine(x + 20, y + 20, 100, y + 20);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.DOT });
        dc.drawLine(x + 20, y + 30, 100, y + 30);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.SHORT_DASH });
        dc.drawLine(x + 20, y + 40, 100, y + 40);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.LONG_DASH });
        dc.drawLine(x + 20, y + 50, 100, y + 50);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.DOT_DASH });
        dc.drawLine(x + 20, y + 60, 100, y + 60);

        
        dc.drawText("Misc hatches", x + 150, y + 70);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.BDIAGONAL_HATCH });
        dc.drawLine(x + 20, y + 70, 100, y + 70);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.CROSSDIAG_HATCH });
        dc.drawLine(x + 20, y + 80, 100, y + 80);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.FDIAGONAL_HATCH });
        dc.drawLine(x + 20, y + 90, 100, y + 90);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.CROSS_HATCH });
        dc.drawLine(x + 20, y + 100, 100, y + 100);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.HORIZONTAL_HATCH });
        dc.drawLine(x + 20, y + 110, 100, y + 110);
        dc.setPen({ colour: wx.RED, width: width, style: wx.PENSTYLE.VERTICAL_HATCH });
        dc.drawLine(x + 20, y + 120, 100, y + 120);


        dc.drawText("User dash", x + 150, y + 140);
        var ud = new wx.Pen(wx.RED, width, wx.PENSTYLE.USER_DASH);
        var dash1 = new Uint8ClampedArray(6);
        dash1[0] = 8;  // Long dash  <---------+
        dash1[1] = 2;  // Short gap            |
        dash1[2] = 3;  // Short dash           |
        dash1[3] = 2;  // Short gap            |
        dash1[4] = 3;  // Short dash           |
        dash1[5] = 2;  // Short gap and repeat +
        ud.dashes = dash1;
        dc.setPen(ud);
        dc.drawLine(x + 20, y + 140, 100, y + 140);
        dash1[0] = 5;  // Make first dash shorter
        ud.dashes = dash1;
        dc.setPen(ud);
        dc.drawLine(x + 20, y + 150, 100, y + 150);
        dash1[2] = 5;  // Make second dash longer
        ud.dashes = dash1;
        dc.setPen(ud);
        dc.drawLine(x + 20, y + 160, 100, y + 160);
        dash1[4] = 5;  // Make third dash longer
        ud.dashes = dash1;
        dc.setPen(ud);
        dc.drawLine(x + 20, y + 170, 100, y + 170);
    }

    frame.canvas.drawText = function (dc)
    {
        // set underlined font for testing
        dc.font = {
            pointSize: 12,
            family: wx.FontFamily.MODERN,
            style: wx.FontStyle.ITALIC,
            weight: wx.FontWeight.BOLD,
            underline: true
        };
        dc.drawText( "This is text", 110, 10 );
        dc.drawRotatedText( "That is text", 20, 10, -45 );

        // use wxSWISS_FONT and not wxNORMAL_FONT as the latter can't be rotated
        // under MSW (it is not TrueType)
        dc.font = wx.SWISS_FONT;

        var text = "";
        dc.backgroundMode = wx.TRANSPARENT;

        for ( var n = -180; n < 180; n += 30 )
        {
            dc.drawRotatedText("     " + n + " rotated text"  , 400, 400, n);
        }

        dc.font = { pointSize: 18, family: wx.FontFamily.SWISS };
//        dc.setFont( wx.FontInfo(18).family(wx.FONTFAMILY_SWISS) );

        dc.drawText( "This is Swiss 18pt text.", 110, 40 );

        var length = 0;
        var height = 0;
        var descent = 0;
        var lhd =  dc.getTextExtent( "This is Swiss 18pt text.");//, &length, &height, &descent );
        //text.Printf( wxT("Dimensions are length %d, height %d, descent %d"), length, height, descent );
        dc.drawText( 
            "Dimensions are length " + lhd.w +
            " height " + lhd.h +
            " descent " + lhd.descent +
            " externalLeading " + lhd.externalLeading
            , 110, 80 );

        //text.Printf( wxT("CharHeight() returns: %d"), dc.GetCharHeight() );
        dc.drawText("CharHeight() returns: " + dc.charHeight, 110, 120);

        length = lhd.w;
        height = lhd.h;
        descent = lhd.descent;

        dc.drawRectangle(100, 40, 4, height);

        //// test the logical function effect
        var y = 150;
        dc.logicalFunction = wx.RasterOperationMode.INVERT;
        //// text drawing should ignore logical function
        dc.drawText( "There should be a text below", 110, 150 );
        dc.drawRectangle( 110, y, 100, height );

        y += height;
        dc.drawText( "Visible text", 110, y );
        dc.drawRectangle( 110, y, 100, height );
        dc.drawText( "Visible text", 110, y );
        dc.drawRectangle( 110, y, 100, height );
        dc.logicalFunction = wx.RasterOperationMode.COPY;

        y += height;
        dc.drawRectangle( 110, y, 100, height );
        dc.drawText( "Another visible text", 110, y );

        y += height;
        dc.drawText("And\nmore\ntext on\nmultiple\nlines", 110, y);
        y += 5*height;

        dc.textForeground = wx.BLUE;
        dc.drawRotatedText("Rotated text\ncan have\nmultiple lines\nas well", 110, y, 15);

    }

    frame.canvas.drawCircles = function (dc) {

        var x = 100,
            y = 100,
            r = 20;

        dc.pen = wx.RED_PEN;
        dc.brush =wx.GREEN_BRUSH;

        dc.drawText("Some circles", 0, y);
        dc.drawCircle(x, y, r);
        dc.drawCircle(x + 2*r, y, r);
        dc.drawCircle(x + 4*r, y, r);

        y += 2*r;
        dc.drawText("And ellipses", 0, y);
        dc.drawEllipse(x - r, y, 2*r, r);
        dc.drawEllipse(x + r, y, 2*r, r);
        dc.drawEllipse(x + 3*r, y, 2*r, r);

        y += 2*r;
        dc.drawText("And arcs", 0, y);
        dc.drawArc(x - r, y, x + r, y, x, y);
        dc.drawArc(x + 4*r, y, x + 2*r, y, x + 3*r, y);
        dc.drawArc(x + 5*r, y, x + 5*r, y, x + 6*r, y);

        y += 2*r;
        dc.drawEllipticArc(x - r, y, 2*r, r, 0, 90);
        dc.drawEllipticArc(x + r, y, 2*r, r, 90, 180);
        dc.drawEllipticArc(x + 3*r, y, 2*r, r, 180, 270);
        dc.drawEllipticArc(x + 5*r, y, 2*r, r, 270, 360);

        // same as above, just transparent brush

        dc.pen = wx.RED_PEN;
        dc.brush = wx.TRANSPARENT_BRUSH;

        y += 2*r;
        dc.drawText("Some circles", 0, y);
        dc.drawCircle(x, y, r);
        dc.drawCircle(x + 2*r, y, r);
        dc.drawCircle(x + 4*r, y, r);

        y += 2*r;
        dc.drawText("And ellipses", 0, y);
        dc.drawEllipse(x - r, y, 2*r, r);
        dc.drawEllipse(x + r, y, 2*r, r);
        dc.drawEllipse(x + 3*r, y, 2*r, r);

        y += 2*r;
        dc.drawText("And arcs", 0, y);
        dc.drawArc(x - r, y, x + r, y, x, y);
        dc.drawArc(x + 4*r, y, x + 2*r, y, x + 3*r, y);
        dc.drawArc(x + 5*r, y, x + 5*r, y, x + 6*r, y);

        y += 2*r;
        dc.drawEllipticArc(x - r, y, 2*r, r, 0, 90);
        dc.drawEllipticArc(x + r, y, 2*r, r, 90, 180);
        dc.drawEllipticArc(x + 3*r, y, 2*r, r, 180, 270);
        dc.drawEllipticArc(x + 5*r, y, 2*r, r, 270, 360);
    }

    frame.canvas.drawSplines = function (dc) {
        dc.drawText("Some splines", 10, 5);

        // values are hardcoded rather than randomly generated
        // so the output can be compared between native
        // implementations on platforms with different random
        // generators

        var R = 300;
        var M_PI = 3.141592;
        var center = { x: R + 20, y: R + 20 };
        var angles = [0, 10, 33, 77, 13, 145, 90];
        var radii = [100, 59, 85, 33, 90];
        var numPoints = 200;
        var pts = [];


        // background spline calculation
        var radius_pos = 0;
        var angle_pos = 0;
        var angle = 0;
        for (var i = 0; i < numPoints; i++) {
            angle += angles[angle_pos];
            var r = R * radii[radius_pos] / 100;
            pts.push(
                {
                    x: center.x + (r * Math.cos(M_PI * angle / 180.0)),
                    y: center.y + (r * Math.sin(M_PI * angle / 180.0))
                }
            );

            angle_pos++;
            if (angle_pos >= angles.length) angle_pos = 0;

            radius_pos++;
            if (radius_pos >= radii.length) radius_pos = 0;
        }
        //dc.setPen(wx.RED_PEN);
        dc.setPen({ colour: wx.RED, width: 5 });
        dc.drawSpline(pts);


        var letters = new Array();
        var letteri = new Array();
        // w
        letteri.push({ x: 0, y: 1 });//  O           O
        letteri.push({ x: 1, y: 3 });//   *         *
        letteri.push({ x: 2, y: 2 });//    *   O   *
        letteri.push({ x: 3, y: 3 });//     * * * *
        letteri.push({ x: 4, y: 1 });//      O   O
        letters.push(letteri);
        // x1
        letteri = new Array();
        letteri.push({ x: 5, y: 1 });//  O*O
        letteri.push({ x: 6, y: 1 });//     *
        letteri.push({ x: 7, y: 2 });//      O
        letteri.push({ x: 8, y: 3 });//       *
        letteri.push({ x: 9, y: 3 });//        O*O
        letters.push(letteri);
        // x2
        letteri = new Array();
        letteri.push({ x: 5, y: 3 });//        O*O
        letteri.push({ x: 6, y: 3 });//       *
        letteri.push({ x: 7, y: 2 });//      O
        letteri.push({ x: 8, y: 1 });//     *
        letteri.push({ x: 9, y: 1 });//  O*O
        letters.push(letteri);
        // W
        letteri = new Array();
        letteri.push({ x: 10, y: 0 });//  O           O
        letteri.push({ x: 11, y: 3 });//   *         *
        letteri.push({ x: 12, y: 1 });//    *   O   *
        letteri.push({ x: 13, y: 3 });//     * * * *
        letteri.push({ x: 14, y: 0 });//      O   O
        letters.push(letteri);

        var dx = 2 * R / letters[3][4].x;
        var h = [-R / 2, 0, R / 4, R / 2];
        for (var m in letters) {
            for (var n in letters[m]) {
                letters[m][n].x = center.x - R + letters[m][n].x * dx;
                letters[m][n].y = center.y + h[letters[m][n].y];
            }

        }
        dc.setPen({ colour: wx.BLUE, width: 1, style: wx.PENSTYLE.DOT });
        dc.drawLines( letters[m]);
        dc.setPen({ colour: wx.BLACK, width: 4 });
        dc.drawSpline( letters[m]);
    }

    frame.canvas.drawGradients = function (dc) {
        var TEXT_HEIGHT = 15;
        
        var r = new wx.Rect(10, 10, 50, 50); // wx.Rect
        dc.drawText("wx.Direction.RIGHT", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillLinear(r, wx.WHITE, wx.BLUE, wx.Direction.RIGHT);

        r.offset(0, r.height + 10);
        dc.drawText("wx.Direction.LEFT", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillLinear(r, wx.WHITE, wx.BLUE, wx.Direction.LEFT);

        r.offset(0, r.height + 10);
        dc.drawText("wx.Direction.DOWN", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillLinear(r, wx.WHITE, wx.BLUE, wx.Direction.DOWN);

        r.offset(0, r.height + 10);
        dc.drawText("wx.Direction.UP", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillLinear(r, wx.WHITE, wx.BLUE, wx.Direction.UP);


        var gfr = new wx.Rect(r); // wx.Rect

        
        // RHS: concentric
        r = new wx.Rect(200, 10, 50, 50);
        dc.drawText("Blue inside", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillConcentric(r, wx.BLUE, wx.WHITE);

        r.offset(0, r.height + 10);
        dc.drawText("White inside", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillConcentric(r, wx.BLUE, wx.WHITE);

        r.offset(0, r.height + 10);
        dc.drawText("Blue in top left corner", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillConcentric(r, wx.BLUE, wx.WHITE, {x:0,y:0});

        r.offset(0, r.height + 10);
        dc.drawText("Blue in bottom right corner", r.x, r.y);
        r.offset(0, TEXT_HEIGHT);
        dc.gradientFillConcentric(r, wx.BLUE, wx.WHITE, {x:r.width,y:r.height});

        // check that the area filled by the gradient is exactly the interior of
        // the rectangle
        r.x = 350;
        r.y = 30;
        dc.drawText("The interior should be filled but", r.x, r.y);
        r.y += 15;
        dc.drawText(" the red border should remain visible:", r.x, r.y);
        r.y += 15;

        r.width =
        r.height = 50;
        var r2 = r;
        r2.x += 60;
        var r3 = r;
        r3.y += 60;
        var r4 = r2;
        r4.y += 60;
        dc.setPen(wx.RED_PEN);
        dc.drawRectangle(r);
        r.deflate(1);
        dc.gradientFillLinear(r, wx.GREEN, wx.BLACK, wx.Direction.NORTH);
        dc.drawRectangle(r2);
        r2.deflate(1);
        dc.gradientFillLinear(r2, wx.BLACK, wx.GREEN, wx.Direction.SOUTH);
        dc.drawRectangle(r3);
        r3.deflate(1);
        dc.gradientFillLinear(r3, wx.GREEN, wx.BLACK, wx.Direction.EAST);
        dc.drawRectangle(r4);
        r4.deflate(1);
        dc.gradientFillLinear(r4, wx.BLACK, wx.GREEN, wx.Direction.WEST);
        /*

            TODO....

#if wxUSE_GRAPHICS_CONTEXT
    if (m_renderer)
    {
        wxGCDC                      &gdc = (wxGCDC&)dc;
        wxGraphicsContext           *gc = gdc.GetGraphicsContext();
        wxGraphicsPath              pth;
        wxGraphicsGradientStops     stops;

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Linear Gradient with Stops"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, *wxBLUE);
        stops.Add(wxColour(255,255,0), 0.33f);
        stops.Add(*wxGREEN, 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y,
                                                   gfr.x + gfr.width, gfr.y + gfr.height,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        wxGraphicsGradientStops simpleStops(*wxRED, *wxBLUE);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Radial Gradient from Red to Blue without intermediary Stops"),
            gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
            gfr.y + gfr.height / 2,
            gfr.x + gfr.width / 2,
            gfr.y + gfr.height / 2,
            gfr.width / 2,
            simpleStops));

        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Radial Gradient from Red to Blue with Yellow and Green Stops"),
            gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Linear Gradient with Stops and Gaps"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, *wxBLUE);
        stops.Add(wxColour(255,255,0), 0.33f);
        stops.Add(wxTransparentColour, 0.33f);
        stops.Add(wxTransparentColour, 0.67f);
        stops.Add(*wxGREEN, 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y + gfr.height,
                                                   gfr.x + gfr.width, gfr.y,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Radial Gradient with Stops and Gaps"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Gradients with Stops and Transparency"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, wxTransparentColour);
        stops.Add(*wxRED, 0.33f);
        stops.Add(wxTransparentColour, 0.33f);
        stops.Add(wxTransparentColour, 0.67f);
        stops.Add(*wxBLUE, 0.67f);
        stops.Add(*wxBLUE, 1.0f);

        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        gc->FillPath(pth);

        stops = wxGraphicsGradientStops(wxColour(255,0,0, 128), wxColour(0,0,255, 128));
        stops.Add(wxColour(255,255,0,128), 0.33f);
        stops.Add(wxColour(0,255,0,128), 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y,
                                                   gfr.x + gfr.width, gfr.y,
                                                   stops));
        gc->FillPath(pth);
    }
#endif // wxUSE_GRAPHICS_CONTEXT        
        */
    }

    frame.canvas.drawImages = function (dc, isStretchMode) {

        dc.drawText("original image", 0, 0);
        dc.drawBitmap(gs_bmpNoMask, 0, 20, 0);
        dc.drawText("with colour mask", 0, 100);
        dc.drawBitmap(gs_bmpWithColMask, 0, 120, true);
        dc.drawText("the mask image", 0, 200);
        dc.drawBitmap(gs_bmpMask, 0, 220, 0);
        dc.drawText("masked image", 0, 300);
        dc.drawBitmap(gs_bmpWithMask, 0, 320, true);

        var cx = gs_bmpWithColMask.width;
        var cy = gs_bmpWithColMask.height;
        var memDC = new wx.MemoryDC();
        try {
            for (var n in rasterOperations) {
                var x = 120 + 150 * (n % 4);
                var y = 20 + 100 * (n / 4);

                dc.drawText(rasterOperations[n][0], x, y - 20);

                memDC.selectObject(gs_bmpWithColMask);
                if (isStretchMode == true) {
                    dc.stretchBlit(x, y, cx, cy, memDC, 0, 0, cx/2, cy/2,
                                   rasterOperations[n][1], true);
                }
                else
                {
                    dc.blit(x, y, cx, cy, memDC, 0, 0, rasterOperations[n][1], true);
                }
            }
        } finally {
            memDC.release();
        }
    }
    frame.canvas.drawTestPoly = function (dc) {

        var brushHatch = new wx.Brush(wx.RED, wx.BRUSHSTYLE.FDIAGONAL_HATCH);
        dc.setBrush(brushHatch);

        var star = [ {x:100,y:60}
            ,   {x:60,y:150}
            ,   {x:160,y:100}
            ,   {x:40,y:100}
            ,   {x:140,y:150}
        ];

        dc.drawText("You should see two (irregular) stars below, the left one hatched", 10, 10);
        dc.drawText("except for the central region and the right one entirely hatched", 10, 30);
        dc.drawText("The third star only has a hatched outline", 10, 50);

        dc.drawPolygon(star, 0, 30);
        dc.drawPolygon( star, 160, 30, wx.PolygonFillMode.WINDING_RULE);

        var star2 = [
             {x:0, y:100} 
         ,   {x:-59, y:-81}
         ,   {x:95, y:31}
         ,   {x:-95, y:31}
         ,   {x:59, y:-81}
         ,   {x:0, y:80}
         ,   {x:-47, y:-64}
         ,   {x:76, y:24}
         ,   {x:-76, y:24}
         ,   {x:47, y:-64}        
        ];


        dc.drawPolyPolygon([5,5], star2, 450, 150);
    }

    frame.canvas.drawWithLogicalOps = function (dc) {
        
        var w = 60;
        var h = 60;

        // reuse the text colour here
        dc.setPen(new wx.Pen(this.m_owner.m_colourForeground));
        dc.setBrush(wx.TRANSPARENT_BRUSH);

        
        for (var n in rasterOperations) {
            var x = 20 + 150*(n%4);
            var y = 20 + 100*(n/4);
            dc.drawText(rasterOperations[n][0], x, y - 20);
            dc.logicalFunction = (rasterOperations[n][1]);
            dc.drawRectangle(x, y, w, h);
            dc.drawLine(x, y, x + w, y + h);
            dc.drawLine(x + w, y, x, y + h);
        }

        // now some filled rectangles
        dc.setBrush(new wx.Brush(this.m_owner.m_colourForeground));

        for (var n in rasterOperations) {
            var x = 20 + 150*(n%4);
            var y = 500 + 100*(n/4);

            dc.drawText(rasterOperations[n][0], x, y - 20);
            dc.logicalFunction = (rasterOperations[n][1]);
            dc.drawRectangle(x, y, w, h);
        }
    }
    frame.canvas.drawRegions = function (dc) {

        dc.drawText(wxT("You should see a red rect partly covered by a cyan one ") +
                    wxT("on the left"), 10, 5);
        dc.drawText(wxT("and 5 smileys from which 4 are partially clipped on the right"), 
                    10, 5 + dc.charHeight);
        dc.drawText(wxT("The second copy should be identical but right part of it ") +
                    wxT("should be offset by 10 pixels."),
                    10, 5 + 2 * dc.charHeight);


        this.drawRegionsHelper(dc, 10, true);
        this.drawRegionsHelper(dc, 350, false);
    }
    frame.canvas.drawRegionsHelper = function (dc, x, firstTime) {

        var y = 100;

        dc.destroyClippingRegion();
        dc.setBrush( wx.WHITE_BRUSH );
        dc.setPen( wx.TRANSPARENT_PEN );
        dc.drawRectangle( x, y, 310, 310 );

        dc.setClippingRegion( x + 10, y + 10, 100, 270 );

        dc.setBrush( wx.RED_BRUSH );
        dc.drawRectangle( x, y, 310, 310 );

        dc.setClippingRegion( x + 10, y + 10, 100, 100 );

        dc.setBrush( wx.CYAN_BRUSH );
        dc.drawRectangle( x, y, 310, 310 );

        dc.destroyClippingRegion();

        var region = new wx.Region(x + 110, y + 20, 100, 270);
//#if !defined(__WXMOTIF__)
//    if ( !firstTime )
//        region.Offset(10, 10);
//#endif
        dc.setDeviceClippingRegion(region);

        dc.setBrush( wx.GREY_BRUSH );
        dc.drawRectangle( x, y, 310, 310 );

        if (this.m_smile_bmp.isOk)
        {
            dc.drawBitmap(this.m_smile_bmp, x + 150, y + 150, true);
            dc.drawBitmap(this.m_smile_bmp, x + 130, y + 10, true);
            dc.drawBitmap(this.m_smile_bmp, x + 130, y + 280, true);
            dc.drawBitmap(this.m_smile_bmp, x + 100, y + 70, true);
            dc.drawBitmap(this.m_smile_bmp, x + 200, y + 70, true);
        }
    }

    frame.createStatusBar(2);


    frame.setStatusWidths(new Array(100, -1, -1));
	frame.title = "さんぷる";

	
	
    // Don't forget to show the frame by setting the visible property to true!
	frame.setVisible(true);
    wxTheApp.topWindow = frame;
	

    return true;
}

