// JavaScript Document
var db = new sqlite.Database("c:\\temp\\test.db");
var stmt = db.prepare("SELECT * FROM person");
var row;
while(row = stmt.fetchObject())
{
  print(row.name);
  print(row.nr);
}
