/*

*/
// パネルのベースクラス。
PanelBase: {
    function PanelBase(parent) {
        this.panel = new wx.Panel(parent, -1);
    }
    var p = PanelBase.prototype;

};
// グリッドプロパティパネルのベースクラス
PanelPropGridBase: {
    function PanelPropGridBase(parent) {
        PanelBase.call(this, parent);

        var topSizer = new wx.BoxSizer(wx.Orientation.VERTICAL);
        this.panel.setSizer(topSizer);

        var style = wx.pg.WindowStyle.BOLD_MODIFIED |
            wx.pg.WindowStyle.SPLITTER_AUTO_CENTER |
            wx.pg.WindowStyle.TOOLBAR |
            wx.pg.WindowStyle.DESCRIPTION |
            wx.pg.WindowStyle.AUTO_SOR;

        this.m_pPropGridManager = new wx.pg.GridManager(
            this.panel,
            wx.NewId(),
            wx.DefaultPosition, wx.DefaultSize,
            style);
        this.m_propGrid = this.m_pPropGridManager.grid;

        this.m_pPropGridManager.setExtraStyle(wx.pg.WindowStyleEx.MODE_BUTTONS | wx.pg.WindowStyleEx.MULTIPLE_SELECTION);
        this.m_pPropGridManagervalidationFailureBehaviore = (wx.pg.VFB.MARK_CELL | wx.pg.VFB.SHOW_MESSAGEBOX);
        this.m_propGrid.verticalSpacing = 2;


        topSizer.add(this.m_pPropGridManager, 1, wx.Direction.ALL | wx.Stretch.EXPAND | wx.Stretch.GROW);
    }
    var p = PanelPropGridBase.prototype;

};



//
//  Annotation
//
PanelRightXsdAnnotation: {
    function PanelRightXsdAnnotation(parent) {
        PanelPropGridBase.call(this, parent);

        var cell = new wx.pg.Cell();
        cell.text = wx.Locale.getTranslation("Unspecified");
        cell.fgColor = wx.wxLIGHT_GREY;
        this.m_propGrid.unspecifiedValueAppearance = cell;

        var pg = this.m_pPropGridManager.addPage( wx.Locale.getTranslation("Attributes") );
        pg.append(new wx.pg.PropertyCategory( wx.Locale.getTranslation("Attribute") , wx.pg.LABEL));

        // id
        this.m_pPrp_Id = new wx.pg.StringProperty(wx.Locale.getTranslation("id"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_Id);
        pg.setPropertyHelpString(this.m_pPrp_Id, "オプション。 要素へユニークな ID を指定する");
        pg.setPropertyAttribute(this.m_pPrp_Id, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter id"));

        //
        //  メンバー関数の実装
        //
        this.set = function (obj) {
            this.obj = obj;
            if (obj == null) {
                return;
            }

            if (obj.id != undefined) {
                this.m_pPrp_Id.setValue(obj.id);
            }
        }
        this.unset = function () {
            if (this.m_pPropGridManager.isPageModified(0) == false) {
                return;
            }
            if (this.obj == undefined || this.obj == null) {
                return;
            }


            this.obj.id = this.m_pPrp_Id.getValue();

            this.m_pPropGridManager.clearModifiedStatus();
        }
    }

};
//
//  Appinfo
//
PanelRightXsdAppinfo: {
    function PanelRightXsdAppinfo(parent) {
        PanelPropGridBase.call(this, parent);

        var cell = new wx.pg.Cell();
        cell.text = wx.Locale.getTranslation("Unspecified");
        cell.fgColor = wx.wxLIGHT_GREY;
        this.m_propGrid.unspecifiedValueAppearance = cell;

        var pg = this.m_pPropGridManager.addPage(wx.Locale.getTranslation("Attributes"));
        pg.append(new wx.pg.PropertyCategory(wx.Locale.getTranslation("Attribute"), wx.pg.LABEL));

        // source
        this.m_pPrp_source = new wx.pg.StringProperty(wx.Locale.getTranslation("source"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_source);
        pg.setPropertyHelpString(this.m_pPrp_source, "オプション。 アプリケーション情報のソースを指定する URI リファレンス");
        pg.setPropertyAttribute(this.m_pPrp_source, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter source"));

        // content
        this.m_pPrp_content = new wx.pg.LongStringProperty(wx.Locale.getTranslation("content"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_content);
        pg.setPropertyHelpString(this.m_pPrp_content, "オプション。 システム的に利用される情報を指定する");
        pg.setPropertyAttribute(this.m_pPrp_content, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter content"));
        //
        //  メンバー関数の実装
        //
        this.set = function (obj) {
            this.obj = obj;
            if (obj == null) {
                return;
            }

            this.m_pPrp_source.setValue(obj.strSource);
            this.m_pPrp_content.setValue(obj.strDoc);
        }
        this.unset = function () {
            if (this.m_pPropGridManager.isPageModified(0) == false) {
                return;
            }
            if (this.obj == undefined || this.obj == null) {
                return;
            }



            this.obj.strSource = this.m_pPrp_source.getValue();
            this.obj.strDoc = this.m_pPrp_content.getValue();

            this.m_pPropGridManager.clearModifiedStatus();
        }
    }

};
//
//  Documentation
//
PanelRightXsdDocumentation: {
    function PanelRightXsdDocumentation(parent) {
        PanelPropGridBase.call(this, parent);

        this.m_pPropGridManager.me = this;
        
        var cell = new wx.pg.Cell();
        cell.text = wx.Locale.getTranslation("Unspecified");
        cell.fgColor = wx.wxLIGHT_GREY;
        this.m_propGrid.unspecifiedValueAppearance = cell;
        
        var pg = this.m_pPropGridManager.addPage(wx.Locale.getTranslation("Attributes"));
        pg.append(new wx.pg.PropertyCategory(wx.Locale.getTranslation("Attribute"), wx.pg.LABEL));

        // source
        this.m_pPrp_source = new wx.pg.StringProperty(wx.Locale.getTranslation("source"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_source);
        pg.setPropertyHelpString(this.m_pPrp_source, "オプション。 アプリケーション情報のソースを指定する URI リファレンス");
        pg.setPropertyAttribute(this.m_pPrp_source, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter source"));

        // lang
        this.m_pPrp_lang = new wx.pg.StringProperty(wx.Locale.getTranslation("lang"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_lang);
        pg.setPropertyHelpString(this.m_pPrp_lang, "オプション。 アプリケーション情報のソースを指定する URI リファレンス");
        pg.setPropertyAttribute(this.m_pPrp_lang, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter lang"));


        // lang
        this.m_pPrp_content = new wx.pg.LongStringProperty(wx.Locale.getTranslation("content"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_content);
        pg.setPropertyHelpString(this.m_pPrp_content, "オプション。 アプリケーション情報のソースを指定する URI リファレンス");
        pg.setPropertyAttribute(this.m_pPrp_content, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter content"));


        //
        //  メンバー関数の実装
        //
        this.set = function (obj) {
            this.obj = obj;
            if (obj == null) {
                return;
            }

            this.m_pPrp_source.setValue(obj.strSource);
            this.m_pPrp_lang.setValue(obj.strLang);
            this.m_pPrp_content.setValue(obj.strDoc);
        }
        this.unset = function () {
            if (this.m_pPropGridManager.isPageModified(0) == false) {
                return;
            }
            if (this.obj == undefined || this.obj == null) {
                return;
            }


            this.obj.strSource = this.m_pPrp_source.getValue();
            this.obj.strLang = this.m_pPrp_lang.getValue();
            this.obj.strDoc = this.m_pPrp_content.getValue();

            this.m_pPropGridManager.clearModifiedStatus();
        }

        this.m_pPropGridManager.onChanged = function (evt) {
            print(this.me.m_pPrp_source.getValue());
            print(this.me.m_pPrp_lang.getValue());
            print(this.me.m_pPrp_content.getValue());
        }
    }

};
//
//  XsdElement
//
PanelRightXsdElement: {
    function PanelRightXsdElement(parent) {
        PanelPropGridBase.call(this, parent);

        this.m_pPropGridManager.me = this;

        var cell = new wx.pg.Cell();
        cell.text = wx.Locale.getTranslation("Unspecified");
        cell.fgColor = wx.wxLIGHT_GREY;
        this.m_propGrid.unspecifiedValueAppearance = cell;

        var pg = this.m_pPropGridManager.addPage(wx.Locale.getTranslation("Attributes"));
        pg.append(new wx.pg.PropertyCategory(wx.Locale.getTranslation("Attribute"), wx.pg.LABEL));

        // id
        this.m_pPrp_Id = new wx.pg.StringProperty(wx.Locale.getTranslation("id"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_Id);
        pg.setPropertyHelpString(this.m_pPrp_Id, "オプション。 要素へユニークな ID を指定する");
        pg.setPropertyAttribute(this.m_pPrp_Id, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter id"));

        // isRef
        this.m_pPrp_IsRef = new wx.pg.BoolProperty(wx.Locale.getTranslation("isRef"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_IsRef);
        pg.setPropertyHelpString(this.m_pPrp_IsRef, "nameかrefかを指定します。");
        pg.setPropertyAttribute(this.m_pPrp_IsRef, "UseCheckbox",
            true);

        // name
        this.m_pPrp_Name = new wx.pg.StringProperty(wx.Locale.getTranslation("name"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_Name);
        pg.setPropertyHelpString(this.m_pPrp_Name, "オプション。要素の名前を指定する。親要素が schema 要素の場合、この属性は必須");
        pg.setPropertyAttribute(this.m_pPrp_Name, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter name"));

        // ref
        {
            var bc = new wx.pg.Choices();
            this.m_pPrp_EmRef = new wx.pg.EnumProperty(wx.Locale.getTranslation("ref"), wx.pg.LABEL, bc, 0);
            pg.append(this.m_pPrp_EmRef);
            pg.setPropertyHelpString(this.m_pPrp_EmRef, "オプション。他の要素の名前を参照する。 ref 属性は、名前空間接頭辞を含めることができる。 親要素が schema 要素の場合、この属性は使用できない");
        }

        // type
        {
            var bc = new wx.pg.Choices();
            this.m_pPrp_EmType = new wx.pg.EnumProperty(wx.Locale.getTranslation("type"), wx.pg.LABEL, bc, 0);
            pg.append(this.m_pPrp_EmType);
            pg.setPropertyHelpString(this.m_pPrp_EmType, "オプション。組込みデータ型の名前か、simpleType または complexType 要素の名前のいずれかを指定する。");
        }

        // substitutionGroup
        {
            var bc = new wx.pg.Choices();
            this.m_pPrp_substitutionGroup = new wx.pg.EnumProperty(wx.Locale.getTranslation("substitutionGroup"), wx.pg.LABEL, bc, 0);
            pg.append(this.m_pPrp_substitutionGroup);
            pg.setPropertyHelpString(this.m_pPrp_substitutionGroup,
                "オプション。この要素で置換することができる要素の名前を指定する。 親要素が schema 要素でない場合、この属性は使用できない");
        }


        // default
        this.m_pPrp_default = new wx.pg.StringProperty(wx.Locale.getTranslation("default"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_default);
        pg.setPropertyHelpString(this.m_pPrp_default, "オプション。要素のデフォルト値を指定する （要素の内容が単純型またはテキストのみの場合にだけ使用することができる）");
        pg.setPropertyAttribute(this.m_pPrp_default, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter default"));


        // fixed
        this.m_pPrp_fixed = new wx.pg.StringProperty(wx.Locale.getTranslation("fixed"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_fixed);
        pg.setPropertyHelpString(this.m_pPrp_fixed, "オプション。要素の固定値を指定する （要素の内容が単純型またはテキストのみの場合にだけ使用することができる）");
        pg.setPropertyAttribute(this.m_pPrp_fixed, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter fixed"));
                             
        // form
        {
            var bc = new wx.pg.Choices();
            bc.add("qualified");
            bc.add("unqualified");
            this.m_pPrp_form = new wx.pg.EnumProperty(wx.Locale.getTranslation("form"), wx.pg.LABEL, bc, 0);
            pg.append(this.m_pPrp_form);
            pg.setPropertyHelpString(this.m_pPrp_form,
                "オプション。要素の形式を指定する。\"unqualified\" は、 この属性は名前空間接頭辞で修飾する必要がないことを示す。 \"qualified\" は、この属性は名前空間接頭辞で修飾する必要があることを示す。 デフォルト値は、スキーマ要素の elementFormDefault 属性の値となる。 親要素が schema 要素である場合、この属性は使用できない");
        }



        // maxOccurs
        this.m_pPrp_maxOccurs = new wx.pg.IntProperty(wx.Locale.getTranslation("maxOccurs"), wx.pg.LABEL);
        pg.append(this.m_pPrp_maxOccurs);
        pg.setPropertyHelpString(this.m_pPrp_maxOccurs, "オプション。この要素が親要素で出現できる最大値を指定する。 値は、任意の数値 >= 0 にすることができる。また、最大数で上限を設定しない場合は、 値に \"unbounded\" を使用する。デフォルト値は 1。 親要素が schema 要素である場合、この属性は使用できない");
        pg.setPropertyAttribute(this.m_pPrp_maxOccurs, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter maxOccurs"));
        var a1 = wx.pg.Editor.stockSpinCtrl;
        var a2 = wx.pg.Editor.stockDatetimeCtrl;
        pg.setPropertyEditor(this.m_pPrp_maxOccurs, wx.pg.Editor.stockSpinCtrl);
        pg.setPropertyAttribute(this.m_pPrp_maxOccurs, wx.pg.ATTR.SPINCTRL_MOTION,
            true);
        // minOccurs
        this.m_pPrp_minOccurs = new wx.pg.IntProperty(wx.Locale.getTranslation("minOccurs"), wx.pg.LABEL);
        pg.append(this.m_pPrp_minOccurs);
        pg.setPropertyHelpString(this.m_pPrp_minOccurs, "オプション。この要素が親要素で出現できる最小値を指定する。 値は、任意の数値 >= 0 にすることができる。デフォルト値は 1。 親要素が schema 要素である場合、この属性は使用できない");
        pg.setPropertyAttribute(this.m_pPrp_minOccurs, wx.pg.ATTR.HINT,
            wx.Locale.getTranslation("Enter minOccurs"));
        var a1 = wx.pg.Editor.stockSpinCtrl;
        var a2 = wx.pg.Editor.stockDatetimeCtrl;
        pg.setPropertyEditor(this.m_pPrp_minOccurs, wx.pg.Editor.stockSpinCtrl);
        pg.setPropertyAttribute(this.m_pPrp_minOccurs, wx.pg.ATTR.SPINCTRL_MOTION,
            true);

        // nillable
        this.m_pPrp_nillable = new wx.pg.BoolProperty(wx.Locale.getTranslation("nillable"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_nillable);
        pg.setPropertyHelpString(this.m_pPrp_nillable, "オプション。明示的な NULL 値を要素に割り当てることができるかどうかを指定する。 True は、要素のインスタンスが null 属性をもつために true へ設定することを可能にする。 null 属性は、インスタンスのXMLスキーマ名前空間の一部として定義される。デフォルトは false。");
        pg.setPropertyAttribute(this.m_pPrp_nillable, "UseCheckbox",
            true);

        // abstract
        this.m_pPrp_abstract = new wx.pg.BoolProperty(wx.Locale.getTranslation("abstract"), wx.pg.LABEL, "");
        pg.append(this.m_pPrp_abstract);
        pg.setPropertyHelpString(this.m_pPrp_abstract, "オプション。要素がインスタンスドキュメント内で使用できるかどうかを指定する。 Trueの場合、要素がインスタンスドキュメントに出現できないを示す。 代わりに、この要素の修飾名（QName）が含まれている substitutionGroup 属性の他の要素は、 この要素の位置に出現する必要がある。デフォルトは false");
        pg.setPropertyAttribute(this.m_pPrp_abstract, "UseCheckbox",
            true);

        // block
        {
            var bc = new wx.pg.Choices();
            bc.add("extension", xsd.BLOCK.EXTENSION);
            bc.add("restriction", xsd.BLOCK.RESTRICTION);
            bc.add("substitution", xsd.BLOCK.SUBSTITUTION);
            this.m_pPrp_block = new wx.pg.MultiChoiceProperty(wx.Locale.getTranslation("block"), wx.pg.LABEL, bc);
            pg.append(this.m_pPrp_block);
            pg.setPropertyHelpString(this.m_pPrp_block,
                "オプション。派生の指定した型をもつ要素を、この要素の代わりに使用されることを防ぐ。 この値は、#all または、拡張、制約、または equivClass のサブセットであるリストを含めることができる:\n* extension - 拡張により派生した要素の使用を防ぐ\n* restriction - 制約により派生した要素の使用を防ぐ\n* substitution - 置換により派生した要素の使用を防ぐ\n* #all - すべての派生した要素の使用を防ぐ\n");
        }

        // final
        {
            var bc = new wx.pg.Choices();
            bc.add("extension", xsd.FINAL.EXTENSION);
            bc.add("restriction", xsd.FINAL.RESTRICTION);
            this.m_pPrp_final = new wx.pg.MultiChoiceProperty(wx.Locale.getTranslation("final"), wx.pg.LABEL, bc);
            pg.append(this.m_pPrp_final);
            pg.setPropertyHelpString(this.m_pPrp_final,
                "オプション。element 要素の final 属性のデフォルト値を設定する。 親要素が schema 要素でない場合、この属性は使用できない。 この値は、#all または、拡張あるいは制約のサブセットであるリストを含めることができる:\n* extension - 拡張により派生した要素を防ぐ\n* restriction - 制約により派生した要素を防ぐ\n* #all - すべての派生した要素を防ぐ");
        }





        //
        //  メンバー関数の実装
        //
        this.set = function (obj) {
            this.obj = obj;
            if (obj == null) {
                return;
            }
            /*
                this.bAbstruct = false;
                this.ulBlock = 0;
                this.strDefault =  "";
                this.ulFinal = 0;
                this.strFixed =  "";
                this.emForm = xsd.IS_QUALIFIED.QUALIFIED;
                this.ulMaxOccurs = 1;
                this.ulMinOccurs = 1;
                this.bIsRef =  false ;
                this.strName =  "";
                this.bNillable = false;
                this.strSubstitutionGroup =  "";
                this.strType =  "";
                this.pContent =  null;
                this.pRef =  null;
                this.pType =  null;
                this.pSubstitutionGroup = null;
                this.cntChldren = new Array();
            */

            var bParentSchema = obj.getParent().getEType() == xsd.E_TYPE.SCHEMA;
            var bIsParent = false;

            if (obj.pContent != null || obj.cntChldren.length != 0) {
                bIsParent = true;
            }

            // id
            if (obj.id != null) {
                this.m_pPrp_Id.setValue(obj.id);
            } else {
                this.m_pPrp_Id.setValue("");
            }

            if (bParentSchema == true) {
                this.m_pPrp_IsRef.setValue(false);
                this.m_pPrp_IsRef.hide(true);
            } else {
                this.m_pPrp_IsRef.setValue(obj.bIsRef);
                this.m_pPrp_IsRef.hide(false);
            }
            if (obj.bIsRef == false) {
                this.m_pPrp_Name.setValue(obj.strName);
                this.m_pPrp_Name.hide(false);
                this.m_pPrp_EmRef.hide(true);
            } else {
                this.m_pPrp_Name.hide(true);
                this.m_pPrp_EmRef.hide(false);
            }

            // ref
            {
                var select_index = -1;
                var index = 0;

                var bc = new wx.pg.Choices();
                bc.add("<<non specify>>");

                var pSchema = obj.getParentByType(xsd.E_TYPE.SCHEMA);

                for (var i in pSchema.cntAllObjs) {
                    var p = pSchema.cntAllObjs[i];
                    if (p.getEType() == xsd.E_TYPE.ELEMENT) {
                        bc.add(p.strName);
                        if (p == obj.pRef) {
                            select_index = index;
                        }
                        index++;
                    }
                }
                this.m_pPrp_EmRef.setChoices( bc );
                this.m_pPrp_EmRef.setValue(  ( select_index == -1 ? 0 : select_index+1) );
            }

            // type
            {
                var select_index = -1;
                var index = 0;

                var bc = new wx.pg.Choices();
                bc.add("<<non specify>>");

                var pSchema = obj.getParentByType(xsd.E_TYPE.SCHEMA);

                for (var i in pSchema.cntAllObjs) {
                    var p = pSchema.cntAllObjs[i];
                    if (p.getEType() == xsd.E_TYPE.SIMPLE_TYPE ||
                        p.getEType() == xsd.E_TYPE.COMPLEX_TYPE) {
                        bc.add(p.strName);
                        if( p == obj.pType ) {
                            select_index = index;
                        }
                        index++;
                    }
                }

                for (var i in pSchema.mapStockPrimitives ) {
                    var prim = pSchema.mapStockPrimitives[i];
                    bc.add("xsd:" + prim.getXmlTagName());
                    if( prim == obj.pType ) {
                        select_index = index;
                    }
                    index++;
                }

                this.m_pPrp_EmType.setChoices(bc);
                this.m_pPrp_EmType.setValue((select_index == -1 ? 0 : select_index + 1));
            }

            // substitutionGroup
            this.m_pPrp_substitutionGroup.hide(bParentSchema == true);
            {
                var select_index = -1;
                var index = 0;

                var bc = new wx.pg.Choices();
                bc.add("<<non specify>>");

                var pSchema = obj.getParentByType(xsd.E_TYPE.SCHEMA);

                for (var i in pSchema.cntAllObjs) {
                    var p = pSchema.cntAllObjs[i];
                    if (p.getEType() == xsd.E_TYPE.E_ELEMENT ) {
                        bc.add(p.strName);
//                        if (p == obj.pType) {
//                            select_index = index;
//                        }
                        index++;
                    }
                }
                this.m_pPrp_substitutionGroup.setChoices( bc );
                this.m_pPrp_substitutionGroup.setValue((select_index == -1 ? 0 : select_index + 1));
            }
            
            // default
            this.m_pPrp_default.setValue(obj.strDefault);
            // fixed
            this.m_pPrp_fixed.setValue(obj.strFixed);
            // form
            this.m_pPrp_form.setValue(obj.emForm);
            this.m_pPrp_form.hide(bParentSchema == true);
            // maxOccurs
            this.m_pPrp_maxOccurs.setValue(obj.ulMaxOccurs);
            this.m_pPrp_maxOccurs.hide(bParentSchema == true);
            // minOccurs
            this.m_pPrp_minOccurs.setValue(obj.ulMinOccurs);
            this.m_pPrp_minOccurs.hide(bParentSchema == true);
            // fixed
            this.m_pPrp_nillable.setValue(obj.bNillable);
            // abstract
            this.m_pPrp_abstract.setValue(obj.ulMinOccurs);
            this.m_pPrp_abstract.hide(bParentSchema != true);	// schema直下の未
            // block
            {
                var arstr = new Array();
                if( obj.ulBlock & xsd.BLOCK.EXTENSION ) {
                    arstr.push("extension");
                }
                if( obj.ulBlock & xsd.BLOCK.RESTRICTION ) {
                    arstr.push("restriction");
                }
                if( obj.ulBlock & xsd.BLOCK.SUBSTITUTION ) {
                    arstr.push("substitution");
                }
                this.m_pPrp_block.setValue(arstr);
            }
            // final
            {
                var arstr = new Array();
                if( obj.ulFinal & xsd.FINAL.EXTENSION ) {
                    arstr.push("extension");
                }
                if( obj.ulFinal & xsd.FINAL.RESTRICTION ) {
                    arstr.push("restriction");
                }
                this.m_pPrp_final.setValue(arstr);
                this.m_pPrp_final.hide( bParentSchema != true );	// schema直下の未
            }


            this.changeIsRef(obj.bIsRef);
        }
        this.unset = function () 
        {
            if (this.m_pPropGridManager.isPageModified(0) == false) {
                return true;
            }
            if (this.obj == undefined || this.obj == null) {
                return true;
            }
            var obj = this.obj;
            this.obj = null;

            var strVal = "";
            var pSchema = obj.getParentByType(xsd.E_TYPE.SCHEMA);

            // id
            strVal = this.m_pPrp_Id.getValue();
            obj.id = strVal.length == 0 ? null : strVal;

            // name or ref 
            if( this.m_pPrp_IsRef.getValue() == true ) {
                
            } else {
                obj.strName = this.m_pPrp_Name.getValue();
            }

            // type
            strVal = this.m_pPrp_EmType.displayString;
            if( strVal == "<<non specify>>") {
                strVal = "";
            }
            if( obj.changeType(strVal) == false ) {
                return false;
            }



            // substitutionGroup
            //  TODO....

            //default
            obj.strDefault = this.m_pPrp_default.getValue();
            //fixed
            obj.strFixed = this.m_pPrp_fixed.getValue();
            //form
            obj.emForm = this.m_pPrp_form.getValue();
            // maxOccurs
            obj.ulMaxOccurs = this.m_pPrp_maxOccurs.getValue();
            // minOccurs
            obj.ulMinOccurs = this.m_pPrp_minOccurs.getValue();
            // nillable
            obj.bNillable = this.m_pPrp_nillable.getValue();
            // abstract
            obj.bAbstruct = this.m_pPrp_abstract.getValue();
            // block
            {
                var flag = 0;
                var arstr = this.m_pPrp_block.getValue();
                for( var oo of arstr ) 
                {
                    if( oo == "extension" ) 
                    {
                      flag |= xsd.BLOCK.EXTENSION;
                    }
                    if( oo == "restriction" ) 
                    {
                       flag |= xsd.BLOCK.RESTRICTION;
                    }
                    if( oo == "substitution" ) 
                    {
                        flag |= xsd.BLOCK.SUBSTITUTION;
                    }
                }
                obj.ulBlock = flag;
            }
           // final
            {
                var flag = 0;
                var arstr = this.m_pPrp_final.getValue();
                for( var oo of arstr ) 
                {
                    if( oo == "extension" ) 
                    {
                        flag |= xsd.FINAL.EXTENSION;
                    }
                    if( oo == "restriction" ) 
                    {
                        flag |= xsd.FINAL.RESTRICTION;
                    }
                }
                obj.ulFinal = flag;
            }


            this.m_pPropGridManager.clearModifiedStatus();

            return true;
        }

        this.m_pPropGridManager.onChanged = function (evt) {

            if (this.me.m_pPrp_IsRef.label == evt.property.label) {
                this.me.changeIsRef(evt.property.getValue());
            }
        }

        // 
        this.changeIsRef = function (bIsRef) {
            this.m_pPrp_Name.hide(bIsRef);
            this.m_pPrp_EmRef.hide(!bIsRef);
            this.m_pPrp_nillable.hide(bIsRef);
            this.m_pPrp_default.hide(bIsRef);
            this.m_pPrp_fixed.hide(bIsRef);
            this.m_pPrp_form.hide(bIsRef);
            this.m_pPrp_block.hide(bIsRef);
            this.m_pPrp_EmType.hide(bIsRef);
        }
    }

};















var RightPane = function (frame/*, parent*/) {
    var m_notebook_style = wx.Aui.NotebookOption.DEFAULT_STYLE | wx.Aui.NotebookOption.TAB_EXTERNAL_MOVE | wx.Border.NONE;
    m_notebook_style &= ~(wx.Aui.NotebookOption.CLOSE_BUTTON |
						  wx.Aui.NotebookOption.CLOSE_ON_ACTIVE_TAB |
						  wx.Aui.NotebookOption.CLOSE_ON_ALL_TABS);
    // NoteBookの作成
    this.pTabRight = new wx.Aui.Notebook(frame, -1,
                                    wx.Point(10, 10),
                                    wx.Size(200, 500),
                                    m_notebook_style
							);



    frame.auiMgr.addPane(this.pTabRight, new wx.Aui.PaneInfo().
				name("Root").
				center().
				layer(2).
				maximizeButton().
				minimizeButton().
				maximize().
				closeButton(false).
				caption("Root")
    );
    this.auiMgr = frame.auiMgr;


    this.cntSetRightPanel = new Array();    // 表示されているマップ
    this.cntRightPanel = new Map();         // このクラスで生成されているマップの一覧

    // Annotation
    this.paneAnnotation = new PanelRightXsdAnnotation(frame);
    this.paneAnnotation.panel.show(false);
    this.cntRightPanel.set(xsd.E_TYPE.ANNOTATION, this.paneAnnotation);


    // Appinfo
    this.paneAppinfo = new PanelRightXsdAppinfo(frame);
    this.paneAppinfo.panel.show(false);
    this.cntRightPanel.set(xsd.E_TYPE.APPINFO, this.paneAppinfo);


    // Documentation
    this.paneDocumentation = new PanelRightXsdDocumentation(frame);
    this.paneDocumentation.panel.show(false);
    this.cntRightPanel.set(xsd.E_TYPE.DOCUMENTATION, this.paneAnnotation);

    // Element
    this.paneElement = new PanelRightXsdElement(frame);
    this.paneElement.panel.show(false);
    this.cntRightPanel.set(xsd.E_TYPE.ELEMENT, this.paneElement);

    //
    // 左ペインのXSDツリーアイテムが選択されたとき、右ペインの画面を切り替える。
    //
    this.notifyXSDItem = function (obj) {

        // 表示されているパネルを非表示にする。
        while (this.pTabRight.pageCount != 0) {
            this.pTabRight.removePage(0);
        }
        for (i in this.cntSetRightPanel) {
            this.cntSetRightPanel[i].panel.show(false);
            this.cntSetRightPanel[i].unset();
        }
        this.cntSetRightPanel = new Array();

        if (obj == null) {
            return;
        }

        // Object　Typeに応じた画面を表示
        if (obj.getEType() == xsd.E_TYPE.ANNOTATION) {
            this.pTabRight.addPage(this.paneAnnotation.panel, wx.Locale.getTranslation("Annotation"));
            this.cntSetRightPanel.push(this.paneAnnotation);
            this.paneAnnotation.panel.show(true);
            this.paneAnnotation.set(obj);
        }
        else if (obj.getEType() == xsd.E_TYPE.APPINFO) {
            this.pTabRight.addPage(this.paneAppinfo.panel, wx.Locale.getTranslation("Appinfo"));
            this.cntSetRightPanel.push(this.paneAppinfo);
            this.paneAppinfo.panel.show(true);
            this.paneAppinfo.set(obj);
        }
        else if (obj.getEType() == xsd.E_TYPE.DOCUMENTATION) {
            this.pTabRight.addPage(this.paneDocumentation.panel, wx.Locale.getTranslation("Documentation"));
            this.cntSetRightPanel.push(this.paneDocumentation);
            this.paneDocumentation.panel.show(true);
            this.paneDocumentation.set(obj);
        }
        else if (obj.getEType() == xsd.E_TYPE.ELEMENT) {
            this.pTabRight.addPage(this.paneElement.panel, wx.Locale.getTranslation("Element"));
            this.cntSetRightPanel.push(this.paneElement);
            this.paneElement.panel.show(true);
            this.paneElement.set(obj);
        }


        this.auiMgr.update();
    }
}