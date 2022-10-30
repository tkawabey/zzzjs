// This example shows how easy it is, to create an 
// application for managing a database.

var MENU_FILE_CLOSE    = 1;
var MENU_PERSON_ADD    = 2;
var MENU_PERSON_REMOVE = 3;

var listCtrl;

function menuFileClose()
{
  this.close();
}

function menuPersonAdd()
{
  var dlg = new wxDialog(wxTheApp.topWindow, -1, "Add a new person", wxDefaultPosition, new wxSize(200, 150));
  
  dlg.sizer = new wxFlexGridSizer(3, 2, 10, 10);
  dlg.sizer.add(new wxStaticText(dlg, -1, "Firstname"));
  dlg.sizer.add(new wxTextCtrl(dlg, -1, ""));
  dlg.sizer.add(new wxStaticText(dlg, -1, "Lastname"));
  dlg.sizer.add(new wxTextCtrl(dlg, -1, ""));
  dlg.sizer.add(new wxButton(dlg, wxId.OK, "Ok"));
  dlg.sizer.add(new wxButton(dlg, wxId.CANCEL, "Cancel"));
  dlg.autoLayout = true;
  dlg.layout();
  dlg.showModal();
}

function menuPersonRemove()
{
}

var db = new sqlite.Database(script.root + "/person.db");

function initApp()
{
  // Check if the database is opened for the first time
  var pragmaStmt = db.prepare("PRAGMA user_version");
  var pragma = pragmaStmt.fetchArray();
  if ( pragma[0] == 0 )
  {
    // Create the database
    db.exec("CREATE TABLE person(id INTEGER PRIMARY KEY, firstname TEXT, lastname TEXT)");
    db.exec("PRAGMA user_version = 1");
  }

  var frame = new wxFrame(null, -1, "Editing the person database");
  topWindow = frame;
  
  var menuBar = new wxMenuBar();
  frame.menuBar = menuBar;
  
  var menu = new wxMenu();
  menu.append(MENU_FILE_CLOSE, "Close", menuFileClose, "Close the application");
  menuBar.append(menu, "File");
  
  menu = new wxMenu();
  menu.append(MENU_PERSON_ADD, "Add", menuPersonAdd, "Add a new person");
  menu.append(MENU_PERSON_REMOVE, "Remove", menuPersonRemove, "Remove a person");
  menuBar.append(menu, "Person");

  listCtrl = new wxListCtrl(frame, -1, wxDefaultPosition,
                                wxDefaultSize, wxListCtrl.REPORT);
  listCtrl.insertColumn(0, "Id");
  listCtrl.insertColumn(1, "Firstname");
  listCtrl.insertColumn(2, "Lastname");

  var stmt = db.prepare("SELECT * FROM person");
  var row;
  while(row = stmt.fetchObject())
  {
    var index = listCtrl.insertItem(0, row.id);
    listCtrl.setItemData(index, row.id);
    listCtrl.setItem(index, 1, row.firstname);
    listCtrl.setItem(index, 2, row.lastname);
  }
 
  frame.show();
  
  return true;
}

wxTheApp.onInit = initApp;
