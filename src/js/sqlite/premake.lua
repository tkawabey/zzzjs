package.name = "sqlite"
package.kind = "dll"
package.target = "wxJS_sqlite"
package.buildflags = { "unicode", "no-64bit-checks", "no-edit-and-continue" }
package.defines = { project.defines, "WXJSDLL_BUILD", "SQLITE_ENABLE_COLUMN_METADATA", "NO_TCL" }

-- Set the include paths
tinsert(package.config["Debug"].includepaths, wx_debug_include)
tinsert(package.config["Release"].includepaths, wx_release_include)
package.includepaths = { js_include, "./sqlite_src" }

-- Set the library paths
if ( windows ) then
  tinsert(package.libpaths, wx_lib)
  tinsert(package.libpaths, js_lib)
end

if ( windows ) then
  package.config["Debug"].links = { "wxbase28ud", "js32mtd" }
  package.config["Release"].links = { "wxbase28u", "js32mt" }
  tinsert(package.config["Debug"].libpaths, "../ext/Debug")
  tinsert(package.config["Release"].libpaths, "../ext/Release")
  package.links = { "shell32", "ole32", "advapi32", "user32", "wsock32" }
elseif ( linux ) then
  tinsert(package.buildoptions, "`" .. wx_lib .. "/wx-config --cxxflags` -W -Wall")
  tinsert(package.linkoptions,  "`" .. wx_lib .. "/wx-config --libs`")
end

tinsert(package.links, "wxJS_ext")

package.files = { matchfiles("*.cpp", "*.h"), 
                  "../common/type.cpp", "../common/type.h", 
                  "../common/jsutil.cpp", "../common/jsutil.h",
                  matchfiles("sqlite_src/*.c", "sqlite_src/*.h") }
