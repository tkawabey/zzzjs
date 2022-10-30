var db = new sqlite.Database("c:\\temp\\test.db");
if ( db.opened )
{
  print("Open success: ");
  print(db.exec("CREATE TABLE person(name TEXT, nr INTEGER)"));
  print(db.exec("INSERT INTO person(name, nr) VALUES('Franky', 10)"));
}
else
{
  print("Open failed");
}
