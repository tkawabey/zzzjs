/*
 * wxJavaScript - db.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: db.cpp 713 2007-05-14 21:15:48Z fbraem $
 */
#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"



#include "js/sqlite/db.h"
#include "js/sqlite/stmt.h"
#include "js/common/jsutil.h"

using namespace zzzJs::sqlite;

Database::Database(JSContext *cx, JSObject *obj) 
         : JavaScriptClientData(cx, obj ,false, true)
         , wxObject()
{
  DatabaseRefData *data = new DatabaseRefData();
  SetRefData(data);
}

int Database::CommitHook(void *arg)
{
    Database *db = (Database *) arg;
    jsval rval;
    CallFunctionProperty(db->GetContext(), db->GetObject(), "onCommit",
                              0, NULL, &rval);
    int rc;
    if ( FromJS(db->GetContext(), rval, rc) )
    {
        return rc;
    }

    return 1;
}

void Database::RollbackHook(void *arg)
{
    Database *db = (Database *) arg;
    jsval rval;
    CallFunctionProperty(db->GetContext(), db->GetObject(), "onRollback",
                              0, NULL, &rval);
}

void Database::Trace(void *arg, const char *SQL)
{
    Database *db = (Database *) arg;
    jsval rval;
    wxMBConvUTF16 conv;
    jsval argv[] = { ToJS(db->GetContext(), wxString(SQL, conv)) };
    CallFunctionProperty(db->GetContext(), db->GetObject(), "onTrace",
                              1, argv, &rval);
}

void Database::Update(void *arg ,int type, char const *dbname,char const *tbname,sqlite_int64 rowid)
{
    Database *db = (Database *) arg;
    jsval rval;
    wxMBConvUTF16 conv;
    jsval argv[] = { 
                     ToJS(db->GetContext(), type),
                     ToJS(db->GetContext(), wxString(dbname, conv)),
                     ToJS(db->GetContext(), wxString(tbname, conv)),
                     ToJS<double>(db->GetContext(), rowid)
                   };
    CallFunctionProperty(db->GetContext(), db->GetObject(), "onUpdate",
                              4, argv, &rval);
}

/***
 * <module>sqlite</module>
 * <file>db</file>
 * <class name="sqlite.Database">
 *  Implements a sqlite database
 * </class>
 */
WXJS_INIT_CLASS(Database, "Database", 1)

/***
 * <constants>
 *  <type>
 *   <constant name="OK">Successful result</constant>
 *   <constant name="ERROR">SQL error or missing database</constant>
 *   <constant name="INTERNAL">An internal logic error in SQLite</constant>
 *   <constant name="PERM">Access permission denied</constant>
 *   <constant name="ABORT">Callback routine requested an abort</constant>
 *   <constant name="BUSY">The database file is locked</constant>
 *   <constant name="LOCKED">A table in the database is locked</constant>
 *   <constant name="NOMEM">A malloc() failed</constant>
 *   <constant name="READONLY">Attempt to write a readonly database</constant>
 *   <constant name="INTERRUPT">Operation terminated by sqlite_interrupt()</constant>
 *   <constant name="IOERR">Some kind of disk I/O error occurred</constant>
 *   <constant name="CORRUPT">The database disk image is malformed</constant>
 *   <constant name="NOTFOUND">(Internal Only) Table or record not found</constant>
 *   <constant name="FULL">Insertion failed because database is full</constant>
 *   <constant name="CANTOPEN">Unable to open the database file</constant>
 *   <constant name="PROTOCOL">Database lock protocol error</constant>
 *   <constant name="EMPTY">(Internal Only) Database table is empty</constant>
 *   <constant name="SCHEMA">The database schema changed</constant>
 *   <constant name="TOOBIG">Too much data for one row of a table</constant>
 *   <constant name="CONSTRAINT">Abort due to constraint violation</constant>
 *   <constant name="MISMATCH">Data type mismatch</constant>
 *   <constant name="MISUSE">Library used incorrectly</constant>
 *   <constant name="NOLFS">Uses OS features not supported on host</constant>
 *   <constant name="AUTH">Authorization denied</constant>
 *   <constant name="ROW">@sqlite.Database#step has another row ready</constant>
 *   <constant name="DONE">@sqlite.Database#step has finished executing</constant>
 *   <constant name="DENY" />
 *   <constant name="INSERT" />
 *   <constant name="DELETE" />
 *   <constant name="UPDATE" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Database)
    WXJS_CONSTANT(SQLITE_, OK)           /* Successful result */
    WXJS_CONSTANT(SQLITE_, ERROR)        /* SQL error or missing database */
    WXJS_CONSTANT(SQLITE_, INTERNAL)     /* An internal logic error in SQLite */
    WXJS_CONSTANT(SQLITE_, PERM)         /* Access permission denied */
    WXJS_CONSTANT(SQLITE_, ABORT)        /* Callback routine requested an abort */
    WXJS_CONSTANT(SQLITE_, BUSY)         /* The database file is locked */
    WXJS_CONSTANT(SQLITE_, LOCKED)       /* A table in the database is locked */
    WXJS_CONSTANT(SQLITE_, NOMEM)        /* A malloc() failed */
    WXJS_CONSTANT(SQLITE_, READONLY)     /* Attempt to write a readonly database */
    WXJS_CONSTANT(SQLITE_, INTERRUPT)    /* Operation terminated by sqlite_interrupt() */
    WXJS_CONSTANT(SQLITE_, IOERR)        /* Some kind of disk I/O error occurred */
    WXJS_CONSTANT(SQLITE_, CORRUPT)      /* The database disk image is malformed */
    WXJS_CONSTANT(SQLITE_, NOTFOUND)     /* (Internal Only) Table or record not found */
    WXJS_CONSTANT(SQLITE_, FULL)         /* Insertion failed because database is full */
    WXJS_CONSTANT(SQLITE_, CANTOPEN)     /* Unable to open the database file */
    WXJS_CONSTANT(SQLITE_, PROTOCOL)     /* Database lock protocol error */
    WXJS_CONSTANT(SQLITE_, EMPTY)        /* (Internal Only) Database table is empty */
    WXJS_CONSTANT(SQLITE_, SCHEMA)       /* The database schema changed */
    WXJS_CONSTANT(SQLITE_, TOOBIG)       /* Too much data for one row of a table */
    WXJS_CONSTANT(SQLITE_, CONSTRAINT)   /* Abort due to constraint violation */
    WXJS_CONSTANT(SQLITE_, MISMATCH)     /* Data type mismatch */
    WXJS_CONSTANT(SQLITE_, MISUSE)       /* Library used incorrectly */
    WXJS_CONSTANT(SQLITE_, NOLFS)        /* Uses OS features not supported on host */
    WXJS_CONSTANT(SQLITE_, AUTH)         /* Authorization denied */
    WXJS_CONSTANT(SQLITE_, ROW)          /* sqlite_step() has another row ready */
    WXJS_CONSTANT(SQLITE_, DONE)         /* sqlite_step() has finished executing */
WXJS_END_CONSTANT_MAP()
/***
 * <ctor>
 *  <function>
 *   <arg name="Filename" type=WXJS_TYPE_STRING>The name of the database file</arg>
 *  </function>
 *  <desc>
 *   Constructs a new SQLiteDatabase object
 *  </desc>
 * </ctor>
 */
//Database* Database::Construct(JSContext *cx, JSObject *obj, uintN WXUNUSED(argc), jsval* argv, bool WXUNUSED(constructing))
//{
WXJS_BEGIN_CONSTRUCTOR(Database, Database)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    Database *database = new Database(cx, obj);
    sqlite3* db;
	
	wxString name;
	FromJS(cx, argv[0], name);
	
	sqlite3_open16(name, &db);
    ((DatabaseRefData*)database->GetRefData())->SetHandle(db);

    return database;
WXJS_END_CONSTRUCTOR

/***
 * <properties>
 *  <property name="autocommit" type="Boolean" readonly="Y">
 *   Test to see whether or not the database connection is in autocommit mode. 
 *   Return TRUE if it is and FALSE if not. Autocommit mode is on by default. 
 *   Autocommit is disabled by a BEGIN statement and reenabled by the next 
 *   COMMIT or ROLLBACK.
 *  </property>
 *  <property name="changes" type=WXJS_TYPE_NUMBER readonly="Y">
 *   This property returns the number of database rows that were changed (or inserted or deleted) 
 *   by the most recently completed INSERT, UPDATE, or DELETE statement. Only changes that are directly 
 *   specified by the INSERT, UPDATE, or DELETE statement are counted. Auxiliary changes caused by 
 *   triggers are not counted. See @sqlite.Database#totalChanges
 *  </property>
 *  <property name="lastInsertRowID" type=WXJS_TYPE_DOUBLE readonly="Y">
 *   Each entry in an SQLite table has a unique integer key called the "rowid". 
 *   The rowid is always available as an undeclared column named ROWID, OID, or _ROWID_. 
 *   If the table has a column of type INTEGER PRIMARY KEY then that column is 
 *   another an alias for the rowid.
 *   <br /><br />
 *   This property returns the rowid of the most recent INSERT into the database from the database
 *   connection. If no inserts have ever occurred on this database connection, zero is returned.
 *   <br /><br />
 *   If an INSERT occurs within a trigger, then the rowid of the inserted row is returned by this
 *   routine as long as the trigger is running. But once the trigger terminates, the value returned by 
 *   this routine reverts to the last value inserted before the trigger fired. 
 *  </property>
 *  <property name="errMsg" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns the error message from the most recent sqlite method call.
 *  </property>
 *  <property name="errNo" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns the error number from the most recent sqlite method call.
 *  </property>
 *  <property name="onCommit" type="Function">
 *   Register a callback function to be invoked whenever a new transaction is committed.
 *   If the callback function returns non-zero, then the commit is converted into a rollback.
 *  </property>
 *  <property name="onTrace" type="Function">
 *   Register a function that is called each time an SQL statement is evaluated. 
 *   The function receives the SQL statement as argument.
 *  </property>
 *  <property name="onRollback" type="Function">
 *   Register a callback to be invoked whenever a transaction is rolled back.
 *  </property>
 *  <property name="onUpdate" type="Function">
 *   Register a callback function with the database to be invoked whenever a row is updated, 
 *   inserted or deleted.
 *   <br /><br />
 *   The function gets 4 arguments: The first argument is one of SQLite.INSERT, SQLite.DELETE 
 *   or SQLite.UPDATE, depending on the operation that caused the callback to be invoked. 
 *   The second and third arguments to the callback contains the database and table name from the affected row. 
 *   The final callback parameter is the rowid of the row. In the case of an update, this is the rowid after the
 *   update takes place.
 *  </property>
 *  <property name="opened" type="Boolean" readonly="Y">
 *   Returns true when the database was successfully opened
 *  </property>
 *  <property name="totalChanges" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Use this property to find the total number of changes including changes caused 
 *   by triggers. See @sqlite.Database#changes
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Database)
    WXJS_READONLY_PROPERTY(P_AUTO_COMMIT, "autoCommit")
	WXJS_READONLY_PROPERTY(P_ERRMSG, "errMsg")
	WXJS_READONLY_PROPERTY(P_ERRNO, "errNo")
    WXJS_READONLY_PROPERTY(P_CHANGES, "changes")
    WXJS_READONLY_PROPERTY(P_LAST_ROWID, "lastInsertRowID")
    WXJS_READONLY_PROPERTY(P_OPENED, "opened")
WXJS_END_PROPERTY_MAP()
 
//bool Database::GetProperty(Database *p, JSContext *cx, JSObject* WXUNUSED(obj), int id, jsval *vp)
//{
WXJS_BEGIN_GET_PROP(Database, Database)
    sqlite3* db = ((DatabaseRefData*) p->GetRefData())->GetHandle();
	switch(id)
	{
    case P_OPENED:
        ToJSVal(cx, vp, db != NULL);
        break;
    case P_AUTO_COMMIT:
        {
            ToJSVal(cx, vp, sqlite3_get_autocommit(db) > 0);
            break;
        }
	case P_ERRMSG:
		{
			wxMBConvUTF16 conv;
			wxString errMsg(sqlite3_errmsg(db), conv);
			ToJSVal(cx, vp, errMsg);
			break;
		}
	case P_ERRNO:
		{
			ToJSVal(cx, vp, sqlite3_errcode(db));
			break;
		}
    case P_CHANGES:
        {
            ToJSVal(cx, vp, sqlite3_changes(db));
            break;
        }
    case P_TOTAL_CHANGES:
        {
            ToJSVal(cx, vp, sqlite3_total_changes(db));
            break;
        }
    case P_LAST_ROWID:
        {
            ToJSVal<double>(cx, vp, sqlite3_last_insert_rowid(db));
            break;
        }
	}
	return true;
WXJS_END_GET_PROP

//bool Database::AddProperty(Database *p, JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), 
//                           const wxString &prop, jsval* WXUNUSED(vp))
//{
WXJS_BEGIN_ADD_PROP(Database, Database)
    sqlite3* db = ((DatabaseRefData*) p->GetRefData())->GetHandle();
    if ( prop.IsSameAs(wxT("onCommit")) )
        sqlite3_commit_hook(db, Database::CommitHook, p);
    else if ( prop.IsSameAs(wxT("onRollback")) )
        sqlite3_rollback_hook(db, Database::RollbackHook, p);
    else if ( prop.IsSameAs(wxT("onTrace")) )
        sqlite3_trace(db, Database::Trace, p);
    else if ( prop.IsSameAs(wxT("onUpdate")) )
        sqlite3_update_hook(db, Database::Update, p);
    return true;
WXJS_END_ADD_PROP

WXJS_BEGIN_METHOD_MAP(Database)
	WXJS_METHOD("prepare", prepare, 1)
	WXJS_METHOD("exec", exec, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="execute">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="SQL" type=WXJS_TYPE_STRING>An SQL statement</arg>
 *  </function>
 *  <desc>
 *   Executes an SQL statement immediately. 
 *  </desc>
 * </method>
 */
JSBool Database::exec(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	Database *p = GetPrivate(cx, obj);
    sqlite3* db = ((DatabaseRefData*) p->GetRefData())->GetHandle();
	
    wxString SQL;
    FromJS(cx, argv[0], SQL);
    sqlite3_stmt *stmt;
	const void *pzTail;
	//TODO: test length
    int rc;
	if ( (rc = sqlite3_prepare16(db, SQL, SQL.length() * sizeof(wxChar), &stmt, &pzTail)) == SQLITE_OK )
	{
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
	}	
    *vp = ToJS(cx, rc);
	return JS_TRUE;
}

/***
 * <method name="prepare">
 *  <function returns="@sqlite.Statement">
 *   <arg name="SQL" type=WXJS_TYPE_STRING>An SQL statement</arg>
 *  </function>
 *  <desc>
 *   To execute an SQL query, it must first be compiled into a byte-code program using prepare.
 *  </desc>
 * </method>
 */
JSBool Database::prepare(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	Database *p = GetPrivate(cx, obj);	
    sqlite3* db = ((DatabaseRefData*) p->GetRefData())->GetHandle();
	
	wxString SQL;
	FromJS(cx, argv[0], SQL);
	
	sqlite3_stmt *stmt;
	const void *pzTail;
	//TODO: test length
	if ( sqlite3_prepare16(db, SQL, SQL.length() * sizeof(wxChar), &stmt, &pzTail) == SQLITE_OK )
	{
		*vp = Statement::CreateObject(cx, NULL);
        JSObject *objStmt = JSVAL_TO_OBJECT(*vp);
		JS_SetPrivate(/*cx,*/ objStmt, new Statement(*p, stmt));
	}
	return JS_TRUE;
}

WXJS_BEGIN_STATIC_METHOD_MAP(Database)
    WXJS_METHOD("complete", complete, 1)
WXJS_END_METHOD_MAP()

/***
 * <class_method name="complete">
 *  <function returns="Boolean">
 *   <arg name="SQL" type=WXJS_TYPE_STRING>An SQL string</arg>
 *  </function>
 *  <desc>
 *   This function returns true if the given input string comprises one or more complete SQL statements
 *  </desc>
 * </class_method>
 */
JSBool Database::complete(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxString SQL;
    FromJS(cx, argv[0], SQL);
    int rc = sqlite3_complete16(SQL);
    *vp = rc == 0 ? JSVAL_FALSE : JSVAL_TRUE;
	return JS_TRUE;
}
