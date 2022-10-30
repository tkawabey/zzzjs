package.name = "expat"
package.kind = "dll"
package.language = "c++"
package.target = "wxJS_expat"
package.buildflags = { "unicode", "no-64bit-checks", "no-edit-and-continue" }
package.defines = { project.defines, "WXJSDLL_BUILD", "XML_UNICODE", "XML_BUILDING_EXPAT" }

if ( linux ) then
  tinsert(package.defines, "HAVE_EXPAT_CONFIG_H");
end

-- Set the include paths
tinsert(package.config["Debug"].includepaths, wx_debug_include)
tinsert(package.config["Release"].includepaths, wx_release_include)
tinsert(package.includepaths, js_include)

-- Set the library paths
tinsert(package.libpaths, { wx_lib, js_lib })
if ( windows ) then
  tinsert(package.defines, "COMPILED_FROM_DSP")
  package.config["Debug"].links = { "wxbase28ud", "js32mtd" }
  package.config["Release"].links = { "wxbase28u", "js32mt" }
  package.links = { "shell32", "ole32", "advapi32", "user32", "wsock32" }
elseif ( linux ) then
  tinsert(package.buildoptions, "`" .. wx_lib .. "/wx-config --cxxflags` -W -Wall")
  tinsert(package.linkoptions,  "`" .. wx_lib .. "/wx-config --libs`")
end
tinsert(package.links, "wxJS_ext")

package.files = { matchfiles("*.cpp", "*.h"),
                  "expat_src/xmltok.c", "expat_src/xmlrole.c", "expat_src/xmlparse.c",  
                  matchfiles("expat_src/*.h"),
                  "../common/type.cpp", "../common/type.h", 
                  "../common/jsutil.cpp", "../common/jsutil.h",
                  "../common/wxjs.h" }
