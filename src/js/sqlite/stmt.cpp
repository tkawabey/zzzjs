/*
 * wxJavaScript - stmt.cpp
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
 * $Id: stmt.cpp 810 2007-07-13 20:07:05Z fbraem $
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


#include "js/common/jsutil.h"
#include "js/ext/wxjs_ext.h"
#include "js/sqlite/db.h"
#include "js/sqlite/stmt.h"

using namespace zzzJs;
using namespace zzzJs::sqlite;

/***
 * <module>sqlite</module>
 * <file>stmt</file>
 * <class name="sqlite.Statement">
 *  Implements an sqlite statement. Use the
 *  @sqlite.Database#prepare method to create a SQLite SQL statement.
 * </class>
 */
WXJS_INIT_CLASS(Statement, "Statement", 0)

/***
 * <properties>
 *  <property name="columnCount" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Return the number of columns in the result set returned by the prepared 
 *   SQL statement.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Statement)
  WXJS_READONLY_PROPERTY(P_COLUMNCOUNT, "columnCount")
WXJS_END_PROPERTY_MAP()
 
//bool Statement::GetProperty(Statement *p, 
//                            JSContext *cx, 
//                            JSObject* WXUNUSED(obj), 
//                            int id, 
//                            jsval *vp)
//{
//
WXJS_BEGIN_GET_PROP(Statement, Statement)
  switch(id)
  {
    case P_COLUMNCOUNT:
      {
        ToJSVal(cx, vp, sqlite3_column_count(p->m_pStmt));
        break;
      }
  }
  return true;
WXJS_END_GET_PROP

WXJS_BEGIN_METHOD_MAP(Statement)
  WXJS_METHOD("bind", bind, 2)
  WXJS_METHOD("columnOriginalName", columnOriginalName, 1)
  WXJS_METHOD("columnDeclType", columnDeclType, 1)
  WXJS_METHOD("columnName", columnName, 1)
  WXJS_METHOD("columnTableName", columnTableName, 1)
  //WXJS_METHOD("clearBindings", clearbindings, 0)
  WXJS_METHOD("fetchObject", fetchObject, 0)
  WXJS_METHOD("fetchArray", fetchArray, 0)
  WXJS_METHOD("step", step, 0)
  WXJS_METHOD("reset", reset, 0)
WXJS_END_METHOD_MAP()

/***
 * <method name="bind">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Parameter" type=WXJS_TYPE_NUMBER>
 *    Number of parameter (index starts at 1)
 *   </arg>
 *   <arg name="Value" type="Mixed">The value to bind</arg>
 *  </function>
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Parameter" type=WXJS_TYPE_STRING>
 *    The name of the parameter
 *   </arg>
 *   <arg name="Value" type="Mixed">The value to bind</arg>
 *  </function>
 *  <desc>
 *   In the SQL strings input to @sqlite.Database#prepare, one or more literals 
 *   can be replace by a parameter "?" or ":AAA" or "$VVV" where AAA is an 
 *   alphanumeric identifier and VVV is a variable name according to the syntax
 *   rules of the TCL programming language. The values of these parameters 
 *   (also called "host parameter names") can be set using bind.
 *   <br /><br />
 *   The first argument to bind is the index or the name of the parameter 
 *   to be set. The first parameter has an index of 1. 
 *   <br /><br />
 *   The second argument is the value to bind to the parameter.
 *   <br /><br />
 *   bind must be called after @sqlite.Database#prepare or
 *   @sqlite.Statement#reset and before sqlite3_step(). Bindings are not 
 *   cleared by the @sqlite.Statement#reset. 
 *   Unbound parameters are interpreted as NULL.
 *   <br /><br />
 *   bind returns SQLite.OK on success or an error code if anything goes wrong. 
 *   SQLite.RANGE is returned if the parameter index is out of range. 
 *   SQLite.NOMEM is returned if malloc fails. SQLite.MISUSE is returned 
 *   if these routines are called on a virtual machine that is the wrong state 
 *   or which has already been finalized.
 *   <br /><br />
 *   Blobs are supported. Use a @wxMemoryBuffer instance as value.
 *  </desc>
 * </method>
 */
JSBool Statement::bind(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj); 
  if ( p == NULL )
  {
    *vp = ToJS(cx, SQLITE_MISUSE);
  }
  else
  {
    int param = 0;
    if ( JSVAL_IS_INT(argv[0]) )
    {
      FromJS(cx, argv[0], param);
    }
    else
    {
      wxString name;
      FromJS(cx, argv[0], name);
      
      param = sqlite3_bind_parameter_index(p->m_pStmt, name.ToAscii());
    }
    
    if ( param == 0 )
    {
      JS_ReportError(cx, "Invalid parameter index in sqlite.Statement.bind");
      return JS_FALSE;
    }
    
    if ( JSVAL_IS_VOID(argv[1]) )
    {
      *vp = ToJS(cx, sqlite3_bind_null(p->m_pStmt, param));
    }
    else if ( JSVAL_IS_INT(argv[1]) )
    {
      int value;
      FromJS(cx, argv[1], value);
      *vp = ToJS(cx, sqlite3_bind_int(p->m_pStmt, param, value));
    }
    else if ( JSVAL_IS_DOUBLE(argv[1]) )
    {
      double value;
      FromJS(cx, argv[1], value);
      *vp = ToJS(cx, sqlite3_bind_double(p->m_pStmt, param, value));
    }
	else if (    argv[1].isObject()
              && zzzJs::HasPrototype(cx, argv[1], "MemoryBuffer") )
    {
        wxMemoryBuffer *buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[1]));
        if ( buffer != NULL )
        {
          *vp = ToJS(cx, sqlite3_bind_blob(p->m_pStmt, 
                                             param,
                                             buffer->GetData(),
                                             buffer->GetDataLen(),
                                             SQLITE_TRANSIENT));
        }
        else
        {
          return JS_FALSE;
        }
    }
    else
    {
      wxString value;
      FromJS(cx, argv[1], value);
      *vp = ToJS(cx, sqlite3_bind_text16(p->m_pStmt, 
                                           param, 
                                           value, 
                                           value.length() * 2,
                                           SQLITE_TRANSIENT));
    }
  }
  return JS_TRUE;
}

/**
 * <method name="clearBindings">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   Clear all the parameter bindings
 *  </desc>
 * </method>
 */
// Not yet available on windows 
// See: http://www.sqlite.org/cvstrac/tktview?tn=1762,29
/*
JSBool Statement::clearbindings(JSContext *cx, 
                                JSObject *obj, 
                                uintN argc, 
                                jsval *argv, 
                                jsval *rval)
{
  Statement *p = GetPrivate(cx, obj); 
  if ( p == NULL )
  {
    *rval = ToJS(cx, SQLITE_MISUSE);
  }
  else
  {
      *rval = ToJS(cx, sqlite3_clear_bindings(p->m_pStmt));
  }
  return JS_TRUE;
}
*/

/***
 * <method name="columnDeclType">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Column" type=WXJS_TYPE_NUMBER>The number of the column</arg>
 *  </function>
 *  <desc>
 *   The declared type of the table column is returned. 
 *   If the column of the result set is not a table column, then null 
 *   is returned. For example, in the database schema:
 *   <pre>
 *   CREATE TABLE t1(c1 INTEGER);</pre>
 *   And the following statement compiled:
 *   <pre>
 *   SELECT c1 + 1, c1 FROM t1;</pre>
 *   Then this method would return the string "INTEGER" for the second result column (Column==1),
 *   and nullL for the first result column (Column==0).
 *   <br />
 *   If the following statements were compiled then this method would return "INTEGER" 
 *   for the first (only) result column.
 *   <pre>
 *   SELECT (SELECT c1) FROM t1;
 *   SELECT (SELECT c1 FROM t1);
 *   SELECT c1 FROM (SELECT c1 FROM t1);
 *   SELECT * FROM (SELECT c1 FROM t1);
 *   SELECT * FROM (SELECT * FROM t1);</pre>
 *  </desc>
 * </method>
 */
JSBool Statement::columnDeclType(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj);

  if ( p != NULL )
  {
      int column;
      if ( FromJS(cx, argv[0], column) )
      {
          wxMBConvUTF16 conv;
          const void *type = sqlite3_column_decltype16(p->m_pStmt, column);
          if ( type == NULL )
          {
              *vp = JSVAL_VOID;
          }
          else
          {
            wxString jsType((const char*) type, conv);
            *vp = ToJS(cx, jsType);
          }
      }
  }
  else
  {
      *vp = JSVAL_VOID;
  }
  return JS_TRUE;
}

/***
 * <method name="columnName">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Column" type=WXJS_TYPE_NUMBER>The number of the column</arg>
 *  </function>
 *  <desc>
 *   This function returns the column heading for the column of this statement,
 *  </desc>
 * </method>
 */
JSBool Statement::columnName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj);

  if ( p != NULL )
  {
      int column;
      if ( FromJS(cx, argv[0], column) )
      {
          wxMBConvUTF16 conv;
          const void *name = sqlite3_column_name16(p->m_pStmt, column);
          if ( name == NULL )
          {
              *vp = JSVAL_VOID;
          }
          else
          {
            wxString jsName((const char*) name, conv);
            *vp = ToJS(cx, jsName);
          }
      }
  }
  else
  {
      *vp = JSVAL_VOID;
  }
  return JS_TRUE;
}

/***
 * <method name="columnOriginalName">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Column" type=WXJS_TYPE_NUMBER>The number of the column</arg>
 *  </function>
 *  <desc>
 *   If the column returned by the statement is a column reference,
 *   this function may be used to access the schema name of the referenced 
 *   column in the database schema. If the column is not a column reference,
 *   NULL is returned.
 *  </desc>
 * </method>
 */
JSBool Statement::columnOriginalName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj);

  if ( p != NULL )
  {
      int column;
      if ( FromJS(cx, argv[0], column) )
      {
          wxMBConvUTF16 conv;
          const void *original = sqlite3_column_origin_name16(p->m_pStmt, column);
          if ( original == NULL )
          {
              *vp = JSVAL_VOID;
          }
          else
          {
            wxString originalName((const char*) original, conv);
            *vp = ToJS(cx, originalName);
          }
      }
      else
      {
          *vp = JSVAL_VOID;
      }
  }
  else
  {
      *vp = JSVAL_VOID;
  }
  return JS_TRUE;
}

/***
 * <method name="columnTableName">
 *  <function returns=WXJS_TYPE_STRING>
 *   <arg name="Column" type=WXJS_TYPE_NUMBER>The number of the column</arg>
 *  </function>
 *  <desc>
 *   If the column returned by the statement is a column reference, 
 *   this function may be used to access the name of the table that 
 *   contains the column. 
 *   If the column is not a column reference, null is returned.
 *  </desc>
 * </method>
 */
JSBool Statement::columnTableName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj);

  if ( p != NULL )
  {
      int column;
      if ( FromJS(cx, argv[0], column) )
      {
          wxMBConvUTF16 conv;
          const void *tableName = sqlite3_column_table_name16(p->m_pStmt, column);
          if ( tableName == NULL )
          {
              *vp = JSVAL_VOID;
          }
          else
          {
            wxString jsTableName((const char*) tableName, conv);
            *vp = ToJS(cx, jsTableName);
          }
      }
      else
      {
          *vp = JSVAL_VOID;
      }
  }
  else
  {
      *vp = JSVAL_VOID;
  }
  return JS_TRUE;
}

/***
 * <method name="fetchArray">
 *  <function returns="Array" />
 *  <desc>
 *   This method calls @sqlite.Statement#step and returns
 *   the row in an array. An empty array will be returned
 *   when no rows are available anymore.
 *  </desc>
 * </method>
 */
JSBool Statement::fetchArray(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  wxMBConvUTF16 conv;
  Statement *p = GetPrivate(cx, obj);
  
  JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
  *vp = OBJECT_TO_JSVAL(objArray);
  if (    p != NULL 
       && sqlite3_step(p->m_pStmt) == SQLITE_ROW )
  {
    int columnCount = sqlite3_column_count(p->m_pStmt);
    if ( columnCount > 0 )
    {
      for(int i = 0; i < columnCount; i++)
      {
        jsval jsValue;
        switch(sqlite3_column_type(p->m_pStmt, i))
        {
          case SQLITE_INTEGER:
            jsValue = ToJS(cx, sqlite3_column_int(p->m_pStmt, i));
            break;
          case SQLITE_FLOAT:
            jsValue = ToJS(cx, sqlite3_column_double(p->m_pStmt, i));
            break;
          case SQLITE_TEXT:
            {
                sqlite3_column_bytes16(p->m_pStmt, i);
                wxString value((const char*) sqlite3_column_text16(p->m_pStmt, i), conv);
                jsValue = ToJS(cx, value);
            }
            break;
          case SQLITE_BLOB:
            {
                jsValue = zzzJs::ext::CreateMemoryBuffer(cx, 
                                                       (void *) sqlite3_column_blob(p->m_pStmt, i), 
                                                        sqlite3_column_bytes(p->m_pStmt, i));
            }
            break;
          case SQLITE_NULL:
            break;
        }
        JS_SetElement(cx, objArray, i, &jsValue);
      }
    }
  }
  return JS_TRUE;
}                             

/***
 * <method name="fetchObject">
 *  <function returns="Object" />
 *  <desc>
 *   This method calls @sqlite.Statement#step and returns
 *   the row as a JavaScript object. null will be returned
 *   when no rows are available anymore.
 *  </desc>
 * </method>
 */
JSBool Statement::fetchObject(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  wxMBConvUTF16 conv;
  Statement *p = GetPrivate(cx, obj);
  
  *vp = JSVAL_VOID;
  if (    p != NULL 
       && sqlite3_step(p->m_pStmt) == SQLITE_ROW )
  {
    int columnCount = sqlite3_column_count(p->m_pStmt);
    if ( columnCount > 0 )
    {
      JSObject *jsRow = JS_NewObject(cx, NULL, NULL, NULL);
      *vp = OBJECT_TO_JSVAL(jsRow);
      for(int i = 0; i < columnCount; i++)
      {
        wxString columnName((const char*) sqlite3_column_name16(p->m_pStmt, i), conv);
        jsval jsValue = JSVAL_VOID;
        switch(sqlite3_column_type(p->m_pStmt, i))
        {
          case SQLITE_INTEGER:
            jsValue = ToJS(cx, sqlite3_column_int(p->m_pStmt, i));
            break;
          case SQLITE_FLOAT:
            jsValue = ToJS(cx, sqlite3_column_double(p->m_pStmt, i));
            break;
          case SQLITE_TEXT:
            {
                sqlite3_column_bytes16(p->m_pStmt, i);
                wxString value((const char*) sqlite3_column_text16(p->m_pStmt, i), conv);
                jsValue = ToJS(cx, value);
            }
            break;
          case SQLITE_BLOB:
            {
                jsValue = zzzJs::ext::CreateMemoryBuffer(cx, 
                                                        (void *) sqlite3_column_blob(p->m_pStmt, i), 
                                                        sqlite3_column_bytes(p->m_pStmt, i));
            }
            break;
          case SQLITE_NULL:
            break;
        }
        wxDefineProperty(cx, jsRow, columnName, &jsValue);
      }
    }
  }
  return JS_TRUE;
}                             

/***
 * <method name="step">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   After an SQL query has been prepared with a call to either
 *   @sqlite.Database#prepare, then this method must be called one or more times 
 *   to execute the statement. The return value will be either SQLite.BUSY, 
 *   SQLite.DONE, SQLite.ROW, SQLite.ERROR, or SQLite.MISUSE.
 *   <ul>
 *    <li>
 *     SQLite.BUSY means that the database engine attempted to open a locked 
 *     database and there is no busy callback registered. 
 *     Call step again to retry the open.
 *    </li>
 *    <li>
 *     SQLite.DONE means that the statement has finished executing successfully. 
 *     step should not be called again on this virtual machine without first 
 *     calling @sqlite.Statement#reset to reset the virtual machine back to its 
 *     initial state.
 *    </li>
 *    <li>
 *     If the SQL statement being executed returns any data, then SQLite.ROW 
 *     is returned each time a new row of data is ready for processing by the 
 *     caller. Call step again to retrieve the next row of data.
 *    </li>
 *    <li>
 *     SQLite.ERROR means that a run-time error (such as a constraint violation)
 *     has occurred. step should not be called again on the VM. More 
 *     information may be found in the property @sqlite.Statement#errmsg.
 *    </li>
 *    <li>
 *     SQLite.MISUSE means that the this routine was called inappropriately. 
 *     Perhaps it was called on a virtual machine that had already been 
 *     finalized or on one that had previously returned SQLite.ERROR or
 *     SQLite.DONE. Or it could be the case that a database connection is being 
 *     used by a different thread than the one it was created it. 
 *     <br /><br />
 *     SQLite.MISUSE is also returned when the associated SQLiteDatabase object 
 *     is not available anymore. This can occur when the SQLiteDatabase is
 *     finalized (when the variable gets out of scope for example). 
 *     Make sure the SQLiteDatabase object is still 
 *     referenced somewhere by a local or global variable.
 *    </li>
 *   </ul>
 *  </desc>
 * </method>
 */
JSBool Statement::step(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj); 
  if ( p == NULL )
  {
    *vp = ToJS(cx, SQLITE_MISUSE);
  }
  else
  {
    *vp = ToJS(cx, sqlite3_step(p->m_pStmt));
  }
  return JS_TRUE;
}

/***
 * <method name="reset">
 *  <function returns=WXJS_TYPE_NUMBER />
 *  <desc>
 *   The reset function is called to reset a prepared SQL statement obtained 
 *   by a previous call to @sqlite.Database#prepare back to it's initial state, 
 *   ready to be re-executed.
 *  </desc>
 * </method>
 */
JSBool Statement::reset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
  Statement *p = GetPrivate(cx, obj); 
  if ( p == NULL )
  {
    *vp = ToJS(cx, SQLITE_MISUSE);
  }
  else
  {
    *vp = ToJS(cx, sqlite3_reset(p->m_pStmt));
  }
  return JS_TRUE;
}
