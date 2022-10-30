
var wx = require("wx");
	
do {
    var objExcel = new wx.AutomationObject();
    if (objExcel.createInstance("Excel.Application") == false) {
        break;
    }
    // Excelを表示する。
    objExcel.putProperty("visible", true);

    var objBooks = objExcel.getObject("workbooks");
    if (objBooks == null) {
        break;
    }
    var objBook = objBooks.callMethod("Add");
    var objSheet = objExcel.getObject("ActiveSheet");

    var objRange = objSheet.getObject("Range", "B2");
    var a = objRange.callMethod("Select");
    objRange.putProperty("FormulaR1C1", "Test0001");

    var objFont = objRange.getObject("Font");
    objFont.putProperty("Color", -16776961);
    objFont.putProperty("Bold", true);
    objFont.putProperty("Italic", true);
    objFont.putProperty("Underline", true);
    var objSelection = objRange.getObject("Interior");
    objSelection.putProperty("Color", 65535);

    var objColumns = objSheet.getObject("Columns", "B");
    objColumns.putProperty("ColumnWidth", 20.14);

    //objBooks.callMethod("open", "c:\\work\\a.xlsx");
        
} while (0);

