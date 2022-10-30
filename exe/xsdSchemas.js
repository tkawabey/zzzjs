/*
    XSD Schemaのデータクラス
*/


///  http://qiita.com/Koizumi-Greenwich/items/96215899b8b61cc85e65




//-------------------------------------
//  ネームスペース
//-------------------------------------
var xsd = new Object();
xsd.XSD_NAMESPACE_URI = "http://www.w3.org/2001/XMLSchema";
// 
xsd.E_TYPE = {
        SCHEMA : 0			    ///< XsdSchema
    ,	ALL : 1				    ///< XsdAll
    ,	ANNOTATION : 2		    ///< XsdAnnotation
    ,	ANY : 3		        	///< XsdAny
    ,	ANY_ATTRIBUTE : 4		///< XsdAnyAttribute
    ,	APPINFO : 5			    ///< XsdAppinfo
    ,	ATTRIBUTE : 6			///< XsdAttribute
    ,	ATTRIBUTE_GROUP : 7	    ///< XsdAttributeGroup
    ,	CHOICE : 8			    ///< XsdChoice
    ,	COMPLEX_CONTEXT : 9	    ///< XsdComplexContent
    ,	COMPLEX_TYPE : 10		///< XsdComplexType
    ,	DOCUMENTATION : 11		///< XsdDocumentation
    ,	ELEMENT : 12			///< XsdElement
    ,	EXTESION : 13			///< XsdExtension
    ,	FIELD : 14				///< XsdField
    ,	GROUP : 15				///< XsdGroup
    ,	IMPORT : 16			    ///< XsdImport
    ,	INCLUDE : 17			///< XsdInclude
    ,	KEY : 18				///< XsdKey
    ,	KEYREF : 19		    	///< XsdKeyref
    ,	LIST : 20				///< XsdList
    ,	NOTION : 21			    ///< XsdNotation
    ,	REDEFINE : 22			///< XsdRedefine
    ,	RESTRICTION : 23		///< XsdRestriction
    ,	RESTRICTION_VAL : 24	///< XsdRestrictionVal
    ,	SELECTOR : 25			///< XsdSelector
    ,	SEQUENCE : 26			///< XsdSequence
    ,	SIMPLE_CONTEXT : 27	    ///< XsdSimpleContent
    ,	SIMPLE_TYPE : 28		    ///< XsdSimpleType
    ,	UNION : 29				///< XsdUnion
    ,	UNIQUE : 30		    	///< XsdUnique

    ,   PRIMITIVTYPE: 31	    ///< XsdPrimitivType
};
//
xsd.IS_QUALIFIED = {
        QUALIFIED : 0
    ,	UNQUALIFIED : 1
};
//
xsd.BLOCK = {
        EXTENSION: 0x0001
    , RESTRICTION: 0x0002
    , SUBSTITUTION: 0x0004
    , ALL: 0x0007
};
// 
xsd.FINAL = {
        EXTENSION: 0x0001
    , RESTRICTION: 0x0002
    , LIST: 0x0004
    , UNION: 0x0008
    , ALL: 0x000F
};
// 
xsd.R_TYPE = {
        EMUERATION : 0x0001
    ,	FRACTION_DIGITS : 0x0002
    ,	LENGTH : 0x0003
    ,	MAX_LENGTH : 0x0004
    ,	MIN_LENGTH : 0x0005
    ,	MAX_EXCLUSIVE : 0x0006
    ,	MAX_INCLUSIVE : 0x0007
    ,	MIN_EXCLUSIVE : 0x0008
    ,	MIN_INCLUSIVE : 0x0009
    ,	PATTERN : 0x000a
    ,	TOTAL_DIGITS : 0x000b
    ,   WHITE_SPACE: 0x000c
};
//
xsd.ANY_NAMESPACE = {
        ANY : 0
    ,	OTHER : 1
    ,	LOCAL : 2
    ,	TARGET_NAMESPACE : 3
};
//
xsd.ANY_PROC_CONT = {
        STRICT : 0
    ,	LAX : 1
    ,	SKIP : 2
};
//
xsd.EMUSE = {
        OPTIONAL : 0
    ,	PROHIBITED : 1
    ,	REQUIRED : 2
};
xsd.PRIM_TYPE = {
        /// 文字列
        ENTITIES : 0
    ,	ENTITY : 1
    ,	ID : 2
    ,	IDREF : 3
    ,	IDREFS : 4
    ,	language : 5
    ,	Name :6 
    ,	NCName : 7
    ,	NMTOKEN : 8	/// XMLのNMTOKEN属性を表す文字列（スキーマ属性でのみ使用）
    ,	NMTOKENS : 9
    ,	normalizedString: 10	/// ラインフィード、キャリッジリターン、またはタブを含まない文字列
    ,	QName : 11
    ,	string : 12
    ,	token: 13				/// ラインフィード、キャリッジリターン、タブ、先頭と末尾のスペース、 および複数のスペースを含まない文字列
        /// 日付型
    ,	date : 14				/// 日付の値を定義する
    ,	dateTime : 15			/// 日付と時刻値を定義する
    ,	duration : 16			/// 時間間隔を定義する
    ,	gDay : 17				/// 日付の一部を定義する - 日 (DD)
    ,	gMonth : 18			/// 日付の一部を定義する - 月 (MM)
    ,	gMonthDay : 19			/// 日付の一部を定義する - 月と日 (MM-DD)
    ,	gYear : 20				/// 日付の一部を定義する - 年 (YYYY)
    ,	gYearMonth : 21		/// 日付の一部を定義する - 年と月 (YYYY-MM)
    ,	time : 22				/// 時刻値を定義する
        /// 数値
    ,	byte : 23				/// 符号付き8ビット整数
    ,	decimal : 24			/// 10進数値
    ,	int : 25				/// 符号付き32ビット整数
    ,	integer : 26			/// 整数値
    ,	long : 27				/// 符号付き64ビット整数
    ,	negativeInteger : 28	/// 負の整数 (..,-2,-1)
    ,	nonNegativeInteger : 29 /// 負でない整数 (0,1,2,..)
    ,	nonPositiveInteger : 30/// 正でない整数 (..,-2,-1,0)
    ,	positiveInteger	: 31/// 正の整数 (1,2,..)
    ,	short : 32				/// 符号付き16ビット整数
    ,	unsignedLong : 33		/// 符号なし64ビット整数
    ,	unsignedInt : 34		/// 符号なし32ビット整数
    ,	unsignedShort : 35		/// 符号なし16ビット整数
    ,	unsignedByte : 36		/// 符号なし8ビット整数
        /// その他
    ,	anyURI : 37			/// 
    ,	base64Binary : 38		/// 
    ,	boolean : 39			/// 
    ,	double : 40			/// 
    ,	float : 41				/// 
    ,	hexBinary :42			/// 
    ,	NOTATION : 43			/// 

    , UNKOWN: 990			/// 
};

//-------------------------------------
//  XsdNamespace
//-------------------------------------
XsdNamespace: {
    function XsdNamespace(strNS, strURI) {
        this.strNS = strNS;
        this.strURI = strURI;
    }
    var p = XsdNamespace.prototype;
    p.toString = function() {
        var ret = "XsdNamespace[" + this.strNS + "/" + this.strURI + "]";
        return ret;
    }
};



//-------------------------------------
//  XsdBase
//-------------------------------------
XsdBase: {
    function XsdBase(parent, ns) {
        this.parent = parent;
        this.namespase = ns;
        this.lineNo = -1;
    }
    var p = XsdBase.prototype;
    p.getParent = function () {
        return this.parent;
    }
    p.isDirty = function () {
        return this.bIsDirty;
    }
    p.getEType = function () {
        return -1;
    }
    p.getXmlTagName = function () {
        return "???";
    }
    p.getParentByType = function (type) {
        if (this.getEType() == type) {
            return this;
        }
        if (this.parent == null) {
            return null;
        }
        return this.parent.getParentByType( type );
    }
    p.getLineNo = function() {
        return this.lineNo;
    }
    p.setLineNo = function( lineNo ) {
        this.lineNo = lineNo;
    }
    p.getName = function()
    {
        return "";
    }
    //　データの妥当性をチェックします。
    p.validate = function() {
        return true;
    }
    //
    // XMLノードから、データをロードします。
    //
    p.load = function (rootNode) {
        try {
            this.setLineNo( rootNode.lineNo );
            if (rootNode.id != undefined) {
                this.id = rootNode.id;
            }
        } catch (e) {

            return false;
        }
        return true;
    }
    
    p.splitNs = function (strName) {
        var ret = new Object();
        var idx = strName.indexOf(":");

        ret.pNameSpace = null;
        if (idx != -1) {
            ret.ns = strName.substr(0, idx);
            ret.Val = strName.substr(idx+1);
            ret.pNameSpace = this.findNamespace( ret.ns );
        } else {
            ret.ns = null;
            ret.Val = strName;
        }
        return ret;
    }

    p.errFmt = function (line, msg) {

        print("ERR!! Line:" + line + " Message:" + msg);
        var schema = this.getParentByType(xsd.E_TYPE.SCHEMA);
        if (schema != null) {
            var errObj = new Object();
            errObj.line = line;
            errObj.msg = msg;
            schema.cntError.push(errObj);
        }
    }

    p.findNamespace = function(ns) {        
        var schema = this.getParentByType(xsd.E_TYPE.SCHEMA);
        if (schema != null) {
            return schema.getNamespaceByName(ns);
        }
        return null;
    }
};



//-------------------------------------
//  XsdPrimitivType
//-------------------------------------
XsdPrimitivType: {
    function XsdPrimitivType(parent, ns, emRType) {
        XsdBase.call(this, parent, ns);

        this.emRType = emRType;
    }
    XsdPrimitivType.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdPrimitivType } });
    var p = XsdPrimitivType.prototype;



    p.PRIM_MAP = new Map();
    p.PRIM_MAP.set(xsd.PRIM_TYPE.ENTITIES, "ENTITIES");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.ENTITY, "ENTITY");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.ID, "ID");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.IDREF, "IDREF");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.IDREFS, "IDREFS");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.language, "language");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.Name, "Name");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.NCName, "NCName");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.NMTOKEN, "NMTOKEN");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.NMTOKENS, "NMTOKENS");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.normalizedString, "normalizedString");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.QName, "QName");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.string, "string");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.token, "token");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.date, "date");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.dateTime, "dateTime");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.duration, "duration");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.gDay, "gDay");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.gMonth, "gMonth");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.gMonthDay, "gMonthDay");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.gYear, "gYear");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.gYearMonth, "gYearMonth");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.time, "time");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.byte, "byte");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.decimal, "decimal");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.int, "int");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.integer, "integer");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.long, "long");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.negativeInteger, "negativeInteger");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.nonNegativeInteger, "nonNegativeInteger");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.nonPositiveInteger, "nonPositiveInteger");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.positiveInteger, "positiveInteger");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.short, "short");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.unsignedLong, "unsignedLong");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.unsignedInt, "unsignedInt");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.unsignedShort, "unsignedShort");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.unsignedByte, "unsignedByte");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.anyURI, "anyURI");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.base64Binary, "base64Binary");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.boolean, "boolean");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.double, "double");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.float, "float");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.hexBinary, "hexBinary");
    p.PRIM_MAP.set(xsd.PRIM_TYPE.NOTATION, "NOTATION");
    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.E_PRIMITIVE_TYPE;
    }
    p.getXmlTagName = function () {
        return this.PRIM_MAP.get(this.emRType);
    }
    p.toString = function() {
        return this.getXmlTagName();
    }


    p.getPrimitiveName = function (emRType) {
        return this.PRIM_MAP.get(this.emRType);
    }
    p.getPrimitiveType = function (name) {
        return xsd.PRIM_TYPE.string;

        for (var [key, value] of  this.PRIM_MAP ) {

            if( name.localeCompare(value)  == 0 ) {
                return key;
            }
        }
        return undefined;

    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
          return true;
    }
};

//-------------------------------------
//  XsdSchema
//-------------------------------------
XsdSchema: {
    function XsdSchema() {
        XsdBase.call(this, null, null);
        this.super = XsdBase.prototype;

        this.emAttributeFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
        this.ulBlockDefault = 0;
        this.emElementFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
        this.ulFinalDefault = 0;
        this.strTargetNamespace = "";
        this.strVersion = "";
        this.strLang = "";

        this.cntNameSpace = new Array();
        this.cntAllObjs = new Array();
        this.cntError = new Array();
        //this.mapStockPrimitives = new Map(); // Mapの動作が、SpiderMokey2.4で不安定なので、Arraiに置き換える
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.ENTITIES, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.ENTITIES));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.ENTITY, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.ENTITY));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.ID, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.ID));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.IDREF, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.IDREF));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.IDREFS, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.IDREFS));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.language, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.language));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.Name, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.Name));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.NCName, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.NCName));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.NMTOKEN, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.NMTOKEN));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.NMTOKENS, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.NMTOKENS));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.normalizedString, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.normalizedString));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.QName, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.QName));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.string, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.string));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.token, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.token));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.date, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.date));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.dateTime, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.dateTime));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.duration, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.duration));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.gDay, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.gDay));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.gMonth, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.gMonth));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.gMonthDay, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.gMonthDay));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.gYear, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.gYear));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.gYearMonth, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.gYearMonth));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.time, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.time));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.byte, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.byte));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.decimal, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.decimal));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.int, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.int));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.integer, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.integer));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.long, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.long));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.negativeInteger, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.negativeInteger));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.nonNegativeInteger, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.nonNegativeInteger));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.nonPositiveInteger, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.nonPositiveInteger));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.positiveInteger, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.positiveInteger));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.short, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.short));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.unsignedLong, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.unsignedLong));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.unsignedInt, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.unsignedInt));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.unsignedShort, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.unsignedShort));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.unsignedByte, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.unsignedByte));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.anyURI, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.anyURI));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.base64Binary, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.base64Binary));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.boolean, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.boolean));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.double, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.double));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.float, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.float));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.hexBinary, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.hexBinary));
        //this.mapStockPrimitives.set(xsd.PRIM_TYPE.NOTATION, new XsdPrimitivType(this, null, xsd.PRIM_TYPE.NOTATION));
        this.mapStockPrimitives = new Array();
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.ENTITIES));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.ENTITY));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.ID));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.IDREF));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.IDREFS));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.language));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.Name));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.NCName));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.NMTOKEN));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.NMTOKENS));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.normalizedString));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.QName));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.string));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.token));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.date));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.dateTime));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.duration));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.gDay));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.gMonth));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.gMonthDay));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.gYear));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.gYearMonth));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.time));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.byte));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.decimal));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.int));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.integer));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.long));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.negativeInteger));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.nonNegativeInteger));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.nonPositiveInteger));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.positiveInteger));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.short));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.unsignedLong));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.unsignedInt));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.unsignedShort));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.unsignedByte));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.anyURI));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.base64Binary));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.boolean));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.double));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.float));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.hexBinary));
        this.mapStockPrimitives.push( new XsdPrimitivType(this,  null,  xsd.PRIM_TYPE.NOTATION));

    }
    XsdSchema.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdSchema } });
    var p = XsdSchema.prototype;
    




    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.SCHEMA;
    }
    p.getXmlTagName = function () {
        return "schema";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    p.getNamespaceByName = function(ns) {
        for(var i in this.cntNameSpace ) {
            if( this.cntNameSpace[i].strNS == ns ) {
                return this.cntNameSpace[i];
            }
        }
        return null;
    }
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBase.prototype.validate.call(this) == false ) {
            bOk = false;
        }
        for(var i in this.cntAllObjs ) {
            
            if( this.cntAllObjs[i].validate() == false ) {
                bOk = false;
            }
        }
        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            // リセット処理
            this.emAttributeFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
            this.ulBlockDefault = 0;
            this.emElementFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
            this.ulFinalDefault = 0;
            this.strTargetNamespace = "";
            this.strVersion = "";
            this.strLang = "";
            this.cntNameSpace = new Array();
            this.cntAllObjs = new Array();
            this.cntError = new Array();

            // 継承元の関数をコール
            this.super.load.call(this, rootNode);
            var attrs = rootNode.attrs;

            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.ns == "xmlns") {
                    var newNs = new XsdNamespace(nsN.Val, attrs[attr]);
                    this.cntNameSpace.push(newNs);
                }
                else if (nsN.ns == "attributeFormDefault") {
                    if (attrs[attr] == "qualified") {
                        this.emAttributeFormDefault = xsd.IS_QUALIFIED.QUALIFIED;
                    }
                    else if (attrs[attr] == "unqualified") {
                        this.emAttributeFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
                    } else {
                        this.errFmt(this.getLineNo(),  "invalid attribute value. attributeFormDefault=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.ns == "blockDefault") {
                    tokens = attrs[attr].split(" ");
                    this.ulBlockDefault = 0;
                    for (var token in tokens) {
                        if (token == "#all") {
                            this.ulBlockDefault |= xsd.BLOCK.ALL;
                        }
                        else if (token == "extension") {
                            this.ulBlockDefault |= xsd.BLOCK.EXTENSION;
                        }
                        else if (token == "restriction") {
                            this.ulBlockDefault |= xsd.BLOCK.RESTRICTION;
                        }
                        else if (token == "substitution") {
                            this.ulBlockDefault |= xsd.BLOCK.SUBSTITUTION;
                        } else {
                            this.errFmt(this.getLineNo(), "invalid attribute value. blockDefault=" + attrs[attr]);
                            return false;
                        }
                    }
                }
                else if (nsN.ns == "elementFormDefault") {
                    if (attrs[attr] == "qualified") {
                        this.emElementFormDefault = xsd.IS_QUALIFIED.QUALIFIED;
                    }
                    else if (attrs[attr] == "unqualified") {
                        this.emElementFormDefault = xsd.IS_QUALIFIED.UNQUALIFIED;
                    } else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. elementFormDefault=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.ns == "finalDefault") {
                    tokens = attrs[attr].split(" ");
                    this.ulFinalDefault = 0;
                    for (var token in tokens) {
                        if (token == "#all") {
                            this.ulFinalDefault |= xsd.FINAL.ALL;
                        }
                        else if (token == "extension") {
                            this.ulFinalDefault |= xsd.FINAL.EXTENSION;
                        }
                        else if (token == "restriction") {
                            this.ulFinalDefault |= xsd.FINAL.RESTRICTION;
                        }
                        else if (token == "list") {
                            this.ulFinalDefault |= xsd.FINAL.LIST;
                        }
                        else if (token == "union") {
                            this.ulFinalDefault |= xsd.FINAL.UNION;
                        } else {
                            this.errFmt(this.getLineNo(), "invalid attribute value. finalDefault=" + attrs[attr]);
                            return false;
                        }
                    }
                }
                else if (nsN.ns == "id") {
                    this.id = attrs[attr];
                }
                else if (nsN.ns == "targetNamespace") {
                    this.strTargetNamespace = attrs[attr];
                }
                else if (nsN.ns == "version") {
                    this.strVersion = attrs[attr];
                }
                else if (nsN.ns == "lang") {
                    this.strLang = attrs[attr];
                }
            }
            for (i in rootNode.elements) {
                var nsN = this.splitNs( rootNode.elements[i].name);
                var newVal = null;
                if (nsN.Val == "annotation") {
                    newVal = new XsdAnnotation(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "include") {
                    newVal = new XsdInclude(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "import") {
                    newVal = new XsdImport(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "redefine") {
                    newVal = new XsdRedefine(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "complexType") {
                    newVal = new XsdComplexType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "attributeGroup") {
                    newVal = new XsdAttributeGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "element") {
                    newVal = new XsdElement(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "attribute") {
                    newVal = new XsdAttribute(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                else if (nsN.Val == "notation") {
                    newVal = new XsdNotation(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }


                if (newVal != null) {
                    this.cntAllObjs.push(newVal);
                }
            }
        } catch (e) {
            throw e;
            return false;
        }

        this.innerBuild( this );
        // 妥当性をチェックする。
        return this.validate();
    }
    


    // 内部関数
    p.innerBuild = function(pParent) {
        switch( pParent.getEType() ) {
            case xsd.E_TYPE.SCHEMA:
                {
                    for(var i in pParent.cntAllObjs ) {
                        if( this.innerBuild( pParent.cntAllObjs[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.ALL:
                {
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntElemnt ) {
                        if( this.innerBuild( pParent.cntElemnt[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.ANNOTATION:
                {
                    for(var i in pParent.cntChldren ) {
                        if( this.innerBuild( pParent.cntChldren[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.ANY:
                {
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.ANY_ATTRIBUTE:
                {
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.APPINFO:
                break;
            case xsd.E_TYPE.ATTRIBUTE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.strRef.length != 0 ) {
                        var pRef = this.findByName( pParent.strRef );
                        if( pRef == null ) {
                            this.errorFmt( pParent.getLineNo(), "name is not found. ref=" + pParent.strRef);
                            return false;
                        }
                        if( pRef.getEType() != xsd.E_TYPE.ATTRIBUTE ) {
                            this.errorFmt( pParent.getLineNo(), "reference item is not attribute. ref=" + pParent.strRef);
                            return false;
                        }
                        pParent.pRef = pRef;
                    }
                    if( pParent.pSimpleType != null ) {
                        if( this.innerBuild( pParent.pSimpleType) == false ) {
                            return false;
                        }
                    }
                    if( pParent.strType.length != 0 ) {
                        var pType = this.innerBuildType(pParent, pParent.strType);
                        if( pType == null ) {
                            return false;
                        }
                        pParent.pType = pType;
                    }
                }
                break;
            case xsd.E_TYPE.ATTRIBUTE_GROUP:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.strRef.length != 0 ) {
                        var pRef = this.findByName( pParent.strRef );
                        if( pRef == null ) {
                            this.errorFmt( pParent.getLineNo(), "name is not found. ref=" + pParent.strRef);
                            return false;
                        }
                        if( pRef.getEType() != xsd.E_TYPE.ATTRIBUTE_GROUP ) {
                            this.errorFmt( pParent.getLineNo(), "reference item is not attributeGroup. ref=" + pParent.strRef);
                            return false;
                        }
                        pParent.pRef = pRef;
                    }
                }
                break;
            case xsd.E_TYPE.CHOICE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    for(var i in pParent.cntChldren ) {
                        if( this.innerBuild( pParent.cntChldren[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.COMPLEX_CONTEXT:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.COMPLEX_TYPE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                    //XsdBaseHasAttr
                    for(var i in pParent.cntAttribute ) {
                        if( this.innerBuild( pParent.cntAttribute[i] ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.anyAttribute != null ) {
                        if( this.innerBuild( pParent.anyAttribute ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.DOCUMENTATION:
                break;
            case xsd.E_TYPE.ELEMENT:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.bIsRef == true ) {
                        var pRef = this.findByName( pParent.strName );
                        if( pRef == null ) {
                            this.errorFmt( pParent.getLineNo(), "name is not found. ref=" + pParent.strName);
                            return false;
                        }
                        if( pRef.getEType() != xsd.E_TYPE.ELEMENT ) {
                            this.errorFmt( pParent.getLineNo(), "reference item is not element. ref=" + pParent.strName);
                            return false;
                        }
                        if( pRef.getParent() != this ) {
                            // refは、schema直下のelementのみ指定可能
                            this.errorFmt( pParent.getLineNo(), "ref=" + pParent.strName + "  can specify only element immediately under schema.");
                            return false;
                        }
                        pParent.pRef = pRef;
                    }
                    // This...
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntChldren ) {
                        if( this.innerBuild( pParent.cntChldren[i] ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.strType.length != 0 ) {
                        var pType = this.innerBuildType(pParent, pParent.strType);
                        if( pType == null ) {
                            return false;
                        }
                        pParent.pType = pType;
                    }
                    if( pParent.strSubstitutionGroup.length != 0 ) {
                        var pRef = this.findByName( pParent.strSubstitutionGroup );
                        if( pRef == null ) {
                            this.errorFmt( pParent.getLineNo(), "name is not found. substitutionGroup=" + pParent.strSubstitutionGroup);
                            return false;
                        }
                        if( pRef.getEType() != xsd.E_TYPE.ELEMENT ) {
                            this.errorFmt( pParent.getLineNo(), "reference item is not element. substitutionGroup=" + pParent.strSubstitutionGroup);
                            return false;
                        }
                        pParent.pRef = pRef;
                    }
                }
                break;
            case xsd.E_TYPE.EXTESION:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                    //XsdBaseHasAttr
                    for(var i in pParent.cntAttribute ) {
                        if( this.innerBuild( pParent.cntAttribute[i] ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.anyAttribute != null ) {
                        if( this.innerBuild( pParent.anyAttribute ) == false ) {
                            return false;
                        }
                    }


                    // This...
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.strBase.length != 0 ) {

                        var pType = this.innerBuildType(pParent, pParent.strBase);
                        if( pType == null ) {
                            return false;
                        }
                        pParent.pBase = pType;

                    }
                }
                break;
            case xsd.E_TYPE.FIELD:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.GROUP:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.bIsRef == true ) {
                        
                        var pRef = this.findByName( pParent.strName );
                        if( pRef == null ) {
                            this.errorFmt( pParent.getLineNo(), "name is not found. ref=" + pParent.strName);
                            return false;
                        }
                        if( pRef.getEType() != xsd.E_TYPE.GROUP ) {
                            this.errorFmt( pParent.getLineNo(), "reference item is not group. ref=" + pParent.strName);
                            return false;
                        }
                        pParent.pRef = pRef;
                    }
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.IMPORT:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                }
                break;
            case xsd.E_TYPE.INCLUDE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                }
                break;
            case xsd.E_TYPE.KEY:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pSelector != null ) {
                        if( this.innerBuild( pParent.pSelector ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntField ) {
                        if( this.innerBuild( pParent.cntField[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.KEYREF:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pSelector != null ) {
                        if( this.innerBuild( pParent.pSelector ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntField ) {
                        if( this.innerBuild( pParent.cntField[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.LIST:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pSimpleType != null ) {
                        if( this.innerBuild( pParent.pSimpleType ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.strItemType.length != 0 ) {
                        
                        var pType = this.innerBuildType(pParent, pParent.strItemType);
                        if( pType == null ) {
                            return false;
                        }
                        pParent.pType = pType;
                    }
                }
                break;
            case xsd.E_TYPE.NOTION:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                }
                break;
            case xsd.E_TYPE.REDEFINE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    for(var i in pParent.cntChldren ) {
                        if( this.innerBuild( pParent.cntChldren[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.RESTRICTION:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pContent != null ) {
                        if( this.innerBuild( pParent.pContent ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntRestrictionVal ) {
                        if( this.innerBuild( pParent.cntRestrictionVal[i] ) == false ) {
                            return false;
                        }
                    }
                    if( pParent.strBaseName.length != 0 ) {
                        
                        var pType = this.innerBuildType(pParent, pParent.strBaseName);
                        if( pType == null ) {
                            return false;
                        }
                        pParent.pBaseType = pType;
                    }
                }
                break;
            case xsd.E_TYPE.RESTRICTION_VAL:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.SELECTOR:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.SEQUENCE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    for(var i in pParent.cntChldren ) {
                        if( this.innerBuild( pParent.cntChldren[i] ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.SIMPLE_CONTEXT:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.content != null ) {
                        if( this.innerBuild( pParent.content ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.SIMPLE_TYPE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    //print("simpleType " + pParent.content);
                    if( pParent.content != null ) {
                        if( this.innerBuild( pParent.content ) == false ) {
                            return false;
                        }
                    }
                }
                break;
            case xsd.E_TYPE.UNION:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    for(var i in pParent.cntSimpleType ) {
                        if( this.innerBuild( pParent.cntSimpleType[i] ) == false ) {
                            return false;
                        }
                    }

                    if( pParent.cntStrMemberTypes != null ) {
                        for(var i in pParent.cntStrMemberTypes ) {
                            
                            var pType = this.innerBuildType(pParent, pParent.cntStrMemberType[i]);
                            if( pType == null ) {
                                return false;
                            }
                            pParent.cntMemberType.push(pType);
                        }
                    }
                    
                }
                break;
            case xsd.E_TYPE.UNIQUE:
                {
                    //XsdBaseHasAnnotation
                    if( pParent.getAnnotation() != null ) {
                        if( this.innerBuild( pParent.getAnnotation() ) == false ) {
                            return false;
                        }
                    }

                    // This...
                    if( pParent.pSelector != null ) {
                        if( this.innerBuild( pParent.pSelector ) == false ) {
                            return false;
                        }
                    }
                    for(var i in pParent.cntField ) {
                        if( this.innerBuild( pParent.cntField[i] ) == false ) {
                            return false;
                        }
                    }
                    
                }
                break;
            default:                
                print("Break  ::::::" + pParent.getXmlTagName() );
                break;
        }
        return true;
    }

    //
    p.innerBuildType = function(pParent, strType) {
        var bIsXsdNs = false;

        var nsN = this.splitNs(strType);

        if( nsN.pNameSpace != null ) {
            if( nsN.pNameSpace.strURI == xsd.XSD_NAMESPACE_URI ) {
                bIsXsdNs = true;
            }
        }

        if( bIsXsdNs == true ) {

            var emType = XsdPrimitivType.prototype.getPrimitiveType( nsN.Val );
            if( emType == undefined ) {
                pParent.errFmt( pParent.getLineNo(), "invalid primitive type. " + nsN.Val);
                return null;
            }
            for( var i in this.mapStockPrimitives ) {
                if( this.mapStockPrimitives[i].emRType == emType ) {
                    return this.mapStockPrimitives[i];
                }
            }
            return null;
        } else {
            var pType = this.findByName( strType );
            if( pType == null ) {
                pParent.errFmt( pParent.getLineNo(), "name is not found. " + strType);
                return null;
            }
            return pType;
        }
        return null;
    }

    // 名前から、アイテムを検索
    p.findByName = function(name) {
        
        for(var i in this.cntAllObjs ) {
            var p = this.cntAllObjs[i];
            if( p.getName() == name ) {
                return p;
            }
        }
        return null;
    }
};





//-------------------------------------
//  XsdBaseHasAnnotation
//-------------------------------------
XsdBaseHasAnnotation: {
    function XsdBaseHasAnnotation(parent, ns) {
        XsdBase.call(this, parent, ns);

        this.annotation = null;
    }
    XsdBaseHasAnnotation.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdBaseHasAnnotation } });
    var p = XsdBaseHasAnnotation.prototype;

    // 
    p.getAnnotation = function() {
        return this.annotation;
    }
    //  overwrite...
    // 
    p.toString = function() {
        return this.getXmlTagName();
    }
    
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        // ベースクラスのチェック
        if(  XsdBase.prototype.validate.call(this) == false ) {
            bOk = false;
        }


        if( this.annotation != null ) {
            if( this.annotation.validate() == false ) {
                bOk = false;
            }
        }
        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBase.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "annotation") {
                    newVal = new XsdAnnotation(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                }
                this.annotation = newVal;
            }


        } catch (e) {
            throw e;
            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdBaseHasAttr
//-------------------------------------
XsdBaseHasAttr: {
    function XsdBaseHasAttr(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.cntAttribute = new Array();
        this.anyAttribute = null;
    }
    XsdBaseHasAttr.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdBaseHasAttr } });
    var p = XsdBaseHasAttr.prototype;

    //  overwrite...
    // 
    

    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBaseHasAnnotation.prototype.validate.call(this) == false ) {
            bOk = false;
        }
        if( this.anyAttribute != null ) {
            if( this.anyAttribute.validate() == false ) {
                bOk = false;
            }
        }
        for(var i in this.cntAttribute ) {
            if( this.cntAttribute[i].validate() == false ) {
                bOk = false;
            }
        }
        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "attribute") {
                    newVal = new XsdAttribute(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntAttribute.push(newVal);
                }
                else if (nsN.Val == "attributeGroup") {
                    newVal = new XsdAttributeGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntAttribute.push(newVal);
                }
                else if (nsN.Val == "anyAttribute") {
                    newVal = new XsdAnyAttribute(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    anyAttribute = newVal;
                }
            }
        } catch (e) {
            throw e;
            return false;
        }
        return true;
    }
};




//-------------------------------------
//  XsdAll
//-------------------------------------
XsdAll: {
    function XsdAll(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.ulMaxOccurs = 1;
        this.ulMinOccurs = 1;
        this.cntElemnt = new Array();
    }
    XsdAll.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdAll } });
    var p = XsdAll.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ALL;
    }
    p.getXmlTagName = function () {
        return "all";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBaseHasAnnotation.prototype.validate.call(this) == false ) {
            bOk = false;
        }
        /*
			maxOccurs 
			指定できる要素最大出現回数。値は 1 である必要があります。

			省略可能です。
		*/
        if( this.ulMaxOccurs != 1 ) {
            this.errorFmt( this.getLineNo(), "maxOccurs attribute is invalid value. must be 1.");
            bOk = false;
        }

        /*
			minOccurs 
			指定できる要素の最小出現回数。この値には、1 に等しい整数値を指定できます。この要素が省略可能であることを指定するには、この属性を 0 に設定します。既定値は 1 です。

			省略可能です。
		*/
        if( this.ulMinOccurs != 0 || this.ulMinOccurs != 1 ) {
            this.errorFmt( this.getLineNo(), "minOccurs attribute is invalid value. must be 0 or 1.");
            bOk = false;
        }


        // 以下、子要素をvalidate
        if( this.getAnnotation() != null ) {
            if( this.getAnnotation().validate() == false ) {
                bOk = false;
            }
        }
        for(var i in this.cntElemnt) {
            if( this.cntElemnt[i].validate() == false ) {
                bOk = false;
            }
        }
        return bOk;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "maxOccurs") {
                    if (attrs[attr] == "1") {
                        this.ulMaxOccurs = 1;
                    } else {
                        this.errFmt(this.getLineNo(),"invalid attribute value. maxOccurs=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    if (attrs[attr] == "0") {
                        this.ulMinOccurs = 0;
                    }
                    else if (attrs[attr] == "1") {
                        this.ulMinOccurs = 1;
                    } else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. maxOccurs=" + attrs[attr]);
                        return false;
                    }
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "element") {
                    newVal = new XsdElement(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntElemnt.push(newVal);
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};
//-------------------------------------
//  XsdAnnotation
//-------------------------------------
XsdAnnotation: {
    function XsdAnnotation(parent, ns) {
        XsdBase.call(this, parent, ns);
        this.super = XsdBase.prototype;

        this.cntChldren = new Array();
    }
    XsdAnnotation.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdAnnotation } });
    var p = XsdAnnotation.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ANNOTATION;
    }
    p.getXmlTagName = function () {
        return "annotation";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBase.prototype.validate.call(this) == false ) {
            bOk = false;
        }
        for(var i in this.cntChldren) {
            if( this.cntChldren[i].validate() == false ) {
                bOk = false;
            }
        }
        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBase.prototype.load.call(this, rootNode);

            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs( rootNode.elements[i].name);

                if (nsN.Val == "appinfo") {
                    newVal = new XsdAppinfo(this, nsN.pNameSpace);
                    if( newVal.load( rootNode.elements[i] ) == false ) {
                        newVal = null;
                    }
                } 
                else if (nsN.Val == "documentation") {
                    newVal = new XsdDocumentation(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                    }
                }

                if (newVal != null) {
                    this.cntChldren.push(newVal);
                }
            }
        } catch (e) {
            throw e;
            return false;
        }
        return true;
    }
};


//-------------------------------------
//  XsdAnyAttribute
//-------------------------------------
XsdAnyAttribute: {
    function XsdAnyAttribute(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.emNameSpace = xsd.ANY_NAMESPACE.ANY;
        this.emProcCont = xsd.ANY_PROC_CONT.STRICT;
    }
    XsdAnyAttribute.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdAnyAttribute } });
    var p = XsdAnyAttribute.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ANY_ATTRIBUTE;
    }
    p.getXmlTagName = function () {
        return "anyAttribute";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBaseHasAnnotation.prototype.validate.call(this) == false ) {
            bOk = false;
        }
        return bOk;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "namespace") {
                    if (attrs[attr] == "##any") {
                        this.emNameSpace = xsd.ANY_NAMESPACE.ANY;
                    }
                    else if (attrs[attr] == "##other") {
                        this.emNameSpace = xsd.ANY_NAMESPACE.OTHER;
                    }
                    else if (attrs[attr] == "##local") {
                        this.emNameSpace = xsd.ANY_NAMESPACE.LOCAL;
                    }
                    else if (attrs[attr] == "##targetNamespace") {
                        this.emNameSpace = xsd.ANY_NAMESPACE.TARGET_NAMESPACE;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. namespace=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "processContents") {
                    if (attrs[attr] == "strict") {
                        this.emProcCont = xsd.ANY_PROC_CONT.STRICT;
                    }
                    else if (attrs[attr] == "lax") {
                        this.emProcCont = xsd.ANY_PROC_CONT.LAX;
                    }
                    else if (attrs[attr] == "skip") {
                        this.emProcCont = xsd.ANY_PROC_CONT.SKIP;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. processContents=" + attrs[attr]);
                        return false;
                    }
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdAny
//-------------------------------------
XsdAny: {
    function XsdAny(parent, ns) {
        XsdAnyAttribute.call(this, parent, ns);

        this.ulMaxOccurs = 1;
        this.ulMinOccurs = 1;
    }
    XsdAny.prototype = Object.create(XsdAnyAttribute.prototype, { value: { constructor: XsdAny } });
    var p = XsdAny.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ANY;
    }
    p.getXmlTagName = function () {
        return "any";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdAnyAttribute.prototype.validate.call(this) == false ) {
            bOk = false;
        }

        /*
			maxOccurs 
			指定できる要素最大出現回数。値は 1 である必要があります。

			省略可能です。
		*/
        if( this.m_ulMinOccurs == -1 ) {
            this.errorFmt( this.getLineNo(), "minOccurs attribute is invalid value. do not specify unbounded.");
            bOk = false;
        }
        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdAnyAttribute.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "maxOccurs") {
                    if (attrs[attr] == "unbounded") {
                        this.ulMaxOccurs = -1;
                    }
                    else {
                        this.ulMaxOccurs = parseInt(attrs[attr]);
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    this.ulMinOccurs = parseInt(attrs[attr]);
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};


//-------------------------------------
//  XsdAppinfo
//-------------------------------------
XsdAppinfo: {
    function XsdAppinfo(parent, ns) {
        XsdBase.call(this, parent, ns);
        this.super = XsdBase.prototype;

        this.strSource = "";
        this.strDoc = "";
    }
    XsdAppinfo.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdAppinfo } });
    var p = XsdAppinfo.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.APPINFO;
    }
    p.getXmlTagName = function () {
        return "appinfo";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBase.prototype.validate.call(this) == false ) {
            bOk = false;
        }

        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;


            for (attr in attrs) {
                var nsN = this.splitNs( attr);
                if (nsN.Val == "source") {
                    this.strSource = attrs[attr];
                }
            }
            this.strDoc = rootNode.nodeContent;
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdAttribute
//-------------------------------------
XsdAttribute: {
    function XsdAttribute(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strDefault = "";
        this.strFixed = "";
        this.emForm = xsd.IS_QUALIFIED.QUALIFIED;
        this.strName = "";
        this.strRef = "";
        this.strType = "";
        this.emUse = xsd.EMUSE.OPTIONAL;
        this.pSimpleType = null;
        this.pRef = null;
        this.pType = null;
    }
    XsdAttribute.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdAttribute } });
    var p = XsdAttribute.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ATTRIBUTE;
    }
    p.getXmlTagName = function () {
        return "attribute";
    }
    p.toString = function() {
        var ret = this.getXmlTagName();
        ret += " : ";
        if( this.isRef() == true ) {
            ret += "r(";
            ret += this.strRef;
        } else {
            ret += "n(";
            ret += this.strName;
        }
        ret += ")";

        return ret;
    }
    p.getName = function()
    {
        return this.strName;
    }
    // 
    p.isRef = function() {
        if( this.pRef == null ) {
            return false;
        }
        return true;
    }
    
    //　データの妥当性をチェックします。
    p.validate = function() {
        var bOk = true;
        
        // ベースクラスのチェック
        if(  XsdBaseHasAnnotation.prototype.validate.call(this) == false ) {
            bOk = false;
        }

        // default 属性と fixed 属性の両方が存在することはできない         
        if( this.strDefault.length != 0 && this.strFixed.length != 0 ) {
            this.errorFmt( this.getLineNo(), "can not specify both the default attribute and the fixed attribute at the same time.");
            bOk = false;
        }

        if( this.pSimpleType != null ) {
            if( this.pSimpleType.validate() == false ) {
                bOk = false;
            }
        }


        return bOk;
    }
    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "default") {
                    this.strDefault = attrs[attr];
                }
                else if (nsN.Val == "fixed") {
                    this.strFixed = attrs[attr];
                }
                else if (nsN.Val == "form") {
                    if (attrs[attr] == "qualified") {
                        this.emForm = xsd.IS_QUALIFIED.QUALIFIED;
                    }
                    else if (attrs[attr] == "unqualified") {
                        this.emForm = xsd.IS_QUALIFIED.UNQUALIFIED;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. form=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "ref") {
                    this.strRef = attrs[attr];
                }
                else if (nsN.Val == "type") {
                    this.strType = attrs[attr];
                }
                else if (nsN.Val == "use") {
                    if (attrs[attr] == "optional") {
                        this.emUse = xsd.EMUSE.OPTIONAL;
                    }
                    else if (attrs[attr] == "prohibited") {
                        this.emUse = xsd.EMUSE.PROHIBITED;
                    }
                    else if (attrs[attr] == "required") {
                        this.emUse = xsd.EMUSE.REQUIRED;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. use=" + attrs[attr]);
                        return false;
                    }
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pSimpleType = newVal;
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdAttributeGroup
//-------------------------------------
XsdAttributeGroup: {
    function XsdAttributeGroup(parent, ns) {
        XsdBaseHasAttr.call(this, parent, ns);

        this.strName = "";
        this.strRef = "";
        this.pRef = null;
    }
    XsdAttributeGroup.prototype = Object.create(XsdBaseHasAttr.prototype, { value: { constructor: XsdAttributeGroup } });
    var p = XsdAttributeGroup.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ATTRIBUTE_GROUP;
    }
    p.getXmlTagName = function () {
        return "attributeGroup";
    }
    p.toString = function() {
        var ret = this.getXmlTagName();
        ret += " : ";
        if( this.isRef() == true ) {
            ret += "r(";
            ret += this.strRef;
        } else {
            ret += "n(";
            ret += this.strName;
        }
        ret += ")";

        return ret;
    }
    p.getName = function()
    {
        return this.strName;
    }
    p.isRef = function() 
    {
        if( this.pRef != null ) {
            return true;
        }
        return false;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAttr.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "ref") {
                    this.strRef = attrs[attr];
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdChoice
//-------------------------------------
XsdChoice: {
    function XsdChoice(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.ulMaxOccurs = -1;
        this.ulMinOccurs = 1;
        this.cntChldren = new Array();
    }
    XsdChoice.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdChoice } });
    var p = XsdChoice.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.CHOICE;
    }
    p.getXmlTagName = function () {
        return "choice";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "maxOccurs") {
                    if (attrs[attr] == "unbounded") {
                        this.ulMaxOccurs = -1;
                    } else {
                        this.ulMaxOccurs = parseInt(attrs[attr]);
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    if (attrs[attr] == "unbounded") {
                        this.ulMinOccurs = -1;
                    } else {
                        this.ulMinOccurs = parseInt(attrs[attr]);
                    }
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "element") {
                    newVal = new XsdElement(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push(newVal);
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push(newVal);
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push(pNewTarget);
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push(newVal);
                }
                else if (nsN.Val == "any") {
                    newVal = new XsdAny(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push(newVal);
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdComplexContent
//-------------------------------------
XsdComplexContent: {
    function XsdComplexContent(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.bMixed = false;

        this.pContent = null;
    }
    XsdComplexContent.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdComplexContent } });
    var p = XsdComplexContent.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.COMPLEX_CONTEXT;
    }
    p.getXmlTagName = function () {
        return "complexContent";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "mixed") {
                    if (attrs[attr] == "true") {
                        this.bMixed = true;
                    }
                    else if (attrs[attr] == "true") {
                        this.bMixed = false;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid atribute value. mixed=" + attrs[attr]);
                        return false;
                    }
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "restriction") {
                    newVal = new XsdRestriction(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "extension") {
                    newVal = new XsdExtension(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdComplexType
//-------------------------------------
XsdComplexType: {
    function XsdComplexType(parent, ns) {
        XsdBaseHasAttr.call(this, parent, ns);

        this.strName = "";
        this.bAbstruct = false;
        this.bMixed = false;
        this.ulBlock = 0;
        this.ulFinal = 0;

        this.pContent = null;
    }
    XsdComplexType.prototype = Object.create(XsdBaseHasAttr.prototype, { value: { constructor: XsdComplexType } });
    var p = XsdComplexType.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.COMPLEX_TYPE;
    }
    p.getXmlTagName = function () {
        return "complexType";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAttr.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "abstract") {
                    if (attrs[attr] == "true") {
                        this.bAbstruct = true;
                    }
                    else if (attrs[attr] == "true") {
                        this.bAbstruct = false;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid atribute value. abstract=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "mixed") {
                    if (attrs[attr] == "true") {
                        this.bMixed = true;
                    }
                    else if (attrs[attr] == "true") {
                        this.bMixed = false;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid atribute value. mixed=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "block") {
                    var ul = 0;
                    var arrayBlocks = attrs[attr].split(" ");
                    for (blc in arrayBlocks) {
                        if (arrayBlocks[blc] == "#all") {
                            ul |= xsd.BLOCK.ALL;
                        }
                        else if (arrayBlocks[blc] == "extension") {
                            ul |= xsd.BLOCK.EXTENSION;
                        }
                        else if (arrayBlocks[blc] == "restriction") {
                            ul |= xsd.BLOCK.RESTRICTION;
                        }
                        else if (arrayBlocks[blc] == "substitution") {
                            ul |= xsd.BLOCK.SUBSTITUTION;
                        }
                        else {
                            this.errFmt(this.getLineNo(), "invalid atribute value. block=" + arrayBlocks[blc]);
                            return false;
                        }
                    }
                    this.ulBlock = ul;
                }
                else if (nsN.Val == "final") {
                    var ul = 0;
                    var arrayBlocks = attrs[attr].split(" ");
                    for (blc in arrayBlocks) {
                        if (arrayBlocks[blc] == "#all") {
                            ul |= xsd.FINAL.ALL;
                        }
                        else if (arrayBlocks[blc] == "extension") {
                            ul |= xsd.FINAL.EXTENSION;
                        }
                        else if (arrayBlocks[blc] == "restriction") {
                            ul |= xsd.FINAL.RESTRICTION;
                        }
                        else {
                            this.errFmt(this.getLineNo(), "invalid atribute value. final=" + arrayBlocks[blc]);
                            return false;
                        }
                    }
                    this.ulFinal = ul;
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleContent") {
                    newVal = new XsdSimpleContent(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "complexContent") {
                    newVal = new XsdComplexContent(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "all") {
                    newVal = new XsdAll(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdDocumentation
//-------------------------------------
XsdDocumentation: {
    function XsdDocumentation(parent, ns) {
        XsdBase.call(this, parent, ns);
        this.super = XsdBase.prototype;

        this.strSource = "";
        this.strLang = "";
        this.strDoc = "";
    }
    XsdDocumentation.prototype = Object.create(XsdBase.prototype, { value: { constructor: XsdDocumentation } });
    var p = XsdDocumentation.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.DOCUMENTATION;
    }
    p.getXmlTagName = function () {
        return "documentation";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;


            for (attr in attrs) {
                var nsN = this.splitNs( attr);
                if (nsN.Val == "source") {
                    this.strSource = attrs[attr];
                }
                else if (nsN.Val == "xml:lang") {
                    this.strLang = attrs[attr];
                }
            }
            this.strDoc = rootNode.nodeContent;
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdElement
//-------------------------------------
XsdElement: {
    function XsdElement(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

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
    }
    XsdElement.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdElement } });
    var p = XsdElement.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.ELEMENT;
    }
    p.getXmlTagName = function () {
        return "element";
    }
    p.toString = function() {
        var ret = this.getXmlTagName();
        ret += " : ";
        if( this.isRef() == true ) {
            ret += "r(";
            ret += this.strName;
        } else {
            ret += "n(";
            ret += this.strName;
        }
        ret += ")";
        return ret;
    }
    p.getName = function()
    {
        return this.strName;
    }
    p.isRef = function() {
        if( this.pRef == null ) {
            return false;
        }
        return true;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                

                if (nsN.Val == "abstract") {
                    if (attrs[attr] == "true") {
                        this.bAbstruct = true;
                    }
                    else if (attrs[attr] == "true") {
                        this.bAbstruct = false;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid atribute value. abstract=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "block") {
                    var ul = 0;
                    var arrayBlocks = attrs[attr].split(" ");
                    for (blc in arrayBlocks) {
                        if (arrayBlocks[blc] == "#all") {
                            ul |= xsd.BLOCK.ALL;
                        }
                        else if (arrayBlocks[blc] == "extension") {
                            ul |= xsd.BLOCK.EXTENSION;
                        }
                        else if (arrayBlocks[blc] == "restriction") {
                            ul |= xsd.BLOCK.RESTRICTION;
                        }
                        else if (arrayBlocks[blc] == "substitution") {
                            ul |= xsd.BLOCK.SUBSTITUTION;
                        }
                        else {
                            this.errFmt(this.getLineNo(), "invalid atribute value. block=" + arrayBlocks[blc]);
                            return false;
                        }
                    }
                    this.ulBlock = ul;
                }
                else if (nsN.Val == "default") {
                    this.strDefault = attrs[attr];
                }
                else if (nsN.Val == "final") {
                    var ul = 0;
                    var arrayBlocks = attrs[attr].split(" ");
                    for (blc in arrayBlocks) {
                        if (arrayBlocks[blc] == "#all") {
                            ul |= xsd.FINAL.ALL;
                        }
                        else if (arrayBlocks[blc] == "extension") {
                            ul |= xsd.FINAL.EXTENSION;
                        }
                        else if (arrayBlocks[blc] == "restriction") {
                            ul |= xsd.FINAL.RESTRICTION;
                        }
                        else {
                            this.errFmt(this.getLineNo(), "invalid atribute value. final=" + arrayBlocks[blc]);
                            return false;
                        }
                    }
                    this.ulFinal = ul;
                }
                else if (nsN.Val == "fixed") {
                    this.strFixed = attrs[attr];
                }
                else if (nsN.Val == "form") {
                    if (attrs[attr] == "qualified") {
                        this.emForm = xsd.IS_QUALIFIED.QUALIFIED;
                    }
                    else if (attrs[attr] == "unqualified") {
                        this.emForm = xsd.IS_QUALIFIED.UNQUALIFIED;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid attribute value. form=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "maxOccurs") {
                    if (attrs[attr] == "unbounded") {
                        this.ulMaxOccurs = -1;
                    }
                    else {
                        this.ulMaxOccurs = parseInt(attrs[attr]);
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    this.ulMinOccurs = parseInt(attrs[attr]);
                }
                else if (nsN.Val == "name") {
                    this.bIsRef = false;
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "nillable") {
                    if (attrs[attr] == "true") {
                        this.bNillable = true;
                    }
                    else if (attrs[attr] == "true") {
                        this.bNillable = false;
                    }
                    else {
                        this.errFmt(this.getLineNo(), "invalid atribute value. nillable=" + attrs[attr]);
                        return false;
                    }
                }
                else if (nsN.Val == "ref") {
                    this.bIsRef = true;
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "substitutionGroup") {
                    this.pSubstitutionGroup = attrs[attr];
                }
                else if (nsN.Val == "type") {
                    this.strType = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "complexType") {
                    newVal = new XsdComplexType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                } else {
                    if (nsN.Val == "unique") {
                        newVal = new XsdUnique(this, nsN.pNameSpace);
                    }
                    else if (nsN.Val == "key") {
                        newVal = new XsdKey(this, nsN.pNameSpace);
                    }
                    else if (nsN.Val == "keyref") {
                        newVal = new XsdKeyref(this, nsN.pNameSpace);
                    }
                    if (newVal != null) {
                        if (newVal.load(rootNode.elements[i]) == false) {
                            newVal = null;
                            return false;
                        }
                        this.cntChldren.push(newVal);
                    }
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
    // タイプを変更
    p.changeType = function (strType) {
        var pSchema = this.getParentByType(xsd.E_TYPE.SCHEMA);
        // 空文字の場合はクリア
        if( strType.length == 0 ) {
            this.strType = "";
            this.pType = null;
        }
        if( pSchema == null ) {
            throw "fail to get schema object.";
            return false;
        }
        var pType = pSchema.innerBuildType(this, strType);
        if( pType == null ) {
            return false;
        }
        this.strType = strType;
        this.pType = pType;
        return true;
    }
};

//-------------------------------------
//  XsdExtension
//-------------------------------------
XsdExtension: {
    function XsdExtension(parent, ns) {
        XsdBaseHasAttr.call(this, parent, ns);
        this.super = XsdBaseHasAttr.prototype;

        this.strBase = "";
        this.pBase = null;
        this.pContent = null;
    }
    XsdExtension.prototype = Object.create(XsdBaseHasAttr.prototype, { value: { constructor: XsdExtension } });
    var p = XsdExtension.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.EXTESION;
    }
    p.getXmlTagName = function () {
        return "extension";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAttr.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "base") {
                    this.strBase = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "all") {
                    newVal = new XsdAll(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                }

                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};


//-------------------------------------
//  XsdField
//-------------------------------------
XsdField: {
    function XsdField(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strXath = "";
    }
    XsdField.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdField } });
    var p = XsdField.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.FIELD;
    }
    p.getXmlTagName = function () {
        return "field";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "xpath") {
                    this.strXath = attrs[attr];
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdGroup
//-------------------------------------
XsdGroup: {
    function XsdGroup(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strName = "";
        this.ulMaxOccurs = 1;
        this.ulMinOccurs = 1;
        this.pContent = null;
        this.pRef = null;
        this.bIsRef = false;
    }
    XsdGroup.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdGroup } });


    var p = XsdGroup.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.GROUP;
    }
    p.getXmlTagName = function () {
        return "group";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.bIsRef = false;
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "ref") {
                    this.bIsRef = true;
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "maxOccurs") {
                    if (attrs[attr] == "unbounded") {
                        this.ulMaxOccurs = -1;
                    } else {
                        this.ulMaxOccurs = parseInt(attrs[attr]);
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    this.ulMinOccurs = parseInt(attrs[attr]);
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "all") {
                    newVal = new XsdAll(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                }

                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdImport
//-------------------------------------
XsdImport: {
    function XsdImport(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strNamespace = "";
        this.strSchemaLocation = "";
    }
    XsdImport.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdImport } });


    var p = XsdImport.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.IMPORT;
    }
    p.getXmlTagName = function () {
        return "import";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "namespace") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "schemaLocation") {
                    this.strSchemaLocation = attrs[attr];
                }
            }


            //for (i in rootNode.elements) {
            //    var newVal = null;
            //    var nsN = this.splitNs(rootNode.elements[i].name);

            //    if (nsN.Val == "all") {
            //        newVal = new XsdAll(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //            return false;
            //        }
            //        this.pContent = newVal;
            //    }
            //    else if (nsN.Val == "choice") {
            //        newVal = new XsdChoice(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //            return false;
            //        }
            //        this.pContent = newVal;
            //    }
            //    else if (nsN.Val == "sequence") {
            //        newVal = new XsdSequence(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //        }
            //    }
            //    this.content = newVal;
            //}


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdInclude
//-------------------------------------
XsdInclude: {
    function XsdInclude(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strSchemaLocation = "";
    }
    XsdInclude.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdInclude } });


    var p = XsdInclude.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.INCLUDE;
    }
    p.getXmlTagName = function () {
        return "include";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "schemaLocation") {
                    this.strSchemaLocation = attrs[attr];
                }
            }


            //for (i in rootNode.elements) {
            //    var newVal = null;
            //    var nsN = this.splitNs(rootNode.elements[i].name);

            //    if (nsN.Val == "all") {
            //        newVal = new XsdAll(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //            return false;
            //        }
            //        this.pContent = newVal;
            //    }
            //    else if (nsN.Val == "choice") {
            //        newVal = new XsdChoice(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //            return false;
            //        }
            //        this.pContent = newVal;
            //    }
            //    else if (nsN.Val == "sequence") {
            //        newVal = new XsdSequence(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //        }
            //    }
            //    this.content = newVal;
            //}


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdKey
//-------------------------------------
XsdKey: {
    function XsdKey(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strName = "";
        this.pSelector = "";
        this.cntField = new Array();
    }
    XsdKey.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdKey } });


    var p = XsdKey.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.KEY;
    }
    p.getXmlTagName = function () {
        return "key";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "selector") {
                    newVal = new XsdSelector(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pSelector = newVal;
                }
                else if (nsN.Val == "field") {
                    newVal = new XsdField(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntField.push(newVal);
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdKeyref
//-------------------------------------
XsdKeyref: {
    function XsdKeyref(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strName = "";
        this.strRefer = "";
        this.pSelector = "";
        this.cntField = new Array();
    }
    XsdKeyref.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdKeyref } });


    var p = XsdKeyref.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.KEYREF;
    }
    p.getXmlTagName = function () {
        return "keyref";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "refer") {
                    this.strRefer = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "selector") {
                    newVal = new XsdSelector(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pSelector = newVal;
                }
                else if (nsN.Val == "field") {
                    newVal = new XsdField(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntField.push(newVal);
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdList
//-------------------------------------
XsdList: {
    function XsdList(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strID = "";
        this.strItemType = "";
        this.pSimpleType = NULL;
        this.pType = NULL;
    }
    XsdList.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdList } });


    var p = XsdList.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.LIST;
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getXmlTagName = function () {
        return "list";
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "id") {
                    this.strID = attrs[attr];
                }
                else if (nsN.Val == "itemType") {
                    this.strItemType = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pSimpleType = newVal;
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



//-------------------------------------
//  XsdNotation
//-------------------------------------
XsdNotation: {
    function XsdNotation(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strName = "";
        this.strPublic = "";
        this.strSystem = "";
    }
    XsdNotation.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdNotation } });
    var p = XsdNotation.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.NOTION;
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getXmlTagName = function () {
        return "notation";
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
                else if (nsN.Val == "public") {
                    this.strPublic = attrs[attr];
                }
                else if (nsN.Val == "public") {
                    this.strSystem = attrs[attr];
                }
            }


            //for (i in rootNode.elements) {
            //    var newVal = null;
            //    var nsN = this.splitNs(rootNode.elements[i].name);

            //    if (nsN.Val == "simpleType") {
            //        newVal = new XsdSimpleType(this, null);
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //            return false;
            //        }
            //        this.pSimpleType = newVal;
            //    }
            //}


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};



/*
*/
//-------------------------------------
//  XsdRedefine
//-------------------------------------
XsdRedefine: {
    function XsdRedefine(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);

        this.strSchemaLocation = "";
        this.cntChldren = new Array();
    }
    XsdRedefine.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdRedefine } });
    var p = XsdRedefine.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.REDEFINE;
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getXmlTagName = function () {
        return "redefine";
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "schemaLocation") {
                    this.strSchemaLocation = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "complexType") {
                    newVal = new XsdComplexType(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "attributeGroup") {
                    newVal = new XsdAttributeGroup(this, nsN.pNameSpace);
                }

                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push( newVal );
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};




/*
|制約          |説明                                                                               
|--------------|-----------------------------------------------------------------------------------
|enumeration   |許容値のリストを定義します                                                         
|fractionDigits|小数点以下の最大桁数を指定します。ゼロ以上でなければなりません。                   
|length        |許容する文字数やリスト項目数を正確に指定します。ゼロ以上でなければなりません       
|maxExclusive  |数値の上限を指定します（値はこの値より小(<)でなければなりません）                  
|maxInclusive  |数値の上限を指定します（値はこの値以下でなければなりません）                       
|maxLength     |許容する文字数やリスト項目数の最大値を指定します。     ゼロ以上でなければなりません
|minExclusive  |数値の下限を指定します（値はこの値より大(>)でなければなりません）                  
|minInclusive  |数値の下限を指定します（値はこの値以上でなければなりません）                       
|minLength     |許容する文字数やリスト項目数の最小値を指定します。     ゼロ以上でなければなりません
|pattern       |許容される文字の正確なシーケンスを定義します                                       
|totalDigits   |許容される最大桁数を指定します。ゼロより大(>)でなければなりません                  
|whiteSpace    |空白（改行、タブ、スペース、およびキャリッジリターン）の処理方法を指定します       

*/
//-------------------------------------
//  XsdRestrictionVal
//-------------------------------------
XsdRestrictionVal: {
    function XsdRestrictionVal(parent, ns, emRType) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.emRType = emRType;
        this.strValue = "";
    }
    XsdRestrictionVal.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdRestrictionVal } });


    var p = XsdRestrictionVal.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.RESTRICTION_VAL;
    }
    p.getXmlTagName = function () {

        switch( this.emRType )  {
            case xsd.R_TYPE.EMUERATION:
                return "enumeration";
                break;
            case xsd.R_TYPE.FRACTION_DIGITS:
                return "fractionDigits";
                break;
            case xsd.R_TYPE.LENGTH:
                return "length";
                break;
            case xsd.R_TYPE.MAX_LENGTH:
                return "maxLength";
                break;
            case xsd.R_TYPE.MIN_LENGTH:
                return "minLength";
                break;
            case xsd.R_TYPE.MAX_EXCLUSIVE:
                return "maxExclusive";
                break;
            case xsd.R_TYPE.MAX_INCLUSIVE:
                return "maxInclusive";
                break;
            case xsd.R_TYPE.MIN_EXCLUSIVE:
                return "minExclusive";
                break;
            case xsd.R_TYPE.MIN_INCLUSIVE:
                return "minInclusive";
                break;
            case xsd.R_TYPE.PATTERN:
                return "pattern";
                break;
            case xsd.R_TYPE.TOTAL_DIGITS:
                return "totalDigits";
                break;
            case xsd.R_TYPE.WHITE_SPACE:
                return "whiteSpace";
                break;
        }
        return "";
    }
    p.toString = function() {
        var ret = this.getXmlTagName();
        if( this.strValue.length != 0 ) {
            ret += " (";
            ret += this.strValue;
            ret += ")";
        }
        return ret;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "value") {
                    this.strValue = attrs[attr];
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdRestriction
//-------------------------------------
XsdRestriction: {
    function XsdRestriction(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strBaseName = "";
        this.cntRestrictionVal = new Array();
        this.pContent = null;
        this.pBaseType = null;
    }
    XsdRestriction.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdRestriction } });


    var p = XsdRestriction.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.RESTRICTION;
    }
    p.getXmlTagName = function () {
        return "restriction";
    }
    p.toString = function() {
        var ret = this.getXmlTagName();
        if( this.strBaseName.length != 0 ) {
            ret += " (";
            ret += this.strBaseName;
            ret += ")";
        }
        return ret;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "base") {
                    this.strBaseName = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                       newVal = null;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "all") {
                    newVal = new XsdAll(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                       newVal = null;
                    }
                    this.pContent = newVal;
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                    }
                    this.pContent = newVal;
                } else {
                    if (nsN.Val == "enumeration") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.EMUERATION);
                    }
                    else if (nsN.Val == "fractionDigits") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.FRACTION_DIGITS);
                    }
                    else if (nsN.Val == "length") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.LENGTH);
                    }
                    else if (nsN.Val == "maxExclusive") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MAX_EXCLUSIVE);
                    }
                    else if (nsN.Val == "maxInclusive") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MAX_INCLUSIVE);
                    }
                    else if (nsN.Val == "maxLength") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MAX_LENGTH);
                    }
                    else if (nsN.Val == "minExclusive") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MIN_EXCLUSIVE);
                    }
                    else if (nsN.Val == "minInclusive") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MIN_INCLUSIVE);
                    }
                    else if (nsN.Val == "minLength") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.MIN_LENGTH);
                    }
                    else if (nsN.Val == "pattern") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.PATTERN);
                    }
                    else if (nsN.Val == "totalDigits") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.TOTAL_DIGITS);
                    }
                    else if (nsN.Val == "whiteSpace") {
                        newVal = new XsdRestrictionVal(this, nsN.pNameSpace, xsd.R_TYPE.WHITE_SPACE);
                    }

                    if( newVal != null ) {
                        if (newVal.load(rootNode.elements[i]) == false) {
                            newVal = null;
                            return false;
                        }
                        this.cntRestrictionVal.push(newVal);
                    }
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};





//-------------------------------------
//  XsdSelector
//-------------------------------------
XsdSelector: {
    function XsdSelector(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strXath = "";
    }
    XsdSelector.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdSelector } });


    var p = XsdSelector.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.SELECTOR;
    }
    p.getXmlTagName = function () {
        return "selector";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "xpath") {
                    this.strXath = attrs[attr];
                }
            }


            //for (i in rootNode.elements) {
            //    var newVal = null;
            //    var nsN = this.splitNs(rootNode.elements[i].name);

            //    if (nsN.Val == "restriction") {
            //        newVal = new XsdRestriction(this, null);
            //    }
            //    else if (nsN.Val == "list") {
            //        newVal = new XsdList(this, null);
            //    }
            //    else if (nsN.Val == "union") {
            //        newVal = new XsdUnion(this, null);
            //    }


            //    if( newVal != null ) {
            //        if (newVal.load(rootNode.elements[i])) {
            //            newVal = null;
            //        }
            //        this.content = newVal;
            //    }
            //}


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};





//-------------------------------------
//  XsdSequence
//-------------------------------------
XsdSequence: {
    function XsdSequence(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;
        
        this.ulMaxOccurs = 1;
        this.ulMinOccurs = 1;
        this.cntChldren = new Array();
    }
    XsdSequence.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdSequence } });
    var p = XsdSequence.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.SEQUENCE;
    }
    p.getXmlTagName = function () {
        return "sequence";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);

                if (nsN.Val == "maxOccurs") {
                    if( attrs[attr] == "unbounded" ) {
                        this.ulMaxOccurs = -1;
                    } else {
                        this.ulMaxOccurs = parseInt(attrs[attr]);
                    }
                }
                else if (nsN.Val == "minOccurs") {
                    this.ulMinOccurs = parseInt(attrs[attr]);
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "element") {
                    newVal = new XsdElement(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "group") {
                    newVal = new XsdGroup(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "choice") {
                    newVal = new XsdChoice(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "sequence") {
                    newVal = new XsdSequence(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "any") {
                    newVal = new XsdAny(this, nsN.pNameSpace);
                }


                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntChldren.push( newVal );
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};





//-------------------------------------
//  XsdSimpleContent
//-------------------------------------
XsdSimpleContent: {
    function XsdSimpleContent(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.content = null;
    }
    XsdSimpleContent.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdSimpleContent } });


    var p = XsdSimpleContent.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.SIMPLE_CONTEXT;
    }
    p.getXmlTagName = function () {
        return "simpleContent";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "xpath") {
                    this.strXath = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "restriction") {
                    newVal = new XsdRestriction(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "extension") {
                    newVal = new XsdExtension(this, nsN.pNameSpace);
                }


                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.content = newVal;
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};

//-------------------------------------
//  XsdSimpleType
//-------------------------------------
XsdSimpleType: {
    function XsdSimpleType(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strName = "";
        this.content = null;
    }
    XsdSimpleType.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdSimpleType } });


    var p = XsdSimpleType.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.SIMPLE_TYPE;
    }
    p.getXmlTagName = function () {
        return "simpleType";
    }
    p.toString = function() {
        ret = this.getXmlTagName();

        if( this.strName.length != 0 ) {
            ret += " (";
            ret += this.strName;
            ret += ")";
        }

        return ret;
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            this.super.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    this.strName = attrs[attr];
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "restriction") {
                    newVal = new XsdRestriction(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "list") {
                    newVal = new XsdList(this, nsN.pNameSpace);
                }
                else if (nsN.Val == "union") {
                    newVal = new XsdUnion(this, nsN.pNameSpace);
                }


                if( newVal != null ) {
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.content = newVal;
                }
            }


        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};


//-------------------------------------
//  XsdUnion
//-------------------------------------
XsdUnion: {
    function XsdUnion(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strID = null;
        this.cntSimpleType = new Array();
        this.cntMemberType = new Array();
        this.cntStrMemberTypes = null;
    }
    XsdUnion.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdUnion } });
    var p = XsdUnion.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.UNION;
    }
    p.getXmlTagName = function () {
        return "union";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "id") {
                    vthis.strID = attrs[attr];
                }
                else if (nsN.Val == "memberTypes") {
                    var strMemberTypes = "" + attrs[attr];
                    this.cntStrMemberTypes = strMemberTypes.split(" ");
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "simpleType") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntSimpleType.push(newVal);
                }
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};


//-------------------------------------
//  XsdUnique
//-------------------------------------
XsdUnique: {
    function XsdUnique(parent, ns) {
        XsdBaseHasAnnotation.call(this, parent, ns);
        this.super = XsdBaseHasAnnotation.prototype;

        this.strName = null;
        this.cntField = new Array();
        this.pSelector  = null;
    }
    XsdUnique.prototype = Object.create(XsdBaseHasAnnotation.prototype, { value: { constructor: XsdUnique } });
    var p = XsdUnique.prototype;

    //  overwrite...
    // 
    p.getEType = function () {
        return xsd.E_TYPE.UNION;
    }
    p.getXmlTagName = function () {
        return "union";
    }
    p.toString = function() {
        return this.getXmlTagName();
    }
    p.getName = function()
    {
        return this.strName;
    }

    // XMLノードから、データをロードします。
    p.load = function (rootNode) {
        try {
            XsdBaseHasAnnotation.prototype.load.call(this, rootNode);

            var attrs = rootNode.attrs;
            for (attr in attrs) {
                var nsN = this.splitNs(attr);
                if (nsN.Val == "name") {
                    vthis.strID = attrs[attr];
                }
                else if (nsN.Val == "memberTypes") {
                    var strMemberTypes = "" + attrs[attr];
                    this.cntStrMemberTypes = strMemberTypes.split(" ");
                }
            }


            for (i in rootNode.elements) {
                var newVal = null;
                var nsN = this.splitNs(rootNode.elements[i].name);

                if (nsN.Val == "selector") {
                    newVal = new XsdSimpleType(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.pSelector  = newVal;
                }
                else if (nsN.Val == "field") {
                    newVal = new XsdField(this, nsN.pNameSpace);
                    if (newVal.load(rootNode.elements[i]) == false) {
                        newVal = null;
                        return false;
                    }
                    this.cntField.push_back(newVal);
                }

                
            }
        } catch (e) {
            throw e;

            return false;
        }
        return true;
    }
};
