// Constructor for a XMLElement object
function Element(parent, name, attrs)
{
  this.parent = parent;
  if ( parent != null )
    parent.elements[parent.elements.length + 1] = this;
  this.name = name;
  this.attrs = attrs;
  this.elements = new Array();
}
