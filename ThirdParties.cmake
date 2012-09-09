
FUNCTION(LINK_THIRDPARTY project extpj base)
  IF (MSVC)
    TARGET_LINK_LIBRARIES(${project} debug ${base}_d optimized ${base})
  ELSE()
    TARGET_LINK_LIBRARIES(${project} ${extpj})
  ENDIF()
ENDFUNCTION(LINK_THIRDPARTY)

FUNCTION(LINK_THIRDPARTY_EXT project extpj base)
  LINK_THIRDPARTY(${project} ${extpj} ${base})
  ADD_DEPENDENCIES(${project} ${extpj}-ext)
ENDFUNCTION(LINK_THIRDPARTY_EXT)

FUNCTION(LINK_THIRDPARTY_GFLAGS project)
  IF(MSVC)
    ADD_DEPENDENCIES(${project} gflags-ext)
  ELSE()
    LINK_THIRDPARTY_EXT(${project} gflags libgflags)
  ENDIF(MSVC)  
ENDFUNCTION(LINK_THIRDPARTY_GFLAGS)

FUNCTION(LINK_THIRDPARTY_GLUT project)
  FIND_PACKAGE(GLUT REQUIRED)
  TARGET_LINK_LIBRARIES(${project} ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY})
ENDFUNCTION(LINK_THIRDPARTY_GLUT)

FUNCTION(LINK_THIRDPARTY_GTEST project)
  ADD_DEPENDENCIES(${project} gtest)
  TARGET_LINK_LIBRARIES(${project} gtest)
ENDFUNCTION(LINK_THIRDPARTY_GTEST)

FUNCTION(LINK_THIRDPARTY_GTEST_MAIN project)
  LINK_THIRDPARTY(${project} gtest_main libgtest_main)
  ADD_DEPENDENCIES(${project} gtest_main)
  TARGET_LINK_LIBRARIES(${project} gtest_main)
ENDFUNCTION(LINK_THIRDPARTY_GTEST_MAIN)

FUNCTION(LINK_THIRDPARTY_TINYXML project)
  ADD_DEPENDENCIES(${project} tinyxml2static)
  TARGET_LINK_LIBRARIES(${project} tinyxml2static)
ENDFUNCTION(LINK_THIRDPARTY_TINYXML)


