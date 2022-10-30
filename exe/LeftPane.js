/*

*/

var LeftPane = function(frame) 
{
    var m_notebook_style = wx.Aui.NotebookOption.DEFAULT_STYLE | wx.Aui.NotebookOption.TAB_EXTERNAL_MOVE | wx.Border.NONE;
    m_notebook_style &= ~(wx.Aui.NotebookOption.CLOSE_BUTTON |
						  wx.Aui.NotebookOption.CLOSE_ON_ACTIVE_TAB |
						  wx.Aui.NotebookOption.CLOSE_ON_ALL_TABS);
    // NoteBookの作成
    this.pTabLeft = new wx.Aui.Notebook(frame, -1,
                                    wx.Point(10, 10),
                                    wx.Size(200, 500),
                                    m_notebook_style
							);

    // ツリータブの作成
    var pSizer = new wx.BoxSizer(wx.Orientation.VERTICAL);
    this.m_pPanelLeft = new wx.Panel(this.pTabLeft, 13);
    this.m_pPanelLeft.tree = new wx.TreeCtrl(this.m_pPanelLeft, 1);
    pSizer.add(this.m_pPanelLeft.tree
        , 1
        , wx.Direction.ALL | wx.Stretch.EXPAND | wx.Stretch.GROW);
    this.m_pPanelLeft.sizer = pSizer;
    this.m_pPanelLeft.fit();


    // ツリーのアイテムが選択されたときの動作を実装
    this.m_pPanelLeft.tree.onSelChanged = function (event) {
        print("getItemText=" + this.getItemText(event.item));
    }


    this.root_node = this.m_pPanelLeft.tree.addRoot("Root");

    this.setTree = function (parent) {

        if (parent.elements.length > 0)
            this.xmlTree(this.m_pPanelLeft.tree, this.root_node, parent.elements)
    }

    this.xmlTree = function (tree, id, elements) {

        try {

            for (i in elements) {
                var newId = tree.appendItem(id, elements[i].name);
                if (elements[i].elements.length > 0)
                    this.xmlTree(tree, newId, elements[i].elements);
            }
        } catch (e) {
            print("ERR:" + e);
        } 
    }



    this.pTabLeft.addPage(this.m_pPanelLeft,
		"Main Tree"
		, false
	);




    // XSD（スタイルシートの表示パネルを作成）
    this.panelXsd = new LeftPaneXSD(frame, this.pTabLeft);//new wx.Panel(this.pTabLeft, 14);
    this.pTabLeft.addPage(this.panelXsd.pane,
		"Style"
		, false
	);

    frame.auiMgr.addPane(this.pTabLeft, new wx.Aui.PaneInfo().
		name("MainTree").
		left().
		maximizeButton().
		minimizeButton().
		maximize().
		closeButton(false).
		caption("Main Tree")
	);
}

/**
 * @brief 左パネルのXSDの箇所
 */
var LeftPaneXSD = function (frame, auiTab) {

    var pSizer = new wx.BoxSizer(wx.Orientation.VERTICAL);
    this.pane = new wx.Panel(auiTab, 14);
    this.tree = new wx.TreeCtrl(this.pane, 1);

    pSizer.add(this.tree
        , 1
        , wx.Direction.ALL | wx.Stretch.EXPAND | wx.Stretch.GROW);
    this.pane.sizer = pSizer;
    this.pane.fit();

    this.tree.frame = frame;
    // ツリーアイテムが選択された時のCB
    this.tree.onSelChanging = function (evt) {
        print("onSelChanging");
//        evt.veto = true;
    }
    // ツリーアイテムが選択された時のCB
    this.tree.onSelChanged = function (evt) {
        print("onSelChanged");

        //
        // 右パネルに変更を通知する。
        this.frame.notifyXSDItem(this.getItemData(evt.item));

//        evt.skip = true;

    }

    // ロードしたオブジェクトを、ツリーにセットします。
    this.setTree = function (objRoot) {

        this.tree.deleteAllItems();
        this.root_node = this.tree.addRoot("schema");
        this.tree.setItemData(this.root_node, objRoot);
        for (var i in objRoot.cntAllObjs) {
            var newId = this.innerSetTree(this.root_node, objRoot.cntAllObjs[i]);
        }
    }
    this.innerSetTree = function(treeID, obj) {
        var newId = this.tree.appendItem(treeID, "" + obj);
        this.tree.setItemData(newId, obj);
        switch (obj.getEType()) {
            case xsd.E_TYPE.ALL:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                for (var i in obj.cntElemnt) {
                    var subNewId = this.innerSetTree(newId, obj.cntElemnt[i]);
                }
                break;
            case xsd.E_TYPE.ATTRIBUTE_GROUP:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // XsdBaseHasAttr
                if (obj.anyAttribute != null) {
                    var subNewId = this.innerSetTree(newId, obj.anyAttribute);
                }
                for (var i in obj.cntAttribute) {
                    var subNewId = this.innerSetTree(newId, obj.cntAttribute[i]);
                }
                // This...
                break;
            case xsd.E_TYPE.ANNOTATION:
                // This...
                for (var i in obj.cntChldren) {
                    var subNewId = this.innerSetTree(newId, obj.cntChldren[i]);
                }
                break;
            case xsd.E_TYPE.COMPLEX_TYPE:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // XsdBaseHasAttr
                if (obj.anyAttribute != null) {
                    var subNewId = this.innerSetTree(newId, obj.anyAttribute);
                }
                for (var i in obj.cntAttribute) {
                    var subNewId = this.innerSetTree(newId, obj.cntAttribute[i]);
                }
                // This...
                if (obj.pContent != null) {
                    var subNewId = this.innerSetTree(newId, obj.pContent);
                }
                break;
            case xsd.E_TYPE.ELEMENT:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                for (var i in obj.cntChldren) {
                    var subNewId = this.innerSetTree(newId, obj.cntChldren[i]);
                }
                if (obj.pContent != null) {
                    var subNewId = this.innerSetTree(newId, obj.pContent);
                }
                break;
            case xsd.E_TYPE.SEQUENCE:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                for (var i in obj.cntChldren) {
                    var subNewId = this.innerSetTree(newId, obj.cntChldren[i]);
                }
            case xsd.E_TYPE.SIMPLE_TYPE:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                if (obj.content != null) {
                    var subNewId = this.innerSetTree(newId, obj.content);
                }
                break;
            case xsd.E_TYPE.RESTRICTION:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                if (obj.pContent != null) {
                    var subNewId = this.innerSetTree(newId, obj.pContent);
                }
                for (var i in obj.cntRestrictionVal) {
                    var subNewId = this.innerSetTree(newId, obj.cntRestrictionVal[i]);
                }
                break;
            case xsd.E_TYPE.KEY:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                if (obj.pSelector != null) {
                    var subNewId = this.innerSetTree(newId, obj.pSelector);
                }
                for (var i in obj.cntField) {
                    var subNewId = this.innerSetTree(newId, obj.cntField[i]);
                }
                break;
            case xsd.E_TYPE.UNION:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                for (var i in obj.cntSimpleType) {
                    var subNewId = this.innerSetTree(newId, obj.cntSimpleType[i]);
                }
                break;
            case xsd.E_TYPE.UNIQUE:
                // XsdBaseHasAnnotation
                if (obj.annotation != null) {
                    var subNewId = this.innerSetTree(newId, obj.annotation);
                }
                // This...
                if (obj.pSelector != null) {
                    var subNewId = this.innerSetTree(newId, obj.pSelector);
                }
                for (var i in obj.cntField) {
                    var subNewId = this.innerSetTree(newId, obj.cntField[i]);
                }
                break;

        }
        return newId;
    }


}
