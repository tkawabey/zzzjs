// Constructor for a XMLElement object
function Element(parent, name, attrs) {
    this.parent = parent;
    if (parent != null)
        parent.elements[parent.elements.length + 1] = this;
    this.name = name;
    this.attrs = attrs;
    this.elements = new Array();
}


function parseXMLFile(filename) {
    var p = new expat.Parser("UTF-8");
    p.currentElement = null;

    p.onStartElement = function (element, attrs) {
        this.currentElement = new Element(this.currentElement, element, attrs);
    }

    p.onEndElement = function (element) {
        this.currentElement.data = this.characters;
        if (this.currentElement.parent != null)
            this.currentElement = this.currentElement.parent;
    }

    p.onCharacter = function (data) {
        this.currentElement.data = data;
    }

    var file = new wx.File(filename);
    var readCount = 0;

    while (!file.eof) {
        var s = file.read(255);
        if (p.parse(s, file.eof) == expat.Parser.XML_STATUS_ERROR) {
            break;
        }
    }
    return p.currentElement;
}
