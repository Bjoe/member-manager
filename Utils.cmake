# Siehe http://developer.qt.nokia.com/wiki/UnitTesting
MACRO(qt4_add_test testname testsrc)
     SET(test_${testname}_SRCS ${testsrc})

     SET(special_additional)
     FOREACH(_additional ${ARGN})
	  LIST(APPEND special_additional ${_additional})
     ENDFOREACH(_additional)
  
     qt4_automoc(${test_${testname}_SRCS} ${special_additional})
     add_executable(test_${testname} ${test_${testname}_SRCS} ${special_additional} ${test_additional})
     target_link_libraries(test_${testname} ${test_additional_lib} ${QT_LIBRARIES})

# ${QT_QTCORE_LIBRARY}
#              ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY} 
#              ${GSOAP_LIBRARIES} ${QT_QTLOCATION_LIBRARY})
  
     ADD_TEST(test_${testname} test_${testname})
ENDMACRO(qt4_add_test)

# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects
MACRO(find_doxygen)
    # check if doxygen is even installed
    find_package(Doxygen) # REQUIRED)

    if(EXISTS ${DOXYGEN_EXECUTABLE})
        # prepare doxygen configuration file
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        # add doxygen as target
        add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        # cleanup $build/api-doc on "make clean"
        set_property(DIRECTORY APPEND PROPERTY
             ADDITIONAL_MAKE_CLEAN_FILES api-doc)

        # add doxygen as dependency to doc-target
        get_target_property(DOC_TARGET doc TYPE)
        if(NOT DOC_TARGET)
            add_custom_target(doc)
        endif()
        add_dependencies(doc doxygen)

        # install HTML API documentation and manual pages
        set(DOC_PATH "share/doc/${CPACK_PACKAGE_NAME}-${VERSION}")
        #
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/html
                 DESTINATION ${DOC_PATH}
               )
        #
        # install man pages into packages, scope is now project root..
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/man/man3
                 DESTINATION share/man/man3/
               )
    endif()
ENDMACRO(find_doxygen)
