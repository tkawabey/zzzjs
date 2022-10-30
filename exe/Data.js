/*

*/


///  http://qiita.com/Koizumi-Greenwich/items/96215899b8b61cc85e65

// Object Source Createrの略
var osc = new Object();
// IDの定義
osc.D_TYPE_PRJ = 0;
osc.D_TYPE_SETTING_JAVA = 1;
osc.D_TYPE_CLASS = 2;
osc.D_TYPE_CONSTRUCT = 3;
osc.D_TYPE_ENUM = 4;
osc.D_TYPE_ENUM_VAL = 5;
osc.D_TYPE_MEMBER = 6;
osc.D_TYPE_MEMBER_ADD_PARAM = 7;
osc.D_TYPE_MEMBER_NEW_DEL_METHOD = 8;
osc.D_TYPE_LOADED_CLASS = 9;
osc.D_TYPE_PARAM = 10;
osc.D_TYPE_ARG = 11;
osc.D_TYPE_FUNCTION = 12;
osc.D_TYPE_RETURN_DESC = 13;
osc.D_TYPE_CODE = 14;
// Method
osc.METHOD = {
    NON: 0,
    GET: 1,
    SET: 2,
    BOTH: 3
};

// Data Type
osc.TYPE = {
    ENUM: 0,
    INT: 1,
    UINT: 2,
    INT64: 3,
    UINT64: 4,
    FLOAT: 5,
    DOUBLE: 6,
    STRING: 7,
    BOOL: 8,
    BYTE_ARRAY: 9,
    DATE: 10,
    OBJ: 11,
    OBJ_ARRAY: 12,
    BASE_OBJ_ARRAY: 13,
    VOID: 14,
    UNKOWN: 15
};

// DBのデータ型
osc.DB_TYPE = {
    NON: 0,
    STRING: 1,
    INT: 2,
    INT64: 3,
    DOUBLE: 4,
    BLOB: 5
};

// データタイプがosc.TYPE.OBJの場合の振る舞い。
osc.OBJ_ROLE = {
    NEW: 0,
    REF_POINTER: 1,     /// 参照設定
    STACK_INST: 2       /// スタックインスタンス
};

//-------------------------------------
//  Declere DBase
//-------------------------------------
DBase: {
    function DBase(parent) {
        this.parent = parent;
        this.bIsDirty = false;
    }
    var p = DBase.prototype;
    p.getParent = function () {
        return this.parent;
    }
    p.isDirty = function () {
        return this.bIsDirty;
    }
    p.getDType = function () {
        return -1;
    }
};


//-------------------------------------
//  Declere DProject
//-------------------------------------
DProject: {
    function DProject() {
        DBase.call(this, null);

        this.cntClass = new Array();
    }
    DProject.prototype = Object.create(DBase.prototype, { value: { constructor: DProject } });


    var p = DProject.prototype;
    p.load = function (rootNode) {
        var attrs = rootNode.attrs;

        //var attrNames = Object.getOwnPropertyNames(attrs);

        //print("Class:" + rootNode.name );
        //for (i in attrNames) {
        //    print("VVV:" + i + " : TTT : " + attrNames[i] + " : RRR : " + attrs[attrNames[i]]);
        //}


        for (i in rootNode.elements) {
            if (rootNode.elements[i].name == "class") {
                var dClass = new DClass(this);
                dClass.load(rootNode.elements[i]);
                this.cntClass.push(dClass);
            }
        }
    }

}
//-------------------------------------
//  Declere DClass
//-------------------------------------
DClass: {
    function DClass(parent) {
        DBase.call(this, parent);

        this.name = "";
        this.defineName = "";
        this.desc = "";
        this.table = "";
        this.extern = "";
        this.xmlTag = "";
        this.bIsXml = false;
        this.bIsDbTable = false;
        this.bIsStream = false;

        this.cntEnum = new Array();
        this.cntConstruct = new Array();
        this.cntMember = new Array();
        this.cntFunction = new Array();
    }
    DClass.prototype = Object.create(DBase.prototype, { value: { constructor: DClass } });

    var p = DClass.prototype;
    p.getDType = function () {
        return 1;
    }
    p.load = function (rootNode) {
        var attrs = rootNode.attrs;

        //var attrNames = Object.getOwnPropertyNames(attrs);
        //print("Class:" + rootNode.name);
        //for (i in attrNames) {
        //    print("VVV:" + i + " : TTT : " + attrNames[i] + " : RRR : " + attrs[attrNames[i]]);
        //}


        if (attrs.name == undefined) {
            throw new Error("undefined attribute class@name");
        }
        this.name = attrs.name;
        if (attrs.table != undefined) {
            this.table = attrs.table;
        }
        if (attrs.extern != undefined) {
            this.extern = attrs.extern;
        }
        if (attrs.xml_tag != undefined) {
            this.xmlTag = attrs.xml_tag;
        }
        if (attrs.is_xml != undefined) {
            if (attrs.is_xml == "true") {
                this.bIsXml = true;
            } else {
                this.bIsXml = false;
            }
        }
        if (attrs.is_db_table != undefined) {
            if (attrs.is_db_table == "true") {
                this.bIsDbTable = true;
            } else {
                this.bIsDbTable = false;
            }
        }
        if (attrs.is_stream != undefined) {
            if (attrs.is_stream == "true") {
                this.bIsStream = true;
            } else {
                this.bIsStream = false;
            }
        }


        for (i in rootNode.elements) {
            if (rootNode.elements[i].name == "desc") {
                this.desc = rootNode.elements[i].data;
            }
        }
    }
}


//-------------------------------------
//  Declere DMember
//-------------------------------------
DMember: {
    function DMember(parent) {
        DBase.call(this, parent);

        this.name = "";
        this.defineName = "";
        this.desc = "";
        this.field = "";
        this.emType = osc.TYPE.UNKOWN;
        this.dbField = "";
        this.nSize = 0;
        this.xmlTag = "";
        this.isXmlElment = false;
        this.isXmlCData = false;
        this.isXmlEnable = false;
        this.isXmlOption = false;
        this.isKey = false;
        this.isNull = false;
        this.isInherit = false;
        this.isGetSetImplFunc = false;
        this.emMethod = osc.METHOD.NON;
        this.emObjRole = osc.OBJ_ROLE.NEW;
        this.noMember = "";
        this.strClass = "";
        this.strRefEnum = "";
        this.strRefEnumClass = "";
        this.isDataDbLong = false;
        this.emDbType = false;
        this.isDbField = false;
        this.isModifyCheck = false;
        this.valueMax = "";
        this.valueMin = "";
        this.valueInit = "";


        this.cntLoadedClass = new Array();
        this.cntParams = new Array();
        this.cntNewParams = new Array();
    }
    DMember.prototype = Object.create(DBase.prototype, { value: { constructor: DMember } });

    var p = DMember.prototype;
    p.getDType = function () {
        return 1;
    }
    // 
    p.judgeTypeStr = function(val) {
        val = val.toLowerCase();
        if (val == "enum") {
            return osc.TYPE.ENUM;
        } else if (val == "integer" || val == "integer") {
            return osc.TYPE.INT;
        } else if (val == "unsigned integer" || val == "uint") {
            return osc.TYPE.UINT;
        } else if (val == "long" || val == "int64") {
            return osc.TYPE.INT64;
        } else if (val == "unsigned long" || val == "ulong" || val == "uint64") {
            return osc.TYPE.UINT64;
        } else if (val == "float") {
            return osc.TYPE.FLOAT;
        } else if (val == "double") {
            return osc.TYPE.DOUBLE;
        } else if (val == "varchar" || val == "string") {
            return osc.TYPE.STRING;
        } else if (val == "bool" || val == "boolean") {
            return osc.TYPE.BOOL;
        } else if (val == "unsigned char*" || val == "byte[]") {
            return osc.TYPE.BYTE_ARRAY;
        } else if (val == "date") {
            return osc.TYPE.DATE;
        } else if (val == "obj" || val == "object") {
            return osc.TYPE.BOOL;
        } else if (val == "obj_array" ) {
            return osc.TYPE.OBJ_ARRAY;
        } else if (val == "base_obj_array") {
            return osc.TYPE.BASE_OBJ_ARRAY;
        } else if (val == "void") {
            return osc.TYPE.VOID;
        }
        return osc.TYPE.UNKOWN;
    }

    // TYPEを文字列にします。
    p.convType2String = function (emType) {
        switch (emType) {
            case osc.TYPE.ENUM:
                return "enum";
                break;
            case osc.TYPE.INT:
                return "int";
                break;
            case osc.TYPE.UINT:
                return "uint";
                break;
        }
    }


    // XMLノードからロードします。
    p.load = function (rootNode) {
        var attrs = rootNode.attrs;

        if (attrs.name == undefined) {
            throw new Error("undefined attribute member@name");
        }
        this.name = attrs.name;
        if (attrs.table != undefined) {
            this.table = attrs.table;
        }
        if (attrs.extern != undefined) {
            this.extern = attrs.extern;
        }
        if (attrs.xml_tag != undefined) {
            this.xmlTag = attrs.xml_tag;
        }
        if (attrs.is_xml != undefined) {
            if (attrs.is_xml == "true") {
                this.bIsXml = true;
            } else {
                this.bIsXml = false;
            }
        }
        if (attrs.is_db_table != undefined) {
            if (attrs.is_db_table == "true") {
                this.bIsDbTable = true;
            } else {
                this.bIsDbTable = false;
            }
        }
        if (attrs.is_stream != undefined) {
            if (attrs.is_stream == "true") {
                this.bIsStream = true;
            } else {
                this.bIsStream = false;
            }
        }


        for (i in rootNode.elements) {
            if (rootNode.elements[i].name == "desc") {
                this.desc = rootNode.elements[i].data;
            }
        }
    }
}



